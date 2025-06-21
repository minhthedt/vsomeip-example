#1.0 ./install_Cmake_20.sh
# Check CMake version
cmake_version=$(cmake --version 2>/dev/null | head -n 1 | awk '{print $3}')
required_version="3.20.0"

if [[ -z "$cmake_version" || "$(printf '%s\n' "$required_version" "$cmake_version" | sort -V | head -n 1)" != "$required_version" ]]; then
    echo "CMake version is less than $required_version or not installed. Installing CMake 3.20.2..."
    rm -rf cmake-3.20.2
    mkdir cmake-3.20.2
    pushd cmake-3.20.2
    sudo apt install build-essential libssl-dev -y
    wget https://github.com/Kitware/CMake/releases/download/v3.20.2/cmake-3.20.2.tar.gz
    tar -zxvf cmake-3.20.2.tar.gz
    cd cmake-3.20.2
    export CC=/usr/bin/gcc
    export CXX="g++ -O2 -std=c++11"
    export CFLAGS="-O2 -Wall"
    export CXXFLAGS="-O2 -g -Wall"
    export LDFLAGS="-L/usr/local/lib -lm"
    ./bootstrap
    make -j16
    sudo make install
    popd
    export PATH=$PATH:/usr/local/bin/
else
    echo "CMake version $cmake_version is sufficient."
fi

# i want to istall boost, vsomeip to custom directory(/usr/local)
#INSTALL_DIR="$(pwd)/../tools"
INSTALL_DIR="/usr/local"

#2.0 download Boost
BOOST_ARCHIVE="boost_1_81_0.tar.gz"
if [[ ! -f "$BOOST_ARCHIVE" ]]; then
    echo "$BOOST_ARCHIVE not found. Downloading..."
    #wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
    wget https://downloads.sourceforge.net/project/boost/boost/1.81.0/$BOOST_ARCHIVE
    tar -xzvf $BOOST_ARCHIVE
else
    echo "$BOOST_ARCHIVE already exists. Skipping download."
fi
#2.1 install Boost
pushd boost_1_81_0
./bootstrap.sh --prefix="$INSTALL_DIR"
sudo ./b2 install
popd
 
#3.0 download vsomeip
if [[ ! -d "vsomeip" ]]; then
    echo "vsomeip folder not found. Cloning repository..."
    git clone https://github.com/COVESA/vsomeip.git
else
    echo "vsomeip folder already exists. Skipping clone."
fi
#3.0 install vsomeip
cd vsomeip
mkdir build
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" -DENABLE_SIGNAL_HANDLING=1 -DCMAKE_CXX_FLAGS="-Wno-unused-variable" .
sudo cmake --build build --target install -j8