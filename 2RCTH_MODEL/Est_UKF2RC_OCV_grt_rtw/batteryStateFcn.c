/*
 * Code generation for system system '<S4>/Simulink Function - State Transition Function'
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
#include "batteryStateFcn_private.h"
#include "batteryStateFcn.h"
#include "Est_UKF2RC_OCV.h"
#include "look1_binlxpw.h"

/* Output and update for Simulink Function: '<S4>/Simulink Function - State Transition Function' */
void batteryStateFcn(const real_T rtu_x[3], real_T rty_xNext[3])
{
  /* local block i/o variables */
  real_T rtb_TmpLatchAtCurrentOutport1_c;
  real_T rtb_C1;
  real_T rtb_C2;

  /* SignalConversion generated from: '<S7>/Current' */
  rtb_TmpLatchAtCurrentOutport1_c = Est_UKF2RC_OCV_B.Gain3_a;

  /* Lookup_n-D: '<S7>/C1' incorporates:
   *  SignalConversion generated from: '<S7>/x'
   */
  rtb_C1 = look1_binlxpw(rtu_x[0], Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.C1,
    6U);

  /* Lookup_n-D: '<S7>/C2' incorporates:
   *  SignalConversion generated from: '<S7>/x'
   */
  rtb_C2 = look1_binlxpw(rtu_x[0], Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.C2,
    6U);

  /* MATLAB Function: '<S7>/f(x,u)' incorporates:
   *  Constant: '<S7>/Constant1'
   *  Lookup_n-D: '<S7>/R1'
   *  Lookup_n-D: '<S7>/R2'
   *  SignalConversion generated from: '<S7>/x'
   */
  rty_xNext[0] = -rtb_TmpLatchAtCurrentOutport1_c / (3600.0 *
    Est_UKF2RC_OCV_P.Battery.Capacity);
  rty_xNext[1] = -1.0 / (rtb_C1 * look1_binlxpw(rtu_x[0],
    Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.R1, 6U)) * rtu_x[1] +
    rtb_TmpLatchAtCurrentOutport1_c / rtb_C1;
  rty_xNext[2] = -1.0 / (rtb_C2 * look1_binlxpw(rtu_x[0],
    Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.R2, 6U)) * rtu_x[2] +
    rtb_TmpLatchAtCurrentOutport1_c / rtb_C2;

  /* SignalConversion generated from: '<S7>/xNext' incorporates:
   *  Constant: '<S7>/Constant'
   *  Product: '<S7>/Product'
   *  SignalConversion generated from: '<S7>/x'
   *  Sum: '<S7>/Add'
   */
  rty_xNext[0] = rty_xNext[0] * Est_UKF2RC_OCV_P.Constant_Value + rtu_x[0];
  rty_xNext[1] = rty_xNext[1] * Est_UKF2RC_OCV_P.Constant_Value + rtu_x[1];
  rty_xNext[2] = rty_xNext[2] * Est_UKF2RC_OCV_P.Constant_Value + rtu_x[2];
}
