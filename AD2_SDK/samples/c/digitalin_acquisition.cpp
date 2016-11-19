#include "sample.h"

int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    double hzSys;
    unsigned short *rgwSamples;
    int cSamples;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    FDwfDigitalInInternalClockInfo(hdwf, &hzSys);
    
    // sample rate to 1MHz
    FDwfDigitalInDividerSet(hdwf, hzSys/1e6);
    
    // 16bit WORD format
    FDwfDigitalInSampleFormatSet(hdwf, 16);

    // get the maximum buffer size
    FDwfDigitalInBufferSizeInfo(hdwf, &cSamples);
    // default buffer size is set to maximum
    //FDwfDigitalInBufferSizeSet(hdwf, cSamples);
    rgwSamples = new unsigned short[cSamples];

    // set trigger position to the middle 
    FDwfDigitalInTriggerPositionSet(hdwf, cSamples/2);
    
    // trigger on any pin transition
    FDwfDigitalInTriggerSourceSet(hdwf, trigsrcDetectorDigitalIn);
    FDwfDigitalInTriggerAutoTimeoutSet(hdwf, 10.0);
    FDwfDigitalInTriggerSet(hdwf, 0,0,0xFFFF,0xFFFF);
    
    // start
    FDwfDigitalInConfigure(hdwf, false, true);
    
    printf("Waiting for triggered or auto acquisition...");
    do{
        if(!FDwfDigitalInStatus(hdwf, true, &sts)) return 0;
    }while(sts != stsDone);

    // get the samples
    FDwfDigitalInStatusData(hdwf, rgwSamples, cSamples*sizeof(unsigned short));

    printf("done\n");
    
    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}