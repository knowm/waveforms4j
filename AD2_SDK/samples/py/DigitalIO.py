"""
   DWF Python Example 8
   Author:  Digilent, Inc.
   Revision: 10/17/2013

   Requires:                       
       Python 2.7
"""

from ctypes import *
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
dwRead = c_uint32()

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
print "Opening first device"
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == hdwfNone.value:
    szerr = create_string_buffer(512)
    dwf.FDwfGetLastErrorMsg(szerr)
    print szerr.value
    print "failed to open device"
    quit()

print "Preparing to read Digital IO pins..."

# enable output/mask on 8 LSB IO pins, from DIO 0 to 7
dwf.FDwfDigitalIOOutputEnableSet(hdwf, c_int(0x00FF)) 
# set value on enabled IO pins
dwf.FDwfDigitalIOOutputSet(hdwf, c_int(0xFF)) 
# fetch digital IO information from the device 
dwf.FDwfDigitalIOStatus (hdwf) 
# read state of all pins, regardless of output enable
dwf.FDwfDigitalIOInputStatus(hdwf, byref(dwRead)) 

#print dwRead as bitfield (32 digits, removing 0b at the front)
print "Digital IO Pins:  " + bin(dwRead.value)[2:].zfill(32)

dwf.FDwfDeviceClose(hdwf)



