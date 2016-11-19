"""
   DWF Python Example 7
   Author:  Digilent, Inc.
   Revision: 10/17/2013

   Requires:                       
       Python 2.7
"""

from ctypes import *
from dwfconstants import *
import time
import sys

if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
    dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
else:
    dwf = cdll.LoadLibrary("libdwf.so")

#declare ctype variables
hdwf = c_int()
deviceVoltage = c_double()
deviceCurrent = c_double()
deviceTemperature = c_double()


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

print "Device USB supply voltage, current and device temperature:"
#monitor voltage, current, temperature
#60 times, once per second
for i in range(1, 61):
    # wait between readings; the update rate is approximately 1Hz
    time.sleep(1)
    # fetch analog IO status from device
    dwf.FDwfAnalogIOStatus(hdwf)
    # get system monitor readings
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(2), c_int(0), byref(deviceVoltage))
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(2), c_int(1), byref(deviceCurrent))
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(2), c_int(2), byref(deviceTemperature))
    print str(deviceVoltage.value) + " V\t" + str(deviceCurrent.value) + " A\t " + str(deviceTemperature.value) + "degC"
    
#close the device
dwf.FDwfDeviceClose(hdwf)
