#1.0 ./install_Cmake_20.sh
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
 
export PATH=$PATH:/usr/local/bin/
 
#2.0 install Boost
#wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
wget https://downloads.sourceforge.net/project/boost/boost/1.81.0/boost_1_81_0.tar.gz
tar -xzvf boost_1_81_0.tar.gz
cd boost_1_81_0
pushd boost_1_81_0
./bootstrap.sh --prefix=/usr/local
sudo ./b2 install
popd
 
#3.0 download build & install vsomeip
rm -rf vsomeip
git clone  https://github.com/COVESA/vsomeip.git
cd vsomeip
mkdir build
cmake -Bbuild -DCMAKE_INSTALL_PREFIX=/usr/local -DENABLE_SIGNAL_HANDLING=1 -DCMAKE_CXX_FLAGS="-Wno-unused-variable" .
sudo cmake --build build --target install -j8