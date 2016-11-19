"""
   DWF Python Example
   Author:  Digilent, Inc.
   Revision: 8/21/2014

   Requires:                       
       Python 2.7, numpy
       python-dateutil, pyparsing
"""
from ctypes import *
import math
import time
import sys

if sys.platform.startswith("win"):
    dwf = cdll.dwf
elif sys.platform.startswith("darwin"):
    dwf = cdll.LoadLibrary("/Library/Frameworks/dwf.framework/dwf")
else:
    dwf = cdll.LoadLibrary("libdwf.so")


#print DWF version
version = create_string_buffer(16)
dwf.FDwfGetVersion(version)
print "DWF Version: "+version.value

#open device
hdwf = c_int()
print "Opening first device"
dwf.FDwfDeviceOpen(c_int(-1), byref(hdwf))

if hdwf.value == 0:
    print "failed to open device"
    quit()

hzSys = c_double()
dwf.FDwfDigitalOutInternalClockInfo(hdwf, byref(hzSys))

# SPI parameters
CPOL = 0 # or 1
CPHA = 0 # or 1
hzFreq = 1e6
cBits = 16
rgdData = (2*c_byte)(*[0x12,0x34])

# serialization time length
dwf.FDwfDigitalOutRunSet(hdwf, c_double((cBits+0.5)/hzFreq))

# DIO 2 Select 
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(2), c_int(1))
# output high while DigitalOut not running
dwf.FDwfDigitalOutIdleSet(hdwf, c_int(2), c_int(2)) # 2=DwfDigitalOutIdleHigh
# output constant low while running
dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(2), c_int(0), c_int(0))
dwf.FDwfDigitalOutCounterSet(hdwf, c_int(2), c_int(0), c_int(0))

# DIO 1 Clock
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(1), c_int(1))
# set prescaler twice of SPI frequency
dwf.FDwfDigitalOutDividerSet(hdwf, c_int(1), c_int(int(hzSys.value/hzFreq/2)))
# 1 tick low, 1 tick high
dwf.FDwfDigitalOutCounterSet(hdwf, c_int(1), c_int(1), c_int(1))
# start with low or high based on clock polarity
dwf.FDwfDigitalOutCounterInitSet(hdwf, c_int(1), c_int(CPOL), c_int(1))
dwf.FDwfDigitalOutIdleSet(hdwf, c_int(1), c_int(1+CPOL)) # 1=DwfDigitalOutIdleLow 2=DwfDigitalOutIdleHigh

# DIO 0 Data
dwf.FDwfDigitalOutEnableSet(hdwf, c_int(0), 1)
dwf.FDwfDigitalOutTypeSet(hdwf, c_int(0), c_int(1)) # 1=DwfDigitalOutTypeCustom
# for high active clock, hold the first bit for 1.5 periods 
dwf.FDwfDigitalOutDividerInitSet(hdwf, c_int(0), c_int(int((1+0.5*CPHA)*hzSys.value/hzFreq))) 
# SPI frequency, bit frequency
dwf.FDwfDigitalOutDividerSet(hdwf, c_int(0), c_int(int(hzSys.value/hzFreq)))
# data sent out LSB first
dwf.FDwfDigitalOutDataSet(hdwf, c_int(0), byref(rgdData), c_int(cBits))


dwf.FDwfDigitalOutConfigure(hdwf, c_int(1))
print "Generating SPI signal"
time.sleep(1)

dwf.FDwfDigitalOutReset(hdwf);

dwf.FDwfDeviceCloseAll()
