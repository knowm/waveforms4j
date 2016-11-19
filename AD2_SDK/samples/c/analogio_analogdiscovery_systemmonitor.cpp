#include "sample.h"

int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    double vUsb, aUsb, degDevice;
    char szError[512];
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    // monitor voltage, current, temperature
    printf("Device USB supply voltage, current and device temperature: \n");
    for(int i = 0; i < 60; i++){
        // wait between readings; the update rate is approximately 1Hz
        Wait(1);
        // fetch analog IO status from device
        FDwfAnalogIOStatus(hdwf);
        // get system monitor readings
        FDwfAnalogIOChannelNodeStatus(hdwf, 2, 0, &vUsb);
        FDwfAnalogIOChannelNodeStatus(hdwf, 2, 1, &aUsb);
        FDwfAnalogIOChannelNodeStatus(hdwf, 2, 2, &degDevice);
        printf("%.3lf V \t%.3lf A \t%.2lf degC\n", vUsb, aUsb, degDevice);
    }
    // close the device
    FDwfDeviceClose(hdwf);
}