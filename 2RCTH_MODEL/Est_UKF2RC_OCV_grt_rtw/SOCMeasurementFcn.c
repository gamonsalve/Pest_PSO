/*
 * Code generation for system system '<S4>/Simulink Function - SOC Measurement'
 *
 * Model                      : Est_UKF2RC_OCV
 * Model version              : 4.24
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Mon Sep 11 16:14:08 2023
 *
 * Note that the functions contained in this file are part of a Simulink
 * model, and are not self-contained algorithms.
 */

#include "rtwtypes.h"
#include "SOCMeasurementFcn.h"

/* Output and update for Simulink Function: '<S4>/Simulink Function - SOC Measurement' */
void SOCMeasurementFcn(const real_T rtu_x[3], real_T *rty_y)
{
  /* SignalConversion generated from: '<S6>/y' incorporates:
   *  SignalConversion generated from: '<S6>/x'
   */
  *rty_y = rtu_x[0];
}
