"""
   DWF Python Example
   Author:  Digilent, Inc.
   Revision: 1/11/2016

   Requires:                       
       Python 2.7, numpy, matplotlib
       python-dateutil, pyparsing
"""
from ctypes import *
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
hzAcq = c_double(100)
nSamples = 1000
rgdSamples = (c_double*nSamples)()
cValid = c_int(0)

print "nSamples:  " + str(nSamples)
print "rgdSamples:  " + str(len(rgdSamples))

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
print "Opening first device"
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == 0:
    szerr = create_string_buffer(512)
    dwf.FDwfGetLastErrorMsg(szerr)
    print szerr.value
    print "failed to open device"
    quit()

print "Preparing to read sample..."

print "Generating sine wave..."
dwf.FDwfAnalogOutNodeEnableSet(hdwf, c_int(0), c_int(0), c_bool(True))
dwf.FDwfAnalogOutNodeFunctionSet(hdwf, c_int(0), c_int(0), c_int(1)) #sine
dwf.FDwfAnalogOutNodeFrequencySet(hdwf, c_int(0), c_int(0), c_double(1))
dwf.FDwfAnalogOutNodeAmplitudeSet(hdwf, c_int(0), c_int(0), c_double(2))
dwf.FDwfAnalogOutConfigure(hdwf, c_int(0), c_bool(True))

#set up acquisition
dwf.FDwfAnalogInChannelEnableSet(hdwf, c_int(0), c_bool(True))
dwf.FDwfAnalogInChannelRangeSet(hdwf, c_int(0), c_double(5))
dwf.FDwfAnalogInAcquisitionModeSet(hdwf, c_int(1)) #acqmodeScanShift
dwf.FDwfAnalogInFrequencySet(hdwf, hzAcq)
dwf.FDwfAnalogInBufferSizeSet(hdwf, c_int(nSamples))

#wait at least 2 seconds for the offset to stabilize
time.sleep(2)

#begin acquisition
dwf.FDwfAnalogInConfigure(hdwf, c_int(0), c_int(1))

plt.axis([0, len(rgdSamples), -2.5, 2.5])
plt.ion()
hl, = plt.plot([], [])
hl.set_xdata(range(0,len(rgdSamples)))

while True:
    dwf.FDwfAnalogInStatus(hdwf, c_int(1), byref(sts))

    dwf.FDwfAnalogInStatusSamplesValid(hdwf, byref(cValid))

    # get samples
    dwf.FDwfAnalogInStatusData(hdwf, c_int(0), byref(rgdSamples), cValid)
    print cValid.value
    rgpy=[0.0]*len(rgdSamples)
    for i in range(0,cValid.value):
        rgpy[i]=rgdSamples[i]
    hl.set_ydata(rgdSamples)
    plt.draw()
    plt.pause(0.01)

