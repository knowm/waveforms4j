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

print "Generating sine wave..."
# enable two channels
dwf.FDwfAnalogOutNodeEnableSet(hdwf, c_int(0), AnalogOutNodeCarrier, c_int(True))
dwf.FDwfAnalogOutNodeEnableSet(hdwf, c_int(1), AnalogOutNodeCarrier, c_int(True))
# for second channel set master the first channel
dwf.FDwfAnalogOutMasterSet(hdwf, c_int(1), c_int(0));
# slave channel is controlled by the master channel
# it is enough to set trigger, wait, run and repeat paramters for master channel

# configure enabled channels
dwf.FDwfAnalogOutNodeFunctionSet(hdwf, c_int(-1), AnalogOutNodeCarrier, funcSine)
dwf.FDwfAnalogOutNodeFrequencySet(hdwf, c_int(-1), AnalogOutNodeCarrier, c_double(1000.0))
dwf.FDwfAnalogOutNodeAmplitudeSet(hdwf, c_int(-1), AnalogOutNodeCarrier, c_double(1.0))

#set phase for second channel
dwf.FDwfAnalogOutNodePhaseSet(hdwf, c_int(1), AnalogOutNodeCarrier, c_double(180.0))

print "Generating sine wave for 10 seconds..."
# start signal generation, 
# the second, slave channel will start too
dwf.FDwfAnalogOutConfigure(hdwf, c_int(0), c_bool(True))

time.sleep(10)

print "done."
dwf.FDwfDeviceClose(hdwf)
