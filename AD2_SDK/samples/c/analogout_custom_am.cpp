#include "sample.h"


int main(int carg, char **szarg){
     
    HDWF hdwf;
    double rgdSamples[1024];
    int idxChannel = 0;
    char szError[512] = {0};

    // generate custom samples normalized to +-1
    for(int i = 0; i < 1024; i++) rgdSamples[i] = 2.0*i/1023-1;
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    printf("Generating custom amplitude modulated waveform for 5 seconds...");    
    
    // needed for EExplorer, don't care for ADiscovery
    FDwfAnalogOutCustomAMFMEnableSet(hdwf, idxChannel, true);
    // enable first channel
    FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, AnalogOutNodeCarrier, true);
    // set sine carrier
    FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, AnalogOutNodeCarrier, funcSine);
    // 1V amplitude, 2V pk2pk
    FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, AnalogOutNodeCarrier, 1.0);
    // 10kHz carrier frequency
    FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, AnalogOutNodeCarrier, 1000.0);
    // enable amplitude modulation
    FDwfAnalogOutNodeEnableSet(hdwf, idxChannel, AnalogOutNodeAM, true);
    // set custom AM
    FDwfAnalogOutNodeFunctionSet(hdwf, idxChannel, AnalogOutNodeAM, funcCustom);
    // +-100% modulation index, will result with 1V amplitude carrier, 0V to 2V
    FDwfAnalogOutNodeAmplitudeSet(hdwf, idxChannel, AnalogOutNodeAM, 100);
    // 10Hz AM frequency
    FDwfAnalogOutNodeFrequencySet(hdwf, idxChannel, AnalogOutNodeAM, 10.0);
    // set custom waveform samples
    // normalized to ±1 values
    FDwfAnalogOutNodeDataSet(hdwf, idxChannel, AnalogOutNodeAM, rgdSamples, 1024);
    // by default the offset is 0V
    // start signal generation
    FDwfAnalogOutConfigure(hdwf, idxChannel, true);
    // it will run until stopped or device closed
    Wait(5);
    printf("done\n");

    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}