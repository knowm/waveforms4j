#include <jni.h>
#include "org_knowm_waveforms4j_DWF.h"
#include "dwf.h"

HDWF hdwf;


/************************************************************
*                                                           *
*                      Device                               *
*                                                           *
*************************************************************/


JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDeviceOpen
  (JNIEnv * env, jobject obj){
  

    //printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        char szError[512] = {0};
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed: \n\t%s", szError);
        return 0;
    }
    return 1;
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDeviceCloseAll
  (JNIEnv * env, jobject obj){
  
    return FDwfDeviceCloseAll();
  }

JNIEXPORT jstring JNICALL Java_org_knowm_waveforms4j_DWF_FDwfGetLastErrorMsg
  (JNIEnv * env, jobject obj){

    char szError[512] = {0};
    FDwfGetLastErrorMsg(szError);
    printf("Error Message: \n\t%s", szError);
    return (*env).NewStringUTF(szError);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDeviceAutoConfigureSet
  (JNIEnv * env, jobject obj, jboolean autoConfigure){

    return FDwfDeviceAutoConfigureSet(hdwf, autoConfigure);
  }

/************************************************************
*                                                           *
*                      Digital I/O                          *
*                                                           *
*************************************************************/


JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOReset
  (JNIEnv * env, jobject obj){
  
    return FDwfDigitalIOReset(hdwf);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOStatus
  (JNIEnv * env, jobject obj){
  
    return FDwfDigitalIOStatus(hdwf);
  }  
  
JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOInputStatus
  (JNIEnv * env, jobject obj){
  
    unsigned int ioStates;
  
    FDwfDigitalIOInputStatus(hdwf, &ioStates);
    
    return ioStates;
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOOutputEnableSet
  (JNIEnv * env, jobject obj, jint outputEnableMask){
  
    return FDwfDigitalIOOutputEnableSet(hdwf, outputEnableMask);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOOutputSet
  (JNIEnv * env, jobject obj, jint outputSetMask){
  
    return FDwfDigitalIOOutputSet(hdwf, outputSetMask);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalIOConfigure
  (JNIEnv * env, jobject obj){

    return FDwfDigitalIOConfigure(hdwf);
  }

/************************************************************
*                                                           *
*                  Digital Pattern Out                      *
*                                                           *
*************************************************************/


JNIEXPORT jdouble JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutInternalClockInfo
  (JNIEnv * env, jobject obj){
  
    double hzSys;
    
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);
    printf("hzSys\t%lf\n", hzSys);
    
    return hzSys;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutEnableSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean enable){
  
    return FDwfDigitalOutEnableSet(hdwf, idxChannel, enable);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutDividerSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint frequency){
  
    double hzSys;
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);
    return FDwfDigitalOutDividerSet(hdwf, 0, hzSys/frequency/2);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutCounterSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint low, jint high){
  
    return FDwfDigitalOutCounterSet(hdwf, idxChannel, low, high);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutCounterInitSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean high, jint dividerValue){
  
  return FDwfDigitalOutCounterInitSet(hdwf, idxChannel, high, dividerValue);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutConfigure
  (JNIEnv * env, jobject obj, jboolean start){
  
    return FDwfDigitalOutConfigure(hdwf, start);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfDigitalOutReset
  (JNIEnv * env, jobject obj){
  
    return FDwfDigitalOutReset(hdwf);
  }
  
  

/************************************************************
*                                                           *
*                      Analog In                            *
*                                                           *
*************************************************************/

JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutTriggerSourceInfo
  (JNIEnv * env, jobject obj, jint idxChannel){
  
    int pfstrigsrc;  
  
    FDwfAnalogOutTriggerSourceInfo(hdwf, idxChannel, &pfstrigsrc);
  
    return pfstrigsrc;
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInChannelEnableSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean enable){
  
    return FDwfAnalogInChannelEnableSet(hdwf, idxChannel, enable);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInChannelRangeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble voltsRange){
  
    return FDwfAnalogInChannelRangeSet(hdwf, idxChannel, voltsRange);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInFrequencySet
  (JNIEnv * env, jobject obj, jdouble hzFrequency){
  
    return FDwfAnalogInFrequencySet(hdwf, hzFrequency);
  }
  
JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInBufferSizeMax
  (JNIEnv * env, jobject obj){
  
    int cSamples;
    FDwfAnalogInBufferSizeInfo(hdwf, NULL, &cSamples);  
    return cSamples;
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInBufferSizeSet
  (JNIEnv * env, jobject obj, jint size){
  
    return FDwfAnalogInBufferSizeSet(hdwf, size);  
  }  

JNIEXPORT jbyte JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInStatus
  (JNIEnv * env, jobject obj, jboolean readData){

    DwfState dwfState;
    FDwfAnalogInStatus(hdwf, readData, &dwfState);
    return dwfState;
  }
  
JNIEXPORT jint JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInStatusSamplesValid
  (JNIEnv * env, jobject obj){
  
    int pcSamplesValid;  
  
    FDwfAnalogInStatusSamplesValid(hdwf, &pcSamplesValid);
  
    return pcSamplesValid;
  }
  
JNIEXPORT jdoubleArray JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInStatusData
  (JNIEnv * env, jobject obj, jint idxChannel, jint size){
  
    double* rgdSamples = new double[size];
    FDwfAnalogInStatusData(hdwf, idxChannel, rgdSamples, size);
    
    jdoubleArray jvalues = env->NewDoubleArray(size);
    env->SetDoubleArrayRegion(jvalues, 0, size, rgdSamples); 
    return jvalues;
  } 
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInConfigure
  (JNIEnv * env, jobject obj, jboolean reconfigure, jboolean start){
  
    return FDwfAnalogInConfigure(hdwf, reconfigure, start);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInAcquisitionModeSet
  (JNIEnv * env, jobject obj, jint mode){
  
    return FDwfAnalogInAcquisitionModeSet(hdwf, mode);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerAutoTimeoutSet
  (JNIEnv * env, jobject obj, double secTimeout){
  
    return FDwfAnalogInTriggerAutoTimeoutSet(hdwf, secTimeout);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerSourceSet
  (JNIEnv * env, jobject obj, jint trigsrc){
  
    return FDwfAnalogInTriggerSourceSet(hdwf, trigsrc);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerTypeSet
  (JNIEnv * env, jobject obj, jint trigtype){
  
    return FDwfAnalogInTriggerTypeSet(hdwf, trigtype);
  }
    
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerConditionSet
  (JNIEnv * env, jobject obj, jint trigcond){
  
    return FDwfAnalogInTriggerConditionSet(hdwf, trigcond);
  }  

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerChannelSet
  (JNIEnv * env, jobject obj, jint idxChannel){
  
    return FDwfAnalogInTriggerChannelSet(hdwf, idxChannel);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogInTriggerLevelSet
  (JNIEnv * env, jobject obj, jdouble voltsLevel){
  
    return FDwfAnalogInTriggerLevelSet(hdwf, voltsLevel);
  }
  
/************************************************************
*                                                           *
*                      Analog Out                            *
*                                                           *
*************************************************************/  
  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeEnableSet
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean enable){
  
    return FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, AnalogOutNodeCarrier, enable);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeFunctionSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint func){
  
    return FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, AnalogOutNodeCarrier, func);
  }  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeFrequencySet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble hzFrequency){
  
    return FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, AnalogOutNodeCarrier, hzFrequency);
  }  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeAmplitudeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble amplitude){
  
    return FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, AnalogOutNodeCarrier, amplitude);
  }  
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeOffsetSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble offset){
  
    return FDwfAnalogOutNodeOffsetSet(hdwf, idxChannel, AnalogOutNodeCarrier, offset);
  }


JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeSymmetrySet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble dutyCycle){

    return FDwfAnalogOutNodeSymmetrySet(hdwf, idxChannel, AnalogOutNodeCarrier, dutyCycle);
  }

    
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutConfigure
  (JNIEnv * env, jobject obj, jint idxChannel, jboolean start){
  
    return FDwfAnalogOutConfigure(hdwf, idxChannel, start);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutRepeatSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint repeat){
  
    return FDwfAnalogOutRepeatSet(hdwf, idxChannel, repeat);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutRunSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdouble secRun){
  
    return FDwfAnalogOutRunSet(hdwf, idxChannel, secRun);
  }

JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutIdleSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint idle){
  
    return FDwfAnalogOutIdleSet(hdwf, idxChannel, idle);
  }

JNIEXPORT jintArray JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeDataInfo
  (JNIEnv * env, jobject obj, jint idxChannel){

  int pnSamplesMin;
  int pnSamplesMax;

  FDwfAnalogOutNodeDataInfo(hdwf, idxChannel, AnalogOutNodeCarrier, &pnSamplesMin, &pnSamplesMax);

  int cValues[2] = {pnSamplesMin, pnSamplesMax};
  jintArray jvalues = env->NewIntArray(2);
  env->SetIntArrayRegion(jvalues, 0, 2, cValues);
  return jvalues;
  }










JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogOutNodeDataSet
  (JNIEnv * env, jobject obj, jint idxChannel, jdoubleArray rgdData, jint size){

  //double *input = new double[size];
//  env->GetDoubleArrayRegion( rgdData, 0, size, &input[0] );

  double *input = new double[size];
  jsize len = env->GetArrayLength(rgdData);
  jdouble *body = env->GetDoubleArrayElements(rgdData, 0);
  int i = 0;
  for (i=0; i<len; i++) {
     input[i] = body[i];
  }
  return FDwfAnalogOutNodeDataSet(hdwf, idxChannel, AnalogOutNodeCarrier, input, size);

//  double *input = new double[size];
//  env->SetDoubleArrayRegion(input, 0, size, rgdData);

//double rgdSamples[4096];
//for(int i = 0; i < 4096; i++){
// rgdSamples[i] = 2.0*i/4095-1;
// }
//  return FDwfAnalogOutNodeDataSet(hdwf, idxChannel, AnalogOutNodeCarrier, rgdSamples, 4096);
  }










/************************************************************
*                                                           *
*                      Analog I/O                           *
*                                                           *
*************************************************************/  
  
      
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogIOChannelNodeSet
  (JNIEnv * env, jobject obj, jint idxChannel, jint idxNode, jdouble value){
  
    return FDwfAnalogIOChannelNodeSet(hdwf, idxChannel, idxNode, value);
  }
 
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogIOEnableSet
  (JNIEnv * env, jobject obj, jboolean masterEnable){
  
    return FDwfAnalogIOEnableSet(hdwf, masterEnable);
  }
  
JNIEXPORT jboolean JNICALL Java_org_knowm_waveforms4j_DWF_FDwfAnalogIOConfigure
  (JNIEnv * env, jobject obj){

  return FDwfAnalogIOConfigure(hdwf);
  }