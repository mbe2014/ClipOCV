#!/bin/csh -v
rm -rf build
mkdir build
cd build
mkdir debug
mkdir release
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make
cd ../release
cmake -DCMAKE_BUILD_TYPE=Release ../..
make

