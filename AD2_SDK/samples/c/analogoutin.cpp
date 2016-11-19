#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    char szError[512] = {0};
    DwfState sts;
    const int nSamples = 1000;
    double* rgdSamples = new double[nSamples];

    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    printf("Configure and start first analog out channel\n");
    FDwfAnalogOutEnableSet(hdwf, 0, true);
    // 1 = Sine wave
    FDwfAnalogOutFunctionSet(hdwf, 0, 1);
    FDwfAnalogOutFrequencySet(hdwf, 0, 3000);
    FDwfAnalogOutConfigure(hdwf, 9, true);

    printf("Configure analog in\n");
    FDwfAnalogInFrequencySet(hdwf, 1000000);
    // set range for all channels
    FDwfAnalogInChannelRangeSet(hdwf, -1, 4);
    FDwfAnalogInBufferSizeSet(hdwf, nSamples);

    printf("Wait after first device opening the analog in offset to stabilize\n");
    Wait(2);

    printf("Starting acquisition\n");
    FDwfAnalogInConfigure(hdwf, true, true);

    printf("Waiting to finish... ");
    while(true){
        FDwfAnalogInStatus(hdwf, true, &sts);
        if(sts == DwfStateDone){
            break;
        }
        Wait(0.1);
    }
    printf("done\n");

    printf("Reading acquisition data\n");
    FDwfAnalogInStatusData(hdwf, 0, rgdSamples, nSamples);
    // do something with the data in rgdSample
    
    FDwfDeviceCloseAll();
}