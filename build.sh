sudo rm -rf build
sudo mkdir build
cd build
sudo cmake ..
sudo make -j"$(nproc)"
sudo make install