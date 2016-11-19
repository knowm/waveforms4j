"""
   DWF Python Example 6
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
sts = c_byte()
IsEnabled = c_bool()
supplyVoltage = c_double()
supplyCurrent = c_double()
supplyPower = c_double()
supplyLoadPercentage = c_double()

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
    
print "Preparing to read sample..."

#set up analog IO channel nodes
# enable positive supply
dwf.FDwfAnalogIOChannelNodeSet(hdwf, 0, 0, 1) 
# enable negative supply
dwf.FDwfAnalogIOChannelNodeSet(hdwf, 1, 0, 1) 
# master enable
dwf.FDwfAnalogIOEnableSet(hdwf, True) 

for i in range(1, 61):
  #wait 1 second between readings
  time.sleep(1)
  #fetch analogIO status from device
  dwf.FDwfAnalogIOStatus(hdwf)

  #supply monitor
  dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(3), c_int(0), byref(supplyVoltage))
  dwf.FDwfAnalogIOChannelNodeStatus(hdwf, c_int(3), c_int(1), byref(supplyCurrent))
  supplyPower.value = supplyVoltage.value * supplyCurrent.value
  print "Total supply power: " + str(supplyPower.value) + "W"

  supplyLoadPercentage.value = 100 * (supplyCurrent.value / 0.2)
  print"Load: " + str(supplyLoadPercentage.value) + "%"

  # in case of over-current condition the supplies are disabled
  dwf.FDwfAnalogIOEnableStatus(hdwf, byref(IsEnabled))
  if not IsEnabled:
    #re-enable supplies
    dwf.FDwfAnalogIOEnableSet(hdwf, c_bool(False)) 
    dwf.FDwfAnalogIOEnableSet(hdwf, c_bool(True))

#close the device
dwf.FDwfDeviceClose(hdwf)
