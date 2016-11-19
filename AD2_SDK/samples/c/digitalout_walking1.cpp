#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    double hzSys;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    printf("Generating digital signals...");
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);

    // 10 bit walking 1
    for(int i = 0; i < 10; i++){
        FDwfDigitalOutEnableSet(hdwf, i, 1);
        // divide system frequency down to 1khz
        FDwfDigitalOutDividerSet(hdwf, i, hzSys/1e3);
        // all pins will be 9 ticks low and 1 high
        FDwfDigitalOutCounterSet(hdwf, i, 9, 1);
        // first bit will start high others low with increasing phase
        FDwfDigitalOutCounterInitSet(hdwf, i, i==0, i==0?0:i);
    }

    // start digital out
    FDwfDigitalOutConfigure(hdwf, 1);
    
    // it will run until stopped, reset, parameter changed or device closed
    Wait(5);
    FDwfDigitalOutReset(hdwf);
    printf("done\n");

    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}