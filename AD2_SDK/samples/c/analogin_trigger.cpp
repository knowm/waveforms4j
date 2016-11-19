#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    int cSamples = 8192;
    double *rgdSamples = new double[cSamples];
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    FDwfAnalogInFrequencySet(hdwf, 20000000.0);
    FDwfAnalogInBufferSizeSet(hdwf, 8192);
    FDwfAnalogInChannelEnableSet(hdwf, 0, true);
    FDwfAnalogInChannelRangeSet(hdwf, 0, 5.0);

    // set up trigger
    // disable auto trigger
    FDwfAnalogInTriggerAutoTimeoutSet(hdwf, 0);
    // one of the analog in channels
    FDwfAnalogInTriggerSourceSet(hdwf, trigsrcDetectorAnalogIn);
    FDwfAnalogInTriggerTypeSet(hdwf, trigtypeEdge);
    // first channel
    FDwfAnalogInTriggerChannelSet(hdwf, 0);
    FDwfAnalogInTriggerLevelSet(hdwf, 0.5);
    FDwfAnalogInTriggerConditionSet(hdwf, trigcondRisingPositive);

    // wait at least 2 seconds with Analog Discovery for the offset to stabilize, before the first reading after device open or offset/range change
    Wait(2);

    printf("Starting repeated acquisitions:\n");
    for(int iTrigger = 0; iTrigger < 100; iTrigger++){
        // begin acquisition
        FDwfAnalogInConfigure(hdwf, false, true);

        while(true){
            FDwfAnalogInStatus(hdwf, true, &sts);
            if(sts == DwfStateDone) {
                break;
            }
            Wait(0.001);
        }
        FDwfAnalogInStatusData(hdwf, 0, rgdSamples, cSamples);
        double vAvg = 0;
        for(int i = 0; i < cSamples; i++){
            vAvg += rgdSamples[i];
        }
        vAvg /= cSamples;
        printf(" #%i average: %.3lf V\n", iTrigger+1, vAvg);
    }
    FDwfDeviceCloseAll();
}