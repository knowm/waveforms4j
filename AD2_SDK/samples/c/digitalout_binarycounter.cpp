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
    
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);

    printf("Generating binary counter...");
    for(int i = 0; i < 16; i++){
        FDwfDigitalOutEnableSet(hdwf, i, 1);
        // increase by 2 the period of successive bits
        FDwfDigitalOutDividerSet(hdwf, i, 1<<i);
        // 100kHz coutner rate, SystemFrequency/100kHz
        FDwfDigitalOutCounterSet(hdwf, i, hzSys/1e5, hzSys/1e5);
    }

    FDwfDigitalOutConfigure(hdwf, 1);
    
    // it will run until stopped, reset, parameter changed or device closed
    Wait(5);
    FDwfDigitalOutReset(hdwf);
    printf("done\n");

    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}