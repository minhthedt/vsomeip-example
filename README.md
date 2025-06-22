# 🚗 vsomeip-example

A basic example project demonstrating communication between services using **vsomeip**.

## 📘 Overview

This project includes the following roles:

- **Sender**: Sends service requests
- **Receiver**: Handles incoming requests
- **Subscriber**: Subscribes to event notifications
- **Notifier**: Sends out notifications to subscribers

## 🖥️ Environment

- Two VMWare Ubuntu hosts configured in **Bridged Mode**
- OS Version: `ubuntu-22.04.5-desktop-amd64.iso`

## 🔧 Install Essential Tools

Install base utilities and networking tools:
```bash
sudo apt update
sudo apt install -y openssh-server screen git
sudo apt install -y net-tools netcat socat tcpdump
sudo apt install dlt-daemon libdlt-dev dlt-tools
```

#### Install Cmake, boost, vsomeip libraries
```bash
git clone https://github.com/minhthedt/vsomeip-example.git
cd vsomeip-example/tool
sudo ./install_vsomeip.sh
```
#### Build vsomeip-example
```bash
cd vsomeip-example
mkdir build
cd build
cmake ..
make install
```