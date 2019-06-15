#include "copyright.h"

//============================================================
// yuv.h - yuv pixel type class
//
// Description:
//
// fYuvPix  - float YUV pixel class
//============================================================

#pragma once

#include <stdint.h>
#include "opencv2/core.hpp"
#include "color.h"

namespace clipocv {

const uint8_t YUV_Y = 0;
const uint8_t YUV_U = 1;
const uint8_t YUV_V = 2;

class bRgbPix;
class fRgbPix;
class fCiePix;
class fCmpPix;

class fYuvPix : public cv::Vec3f {
    
public:
    float &YuvY() {return operator[](YUV_Y);}
    const float &YuvY() const {return operator[](YUV_Y);}
    float &YuvU() {return operator[] (YUV_Y);}
    const float &YuvU() const {return operator[](YUV_U);}
    float &YuvV() {return operator[] (YUV_V);}
    const float &YuvV() const {return operator[](YUV_V);}

    float GetRed() const {
        return YuvY() * YUV2RGB[0] +
               YuvU() * YUV2RGB[1] +
               YuvU() * YUV2RGB[2];
    }
    float GetGreen() const {
        return YuvY() * YUV2RGB[3] +
               YuvU() * YUV2RGB[4] +
               YuvU() * YUV2RGB[5];
    }
    float GetBlue() const {
        return YuvY() * YUV2RGB[6] +
               YuvU() * YUV2RGB[7] +
               YuvU() * YUV2RGB[8];
    }
    

    float GetCieX() const {
        return YuvY() * YUV2XYZ[0] +
               YuvU() * YUV2XYZ[1] +
               YuvU() * YUV2XYZ[2];
    }
    float GetCieY() const {
        return YuvY() * YUV2XYZ[3] +
               YuvU() * YUV2XYZ[4] +
               YuvU() * YUV2XYZ[5];
    }
    float GetCieZ() const {
        return YuvY() * YUV2XYZ[6] +
               YuvU() * YUV2XYZ[7] +
               YuvU() * YUV2XYZ[8];
    }
    
    
    fCiePix GetCiePix() { return fCiePix(GetCieX(), GetCieY(), GetCieZ());  }
    fRgbPix GetRgbPix() { return fRgbPix(GetRed(), GetGreen(), GetBlue());  }

    // assign and cast operators.
    
    fYuvPix &operator=(const float v){	// float level
        YuvY()  = v;
        YuvU()  = 0;
        YuvV()  = 0;
        return *this;
    }
    
    fYuvPix &operator=(const fYuvPix &pix){
        YuvY() = pix.YuvY();
        YuvU() = pix.YuvU();
        YuvV() = pix.YuvV();
        return *this;
    }
    
    fYuvPix &operator=(const bRgbPix &pix);
    fYuvPix &operator=(const fRgbPix &pix);
    fYuvPix &operator=(const fCiePix &pix);
    fYuvPix &operator=(const fCmpPix &pix);
    
    
    // casting operators
    operator bRgbPix();
    operator fRgbPix();
    operator fCiePix();
    operator fCmpPix();
    operator bMonoPix();
    operator fMonoPix();

    
    // Pixel Constant reflexive operators
    
    fYuvPix &operator+= (const float c){
        YuvY()   += c;
        return *this;
    }
    
    fYuvPix &operator-= (const float c){
        YuvY()   -= c;
        return *this;
    }
    
    fYuvPix &operator*= (const float c){
        YuvY()   *= c;
        return *this;
    }
    
    fYuvPix &operator/= (const float c){
        YuvY()   /= c;
        return *this;
    }
    
    // Pixel Constant non-reflexive operators
    
    fYuvPix operator+ (const float c){
        fYuvPix tmp;
        tmp.YuvY() = YuvY()   + c;
        tmp.YuvU() = YuvU();
        tmp.YuvV() = YuvV();
        return tmp;
    }
    
    fYuvPix operator- (const float c){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() - c;
        tmp.YuvU() = YuvU();
        tmp.YuvV() = YuvV();
        return tmp;
    }
    
    fYuvPix operator* (const float c){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() * c;
        tmp.YuvU() = YuvU();
        tmp.YuvV() = YuvV();
        return tmp;
    }
    
    fYuvPix operator/ (const float c){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() / c;
        tmp.YuvU() = YuvU();
        tmp.YuvV() = YuvV();
        return tmp;
    }
    
    
    // Pixel Pixel reflexive operators  @@@ is this valid?
    
    fYuvPix &operator+= (const fYuvPix &pix){
        YuvY() += pix.YuvY();
        YuvU() += pix.YuvU();
        YuvV() += pix.YuvV();
        return *this;
    }
    
    fYuvPix &operator-= (const fYuvPix &pix){
        YuvY() -= pix.YuvY();
        YuvU() -= pix.YuvU();
        YuvV() -= pix.YuvV();
        return *this;
    }
    
    fYuvPix &operator*= (const fYuvPix &pix){
        YuvY() *= pix.YuvY();
        YuvU() *= pix.YuvU();
        YuvV() *= pix.YuvV();
        return *this;
    }
    
    fYuvPix &operator/= (const fYuvPix &pix){
        YuvY() /= pix.YuvY();
        YuvU() /= pix.YuvU();
        YuvV() /= pix.YuvV();
        return *this;
    }
    
    // Pixel Pixel non-reflexive operators
    
    fYuvPix operator+ (const fYuvPix &pix){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() + pix.YuvY();
        tmp.YuvU() = YuvU() + pix.YuvU();
        tmp.YuvV() = YuvV() + pix.YuvV();
        return tmp;
    }
    
    fYuvPix operator- (const fYuvPix &pix){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() - pix.YuvY();
        tmp.YuvU() = YuvU() - pix.YuvU();
        tmp.YuvV() = YuvV() - pix.YuvV();
        return tmp;
    }
    
    fYuvPix operator* (const fYuvPix &pix){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() * pix.YuvY();
        tmp.YuvU() = YuvU() * pix.YuvU();
        tmp.YuvV() = YuvV() * pix.YuvV();
        return tmp;
    }
    
    fYuvPix operator/ (const fYuvPix &pix){
        fYuvPix tmp;
        tmp.YuvY() = YuvY() / pix.YuvY();
        tmp.YuvU() = YuvU() / pix.YuvU();
        tmp.YuvV() = YuvV() / pix.YuvV();
        return tmp;
    }
    
    
    // constructors
    fYuvPix() {};
    
    fYuvPix(const float v){
        YuvY() = v;
        YuvU() = YuvV() = 0;
    }
    
    fYuvPix(const float y, const float u, const float v) {
        YuvY() = y;
        YuvU() = u;
        YuvV() = v;
    }
    
    // copy constructor  
    fYuvPix(const fYuvPix &pix){
        YuvY() = pix.YuvY();
        YuvU() = pix.YuvU();
        YuvV() = pix.YuvV();
    }
    
    // move constructor  
    fYuvPix(fYuvPix &&pix){
        YuvY() = pix.YuvY();
        YuvU() = pix.YuvU();
        YuvV() = pix.YuvV();
    }

    // move assignmnet
    fYuvPix &operator=(fYuvPix &&pix){
        YuvY() = pix.YuvY();
        YuvU() = pix.YuvU();
        YuvV() = pix.YuvV();
        return *this;
    }

};

} // namespace






