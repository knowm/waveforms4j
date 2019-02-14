## What to Install on a Fresh System

1. Java 11 SDK - see below
1. IntelliJ - see below
1. Waveforms - see below
1. Git - use the git tool in IntelliJ
1. Maven - use the maven plugin in IntelliJ (Maven Helper)

### Java 11

As of 30.01.2019, Ubuntu 10.04 LTS doesn't upgrade to Java 11, so we do it manually. Otherwise we could do it with `sudo apt-get install default-jdk` if it wasn't already on Java 11. 

Download OpenJDK from [here](https://jdk.java.net/11/)

```
sudo apt-get remove openjdk-*
sudo apt-get purge openjdk-*
sudo apt autoremove

cd /usr/lib
mkdir jdk
cd jdk
sudo tar -xvzf ~/Downloads/openjdk-11.0.2_linux-x64_bin.tar.gz
nano ~/.bashrc
```

Add to bottom of fine:

```
export JAVA_HOME=/usr/lib/jdk/jdk-11.0.2
export PATH=$PATH:$JAVA_HOME/bin
```

Restart Console.

```
java -version
```

### IntelliJ

Install from Software Center. Search for "Idea". It's packaged as a "snap".

The following did not work. I could not accept the privacy policy as the accept button was greyed out.

[Download for Linux](https://www.jetbrains.com/idea/download/index.html#section=linux) and extract zip file from eclipse.org.

```
cd /opt
sudo tar -xvzf ~/Downloads/ideaIC-2018.3.4-no-jdk.tar.gz
cd /opt/idea-IC-183.5429.30/bin
./idea.sh
```

## Install DWF Framework on Linux

Get .deb files from here: <https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start>

```  
sudo mv ~/Downloads/digilent.adept.runtime_2.19.2-amd64.deb /var/cache/apt/archives
cd /var/cache/apt/archives
sudo dpkg -i digilent.adept.runtime_2.19.2-amd64.deb

sudo mv ~/Downloads/digilent.waveforms_3.9.1_amd64.deb /var/cache/apt/archives
cd /var/cache/apt/archives
sudo dpkg -i digilent.waveforms_3.9.1_amd64.deb
```

## Compile Java Code and Generate Header File

Move to project directory
    
    cd ~/path/to/waveforms4j

Manually Compile All Java Classes (skip this if using Eclipse or IntelliJ)

    javac src/main/java/org/knowm/waveforms4j/*.java

Take the `native` methods we've defined in `DWF.java` and create a header file.

```
javac -cp ./src/main/java:/home/tim/.m2/repository/org/slf4j/slf4j-api/1.7.25/slf4j-api-1.7.25.jar -h ./c src/main/java/org/knowm/waveforms4j/DWF.java
```
Note: You need to take those methods created in the header file and implement them in the C++ file.

## Building the JNI Library

The following steps outline how to create the JNI library file and put it in the `resources` folder, which will get bundled with the deployable jar we build later with Maven. The final step is platform dependent, but the first steps are the same.

## Linux

You need to find where the Java JNI Headers are located first and use it for the first two `-I` arguments:

```
sudo find / -name "jni.h"
find / -name jni_md.h 2> /dev/null
cd ~/Github/waveforms4j/
gcc -Wall -lstdc++ -fPIC -shared -o waveforms4j.so ./c/org_knowm_waveforms4j_DWF.cpp -I/usr/lib/jvm/jdk-11.0.2/include -I/usr/lib/jvm/jdk-11.0.2/include/linux -L/usr/lib -ldwf
mv ./waveforms4j.so ./src/main/resources
```
 













### C++ Build Tools

gcc: error trying to exec 'cc1plus': execvp: No such file or directory

sudo apt-get update
sudo apt-get install --reinstall build-essential

### Push Changes

Use Git Cola or the git tools in Eclipse.

