#!/bin/bash
#https://github.com/COVESA/capicxx-core-runtime
#https://github.com/COVESA/capicxx-someip-runtime

# Variables
INSTALL_DIR="/usr/local"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
set -e

cd "$SCRIPT_DIR"
if [ ! -d "download" ]; then
    sudo mkdir download
fi
cd download

#Clean all exist lib
sudo rm -f /usr/local/lib/libCommonAPI*
sudo rm -rf /usr/local/lib/cmake/CommonAPI*
sudo ldconfig
#ldd ./bin/HelloWorldService | grep CommonAPI
#ldd ./bin/libHelloWorld-someip.so | grep CommonAPI
install_capicxx_core() {
    if [ -d "capicxx-core-runtime" ]; then
        sudo rm -rf capicxx-core-runtime
    fi
    #3.2.0 version is compatible gcc 7.5 on ubuntu 18
    sudo git clone --branch 3.2.0 https://github.com/COVESA/capicxx-core-runtime.git
    pushd capicxx-core-runtime
    sudo mkdir build
    cd build
    sudo cmake -D CMAKE_INSTALL_PREFIX=$INSTALL_DIR ..
    sudo make -j"$(nproc)" || exit 1
    sudo make install
    popd
}

install_capicxx_someip() {
    if [ -d "capicxx-someip-runtime" ]; then
        sudo rm -rf capicxx-someip-runtime
    fi
    #3.2.4 version is compatible gcc 7.5 on ubuntu 18
    sudo git clone --branch 3.2.0  https://github.com/COVESA/capicxx-someip-runtime.git
    pushd capicxx-someip-runtime
    sudo mkdir build
    cd build
    sudo cmake -D USE_INSTALLED_COMMONAPI=ON -D CMAKE_INSTALL_PREFIX=$INSTALL_DIR ..
    sudo make -j"$(nproc)" || exit 1
    sudo make install
    popd
}

install_capicxx_core
install_capicxx_someip