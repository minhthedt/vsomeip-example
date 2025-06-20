rm -rf build_cmake
mkdir build_cmake
pushd build_cmake
sudo apt install build-essential libssl-dev
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
#/usr/local/bin/cmake