# Introduction

This library is a Java implementation of the Digilent Waveforms AD2 SDK. A C++ and Python SDK is provided by Digilent, but no Java SDK existed. The entire API is not yet implemented and this project is a work in progress.

|OS | Progress |
|---|---|
|MacOS|Working|
|Linux|Working|
|Windows 10|Working|

This library should work for your Java-based Waveforms app by simply adding the jar to your app's classpath. However, if you need to add more API features that are not yet implemented, then the rest of this readme file explains how to do that.

# Pre-requisites for Development

See separate instructions for different operating systems.

## Accessing the AD2 SDK from Java

The SDK for the Digilent Analog Discovery 2 comes in the form of a compiled C++ framework. On Mac OSX, this comes in the form of a `*.framework` file, which is described above. On a Windows system, the SDK is a `.DLL`. In order to interact with the SDK with our Java app, we use Java JNI.

In single class called `DWF` is where our Java app code interacts with the SDK. DWF stands for `Digilent Waveform`. Note that in our `DWF` class, a static block is used to load the JNI library. We need to create this library manually and it's not provided By Digilent.

```
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
```
    
The `waveforms4j.dylib`, `waveforms4j.so` and `waveforms4j.dll` file is something we need to create ourselves. This file is the JNI bridge between our Java code and Digilent's binary SDK.

## Test

A simple test to see if the JNI library works is to run `AnalogOutSine.java`. If you don't see any exception thrown, that means it's probably working.

## Some Resources

1. [Adept SDK Docs](https://reference.digilentinc.com/reference/software/adept/start?redirect=1id=digilent_adept_2#software_downloads)
1. [Waveforms Downloads](https://reference.digilentinc.com//reference/software/waveforms/waveforms-3/start?redirect=1id=waveforms3)
1. [Analog Discovery 2 Reference Manual](https://reference.digilentinc.com/analog_discovery_2/refmanual)
1. [Digilent's DWF library wrapper for python](https://github.com/amuramatsu/dwf)
1. [Waveforms3 Manual](https://reference.digilentinc.com/waveforms3/refmanual)

## Building the Jar

### general

    mvn clean package
    mvn clean install  
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
    <version>0.0.10</version>
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
    <version>0.0.11-SNAPHOT</version>
</dependency>
```
