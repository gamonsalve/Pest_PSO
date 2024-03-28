/*
 * xgemv_W2hZyGQZ.c
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
#include "xgemv_W2hZyGQZ.h"
#include <string.h>
#include "div_nde_s32_floor.h"

/* Function for MATLAB Function: '<S10>/Correct' */
void xgemv_W2hZyGQZ(int32_T m, int32_T n, const real_T A[9], int32_T ia0, const
                    real_T x[9], int32_T ix0, real_T y[3])
{
  int32_T b;
  int32_T b_iy;
  if (n != 0) {
    int32_T d;
    memset(&y[0], 0, (uint8_T)n * sizeof(real_T));
    d = (n - 1) * 3 + ia0;
    for (b_iy = ia0; b_iy <= d; b_iy += 3) {
      real_T c;
      int32_T e;
      c = 0.0;
      e = b_iy + m;
      for (b = b_iy; b < e; b++) {
        c += x[((ix0 + b) - b_iy) - 1] * A[b - 1];
      }

      b = div_nde_s32_floor(b_iy - ia0, 3);
      y[b] += c;
    }
  }
}
