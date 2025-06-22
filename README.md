# vsomeip-example

##### Overview
* sender:
* receiver: 
* subscriber: 
* notifier: 

##### Environment
* 2 VMWare host is set up in Bridged Mode 
  Ubuntu version: ubuntu-22.04.5-desktop-amd64.iso

#### Install essential tool
--`sudo apt update`
--`sudo apt install -y openssh-server net-tools  git screen netcat socat tcpdump`

#### Install Cmake, boost, vsomeip libraries
--`git clone https://github.com/minhthedt/vsomeip-example.git`
--`cd vsomeip-example/tool`
--`sudo ./install_vsomeip.sh`

#### Build vsomeip-example
--`cd vsomeip-example`
--`mkdir build`
--`cd build`
--`cmake ..`
--`make install`
