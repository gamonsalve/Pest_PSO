/*
 * Est_UKF2RC_OCV.c
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

#include "Est_UKF2RC_OCV.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>
#include "rt_hypotd_snf.h"
#include "rotate_3AIOL9tK.h"
#include "trisolve_7ekc8URj.h"
#include "qr_cqxNMU1I.h"
#include "Est_UKF2RC_OCV_private.h"
#include "svd_OY2AbR3b.h"
#include "rt_nonfinite.h"
#include "xnrm2_0XtxOmV3.h"
#include "xgemv_W2hZyGQZ.h"
#include "xgerc_iRBGkROB.h"
#include "look1_binlxpw.h"
#include "batteryStateFcn_private.h"
#include "batteryMeasurementFcn_private.h"
#include "batteryMeasurementFcn.h"
#include "SOCMeasurementFcn.h"
#include "batteryStateFcn.h"

/* Block signals (default storage) */
B_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_B;

/* Continuous states */
X_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_X;

/* Block states (default storage) */
DW_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_U;

/* Real-time model */
static RT_MODEL_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_M_;
RT_MODEL_Est_UKF2RC_OCV_T *const Est_UKF2RC_OCV_M = &Est_UKF2RC_OCV_M_;

/* Forward declaration for local functions */
static void Est_UKF2RC_OCV_cholUpdateFactor(real_T S[9], const real_T U[3]);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Est_UKF2RC_OCV_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Est_UKF2RC_OCV_step();
  Est_UKF2RC_OCV_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Est_UKF2RC_OCV_step();
  Est_UKF2RC_OCV_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Function for MATLAB Function: '<S10>/Correct' */
static void Est_UKF2RC_OCV_cholUpdateFactor(real_T S[9], const real_T U[3])
{
  real_T A[9];
  real_T S_0[9];
  real_T Ss[9];
  real_T c[3];
  real_T s[3];
  real_T x[3];
  real_T scale;
  real_T temp;
  int32_T coltop;
  int32_T iAcol;
  int32_T ii;
  int32_T j;
  int32_T knt;
  int8_T p;
  boolean_T errorCondition;
  for (j = 0; j < 3; j++) {
    if (1 - j >= 0) {
      memset(&S[(j << 2) + 1], 0, (uint32_T)((1 - j) + 1) * sizeof(real_T));
    }
  }

  p = 0;
  errorCondition = false;
  if ((S[0] == 0.0) || (S[4] == 0.0)) {
    errorCondition = true;
  }

  if (errorCondition || (S[8] == 0.0)) {
    errorCondition = true;
  }

  if (errorCondition) {
    p = 2;
  } else {
    real_T absxk;
    real_T t;
    x[0] = U[0];
    x[1] = U[1];
    x[2] = U[2];
    for (j = 0; j < 3; j++) {
      iAcol = 3 * j;
      temp = x[j];
      for (ii = 0; ii < j; ii++) {
        temp -= S[ii + iAcol] * x[ii];
      }

      x[j] = temp / S[j + iAcol];
    }

    scale = 3.3121686421112381E-170;
    absxk = fabs(x[0]);
    if (absxk > 3.3121686421112381E-170) {
      temp = 1.0;
      scale = absxk;
    } else {
      t = absxk / 3.3121686421112381E-170;
      temp = t * t;
    }

    absxk = fabs(x[1]);
    if (absxk > scale) {
      t = scale / absxk;
      temp = temp * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      temp += t * t;
    }

    absxk = fabs(x[2]);
    if (absxk > scale) {
      t = scale / absxk;
      temp = temp * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      temp += t * t;
    }

    temp = scale * sqrt(temp);
    if (temp >= 1.0) {
      p = 1;
    } else {
      rotate_3AIOL9tK(sqrt(1.0 - temp * temp), x[2], &c[2], &s[2], &temp);
      x[2] = 0.0;
      rotate_3AIOL9tK(temp, x[1], &c[1], &s[1], &temp);
      x[1] = 0.0;
      rotate_3AIOL9tK(temp, x[0], &c[0], &s[0], &temp);
      x[0] = 0.0;
      for (j = 0; j < 3; j++) {
        for (ii = j + 1; ii >= 1; ii--) {
          scale = x[j];
          iAcol = (3 * j + ii) - 1;
          temp = S[iAcol];
          absxk = s[ii - 1];
          t = c[ii - 1];
          S[iAcol] = temp * t - absxk * scale;
          x[j] = t * scale + temp * absxk;
        }
      }
    }
  }

  if (p != 0) {
    int32_T exitg1;
    boolean_T exitg2;
    for (j = 0; j < 3; j++) {
      for (ii = 0; ii < 3; ii++) {
        iAcol = 3 * ii + j;
        S_0[iAcol] = 0.0;
        S_0[iAcol] += S[3 * j] * S[3 * ii];
        S_0[iAcol] += S[3 * j + 1] * S[3 * ii + 1];
        S_0[iAcol] += S[3 * j + 2] * S[3 * ii + 2];
        Ss[ii + 3 * j] = U[ii] * U[j];
      }
    }

    for (j = 0; j < 9; j++) {
      A[j] = S_0[j] - Ss[j];
    }

    errorCondition = true;
    for (j = 0; j < 9; j++) {
      scale = A[j];
      if (errorCondition && ((!rtIsInf(scale)) && (!rtIsNaN(scale)))) {
      } else {
        errorCondition = false;
      }
    }

    if (errorCondition) {
      svd_OY2AbR3b(A, Ss, s, S_0);
    } else {
      s[0] = (rtNaN);
      s[1] = (rtNaN);
      s[2] = (rtNaN);
      for (j = 0; j < 9; j++) {
        S_0[j] = (rtNaN);
      }
    }

    memset(&Ss[0], 0, 9U * sizeof(real_T));
    Ss[0] = s[0];
    Ss[4] = s[1];
    Ss[8] = s[2];
    for (j = 0; j < 9; j++) {
      Ss[j] = sqrt(Ss[j]);
    }

    for (j = 0; j < 3; j++) {
      for (ii = 0; ii < 3; ii++) {
        iAcol = 3 * ii + j;
        S[iAcol] = 0.0;
        S[iAcol] += Ss[3 * j] * S_0[ii];
        S[iAcol] += Ss[3 * j + 1] * S_0[ii + 3];
        S[iAcol] += Ss[3 * j + 2] * S_0[ii + 6];
      }
    }

    errorCondition = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 3)) {
      ii = j + 1;
      do {
        exitg1 = 0;
        if (ii + 1 < 4) {
          if (!(S[3 * j + ii] == 0.0)) {
            errorCondition = false;
            exitg1 = 1;
          } else {
            ii++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (!errorCondition) {
      memcpy(&A[0], &S[0], 9U * sizeof(real_T));
      x[0] = 0.0;
      c[0] = 0.0;
      x[1] = 0.0;
      c[1] = 0.0;
      x[2] = 0.0;
      c[2] = 0.0;
      for (j = 0; j < 3; j++) {
        ii = j * 3 + j;
        if (j + 1 < 3) {
          int32_T g_tmp;
          scale = A[ii];
          iAcol = ii + 2;
          x[j] = 0.0;
          temp = xnrm2_0XtxOmV3(2 - j, A, ii + 2);
          if (temp != 0.0) {
            temp = rt_hypotd_snf(A[ii], temp);
            if (A[ii] >= 0.0) {
              temp = -temp;
            }

            if (fabs(temp) < 1.0020841800044864E-292) {
              knt = 0;
              do {
                knt++;
                g_tmp = (ii - j) + 3;
                for (coltop = iAcol; coltop <= g_tmp; coltop++) {
                  A[coltop - 1] *= 9.9792015476736E+291;
                }

                temp *= 9.9792015476736E+291;
                scale *= 9.9792015476736E+291;
              } while ((fabs(temp) < 1.0020841800044864E-292) && (knt < 20));

              temp = rt_hypotd_snf(scale, xnrm2_0XtxOmV3(2 - j, A, ii + 2));
              if (scale >= 0.0) {
                temp = -temp;
              }

              x[j] = (temp - scale) / temp;
              scale = 1.0 / (scale - temp);
              for (coltop = iAcol; coltop <= g_tmp; coltop++) {
                A[coltop - 1] *= scale;
              }

              for (iAcol = 0; iAcol < knt; iAcol++) {
                temp *= 1.0020841800044864E-292;
              }

              scale = temp;
            } else {
              x[j] = (temp - A[ii]) / temp;
              scale = 1.0 / (A[ii] - temp);
              coltop = (ii - j) + 3;
              for (knt = iAcol; knt <= coltop; knt++) {
                A[knt - 1] *= scale;
              }

              scale = temp;
            }
          }

          A[ii] = scale;
          temp = A[ii];
          A[ii] = 1.0;
          if (x[j] != 0.0) {
            iAcol = 3 - j;
            knt = (ii - j) + 2;
            while ((iAcol > 0) && (A[knt] == 0.0)) {
              iAcol--;
              knt--;
            }

            knt = 2 - j;
            exitg2 = false;
            while ((!exitg2) && (knt > 0)) {
              coltop = ((knt - 1) * 3 + ii) + 3;
              g_tmp = coltop;
              do {
                exitg1 = 0;
                if (g_tmp + 1 <= coltop + iAcol) {
                  if (A[g_tmp] != 0.0) {
                    exitg1 = 1;
                  } else {
                    g_tmp++;
                  }
                } else {
                  knt--;
                  exitg1 = 2;
                }
              } while (exitg1 == 0);

              if (exitg1 == 1) {
                exitg2 = true;
              }
            }
          } else {
            iAcol = 0;
            knt = 0;
          }

          if (iAcol > 0) {
            xgemv_W2hZyGQZ(iAcol, knt, A, ii + 4, A, ii + 1, c);
            xgerc_iRBGkROB(iAcol, knt, -x[j], ii + 1, c, A, ii + 4);
          }

          A[ii] = temp;
        } else {
          x[2] = 0.0;
        }
      }

      for (j = 0; j < 3; j++) {
        for (ii = 0; ii <= j; ii++) {
          S[ii + 3 * j] = A[3 * j + ii];
        }

        for (ii = j + 2; ii < 4; ii++) {
          S[(ii + 3 * j) - 1] = 0.0;
        }
      }
    }
  }

  for (j = 0; j < 3; j++) {
    S_0[3 * j] = S[j];
    S_0[3 * j + 1] = S[j + 3];
    S_0[3 * j + 2] = S[j + 6];
  }

  memcpy(&S[0], &S_0[0], 9U * sizeof(real_T));
}

/* Model step function */
void Est_UKF2RC_OCV_step(void)
{
  real_T X2[18];
  real_T Y2_0[18];
  real_T tmp[18];
  real_T P[9];
  real_T sqrtP[9];
  real_T sqrtP_0[9];
  real_T A[6];
  real_T Y2[6];
  real_T K[3];
  real_T X2_0[3];
  real_T rtb_xNew[3];
  real_T rtb_xNew_g[3];
  real_T unusedExpr_0[3];
  real_T atmp;
  real_T rtb_Add_m;
  real_T rtb_Integrator1;
  real_T rtb_Integrator2;
  real_T rtb_SOCOCVTable;
  real_T rtb_Saturation;
  real_T t;
  real_T tempY;
  real_T tempY_0;
  real_T unusedExpr;
  real_T xnorm;
  int32_T b_knt;
  int32_T kkC;
  int32_T knt;
  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
    /* set solver stop time */
    if (!(Est_UKF2RC_OCV_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Est_UKF2RC_OCV_M->solverInfo,
                            ((Est_UKF2RC_OCV_M->Timing.clockTickH0 + 1) *
        Est_UKF2RC_OCV_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Est_UKF2RC_OCV_M->solverInfo,
                            ((Est_UKF2RC_OCV_M->Timing.clockTick0 + 1) *
        Est_UKF2RC_OCV_M->Timing.stepSize0 +
        Est_UKF2RC_OCV_M->Timing.clockTickH0 *
        Est_UKF2RC_OCV_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Est_UKF2RC_OCV_M)) {
    Est_UKF2RC_OCV_M->Timing.t[0] = rtsiGetT(&Est_UKF2RC_OCV_M->solverInfo);
  }

  /* Gain: '<S1>/Gain3' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/Ah'
   *  Sum: '<S1>/Add3'
   */
  Est_UKF2RC_OCV_B.Gain3 = 1.0 / Est_UKF2RC_OCV_P.Battery.Capacity *
    (Est_UKF2RC_OCV_P.Battery.Capacity - Est_UKF2RC_OCV_U.Ah);

  /* Integrator: '<S1>/Integrator1' */
  /* Limited  Integrator  */
  if (Est_UKF2RC_OCV_X.Integrator1_CSTATE >=
      Est_UKF2RC_OCV_P.Integrator1_UpperSat) {
    Est_UKF2RC_OCV_X.Integrator1_CSTATE = Est_UKF2RC_OCV_P.Integrator1_UpperSat;
  } else if (Est_UKF2RC_OCV_X.Integrator1_CSTATE <=
             Est_UKF2RC_OCV_P.Integrator1_LowerSat) {
    Est_UKF2RC_OCV_X.Integrator1_CSTATE = Est_UKF2RC_OCV_P.Integrator1_LowerSat;
  }

  rtb_Integrator1 = Est_UKF2RC_OCV_X.Integrator1_CSTATE;

  /* Integrator: '<S1>/Integrator2' */
  rtb_Integrator2 = Est_UKF2RC_OCV_X.Integrator2_CSTATE;

  /* Gain: '<Root>/Gain3' incorporates:
   *  Inport: '<Root>/Current'
   */
  Est_UKF2RC_OCV_B.Gain3_a = Est_UKF2RC_OCV_P.Gain3_Gain *
    Est_UKF2RC_OCV_U.Current;

  /* Sum: '<S1>/Add2' incorporates:
   *  Gain: '<S1>/Gain3'
   *  Integrator: '<S1>/Integrator1'
   *  Integrator: '<S1>/Integrator2'
   *  Lookup_n-D: '<S1>/1-D Lookup Table3'
   *  Lookup_n-D: '<S1>/1-D Lookup Table5'
   *  Product: '<S1>/Product2'
   */
  Est_UKF2RC_OCV_B.Add2 = ((look1_binlxpw(Est_UKF2RC_OCV_B.Gain3,
    Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.OCV, 6U) -
    Est_UKF2RC_OCV_X.Integrator1_CSTATE) - Est_UKF2RC_OCV_X.Integrator2_CSTATE)
    - Est_UKF2RC_OCV_B.Gain3_a * look1_binlxpw(Est_UKF2RC_OCV_B.Gain3,
    Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.Rt, 6U);

  /* Sum: '<Root>/Add' incorporates:
   *  Inport: '<Root>/Voltage'
   */
  Est_UKF2RC_OCV_B.Verror = Est_UKF2RC_OCV_B.Add2 - Est_UKF2RC_OCV_U.Measured;
  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
  }

  /* Integrator: '<S1>/Integrator' */
  /* Limited  Integrator  */
  if (Est_UKF2RC_OCV_X.Integrator_CSTATE >= Est_UKF2RC_OCV_P.Integrator_UpperSat)
  {
    Est_UKF2RC_OCV_X.Integrator_CSTATE = Est_UKF2RC_OCV_P.Integrator_UpperSat;
  } else if (Est_UKF2RC_OCV_X.Integrator_CSTATE <=
             Est_UKF2RC_OCV_P.Integrator_LowerSat) {
    Est_UKF2RC_OCV_X.Integrator_CSTATE = Est_UKF2RC_OCV_P.Integrator_LowerSat;
  }

  /* Integrator: '<S1>/Integrator' */
  Est_UKF2RC_OCV_B.Integrator = Est_UKF2RC_OCV_X.Integrator_CSTATE;
  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
    real_T absxk;
    real_T b_beta1;
    real_T rtb_DataTypeConversion_y1;
    real_T scale;

    /* Lookup_n-D: '<S4>/R0' incorporates:
     *  Integrator: '<S1>/Integrator'
     */
    rtb_Add_m = look1_binlxpw(Est_UKF2RC_OCV_B.Integrator,
      Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.Rt, 6U);

    /* Sum: '<S4>/Add' incorporates:
     *  Inport: '<Root>/Voltage'
     *  Product: '<S4>/Product'
     */
    rtb_Add_m = rtb_Add_m * Est_UKF2RC_OCV_B.Gain3_a + Est_UKF2RC_OCV_U.Measured;

    /* Lookup_n-D: '<S4>/SOC(OCV) Table' incorporates:
     *  Sum: '<S4>/Add'
     */
    rtb_SOCOCVTable = look1_binlxpw(rtb_Add_m, Est_UKF2RC_OCV_P.OCV,
      Est_UKF2RC_OCV_P.SOC_LUT, 6U);

    /* DataTypeConversion: '<S8>/DataTypeConversion_y1' incorporates:
     *  Inport: '<Root>/Voltage'
     */
    rtb_DataTypeConversion_y1 = Est_UKF2RC_OCV_U.Measured;

    /* Outputs for Enabled SubSystem: '<S8>/Correct1' incorporates:
     *  EnablePort: '<S10>/Enable'
     */
    /* Constant: '<S8>/Enable1' */
    if (Est_UKF2RC_OCV_P.Enable1_Value) {
      /* MATLAB Function: '<S10>/Correct' incorporates:
       *  Constant: '<S8>/R1'
       *  DataStoreRead: '<S10>/Data Store ReadP'
       *  DataStoreRead: '<S10>/Data Store ReadX'
       */
      rtb_xNew_g[0] = Est_UKF2RC_OCV_DW.x[0];
      rtb_xNew_g[1] = Est_UKF2RC_OCV_DW.x[1];
      rtb_xNew_g[2] = Est_UKF2RC_OCV_DW.x[2];
      memcpy(&P[0], &Est_UKF2RC_OCV_DW.P[0], 9U * sizeof(real_T));
      b_beta1 = Est_UKF2RC_OCV_P.R1_Value;

      /* DataStoreRead: '<S10>/Data Store ReadX' */
      for (b_knt = 0; b_knt < 3; b_knt++) {
        X2_0[b_knt] = Est_UKF2RC_OCV_DW.x[b_knt];
      }

      /* MATLAB Function: '<S10>/Correct' */
      batteryMeasurementFcn(X2_0, &unusedExpr);
      for (kkC = 0; kkC < 9; kkC++) {
        t = 1.7320508075688772 * P[kkC];
        X2[kkC] = t;
        X2[kkC + 9] = -t;
      }

      for (kkC = 0; kkC < 6; kkC++) {
        X2[3 * kkC] += rtb_xNew_g[0];
        b_knt = 3 * kkC + 1;
        X2[b_knt] += rtb_xNew_g[1];
        b_knt = 3 * kkC + 2;
        X2[b_knt] += rtb_xNew_g[2];
      }

      for (kkC = 0; kkC < 6; kkC++) {
        for (b_knt = 0; b_knt < 3; b_knt++) {
          X2_0[b_knt] = X2[3 * kkC + b_knt];
        }

        batteryMeasurementFcn(X2_0, &Y2[kkC]);
      }

      for (b_knt = 0; b_knt < 3; b_knt++) {
        K[b_knt] = rtb_xNew_g[b_knt];
      }

      batteryMeasurementFcn(K, &tempY);
      for (kkC = 0; kkC < 6; kkC++) {
        Y2[kkC] = (Y2[kkC] - tempY) + tempY;
      }

      unusedExpr = tempY * 0.0;
      for (kkC = 0; kkC < 6; kkC++) {
        unusedExpr += Y2[kkC] * 0.16666666666666666;
      }

      for (kkC = 0; kkC < 6; kkC++) {
        Y2[kkC] -= unusedExpr;
      }

      for (kkC = 0; kkC < 6; kkC++) {
        A[kkC] = 0.408248290463863 * Y2[kkC];
      }

      atmp = A[0];
      xnorm = 0.0;
      scale = 3.3121686421112381E-170;
      for (knt = 0; knt < 5; knt++) {
        absxk = fabs(A[knt + 1]);
        if (absxk > scale) {
          t = scale / absxk;
          xnorm = xnorm * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          xnorm += t * t;
        }
      }

      xnorm = scale * sqrt(xnorm);
      if (xnorm != 0.0) {
        xnorm = rt_hypotd_snf(A[0], xnorm);
        if (A[0] >= 0.0) {
          xnorm = -xnorm;
        }

        if (fabs(xnorm) < 1.0020841800044864E-292) {
          knt = 0;
          do {
            knt++;
            for (b_knt = 0; b_knt < 5; b_knt++) {
              A[b_knt + 1] *= 9.9792015476736E+291;
            }

            xnorm *= 9.9792015476736E+291;
            atmp *= 9.9792015476736E+291;
          } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

          xnorm = 0.0;
          t = 3.3121686421112381E-170;
          for (b_knt = 0; b_knt < 5; b_knt++) {
            scale = fabs(A[b_knt + 1]);
            if (scale > t) {
              absxk = t / scale;
              xnorm = xnorm * absxk * absxk + 1.0;
              t = scale;
            } else {
              absxk = scale / t;
              xnorm += absxk * absxk;
            }
          }

          xnorm = rt_hypotd_snf(atmp, t * sqrt(xnorm));
          if (atmp >= 0.0) {
            xnorm = -xnorm;
          }

          for (b_knt = 0; b_knt < knt; b_knt++) {
            xnorm *= 1.0020841800044864E-292;
          }

          atmp = xnorm;
        } else {
          atmp = xnorm;
        }
      }

      rotate_3AIOL9tK(atmp, tempY - unusedExpr, &atmp, &xnorm, &t);
      for (kkC = 0; kkC < 6; kkC++) {
        X2[3 * kkC] -= rtb_xNew_g[0];
        b_knt = 3 * kkC + 1;
        X2[b_knt] -= rtb_xNew_g[1];
        b_knt = 3 * kkC + 2;
        X2[b_knt] -= rtb_xNew_g[2];
      }

      for (kkC = 0; kkC < 3; kkC++) {
        K[kkC] = 0.0;
        for (b_knt = 0; b_knt < 6; b_knt++) {
          tempY = X2[3 * b_knt + kkC] * Y2[b_knt] + K[kkC];
          K[kkC] = tempY;
        }
      }

      atmp = b_beta1;
      tempY = t;
      b_beta1 = fabs(b_beta1);
      if (b_beta1 != 0.0) {
        b_beta1 = rt_hypotd_snf(t, b_beta1);
        if (t >= 0.0) {
          b_beta1 = -b_beta1;
        }

        if (fabs(b_beta1) < 1.0020841800044864E-292) {
          b_knt = 0;
          do {
            b_knt++;
            atmp *= 9.9792015476736E+291;
            b_beta1 *= 9.9792015476736E+291;
            tempY *= 9.9792015476736E+291;
          } while ((fabs(b_beta1) < 1.0020841800044864E-292) && (b_knt < 20));

          b_beta1 = rt_hypotd_snf(tempY, fabs(atmp));
          if (tempY >= 0.0) {
            b_beta1 = -b_beta1;
          }

          tempY = 1.0 / (tempY - b_beta1);
          for (knt = 0; knt < b_knt; knt++) {
            b_beta1 *= 1.0020841800044864E-292;
          }

          tempY = b_beta1;
        } else {
          tempY = b_beta1;
        }
      }

      rtb_DataTypeConversion_y1 -= unusedExpr;
      rtb_xNew[0] = K[0] * 0.16666666666666666;
      rtb_xNew[1] = K[1] * 0.16666666666666666;
      rtb_xNew[2] = K[2] * 0.16666666666666666;
      trisolve_7ekc8URj(tempY, rtb_xNew);
      K[0] = rtb_xNew[0];
      K[1] = rtb_xNew[1];
      K[2] = rtb_xNew[2];
      trisolve_7ekc8URj(tempY, K);
      for (kkC = 0; kkC < 3; kkC++) {
        /* DataStoreWrite: '<S10>/Data Store WriteP' incorporates:
         *  MATLAB Function: '<S10>/Correct'
         */
        Est_UKF2RC_OCV_DW.P[3 * kkC] = P[kkC];
        Est_UKF2RC_OCV_DW.P[3 * kkC + 1] = P[kkC + 3];
        Est_UKF2RC_OCV_DW.P[3 * kkC + 2] = P[kkC + 6];

        /* MATLAB Function: '<S10>/Correct' */
        X2_0[kkC] = K[kkC] * tempY;
      }

      /* MATLAB Function: '<S10>/Correct' incorporates:
       *  DataStoreWrite: '<S10>/Data Store WriteP'
       */
      Est_UKF2RC_OCV_cholUpdateFactor(Est_UKF2RC_OCV_DW.P, X2_0);

      /* DataStoreWrite: '<S10>/Data Store WriteX' incorporates:
       *  MATLAB Function: '<S10>/Correct'
       */
      Est_UKF2RC_OCV_DW.x[0] = K[0] * rtb_DataTypeConversion_y1 + rtb_xNew_g[0];
      Est_UKF2RC_OCV_DW.x[1] = K[1] * rtb_DataTypeConversion_y1 + rtb_xNew_g[1];
      Est_UKF2RC_OCV_DW.x[2] = K[2] * rtb_DataTypeConversion_y1 + rtb_xNew_g[2];
    }

    /* End of Constant: '<S8>/Enable1' */
    /* End of Outputs for SubSystem: '<S8>/Correct1' */

    /* Outputs for Enabled SubSystem: '<S8>/Correct2' incorporates:
     *  EnablePort: '<S11>/Enable'
     */
    /* Constant: '<S8>/Enable2' */
    if (Est_UKF2RC_OCV_P.Enable2_Value) {
      /* MATLAB Function: '<S11>/Correct' incorporates:
       *  Constant: '<S8>/R2'
       *  DataStoreRead: '<S11>/Data Store ReadP'
       *  DataStoreRead: '<S11>/Data Store ReadX'
       */
      rtb_xNew_g[0] = Est_UKF2RC_OCV_DW.x[0];
      rtb_xNew_g[1] = Est_UKF2RC_OCV_DW.x[1];
      rtb_xNew_g[2] = Est_UKF2RC_OCV_DW.x[2];
      memcpy(&P[0], &Est_UKF2RC_OCV_DW.P[0], 9U * sizeof(real_T));
      b_beta1 = Est_UKF2RC_OCV_P.R2_Value;

      /* DataStoreRead: '<S11>/Data Store ReadX' */
      for (b_knt = 0; b_knt < 3; b_knt++) {
        X2_0[b_knt] = Est_UKF2RC_OCV_DW.x[b_knt];
      }

      /* MATLAB Function: '<S11>/Correct' */
      SOCMeasurementFcn(X2_0, &rtb_Saturation);
      for (kkC = 0; kkC < 9; kkC++) {
        t = 1.7320508075688772 * P[kkC];
        X2[kkC] = t;
        X2[kkC + 9] = -t;
      }

      for (kkC = 0; kkC < 6; kkC++) {
        X2[3 * kkC] += rtb_xNew_g[0];
        b_knt = 3 * kkC + 1;
        X2[b_knt] += rtb_xNew_g[1];
        b_knt = 3 * kkC + 2;
        X2[b_knt] += rtb_xNew_g[2];
      }

      for (kkC = 0; kkC < 6; kkC++) {
        for (b_knt = 0; b_knt < 3; b_knt++) {
          X2_0[b_knt] = X2[3 * kkC + b_knt];
        }

        SOCMeasurementFcn(X2_0, &Y2[kkC]);
      }

      for (b_knt = 0; b_knt < 3; b_knt++) {
        K[b_knt] = rtb_xNew_g[b_knt];
      }

      SOCMeasurementFcn(K, &tempY_0);
      for (kkC = 0; kkC < 6; kkC++) {
        Y2[kkC] = (Y2[kkC] - tempY_0) + tempY_0;
      }

      unusedExpr = tempY_0 * 0.0;
      for (kkC = 0; kkC < 6; kkC++) {
        unusedExpr += Y2[kkC] * 0.16666666666666666;
      }

      for (kkC = 0; kkC < 6; kkC++) {
        Y2[kkC] -= unusedExpr;
      }

      for (kkC = 0; kkC < 6; kkC++) {
        A[kkC] = 0.408248290463863 * Y2[kkC];
      }

      atmp = A[0];
      xnorm = 0.0;
      scale = 3.3121686421112381E-170;
      for (knt = 0; knt < 5; knt++) {
        absxk = fabs(A[knt + 1]);
        if (absxk > scale) {
          t = scale / absxk;
          xnorm = xnorm * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          xnorm += t * t;
        }
      }

      xnorm = scale * sqrt(xnorm);
      if (xnorm != 0.0) {
        xnorm = rt_hypotd_snf(A[0], xnorm);
        if (A[0] >= 0.0) {
          xnorm = -xnorm;
        }

        if (fabs(xnorm) < 1.0020841800044864E-292) {
          knt = 0;
          do {
            knt++;
            for (b_knt = 0; b_knt < 5; b_knt++) {
              A[b_knt + 1] *= 9.9792015476736E+291;
            }

            xnorm *= 9.9792015476736E+291;
            atmp *= 9.9792015476736E+291;
          } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

          xnorm = 0.0;
          t = 3.3121686421112381E-170;
          for (b_knt = 0; b_knt < 5; b_knt++) {
            scale = fabs(A[b_knt + 1]);
            if (scale > t) {
              absxk = t / scale;
              xnorm = xnorm * absxk * absxk + 1.0;
              t = scale;
            } else {
              absxk = scale / t;
              xnorm += absxk * absxk;
            }
          }

          xnorm = rt_hypotd_snf(atmp, t * sqrt(xnorm));
          if (atmp >= 0.0) {
            xnorm = -xnorm;
          }

          for (b_knt = 0; b_knt < knt; b_knt++) {
            xnorm *= 1.0020841800044864E-292;
          }

          atmp = xnorm;
        } else {
          atmp = xnorm;
        }
      }

      rotate_3AIOL9tK(atmp, tempY_0 - unusedExpr, &atmp, &xnorm, &t);
      for (kkC = 0; kkC < 6; kkC++) {
        X2[3 * kkC] -= rtb_xNew_g[0];
        b_knt = 3 * kkC + 1;
        X2[b_knt] -= rtb_xNew_g[1];
        b_knt = 3 * kkC + 2;
        X2[b_knt] -= rtb_xNew_g[2];
      }

      for (kkC = 0; kkC < 3; kkC++) {
        K[kkC] = 0.0;
        for (b_knt = 0; b_knt < 6; b_knt++) {
          tempY = X2[3 * b_knt + kkC] * Y2[b_knt] + K[kkC];
          K[kkC] = tempY;
        }
      }

      atmp = b_beta1;
      tempY = t;
      b_beta1 = fabs(b_beta1);
      if (b_beta1 != 0.0) {
        b_beta1 = rt_hypotd_snf(t, b_beta1);
        if (t >= 0.0) {
          b_beta1 = -b_beta1;
        }

        if (fabs(b_beta1) < 1.0020841800044864E-292) {
          b_knt = 0;
          do {
            b_knt++;
            atmp *= 9.9792015476736E+291;
            b_beta1 *= 9.9792015476736E+291;
            tempY *= 9.9792015476736E+291;
          } while ((fabs(b_beta1) < 1.0020841800044864E-292) && (b_knt < 20));

          b_beta1 = rt_hypotd_snf(tempY, fabs(atmp));
          if (tempY >= 0.0) {
            b_beta1 = -b_beta1;
          }

          tempY = 1.0 / (tempY - b_beta1);
          for (knt = 0; knt < b_knt; knt++) {
            b_beta1 *= 1.0020841800044864E-292;
          }

          tempY = b_beta1;
        } else {
          tempY = b_beta1;
        }
      }

      rtb_DataTypeConversion_y1 = rtb_SOCOCVTable - unusedExpr;
      rtb_xNew[0] = K[0] * 0.16666666666666666;
      rtb_xNew[1] = K[1] * 0.16666666666666666;
      rtb_xNew[2] = K[2] * 0.16666666666666666;
      trisolve_7ekc8URj(tempY, rtb_xNew);
      K[0] = rtb_xNew[0];
      K[1] = rtb_xNew[1];
      K[2] = rtb_xNew[2];
      trisolve_7ekc8URj(tempY, K);
      for (kkC = 0; kkC < 3; kkC++) {
        /* DataStoreWrite: '<S11>/Data Store WriteP' incorporates:
         *  MATLAB Function: '<S11>/Correct'
         */
        Est_UKF2RC_OCV_DW.P[3 * kkC] = P[kkC];
        Est_UKF2RC_OCV_DW.P[3 * kkC + 1] = P[kkC + 3];
        Est_UKF2RC_OCV_DW.P[3 * kkC + 2] = P[kkC + 6];

        /* MATLAB Function: '<S11>/Correct' */
        X2_0[kkC] = K[kkC] * tempY;
      }

      /* MATLAB Function: '<S11>/Correct' incorporates:
       *  DataStoreWrite: '<S11>/Data Store WriteP'
       */
      Est_UKF2RC_OCV_cholUpdateFactor(Est_UKF2RC_OCV_DW.P, X2_0);

      /* DataStoreWrite: '<S11>/Data Store WriteX' incorporates:
       *  MATLAB Function: '<S11>/Correct'
       */
      Est_UKF2RC_OCV_DW.x[0] = K[0] * rtb_DataTypeConversion_y1 + rtb_xNew_g[0];
      Est_UKF2RC_OCV_DW.x[1] = K[1] * rtb_DataTypeConversion_y1 + rtb_xNew_g[1];
      Est_UKF2RC_OCV_DW.x[2] = K[2] * rtb_DataTypeConversion_y1 + rtb_xNew_g[2];
    }

    /* End of Constant: '<S8>/Enable2' */
    /* End of Outputs for SubSystem: '<S8>/Correct2' */

    /* Outputs for Atomic SubSystem: '<S8>/Subsystem' */
    /* DataStoreRead: '<S13>/Data Store Read' */
    Est_UKF2RC_OCV_B.DataStoreRead[0] = Est_UKF2RC_OCV_DW.x[0];
    Est_UKF2RC_OCV_B.DataStoreRead[1] = Est_UKF2RC_OCV_DW.x[1];
    Est_UKF2RC_OCV_B.DataStoreRead[2] = Est_UKF2RC_OCV_DW.x[2];

    /* End of Outputs for SubSystem: '<S8>/Subsystem' */

    /* Saturate: '<Root>/Saturation' */
    if (Est_UKF2RC_OCV_B.DataStoreRead[0] > Est_UKF2RC_OCV_P.Saturation_UpperSat)
    {
      /* Saturate: '<Root>/Saturation' */
      Est_UKF2RC_OCV_B.SoCEstimated = Est_UKF2RC_OCV_P.Saturation_UpperSat;
    } else if (Est_UKF2RC_OCV_B.DataStoreRead[0] <
               Est_UKF2RC_OCV_P.Saturation_LowerSat) {
      /* Saturate: '<Root>/Saturation' */
      Est_UKF2RC_OCV_B.SoCEstimated = Est_UKF2RC_OCV_P.Saturation_LowerSat;
    } else {
      /* Saturate: '<Root>/Saturation' */
      Est_UKF2RC_OCV_B.SoCEstimated = Est_UKF2RC_OCV_B.DataStoreRead[0];
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* Sum: '<Root>/Sum' */
  Est_UKF2RC_OCV_B.SoCError = Est_UKF2RC_OCV_B.Integrator -
    Est_UKF2RC_OCV_B.SoCEstimated;
  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
    /* Saturate: '<S3>/Saturation' */
    if (Est_UKF2RC_OCV_B.DataStoreRead[0] >
        Est_UKF2RC_OCV_P.Saturation_UpperSat_c) {
      rtb_Saturation = Est_UKF2RC_OCV_P.Saturation_UpperSat_c;
    } else if (Est_UKF2RC_OCV_B.DataStoreRead[0] <
               Est_UKF2RC_OCV_P.Saturation_LowerSat_g) {
      rtb_Saturation = Est_UKF2RC_OCV_P.Saturation_LowerSat_g;
    } else {
      rtb_Saturation = Est_UKF2RC_OCV_B.DataStoreRead[0];
    }

    /* End of Saturate: '<S3>/Saturation' */

    /* Lookup_n-D: '<S3>/Em Table' incorporates:
     *  Saturate: '<S3>/Saturation'
     */
    Est_UKF2RC_OCV_B.EmTable = look1_binlxpw(rtb_Saturation,
      Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.OCV, 6U);

    /* Lookup_n-D: '<S3>/R0 Table' incorporates:
     *  Saturate: '<S3>/Saturation'
     */
    Est_UKF2RC_OCV_B.R0Table = look1_binlxpw(rtb_Saturation,
      Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.Rt, 6U);
  }

  /* Sum: '<S3>/Add1' incorporates:
   *  Product: '<S3>/Product'
   */
  Est_UKF2RC_OCV_B.Add1 = ((Est_UKF2RC_OCV_B.EmTable - Est_UKF2RC_OCV_B.R0Table *
    Est_UKF2RC_OCV_B.Gain3_a) - Est_UKF2RC_OCV_B.DataStoreRead[1]) -
    Est_UKF2RC_OCV_B.DataStoreRead[2];

  /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/Voltage'
   */
  Est_UKF2RC_OCV_B.Verror_k = Est_UKF2RC_OCV_U.Measured - Est_UKF2RC_OCV_B.Add1;
  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
  }

  /* Lookup_n-D: '<S1>/1-D Lookup Table2' incorporates:
   *  Gain: '<S1>/Gain3'
   */
  rtb_Saturation = look1_binlxpw(Est_UKF2RC_OCV_B.Gain3,
    Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.C1, 6U);

  /* Lookup_n-D: '<S1>/1-D Lookup Table4' incorporates:
   *  Gain: '<S1>/Gain3'
   */
  tempY_0 = look1_binlxpw(Est_UKF2RC_OCV_B.Gain3, Est_UKF2RC_OCV_P.SOC_LUT,
    Est_UKF2RC_OCV_P.C2, 6U);

  /* Sum: '<S1>/Add' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain3'
   *  Lookup_n-D: '<S1>/1-D Lookup Table'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Divide1'
   */
  Est_UKF2RC_OCV_B.Add = Est_UKF2RC_OCV_P.Gain1_Gain * rtb_Integrator1 /
    rtb_Saturation / look1_binlxpw(Est_UKF2RC_OCV_B.Gain3,
    Est_UKF2RC_OCV_P.SOC_LUT, Est_UKF2RC_OCV_P.R1, 6U) +
    Est_UKF2RC_OCV_B.Gain3_a / rtb_Saturation;

  /* Sum: '<S1>/Add1' incorporates:
   *  Gain: '<S1>/Gain2'
   *  Gain: '<S1>/Gain3'
   *  Lookup_n-D: '<S1>/1-D Lookup Table1'
   *  Product: '<S1>/Divide2'
   *  Product: '<S1>/Divide3'
   */
  Est_UKF2RC_OCV_B.Add1_n = Est_UKF2RC_OCV_P.Gain2_Gain * rtb_Integrator2 /
    tempY_0 / look1_binlxpw(Est_UKF2RC_OCV_B.Gain3, Est_UKF2RC_OCV_P.SOC_LUT,
    Est_UKF2RC_OCV_P.R2, 6U) + Est_UKF2RC_OCV_B.Gain3_a / tempY_0;

  /* Gain: '<S1>/Gain' */
  Est_UKF2RC_OCV_B.Gain = -1.0 / (Est_UKF2RC_OCV_P.Battery.Capacity * 3600.0) *
    Est_UKF2RC_OCV_B.Gain3_a;
  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
    /* MATLAB Function: '<Root>/MAE Calculator' */
    if (!Est_UKF2RC_OCV_DW.sum_not_empty) {
      Est_UKF2RC_OCV_DW.sum = fabs(Est_UKF2RC_OCV_B.SoCError);
      Est_UKF2RC_OCV_DW.sum_not_empty = true;
      Est_UKF2RC_OCV_DW.i = 1.0;
    } else {
      Est_UKF2RC_OCV_DW.i++;
      Est_UKF2RC_OCV_DW.sum += fabs(Est_UKF2RC_OCV_B.SoCError);
    }

    /* End of MATLAB Function: '<Root>/MAE Calculator' */
    /* Outputs for Atomic SubSystem: '<S8>/Predict' */
    /* MATLAB Function: '<S12>/Predict' incorporates:
     *  DataStoreRead: '<S12>/Data Store ReadP'
     *  DataStoreRead: '<S12>/Data Store ReadX'
     */
    K[0] = Est_UKF2RC_OCV_DW.x[0];
    K[1] = Est_UKF2RC_OCV_DW.x[1];
    K[2] = Est_UKF2RC_OCV_DW.x[2];
    memcpy(&P[0], &Est_UKF2RC_OCV_DW.P[0], 9U * sizeof(real_T));

    /* DataStoreRead: '<S12>/Data Store ReadX' */
    for (b_knt = 0; b_knt < 3; b_knt++) {
      X2_0[b_knt] = Est_UKF2RC_OCV_DW.x[b_knt];
    }

    /* MATLAB Function: '<S12>/Predict' incorporates:
     *  Constant: '<S8>/Q'
     */
    batteryStateFcn(X2_0, unusedExpr_0);
    for (kkC = 0; kkC < 9; kkC++) {
      rtb_Integrator1 = 1.7320508075688772 * P[kkC];
      X2[kkC] = rtb_Integrator1;
      X2[kkC + 9] = -rtb_Integrator1;
      P[kkC] = rtb_Integrator1;
    }

    for (kkC = 0; kkC < 6; kkC++) {
      X2[3 * kkC] += K[0];
      b_knt = 3 * kkC + 1;
      X2[b_knt] += K[1];
      b_knt = 3 * kkC + 2;
      X2[b_knt] += K[2];
    }

    for (kkC = 0; kkC < 6; kkC++) {
      for (b_knt = 0; b_knt < 3; b_knt++) {
        X2_0[b_knt] = X2[3 * kkC + b_knt];
      }

      batteryStateFcn(X2_0, &Y2_0[3 * kkC]);
    }

    batteryStateFcn(K, unusedExpr_0);
    rtb_xNew[0] = unusedExpr_0[0] * 0.0;
    rtb_xNew[1] = unusedExpr_0[1] * 0.0;
    rtb_xNew[2] = unusedExpr_0[2] * 0.0;
    for (kkC = 0; kkC < 6; kkC++) {
      rtb_xNew[0] += Y2_0[3 * kkC] * 0.16666666666666666;
      rtb_xNew[1] += Y2_0[3 * kkC + 1] * 0.16666666666666666;
      rtb_xNew[2] += Y2_0[3 * kkC + 2] * 0.16666666666666666;
    }

    unusedExpr_0[0] -= rtb_xNew[0];
    unusedExpr_0[1] -= rtb_xNew[1];
    unusedExpr_0[2] -= rtb_xNew[2];
    for (kkC = 0; kkC < 6; kkC++) {
      rtb_Integrator1 = Y2_0[3 * kkC] - rtb_xNew[0];
      b_knt = 3 * kkC + 1;
      t = Y2_0[b_knt] - rtb_xNew[1];
      knt = 3 * kkC + 2;
      rtb_Integrator2 = Y2_0[knt] - rtb_xNew[2];
      Y2_0[3 * kkC] = rtb_Integrator1;
      Y2_0[b_knt] = t;
      Y2_0[knt] = rtb_Integrator2;
    }

    for (kkC = 0; kkC < 3; kkC++) {
      for (b_knt = 0; b_knt < 6; b_knt++) {
        tmp[b_knt + 6 * kkC] = Y2_0[3 * b_knt + kkC] * 0.408248290463863;
      }
    }

    qr_cqxNMU1I(tmp, X2, sqrtP);
    for (knt = 0; knt < 3; knt++) {
      if (1 - knt >= 0) {
        memset(&sqrtP[(knt << 2) + 1], 0, (uint32_T)((1 - knt) + 1) * sizeof
               (real_T));
      }

      K[knt] = 0.0;
      rtb_xNew_g[knt] = 0.0;
    }

    rotate_3AIOL9tK(sqrtP[0], unusedExpr_0[0], &K[0], &rtb_xNew_g[0], &sqrtP[0]);
    for (kkC = 0; kkC < 2; kkC++) {
      t = unusedExpr_0[kkC + 1];
      for (knt = 0; knt <= kkC; knt++) {
        rtb_Integrator2 = K[knt];
        rtb_Add_m = rtb_xNew_g[knt];
        rtb_Integrator1 = rtb_Add_m * t;
        b_knt = (kkC + 1) * 3 + knt;
        rtb_SOCOCVTable = sqrtP[b_knt];
        t = rtb_Integrator2 * t - rtb_SOCOCVTable * rtb_Add_m;
        sqrtP[b_knt] = rtb_SOCOCVTable * rtb_Integrator2 + rtb_Integrator1;
      }

      rotate_3AIOL9tK(sqrtP[(kkC + 3 * (kkC + 1)) + 1], t, &K[kkC + 1],
                      &rtb_xNew_g[kkC + 1], &sqrtP[(kkC + 3 * (kkC + 1)) + 1]);
    }

    for (kkC = 0; kkC < 3; kkC++) {
      sqrtP_0[3 * kkC] = sqrtP[kkC];
      sqrtP_0[3 * kkC + 1] = sqrtP[kkC + 3];
      sqrtP_0[3 * kkC + 2] = sqrtP[kkC + 6];
    }

    for (kkC = 0; kkC < 9; kkC++) {
      sqrtP[kkC] = sqrtP_0[kkC];
      P[kkC] = 0.0;
    }

    P[0] = 1.0;
    P[4] = 1.0;
    P[8] = 1.0;
    for (b_knt = 0; b_knt < 3; b_knt++) {
      knt = b_knt * 3;
      for (kkC = 0; kkC < 3; kkC++) {
        int32_T aoffset;
        aoffset = kkC * 3;
        sqrtP_0[knt + kkC] = (sqrtP[aoffset + 1] * P[b_knt + 3] + sqrtP[aoffset]
                              * P[b_knt]) + sqrtP[aoffset + 2] * P[b_knt + 6];
      }
    }

    for (kkC = 0; kkC < 3; kkC++) {
      Y2_0[6 * kkC] = sqrtP_0[3 * kkC];
      Y2_0[6 * kkC + 3] = Est_UKF2RC_OCV_P.Q_Value[kkC];
      Y2_0[6 * kkC + 1] = sqrtP_0[3 * kkC + 1];
      Y2_0[6 * kkC + 4] = Est_UKF2RC_OCV_P.Q_Value[kkC + 3];
      Y2_0[6 * kkC + 2] = sqrtP_0[3 * kkC + 2];
      Y2_0[6 * kkC + 5] = Est_UKF2RC_OCV_P.Q_Value[kkC + 6];
    }

    qr_cqxNMU1I(Y2_0, X2, sqrtP);
    for (kkC = 0; kkC < 3; kkC++) {
      /* DataStoreWrite: '<S12>/Data Store WriteP' incorporates:
       *  MATLAB Function: '<S12>/Predict'
       */
      Est_UKF2RC_OCV_DW.P[3 * kkC] = sqrtP[kkC];
      Est_UKF2RC_OCV_DW.P[3 * kkC + 1] = sqrtP[kkC + 3];
      Est_UKF2RC_OCV_DW.P[3 * kkC + 2] = sqrtP[kkC + 6];

      /* DataStoreWrite: '<S12>/Data Store WriteX' */
      Est_UKF2RC_OCV_DW.x[kkC] = rtb_xNew[kkC];
    }

    /* End of Outputs for SubSystem: '<S8>/Predict' */
  }

  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
  }

  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
  }

  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Est_UKF2RC_OCV_M->rtwLogInfo,
                        (Est_UKF2RC_OCV_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Est_UKF2RC_OCV_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Est_UKF2RC_OCV_M)!=-1) &&
          !((rtmGetTFinal(Est_UKF2RC_OCV_M)-
             (((Est_UKF2RC_OCV_M->Timing.clockTick1+
                Est_UKF2RC_OCV_M->Timing.clockTickH1* 4294967296.0)) * 0.1)) >
            (((Est_UKF2RC_OCV_M->Timing.clockTick1+
               Est_UKF2RC_OCV_M->Timing.clockTickH1* 4294967296.0)) * 0.1) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(Est_UKF2RC_OCV_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Est_UKF2RC_OCV_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Est_UKF2RC_OCV_M->Timing.clockTick0)) {
      ++Est_UKF2RC_OCV_M->Timing.clockTickH0;
    }

    Est_UKF2RC_OCV_M->Timing.t[0] = rtsiGetSolverStopTime
      (&Est_UKF2RC_OCV_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Est_UKF2RC_OCV_M->Timing.clockTick1++;
      if (!Est_UKF2RC_OCV_M->Timing.clockTick1) {
        Est_UKF2RC_OCV_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Est_UKF2RC_OCV_derivatives(void)
{
  XDot_Est_UKF2RC_OCV_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_Est_UKF2RC_OCV_T *) Est_UKF2RC_OCV_M->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  lsat = (Est_UKF2RC_OCV_X.Integrator1_CSTATE <=
          Est_UKF2RC_OCV_P.Integrator1_LowerSat);
  usat = (Est_UKF2RC_OCV_X.Integrator1_CSTATE >=
          Est_UKF2RC_OCV_P.Integrator1_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (Est_UKF2RC_OCV_B.Add > 0.0)) || (usat &&
       (Est_UKF2RC_OCV_B.Add < 0.0))) {
    _rtXdot->Integrator1_CSTATE = Est_UKF2RC_OCV_B.Add;
  } else {
    /* in saturation */
    _rtXdot->Integrator1_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S1>/Integrator1' */

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = Est_UKF2RC_OCV_B.Add1_n;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  lsat = (Est_UKF2RC_OCV_X.Integrator_CSTATE <=
          Est_UKF2RC_OCV_P.Integrator_LowerSat);
  usat = (Est_UKF2RC_OCV_X.Integrator_CSTATE >=
          Est_UKF2RC_OCV_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (Est_UKF2RC_OCV_B.Gain > 0.0)) || (usat &&
       (Est_UKF2RC_OCV_B.Gain < 0.0))) {
    _rtXdot->Integrator_CSTATE = Est_UKF2RC_OCV_B.Gain;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S1>/Integrator' */
}

/* Model initialize function */
void Est_UKF2RC_OCV_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Est_UKF2RC_OCV_M, 0,
                sizeof(RT_MODEL_Est_UKF2RC_OCV_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Est_UKF2RC_OCV_M->solverInfo,
                          &Est_UKF2RC_OCV_M->Timing.simTimeStep);
    rtsiSetTPtr(&Est_UKF2RC_OCV_M->solverInfo, &rtmGetTPtr(Est_UKF2RC_OCV_M));
    rtsiSetStepSizePtr(&Est_UKF2RC_OCV_M->solverInfo,
                       &Est_UKF2RC_OCV_M->Timing.stepSize0);
    rtsiSetdXPtr(&Est_UKF2RC_OCV_M->solverInfo, &Est_UKF2RC_OCV_M->derivs);
    rtsiSetContStatesPtr(&Est_UKF2RC_OCV_M->solverInfo, (real_T **)
                         &Est_UKF2RC_OCV_M->contStates);
    rtsiSetNumContStatesPtr(&Est_UKF2RC_OCV_M->solverInfo,
      &Est_UKF2RC_OCV_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Est_UKF2RC_OCV_M->solverInfo,
      &Est_UKF2RC_OCV_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Est_UKF2RC_OCV_M->solverInfo,
      &Est_UKF2RC_OCV_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Est_UKF2RC_OCV_M->solverInfo,
      &Est_UKF2RC_OCV_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Est_UKF2RC_OCV_M->solverInfo, (&rtmGetErrorStatus
      (Est_UKF2RC_OCV_M)));
    rtsiSetRTModelPtr(&Est_UKF2RC_OCV_M->solverInfo, Est_UKF2RC_OCV_M);
  }

  rtsiSetSimTimeStep(&Est_UKF2RC_OCV_M->solverInfo, MAJOR_TIME_STEP);
  Est_UKF2RC_OCV_M->intgData.y = Est_UKF2RC_OCV_M->odeY;
  Est_UKF2RC_OCV_M->intgData.f[0] = Est_UKF2RC_OCV_M->odeF[0];
  Est_UKF2RC_OCV_M->intgData.f[1] = Est_UKF2RC_OCV_M->odeF[1];
  Est_UKF2RC_OCV_M->intgData.f[2] = Est_UKF2RC_OCV_M->odeF[2];
  Est_UKF2RC_OCV_M->contStates = ((X_Est_UKF2RC_OCV_T *) &Est_UKF2RC_OCV_X);
  rtsiSetSolverData(&Est_UKF2RC_OCV_M->solverInfo, (void *)
                    &Est_UKF2RC_OCV_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&Est_UKF2RC_OCV_M->solverInfo, false);
  rtsiSetSolverName(&Est_UKF2RC_OCV_M->solverInfo,"ode3");
  rtmSetTPtr(Est_UKF2RC_OCV_M, &Est_UKF2RC_OCV_M->Timing.tArray[0]);
  rtmSetTFinal(Est_UKF2RC_OCV_M, 1921.9);
  Est_UKF2RC_OCV_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    Est_UKF2RC_OCV_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Est_UKF2RC_OCV_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Est_UKF2RC_OCV_M->rtwLogInfo, (NULL));
    rtliSetLogT(Est_UKF2RC_OCV_M->rtwLogInfo, "tout");
    rtliSetLogX(Est_UKF2RC_OCV_M->rtwLogInfo, "");
    rtliSetLogXFinal(Est_UKF2RC_OCV_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Est_UKF2RC_OCV_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Est_UKF2RC_OCV_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(Est_UKF2RC_OCV_M->rtwLogInfo, 0);
    rtliSetLogDecimation(Est_UKF2RC_OCV_M->rtwLogInfo, 1);
    rtliSetLogY(Est_UKF2RC_OCV_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Est_UKF2RC_OCV_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Est_UKF2RC_OCV_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Est_UKF2RC_OCV_B), 0,
                sizeof(B_Est_UKF2RC_OCV_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Est_UKF2RC_OCV_X, 0,
                  sizeof(X_Est_UKF2RC_OCV_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Est_UKF2RC_OCV_DW, 0,
                sizeof(DW_Est_UKF2RC_OCV_T));

  /* external inputs */
  (void)memset(&Est_UKF2RC_OCV_U, 0, sizeof(ExtU_Est_UKF2RC_OCV_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Est_UKF2RC_OCV_M->rtwLogInfo, 0.0,
    rtmGetTFinal(Est_UKF2RC_OCV_M), Est_UKF2RC_OCV_M->Timing.stepSize0,
    (&rtmGetErrorStatus(Est_UKF2RC_OCV_M)));

  /* Start for DataStoreMemory: '<S8>/DataStoreMemory - P' */
  memcpy(&Est_UKF2RC_OCV_DW.P[0],
         &Est_UKF2RC_OCV_P.DataStoreMemoryP_InitialValue[0], 9U * sizeof(real_T));

  /* Start for DataStoreMemory: '<S8>/DataStoreMemory - x' */
  Est_UKF2RC_OCV_DW.x[0] = Est_UKF2RC_OCV_P.DataStoreMemoryx_InitialValue[0];
  Est_UKF2RC_OCV_DW.x[1] = Est_UKF2RC_OCV_P.DataStoreMemoryx_InitialValue[1];
  Est_UKF2RC_OCV_DW.x[2] = Est_UKF2RC_OCV_P.DataStoreMemoryx_InitialValue[2];

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  Est_UKF2RC_OCV_X.Integrator1_CSTATE = Est_UKF2RC_OCV_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<S1>/Integrator2' */
  Est_UKF2RC_OCV_X.Integrator2_CSTATE = Est_UKF2RC_OCV_P.Integrator2_IC;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  Est_UKF2RC_OCV_X.Integrator_CSTATE = Est_UKF2RC_OCV_P.Integrator_IC;

  /* SystemInitialize for MATLAB Function: '<Root>/MAE Calculator' */
  Est_UKF2RC_OCV_DW.sum_not_empty = false;
}

/* Model terminate function */
void Est_UKF2RC_OCV_terminate(void)
{
  /* (no terminate code required) */
}
