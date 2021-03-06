/*
 * Copyright (C) 2015 Michal Podhradsky, michal.podhradsky@aggiemail.usu.edu
 * Utah State University, http://aggieair.usu.edu/
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
/**
 * @file Sender.h
 *
 * HITL demo version - main class that handles sending and receving of data
 * plus timing the simulation results
 *
 * @author Michal Podhradsky <michal.podhradsky@aggiemail.usu.edu>
 */
#ifndef SENDER_H_
#define SENDER_H_

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <fstream>

#include "LogTime.h"
#include "Autopilot.h"
#include "VectorNav.h"
#include "FDM.h"

#include "../../flight_gear.h"

#define DEBUG_SENDER 0

using boost::asio::ip::udp;

class Sender
{
private:
  boost::asio::io_service& io_service_;

  /*
   * When running Minion, we have 60Hz control loops and 100Hz VN but it seems to be working just fine, so
   * take it in account in future development
   */
  //const int send_rate_ = 16000; // us -> 60Hz VN data
  //const int send_rate_ = 10000; // us -> 100Hz VN data
  //const int send_rate_ = 5000; // us -> 200Hz VN data
  const int send_rate_ = 2500; // us -> 400Hz VN data

  boost::asio::ip::udp::endpoint endpoint_;
  boost::asio::ip::udp::socket socket_;

  boost::asio::deadline_timer timer_;
  boost::asio::deadline_timer timer_fg_;
  int milliseconds_;
  int sim_dt_us_;
  std::string message_;
  bool fg_udp_active;
  Autopilot *ap_;
  VectorNav *vn_;

  timeval start_time_;
  int fdm_counter_;

  AutopilotData rx_data_;
  VectorNavData tx_data_;

  vector<uint8_t> net_;
  struct FGNetFDM gui_;

  ofstream file_;
  string ext_ = "csv";
  string filename_;
  string endl_ = "\r\n";
  string separator_ = ",";
  string header_ = "";
  vector<string> vars_ = { { "timeLogger", "timeStartup",
                             "Yaw", "Pitch", "Roll",
                             "AngularRate-p", "AngularRate-q",  "AngularRate-r",
                             "Position-Lat", "Position-Lon", "Position-Alt",
                             "Velocity-N", "Velocity-E", "Velocity-D",
                             "Accel-x", "Accel-y", "Accel-z",
                             "Tow", "NumSats", "Fix", "PosU-N", "PosU-E", "PosU-D", "VelU",
                             "LinearAccelBody-x", "LinearAccelBody-y", "LinearAccelBody-z",
                             "YprU-Yaw", "YprU-Pitch", "YprU-Roll", "InsStatus",
                             "VelBody-x", "VelBody-y", "VelBody-z",
                             "ap_time", "COMMANDS_NB", "COMMAND_THROTTLE",
                             "COMMAND_ROLL", "COMMAND_PITCH", "COMMAND_YAW", "COMMAND_FLAPS", "COMMAND_DUMMY",
                             "alpha", "beta", "airspeed", "ap_settings"} };
  FDM fdm_;


void fg_prepare_data(){
  memset(&gui_, 0, sizeof(gui_));
  gui_.version = htonl(FG_NET_FDM_VERSION);

  gui_.latitude  = htond(fdm_.fdm.lla_pos.lat);
  gui_.longitude = htond(fdm_.fdm.lla_pos.lon);
  gui_.altitude  = htond(fdm_.fdm.lla_pos.alt);

  gui_.phi = htonf(fdm_.fdm.ltp_to_body_eulers.phi);
  gui_.theta = htonf(fdm_.fdm.ltp_to_body_eulers.theta);
  gui_.psi = htonf(fdm_.fdm.ltp_to_body_eulers.psi);

  gui_.alpha = htonf(rx_data_.alpha);                // angle of attack (radians)
  gui_.beta = htonf(rx_data_.beta);                 // side slip angle (radians)

  // Velocities
  // TODO: float phidot;               // roll rate (radians/sec)
  // TODO: float thetadot;             // pitch rate (radians/sec)
  // TODO: float psidot;               // yaw rate (radians/sec)
  // TODO: float vcas;                 // calibrated airspeed
  // TODO: float climb_rate;           // feet per second
  // TODO: float v_north;              // north velocity in local/body frame, fps
  // TODO: float v_east;               // east velocity in local/body frame, fps
  // TODO: float v_down;               // down/vertical velocity in local/body frame, fps
  // TODO: float v_body_u;    // ECEF velocity in body frame
  // TODO: float v_body_v;    // ECEF velocity in body frame
  // TODO: float v_body_w;    // ECEF velocity in body frame

  // Accelerations
  // TODO: float A_X_pilot;            // X accel in body frame ft/sec^2
  // TODO: float A_Y_pilot;            // Y accel in body frame ft/sec^2
  // TODO: float A_Z_pilot;            // Z accel in body frame ft/sec^2

  // Stall
  // TODO: float stall_warning;        // 0.0 - 1.0 indicating the amount of stall
  // TODO: float slip_deg;             // slip ball deflection

  // Pressure

  // Engine status
  gui_.num_engines = htonl(1);      // Number of valid engines
  // FIXME
  if (rx_data_.cmd_throttle_norm > 0.05) { // running engine
    gui_.eng_state[0] = htonl(2);// Engine state (off, cranking, running)
    gui_.rpm[0] = htonf(((float)rx_data_.cmd_throttle_norm)*1000); // magic constant
  }
  else { // engine off
    gui_.eng_state[0] = htonl(0);// Engine state (off, cranking, running)
    gui_.rpm[0] = htonf(0.0); // magic constant
  }

  // TODO: float rpm[FG_NET_FDM_MAX_ENGINES];       // Engine RPM rev/min
  // TODO: float fuel_flow[FG_NET_FDM_MAX_ENGINES]; // Fuel flow gallons/hr
  // TODO: float fuel_px[FG_NET_FDM_MAX_ENGINES];   // Fuel pressure psi
  // TODO: float egt[FG_NET_FDM_MAX_ENGINES];       // Exhuast gas temp deg F
  // TODO: float cht[FG_NET_FDM_MAX_ENGINES];       // Cylinder head temp deg F
  // TODO: float mp_osi[FG_NET_FDM_MAX_ENGINES];    // Manifold pressure
  // TODO: float tit[FG_NET_FDM_MAX_ENGINES];       // Turbine Inlet Temperature
  // TODO: float oil_temp[FG_NET_FDM_MAX_ENGINES];  // Oil temp deg F
  // TODO: float oil_px[FG_NET_FDM_MAX_ENGINES];    // Oil pressure psi

  // Consumables
  // TODO: uint32_t num_tanks;         // Max number of fuel tanks
  // TODO: float fuel_quantity[FG_NET_FDM_MAX_TANKS];

  // Gear status
  // TODO: uint32_t num_wheels;
  // TODO: uint32_t wow[FG_NET_FDM_MAX_WHEELS];
  // TODO: float gear_pos[FG_NET_FDM_MAX_WHEELS];
  // TODO: float gear_steer[FG_NET_FDM_MAX_WHEELS];
  // TODO: float gear_compression[FG_NET_FDM_MAX_WHEELS];

  // Environment
  // TODO: uint32_t cur_time;           // current unix time
  // FIXME: make this uint64_t before 2038
  // TODO: int32_t warp;                // offset in seconds to unix time
  // TODO: float visibility;            // visibility in meters (for env. effects)

  // Control surface positions (normalized values)
  gui_.elevator = htonf(-1*(float)rx_data_.cmd_pitch_norm);
  gui_.elevator_trim_tab = htonf((float)0.0);
  gui_.left_flap = htonf((float)rx_data_.cmd_flaps_norm);
  gui_.right_flap= htonf((float)rx_data_.cmd_flaps_norm);
  gui_.left_aileron = htonf(-1*(float)rx_data_.cmd_roll_norm);
  gui_.right_aileron = htonf((float)rx_data_.cmd_roll_norm);
  gui_.rudder = htonf((float)rx_data_.cmd_yaw_norm);
  gui_.nose_wheel = htonf((float)0.0);
  gui_.speedbrake = htonf((float)0.0);
  gui_.spoilers = htonf((float)0.0);
}

public:
  Sender(boost::asio::io_service& io_service,
      short broadcast_port,
      int milliseconds,
      Autopilot *aut, VectorNav *vn, double dt, bool fg_bind,
      timeval start_t)
: endpoint_(boost::asio::ip::address_v4::broadcast(), broadcast_port),
  //socket_(io_service, endpoint_.protocol()),
  socket_(io_service, udp::endpoint(udp::v4(), broadcast_port)),
  timer_(io_service),
  timer_fg_(io_service),
  io_service_(io_service),
  fdm_(dt, start_t)

{
    // Port settings
    udp::resolver resolver(io_service_);
    udp::resolver::query query(udp::v4(), "127.0.01", "5501");
    endpoint_ = *resolver.resolve(query);


    // Simulation time
    start_time_ = start_t;
    sim_dt_us_ = (int)(dt*1e6);
    cout << "Dt us = " << sim_dt_us_ << endl;

    // Init flight related tasks
    ap_ = aut;
    vn_ = vn;

    // Calculate ration of sim steps/vn steps
    fdm_counter_ = send_rate_/sim_dt_us_;
    cout << "FDM counter = " << fdm_counter_ << endl;

    // structures
    rx_data_ = AutopilotData();
    tx_data_ = VectorNavData();

    // timing
    milliseconds_ = milliseconds;
    fg_udp_active = fg_bind; // will be fg binding

    // Open file
    filename_ = "var/logs/" + LogTime::get() + "." + ext_;
    cout << "Sender: Opening " << filename_ << endl;
    try {
      file_.open(filename_.c_str());
      write_header();
    }
    catch (const std::exception& e)
    {
      std::cout << "Sender: Exception: " << e.what() << "\n";
      exit(-1);
    }

    std::cout << "Sender Initialized \n";


    if(fg_bind) {
      handle_fg_timeout();
    }

    if (fdm_.isInitialized()){
      handle_sim_timer();
    }
    else {
      cout << "FDM not initialized, exiting..." << endl;
    }


}

  /**
   * Destructor - important to close the file
   */
  ~Sender(){
    file_.close();
  }

  /**
   * Write header to log file
   */
  void write_header(){
    vector<string>::iterator it;
    for(it = vars_.begin(); it != vars_.end() && (it+1 != vars_.end()); it++)
    {
        header_ = header_ + *it + separator_ + " ";
    }
    header_ = header_ + *it + endl_;
    file_ << header_;
    file_.flush();
  }

  /**
   * Write new data into log file
   */
  void write_row(){
    // drop the first packet we receive - for some reason it contains corrupted data
    static bool first;
    if (first== false) {
      first = true;
      return;
    }
    file_ << LogTime::getTimeSinceStart(start_time_) + separator_ + " "; // Logger timestamp
    file_ << boost::lexical_cast<string>(rx_data_.time_startup) + separator_ + " "; // IMU timestamp

    file_ << boost::lexical_cast<string>(rx_data_.YawPitchRoll[0]) + separator_ + " "; // Yaw
    file_ << boost::lexical_cast<string>(rx_data_.YawPitchRoll[1]) + separator_ + " "; // Pitch
    file_ << boost::lexical_cast<string>(rx_data_.YawPitchRoll[2]) + separator_ + " "; // Roll

    file_ << boost::lexical_cast<string>(rx_data_.angularRate[0]) + separator_ + " "; // rate P
    file_ << boost::lexical_cast<string>(rx_data_.angularRate[1]) + separator_ + " "; // rate Q
    file_ << boost::lexical_cast<string>(rx_data_.angularRate[2]) + separator_ + " "; // rate R

    file_ << boost::lexical_cast<string>(rx_data_.position[0]) + separator_ + " "; // Latitude
    file_ << boost::lexical_cast<string>(rx_data_.position[1]) + separator_ + " "; // Longitude
    file_ << boost::lexical_cast<string>(rx_data_.position[2]) + separator_ + " "; // Altitude

    file_ << boost::lexical_cast<string>(rx_data_.velocity_NED[0])  + separator_ + " "; // Velocity-N
    file_ << boost::lexical_cast<string>(rx_data_.velocity_NED[1])  + separator_ + " "; // Velocity-E
    file_ << boost::lexical_cast<string>(rx_data_.velocity_NED[2])  + separator_ + " "; // Velocity-D

    file_ << boost::lexical_cast<string>(rx_data_.accel[0])  + separator_ + " "; // accel-x
    file_ << boost::lexical_cast<string>(rx_data_.accel[1])  + separator_ + " "; // accel-y
    file_ << boost::lexical_cast<string>(rx_data_.accel[2])  + separator_ + " "; // accel-z

    file_ << boost::lexical_cast<string>(rx_data_.tow)  + separator_ + " "; // TimeOfWeek

    file_ << boost::lexical_cast<string>((int)rx_data_.numSats)  + separator_ + " "; // NumSats

    file_ << boost::lexical_cast<string>((int)rx_data_.gpsFix)  + separator_ + " "; // Gps Fix

    file_ << boost::lexical_cast<string>(rx_data_.posU[0])  + separator_ + " "; // PosU -N
    file_ << boost::lexical_cast<string>(rx_data_.posU[1])  + separator_ + " "; // PosU -E
    file_ << boost::lexical_cast<string>(rx_data_.posU[2])  + separator_ + " "; // PosU -D

    file_ << boost::lexical_cast<string>(rx_data_.velU)  + separator_ + " "; // VelU

    file_ << boost::lexical_cast<string>(rx_data_.linAccelBody[0])  + separator_ + " "; // LinAccelBody-x
    file_ << boost::lexical_cast<string>(rx_data_.linAccelBody[1])  + separator_ + " "; // LinAccelBody-y
    file_ << boost::lexical_cast<string>(rx_data_.linAccelBody[2])  + separator_ + " "; // LinAccelBody-z

    file_ << boost::lexical_cast<string>(rx_data_.yprU[0])  + separator_ + " "; // Yaw Uncertainty
    file_ << boost::lexical_cast<string>(rx_data_.yprU[1])  + separator_ + " "; // Pitch Uncertainty
    file_ << boost::lexical_cast<string>(rx_data_.yprU[2])  + separator_ + " "; // Roll Uncertainty

    file_ << boost::lexical_cast<string>(rx_data_.insStatus)  + separator_ + " "; // Ins Status

    file_ << boost::lexical_cast<string>(rx_data_.velBody[0])  + separator_ + " "; // velbody-x
    file_ << boost::lexical_cast<string>(rx_data_.velBody[1])  + separator_ + " "; // velbody-y
    file_ << boost::lexical_cast<string>(rx_data_.velBody[2])  + separator_ + " "; // velbody-z

    file_ << boost::lexical_cast<string>(rx_data_.ap_time)  + separator_ + " "; // ap time

    file_ << boost::lexical_cast<string>((int)rx_data_.actuators_nb)  + separator_ + " "; // commands_nb
    file_ << boost::lexical_cast<string>(rx_data_.cmd_throttle)  + separator_ + " "; // cmd_throttle, servo#0
    file_ << boost::lexical_cast<string>(rx_data_.cmd_roll) + separator_ + " "; // cmd_roll, servo#1
    file_ << boost::lexical_cast<string>(rx_data_.cmd_pitch) + separator_ + " "; // cmd_pitch, servo#2
    file_ << boost::lexical_cast<string>(rx_data_.cmd_yaw)  + separator_ + " "; // cmd_yaw, servo#3
    file_ << boost::lexical_cast<string>(rx_data_.cmd_flaps)  + separator_ + " "; // cmd_flaps, servo#4
    file_ << boost::lexical_cast<string>(rx_data_.cmd_dummy)  + separator_ + " "; // cmd_flaps, servo#5

    file_ << boost::lexical_cast<string>(rx_data_.alpha) + separator_ + " "; // alpha
    file_ << boost::lexical_cast<string>(rx_data_.beta) + separator_ + " "; // beta
    file_ << boost::lexical_cast<string>(rx_data_.airspeed) + separator_ + " "; // airspeed

    file_ << boost::lexical_cast<string>(rx_data_.ap_settings); // ap-settings (last one, no separator)

    file_ << endl_;
    file_.flush();
  }

  /**
   * Schedule sending flight gear data. Called only if fg_bind
   * is active
   */
  void handle_fg_timeout(){
    if (!fdm_.check_for_nan()) {
      timer_fg_.expires_from_now(boost::posix_time::milliseconds(milliseconds_));
      timer_fg_.async_wait(boost::bind(&Sender::handle_fg_send, this));
    }
    else {
      std::cerr << "Error too many NaNs! Stopping sending FG packets." << endl;
    }

  }

  /**
   * Prepare and send flight gear data and then schedule next timeout
   */
  void handle_fg_send()
  {
    //helper variable
    static int counter = 0;

    fg_prepare_data();

    uint8_t* buf;
    buf = (uint8_t*)&gui_;

    boost::array<uint8_t, sizeof(gui_)> send_buf_ = {0};
    for (uint32_t i = 0; i<sizeof(gui_); i++){
      send_buf_[i] = buf[i];
    }

    socket_.async_send_to(
        boost::asio::buffer(send_buf_, send_buf_.size()), endpoint_,
        boost::bind(&Sender::handle_send, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

    // send lidar data every 10*30 = 300 ms
    if ( (counter % 10 ) == 0){
      //cout << "Counter = " << counter << ", sending Lidar" << endl;
      ap_->sendLidarData();
    }


    // send isaac status every 30*30 = 900ms
    if ( (counter % 30 ) == 0){
      //cout << "Counter = " << counter << ", sending Isaac" << endl;
      ap_->sendIsaacStatus();
    }



    // send payload status every 33*30=990ms
    if ( (counter % 33 ) == 0){
      //cout << "Counter = " << counter << ", sending Payload" << endl;
      ap_->sendPayloadStatus();
    }


    //cout << "Counter increment= " << counter << endl;
    counter++;


    handle_fg_timeout();
  }

  /**
   * Callback after sending flightgear packet
   * @param
   * @param
   */
  void handle_send(const boost::system::error_code& e/*error*/,
      std::size_t t /*bytes_transferred*/)
  {
#if DEBUG_SENDER
    std::cerr << "Status: " << e.message() << endl;
    std::cerr << "Send  " << t << " bytes" << endl;
#else
    (void)t;
    (void)e;
#endif
  }

  /**
   * Maintain timer related to simulation
   */
  void handle_sim_timer()
  {
    // function to add/handle delays in function
    timer_.expires_from_now(boost::posix_time::microseconds(sim_dt_us_));
    timer_.async_wait(
        boost::bind(&Sender::handle_sim_step, this,
            boost::asio::placeholders::error));
  }

  /**
   * Maintain timer related to simulation with specific sleep period
   * @param us sleep time in microseconds (to maintain more precise timing)
   */
  void handle_sim_timer(int us)
  {
    if (!fdm_.check_for_nan()) {
      // function to add/handle delays in function
      timer_.expires_from_now(boost::posix_time::microseconds(us));
      timer_.async_wait(
          boost::bind(&Sender::handle_sim_step, this,
              boost::asio::placeholders::error));
    }
    else {
      std::cerr << "Error too many NaNs! Stopping simulation." << endl;
    }

  }

  /**
   * Maintain simulation
   * @param error
   */
  void handle_sim_step(const boost::system::error_code& error)
  {
    (void)error;

    static timeval t1, t2;
    gettimeofday(&t1, NULL);
    static int cnt;

    if (ap_->hasNewData() && fdm_.isInitialized()) {
      //cout << LogTime::getTimeSinceStart(start_time_) << " Sim step!"  << endl;
      // get data
      rx_data_ = ap_->getAutopilotData();

      // check for launch
      if ((rx_data_.ap_settings >> 12)) { // launch is now the last bit
        fdm_.launch = true;
      }

#if DEBUG_SENDER
      // parse_ap settings
      cout << LogTime::getTimeSinceStart(start_time_) << ", ";
      cout << "RC_STATUS=" << ((rx_data_.ap_settings >> 2) & 0x3) << ", ";
      cout << "AP_MODE=" << ((rx_data_.ap_settings >> 4) & 0xF) << ", ";
      cout << "LATERAL_MODE=" << ((rx_data_.ap_settings >> 8) & 0xF) << ", ";
      cout << "LAUNCH=" << (rx_data_.ap_settings >> 12) << ", ";
      cout << endl;
#endif
      write_row();
    }

    // feed simulation
    fdm_.feed_jsbsim(rx_data_.commands, (int)rx_data_.actuators_nb);

    // run step
    if (!fdm_.run_step()){
      cout << "error in model run!" << endl;
    }

    if (cnt == fdm_counter_) {
      cnt = 0;
      // fetch data
      tx_data_ = fdm_.fetch_data();

      // set new data
      vn_->setNewData(tx_data_);
      vn_->send_data();
    }
    else {
      cnt++;
    }


    //cout << "about to ask what is the time" << endl;
    gettimeofday(&t2, NULL);
    //cout << "Time diff: " << LogTime::getTimeDiff(t2, t1) << endl;
    static int us = LogTime::getTimeDiff(t2, t1)*1e6;
    //cout << "Time diff(us):: " << us << endl;
    //static int sleep = sim_dt_us_ - us - 100;// magic constant of 100us to shorten the time between the calls

    // FIXME: this value (sleeps for ~1ms works well for sending data at ~400Hz)
    static int sleep = sim_dt_us_ - us - 1500;// magic constant of 100us to shorten the time between the calls
    //cout << "Normal sim us is:" << sim_dt_us_ << endl;
    //cout << "Will sleep for(us):: " << sleep << endl;
    handle_sim_timer(sleep);
    //handle_sim_timer();
  }

  /**
   * Host To Network Double
   * @param x
   * @return
   */
  static double htond (double x)
  {
    int * p = (int*)&x;
    int tmp = p[0];
    p[0] = htonl(p[1]);
    p[1] = htonl(tmp);

    return x;
  }

  /**
   * Host To Network Float
   * @param x
   * @return
   */
  static float htonf (float x)
  {
    int * p = (int *)&x;
    *p = htonl(*p);
    return x;
  }
};

/*
 * Note: shared pointer is super important because it
 * keeps the structure in memory, so we access sockets etc.
 * See http://stackoverflow.com/questions/12402507/got-bad-file-descriptor-when-use-boostasio-and-boostthread
 * for details
 */
typedef boost::shared_ptr<Sender> Sender_ptr;


#endif /* SENDER_H_ */
