#include "sample.h"


int main(int carg, char **szarg){
    HDWF hdwf;
    double voltage;
    char szError[512] = {0};
    
    // open automatically the first available device
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }
    
    // enable first channel FDwfAnalogInChannelEnableSet(hdwf, 0, true)
    // set 0V offset
    FDwfAnalogInChannelOffsetSet(hdwf, 0, 0);
    // set 5V pk2pk input range, -2.5V to 2.5V
    FDwfAnalogInChannelRangeSet(hdwf, 0, 5);
    // start signal generation
    FDwfAnalogInConfigure(hdwf, 0, false);
    // wait at least 2 seconds with Analog Discovery for the offset to stabilize, before the first reading after device open or offset/range change
    Wait(2);
    
    printf("Analog in channel 1 voltage:\n");
    for(int i = 0; i < 10; i++){
        Wait(1);
        // fetch analog input information from the device
        FDwfAnalogInStatus(hdwf, false, NULL);
        // read voltage input of first channel
        FDwfAnalogInStatusSample(hdwf, 0, &voltage);
        printf("%.3lf V\n", voltage);
    }
    // close all opened devices by this process
    FDwfDeviceCloseAll();
}