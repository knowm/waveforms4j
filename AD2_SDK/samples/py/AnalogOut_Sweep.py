"""
   DWF Python Example 2
   Author:  Digilent, Inc.
   Revision: 10/17/2013

   Requires:                       
       Python 2.7
"""

from ctypes import *
import time
from dwfconstants import *
import sys

if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
    dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
else:
    dwf = cdll.LoadLibrary("libdwf.so")

#declare ctype variables
hdwf = c_int()
channel = c_int(0)

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
print "Opening first device..."
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == hdwfNone.value:
    print "failed to open device"
    quit()

hzStart = c_double(1e3)
hzStop = c_double(1e5)
secSweep = c_double(1)

print "Generating sine wave..."
dwf.FDwfAnalogOutNodeEnableSet(hdwf, channel, AnalogOutNodeCarrier, c_bool(True))
dwf.FDwfAnalogOutNodeFunctionSet(hdwf, channel, AnalogOutNodeCarrier, funcSine)
dwf.FDwfAnalogOutNodeFrequencySet(hdwf, channel, AnalogOutNodeCarrier, c_double(10000))
dwf.FDwfAnalogOutNodeAmplitudeSet(hdwf, channel, AnalogOutNodeCarrier, c_double(1))
dwf.FDwfAnalogOutNodeOffsetSet(hdwf, channel, AnalogOutNodeCarrier, c_double(1))

dwf.FDwfAnalogOutNodeEnableSet(hdwf, channel, AnalogOutNodeFM, c_bool(True))
dwf.FDwfAnalogOutNodeFunctionSet(hdwf, channel, AnalogOutNodeFM, funcRampUp)
dwf.FDwfAnalogOutNodeFrequencySet(hdwf, channel, AnalogOutNodeFM, c_double(10000))
dwf.FDwfAnalogOutNodeAmplitudeSet(hdwf, channel, AnalogOutNodeFM, c_double(1))
dwf.FDwfAnalogOutNodeOffsetSet(hdwf, channel, AnalogOutNodeFM, c_double(1))

print "Play sine wave for 10 seconds..."
dwf.FDwfAnalogOutConfigure(hdwf, channel, c_bool(True))
time.sleep(10)
print "done."
dwf.FDwfDeviceClose(hdwf)
