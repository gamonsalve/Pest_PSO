/*
 * svd_OY2AbR3b.c
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
#include "svd_OY2AbR3b.h"
#include "xnrm2_0XtxOmV3.h"
#include <math.h>
#include "xdotc_6O0r46Vz.h"
#include "xaxpy_Z0aVBByk.h"
#include "xnrm2_v4pHr6JM.h"
#include "xaxpy_2XzzEcAx.h"
#include "xrotg_B2eK2SzN.h"
#include "xaxpy_73DBh0ev.h"
#include "xrot_miKOw6Cs.h"
#include "xswap_U9h3dV3C.h"

/* Function for MATLAB Function: '<S10>/Correct' */
void svd_OY2AbR3b(const real_T A[9], real_T U[9], real_T s[3], real_T V[9])
{
  real_T b_A[9];
  real_T b_s[3];
  real_T e[3];
  real_T work[3];
  real_T nrm;
  real_T rt;
  real_T smm1;
  real_T sqds;
  real_T ztest;
  int32_T kase;
  int32_T m;
  int32_T qjj;
  int32_T qp1;
  int32_T qq;
  b_s[0] = 0.0;
  e[0] = 0.0;
  work[0] = 0.0;
  b_s[1] = 0.0;
  e[1] = 0.0;
  work[1] = 0.0;
  b_s[2] = 0.0;
  e[2] = 0.0;
  work[2] = 0.0;
  for (m = 0; m < 9; m++) {
    b_A[m] = A[m];
    U[m] = 0.0;
    V[m] = 0.0;
  }

  for (m = 0; m < 2; m++) {
    boolean_T apply_transform;
    qp1 = m + 2;
    qq = (3 * m + m) + 1;
    apply_transform = false;
    nrm = xnrm2_0XtxOmV3(3 - m, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        b_s[m] = -nrm;
      } else {
        b_s[m] = nrm;
      }

      if (fabs(b_s[m]) >= 1.0020841800044864E-292) {
        nrm = 1.0 / b_s[m];
        qjj = (qq - m) + 2;
        for (kase = qq; kase <= qjj; kase++) {
          b_A[kase - 1] *= nrm;
        }
      } else {
        qjj = (qq - m) + 2;
        for (kase = qq; kase <= qjj; kase++) {
          b_A[kase - 1] /= b_s[m];
        }
      }

      b_A[qq - 1]++;
      b_s[m] = -b_s[m];
    } else {
      b_s[m] = 0.0;
    }

    for (kase = qp1; kase < 4; kase++) {
      qjj = (kase - 1) * 3 + m;
      if (apply_transform) {
        xaxpy_Z0aVBByk(3 - m, -(xdotc_6O0r46Vz(3 - m, b_A, qq, b_A, qjj + 1) /
          b_A[m + 3 * m]), qq, b_A, qjj + 1);
      }

      e[kase - 1] = b_A[qjj];
    }

    for (qq = m + 1; qq < 4; qq++) {
      kase = (3 * m + qq) - 1;
      U[kase] = b_A[kase];
    }

    if (m + 1 <= 1) {
      nrm = xnrm2_v4pHr6JM(e, 2);
      if (nrm == 0.0) {
        e[0] = 0.0;
      } else {
        if (e[1] < 0.0) {
          e[0] = -nrm;
        } else {
          e[0] = nrm;
        }

        nrm = e[0];
        if (fabs(e[0]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[0];
          for (qq = qp1; qq < 4; qq++) {
            e[qq - 1] *= nrm;
          }
        } else {
          for (qq = qp1; qq < 4; qq++) {
            e[qq - 1] /= nrm;
          }
        }

        e[1]++;
        e[0] = -e[0];
        for (qq = qp1; qq < 4; qq++) {
          work[qq - 1] = 0.0;
        }

        for (qq = qp1; qq < 4; qq++) {
          xaxpy_2XzzEcAx(2, e[qq - 1], b_A, 3 * (qq - 1) + 2, work, 2);
        }

        for (qq = qp1; qq < 4; qq++) {
          xaxpy_73DBh0ev(2, -e[qq - 1] / e[1], work, 2, b_A, 3 * (qq - 1) + 2);
        }
      }

      for (qq = qp1; qq < 4; qq++) {
        V[qq - 1] = e[qq - 1];
      }
    }
  }

  m = 1;
  b_s[2] = b_A[8];
  e[1] = b_A[7];
  e[2] = 0.0;
  U[6] = 0.0;
  U[7] = 0.0;
  U[8] = 1.0;
  for (qp1 = 1; qp1 >= 0; qp1--) {
    qq = 3 * qp1 + qp1;
    if (b_s[qp1] != 0.0) {
      for (kase = qp1 + 2; kase < 4; kase++) {
        qjj = ((kase - 1) * 3 + qp1) + 1;
        xaxpy_Z0aVBByk(3 - qp1, -(xdotc_6O0r46Vz(3 - qp1, U, qq + 1, U, qjj) /
          U[qq]), qq + 1, U, qjj);
      }

      for (qjj = qp1 + 1; qjj < 4; qjj++) {
        kase = (3 * qp1 + qjj) - 1;
        U[kase] = -U[kase];
      }

      U[qq]++;
      if (qp1 - 1 >= 0) {
        U[3 * qp1] = 0.0;
      }
    } else {
      U[3 * qp1] = 0.0;
      U[3 * qp1 + 1] = 0.0;
      U[3 * qp1 + 2] = 0.0;
      U[qq] = 1.0;
    }
  }

  for (qp1 = 2; qp1 >= 0; qp1--) {
    if ((qp1 + 1 <= 1) && (e[0] != 0.0)) {
      xaxpy_Z0aVBByk(2, -(xdotc_6O0r46Vz(2, V, 2, V, 5) / V[1]), 2, V, 5);
      xaxpy_Z0aVBByk(2, -(xdotc_6O0r46Vz(2, V, 2, V, 8) / V[1]), 2, V, 8);
    }

    V[3 * qp1] = 0.0;
    V[3 * qp1 + 1] = 0.0;
    V[3 * qp1 + 2] = 0.0;
    V[qp1 + 3 * qp1] = 1.0;
  }

  for (qp1 = 0; qp1 < 3; qp1++) {
    smm1 = e[qp1];
    if (b_s[qp1] != 0.0) {
      rt = fabs(b_s[qp1]);
      nrm = b_s[qp1] / rt;
      b_s[qp1] = rt;
      if (qp1 + 1 < 3) {
        smm1 /= nrm;
      }

      qq = 3 * qp1 + 1;
      for (qjj = qq; qjj <= qq + 2; qjj++) {
        U[qjj - 1] *= nrm;
      }
    }

    if ((qp1 + 1 < 3) && (smm1 != 0.0)) {
      rt = fabs(smm1);
      nrm = rt / smm1;
      smm1 = rt;
      b_s[qp1 + 1] *= nrm;
      qq = (qp1 + 1) * 3 + 1;
      for (qjj = qq; qjj <= qq + 2; qjj++) {
        V[qjj - 1] *= nrm;
      }
    }

    e[qp1] = smm1;
  }

  qp1 = 0;
  nrm = fmax(fmax(fmax(0.0, fmax(fabs(b_s[0]), fabs(e[0]))), fmax(fabs(b_s[1]),
    fabs(e[1]))), fmax(fabs(b_s[2]), fabs(e[2])));
  while ((m + 2 > 0) && (qp1 < 75)) {
    kase = m + 1;
    int32_T exitg1;
    do {
      exitg1 = 0;
      qq = kase;
      if (kase == 0) {
        exitg1 = 1;
      } else {
        rt = fabs(e[kase - 1]);
        if ((rt <= (fabs(b_s[kase - 1]) + fabs(b_s[kase])) *
             2.2204460492503131E-16) || ((rt <= 1.0020841800044864E-292) ||
             ((qp1 > 20) && (rt <= 2.2204460492503131E-16 * nrm)))) {
          e[kase - 1] = 0.0;
          exitg1 = 1;
        } else {
          kase--;
        }
      }
    } while (exitg1 == 0);

    if (m + 1 == kase) {
      kase = 4;
    } else {
      int32_T k_ii;
      boolean_T exitg2;
      qjj = m + 2;
      k_ii = m + 2;
      exitg2 = false;
      while ((!exitg2) && (k_ii >= kase)) {
        qjj = k_ii;
        if (k_ii == kase) {
          exitg2 = true;
        } else {
          rt = 0.0;
          if (k_ii < m + 2) {
            rt = fabs(e[k_ii - 1]);
          }

          if (k_ii > kase + 1) {
            rt += fabs(e[k_ii - 2]);
          }

          ztest = fabs(b_s[k_ii - 1]);
          if ((ztest <= 2.2204460492503131E-16 * rt) || (ztest <=
               1.0020841800044864E-292)) {
            b_s[k_ii - 1] = 0.0;
            exitg2 = true;
          } else {
            k_ii--;
          }
        }
      }

      if (qjj == kase) {
        kase = 3;
      } else if (m + 2 == qjj) {
        kase = 1;
      } else {
        kase = 2;
        qq = qjj;
      }
    }

    switch (kase) {
     case 1:
      rt = e[m];
      e[m] = 0.0;
      for (qjj = m + 1; qjj >= qq + 1; qjj--) {
        smm1 = e[0];
        xrotg_B2eK2SzN(&b_s[qjj - 1], &rt, &ztest, &sqds);
        if (qjj > qq + 1) {
          rt = -sqds * e[0];
          smm1 = e[0] * ztest;
        }

        xrot_miKOw6Cs(V, 3 * (qjj - 1) + 1, 3 * (m + 1) + 1, ztest, sqds);
        e[0] = smm1;
      }
      break;

     case 2:
      {
        rt = e[qq - 1];
        e[qq - 1] = 0.0;
        for (qjj = qq + 1; qjj <= m + 2; qjj++) {
          real_T emm1;
          xrotg_B2eK2SzN(&b_s[qjj - 1], &rt, &ztest, &sqds);
          emm1 = e[qjj - 1];
          rt = emm1 * -sqds;
          e[qjj - 1] = emm1 * ztest;
          xrot_miKOw6Cs(U, 3 * (qjj - 1) + 1, 3 * (qq - 1) + 1, ztest, sqds);
        }
      }
      break;

     case 3:
      {
        real_T emm1;
        real_T shift;
        sqds = b_s[m + 1];
        ztest = fmax(fmax(fmax(fmax(fabs(sqds), fabs(b_s[m])), fabs(e[m])), fabs
                          (b_s[qq])), fabs(e[qq]));
        rt = sqds / ztest;
        smm1 = b_s[m] / ztest;
        emm1 = e[m] / ztest;
        sqds = b_s[qq] / ztest;
        smm1 = ((smm1 + rt) * (smm1 - rt) + emm1 * emm1) / 2.0;
        emm1 *= rt;
        emm1 *= emm1;
        if ((smm1 != 0.0) || (emm1 != 0.0)) {
          shift = sqrt(smm1 * smm1 + emm1);
          if (smm1 < 0.0) {
            shift = -shift;
          }

          shift = emm1 / (smm1 + shift);
        } else {
          shift = 0.0;
        }

        rt = (sqds + rt) * (sqds - rt) + shift;
        ztest = e[qq] / ztest * sqds;
        for (qjj = qq + 1; qjj <= m + 1; qjj++) {
          xrotg_B2eK2SzN(&rt, &ztest, &sqds, &smm1);
          if (qjj > qq + 1) {
            e[0] = rt;
          }

          emm1 = e[qjj - 1];
          rt = b_s[qjj - 1];
          e[qjj - 1] = emm1 * sqds - rt * smm1;
          ztest = smm1 * b_s[qjj];
          b_s[qjj] *= sqds;
          xrot_miKOw6Cs(V, 3 * (qjj - 1) + 1, 3 * qjj + 1, sqds, smm1);
          b_s[qjj - 1] = rt * sqds + emm1 * smm1;
          xrotg_B2eK2SzN(&b_s[qjj - 1], &ztest, &sqds, &smm1);
          rt = e[qjj - 1] * sqds + smm1 * b_s[qjj];
          b_s[qjj] = e[qjj - 1] * -smm1 + sqds * b_s[qjj];
          ztest = smm1 * e[qjj];
          e[qjj] *= sqds;
          xrot_miKOw6Cs(U, 3 * (qjj - 1) + 1, 3 * qjj + 1, sqds, smm1);
        }

        e[m] = rt;
        qp1++;
      }
      break;

     default:
      if (b_s[qq] < 0.0) {
        b_s[qq] = -b_s[qq];
        qp1 = 3 * qq + 1;
        for (qjj = qp1; qjj <= qp1 + 2; qjj++) {
          V[qjj - 1] = -V[qjj - 1];
        }
      }

      qp1 = qq + 1;
      while ((qq + 1 < 3) && (b_s[qq] < b_s[qp1])) {
        rt = b_s[qq];
        b_s[qq] = b_s[qp1];
        b_s[qp1] = rt;
        xswap_U9h3dV3C(V, 3 * qq + 1, 3 * (qq + 1) + 1);
        xswap_U9h3dV3C(U, 3 * qq + 1, 3 * (qq + 1) + 1);
        qq = qp1;
        qp1++;
      }

      qp1 = 0;
      m--;
      break;
    }
  }

  s[0] = b_s[0];
  s[1] = b_s[1];
  s[2] = b_s[2];
}
