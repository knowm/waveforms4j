#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }
  
    printf("Generating phased pulses:\n");

  
    // 2 pin phase start low and high
    for(int i = 0; i < 2; i++){
        FDwfDigitalOutEnableSet(hdwf, i, true);
        FDwfDigitalOutCounterInitSet(hdwf, i, (i==1), 0);
        //100MHz base freq /(50+50) = 1MHz
        FDwfDigitalOutCounterSet(hdwf, i, 50, 50);
    }
    FDwfDigitalOutConfigure(hdwf, true);
    printf("on 2 IOs for 5 seconds...\n");
    Wait(5);

    // 3 pin phase
    FDwfDigitalOutCounterInitSet(hdwf, 0, 1, 0);
    FDwfDigitalOutCounterInitSet(hdwf, 1, 0, 20);
    FDwfDigitalOutCounterInitSet(hdwf, 2, 1, 10);
    for(int i = 0; i < 3; i++){
        FDwfDigitalOutEnableSet(hdwf, i, true);
        // 100MHz base freq /(30+30) = 1.67 MHz
        FDwfDigitalOutCounterSet(hdwf, i, 30, 30);
    }
    FDwfDigitalOutConfigure(hdwf, true);
    printf("on 3 IOs for 5 seconds...\n");
    Wait(5);


    // 4 pin phase starting: low & 25, low $ 50, high & 25, high & 50 
    for(int i = 0; i < 4; i++){
        FDwfDigitalOutEnableSet(hdwf, i, 1);
        FDwfDigitalOutCounterInitSet(hdwf, i, ((i==2) || (i==3)), ((i==0 || i==2)?25:50));
        FDwfDigitalOutCounterSet(hdwf, i, 50, 50);
    }
    FDwfDigitalOutConfigure(hdwf, 1);
    printf("on 4 IOs for 5 seconds...\n");
    Wait(5);

    printf("done\n");
    FDwfDeviceCloseAll();
}