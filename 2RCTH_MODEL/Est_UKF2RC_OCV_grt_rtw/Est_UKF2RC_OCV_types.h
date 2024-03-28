/*
 * Est_UKF2RC_OCV_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Est_UKF2RC_OCV".
 *
 * Model version              : 4.24
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Mon Sep 11 16:14:08 2023
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Est_UKF2RC_OCV_types_h_
#define RTW_HEADER_Est_UKF2RC_OCV_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_rDbdhNWsML2YfEwGewUBJ_
#define DEFINED_TYPEDEF_FOR_struct_rDbdhNWsML2YfEwGewUBJ_

typedef struct {
  real_T Timestamp[19220];
  real_T Time[19220];
  real_T Current[19220];
  real_T Voltage[19220];
  real_T SoC_Est[19220];
  real_T SoC_Mes[19220];
  real_T Temperature[19220];
  real_T Ah[19220];
  real_T Capacity;
} struct_rDbdhNWsML2YfEwGewUBJ;

#endif

/* Parameters (default storage) */
typedef struct P_Est_UKF2RC_OCV_T_ P_Est_UKF2RC_OCV_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_Est_UKF2RC_OCV_T RT_MODEL_Est_UKF2RC_OCV_T;

#endif                                 /* RTW_HEADER_Est_UKF2RC_OCV_types_h_ */
