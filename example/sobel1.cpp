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

const float g3[3] = { 1.0F/4.0,   2.0F/4.0,  1.0F/4.0};
const float d3[3] = {-1.0F,       0.0F,      1.0F    };

fKernel gx3(3,1,g3);
fKernel gy3(1,3,g3);

fKernel dx3(3,1,d3);
fKernel dy3(1,3,d3);


fRgbPix sqrtPix(fRgbPix p)
{
    return fRgbPix(sqrtf(p[0]), sqrtf(p[1]), sqrtf(p[2]));
}

fRgbPix trim(fRgbPix p)
{
    return fRgbPix (p[0] < 0 ? 0 : (p[0] > 255 ? 255 : p[0]),
                    p[1] < 0 ? 0 : (p[1] > 255 ? 255 : p[1]),
                    p[2] < 0 ? 0 : (p[2] > 255 ? 255 : p[2]));
}

int main()
{
    fRgbImg img = pnm(stdin);

    fRgbImg Ix  = (img * gy3) * dx3;
    fRgbImg Iy  = (img * gx3) * dy3;
    fRgbImg res = (Ix*Ix + Iy*Iy).map(sqrtPix);

    pnm((bRgbImg) res.map(trim)).Write(stdout);

    return 0;
}

