#include "sample.h"


int main(int carg, char **szarg){
    int cDevice;
    int cChannel;
    double hzFreq;
    char szDeviceName[32];
    char szSN[32];
    BOOL fIsInUse;
    HDWF hdwf;
    char szError[512];

    // detect connected all supported devices
    if(!FDwfEnum(enumfilterAll, &cDevice)){
        FDwfGetLastErrorMsg(szError);
        printf("FDwfEnum: %s\n", szError);
        return 0;
    }
    // list information about each device
    printf("Found %d devices:\n", cDevice);
    for(int i = 0; i < cDevice; i++){
        // we use 0 based indexing
        FDwfEnumDeviceName (i, szDeviceName);
        FDwfEnumSN(i, szSN);
        printf("\nDevice: %d name: %s %s\n", i+1, szDeviceName, szSN);
        // before opening, check if the device isn’t already opened by other application, like: WaveForms
        FDwfEnumDeviceIsOpened(i, &fIsInUse);
        if(!fIsInUse){
            if(!FDwfDeviceOpen(i, &hdwf)){
                FDwfGetLastErrorMsg(szError);
                printf("FDwfDeviceOpen: %s\n", szError);
                continue;
            }
            FDwfAnalogInChannelCount(hdwf, &cChannel);
            FDwfAnalogInFrequencyInfo(hdwf, NULL, &hzFreq);
            printf("number of analog input channels: %d maximum freq.: %.0f Hz\n", cChannel, hzFreq);
            FDwfDeviceClose(hdwf);
            hdwf = hdwfNone;
        }
    }
    // before application exit make sure to close all opened devices by this process
    FDwfDeviceCloseAll();
}