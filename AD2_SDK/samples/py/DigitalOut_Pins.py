"""
   DWF Python Example
   Author:  Digilent, Inc.
   Revision: 8/21/2014

   Requires:                       
       Python 2.7, numpy
       python-dateutil, pyparsing
"""
from ctypes import *
from dwfconstants import *
import math
import time
import sys

print "sys.platform: "+sys.platform


if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
#    dwf = cdll.LoadLibrary("/Applications/WaveForms.app/Contents/Frameworks/dwf.framework/Versions/A/dwf")
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

# 1kHz pulse on IO pin 0
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(0), c_int(1))
# prescaler to 2kHz, SystemFrequency/1kHz/2
dwf.FDwfDigitalOutDividerSet(hdwf, c_int(0), c_int(int(hzSys.value/1e3/2)))
# 1 tick low, 1 tick high
dwf.FDwfDigitalOutCounterSet(hdwf, c_int(0), c_int(1), c_int(1))

# 1kHz 25% duty pulse on IO pin 1
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(1), c_int(1))
# prescaler to 4kHz SystemFrequency/1kHz/2
dwf.FDwfDigitalOutDividerSet(hdwf, c_int(1), c_int(int(hzSys.value/1e3/4)))
# 3 ticks low, 1 tick high
dwf.FDwfDigitalOutCounterSet(hdwf, c_int(1), c_int(3), c_int(1))

# 2kHz random on IO pin 2
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(2), c_int(1))
dwf.FDwfDigitalOutTypeSet(hdwf, c_int(2), DwfDigitalOutTypeRandom)
dwf.FDwfDigitalOutDividerSet(hdwf, c_int(2), c_int(int(hzSys.value/2e3)))

rgdSamples = (c_byte*4)(*[0x00,0xAA,0x66,0xFF])
# 1kHz sample rate custom on IO pin 3
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(3), 1)
dwf.FDwfDigitalOutTypeSet(hdwf, c_int(3), DwfDigitalOutTypeCustom)
dwf.FDwfDigitalOutDividerSet(hdwf, c_int(3), c_int(int(hzSys.value/1e3)))
dwf.FDwfDigitalOutDataSet(hdwf, c_int(3), byref(rgdSamples), c_int(4*8))

dwf.FDwfDigitalOutConfigure(hdwf, c_int(1))

print "Generating output counter for 10 seconds..."
time.sleep(10)

dwf.FDwfDigitalOutReset(hdwf);

dwf.FDwfDeviceCloseAll()
