#!/bin/bash

# Variables
INSTALL_DIR="/usr/local"
BOOST_VERSION="1_81_0"
BOOST_VERSION_DOTS="1.81.0"
BOOST_BRANCH="boost-$BOOST_VERSION_DOTS"
BOOST_ARCHIVE="boost-1.81.0.tar.gz"
BOOST_SRC_DIR="boost_1_81_0"
BOOST_INCLUDE_DIR="$INSTALL_DIR/include/boost"
BOOST_HEADER="$BOOST_INCLUDE_DIR/version.hpp"
VSOMEIP_VERSION="3.5.0"
VSOMEIP_DIR="vsomeip"
CMAKE_REQUIRED_VERSION="3.20.0"
CMAKE_INSTALL_VERSION="3.20.2"
CMAKE_ARCHIVE="cmake-$CMAKE_INSTALL_VERSION.tar.gz"
CMAKE_SRC_DIR="cmake-$CMAKE_INSTALL_VERSION"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Prepare libraries directory
cd "$SCRIPT_DIR"
if [ -d "download" ]; then
    sudo rm -rf download
fi
sudo mkdir download
cd download

#the script exits immediately at the failed command
set -e
# 1. Check and install CMake
install_Cmake() {
    cmake_version=$(cmake --version 2>/dev/null | head -n 1 | awk '{print $3}')
    if [[ -z "$cmake_version" || "$(printf '%s\n' "$CMAKE_REQUIRED_VERSION" "$cmake_version" | sort -V | head -n 1)" != "$CMAKE_REQUIRED_VERSION" ]]; then
        echo "Installing CMake $CMAKE_INSTALL_VERSION..."
        sudo apt install -y build-essential libssl-dev
        sudo wget https://github.com/Kitware/CMake/releases/download/v$CMAKE_INSTALL_VERSION/$CMAKE_ARCHIVE
        sudo tar -zxvf $CMAKE_ARCHIVE
        pushd $CMAKE_SRC_DIR
        export CC=/usr/bin/gcc
        export CXX="g++ -O2 -std=c++11"
        export CFLAGS="-O2 -Wall"
        export CXXFLAGS="-O2 -g -Wall"
        export LDFLAGS="-L/usr/local/lib -lm"
        sudo ./bootstrap --prefix="$INSTALL_DIR"
        sudo make -j4
        sudo make install
        popd
        export PATH=$PATH:/usr/local/bin/
    else
        echo "[OK] CMake version $cmake_version is sufficient."
    fi
}


# 2. Check and install Boost
install_Boost() {
    # Helper functions
    get_boost_version() {
        apt_version=$(dpkg -s libboost-dev 2>/dev/null | grep '^Version:' | awk '{print $2}')
        if [[ -n "$apt_version" ]]; then
            echo "$apt_version"
            return
        fi
        if [[ -f "$BOOST_HEADER" ]]; then
            grep "#define BOOST_LIB_VERSION" "$BOOST_HEADER" | awk '{print $3}' | tr -d '"'
        else
            echo ""
        fi
    }

    version_ge() {
        [[ "$(printf '%s\n' "$1" "$2" | sort -V | head -n1)" == "$2" ]]
    }
    boost_version=$(get_boost_version)
    if [[ -n "$boost_version" ]] && version_ge "$boost_version" "${BOOST_VERSION_DOTS//_/.}"; then
        echo "[OK] Boost $boost_version already installed in $INSTALL_DIR. Skipping download and install."
    else
        if [[ ! -f "$BOOST_ARCHIVE" ]]; then
            echo "Downloading Boost $BOOST_VERSION_DOTS..."
            #wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
            #sudo wget https://github.com/boostorg/boost/archive/refs/tags/$BOOST_ARCHIVE
            #sudo tar -xzvf $BOOST_ARCHIVE
            sudo git clone --branch $BOOST_BRANCH --recursive https://github.com/boostorg/boost.git $BOOST_SRC_DIR
        fi
        pushd $BOOST_SRC_DIR
        sudo ./bootstrap.sh --prefix="$INSTALL_DIR" --without-libraries=python
        sudo ./b2 install --without-python
        echo "[OK] Boost $BOOST_BRANCH installed successfully"
        popd
    fi
}


# 3. Check and install dlt-daemon
install_dlt_daemon() {
    if ! command -v dlt-daemon &> /dev/null; then
        echo "dlt-daemon not found. Installing..."
        sudo git clone https://github.com/GENIVI/dlt-daemon.git dlt-daemon
        cd dlt-daemon || exit 1
        sudo mkdir build && cd build || exit 1
        sudo cmake .. || exit 1
        sudo make -j4 || exit 1
        sudo make install || exit 1
        cd / || exit 1
        echo "[OK] dlt-daemon installed successfully."
    else
        echo "[OK] dlt-daemon is installed at: $(command -v dlt-daemon)"
    fi
}

# 4. Clone vsomeip
install_vsomeip() {
    if [[ ! -d "$VSOMEIP_DIR" ]]; then
        echo "Cloning vsomeip repository..."
        sudo git clone https://github.com/COVESA/vsomeip.git
        pushd $VSOMEIP_DIR
        sudo git checkout $VSOMEIP_VERSION
        popd
    else
        echo "vsomeip folder already exists. Skipping clone."
    fi

    # Build & install vsomeip
    cd $VSOMEIP_DIR

    if [[ "$1" == "clean" ]]; then
        echo "Cleaning build directory..."
        sudo rm -rf build
    fi

    if [ ! -d "build" ]; then
        sudo mkdir build
    fi

    sudo cmake -Bbuild -DDISABLE_DLT=0 -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
        -DENABLE_SIGNAL_HANDLING=1 -DCMAKE_CXX_FLAGS="-Wno-unused-variable" .
    sudo cmake --build build --target install -j4
}

install_Cmake
install_Boost
install_dlt_daemon
install_vsomeip