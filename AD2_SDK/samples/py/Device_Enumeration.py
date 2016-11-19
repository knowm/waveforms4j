"""
   DWF Python Example 1
   Author:  Digilent, Inc.
   Revision:  10/17/2013

   Requires:                       
       Python 2.7
"""

from ctypes import *
import sys

if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
    dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
else:
    dwf = cdll.LoadLibrary("libdwf.so")

#check library loading errors, like: Adept Runtime not found
szerr = create_string_buffer(512)
dwf.FDwfGetLastErrorMsg(szerr)
print szerr.value

#declare ctype variables
IsInUse = c_bool()
hdwf = c_int()
channel = c_int()
hzfreq = c_double()
cdevices = c_int()

#declare string variables
devicename = create_string_buffer(64)
serialnum = create_string_buffer(16)

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#enumerate and print device information
dwf.FDwfEnum(c_int(0), byref(cdevices))
print "Number of Devices: "+str(cdevices.value)

for i in range(0, cdevices.value):
    dwf.FDwfEnumDeviceName (c_int(i), devicename)
    dwf.FDwfEnumSN (c_int(i), serialnum)
    print "------------------------------"
    print "Device "+str(i)+" : "
    print "\t" + devicename.value
    print "\t" + serialnum.value
    dwf.FDwfEnumDeviceIsOpened(c_int(i), byref(IsInUse))

    if not IsInUse:
        dwf.FDwfDeviceOpen(c_int(i), byref(hdwf))
        if hdwf.value == 0:
            szerr = create_string_buffer(512)
            dwf.FDwfGetLastErrorMsg(szerr)
            print szerr.value
        else:
            dwf.FDwfAnalogInChannelCount(hdwf, byref(channel))
            dwf.FDwfAnalogInFrequencyInfo(hdwf, None, byref(hzfreq))
            print "\tAnalog input channels: "+str(channel.value)
            print "\tMax freq: "+str(hzfreq.value)
            dwf.FDwfDeviceClose(hdwf)
            hdwf = c_int(-1)

# ensure all devices are closed
dwf.FDwfDeviceCloseAll()
