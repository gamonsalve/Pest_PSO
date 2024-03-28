/*
 * xgemv_QDh8c9kG.c
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
#include "xgemv_QDh8c9kG.h"
#include <string.h>
#include "div_nde_s32_floor.h"

/* Function for MATLAB Function: '<S12>/Predict' */
void xgemv_QDh8c9kG(int32_T m, int32_T n, const real_T A[18], int32_T ia0, const
                    real_T x[18], int32_T ix0, real_T y[3])
{
  int32_T b_iy;
  int32_T iyend;
  if ((m != 0) && (n != 0)) {
    int32_T b;
    if (n - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)n * sizeof(real_T));
    }

    b = (n - 1) * 6 + ia0;
    for (b_iy = ia0; b_iy <= b; b_iy += 6) {
      real_T c;
      int32_T d;
      c = 0.0;
      d = b_iy + m;
      for (iyend = b_iy; iyend < d; iyend++) {
        c += x[((ix0 + iyend) - b_iy) - 1] * A[iyend - 1];
      }

      iyend = div_nde_s32_floor(b_iy - ia0, 6);
      y[iyend] += c;
    }
  }
}
