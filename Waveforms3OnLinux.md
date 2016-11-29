## Install Waveforms

Get .deb files from here: <https://reference.digilentinc.com/reference/software/waveforms/waveforms-3>

	sudo mv ~/Downloads/digilent.waveforms_3.3.7_amd64.deb /var/cache/apt/archives
	cd /var/cache/apt/archives
	sudo dpkg -i digilent.waveforms_3.3.7_amd64.deb
	
	sudo mv ~/Downloads/digilent.adept.runtime_2.16.5-amd64.deb /var/cache/apt/archives
	cd /var/cache/apt/archives
	sudo dpkg -i digilent.adept.runtime_2.16.5-amd64.deb
	
## Some Useful Commands
    
    nano /etc/digilent-adept.conf
    /usr/share/digilent