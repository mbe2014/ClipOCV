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
 
#define SGN(x) (((x) > 0) - ((x) < 0))

fRgbPix warp(int x, int y, fRgbImgBasep(self))
{
    float tx = SGN(x)*sqrtf((float)abs(x))*sqrtf((float)self->GetWidth()/2);
    float ty = SGN(y)*sqrtf((float)abs(y))*sqrtf((float)self->GetHeight()/2);

    return self->bPix(tx,ty);

}
 
int main()
{
    fRgbImg img = pnm(stdin);
    fRgbImg res(img.GetWidth(),img.GetHeight());
   
    img.SetOrigin(img.GetWidth()/2,img.GetHeight()/2);
    res.SetOrigin(res.GetWidth()/2,res.GetHeight()/2);

    res = img.map(warp);

    pnm((bRgbImg) res).Write(stdout);

    return 0;
}