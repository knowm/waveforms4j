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

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
print "Opening first device"
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == hdwfNone.value:
    print "failed to open device"
    quit()

hzSys = c_double()
dwf.FDwfDigitalOutInternalClockInfo(hdwf, byref(hzSys))
print " internal frequency is " + str(hzSys.value)

# 100kHz counter rate, SystemFrequency/100kHz
cntFreq = c_uint(int(hzSys.value/1e5))

# generate counter
for i in range(0, 16):
    dwf.FDwfDigitalOutEnableSet(hdwf, c_int(i), c_int(1))
    # increase by 2 the period of successive bits
    dwf.FDwfDigitalOutDividerSet(hdwf, c_int(i), c_int(1<<i))
    dwf.FDwfDigitalOutCounterSet(hdwf, c_int(i), cntFreq, cntFreq)

dwf.FDwfDigitalOutConfigure(hdwf, c_int(1))

print "Generating binary counter for 10 seconds..."
time.sleep(10)

dwf.FDwfDeviceCloseAll()
