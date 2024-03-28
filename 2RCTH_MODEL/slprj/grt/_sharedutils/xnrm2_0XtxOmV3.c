/*
 * xnrm2_0XtxOmV3.c
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
#include "xnrm2_0XtxOmV3.h"
#include <math.h>

/* Function for MATLAB Function: '<S10>/Correct' */
real_T xnrm2_0XtxOmV3(int32_T n, const real_T x[9], int32_T ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}
