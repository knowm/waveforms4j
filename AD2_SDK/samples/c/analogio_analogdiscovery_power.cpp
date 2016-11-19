#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    double vSupply, aSupply, wSupply;
    int prcSupply;
    int fOn;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    // set up analog IO channel nodes
    // enable positive supply
    FDwfAnalogIOChannelNodeSet(hdwf, 0, 0, 1);
    // enable negative supply
    FDwfAnalogIOChannelNodeSet(hdwf, 1, 0, 1);
    // master enable
    FDwfAnalogIOEnableSet(hdwf, true);

    printf("Total supply power and load percentage:\n");
    for(int i = 0; i < 60; i++){
        // wait 1 second between readings
        Wait(1);
        // fetch analogIO status from device
        FDwfAnalogIOStatus(hdwf);

        // supply monitor
        FDwfAnalogIOChannelNodeStatus(hdwf, 3, 0, &vSupply);
        FDwfAnalogIOChannelNodeStatus(hdwf, 3, 1, &aSupply);
        wSupply = vSupply * aSupply;

        prcSupply = 100 * (aSupply / 0.2);
        printf("%.3lf W \t%i%%\n", wSupply, prcSupply);
        
        // in case of over-current condition the supplies are disabled
        FDwfAnalogIOEnableStatus(hdwf, &fOn);
        if(!fOn){
            // re-enable supplies
            FDwfAnalogIOEnableSet(hdwf, false);
            FDwfAnalogIOEnableSet(hdwf, true);
        }
    }

    // close the device
    FDwfDeviceClose(hdwf);
}