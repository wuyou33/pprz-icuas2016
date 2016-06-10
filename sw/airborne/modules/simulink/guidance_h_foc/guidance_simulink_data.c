/*
 * File: guidance_simulink_data.c
 *
 * Code generated for Simulink model 'guidance_simulink'.
 *
 * Model version                  : 1.32
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * TLC version                    : 8.4 (Jan 18 2013)
 * C/C++ source code generated on : Tue Feb 23 22:48:37 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->ST10/Super10
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "guidance_simulink.h"
#include "guidance_simulink_private.h"

/* Block parameters (auto storage) */
P_guidance_simulink_T guidance_simulink_P = {
  4096.0F,                             /* Computed Parameter: MAX_POS_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  -4096.0F,                            /* Computed Parameter: MAX_POS_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_POS_ERR'
                                        */
  50.0F,                               /* Computed Parameter: P_Gain
                                        * Referenced by: '<Root>/P'
                                        */
  0.015625F,                           /* Computed Parameter: scale1_Gain
                                        * Referenced by: '<Root>/scale1'
                                        */
  8.388608E+6F,                        /* Computed Parameter: MAX_SPEED_ERR_UpperSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  -8.388608E+6F,                       /* Computed Parameter: MAX_SPEED_ERR_LowerSat
                                        * Referenced by: '<Root>/MAX_SPEED_ERR'
                                        */
  80.0F,                               /* Computed Parameter: D_Gain
                                        * Referenced by: '<Root>/D'
                                        */
  0.25F,                               /* Computed Parameter: scale2_Gain
                                        * Referenced by: '<Root>/scale2'
                                        */
  3.05175781E-5F,                      /* Computed Parameter: scale3_Gain
                                        * Referenced by: '<Root>/scale3'
                                        */

  /*  Computed Parameter: DiscreteZeroPole_A
   * Referenced by: '<S1>/Discrete Zero-Pole'
   */
  { 0.998960435F, 0.000383918377F, 1.0F, 0.000383918377F, 1.0F, 0.000383918377F,
    1.0F, 0.000383918377F, 1.0F, 0.000383918377F, 0.000383918377F, 4.24916E-41F,
    0.000383918377F, 4.24916E-41F, 4.06117091E-19F, -1.51353109E-23F,
    1.51353109E-23F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.18649737E-9F, -4.0209832E-11F, 4.0209832E-11F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.00015472855F, -1.83758621E-5F,
    1.83758621E-5F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.0209060553F, -0.00696025882F, 0.00696025882F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.228474379F, -0.104041547F, 0.104041547F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F, 0.727699637F,
    -0.356687605F, 0.356687605F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 1.25567079F, -0.625236809F, 0.625236809F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F,
    -0.190207243F, 0.196240053F, -0.183369935F, 1.61618912F, -0.807398558F,
    0.807398558F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F,
    -0.118092149F, 1.81460273F, -0.907139063F, 0.907139063F, 0.000383918377F,
    4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F, 4.1831445E-9F,
    -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F, 0.016453119F,
    -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F, -0.190207243F,
    0.196240053F, -0.183369935F, 0.121737421F, -0.118092149F, 0.0639219657F,
    -0.0630492941F, 1.9132179F, -0.956573427F, 0.956573427F, 0.000383918377F,
    4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F, 4.1831445E-9F,
    -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F, 0.016453119F,
    -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F, -0.190207243F,
    0.196240053F, -0.183369935F, 0.121737421F, -0.118092149F, 0.0639219657F,
    -0.0630492941F, 0.0310751889F, -0.0308818612F, 1.95997059F, -0.979977727F,
    0.979977727F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F,
    -0.118092149F, 0.0639219657F, -0.0630492941F, 0.0310751889F, -0.0308818612F,
    0.0145826023F, -0.0145412674F, 1.98166037F, -0.990828633F, 0.990828633F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F,
    -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F, -0.118092149F,
    0.0639219657F, -0.0630492941F, 0.0310751889F, -0.0308818612F, 0.0145826023F,
    -0.0145412674F, 0.00673358841F, -0.00672489312F, 1.99162364F, -0.995811462F,
    0.995811462F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F,
    -0.118092149F, 0.0639219657F, -0.0630492941F, 0.0310751889F, -0.0308818612F,
    0.0145826023F, -0.0145412674F, 0.00673358841F, -0.00672489312F,
    0.00308645959F, -0.00308464398F, 1.99617958F, -0.998089731F, 0.998089731F,
    1.95298835E+38F, 4.558E-41F, 1.95385157E+38F, 4.558E-41F, 1.95303379E+38F,
    4.558E-41F, 1.95155723E+38F, 4.558E-41F, 1.95312465E+38F, 4.558E-41F,
    1.95328366E+38F, 4.558E-41F, 1.95394244E+38F, 4.558E-41F, 1.95130735E+38F,
    4.558E-41F, 1.95355626E+38F, 4.558E-41F, 1.95248859E+38F, 4.558E-41F,
    1.95164809E+38F, 4.558E-41F, 1.95223872E+38F, 4.558E-41F, 1.95196612E+38F,
    4.558E-41F, 1.95371527E+38F, 4.558E-41F, 1.9531928E+38F, 4.558E-41F,
    1.95326095E+38F, 4.558E-41F, 1.95253403E+38F, 4.558E-41F, 1.95230686E+38F,
    4.558E-41F, 1.95237501E+38F, 4.558E-41F, 1.95260218E+38F, 4.558E-41F,
    1.95348811E+38F, 4.558E-41F, 1.95146636E+38F, 4.558E-41F, 1.95085302E+38F,
    4.558E-41F, 1.95323823E+38F, 4.558E-41F, 1.95335181E+38F, 4.558E-41F,
    1.95178439E+38F, 4.558E-41F, 1.9512392E+38F, 4.558E-41F, 1.95126191E+38F,
    4.558E-41F, 1.95108018E+38F, 4.558E-41F, 1.9530565E+38F, 4.558E-41F,
    1.95117105E+38F, 4.558E-41F, 1.95353354E+38F, 4.558E-41F, 1.95330638E+38F,
    4.558E-41F },

  /*  Computed Parameter: DiscreteZeroPole_B
   * Referenced by: '<S1>/Discrete Zero-Pole'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
    1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /*  Computed Parameter: DiscreteZeroPole_C
   * Referenced by: '<S1>/Discrete Zero-Pole'
   */
  { 0.000383765204F, 4.24748E-41F, 4.05955E-19F, -1.51292714E-23F,
    4.18147561E-9F, -4.01937893E-11F, 0.000148725172F, -1.8362729E-5F,
    0.016446555F, -0.00678053871F, 0.121457309F, -0.084474422F, 0.221834823F,
    -0.190131366F, 0.196161762F, -0.18329677F, 0.12168885F, -0.118045039F,
    0.0638964623F, -0.0630241409F, 0.0310627911F, -0.0308695398F, 0.0145767843F,
    -0.0145354653F, 0.00673090201F, -0.00672221F, 0.00308522838F,
    -0.00308341323F, 0.0014094311F, -0.00140905334F, 2.24208E-44F, 0.0F,
    2.38221E-44F, 0.0F },
  0.999601066F,                        /* Computed Parameter: DiscreteZeroPole_D
                                        * Referenced by: '<S1>/Discrete Zero-Pole'
                                        */

  /*  Computed Parameter: DiscreteZeroPole_A_a
   * Referenced by: '<S2>/Discrete Zero-Pole'
   */
  { 0.998960435F, 0.000383918377F, 1.0F, 0.000383918377F, 1.0F, 0.000383918377F,
    1.0F, 0.000383918377F, 1.0F, 0.000383918377F, 0.000383918377F, 4.24916E-41F,
    0.000383918377F, 4.24916E-41F, 4.06117091E-19F, -1.51353109E-23F,
    1.51353109E-23F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.18649737E-9F, -4.0209832E-11F, 4.0209832E-11F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.00015472855F, -1.83758621E-5F,
    1.83758621E-5F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.0209060553F, -0.00696025882F, 0.00696025882F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.228474379F, -0.104041547F, 0.104041547F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F, 0.727699637F,
    -0.356687605F, 0.356687605F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 1.25567079F, -0.625236809F, 0.625236809F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F,
    -0.190207243F, 0.196240053F, -0.183369935F, 1.61618912F, -0.807398558F,
    0.807398558F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F,
    -0.118092149F, 1.81460273F, -0.907139063F, 0.907139063F, 0.000383918377F,
    4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F, 4.1831445E-9F,
    -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F, 0.016453119F,
    -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F, -0.190207243F,
    0.196240053F, -0.183369935F, 0.121737421F, -0.118092149F, 0.0639219657F,
    -0.0630492941F, 1.9132179F, -0.956573427F, 0.956573427F, 0.000383918377F,
    4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F, 4.1831445E-9F,
    -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F, 0.016453119F,
    -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F, -0.190207243F,
    0.196240053F, -0.183369935F, 0.121737421F, -0.118092149F, 0.0639219657F,
    -0.0630492941F, 0.0310751889F, -0.0308818612F, 1.95997059F, -0.979977727F,
    0.979977727F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F,
    -0.118092149F, 0.0639219657F, -0.0630492941F, 0.0310751889F, -0.0308818612F,
    0.0145826023F, -0.0145412674F, 1.98166037F, -0.990828633F, 0.990828633F,
    0.000383918377F, 4.24916E-41F, 4.06117014E-19F, -1.51353109E-23F,
    4.1831445E-9F, -4.0209832E-11F, 0.000148784529F, -1.83700577E-5F,
    0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F, 0.221923366F,
    -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F, -0.118092149F,
    0.0639219657F, -0.0630492941F, 0.0310751889F, -0.0308818612F, 0.0145826023F,
    -0.0145412674F, 0.00673358841F, -0.00672489312F, 1.99162364F, -0.995811462F,
    0.995811462F, 0.000383918377F, 4.24916E-41F, 4.06117014E-19F,
    -1.51353109E-23F, 4.1831445E-9F, -4.0209832E-11F, 0.000148784529F,
    -1.83700577E-5F, 0.016453119F, -0.00678324467F, 0.121505782F, -0.0845081359F,
    0.221923366F, -0.190207243F, 0.196240053F, -0.183369935F, 0.121737421F,
    -0.118092149F, 0.0639219657F, -0.0630492941F, 0.0310751889F, -0.0308818612F,
    0.0145826023F, -0.0145412674F, 0.00673358841F, -0.00672489312F,
    0.00308645959F, -0.00308464398F, 1.99617958F, -0.998089731F, 0.998089731F,
    1.34525E-43F, 0.0F, 7.28675E-44F, 0.0F, 1.01286068E+21F, 4.558E-41F,
    3.53145246E-9F, 4.558E-41F, 3.66414555E+20F, 4.558E-41F, 3.72745E-42F, 0.0F,
    131073.875F, 4.55814E-41F, 6.86636E-44F, 0.0F, 3385.21094F, 4.558E-41F,
    131073.875F, 4.55814E-41F, 3.66417369E+20F, 4.558E-41F, 3.69102E-42F, 0.0F,
    8.96831E-43F, 0.0F, 7.28675E-44F, 0.0F, 7.4498221E+13F, 4.558E-41F,
    1.4013E-45F, 8.9029E+11F, 2.96367747E-21F, 3892.59082F, 1.26117E-44F,
    1.35631564E-19F, 1.20912524E-32F, 0.0F, 1.58347E-43F, 0.0F, 7.31034425E+20F,
    4.558E-41F, 1.7697547E+14F, 4.558E-41F, 0.0F, 0.0F, 0.0F, 0.0F, 2.57839E-43F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 6.86636E-44F, 0.0F, 3.67185796E+20F,
    4.558E-41F, 2.91014636E+14F, 4.558E-41F, 3.66142931E+20F, 4.558E-41F,
    8.58996E-43F, 0.0F, 1.12104E-42F, 0.0F },

  /*  Computed Parameter: DiscreteZeroPole_B_b
   * Referenced by: '<S2>/Discrete Zero-Pole'
   */
  { 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F,
    1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F },

  /*  Computed Parameter: DiscreteZeroPole_C_p
   * Referenced by: '<S2>/Discrete Zero-Pole'
   */
  { 0.000383765204F, 4.24748E-41F, 4.05955E-19F, -1.51292714E-23F,
    4.18147561E-9F, -4.01937893E-11F, 0.000148725172F, -1.8362729E-5F,
    0.016446555F, -0.00678053871F, 0.121457309F, -0.084474422F, 0.221834823F,
    -0.190131366F, 0.196161762F, -0.18329677F, 0.12168885F, -0.118045039F,
    0.0638964623F, -0.0630241409F, 0.0310627911F, -0.0308695398F, 0.0145767843F,
    -0.0145354653F, 0.00673090201F, -0.00672221F, 0.00308522838F,
    -0.00308341323F, 0.0014094311F, -0.00140905334F, 1.07448918E-38F,
    8.90820288E-39F, 9.27554766E-39F, 2.9388E-39F },
  0.999601066F,                        /* Computed Parameter: DiscreteZeroPole_D_b
                                        * Referenced by: '<S2>/Discrete Zero-Pole'
                                        */
  20.0F,                               /* Computed Parameter: I_Gain
                                        * Referenced by: '<Root>/I'
                                        */
  6.1408312E+12F,                      /* Computed Parameter: MAX_INTEGRATOR_UpperSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  -6.1408312E+12F,                     /* Computed Parameter: MAX_INTEGRATOR_LowerSat
                                        * Referenced by: '<Root>/MAX_INTEGRATOR'
                                        */
  1.52587891E-5F,                      /* Computed Parameter: scale6_Gain
                                        * Referenced by: '<Root>/scale6'
                                        */
  70.0F,                               /* Computed Parameter: A_Gain
                                        * Referenced by: '<Root>/A'
                                        */
  0.00390625F,                         /* Computed Parameter: scale5_Gain
                                        * Referenced by: '<Root>/scale5'
                                        */
  0.0F,                                /* Computed Parameter: V_Gain
                                        * Referenced by: '<Root>/V'
                                        */
  7.62939453E-6F,                      /* Computed Parameter: scale4_Gain
                                        * Referenced by: '<Root>/scale4'
                                        */
  1429.77368F,                         /* Computed Parameter: TRAJ_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  -1429.77368F,                        /* Computed Parameter: TRAJ_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TRAJ_MAX_BANK'
                                        */
  3216.99097F,                         /* Computed Parameter: TOTAL_MAX_BANK_UpperSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
  -3216.99097F                         /* Computed Parameter: TOTAL_MAX_BANK_LowerSat
                                        * Referenced by: '<Root>/TOTAL_MAX_BANK'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */