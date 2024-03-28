/*
 * xgerc_iRBGkROB.c
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
#include "xgerc_iRBGkROB.h"

/* Function for MATLAB Function: '<S10>/Correct' */
void xgerc_iRBGkROB(int32_T m, int32_T n, real_T alpha1, int32_T ix0, const
                    real_T y[3], real_T A[9], int32_T ia0)
{
  int32_T ijA;
  int32_T j;
  if (!(alpha1 == 0.0)) {
    int32_T b;
    int32_T jA;
    jA = ia0;
    b = (uint8_T)n;
    for (j = 0; j < b; j++) {
      real_T temp;
      temp = y[j];
      if (temp != 0.0) {
        int32_T c;
        temp *= alpha1;
        c = m + jA;
        for (ijA = jA; ijA < c; ijA++) {
          A[ijA - 1] += A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }

      jA += 3;
    }
  }
}