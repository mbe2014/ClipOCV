#!/bin/csh -v
rm -rf testdir
mkdir testdir
cd testdir
ln -s ../build/debug/example/* .
ln -s ../example/lena.ppm .

./display < lena.ppm 
./display1 lena.ppm 
./invert < lena.ppm > inv.ppm ; 	display inv.ppm
./fft < lena.ppm > fft.ppm ; 		display fft.ppm
./mirror < lena.ppm > mirror.ppm ; 	display mirror.ppm
./mirror1 < lena.ppm > mirror1.ppm ; 	display mirror1.ppm
./pow0_5 < lena.ppm > pow.ppm ; 	display pow.ppm
./sobel1 < lena.ppm > sobel1.ppm ; 	display sobel1.ppm
./sobel2 < lena.ppm > sobel2.ppm ; 	display sobel2.ppm
./togray < lena.ppm > gray.ppm ; 	display gray.ppm
./togray1 < lena.ppm > gray1.ppm ; 	display gray1.ppm
./warp < lena.ppm > warp.ppm ; 		display warp.ppm
./roi1 < lena.ppm > roi1.ppm ;		display roi1.ppm
./roi2  > roi2.ppm ;			display roi2.ppm

