## What to Install on a Fresh System

1. [Java 11 SDK](https://stackoverflow.com/a/52531093/1625820)
1. [IntelliJ](https://www.jetbrains.com/idea/download/index.html#section=windows)
1. [Mingw-w64](https://stackoverflow.com/a/60212467)
1. [Waveforms](https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start)

## Install DWF Framework on Windows 10

Download Waveforms from [Digilent](https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start?redirect=1#newest) and launch it to run the installation wizard. This process will install the required frameworks.

## First Sanity Check - Waveforms

After downloading and installing Waveforms, open it up and make sure it connects to the AD2 device and operates as expected.

## Second Sanity Check - Compile and Run SDK Example

Unzip Mingw64 and move 'mingw64' to 'C:\' and add 'C:\mingw64\bin' to your PATH environment variable via the Windows Settings GUI. Open up the terminal with 'CMD'.

Change permissions on `cd C:\Program Files\Digilent\WaveFormsSDK\samples\c` via the GUI so that the gcc command can write the *.out file in that folder.
Open up the terminal with 'cmd'.

    cd C:\Program Files (x86)\Digilent\WaveFormsSDK\samples\c
    // gcc digitalout_pins.cpp -o digitalout_pins.out -L"C:\Windows\System32" -ldwf
    gcc digitalout_pins.cpp -o digitalout_pins.out -L"C:\Program Files (x86)\Digilent\WaveFormsSDK\lib\x64" -ldwf
    digitalout_pins.out

## Compile Java Code and Generate Header File

Move to project directory
    
    cd ~/path/to/waveforms4j

Manually Compile All Java Classes (skip this if using Eclipse or IntelliJ)

    javac src/main/java/org/knowm/waveforms4j/*.java

Take the `native` methods we've defined in `DWF.java` and create a header file.

```
// javah -jni -classpath src/main/java -d ./c org.knowm.waveforms4j.DWF
javah -jni -classpath target/classes -d ./c org.knowm.waveforms4j.DWF
```

```
"C:\Program Files\Java\jdk1.8.0_112\bin\javah" -jni -classpath target/classes -d ./c org.knowm.waveforms4j.DWF
```

Note: You need to take those methods created in the header file and implement them in the C++ file.

## Build Waveforms4J DLL for JNI

You need to find where the Java JNI Headers are located first and use it for the first two `-I` arguments. This is usually somewhere such as: C:\Program Files\Java\jdk1.8.0_112.

```
cd C:\Users\knowm\Documents\GitHub\waveforms4j
g++ -static -static-libgcc -static-libstdc++ -m64 -Wall -D_JNI_IMPLEMENTATION_ -I"C:\Program Files\Java\jdk-11.0.2\include" -I"C:\Program Files\Java\jdk-11.0.2\include\win32" -shared -o waveforms4j.dll ./c/org_knowm_waveforms4j_DWF.cpp -L"C:\Program Files (x86)\Digilent\WaveFormsSDK\lib\x64" -ldwf
move ./waveforms4j.dll ./src/main/resources
```
Note: the key to solving the UnsatifiedLinkError was here: <http://stackoverflow.com/questions/18138635/mingw-exe-requires-a-few-gcc-dlls-regardless-of-the-code>.

I used the program Dependency Walker to figure out that the waveforms4j dll depended on `libstdc++-6.dll` and it could not link it during run time. The `-static -static-libgcc -static-libstdc++` options link it statically during compilation.

## Building the JNI Library

The following steps outline how to create the JNI library file and put it in the `resources` folder, which will get bundled with the deployable jar we build later with Maven. The final step is platform dependent, but the first steps are the same.


## Useful Commands (Run in GitBash or Terminal in IntelliJ)

cd /c/Users/knowm/Downloads/Memristor-Discovery/Memristor-Discovery
"C:\Program Files\Java\jdk-11.0.2\bin\java.exe" -jar memristor-discovery-0.0.7.jar

"C:\Program Files\Java\jdk-11.0.2\bin\java.exe" -jar C:/Users/knowm/Documents/GitHub/memristor-discovery/target/memristor-discovery-0.0.8-SNAPSHOT.jar

https://medium.com/azulsystems/using-jlink-to-build-java-runtimes-for-non-modular-applications-9568c5e70ef4