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

    printf("Generating synchronized waveforms for 5 seconds...");    
    // enable two channels
    FDwfAnalogOutNodeEnableSet(hdwf, 0, AnalogOutNodeCarrier, true);
    FDwfAnalogOutNodeEnableSet(hdwf, 1, AnalogOutNodeCarrier, true);
    // for second channel set master the first channel
    FDwfAnalogOutMasterSet(hdwf, 1, 0);
    // slave channel is controlled by the master channel
    // it is enough to set trigger, wait, run and repeat parameters for master channel
    // when using different frequencies it might need periodical resynchronization
    // to do so set limited runtime and repeat infinite
    
    // configure enabled channels
    FDwfAnalogOutNodeFunctionSet(hdwf, -1, AnalogOutNodeCarrier, funcSine);
    FDwfAnalogOutNodeFrequencySet(hdwf, -1, AnalogOutNodeCarrier, 10000.0);
    FDwfAnalogOutNodeAmplitudeSet(hdwf, -1, AnalogOutNodeCarrier, 1.0);
    // set phase for second channel
    FDwfAnalogOutNodePhaseSet(hdwf, 1, AnalogOutNodeCarrier, 180.0);    
    
    // slave channel will only be initialized
    FDwfAnalogOutConfigure(hdwf, 1, true);
    // starting master will start slave channels too
    FDwfAnalogOutConfigure(hdwf, 0, true);
    // it will run until stopped, reset, parameter changed or device closed
    Wait(5);
    printf("done\n");
    // on close device is stopped and configuration lost
    FDwfDeviceClose(hdwf);
}