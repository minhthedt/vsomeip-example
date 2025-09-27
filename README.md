# 🚗 vsomeip-example

A basic example project demonstrating communication between services using **vsomeip**.

## 📘 Overview

This project includes the following roles:

- **Sender**: Sends service requests
- **Receiver**: Handles incoming requests
- **Subscriber**: Subscribes to event notifications
- **Notifier**: Sends out notifications to subscribers

## 🖥️ Environment

- Two [Virual Box](https://www.virtualbox.org/wiki/Downloads) Ubuntu hosts configured in **Bridged Mode**
- Ubuntu Version: [`ubuntu-22.04.5-desktop-amd64.iso`](https://releases.ubuntu.com/jammy/)

## ⬇️ Download & Install Prerequisites
#### Download vsomeip-example
```
# Install Essential Tools
sudo apt update
sudo apt install -y openssh-server screen git
sudo apt install -y net-tools netcat socat tcpdump

# Download example and install Cmake, boost, dlt, vsomeip
git clone https://github.com/minhthedt/vsomeip-example.git
cd vsomeip-example
sudo ./set_env.sh 2>&1 | tee log.txt
```
#### Build vsomeip-example
```bash
cd vsomeip-example
sudo ./build.sh
```
#### <h4 style="color:#0074D9">Verify Multicast (make sure 2 PC can send/receive multicast)</h4>
```
#(optional) all traffic destined for any multicast address (224.0.0.0/4) out through the enp0s3 network interface.
    ifconfig
    sudo ip route add 224.0.0.0/4 dev enp0s3 (alternative: sudo route add -net 224.0.0.0/4 dev enp0s3)
#show routing table
    netstat -rn

#sender
    echo "Hello multicast" | socat - UDP4-DATAGRAM:239.0.0.1:12345
#receiver
    socat -v UDP4-RECVFROM:12345,ip-add-membership=239.0.0.1:0.0.0.0,fork -
```

## 📝 Design Overview

#### 0) SOME/IP-SD
![SOME/IP-SD](doc/design/OverView.svg)

#### 1.0) request-sample
![1.0_request-sample](doc/design/1.0_request-sample.svg)

#### 1.1) response-sample
![1.1_response-sample](doc/design/1.1_response-sample.svg)

#### 2.0) subscribe-sample
![2.0_subscribe-sample](doc/design/2.0_subscribe-sample.svg)

#### 2.1) notify-sample
![2.1_notify-sample](doc/design/2.1_notify-sample.svg)

#### 3.0) OfferService Repetition Pattern
![OfferService_Repetition](doc/picture/OfferService_Repetition_Pattern.png)

#### 3.1) someip_udp_packet(offerservice)
![OfferService_Repetition](doc/picture/someip_udp_packet(offerservice).png)

#### 3.2) someip_tcp_packet(request_response)
![OfferService_Repetition](doc/picture/someip_tcp_packet(request_response).png)