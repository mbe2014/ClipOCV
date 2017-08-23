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
    fRgbImg res(width, height);
    cv::cvtColor(mat, res.mat, cv::COLOR_GRAY2RGB);
    return res;
}


fMonoImg::operator bMonoImg() {
    bMonoImg res(width, height);
    mat.convertTo(res.GetMat(),CV_8UC1);
    return res;
}

fMonoImg::operator bRgbImg() {
    bRgbImg res(width, height);
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_GRAY2RGB);
    tmp.convertTo(res.GetMat(),CV_32FC3);
    return res;
}

//@@@ need to consider ROI
fMonoImg::operator fCieImg() {
    fCieImg res(width, height);
    fMonoPix    *p = GetData();
    fCiePix  *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

//@@@ need to consider ROI
fMonoImg::operator fCmpImg() {
    fCmpImg res(width, height);
    fMonoPix   *p = GetData();
    fCmpPix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}


// rgb image casting

fRgbImg::operator fMonoImg() {
    fMonoImg res(width, height);
    cv::cvtColor(mat, res.mat, cv::COLOR_RGB2GRAY);
    return res;
}


fRgbImg::operator bMonoImg() {
    bMonoImg res(width, height);
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_RGB2GRAY);
    tmp.convertTo(res.GetMat(),CV_8UC1);
    return res;
}

fRgbImg::operator bRgbImg() {
    bRgbImg res(width, height);
    mat.convertTo(res.GetMat(),CV_8UC3);
    return res;
}

// @@@ need to consider ROI
fRgbImg::operator fCieImg() {
    fCieImg res(width, height);
    fRgbPix *p = GetData();
    fCiePix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

//@@@ need to consider ROI

fRgbImg::operator fCmpImg() {
    fCmpImg  res(width, height);
    fRgbPix  *p = GetData();
    fCmpPix  *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}


// Cie image casting

// @@@ Need to consider ROI
fCieImg::operator fMonoImg() {
    fMonoImg res(width, height);
    fCiePix *p = GetData();
    fMonoPix   *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = (p++)->CieY();
        i++;
    }
    return res;
}

// @@@ need to consider ROI
fCieImg::operator bMonoImg() {
    bMonoImg res(width, height);
    fCiePix *p = GetData();
    uint8_t *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = (p++)->CieY();
        i++;
    }
    return res;
}

//@@@ need to consider ROI
fCieImg::operator bRgbImg() {
    bRgbImg res(width, height);
    fCiePix *p = GetData();
    bRgbPix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

// @@@ need to consider ROI
fCieImg::operator fRgbImg() {
    fRgbImg res(width, height);
    fCiePix *p = GetData();
    fRgbPix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

// @@@ need to consider ROI
fCieImg::operator fCmpImg() {
    fCmpImg res(width, height);
    fCiePix *p = GetData();
    fCmpPix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

// Complex image casting

// @@@ need to consider ROI
fCmpImg::operator fMonoImg() {
    fMonoImg res(width, height);
    fCmpPix *p = GetData();
    fMonoPix   *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
        *(q+0) = (p+0)->GetNorm();
        *(q+1) = (p+1)->GetNorm();
        *(q+2) = (p+2)->GetNorm();
        *(q+3) = (p+3)->GetNorm();
        *(q+4) = (p+4)->GetNorm();
        *(q+5) = (p+5)->GetNorm();
        *(q+6) = (p+6)->GetNorm();
        *(q+7) = (p+7)->GetNorm();
        p+=8;
        q+=8;
    }
    while (i < GetSize()) {
        *(q++) = (p++)->GetNorm();
        i++;
    }
    return res;
}


fCmpImg::operator bMonoImg() {
    bMonoImg res(width, height);
    fCmpPix  *p = GetData();
    uint8_t  *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
        *(q+0) = (uint8_t) ((p+0)->GetNorm() + 0.5);
        *(q+1) = (uint8_t) ((p+1)->GetNorm() + 0.5);
        *(q+2) = (uint8_t) ((p+2)->GetNorm() + 0.5);
        *(q+3) = (uint8_t) ((p+3)->GetNorm() + 0.5);
        *(q+4) = (uint8_t) ((p+4)->GetNorm() + 0.5);
        *(q+5) = (uint8_t) ((p+5)->GetNorm() + 0.5);
        *(q+6) = (uint8_t) ((p+6)->GetNorm() + 0.5);
        *(q+7) = (uint8_t) ((p+7)->GetNorm() + 0.5);
        p+=8;
        q+=8;
    }
    while (i < GetSize()) {
        *(q++) = (uint8_t) ((p++)->GetNorm() + 0.5);
        i++;
    }
    return res;
}


fCmpImg::operator bRgbImg() {
    bRgbImg res(width, height);
    fCmpPix  *p = GetData();
    bRgbPix  *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}


fCmpImg::operator fRgbImg() {
    fRgbImg res(width, height);
    fCmpPix  *p = GetData();
    fRgbPix  *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

fCmpImg::operator fCieImg() {
    fCieImg res(width, height);
    fCmpPix  *p = GetData();
    fCiePix  *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}


//----------------------------------
// uint8_t image conversions
//----------------------------------

// monochome image casting

bMonoImg::operator fRgbImg() {
    fRgbImg res(width, height);
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_GRAY2RGB);
    tmp.convertTo(res.GetMat(),CV_32FC3);
    return res;
}


bMonoImg::operator fMonoImg() {
    fMonoImg res(width, height);
    mat.convertTo(res.GetMat(),CV_32FC1);
    return res;
}

bMonoImg::operator bRgbImg() {
    bRgbImg res(width, height);
    cv::cvtColor(mat, res.GetMat(), cv::COLOR_GRAY2RGB);
    return res;
}

// @@@ need to consider ROI
bMonoImg::operator fCieImg() {
    fCieImg res(width, height);
    uint8_t *p = GetData();
    fCiePix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

// @@@ need to consider ROI
bMonoImg::operator fCmpImg() {
    fCmpImg res(width, height);
    uint8_t *p = GetData();
    fCmpPix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}


// rgb image casting

bRgbImg::operator fMonoImg() {
    fMonoImg res(width, height);
    cv::Mat tmp;
    cv::cvtColor(mat, tmp, cv::COLOR_RGB2GRAY);
    tmp.convertTo(res.GetMat(),CV_8UC1);
    return res;
}


bRgbImg::operator bMonoImg() {
    bMonoImg res(width, height);
    cv::cvtColor(mat, res.GetMat(), cv::COLOR_RGB2GRAY);
    return res;
}

bRgbImg::operator fRgbImg() {
    fRgbImg res(width, height);
    mat.convertTo(res.GetMat(),CV_32FC3);
    return res;
}

//@@@ need to consider ROI
bRgbImg::operator fCieImg() {
    fCieImg res(width, height);
    bRgbPix *p = GetData();
    fCiePix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
    }
    return res;
}

bRgbImg::operator fCmpImg() {
    fCmpImg res(width, height);
    bRgbPix *p = GetData();
    fCmpPix *q = res.GetData();
    unsigned i;
    for(i=0; i < GetSize(); i+=8){
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
    while (i < GetSize()) {
        *(q++) = *(p++);
        i++;
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

