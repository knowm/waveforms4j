## What to Install on a Fresh System

1. `sudo apt install git`, `mkdir Github`, `cd Github`, `git clone https://github.com/knowm/waveforms4j.git`
1. Gitcola - install through Discover App
1. Java 11 SDK
1. [Waveforms](https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start)
1. Eclipse - download installer and extract zip file from eclipse.org. 


## Install DWF Framework on Linux

Download .deb files from here: <https://reference.digilentinc.com/reference/software/waveforms/waveforms-3/start>

```
sudo mv ~/Downloads/digilent.adept.runtime_2.16.6-amd64.deb /var/cache/apt/archives
cd /var/cache/apt/archives
sudo dpkg -i digilent.adept.runtime_2.16.6-amd64.deb

sudo mv ~/Downloads/digilent.waveforms_3.6.8_amd64.deb /var/cache/apt/archives
cd /var/cache/apt/archives
sudo dpkg -i digilent.waveforms_3.6.8_amd64.deb
```
    
### Java 11

As of 30.01.2019, Ubuntu 10.04 LTS doesn't upgrade to Java 11, so we do it manually. Otherwise we could do it with `sudo apt-get install default-jdk` if it wasn't already on Java 11. 

Download .deb files from here: <https://packages.ubuntu.com/cosmic/amd64/openjdk-11-jdk/download>


```
sudo add-apt-repository -y ppa:webupd8team/java
sudo apt-get update
echo debconf shared/accepted-oracle-license-v1-1 select true | sudo debconf-set-selections
echo debconf shared/accepted-oracle-license-v1-1 seen true | sudo debconf-set-selections
sudo apt-get -y install oracle-java8-installer
java -version
```

### Eclipse

[linux Download](https://www.eclipse.org/downloads/eclipse-packages/?show_instructions=TRUE)

Extract to home directory and double-click `eclipse-inst`. 

### C++ Build Tools

gcc: error trying to exec 'cc1plus': execvp: No such file or directory

sudo apt-get update
sudo apt-get install --reinstall build-essential

### Push Changes



