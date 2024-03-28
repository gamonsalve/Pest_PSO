/*
 * trisolve_7ekc8URj.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Est_UKF2RC_OCV".
 *
 * Model version              : 4.24
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Mon Sep 11 15:27:06 2023
 * Created for block: Est_UKF2RC_OCV
 */

#include "rtwtypes.h"
#include "trisolve_7ekc8URj.h"

/* Function for MATLAB Function: '<S10>/Correct' */
void trisolve_7ekc8URj(real_T A, real_T B[3])
{
  if (B[0] != 0.0) {
    B[0] /= A;
  }

  if (B[1] != 0.0) {
    B[1] /= A;
  }

  if (B[2] != 0.0) {
    B[2] /= A;
  }
}
