"""
   DWF Python Example
   Author:  Digilent, Inc.
   Revision: 12/28/2015

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
sts = c_byte()
IsEnabled = c_bool()
usbVoltage = c_double()
usbCurrent = c_double()
auxVoltage = c_double()
auxCurrent = c_double()

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

# set up analog IO channel nodes
# enable positive supply
dwf.FDwfAnalogIOChannelNodeSet(hdwf, c_int(0), c_int(0), c_double(True)) 
# set voltage to 5 V
dwf.FDwfAnalogIOChannelNodeSet(hdwf, c_int(0), c_int(1), c_double(5.0)) 
# enable negative supply
dwf.FDwfAnalogIOChannelNodeSet(hdwf, c_int(1), c_int(0), c_double(True)) 
# set voltage to -5 V
dwf.FDwfAnalogIOChannelNodeSet(hdwf, c_int(1), c_int(1), c_double(-5.0)) 
# master enable
dwf.FDwfAnalogIOEnableSet(hdwf, c_int(True))

for i in range(1, 61):
    #wait 1 second between readings
    time.sleep(1)
    #fetch analogIO status from device
    if dwf.FDwfAnalogIOStatus(hdwf) == 0:
        break

    #supply monitor
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(2), c_int(0), byref(usbVoltage))
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(2), c_int(1), byref(usbCurrent))
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(3), c_int(0), byref(auxVoltage))
    dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(3), c_int(1), byref(auxCurrent))
    print "USB: " + str(round(usbVoltage.value,3)) + "V\t" + str(round(usbCurrent.value,3)) + "A"
    print "AUX: " + str(round(auxVoltage.value,3)) + "V\t" + str(round(auxCurrent.value,3)) + "A"

    # in case of over-current condition the supplies are disabled
    dwf.FDwfAnalogIOEnableStatus(hdwf, byref(IsEnabled))
    if not IsEnabled:
        #re-enable supplies
        print "Restart"
        dwf.FDwfAnalogIOEnableSet(hdwf, c_int(False)) 
        dwf.FDwfAnalogIOEnableSet(hdwf, c_int(True))

#close the device
dwf.FDwfDeviceClose(hdwf)
