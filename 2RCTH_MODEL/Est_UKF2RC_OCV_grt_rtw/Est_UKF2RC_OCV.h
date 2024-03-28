/*
 * Est_UKF2RC_OCV.h
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

#ifndef RTW_HEADER_Est_UKF2RC_OCV_h_
#define RTW_HEADER_Est_UKF2RC_OCV_h_
#ifndef Est_UKF2RC_OCV_COMMON_INCLUDES_
#define Est_UKF2RC_OCV_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* Est_UKF2RC_OCV_COMMON_INCLUDES_ */

#include "Est_UKF2RC_OCV_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "batteryStateFcn.h"
#include "SOCMeasurementFcn.h"
#include "batteryMeasurementFcn.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Gain3;                        /* '<S1>/Gain3' */
  real_T Gain3_a;                      /* '<Root>/Gain3' */
  real_T Add2;                         /* '<S1>/Add2' */
  real_T Verror;                       /* '<Root>/Add' */
  real_T Integrator;                   /* '<S1>/Integrator' */
  real_T SoCEstimated;                 /* '<Root>/Saturation' */
  real_T SoCError;                     /* '<Root>/Sum' */
  real_T EmTable;                      /* '<S3>/Em Table' */
  real_T R0Table;                      /* '<S3>/R0 Table' */
  real_T Add1;                         /* '<S3>/Add1' */
  real_T Verror_k;                     /* '<Root>/Sum1' */
  real_T Add;                          /* '<S1>/Add' */
  real_T Add1_n;                       /* '<S1>/Add1' */
  real_T Gain;                         /* '<S1>/Gain' */
  real_T DataStoreRead[3];             /* '<S13>/Data Store Read' */
} B_Est_UKF2RC_OCV_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T P[9];                         /* '<S8>/DataStoreMemory - P' */
  real_T x[3];                         /* '<S8>/DataStoreMemory - x' */
  real_T sum;                          /* '<Root>/MAE Calculator' */
  real_T i;                            /* '<Root>/MAE Calculator' */
  boolean_T sum_not_empty;             /* '<Root>/MAE Calculator' */
} DW_Est_UKF2RC_OCV_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S1>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<S1>/Integrator2' */
  real_T Integrator_CSTATE;            /* '<S1>/Integrator' */
} X_Est_UKF2RC_OCV_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S1>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<S1>/Integrator2' */
  real_T Integrator_CSTATE;            /* '<S1>/Integrator' */
} XDot_Est_UKF2RC_OCV_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S1>/Integrator1' */
  boolean_T Integrator2_CSTATE;        /* '<S1>/Integrator2' */
  boolean_T Integrator_CSTATE;         /* '<S1>/Integrator' */
} XDis_Est_UKF2RC_OCV_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Current;                      /* '<Root>/Current' */
  real_T Measured;                     /* '<Root>/Voltage' */
  real_T Ah;                           /* '<Root>/Ah' */
} ExtU_Est_UKF2RC_OCV_T;

/* Parameters (default storage) */
struct P_Est_UKF2RC_OCV_T_ {
  struct_rDbdhNWsML2YfEwGewUBJ Battery;/* Variable: Battery
                                        * Referenced by:
                                        *   '<S1>/Constant'
                                        *   '<S1>/Gain'
                                        *   '<S1>/Gain3'
                                        *   '<S7>/Constant1'
                                        */
  real_T C1[7];                        /* Variable: C1
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table2'
                                        *   '<S7>/C1'
                                        */
  real_T C2[7];                        /* Variable: C2
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table4'
                                        *   '<S7>/C2'
                                        */
  real_T OCV[7];                       /* Variable: OCV
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table3'
                                        *   '<S3>/Em Table'
                                        *   '<S4>/SOC(OCV) Table'
                                        *   '<S5>/Em Table'
                                        */
  real_T R1[7];                        /* Variable: R1
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table'
                                        *   '<S7>/R1'
                                        */
  real_T R2[7];                        /* Variable: R2
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table1'
                                        *   '<S7>/R2'
                                        */
  real_T Rt[7];                        /* Variable: Rt
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table5'
                                        *   '<S3>/R0 Table'
                                        *   '<S4>/R0'
                                        *   '<S5>/R0 Table'
                                        */
  real_T SOC_LUT[7];                   /* Variable: SOC_LUT
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table'
                                        *   '<S1>/1-D Lookup Table1'
                                        *   '<S1>/1-D Lookup Table2'
                                        *   '<S1>/1-D Lookup Table3'
                                        *   '<S1>/1-D Lookup Table4'
                                        *   '<S1>/1-D Lookup Table5'
                                        *   '<S3>/Em Table'
                                        *   '<S3>/R0 Table'
                                        *   '<S4>/R0'
                                        *   '<S4>/SOC(OCV) Table'
                                        *   '<S5>/Em Table'
                                        *   '<S5>/R0 Table'
                                        *   '<S7>/C1'
                                        *   '<S7>/C2'
                                        *   '<S7>/R1'
                                        *   '<S7>/R2'
                                        */
  real_T Constant_Value;               /* Expression: 0.1
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  real_T Integrator1_UpperSat;         /* Expression: 100
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  real_T Integrator1_LowerSat;         /* Expression: -100
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * Referenced by: '<S1>/Integrator2'
                                        */
  real_T Gain3_Gain;                   /* Expression: 1
                                        * Referenced by: '<Root>/Gain3'
                                        */
  real_T Integrator_IC;                /* Expression: 1
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Integrator_UpperSat;          /* Expression: 1
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Integrator_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T R2_Value;                     /* Expression: p.R{2}
                                        * Referenced by: '<S8>/R2'
                                        */
  real_T MeasurementFcn2Inputs_Value;  /* Expression: 1
                                        * Referenced by: '<S8>/MeasurementFcn2Inputs'
                                        */
  real_T R1_Value;                     /* Expression: p.R{1}
                                        * Referenced by: '<S8>/R1'
                                        */
  real_T MeasurementFcn1Inputs_Value;  /* Expression: 0
                                        * Referenced by: '<S8>/MeasurementFcn1Inputs'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_UpperSat_c;        /* Expression: 1
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T Saturation_LowerSat_g;        /* Expression: 0
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: -1
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Q_Value[9];                   /* Expression: p.Q
                                        * Referenced by: '<S8>/Q'
                                        */
  real_T StateTransitionFcnInputs_Value;/* Expression: 0
                                         * Referenced by: '<S8>/StateTransitionFcnInputs'
                                         */
  real_T DataStoreMemoryP_InitialValue[9];/* Expression: p.InitialCovariance
                                           * Referenced by: '<S8>/DataStoreMemory - P'
                                           */
  real_T DataStoreMemoryx_InitialValue[3];/* Expression: p.InitialState
                                           * Referenced by: '<S8>/DataStoreMemory - x'
                                           */
  boolean_T yBlockOrdering_Y0;         /* Computed Parameter: yBlockOrdering_Y0
                                        * Referenced by: '<S10>/yBlockOrdering'
                                        */
  boolean_T yBlockOrdering_Y0_a;      /* Computed Parameter: yBlockOrdering_Y0_a
                                       * Referenced by: '<S11>/yBlockOrdering'
                                       */
  boolean_T BlockOrdering_Value;       /* Expression: true()
                                        * Referenced by: '<S8>/BlockOrdering'
                                        */
  boolean_T Enable1_Value;             /* Expression: true()
                                        * Referenced by: '<S8>/Enable1'
                                        */
  boolean_T Enable2_Value;             /* Expression: true()
                                        * Referenced by: '<S8>/Enable2'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Est_UKF2RC_OCV_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_Est_UKF2RC_OCV_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Est_UKF2RC_OCV_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[3];
  real_T odeF[3][3];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_P;

/* Block signals (default storage) */
extern B_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_B;

/* Continuous states (default storage) */
extern X_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_X;

/* Block states (default storage) */
extern DW_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Est_UKF2RC_OCV_T Est_UKF2RC_OCV_U;

/* Model entry point functions */
extern void Est_UKF2RC_OCV_initialize(void);
extern void Est_UKF2RC_OCV_step(void);
extern void Est_UKF2RC_OCV_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Est_UKF2RC_OCV_T *const Est_UKF2RC_OCV_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Est_UKF2RC_OCV'
 * '<S1>'   : 'Est_UKF2RC_OCV/2RC Thevenin Model'
 * '<S2>'   : 'Est_UKF2RC_OCV/MAE Calculator'
 * '<S3>'   : 'Est_UKF2RC_OCV/Subsystem'
 * '<S4>'   : 'Est_UKF2RC_OCV/UKF'
 * '<S5>'   : 'Est_UKF2RC_OCV/UKF/Simulink Function - Measurement Function'
 * '<S6>'   : 'Est_UKF2RC_OCV/UKF/Simulink Function - SOC Measurement'
 * '<S7>'   : 'Est_UKF2RC_OCV/UKF/Simulink Function - State Transition Function'
 * '<S8>'   : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation'
 * '<S9>'   : 'Est_UKF2RC_OCV/UKF/Simulink Function - State Transition Function/f(x,u)'
 * '<S10>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Correct1'
 * '<S11>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Correct2'
 * '<S12>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Predict'
 * '<S13>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Subsystem'
 * '<S14>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Correct1/Correct'
 * '<S15>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Correct2/Correct'
 * '<S16>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Predict/Predict'
 * '<S17>'  : 'Est_UKF2RC_OCV/UKF/Unscented Kalman Filter for SOC Estimation/Subsystem/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_Est_UKF2RC_OCV_h_ */
