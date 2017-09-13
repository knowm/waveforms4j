## What to Install on a Fresh System

### Waveforms4j

```
sudo apt-get update
sudo apt install git
mkdir Github
cd Github
git clone https://github.com/knowm/waveforms4j.git

```
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
    
### Java 8

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



