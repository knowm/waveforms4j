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
import matplotlib.pyplot as plt

if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
    dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
else:
    dwf = cdll.LoadLibrary("libdwf.so")

#declare ctype variables
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "Version: "+version.value

cdevices = c_int()
dwf.FDwfEnum(c_int(0), byref(cdevices))
print "Number of Devices: "+str(cdevices.value)

if cdevices.value == 0:
    print "no device detected"
    quit()

print "Opening first device"
hdwf = c_int()
dwf.FDwfDeviceOpen(c_int(0), byref(hdwf))

if hdwf.value == hdwfNone.value:
    print "failed to open device"
    quit()

print "Configure and start first analog out channel"
dwf.FDwfAnalogOutEnableSet(hdwf, c_int(0), c_int(1))
print "1 = Sine wave"
dwf.FDwfAnalogOutFunctionSet(hdwf, c_int(0), c_int(1))
dwf.FDwfAnalogOutFrequencySet(hdwf, c_int(0), c_double(3000))
print ""
dwf.FDwfAnalogOutConfigure(hdwf, c_int(0), c_int(1))

print "Configure analog in"
dwf.FDwfAnalogInFrequencySet(hdwf, c_double(1000000))
print "Set range for all channels"
dwf.FDwfAnalogInChannelRangeSet(hdwf, c_int(-1), c_double(4))
dwf.FDwfAnalogInBufferSizeSet(hdwf, c_int(1000))

print "Wait after first device opening the analog in offset to stabilize"
time.sleep(2)

print "Starting acquisition"
dwf.FDwfAnalogInConfigure(hdwf, c_int(1), c_int(1))

print "   waiting to finish"
sts = c_int()
while True:
    dwf.FDwfAnalogInStatus(hdwf, c_int(1), byref(sts))
    if sts.value == DwfStateDone.value :
        break
    time.sleep(0.1)
print "   done"


print "   reading data"
rg = (c_double*1000)()
dwf.FDwfAnalogInStatusData(hdwf, c_int(0), rg, len(rg))

dwf.FDwfDeviceCloseAll()

dc = sum(rg)/len(rg)
print "DC: "+str(dc)+"V"


rgpy=[0.0]*len(rg)
for i in range(0,len(rgpy)):
    rgpy[i]=rg[i]

plt.plot(rgpy)
plt.show()

