This `AD2_SDK` folder contains the SDK from Digilent and is mostly here just for reference for the Java implementation.

1. [Adept SDK Docs](https://reference.digilentinc.com/reference/software/adept/start?redirect=1id=digilent_adept_2#software_downloads)
1. [Waveforms 2015 Downloads](https://reference.digilentinc.com//reference/software/waveforms/waveforms-3/start?redirect=1id=waveforms3)
1. [Analog Discovery 2 Reference Manual](https://reference.digilentinc.com/analog_discovery_2/refmanual)
1. [Digilent's DWF library wrapper for python](https://github.com/amuramatsu/dwf)
1. [Waveforms3 Manual](https://reference.digilentinc.com/waveforms3/refmanual)


## Prepare SDK for Development on Mac

Move the dwf.framework to `/Library/Frameworks`, as indicated during the install of Waveforms from the DMG:

![](_img/Framework.png)

## Python

The easiest thing to try out first is running one of the Python scripts:

    brew install python
    pip install matplotlib
    cd ~/workspaces/workspace_knowm/memristor-dev/AD2_SDK/samples/py
    python DigitalOut_Pins.py

You should see something like this:

    DWF Version: 3.3.5
    Opening first device
    Generating for 10 seconds...
    Generating for 10 seconds...
    Generating for 10 seconds...

## C++

    brew install homebrew/versions/gcc6
    cd ~/workspaces/workspace_knowm/memristor-dev/AD2_SDK/samples/c

    gcc-6 digitalout_pins.cpp -o digitalout_pins.out -I/Library/Frameworks/dwf.framework -framework dwf
    ./digitalout_pins.out

    gcc-6 analogout_sine.cpp -o analogout_sine.out -I/Library/Frameworks/dwf.framework -framework dwf
    ./analogout_sine.out

    gcc-6 analogio_analogdiscovery2_power.cpp -o analogio_analogdiscovery2_power.out -I/Library/Frameworks/dwf.framework -framework dwf
    ./analogio_analogdiscovery2_power.out


    cpp digitalout_walking1.cpp -I/Library/Frameworks/dwf.framework/dwf -framework dwf
    cpp digitalout_walking1.cpp -I/Library/Frameworks/dwf.framework/Versions/A/Headers -L/Library/Frameworks/dwf.framework/Versions/A/Libraries -framework dwf
    gcc digitalout_walking1.cpp -ldwf
    /usr/local/Cellar/gcc6 digitalout_walking1.cpp -ldwf

