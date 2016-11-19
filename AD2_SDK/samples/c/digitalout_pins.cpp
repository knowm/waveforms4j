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
    
    // 1kHz pulse on IO pin 0
    FDwfDigitalOutEnableSet(hdwf, 0, 1);
    // prescaler to 2kHz, SystemFrequency/1kHz/2
    FDwfDigitalOutDividerSet(hdwf, 0, hzSys/1e3/2);
    // 1 tick low, 1 tick high
    FDwfDigitalOutCounterSet(hdwf, 0, 1, 1);
    
    // 1kHz 25% duty pulse on IO pin 1
    FDwfDigitalOutEnableSet(hdwf, 1, 1);
    // prescaler to 4kHz SystemFrequency/1kHz/2
    FDwfDigitalOutDividerSet(hdwf, 1, hzSys/1e3/4);
    // 3 ticks low, 1 tick high
    FDwfDigitalOutCounterSet(hdwf, 1, 3, 1);
    
    // 2kHz random on IO pin 2
    FDwfDigitalOutEnableSet(hdwf, 2, 1);
    FDwfDigitalOutTypeSet(hdwf, 2, DwfDigitalOutTypeRandom);
    FDwfDigitalOutDividerSet(hdwf, 2, hzSys/2e3);

    BYTE rgcustom[4] = {0x00,0xAA,0x66,0xFF};
    // 1kHz custom on IO pin 3
    FDwfDigitalOutEnableSet(hdwf, 3, 1);
    FDwfDigitalOutTypeSet(hdwf, 3, DwfDigitalOutTypeCustom);
    FDwfDigitalOutDividerSet(hdwf, 3, hzSys/1e3);
    FDwfDigitalOutDataSet(hdwf, 3, rgcustom, 4*8);
    
    FDwfDigitalOutConfigure(hdwf, 1);
    
    // it will run until stopped, reset, parameter changed or device closed
    Wait(5);
    printf("done\n");

    FDwfDigitalOutReset(hdwf);
    // on close device is stopped and configuration lost
    FDwfDeviceCloseAll();
}