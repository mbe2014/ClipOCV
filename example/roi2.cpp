//-----------------------------------------------------------------------------------                                                            
// Copyright (c) 2017 Moshe Ben-Ezra
// 
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, 
//    this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, 
//    this list of conditions and the following disclaimer in the documentation and/or
//    other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may 
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------------                                                            
#include "clipocv.h"
using namespace clipocv;

int main(int argc, char *argv[])
{
    fRgbImg img1 (512,512);
    fRgbImg img2 (512,512);

    img1 = fRgbPix(200,0,0); // red
    img2 = fRgbPix(0,200,0); // green

    img1.SetRoi(img1.GetWidth()/4, img1.GetHeight()/4, img1.GetWidth()/2, img1.GetHeight()/2); 
    img2.SetRoi(img2.GetWidth()/4, img2.GetHeight()/4, img2.GetWidth()/2, img2.GetHeight()/2);

    img1 = fRgbPix(0,0,200); // red with blue center
    img2 = img1;  // green with blue center

    pnm((bRgbImg) img2).Write(stdout);
}
