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
    
    printf("Generating digital signals...\n");
    FDwfDigitalOutInternalClockInfo(hdwf, &hzSys);
    printf("hzSysn\t%d\n", hzSys); 
   
    
    // Enable digital I/O channel 0
    FDwfDigitalOutEnableSet(hdwf, 0, 1);
    // prescaler to 2kHz, SystemFrequency/1Hz/2
    FDwfDigitalOutDividerSet(hdwf, 0, hzSys/4/2);
    // 1 tick low, 1 tick high
    FDwfDigitalOutCounterSet(hdwf, 0, 1, 1);
    

    FDwfDigitalOutConfigure(hdwf, 1);
    
    // it will run until stopped, reset, parameter changed or device closed
    Wait(5);
    printf("done\n");

    FDwfDigitalOutReset(hdwf);
    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}