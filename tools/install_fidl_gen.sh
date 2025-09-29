#!/bin/bash
#https://github.com/COVESA/capicxx-dbus-tools/wiki/CommonAPI-C---D-Bus-in-10-minutes

# Variables
INSTALL_DIR="/usr/local"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
set -e

cd "$SCRIPT_DIR"
if [ ! -d "download" ]; then
    sudo mkdir download
fi
cd download
#IMPORTANT: version must be compatible with capicxx-core-runtime, capicxx-someip-runtime
install_commonapi_core_generator() {
    if [ -d "commonapi_core_generator" ]; then
        sudo rm -rf commonapi_core_generator
    fi
    if [ -f "commonapi_core_generator.zip" ]; then
        sudo rm -rf commonapi_core_generator.zip
    else
        echo "commonapi_core_generator.zip not found, downloading..."
    fi
    sudo wget https://github.com/GENIVI/capicxx-core-tools/releases/download/3.2.0.1/commonapi_core_generator.zip
    sudo unzip commonapi_core_generator.zip -d commonapi_core_generator/
}

install_commonapi_someip_generator() {
    if [ -d "commonapi_someip_generator" ]; then
        sudo rm -rf commonapi_someip_generator
    fi
    if [ -f "commonapi_someip_generator.zip" ]; then
        sudo rm -rf commonapi_someip_generator.zip
    else
        echo "commonapi_someip_generator.zip not found, downloading..."
    fi
    sudo wget https://github.com/GENIVI/capicxx-someip-tools/releases/download/3.2.0.1/commonapi_someip_generator.zip
    sudo unzip commonapi_someip_generator.zip -d commonapi_someip_generator/
}

install_commonapi_core_generator
install_commonapi_someip_generator