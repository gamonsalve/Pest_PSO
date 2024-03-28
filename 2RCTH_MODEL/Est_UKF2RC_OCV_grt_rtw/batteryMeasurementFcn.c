/*
 * Code generation for system system '<S4>/Simulink Function - Measurement Function'
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
#include "batteryMeasurementFcn_private.h"
#include "batteryMeasurementFcn.h"
#include "Est_UKF2RC_OCV.h"
#include "look1_binlxpw.h"

/* Output and update for Simulink Function: '<S4>/Simulink Function - Measurement Function' */
void batteryMeasurementFcn(const real_T rtu_x[3], real_T *rty_y)
{
  /* local block i/o variables */
  real_T rtb_TmpLatchAtCurrentOutport1;

  /* SignalConversion generated from: '<S5>/Current' */
  rtb_TmpLatchAtCurrentOutport1 = Est_UKF2RC_OCV_B.Gain3_a;

  /* SignalConversion generated from: '<S5>/y' incorporates:
   *  Lookup_n-D: '<S5>/Em Table'
   *  Lookup_n-D: '<S5>/R0 Table'
   *  Product: '<S5>/Product'
   *  SignalConversion generated from: '<S5>/x'
   *  Sum: '<S5>/Add1'
   */
  *rty_y = ((look1_binlxpw(rtu_x[0], Est_UKF2RC_OCV_P.SOC_LUT,
              Est_UKF2RC_OCV_P.OCV, 6U) - look1_binlxpw(rtu_x[0],
              Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.Rt, 6U) *
             rtb_TmpLatchAtCurrentOutport1) - rtu_x[1]) - rtu_x[2];
}
