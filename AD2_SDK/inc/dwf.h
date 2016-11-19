/************************************************************************/
/*                                                                      */
/*    dwf.h  --    Public Interface Declarations for DWF.DLL            */
/*                                                                      */
/************************************************************************/
/*    Author: Laszlo Attila Kovacs                                      */
/*    Copyright 2013 Digilent Inc.                                      */
/************************************************************************/
/*  File Description:                                                   */
/*                                                                      */
/*    This header file contains the public interface declarations for   */
/*    the DWF.DLL.  This interface consists of  hardware device         */
/*    enumeration, connection (open/close), and hardware instrument     */
/*    control.  This spans all 4 main instruments  supported by the     */
/*    WaveForms system:                                                 */
/*      Analog In, Analog Out, Analog I/O, and Digital I/O              */
/*                                                                      */
/*    For details on using this interface, refer to:                    */
/*    The WaveForms SDK User's Manual (available in the WaveForms SDK)  */
/*                                                                      */
/************************************************************************/
/*  Revision History:                                                   */
/*                                                                      */
/*  06/6/2009(KovacsLA) : Created                                       */
/*  08/1/2013(JPederson):  Edited for initial public release (WF 2.5)   */
/*  11/07/2013(KovacsLA) : added FDWFAnalogOutMaster *functions         */
/*   DwfState declarations                                              */
/*  10/14/2013(KovacsLA) : added FDWFAnalogOutNode *functions           */
/*  4/29/2014(KovacsLA) : added FDWFAnalogOutMode, Limitation *functions*/
/*                                                                      */
/************************************************************************/


#pragma once

#ifndef DWFINC 
#define DWFINC TRUE

#ifndef DWFAPI
    #if defined(WIN32)
        #if defined(__cplusplus)
            #define    DWFAPI extern "C" __declspec(dllimport)
        #else
            #define    DWFAPI __declspec(dllimport)
        #endif
    #else        
        #if defined(__cplusplus)
            #define DWFAPI extern "C"
        #else
            #define DWFAPI
        #endif
    #endif
#endif

#ifndef BOOL
typedef int BOOL;
#endif

#ifndef BYTE
typedef	unsigned char	BYTE;
#endif

// hardware device handle
typedef int HDWF;
const HDWF hdwfNone = 0;

// device enumeration filters
typedef int ENUMFILTER;
const ENUMFILTER enumfilterAll      = 0;
const ENUMFILTER enumfilterEExplorer= 1;
const ENUMFILTER enumfilterDiscovery= 2;

// device ID
typedef int DEVID;
const DEVID devidEExplorer  = 1;
const DEVID devidDiscovery  = 2;
const DEVID devidDiscovery2 = 3;

// device version
typedef int DEVVER;
const DEVVER devverEExplorerC   = 2;
const DEVVER devverEExplorerE   = 4;
const DEVVER devverEExplorerF   = 5;
const DEVVER devverDiscoveryA   = 1;
const DEVVER devverDiscoveryB   = 2;
const DEVVER devverDiscoveryC   = 3;

// trigger source
typedef BYTE TRIGSRC;
const TRIGSRC trigsrcNone               = 0;
const TRIGSRC trigsrcPC                 = 1;
const TRIGSRC trigsrcDetectorAnalogIn   = 2;
const TRIGSRC trigsrcDetectorDigitalIn  = 3;
const TRIGSRC trigsrcAnalogIn           = 4;
const TRIGSRC trigsrcDigitalIn          = 5;
const TRIGSRC trigsrcDigitalOut         = 6;
const TRIGSRC trigsrcAnalogOut1         = 7;
const TRIGSRC trigsrcAnalogOut2         = 8;
const TRIGSRC trigsrcAnalogOut3         = 9;
const TRIGSRC trigsrcAnalogOut4         = 10;
const TRIGSRC trigsrcExternal1          = 11;
const TRIGSRC trigsrcExternal2          = 12;
const TRIGSRC trigsrcExternal3          = 13;
const TRIGSRC trigsrcExternal4          = 14;

// instrument states:
typedef BYTE DwfState;
const DwfState DwfStateReady        = 0;
const DwfState DwfStateConfig       = 4;
const DwfState DwfStatePrefill      = 5;
const DwfState DwfStateArmed        = 1;
const DwfState DwfStateWait         = 7;
const DwfState DwfStateTriggered    = 3;
const DwfState DwfStateRunning      = 3;
const DwfState DwfStateDone         = 2;

//
typedef int DwfEnumConfigInfo;
const DwfEnumConfigInfo DECIAnalogInChannelCount = 1;
const DwfEnumConfigInfo DECIAnalogOutChannelCount = 2;
const DwfEnumConfigInfo DECIAnalogIOChannelCount = 3;
const DwfEnumConfigInfo DECIDigitalInChannelCount = 4;
const DwfEnumConfigInfo DECIDigitalOutChannelCount = 5;
const DwfEnumConfigInfo DECIDigitalIOChannelCount = 6;
const DwfEnumConfigInfo DECIAnalogInBufferSize = 7;
const DwfEnumConfigInfo DECIAnalogOutBufferSize = 8;
const DwfEnumConfigInfo DECIDigitalInBufferSize = 9;
const DwfEnumConfigInfo DECIDigitalOutBufferSize = 10;

// acquisition modes:
typedef int ACQMODE;
const ACQMODE acqmodeSingle     = 0;
const ACQMODE acqmodeScanShift  = 1;
const ACQMODE acqmodeScanScreen = 2;
const ACQMODE acqmodeRecord     = 3;

// analog acquisition filter:
typedef int FILTER;
const FILTER filterDecimate = 0;
const FILTER filterAverage  = 1;
const FILTER filterMinMax   = 2;

// analog in trigger mode:
typedef int TRIGTYPE;
const TRIGTYPE trigtypeEdge         = 0;
const TRIGTYPE trigtypePulse        = 1;
const TRIGTYPE trigtypeTransition   = 2;

// analog in trigger condition
typedef int TRIGCOND;
const TRIGCOND trigcondRisingPositive   = 0;
const TRIGCOND trigcondFallingNegative  = 1;

// analog in trigger length condition
typedef int TRIGLEN;
const TRIGLEN triglenLess       = 0;
const TRIGLEN triglenTimeout    = 1;
const TRIGLEN triglenMore       = 2;

// error codes for DWF Public API:
typedef int DWFERC;                           
const   DWFERC dwfercNoErc                  = 0;        //  No error occurred
const   DWFERC dwfercUnknownError           = 1;        //  API waiting on pending API timed out
const   DWFERC dwfercApiLockTimeout         = 2;        //  API waiting on pending API timed out
const   DWFERC dwfercAlreadyOpened          = 3;        //  Device already opened
const   DWFERC dwfercNotSupported           = 4;        //  Device not supported
const   DWFERC dwfercInvalidParameter0      = 0x10;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter1      = 0x11;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter2      = 0x12;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter3      = 0x13;     //  Invalid parameter sent in API call
const   DWFERC dwfercInvalidParameter4      = 0x14;     //  Invalid parameter sent in API call

// analog out signal types
typedef BYTE FUNC;
const FUNC funcDC       = 0;
const FUNC funcSine     = 1;
const FUNC funcSquare   = 2;
const FUNC funcTriangle = 3;
const FUNC funcRampUp   = 4;
const FUNC funcRampDown = 5;
const FUNC funcNoise    = 6;
const FUNC funcCustom   = 30;
const FUNC funcPlay     = 31;

// analog io channel node types
typedef BYTE ANALOGIO;
const ANALOGIO analogioEnable       = 1;
const ANALOGIO analogioVoltage      = 2;
const ANALOGIO analogioCurrent      = 3;
const ANALOGIO analogioPower        = 4;
const ANALOGIO analogioTemperature  = 5;

typedef int AnalogOutNode;
const AnalogOutNode AnalogOutNodeCarrier  = 0;
const AnalogOutNode AnalogOutNodeFM       = 1;
const AnalogOutNode AnalogOutNodeAM       = 2;

typedef int DwfAnalogOutMode;
const DwfAnalogOutMode DwfAnalogOutModeVoltage  = 0;
const DwfAnalogOutMode DwfAnalogOutModeCurrent  = 1;

typedef int DwfAnalogOutIdle;
const DwfAnalogOutIdle DwfAnalogOutIdleDisable  = 0;
const DwfAnalogOutIdle DwfAnalogOutIdleOffset   = 1;
const DwfAnalogOutIdle DwfAnalogOutIdleInitial  = 2;

typedef int DwfDigitalInClockSource;
const DwfDigitalInClockSource DwfDigitalInClockSourceInternal = 0;
const DwfDigitalInClockSource DwfDigitalInClockSourceExternal = 1;

typedef int DwfDigitalInSampleMode;
const DwfDigitalInSampleMode DwfDigitalInSampleModeSimple   = 0;
// alternate samples: noise|sample|noise|sample|...  
// where noise is more than 1 transition between 2 samples
const DwfDigitalInSampleMode DwfDigitalInSampleModeNoise    = 1; 

typedef int DwfDigitalOutOutput;
const DwfDigitalOutOutput DwfDigitalOutOutputPushPull   = 0;
const DwfDigitalOutOutput DwfDigitalOutOutputOpenDrain  = 1;
const DwfDigitalOutOutput DwfDigitalOutOutputOpenSource = 2;
const DwfDigitalOutOutput DwfDigitalOutOutputThreeState = 3; // for custom and random

typedef int DwfDigitalOutType;
const DwfDigitalOutType DwfDigitalOutTypePulse      = 0;
const DwfDigitalOutType DwfDigitalOutTypeCustom     = 1;
const DwfDigitalOutType DwfDigitalOutTypeRandom     = 2;
const DwfDigitalOutType DwfDigitalOutTypeFSM        = 3;

typedef int DwfDigitalOutIdle;
const DwfDigitalOutIdle DwfDigitalOutIdleInit     = 0;
const DwfDigitalOutIdle DwfDigitalOutIdleLow      = 1;
const DwfDigitalOutIdle DwfDigitalOutIdleHigh     = 2;
const DwfDigitalOutIdle DwfDigitalOutIdleZet      = 3;

// Macro used to verify if bit is 1 or 0 in given bit field
#define IsBitSet(fs, bit) ((fs & (1<<bit)) != 0)

// Error and version APIs:
DWFAPI BOOL FDwfGetLastError(DWFERC *pdwferc);
DWFAPI BOOL FDwfGetLastErrorMsg(char szError[512]);
DWFAPI BOOL FDwfGetVersion(char szVersion[32]);  // Returns DLL version, for instance: "2.4.3"


// DEVICE MANAGMENT FUNCTIONS
// Enumeration:
DWFAPI BOOL FDwfEnum(ENUMFILTER enumfilter, int *pcDevice);
DWFAPI BOOL FDwfEnumDeviceType(int idxDevice, DEVID *pDeviceId, DEVVER *pDeviceRevision);
DWFAPI BOOL FDwfEnumDeviceIsOpened(int idxDevice, BOOL *pfIsUsed);
DWFAPI BOOL FDwfEnumUserName(int idxDevice, char szUserName[32]);
DWFAPI BOOL FDwfEnumDeviceName(int idxDevice, char szDeviceName[32]);
DWFAPI BOOL FDwfEnumSN(int idxDevice, char szSN[32]);
DWFAPI BOOL FDwfEnumConfig(int idxDevice, int *pcConfig);
DWFAPI BOOL FDwfEnumConfigInfo(int idxConfig, DwfEnumConfigInfo info, int *pv);

// Open/Close:
DWFAPI BOOL FDwfDeviceOpen(int idxDevice, HDWF *phdwf);
DWFAPI BOOL FDwfDeviceConfigOpen(int idxDev, int idxCfg, HDWF *phdwf);
DWFAPI BOOL FDwfDeviceClose(HDWF hdwf);
DWFAPI BOOL FDwfDeviceCloseAll();
DWFAPI BOOL FDwfDeviceAutoConfigureSet(HDWF hdwf, BOOL fAutoConfigure);
DWFAPI BOOL FDwfDeviceAutoConfigureGet(HDWF hdwf, BOOL *pfAutoConfigure);
DWFAPI BOOL FDwfDeviceReset(HDWF hdwf);
DWFAPI BOOL FDwfDeviceEnableSet(HDWF hdwf, BOOL fEnable);
DWFAPI BOOL FDwfDeviceTriggerInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfDeviceTriggerSet(HDWF hdwf, int idxPin, TRIGSRC trigsrc);
DWFAPI BOOL FDwfDeviceTriggerGet(HDWF hdwf, int idxPin, TRIGSRC *ptrigsrc);
DWFAPI BOOL FDwfDeviceTriggerPC(HDWF hdwf);


// ANALOG IN INSTRUMENT FUNCTIONS
// Control and status: 
DWFAPI BOOL FDwfAnalogInReset(HDWF hdwf);
DWFAPI BOOL FDwfAnalogInConfigure(HDWF hdwf, BOOL fReconfigure, BOOL fStart);
DWFAPI BOOL FDwfAnalogInStatus(HDWF hdwf, BOOL fReadData, DwfState *psts);
DWFAPI BOOL FDwfAnalogInStatusSamplesLeft(HDWF hdwf, int *pcSamplesLeft);
DWFAPI BOOL FDwfAnalogInStatusSamplesValid(HDWF hdwf, int *pcSamplesValid);
DWFAPI BOOL FDwfAnalogInStatusIndexWrite(HDWF hdwf, int *pidxWrite);
DWFAPI BOOL FDwfAnalogInStatusAutoTriggered(HDWF hdwf, BOOL *pfAuto);
DWFAPI BOOL FDwfAnalogInStatusData(HDWF hdwf, int idxChannel, double *rgdVoltData, int cdData);
DWFAPI BOOL FDwfAnalogInStatusData2(HDWF hdwf, int idxChannel, double *rgdVoltData, int idxData, int cdData);
DWFAPI BOOL FDwfAnalogInStatusNoise(HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int cdData);
DWFAPI BOOL FDwfAnalogInStatusNoise2(HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int idxData, int cdData);
DWFAPI BOOL FDwfAnalogInStatusSample(HDWF hdwf, int idxChannel, double *pdVoltSample);

DWFAPI BOOL FDwfAnalogInStatusRecord(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt);
DWFAPI BOOL FDwfAnalogInRecordLengthSet(HDWF hdwf, double sLegth);
DWFAPI BOOL FDwfAnalogInRecordLengthGet(HDWF hdwf, double *psLegth);

// Acquisition configuration:
DWFAPI BOOL FDwfAnalogInFrequencyInfo(HDWF hdwf, double *phzMin, double *phzMax);
DWFAPI BOOL FDwfAnalogInFrequencySet(HDWF hdwf, double hzFrequency);
DWFAPI BOOL FDwfAnalogInFrequencyGet(HDWF hdwf, double *phzFrequency);

DWFAPI BOOL FDwfAnalogInBitsInfo(HDWF hdwf, int *pnBits); // Returns the number of ADC bits 

DWFAPI BOOL FDwfAnalogInBufferSizeInfo(HDWF hdwf, int *pnSizeMin, int *pnSizeMax);
DWFAPI BOOL FDwfAnalogInBufferSizeSet(HDWF hdwf, int nSize);
DWFAPI BOOL FDwfAnalogInBufferSizeGet(HDWF hdwf, int *pnSize);

DWFAPI BOOL FDwfAnalogInNoiseSizeInfo(HDWF hdwf, int *pnSizeMax);
DWFAPI BOOL FDwfAnalogInNoiseSizeSet(HDWF hdwf, int nSize);
DWFAPI BOOL FDwfAnalogInNoiseSizeGet(HDWF hdwf, int *pnSize);

DWFAPI BOOL FDwfAnalogInAcquisitionModeInfo(HDWF hdwf, int *pfsacqmode); // use IsBitSet
DWFAPI BOOL FDwfAnalogInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode);
DWFAPI BOOL FDwfAnalogInAcquisitionModeGet(HDWF hdwf, ACQMODE *pacqmode);

// Channel configuration:
DWFAPI BOOL FDwfAnalogInChannelCount(HDWF hdwf, int *pcChannel);
DWFAPI BOOL FDwfAnalogInChannelEnableSet(HDWF hdwf, int idxChannel, BOOL fEnable);
DWFAPI BOOL FDwfAnalogInChannelEnableGet(HDWF hdwf, int idxChannel, BOOL *pfEnable);
DWFAPI BOOL FDwfAnalogInChannelFilterInfo(HDWF hdwf, int *pfsfilter); // use IsBitSet
DWFAPI BOOL FDwfAnalogInChannelFilterSet(HDWF hdwf, int idxChannel, FILTER filter);
DWFAPI BOOL FDwfAnalogInChannelFilterGet(HDWF hdwf, int idxChannel, FILTER *pfilter);
DWFAPI BOOL FDwfAnalogInChannelRangeInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInChannelRangeSteps(HDWF hdwf, double rgVoltsStep[32], int *pnSteps);
DWFAPI BOOL FDwfAnalogInChannelRangeSet(HDWF hdwf, int idxChannel, double voltsRange);
DWFAPI BOOL FDwfAnalogInChannelRangeGet(HDWF hdwf, int idxChannel, double *pvoltsRange);
DWFAPI BOOL FDwfAnalogInChannelOffsetInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInChannelOffsetSet(HDWF hdwf, int idxChannel, double voltOffset);
DWFAPI BOOL FDwfAnalogInChannelOffsetGet(HDWF hdwf, int idxChannel, double *pvoltOffset);
DWFAPI BOOL FDwfAnalogInChannelAttenuationSet(HDWF hdwf, int idxChannel, double xAttenuation);
DWFAPI BOOL FDwfAnalogInChannelAttenuationGet(HDWF hdwf, int idxChannel, double *pxAttenuation);


// Trigger configuration:
DWFAPI BOOL FDwfAnalogInTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI BOOL FDwfAnalogInTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI BOOL FDwfAnalogInTriggerPositionInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerPositionSet(HDWF hdwf, double secPosition);
DWFAPI BOOL FDwfAnalogInTriggerPositionGet(HDWF hdwf, double *psecPosition);
DWFAPI BOOL FDwfAnalogInTriggerPositionStatus(HDWF hdwf, double *psecPosition);

DWFAPI BOOL FDwfAnalogInTriggerAutoTimeoutInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout);
DWFAPI BOOL FDwfAnalogInTriggerAutoTimeoutGet(HDWF hdwf, double *psecTimeout);

DWFAPI BOOL FDwfAnalogInTriggerHoldOffInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnStep);
DWFAPI BOOL FDwfAnalogInTriggerHoldOffSet(HDWF hdwf, double secHoldOff);
DWFAPI BOOL FDwfAnalogInTriggerHoldOffGet(HDWF hdwf, double *psecHoldOff);

DWFAPI BOOL FDwfAnalogInTriggerTypeInfo(HDWF hdwf, int *pfstrigtype); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerTypeSet(HDWF hdwf, TRIGTYPE trigtype);
DWFAPI BOOL FDwfAnalogInTriggerTypeGet(HDWF hdwf, TRIGTYPE *ptrigtype);

DWFAPI BOOL FDwfAnalogInTriggerChannelInfo(HDWF hdwf, int *pidxMin, int *pidxMax);
DWFAPI BOOL FDwfAnalogInTriggerChannelSet(HDWF hdwf, int idxChannel);
DWFAPI BOOL FDwfAnalogInTriggerChannelGet(HDWF hdwf, int *pidxChannel);

DWFAPI BOOL FDwfAnalogInTriggerFilterInfo(HDWF hdwf, int *pfsfilter); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerFilterSet(HDWF hdwf, FILTER filter);
DWFAPI BOOL FDwfAnalogInTriggerFilterGet(HDWF hdwf, FILTER *pfilter);

DWFAPI BOOL FDwfAnalogInTriggerLevelInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerLevelSet(HDWF hdwf, double voltsLevel);
DWFAPI BOOL FDwfAnalogInTriggerLevelGet(HDWF hdwf, double *pvoltsLevel);

DWFAPI BOOL FDwfAnalogInTriggerHysteresisInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerHysteresisSet(HDWF hdwf, double voltsLevel);
DWFAPI BOOL FDwfAnalogInTriggerHysteresisGet(HDWF hdwf, double *pvoltsHysteresis);

DWFAPI BOOL FDwfAnalogInTriggerConditionInfo(HDWF hdwf, int *pfstrigcond); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerConditionSet(HDWF hdwf, TRIGCOND trigcond);
DWFAPI BOOL FDwfAnalogInTriggerConditionGet(HDWF hdwf, TRIGCOND *ptrigcond);

DWFAPI BOOL FDwfAnalogInTriggerLengthInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI BOOL FDwfAnalogInTriggerLengthSet(HDWF hdwf, double secLength);
DWFAPI BOOL FDwfAnalogInTriggerLengthGet(HDWF hdwf, double *psecLength);

DWFAPI BOOL FDwfAnalogInTriggerLengthConditionInfo(HDWF hdwf, int *pfstriglen); // use IsBitSet
DWFAPI BOOL FDwfAnalogInTriggerLengthConditionSet(HDWF hdwf, TRIGLEN triglen);
DWFAPI BOOL FDwfAnalogInTriggerLengthConditionGet(HDWF hdwf, TRIGLEN *ptriglen);


// ANALOG OUT INSTRUMENT FUNCTIONS
// Configuration:
DWFAPI BOOL FDwfAnalogOutCount(HDWF hdwf, int *pcChannel);

DWFAPI BOOL FDwfAnalogOutMasterSet(HDWF hdwf, int idxChannel, int idxMaster);
DWFAPI BOOL FDwfAnalogOutMasterGet(HDWF hdwf, int idxChannel, int *pidxMaster);

DWFAPI BOOL FDwfAnalogOutTriggerSourceInfo(HDWF hdwf, int idxChannel, int *pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfAnalogOutTriggerSourceSet(HDWF hdwf, int idxChannel, TRIGSRC trigsrc);
DWFAPI BOOL FDwfAnalogOutTriggerSourceGet(HDWF hdwf, int idxChannel, TRIGSRC *ptrigsrc);

DWFAPI BOOL FDwfAnalogOutRunInfo(HDWF hdwf, int idxChannel, double *psecMin, double *psecMax);
DWFAPI BOOL FDwfAnalogOutRunSet(HDWF hdwf, int idxChannel, double secRun);
DWFAPI BOOL FDwfAnalogOutRunGet(HDWF hdwf, int idxChannel, double *psecRun);
DWFAPI BOOL FDwfAnalogOutRunStatus(HDWF hdwf, int idxChannel, double *psecRun);

DWFAPI BOOL FDwfAnalogOutWaitInfo(HDWF hdwf, int idxChannel, double *psecMin, double *psecMax);
DWFAPI BOOL FDwfAnalogOutWaitSet(HDWF hdwf, int idxChannel, double secWait);
DWFAPI BOOL FDwfAnalogOutWaitGet(HDWF hdwf, int idxChannel, double *psecWait);

DWFAPI BOOL FDwfAnalogOutRepeatInfo(HDWF hdwf, int idxChannel, int *pnMin, int *pnMax);
DWFAPI BOOL FDwfAnalogOutRepeatSet(HDWF hdwf, int idxChannel, int cRepeat);
DWFAPI BOOL FDwfAnalogOutRepeatGet(HDWF hdwf, int idxChannel, int *pcRepeat);
DWFAPI BOOL FDwfAnalogOutRepeatStatus(HDWF hdwf, int idxChannel, int *pcRepeat);

DWFAPI BOOL FDwfAnalogOutRepeatTriggerSet(HDWF hdwf, int idxChannel, BOOL fRepeatTrigger);
DWFAPI BOOL FDwfAnalogOutRepeatTriggerGet(HDWF hdwf, int idxChannel, BOOL *pfRepeatTrigger);

// EExplorer channel 3&4 current/voltage limitation
DWFAPI BOOL FDwfAnalogOutLimitationInfo(HDWF hdwf, int idxChannel, double *pMin, double *pMax);
DWFAPI BOOL FDwfAnalogOutLimitationSet(HDWF hdwf, int idxChannel, double limit);
DWFAPI BOOL FDwfAnalogOutLimitationGet(HDWF hdwf, int idxChannel, double *plimit);

DWFAPI BOOL FDwfAnalogOutModeSet(HDWF hdwf, int idxChannel, DwfAnalogOutMode mode);
DWFAPI BOOL FDwfAnalogOutModeGet(HDWF hdwf, int idxChannel, DwfAnalogOutMode *pmode);

DWFAPI BOOL FDwfAnalogOutIdleInfo(HDWF hdwf, int idxChannel, int *pfsidle);
DWFAPI BOOL FDwfAnalogOutIdleSet(HDWF hdwf, int idxChannel, DwfAnalogOutIdle idle);
DWFAPI BOOL FDwfAnalogOutIdleGet(HDWF hdwf, int idxChannel, DwfAnalogOutIdle *pidle);

DWFAPI BOOL FDwfAnalogOutNodeInfo(HDWF hdwf, int idxChannel, int *pfsnode); // use IsBitSet

DWFAPI BOOL FDwfAnalogOutNodeEnableSet(HDWF hdwf, int idxChannel, AnalogOutNode node, BOOL fEnable);
DWFAPI BOOL FDwfAnalogOutNodeEnableGet(HDWF hdwf, int idxChannel, AnalogOutNode node, BOOL *pfEnable);

DWFAPI BOOL FDwfAnalogOutNodeFunctionInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pfsfunc); // use IsBitSet
DWFAPI BOOL FDwfAnalogOutNodeFunctionSet(HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC func);
DWFAPI BOOL FDwfAnalogOutNodeFunctionGet(HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC *pfunc);

DWFAPI BOOL FDwfAnalogOutNodeFrequencyInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzMin, double *phzMax);
DWFAPI BOOL FDwfAnalogOutNodeFrequencySet(HDWF hdwf, int idxChannel, AnalogOutNode node, double hzFrequency);
DWFAPI BOOL FDwfAnalogOutNodeFrequencyGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzFrequency);
// Carrier Amplitude or Modulation Index 
DWFAPI BOOL FDwfAnalogOutNodeAmplitudeInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax);
DWFAPI BOOL FDwfAnalogOutNodeAmplitudeSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double vAmplitude);
DWFAPI BOOL FDwfAnalogOutNodeAmplitudeGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvAmplitude);

DWFAPI BOOL FDwfAnalogOutNodeOffsetInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax);
DWFAPI BOOL FDwfAnalogOutNodeOffsetSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double vOffset);
DWFAPI BOOL FDwfAnalogOutNodeOffsetGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvOffset);

DWFAPI BOOL FDwfAnalogOutNodeSymmetryInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageMin, double *ppercentageMax);
DWFAPI BOOL FDwfAnalogOutNodeSymmetrySet(HDWF hdwf, int idxChannel, AnalogOutNode node, double percentageSymmetry);
DWFAPI BOOL FDwfAnalogOutNodeSymmetryGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageSymmetry);

DWFAPI BOOL FDwfAnalogOutNodePhaseInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreeMin, double *pdegreeMax);
DWFAPI BOOL FDwfAnalogOutNodePhaseSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double degreePhase);
DWFAPI BOOL FDwfAnalogOutNodePhaseGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreePhase);

DWFAPI BOOL FDwfAnalogOutNodeDataInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pnSamplesMin, int *pnSamplesMax);
DWFAPI BOOL FDwfAnalogOutNodeDataSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData);

// needed for EExplorer, don't care for ADiscovery
DWFAPI BOOL FDwfAnalogOutCustomAMFMEnableSet(HDWF hdwf, int idxChannel, BOOL fEnable);
DWFAPI BOOL FDwfAnalogOutCustomAMFMEnableGet(HDWF hdwf, int idxChannel, BOOL *pfEnable);

// Control:
DWFAPI BOOL FDwfAnalogOutReset(HDWF hdwf, int idxChannel);
DWFAPI BOOL FDwfAnalogOutConfigure(HDWF hdwf, int idxChannel, BOOL fStart);
DWFAPI BOOL FDwfAnalogOutStatus(HDWF hdwf, int idxChannel, DwfState *psts);
DWFAPI BOOL FDwfAnalogOutNodePlayStatus(HDWF hdwf, int idxChannel, AnalogOutNode node, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted);
DWFAPI BOOL FDwfAnalogOutNodePlayData(HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData);


// ANALOG IO INSTRUMENT FUNCTIONS
// Control:
DWFAPI BOOL FDwfAnalogIOReset(HDWF hdwf);
DWFAPI BOOL FDwfAnalogIOConfigure(HDWF hdwf);
DWFAPI BOOL FDwfAnalogIOStatus(HDWF hdwf);

// Configure:
DWFAPI BOOL FDwfAnalogIOEnableInfo(HDWF hdwf, BOOL *pfSet, BOOL *pfStatus);
DWFAPI BOOL FDwfAnalogIOEnableSet(HDWF hdwf, BOOL fMasterEnable);
DWFAPI BOOL FDwfAnalogIOEnableGet(HDWF hdwf, BOOL *pfMasterEnable);
DWFAPI BOOL FDwfAnalogIOEnableStatus(HDWF hdwf, BOOL *pfMasterEnable);
DWFAPI BOOL FDwfAnalogIOChannelCount(HDWF hdwf, int *pnChannel);
DWFAPI BOOL FDwfAnalogIOChannelName(HDWF hdwf, int idxChannel, char szName[32], char szLabel[16]);
DWFAPI BOOL FDwfAnalogIOChannelInfo(HDWF hdwf, int idxChannel, int *pnNodes);
DWFAPI BOOL FDwfAnalogIOChannelNodeName(HDWF hdwf, int idxChannel, int idxNode, char szNodeName[32], char szNodeUnits[16]);
DWFAPI BOOL FDwfAnalogIOChannelNodeInfo(HDWF hdwf, int idxChannel, int idxNode, ANALOGIO *panalogio);
DWFAPI BOOL FDwfAnalogIOChannelNodeSetInfo(HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps);
DWFAPI BOOL FDwfAnalogIOChannelNodeSet(HDWF hdwf, int idxChannel, int idxNode, double value);
DWFAPI BOOL FDwfAnalogIOChannelNodeGet(HDWF hdwf, int idxChannel, int idxNode, double *pvalue);
DWFAPI BOOL FDwfAnalogIOChannelNodeStatusInfo(HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps);
DWFAPI BOOL FDwfAnalogIOChannelNodeStatus(HDWF hdwf, int idxChannel, int idxNode, double *pvalue);


// DIGITAL IO INSTRUMENT FUNCTIONS
// Control:
DWFAPI BOOL FDwfDigitalIOReset(HDWF hdwf);
DWFAPI BOOL FDwfDigitalIOConfigure(HDWF hdwf);
DWFAPI BOOL FDwfDigitalIOStatus(HDWF hdwf);

// Configure:
DWFAPI BOOL FDwfDigitalIOOutputEnableInfo(HDWF hdwf, unsigned int *pfsOutputEnableMask);
DWFAPI BOOL FDwfDigitalIOOutputEnableSet(HDWF hdwf, unsigned int fsOutputEnable);
DWFAPI BOOL FDwfDigitalIOOutputEnableGet(HDWF hdwf, unsigned int *pfsOutputEnable);
DWFAPI BOOL FDwfDigitalIOOutputInfo(HDWF hdwf, unsigned int *pfsOutputMask);
DWFAPI BOOL FDwfDigitalIOOutputSet(HDWF hdwf, unsigned int fsOutput);
DWFAPI BOOL FDwfDigitalIOOutputGet(HDWF hdwf, unsigned int *pfsOutput);
DWFAPI BOOL FDwfDigitalIOInputInfo(HDWF hdwf, unsigned int *pfsInputMask);
DWFAPI BOOL FDwfDigitalIOInputStatus(HDWF hdwf, unsigned int *pfsInput);


// DIGITAL IN INSTRUMENT FUNCTIONS
// Control and status: 
DWFAPI BOOL FDwfDigitalInReset(HDWF hdwf);
DWFAPI BOOL FDwfDigitalInConfigure(HDWF hdwf, BOOL fReconfigure, BOOL fStart);
DWFAPI BOOL FDwfDigitalInStatus(HDWF hdwf, BOOL fReadData, DwfState *psts);
DWFAPI BOOL FDwfDigitalInStatusSamplesLeft(HDWF hdwf, int *pcSamplesLeft);
DWFAPI BOOL FDwfDigitalInStatusSamplesValid(HDWF hdwf, int *pcSamplesValid);
DWFAPI BOOL FDwfDigitalInStatusIndexWrite(HDWF hdwf, int *pidxWrite);
DWFAPI BOOL FDwfDigitalInStatusAutoTriggered(HDWF hdwf, BOOL *pfAuto);
DWFAPI BOOL FDwfDigitalInStatusData(HDWF hdwf, void *rgData, int countOfDataBytes);
DWFAPI BOOL FDwfDigitalInStatusData2(HDWF hdwf, void *rgData, int idxByte, int countOfDataBytes);
DWFAPI BOOL FDwfDigitalInStatusRecord(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt);

// Acquisition configuration:
DWFAPI BOOL FDwfDigitalInInternalClockInfo(HDWF hdwf, double *phzFreq);

DWFAPI BOOL FDwfDigitalInClockSourceInfo(HDWF hdwf, int *pfsDwfDigitalInClockSource); // use IsBitSet
DWFAPI BOOL FDwfDigitalInClockSourceSet(HDWF hdwf, DwfDigitalInClockSource v);
DWFAPI BOOL FDwfDigitalInClockSourceGet(HDWF hdwf, DwfDigitalInClockSource *pv);

DWFAPI BOOL FDwfDigitalInDividerInfo(HDWF hdwf, unsigned int *pdivMax);
DWFAPI BOOL FDwfDigitalInDividerSet(HDWF hdwf, unsigned int div);
DWFAPI BOOL FDwfDigitalInDividerGet(HDWF hdwf, unsigned int *pdiv);

DWFAPI BOOL FDwfDigitalInBitsInfo(HDWF hdwf, int *pnBits); // Returns the number of Digital In bits
DWFAPI BOOL FDwfDigitalInSampleFormatSet(HDWF hdwf, int nBits);  // valid options 8/16/32
DWFAPI BOOL FDwfDigitalInSampleFormatGet(HDWF hdwf, int *pnBits);

DWFAPI BOOL FDwfDigitalInBufferSizeInfo(HDWF hdwf, int *pnSizeMax);
DWFAPI BOOL FDwfDigitalInBufferSizeSet(HDWF hdwf, int nSize);
DWFAPI BOOL FDwfDigitalInBufferSizeGet(HDWF hdwf, int *pnSize);

DWFAPI BOOL FDwfDigitalInSampleModeInfo(HDWF hdwf, int *pfsDwfDigitalInSampleMode); // use IsBitSet
DWFAPI BOOL FDwfDigitalInSampleModeSet(HDWF hdwf, DwfDigitalInSampleMode v);  // 
DWFAPI BOOL FDwfDigitalInSampleModeGet(HDWF hdwf, DwfDigitalInSampleMode *pv);

DWFAPI BOOL FDwfDigitalInAcquisitionModeInfo(HDWF hdwf, int *pfsacqmode); // use IsBitSet
DWFAPI BOOL FDwfDigitalInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode);
DWFAPI BOOL FDwfDigitalInAcquisitionModeGet(HDWF hdwf, ACQMODE *pacqmode);
DWFAPI BOOL FDwfDigitalInMixedSet(HDWF hdwf, BOOL fEnable);

// Trigger configuration:
DWFAPI BOOL FDwfDigitalInTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfDigitalInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI BOOL FDwfDigitalInTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI BOOL FDwfDigitalInTriggerPositionInfo(HDWF hdwf, unsigned int *pnSamplesAfterTriggerMax);
DWFAPI BOOL FDwfDigitalInTriggerPositionSet(HDWF hdwf, unsigned int cSamplesAfterTrigger);
DWFAPI BOOL FDwfDigitalInTriggerPositionGet(HDWF hdwf, unsigned int *pcSamplesAfterTrigger);

DWFAPI BOOL FDwfDigitalInTriggerPrefillSet(HDWF hdwf, unsigned int cSamplesBeforeTrigger);
DWFAPI BOOL FDwfDigitalInTriggerPrefillGet(HDWF hdwf, unsigned int *pcSamplesBeforeTrigger);

DWFAPI BOOL FDwfDigitalInTriggerAutoTimeoutInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps);
DWFAPI BOOL FDwfDigitalInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout);
DWFAPI BOOL FDwfDigitalInTriggerAutoTimeoutGet(HDWF hdwf, double *psecTimeout);

DWFAPI BOOL FDwfDigitalInTriggerInfo(HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall);
DWFAPI BOOL FDwfDigitalInTriggerSet(HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall);
DWFAPI BOOL FDwfDigitalInTriggerGet(HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall);
// the logic for trigger bits: Low and High and (Rise or Fall)
// bits set in Rise and Fall means any edge

DWFAPI BOOL FDwfDigitalInTriggerResetSet(HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall);
DWFAPI BOOL FDwfDigitalInTriggerCountSet(HDWF hdwf, int cCount, int fRestart);
DWFAPI BOOL FDwfDigitalInTriggerLengthSet(HDWF hdwf, double secMin, double secMax, int fSync);
DWFAPI BOOL FDwfDigitalInTriggerMatchSet(HDWF hdwf, int iPin, unsigned int fsMask, unsigned int fsValue, int cBitStuffing);


// DIGITAL OUT INSTRUMENT FUNCTIONS
// Control:
DWFAPI BOOL FDwfDigitalOutReset(HDWF hdwf);
DWFAPI BOOL FDwfDigitalOutConfigure(HDWF hdwf, BOOL fStart);
DWFAPI BOOL FDwfDigitalOutStatus(HDWF hdwf, DwfState *psts);

// Configuration:
DWFAPI BOOL FDwfDigitalOutInternalClockInfo(HDWF hdwf, double *phzFreq);

DWFAPI BOOL FDwfDigitalOutTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc); // use IsBitSet
DWFAPI BOOL FDwfDigitalOutTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc);
DWFAPI BOOL FDwfDigitalOutTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc);

DWFAPI BOOL FDwfDigitalOutRunInfo(HDWF hdwf, double *psecMin, double *psecMax);
DWFAPI BOOL FDwfDigitalOutRunSet(HDWF hdwf, double secRun);
DWFAPI BOOL FDwfDigitalOutRunGet(HDWF hdwf, double *psecRun);
DWFAPI BOOL FDwfDigitalOutRunStatus(HDWF hdwf, double *psecRun);

DWFAPI BOOL FDwfDigitalOutWaitInfo(HDWF hdwf, double *psecMin, double *psecMax);
DWFAPI BOOL FDwfDigitalOutWaitSet(HDWF hdwf, double secWait);
DWFAPI BOOL FDwfDigitalOutWaitGet(HDWF hdwf, double *psecWait);

DWFAPI BOOL FDwfDigitalOutRepeatInfo(HDWF hdwf, unsigned int *pnMin, unsigned int *pnMax);
DWFAPI BOOL FDwfDigitalOutRepeatSet(HDWF hdwf, unsigned int cRepeat);
DWFAPI BOOL FDwfDigitalOutRepeatGet(HDWF hdwf, unsigned int *pcRepeat);
DWFAPI BOOL FDwfDigitalOutRepeatStatus(HDWF hdwf, unsigned int *pcRepeat);

DWFAPI BOOL FDwfDigitalOutRepeatTriggerSet(HDWF hdwf, BOOL fRepeatTrigger);
DWFAPI BOOL FDwfDigitalOutRepeatTriggerGet(HDWF hdwf, BOOL *pfRepeatTrigger);

DWFAPI BOOL FDwfDigitalOutCount(HDWF hdwf, int *pcChannel);
DWFAPI BOOL FDwfDigitalOutEnableSet(HDWF hdwf, int idxChannel, BOOL fEnable);
DWFAPI BOOL FDwfDigitalOutEnableGet(HDWF hdwf, int idxChannel, BOOL *pfEnable);

DWFAPI BOOL FDwfDigitalOutOutputInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutOutput); // use IsBitSet
DWFAPI BOOL FDwfDigitalOutOutputSet(HDWF hdwf, int idxChannel, DwfDigitalOutOutput v); 
DWFAPI BOOL FDwfDigitalOutOutputGet(HDWF hdwf, int idxChannel, DwfDigitalOutOutput *pv);

DWFAPI BOOL FDwfDigitalOutTypeInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutType); // use IsBitSet
DWFAPI BOOL FDwfDigitalOutTypeSet(HDWF hdwf, int idxChannel, DwfDigitalOutType v);
DWFAPI BOOL FDwfDigitalOutTypeGet(HDWF hdwf, int idxChannel, DwfDigitalOutType *pv);

DWFAPI BOOL FDwfDigitalOutIdleInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutIdle); // use IsBitSet
DWFAPI BOOL FDwfDigitalOutIdleSet(HDWF hdwf, int idxChannel, DwfDigitalOutIdle v);
DWFAPI BOOL FDwfDigitalOutIdleGet(HDWF hdwf, int idxChannel, DwfDigitalOutIdle *pv);

DWFAPI BOOL FDwfDigitalOutDividerInfo(HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax);
DWFAPI BOOL FDwfDigitalOutDividerInitSet(HDWF hdwf, int idxChannel, unsigned int v);
DWFAPI BOOL FDwfDigitalOutDividerInitGet(HDWF hdwf, int idxChannel, unsigned int *pv);
DWFAPI BOOL FDwfDigitalOutDividerSet(HDWF hdwf, int idxChannel, unsigned int v);
DWFAPI BOOL FDwfDigitalOutDividerGet(HDWF hdwf, int idxChannel, unsigned int *pv);

DWFAPI BOOL FDwfDigitalOutCounterInfo(HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax);
DWFAPI BOOL FDwfDigitalOutCounterInitSet(HDWF hdwf, int idxChannel, BOOL fHigh, unsigned int v);
DWFAPI BOOL FDwfDigitalOutCounterInitGet(HDWF hdwf, int idxChannel, int *pfHigh, unsigned int *pv);
DWFAPI BOOL FDwfDigitalOutCounterSet(HDWF hdwf, int idxChannel, unsigned int vLow, unsigned int vHigh);
DWFAPI BOOL FDwfDigitalOutCounterGet(HDWF hdwf, int idxChannel, unsigned int *pvLow, unsigned int *pvHigh);

DWFAPI BOOL FDwfDigitalOutDataInfo(HDWF hdwf, int idxChannel, unsigned int *pcountOfBitsMax);
DWFAPI BOOL FDwfDigitalOutDataSet(HDWF hdwf, int idxChannel, void *rgBits, unsigned int countOfBits);
// bits order is lsb first
// for TS output the count of bits its the total number of IO|OE bits, it should be an even number
// BYTE:   0                 |1     ...
// bit:    0 |1 |2 |3 |...|7 |0 |1 |...
// sample: IO|OE|IO|OE|...|OE|IO|OE|...


// OBSOLETE, do not use them:
typedef BYTE STS;
const STS stsRdy        = 0;
const STS stsArm        = 1;
const STS stsDone       = 2;
const STS stsTrig       = 3;
const STS stsCfg        = 4;
const STS stsPrefill    = 5;
const STS stsNotDone    = 6;
const STS stsTrigDly    = 7;
const STS stsError      = 8;
const STS stsBusy       = 9;
const STS stsStop       = 10;

DWFAPI BOOL FDwfAnalogOutEnableSet(HDWF hdwf, int idxChannel, BOOL fEnable);
DWFAPI BOOL FDwfAnalogOutEnableGet(HDWF hdwf, int idxChannel, BOOL *pfEnable);
DWFAPI BOOL FDwfAnalogOutFunctionInfo(HDWF hdwf, int idxChannel, int *pfsfunc); // use IsBitSet
DWFAPI BOOL FDwfAnalogOutFunctionSet(HDWF hdwf, int idxChannel, FUNC func);
DWFAPI BOOL FDwfAnalogOutFunctionGet(HDWF hdwf, int idxChannel, FUNC *pfunc);
DWFAPI BOOL FDwfAnalogOutFrequencyInfo(HDWF hdwf, int idxChannel, double *phzMin, double *phzMax);
DWFAPI BOOL FDwfAnalogOutFrequencySet(HDWF hdwf, int idxChannel, double hzFrequency);
DWFAPI BOOL FDwfAnalogOutFrequencyGet(HDWF hdwf, int idxChannel, double *phzFrequency);
DWFAPI BOOL FDwfAnalogOutAmplitudeInfo(HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax);
DWFAPI BOOL FDwfAnalogOutAmplitudeSet(HDWF hdwf, int idxChannel, double voltsAmplitude);
DWFAPI BOOL FDwfAnalogOutAmplitudeGet(HDWF hdwf, int idxChannel, double *pvoltsAmplitude);
DWFAPI BOOL FDwfAnalogOutOffsetInfo(HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax);
DWFAPI BOOL FDwfAnalogOutOffsetSet(HDWF hdwf, int idxChannel, double voltsOffset);
DWFAPI BOOL FDwfAnalogOutOffsetGet(HDWF hdwf, int idxChannel, double *pvoltsOffset);
DWFAPI BOOL FDwfAnalogOutSymmetryInfo(HDWF hdwf, int idxChannel, double *ppercentageMin, double *ppercentageMax);
DWFAPI BOOL FDwfAnalogOutSymmetrySet(HDWF hdwf, int idxChannel, double percentageSymmetry);
DWFAPI BOOL FDwfAnalogOutSymmetryGet(HDWF hdwf, int idxChannel, double *ppercentageSymmetry);
DWFAPI BOOL FDwfAnalogOutPhaseInfo(HDWF hdwf, int idxChannel, double *pdegreeMin, double *pdegreeMax);
DWFAPI BOOL FDwfAnalogOutPhaseSet(HDWF hdwf, int idxChannel, double degreePhase);
DWFAPI BOOL FDwfAnalogOutPhaseGet(HDWF hdwf, int idxChannel, double *pdegreePhase);
DWFAPI BOOL FDwfAnalogOutDataInfo(HDWF hdwf, int idxChannel, int *pnSamplesMin, int *pnSamplesMax);
DWFAPI BOOL FDwfAnalogOutDataSet(HDWF hdwf, int idxChannel, double *rgdData, int cdData);
DWFAPI BOOL FDwfAnalogOutPlayStatus(HDWF hdwf, int idxChannel, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted);
DWFAPI BOOL FDwfAnalogOutPlayData(HDWF hdwf, int idxChannel, double *rgdData, int cdData);

DWFAPI BOOL FDwfEnumAnalogInChannels(int idxDevice, int *pnChannels);
DWFAPI BOOL FDwfEnumAnalogInBufferSize(int idxDevice, int *pnBufferSize);
DWFAPI BOOL FDwfEnumAnalogInBits(int idxDevice, int *pnBits);
DWFAPI BOOL FDwfEnumAnalogInFrequency(int idxDevice, double *phzFrequency);

#endif
