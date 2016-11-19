"""
   DWF Python Example 
   Author:  Digilent, Inc.
   Revision: 04/20/2015

   Requires:                       
       Python 2.7, numpy, 
"""
from ctypes import *
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

#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
print "Opening first device"
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == 0:
    print "failed to open device"
    quit()


# 2 pin phase start low and high
for i in range(0, 2):
    dwf.FDwfDigitalOutEnableSet(hdwf, c_int(i), c_int(1))
    dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(i), c_uint(i==1), c_uint(50)) 
    dwf.FDwfDigitalOutCounterSet(hdwf, c_int(i), c_uint(50), c_uint(50)) # 100MHz base freq /(50+50) = 1MHz

dwf.FDwfDigitalOutConfigure(hdwf, c_int(1))
print "Generating for 10 seconds..."
time.sleep(10)


# 3 pin phase
dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(0), c_uint(1), c_uint(0))
dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(1), c_uint(0), c_uint(20))
dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(2), c_uint(1), c_uint(10))
for i in range(0, 3):
    dwf.FDwfDigitalOutEnableSet(hdwf, c_int(i), c_int(1))
    dwf.FDwfDigitalOutCounterSet(hdwf, c_int(i), c_uint(30), c_uint(30)) # 100MHz base freq /(30+30) = 1.67 MHz

dwf.FDwfDigitalOutConfigure(hdwf, c_int(1))
print "Generating for 10 seconds..."
time.sleep(10)


# 4 pin phase starting: low & 25, low $ 50, high & 25, high & 50 
for i in range(0, 4):
    dwf.FDwfDigitalOutEnableSet(hdwf, c_int(i), c_int(1))
    dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(i), c_uint((i==2) or (i==3)), c_uint(25 if (i==0 or i==2) else 50))
    dwf.FDwfDigitalOutCounterSet(hdwf, c_int(i), c_uint(50), c_uint(50)) 

dwf.FDwfDigitalOutConfigure(hdwf, c_int(1))
print "Generating for 10 seconds..."
time.sleep(10)

dwf.FDwfDeviceCloseAll()
