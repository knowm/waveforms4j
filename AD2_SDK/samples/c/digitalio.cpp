#include "sample.h"

int main(int carg, char **szarg){
    HDWF hdwf;
    STS sts;
    unsigned int dwRead;
    char szError[512] = {0};
    
    printf("Open automatically the first available device\n");
    if(!FDwfDeviceOpen(-1, &hdwf)) {
        FDwfGetLastErrorMsg(szError);
        printf("Device open failed\n\t%s", szError);
        return 0;
    }

    // enable output/mask on 8 LSB IO pins, from DIO 0 to 7
    FDwfDigitalIOOutputEnableSet(hdwf, 0x00FF);
    // set value on enabled IO pins
    FDwfDigitalIOOutputSet(hdwf, 0xFF);
    // fetch digital IO information from the device 
    FDwfDigitalIOStatus (hdwf);
    // read state of all pins, regardless of output enable
    FDwfDigitalIOInputStatus(hdwf, &dwRead);

    printf("Digital IO Pins:  0x%08X\n", dwRead);

    FDwfDeviceClose(hdwf);
}