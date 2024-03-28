/*
 * xaxpy_73DBh0ev.c
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
#include "xaxpy_73DBh0ev.h"

/* Function for MATLAB Function: '<S10>/Correct' */
void xaxpy_73DBh0ev(int32_T n, real_T a, const real_T x[3], int32_T ix0, real_T
                    y[9], int32_T iy0)
{
  int32_T k;
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_T tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += x[(ix0 + k) - 1] * a;
    }
  }
}
