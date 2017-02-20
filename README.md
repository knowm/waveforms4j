# Introduction

This library is a Java implementation of the Digilent Waveforms AD2 SDK. A C++ and Python SDK is provided by Digilent, but no Java SDK existed. The entire API is not yet implemented and this project is a work in progress.

|OS | Progress |
|---|---|
|MacOS|Working|
|Linux|Working|
|Windows 10|Working|

This library should work for your Java-based Waveforms app by simply adding the jar to your app's classpath. However, if you need to add more API features that are not yet implemented, then the rest of this readme file explains how to do that.

# Pre-requisites for Development

Obviously Java is required on your platform, and instructions for that are not included here. This library was compiled with Java 8.

## Install DWF Framework on MacOS

Download Waveforms 2015 from [Digilent](https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start?redirect=1#newest) and open the DMG file, carrying on as usual. Move the `dwf.framework` to `/Library/Frameworks`, as indicated during the install of Waveforms from the DMG:

![](AD2_SDK/_img/Framework.png)

## Install DWF Framework on Linux

Get .deb files from here: <https://reference.digilentinc.com/reference/software/waveforms/waveforms-3>

    sudo mv ~/Downloads/digilent.waveforms_3.3.7_amd64.deb /var/cache/apt/archives
    cd /var/cache/apt/archives
    sudo dpkg -i digilent.waveforms_3.3.7_amd64.deb
    
    sudo mv ~/Downloads/digilent.adept.runtime_2.16.5-amd64.deb /var/cache/apt/archives
    cd /var/cache/apt/archives
    sudo dpkg -i digilent.adept.runtime_2.16.5-amd64.deb

## Install DWF Framework on Windows 10

Download Waveforms 2015 from [Digilent](https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start?redirect=1#newest) and launch it to run the installation wizard. This process will install the required frameworks.

## Accessing the AD2 SDK from Java

The SDK for the Digilent Analog Discovery 2 comes in the form of a compiled C++ framework. On Mac OSX, this comes in the form of a `*.framework` file, which is described above. On a Windows system, the SDK is a `.DLL`. In order to interact with the SDK with our Java app, we use Java JNI.

In single class called `DWF` is where our Java app code interacts with the SDK. DWF stands for `Digilent Waveform`. Note that in our `DWF` class, a static block is used to load the JNI library. We need to create this library manually and it's not provided By Digilent.

  static {
    try {
      if (OSUtils.isMac()) {
        NativeUtils.loadLibraryFromJar("/waveforms4j.dylib");
      }
      else if (OSUtils.isLinux()) {
          NativeUtils.loadLibraryFromJar("/waveforms4j.so");
      }
      else if (OSUtils.isWindows()) {
          NativeUtils.loadLibraryFromJar("/waveforms4j.dll");
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
    
The `waveforms4j.dylib`, `waveforms4j.so` and `waveforms4j.dll` file is something we need to create ourselves. This file is the JNI bridge between our Java code and Digilent's binary SDK.

## Compile Java Code and Generate Header File

Move to project directory
    
    cd ~/path/to/waveforms4j

Manually Compile All Java Classes (skip this if using Eclipse or IntelliJ)

    javac src/main/java/org/knowm/waveforms4j/*.java

Take the `native` methods we've defined in `DWF.java` and create a header file.

    // javah -jni -classpath src/main/java -d ./c org.knowm.waveforms4j.DWF
    javah -jni -classpath target/classes -d ./c org.knowm.waveforms4j.DWF

### Windows

    // "C:\Program Files\Java\jdk1.8.0_112\bin\javah" -jni -classpath src/main/java -d ./c org.knowm.waveforms4j.DWF
    "C:\Program Files\Java\jdk1.8.0_112\bin\javah" -jni -classpath target/classes -d ./c org.knowm.waveforms4j.DWF

Note: You need to take those methods created in the header file and implement them in the C++ file.

## Building the JNI Library

The following steps outline how to create the JNI library file and put it in the `resources` folder, which will get bundled with the deployable jar we build later with Maven. The final step is platform dependent, but the first steps are the same.

## MacOS

You need to find where the Java JNI Headers are located first and use it for the first two `-I` arguments:

    sudo find / -name "jni.h"
    find / -name jni_md.h 2> /dev/null

    gcc-6 -lstdc++ -shared ./c/org_knowm_waveforms4j_DWF.cpp -I/Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home/include -I/Library/Java/JavaVirtualMachines/jdk1.8.0_121.jdk/Contents/Home/include/darwin -F/Library/Frameworks/dwf.framework -framework dwf -o waveforms4j.dylib
    mv ./waveforms4j.dylib ./src/main/resources

## Linux

You need to find where the Java JNI Headers are located first and use it for the first two `-I` arguments:

    sudo find / -name "jni.h"
    find / -name jni_md.h 2> /dev/null

	cd ~/workspace/waveforms4j
    gcc -Wall -lstdc++ -fPIC -shared -o waveforms4j.so ./c/org_knowm_waveforms4j_DWF.cpp -I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux -L/usr/lib -ldwf
    mv ./waveforms4j.so ./src/main/resources

 
## Windows

You need to find where the Java JNI Headers are located first and use it for the first two `-I` arguments. This is usually somewhere such as: C:\Program Files\Java\jdk1.8.0_112.

You need to install a GCC compiler for Windows such as [Mingw-64](https://sourceforge.net/projects/mingw-w64/).

	cd C:\...\...\...\waveforms4j
	g++ -static -static-libgcc -static-libstdc++ -m64 -Wall -D_JNI_IMPLEMENTATION_ -I"C:\Program Files\Java\jdk1.8.0_121\include" -I"C:\Program Files\Java\jdk1.8.0_121\include\win32" -shared -o waveforms4j.dll ./c/org_knowm_waveforms4j_DWF.cpp -L"C:\Program Files\Digilent\WaveFormsSDK\lib\x64" -ldwf
    move ./waveforms4j.dll ./src/main/resources

See `Dev4Windows.md` for more details in setting up a Windows10 Dev environment.

## Test

A simple test to see if the JNI library works is to run `AnalogOutSine.java`. If you don't see any exception thrown, that means it's probably working.

## Some Resources

1. [Adept SDK Docs](https://reference.digilentinc.com/reference/software/adept/start?redirect=1id=digilent_adept_2#software_downloads)
1. [Waveforms 2015 Downloads](https://reference.digilentinc.com//reference/software/waveforms/waveforms-3/start?redirect=1id=waveforms3)
1. [Analog Discovery 2 Reference Manual](https://reference.digilentinc.com/analog_discovery_2/refmanual)
1. [Digilent's DWF library wrapper for python](https://github.com/amuramatsu/dwf)
1. [Waveforms3 Manual](https://reference.digilentinc.com/waveforms3/refmanual)

## Building the Jar

### general

    mvn clean package  
    mvn javadoc:javadoc  
    
Since we moved the JNI libs into `src/main/resources` in the above step, they are bundled in the jar.

### maven-license-plugin

    mvn license:check
    mvn license:format
    mvn license:remove
    
### Getting the Jar

The waveforms4j release artifacts are hosted on [Maven Central](https://search.maven.org/#search%7Cga%7C1%7Cg%3A%22org.knowm.waveforms4j%22).

Or if you use Maven, add the following to your pom file:

```xml
<dependency>
    <groupId>org.knowm</groupId>
    <artifactId>waveforms4j</artifactId>
    <version>0.0.5</version>
</dependency>
```
For snapshots, add the following to your pom.xml file:
```xml
<repository>
  <id>sonatype-oss-snapshot</id>
  <snapshots/>
  <url>https://oss.sonatype.org/content/repositories/snapshots</url>
</repository>

<dependency>
    <groupId>org.knowm</groupId>
    <artifactId>waveforms4j</artifactId>
    <version>0.0.6-SNAPHOT</version>
</dependency>
```
