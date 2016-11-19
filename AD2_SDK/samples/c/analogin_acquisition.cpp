#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    double* rgdSamples;
    int cSamples;
    int cChannel;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    // get the number of analog in channels
    FDwfAnalogInChannelCount(hdwf, &cChannel);
    
    // enable channels
    for(int c = 0; c < cChannel; c++){
        FDwfAnalogInChannelEnableSet(hdwf, c, true);
    }
    // set 5V pk2pk input range for all channels
    FDwfAnalogInChannelRangeSet(hdwf, -1, 5);
    
    // 20MHz sample rate
    FDwfAnalogInFrequencySet(hdwf, 20000000.0);
        
    // get the maximum buffer size
    FDwfAnalogInBufferSizeInfo(hdwf, NULL, &cSamples);
    FDwfAnalogInBufferSizeSet(hdwf, cSamples);
    
    rgdSamples = new double[cSamples];

    // configure trigger
    FDwfAnalogInTriggerSourceSet(hdwf, trigsrcDetectorAnalogIn);
    FDwfAnalogInTriggerAutoTimeoutSet(hdwf, 10.0);
    FDwfAnalogInTriggerChannelSet(hdwf, 0);
    FDwfAnalogInTriggerTypeSet(hdwf, trigtypeEdge);
    FDwfAnalogInTriggerLevelSet(hdwf, 1.0);
    FDwfAnalogInTriggerConditionSet(hdwf, trigcondRisingPositive);

    // wait at least 2 seconds with Analog Discovery for the offset to stabilize, before the first reading after device open or offset/range change
    Wait(2);

    // start
    FDwfAnalogInConfigure(hdwf, 0, true);
    
    printf("Waiting for triggered or auto acquisition\n");
    do{
        FDwfAnalogInStatus(hdwf, true, &sts);
    }while(sts != stsDone);
    
    // get the samples for each channel
    for(int c = 0; c < cChannel; c++){
        FDwfAnalogInStatusData(hdwf, c, rgdSamples, cSamples);
        // do something with it
    }
    
    printf("done\n");
    
    // close the device
    FDwfDeviceClose(hdwf);
}