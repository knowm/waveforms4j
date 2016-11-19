#include "sample.h"


int main(int carg, char **szarg){
     
    HDWF hdwf;
    int idxChannel = 0;
    double hzStart = 1e3;
    double hzStop = 1e5;
    double secSweep = 1;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    printf("Generating frequency sweep for 5 seconds...");    
    // enable first channel
    FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, AnalogOutNodeCarrier, true);
    // set sine carrier
    FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, AnalogOutNodeCarrier, funcSine);
    // 1V amplitude, 2V pk2pk
    FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, AnalogOutNodeCarrier, 1.0);
    // 10kHz carrier frequency
    FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, AnalogOutNodeCarrier, (hzStart+hzStop)/2);
    // enable frequency modulation
    FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, AnalogOutNodeFM, true);
    // linear sweep with ramp up symmetry 100%
    FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, AnalogOutNodeFM, funcRampUp);
    FDwfAnalogOutNodeSymmetrySet(hdwf, idxChannel, AnalogOutNodeFM, 100);
    // modulation index
    FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, AnalogOutNodeFM, 100.0*(hzStop-hzStart)/(hzStart+hzStop));
    // FM frequency = 1/sweep time
    FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, AnalogOutNodeFM, 1.0/secSweep);

    // by default the offset is 0V
    // start signal generation
    FDwfAnalogOutConfigure(hdwf, idxChannel, true);
    // it will run until stopped or device closed
    Wait(5);
    printf("done\n");

    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}