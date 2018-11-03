#include "copyright.h"

//=================================================================
// image.cpp - image utilities.
//
// Description:
//	This file contains casting utilities for predefined image
//      types.
//
//=================================================================

#include <stdint.h>
#include "image.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

//------------------------
// Float image conversions
//------------------------

// monochome image casting

namespace clipocv {

fMonoImg::operator fRgbImg() {
    fRgbImg res(GetWidth(), GetHeight());
    cv::cvtColor(mat, res.GetMat(), cv::COLOR_GRAY2RGB);
    return res;
}


fMonoImg::operator bMonoImg() {
    bMonoImg res(GetWidth(), GetHeight());
    mat.convertTo(res.GetMat(),CV_8UC1);
    return res;
}

fMonoImg::operator bRgbImg() {
    bRgbImg res(GetWidth(), GetHeight());
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_GRAY2RGB);
    tmp.convertTo(res.GetMat(),CV_32FC3);
    return res;
}


//==============================================
// The following does not compile unfortuately
//==============================================
#ifdef UNDEF
template <class inT, class InP,  class outT, class outP> inT::operator outT() {
    outT res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        inP *p = GetRoiLine(y);
        outP  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}
#endif

fMonoImg::operator fCieImg() {
    fCieImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fMonoPix *p = GetRoiLine(y);
        fCiePix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

fMonoImg::operator fCmpImg() {
    fCmpImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fMonoPix *p = GetRoiLine(y);
        fCmpPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}


// rgb image casting

fRgbImg::operator fMonoImg() {
    fMonoImg res(GetWidth(), GetHeight());
    cv::cvtColor(mat, res.GetMat(), cv::COLOR_RGB2GRAY);
    return res;
}


fRgbImg::operator bMonoImg() {
    bMonoImg res(GetWidth(), GetHeight());
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_RGB2GRAY);
    tmp.convertTo(res.GetMat(),CV_8UC1);
    return res;
}

fRgbImg::operator bRgbImg() {
    bRgbImg res(GetWidth(), GetHeight());
    mat.convertTo(res.GetMat(),CV_8UC3);
    return res;
}

fRgbImg::operator fCieImg() {
    fCieImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fRgbPix *p = GetRoiLine(y);
        fCiePix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

fRgbImg::operator fCmpImg() {
    fCmpImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fRgbPix *p = GetRoiLine(y);
        fCmpPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}


// Cie image casting
//@@@ need to define pixel level casting i.o. CieY()
fCieImg::operator fMonoImg() {
    fMonoImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCiePix *p = GetRoiLine(y);
        fMonoPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = (p+0)->CieY();
            *(q+1) = (p+1)->CieY();
            *(q+2) = (p+2)->CieY();
            *(q+3) = (p+3)->CieY();
            *(q+4) = (p+4)->CieY();
            *(q+5) = (p+5)->CieY();
            *(q+6) = (p+6)->CieY();
            *(q+7) = (p+7)->CieY();
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = (p++)->CieY();
            i++;
        }
    }
    return res;
}

//@@@ need to define pixel level casting i.o. CieY()
fCieImg::operator bMonoImg() {
    bMonoImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCiePix *p = GetRoiLine(y);
        bMonoPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = (p+0)->CieY();
            *(q+1) = (p+1)->CieY();
            *(q+2) = (p+2)->CieY();
            *(q+3) = (p+3)->CieY();
            *(q+4) = (p+4)->CieY();
            *(q+5) = (p+5)->CieY();
            *(q+6) = (p+6)->CieY();
            *(q+7) = (p+7)->CieY();
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = (p++)->CieY();
            i++;
        }
    }
    return res;
}

fCieImg::operator bRgbImg() {
    bRgbImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCiePix *p = GetRoiLine(y);
        bRgbPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

fCieImg::operator fRgbImg() {
    fRgbImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCiePix *p = GetRoiLine(y);
        fRgbPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

fCieImg::operator fCmpImg() {
    fCmpImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCiePix *p = GetRoiLine(y);
        fCmpPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

// Complex image casting

fCmpImg::operator fMonoImg() {
    fMonoImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCmpPix *p = GetRoiLine(y);
        fMonoPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);  
            *(q+1) = *(p+1);   
            *(q+2) = *(p+2);  
            *(q+3) = *(p+3);  
            *(q+4) = *(p+4);  
            *(q+5) = *(p+5);  
            *(q+6) = *(p+6); 
            *(q+7) = *(p+7);  
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++); 
            i++;
        }
    }
    return res;
}
  
fCmpImg::operator bMonoImg() {
    bMonoImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCmpPix *p = GetRoiLine(y);
        bMonoPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = (bMonoPix) *(p+0);  
            *(q+1) = (bMonoPix) *(p+1); 
            *(q+2) = (bMonoPix) *(p+2);   ;
            *(q+3) = (bMonoPix) *(p+3); 
            *(q+4) = (bMonoPix) *(p+4); 
            *(q+5) = (bMonoPix) *(p+5);
            *(q+6) = (bMonoPix) *(p+6); 
            *(q+7) = (bMonoPix) *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = (bMonoPix) *(p++);
            i++;
        }
    }
    return res;
}


fCmpImg::operator bRgbImg() {
    bRgbImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCmpPix *p = GetRoiLine(y);
        bRgbPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}


fCmpImg::operator fRgbImg() {
    fRgbImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCmpPix *p = GetRoiLine(y);
        fRgbPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

fCmpImg::operator fCieImg() {
    fCieImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        fCmpPix *p = GetRoiLine(y);
        fCiePix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}


//----------------------------------
// uint8_t image conversions
//----------------------------------

// monochome image casting

bMonoImg::operator fRgbImg() {
    fRgbImg res(GetWidth(), GetHeight());
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_GRAY2RGB);
    tmp.convertTo(res.GetMat(),CV_32FC3);
    return res;
}


bMonoImg::operator fMonoImg() {
    fMonoImg res(GetWidth(), GetHeight());
    mat.convertTo(res.GetMat(),CV_32FC1);
    return res;
}

bMonoImg::operator bRgbImg() {
    bRgbImg res(GetWidth(), GetHeight());
    cv::cvtColor(mat, res.GetMat(), cv::COLOR_GRAY2RGB);
    return res;
}

bMonoImg::operator fCieImg() {
    fCieImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        bMonoPix *p = GetRoiLine(y);
        fCiePix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

bMonoImg::operator fCmpImg() {
    fCmpImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        bMonoPix *p = GetRoiLine(y);
        fCmpPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}


// rgb image casting

bRgbImg::operator fMonoImg() {
    fMonoImg res(GetWidth(), GetHeight());
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_RGB2GRAY);
    tmp.convertTo(res.GetMat(),CV_8UC1);
    return res;
}


bRgbImg::operator bMonoImg() {
    bMonoImg res(GetWidth(), GetHeight());
    cv::cvtColor(mat, res.GetMat(), cv::COLOR_RGB2GRAY);
    return res;
}

bRgbImg::operator fRgbImg() {
    fRgbImg res(GetWidth(), GetHeight());
    mat.convertTo(res.GetMat(),CV_32FC3);
    return res;
}

bRgbImg::operator fCieImg() {
    fCieImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        bRgbPix *p = GetRoiLine(y);
        fCiePix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

bRgbImg::operator fCmpImg() {
    fCmpImg res(GetRoiWidth(), GetRoiHeight());
    res.SetRoi(0,0,res.GetWidth(),res.GetHeight());
    res.SetOrigin(orgX, orgY);
    
    for (int y=0; y<res.GetRoiHeight(); y++) {
        bRgbPix *p = GetRoiLine(y);
        fCmpPix  *q = res.GetRoiLine(y);
        unsigned i;
        for (i = 0 ; i < res.GetRoiWidth()-8 ; i+=8) {
            *(q+0) = *(p+0);
            *(q+1) = *(p+1);
            *(q+2) = *(p+2);
            *(q+3) = *(p+3);
            *(q+4) = *(p+4);
            *(q+5) = *(p+5);
            *(q+6) = *(p+6);
            *(q+7) = *(p+7);
            p+=8;
            q+=8;
        }
        while (i < GetRoiWidth()) {
            *(q++) = *(p++);
            i++;
        }
    }
    return res;
}

//----------------------
// define common kernels
//----------------------

// derivatives
const float d3[3] = { 1.0F/1.0F,   0.0F/1.0F, -1.0F/1.0F                                                 };
const float d5[5] = { 1.0F/3.0F,   2.0F/3.0F,  0.0F/1.0F, -2.0F/3.0F, -1.0F/3.0F                         };
const float d7[7] = { 1.0F/7.0F,   2.0F/7.0F,  4.0F/7.0F,  0.0F/7.0F, -4.0F/7.0F, -2.0F/7.0F, -1.0F/7.0F };

fKernel Di2Dx3(3,1,d3);
fKernel Di2Dy3(1,3,d3);
fKernel Di2Dx5(5,1,d5);
fKernel Di2Dy5(1,5,d5);
fKernel Di2Dx7(7,1,d7);
fKernel Di2Dy7(1,7,d7);

// gousian (seperable).
const float g3[3] = { 0.25F,   0.5F,   0.25F                                        };
const float g5[5] = { 0.0625F, 0.25F,   0.375F, 0.25F,  0.0625F                     };
const float g7[7] = { 0.0156F, 0.0938F, 0.2344F, 0.3125F, 0.2344F, 0.0938F, 0.0156F };

fKernel Gx3(3,1,g3);
fKernel Gy3(1,3,g3);
fKernel Gx5(5,1,g5);
fKernel Gy5(1,5,g5);
fKernel Gx7(7,1,g7);
fKernel Gy7(1,7,g7);


} // namespace

