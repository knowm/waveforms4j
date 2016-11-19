#include "sample.h"

#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    double hzAcq = 50000.0, secRecord;
    const int nSamples = 100000;
    double* rgdSamples = new double[nSamples];
    int cSamples = 0;
    int cAvailable, cLost, cCorrupted;
    bool fLost = false, fCorrupted = false;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }
    
    FDwfAnalogInChannelEnableSet(hdwf, 0, true);
    
    FDwfAnalogInChannelRangeSet(hdwf, 0, 5);
    
    // recording rate for more samples than the device buffer is limited by device communication
    FDwfAnalogInAcquisitionModeSet(hdwf, acqmodeRecord);
    FDwfAnalogInFrequencySet(hdwf, hzAcq);
    FDwfAnalogInRecordLengthSet(hdwf, 1.0*nSamples/hzAcq);
    
    // wait at least 2 seconds with Analog Discovery for the offset to stabilize, before the first reading after device open or offset/range change
    Wait(2);
    
    // start
    FDwfAnalogInConfigure(hdwf, false, true);
    
    printf("Recording...\n");
    while(cSamples < nSamples){
        if(!FDwfAnalogInStatus(hdwf, true, &sts)) {
            printf("error");
            return 0;
        }
        if(cSamples == 0 && (sts == stsCfg || sts == stsPrefill || sts == stsArm)){
            // Acquisition not yet started.
            continue;
        }

        FDwfAnalogInStatusRecord(hdwf, &cAvailable, &cLost, &cCorrupted);

        cSamples += cLost;
        
        if(cLost) fLost = true;
        if(cCorrupted) fCorrupted = false;

        if(!cAvailable) continue;

        // get samples
        FDwfAnalogInStatusData(hdwf, 0, &rgdSamples[cSamples], cAvailable);
        cSamples += cAvailable;
    }

    printf("done\n");
    
    if(fLost){
        printf("Samples were lost! Reduce frequency");
    }else if(cCorrupted){
        printf("Samples could be corrupted! Reduce frequency");
    }

    // close the device
    FDwfDeviceClose(hdwf);
}