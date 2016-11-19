#include "sample.h"

int main(int carg, char **szarg){
    HDWF hdwf;
    DwfState sts;
    double hzSys;
    int nSamples = 100000;
    unsigned short *rgwSamples = new unsigned short[nSamples];
    int cSamples = 0, cAvailable, cLost, cCorrupt;
    bool fLost = false, fCorrupt = false;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }
    // in record mode samples after trigger are acquired only
    FDwfDigitalInAcquisitionModeSet(hdwf, acqmodeRecord);
    // sample rate = system frequency / divider, 100MHz/1000 = 100kHz
    FDwfDigitalInDividerSet(hdwf, 1000);
    // 16bit per sample format
    FDwfDigitalInSampleFormatSet(hdwf, 16);
    // number of samples after trigger
    FDwfDigitalInTriggerPositionSet(hdwf, nSamples);
    // trigger when all digital pins are low
    FDwfDigitalInTriggerSourceSet(hdwf, trigsrcDetectorDigitalIn);
    // trigger detector mask: low &  hight & ( rising | falling )
    FDwfDigitalInTriggerSet(hdwf, 0xFFFF, 0, 0, 0);

    // begin acquisition
    FDwfDigitalInConfigure(hdwf, false, true);

    printf("Starting record...");

    while(cSamples < nSamples){
        FDwfDigitalInStatus(hdwf, 1, &sts);
        if(cSamples == 0 && (sts == DwfStateConfig || sts == DwfStatePrefill || sts == DwfStateArmed)){
            // acquisition not yet started.
            continue;
        }

        FDwfDigitalInStatusRecord(hdwf, &cAvailable, &cLost, &cCorrupt);

        cSamples += cLost;
        
        // samples lost due to device FIFO overflow
        if(cLost){
            fLost = true;
        }
        // samples could be corrupted by FIFO overflow
        if(cCorrupt){
            fCorrupt = true;
        }
        if(cAvailable==0){
            continue;
        }
        if(cSamples+cAvailable > nSamples){
            cAvailable = nSamples-cSamples;
        }
        // get samples
        FDwfDigitalInStatusData(hdwf, &rgwSamples[cSamples], 2*cAvailable);
        cSamples += cAvailable;
    }
    printf("done\n");
    FDwfDeviceClose(hdwf);
}