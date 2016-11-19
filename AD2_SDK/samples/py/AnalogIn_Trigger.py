"""
   DWF Python Example 5
   Author:  Digilent, Inc.
   Revision: 10/17/2013

   Requires:                       
       Python 2.7, numpy, matplotlib
       python-dateutil, pyparsing
"""
from ctypes import *
from dwfconstants import *
import math
import time
import matplotlib.pyplot as plt
import sys

if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
    dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
else:
    dwf = cdll.LoadLibrary("libdwf.so")

#declare ctype variables
hdwf = c_int()
sts = c_byte()
rgdSamples = (c_double*8192)()

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
print "Opening first device"
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == hdwfNone.value:
    szError = create_string_buffer(512)
    dwf.FDwfGetLastErrorMsg(szError);
    print "failed to open device\n"+szError.value
    quit()

print "Preparing to read sample..."

#set up acquisition
dwf.FDwfAnalogInFrequencySet(hdwf, c_double(20000000.0))
dwf.FDwfAnalogInBufferSizeSet(hdwf, c_int(8192)) 
dwf.FDwfAnalogInChannelEnableSet(hdwf, c_int(0), c_bool(True))
dwf.FDwfAnalogInChannelRangeSet(hdwf, c_int(0), c_double(5))

#set up trigger
dwf.FDwfAnalogInTriggerAutoTimeoutSet(hdwf, c_double(0)) #disable auto trigger
dwf.FDwfAnalogInTriggerSourceSet(hdwf, trigsrcDetectorAnalogIn) #one of the analog in channels
dwf.FDwfAnalogInTriggerTypeSet(hdwf, trigtypeEdge)
dwf.FDwfAnalogInTriggerChannelSet(hdwf, c_int(0)) # first channel
dwf.FDwfAnalogInTriggerLevelSet(hdwf, c_double(1.5)) # 1.5V
dwf.FDwfAnalogInTriggerConditionSet(hdwf, trigcondRisingPositive) 

# wait at least 2 seconds with Analog Discovery for the offset to stabilize, before the first reading after device open or offset/range change
time.sleep(2)

print "   starting repeated acquisitions"

# begin acquisition
dwf.FDwfAnalogInConfigure(hdwf, c_bool(False), c_bool(True))

for iTrigger in range(1,101):
    # new acquisition is started automatically after done state 

    while True:
        dwf.FDwfAnalogInStatus(hdwf, c_int(1), byref(sts))
        if sts.value == DwfStateDone.value :
            break
        time.sleep(0.001)
    
    dwf.FDwfAnalogInStatusData(hdwf, 0, rgdSamples, 8192)
    
    dc = sum(rgdSamples)/len(rgdSamples)
    print "Acquisition #"+str(iTrigger)+" average: "+str(dc)+"V"
    
dwf.FDwfDeviceCloseAll()


