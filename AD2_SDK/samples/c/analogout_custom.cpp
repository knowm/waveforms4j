#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    double rgdSamples[4096];
    char szError[512] = {0};
    
    // generate custom samples normalized to +-1
    for(int i = 0; i < 4096; i++) rgdSamples[i] = 2.0*i/4095-1;
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    
    }

    printf("Generating custom waveform for 5 seconds...");    
    // enable first channel
    FDwfAnalogOutNodeEnableSet(hdwf, 0, AnalogOutNodeCarrier, true);
    // set custom function
    FDwfAnalogOutNodeFunctionSet(hdwf, 0, AnalogOutNodeCarrier, funcCustom);
    // set custom waveform samples
    // normalized to ±1 values
    FDwfAnalogOutNodeDataSet(hdwf, 0, AnalogOutNodeCarrier, rgdSamples, 4096);
    // 10kHz waveform frequency
    FDwfAnalogOutNodeFrequencySet(hdwf, 0, AnalogOutNodeCarrier, 10000.0);
    // 2V amplitude, 4V pk2pk, for sample value -1 will output -2V, for 1 +2V
    FDwfAnalogOutNodeAmplitudeSet(hdwf, 0, AnalogOutNodeCarrier, 2);
    // by default the offset is 0V
    // start signal generation
    FDwfAnalogOutConfigure(hdwf, 0, true);
    // it will run until stopped or device closed
    Wait(5);
    printf("done\n");
    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}