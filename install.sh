rm -rf build
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/scratch/.local/ ..
make install
