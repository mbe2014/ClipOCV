#!/bin/csh -v
rm -rf testdir
mkdir testdir
cd testdir
ln -s ../build/release/example/* .
ln -s ../example/lena.ppm .

./display < lena.ppm 
./display1 lena.ppm 
./invert < lena.ppm > inv.ppm
./fft < lena.ppm > fft.ppm
./mirror < lena.ppm > mirror.ppm
./mirror1 < lena.ppm > mirror1.ppm
./pow0_5 < lena.ppm > pow.ppm
./sobel < lena.ppm > sobel.ppm
./sobel1 < lena.ppm > sobel1.ppm
./sobel2 < lena.ppm > sobel2.ppm
./togray < lena.ppm > gray.ppm
./togray1 < lena.ppm > gray1.ppm
./warp < lena.ppm > warp.ppm
./roi1 < lena.ppm > roi1.ppm

