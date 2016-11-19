#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }
    
    printf("Generating waveform for 5 seconds...");    
    // enable first channel
    FDwfAnalogOutNodeEnableSet(hdwf, 0, AnalogOutNodeCarrier, true);
    // set sine function
    FDwfAnalogOutNodeFunctionSet(hdwf, 0, AnalogOutNodeCarrier, funcSine);
    // 10 Hz
    FDwfAnalogOutNodeFrequencySet(hdwf, 0, AnalogOutNodeCarrier, 10.0);
    // 1.41V amplitude (1Vrms), 2.82V pk2pk
    FDwfAnalogOutNodeAmplitudeSet(hdwf, 0, AnalogOutNodeCarrier, 1.41);
    // 1.41V offset
    FDwfAnalogOutNodeOffsetSet(hdwf, 0, AnalogOutNodeCarrier, 1.41);
    // start signal generation
    FDwfAnalogOutConfigure(hdwf, 0, true);
    // it will run until stopped, reset, parameter changed or device closed
    Wait(5);
    printf("done\n");

    // on close device is stopped and configuration lost
    FDwfDeviceClose(hdwf);
}