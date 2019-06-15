#include "copyright.h"

//============================================================
// cie.h - cie pixel type class
//
// Description:
//
// fCiePix  - cie color space pixel class
// Cie is memory only data type.
//
//============================================================

#pragma once
#ifndef CIE_H
#define CIE_H

#include "color.h"

namespace clipocv {

const unsigned CIE_X = 0;
const unsigned CIE_Y = 1;
const unsigned CIE_Z = 2;

class fRgbPix;
class bRgbPix;
class fCmpPix;
class fYuvPix;

class fCiePix : public cv::Vec3f {
    
public:
    float &CieX() {return operator[](0);}
    const float &CieX() const {return operator[](CIE_X);}
    float &CieY() {return operator[](1);}
    const float &CieY() const {return operator[](CIE_Y);}
    float &CieZ() {return operator[](2);}
    const float &CieZ() const {return operator[](CIE_Z);}
    
    float GetRed() const {
        return	CieX() * XYZ2RGB[0] +
      		    CieY() * XYZ2RGB[1] +
                CieZ() * XYZ2RGB[2] ;
    }
    float GetGreen() const {
        return	CieX() * XYZ2RGB[3] +
      		    CieY() * XYZ2RGB[4] +
                CieZ() * XYZ2RGB[5] ;
    }
    float GetBlue() const {
        return	CieX() * XYZ2RGB[6]  +
      		    CieY() * XYZ2RGB[7]  +
                CieZ() * XYZ2RGB[8] ;
    }
    
    float GetYuvY() const {
        return	CieX() * XYZ2YUV[0] +
      		    CieY() * XYZ2YUV[1] +
                CieZ() * XYZ2YUV[2] ;
    }
    float GetYuvU() const {
        return	CieX() * XYZ2YUV[3] +
      		    CieY() * XYZ2YUV[4] +
                CieZ() * XYZ2YUV[5] ;
    }
    float GetYuvV() const {
        return	CieX() * XYZ2YUV[6]  +
      		    CieY() * XYZ2YUV[7]  +
                CieZ() * XYZ2YUV[8] ;
    }



    // assign and cast operators.
    
    fCiePix &operator=(const float v){
        CieX() = v * (RGB2XYZ[0] + RGB2XYZ[1] + RGB2XYZ[2]);
        CieY() = v * (RGB2XYZ[3] + RGB2XYZ[4] + RGB2XYZ[5]);
        CieZ() = v * (RGB2XYZ[6] + RGB2XYZ[7] + RGB2XYZ[8]);
        return *this;
    }
    
    fCiePix &operator=(const fCiePix &pix){
        CieX() = pix.CieX();
        CieY() = pix.CieY();
        CieZ() = pix.CieZ();
        return *this;
    }
    
    fCiePix &operator=(const fRgbPix &pix);
    fCiePix &operator=(const bRgbPix &pix);
    fCiePix &operator=(const fCmpPix &pix);
    fCiePix &operator=(const fYuvPix &pix);
    
    // casting operators
    operator fRgbPix();
    operator bRgbPix();  
    operator fCmpPix();
    operator bMonoPix();
    operator fMonoPix();
    operator fYuvPix();
    
    // Pixel Constant reflexive operators
    // agrees with the RGB semantics.
    
    fCiePix &operator+= (const float c){
        CieX() += c * (RGB2XYZ[0] + RGB2XYZ[1] + RGB2XYZ[2]);
        CieY() += c * (RGB2XYZ[3] + RGB2XYZ[4] + RGB2XYZ[5]);
        CieZ() += c * (RGB2XYZ[6] + RGB2XYZ[7] + RGB2XYZ[8]);
        return *this;
    }
    
    fCiePix &operator-= (const float c){
        CieX() -= c * (RGB2XYZ[0] + RGB2XYZ[1] + RGB2XYZ[2]);
        CieY() -= c * (RGB2XYZ[3] + RGB2XYZ[4] + RGB2XYZ[5]);
        CieZ() -= c * (RGB2XYZ[6] + RGB2XYZ[7] + RGB2XYZ[8]);
        return *this;
    }
    
    fCiePix &operator*= (const float c){
        CieX() *= c;
        CieY() *= c;
        CieZ() *= c;
        return *this;
    }
    
    fCiePix &operator/= (const float c){
        CieX() /= c;
        CieY() /= c;
        CieZ() /= c;
        return *this;
    }
    
    // Pixel Constant non-reflexive operators
    
    fCiePix operator+ (const float c){
        fCiePix tmp;
        tmp.CieX() = CieX() + c;
        tmp.CieY() = CieY() + c;
        tmp.CieZ() = CieZ() + c;
        return tmp;
    }
    
    fCiePix operator- (const float c){
        fCiePix tmp;
        tmp.CieX() = CieX() - c;
        tmp.CieY() = CieY() - c;
        tmp.CieZ() = CieZ() - c;
        return tmp;
    }
    
    fCiePix operator* (const float c){
        fCiePix tmp;
        tmp.CieX() = CieX() * c;
        tmp.CieY() = CieY() * c;
        tmp.CieZ() = CieZ() * c;
        return tmp;
    }
    
    fCiePix operator/ (const float c){
        fCiePix tmp;
        tmp.CieX() = CieX() / c;
        tmp.CieY() = CieY() / c;
        tmp.CieZ() = CieZ() / c;
        return tmp;
    }
    
    // Pixel Pixel reflexive operators
    
    fCiePix &operator+= (const fCiePix &pix){
        CieX() += pix.CieX();
        CieY() += pix.CieY();
        CieZ() += pix.CieZ();
        return *this;
    }
    
    fCiePix &operator-= (const fCiePix &pix){
        CieX() -= pix.CieX();
        CieY() -= pix.CieY();
        CieZ() -= pix.CieZ();
        return *this;
    }
    
    
    fCiePix &operator*= (const fCiePix &pix){
        CieX() *= pix.CieX();
        CieY() *= pix.CieY();
        CieZ() *= pix.CieZ();
        return *this;
    }
    
    fCiePix &operator/= (const fCiePix &pix){
        CieX() /= pix.CieX();
        CieY() /= pix.CieY();
        CieZ() /= pix.CieZ();
        return *this;
    }
    
    // Pixel Pixel non-reflexive operators
    
    fCiePix operator+ (const fCiePix &pix){
        fCiePix tmp;
        tmp.CieX() = CieX() + pix.CieX();
        tmp.CieY() = CieY() + pix.CieY();
        tmp.CieZ() = CieZ() + pix.CieZ();
        return tmp;
    }
    
    fCiePix operator- (const fCiePix &pix){
        fCiePix tmp;
        tmp.CieX() = CieX() - pix.CieX();
        tmp.CieY() = CieY() - pix.CieY();
        tmp.CieZ() = CieZ() - pix.CieZ();
        return tmp;
    }
    
    fCiePix operator* (const fCiePix &pix){
        fCiePix tmp;
        tmp.CieX() = CieX() * pix.CieX();
        tmp.CieY() = CieY() * pix.CieY();
        tmp.CieZ() = CieZ() * pix.CieZ();
        return tmp;
    }
    
    fCiePix operator/ (const fCiePix &pix){
        fCiePix tmp;
        tmp.CieX() = CieX() / pix.CieX();
        tmp.CieY() = CieY() / pix.CieY();
        tmp.CieZ() = CieZ() / pix.CieZ();
        return tmp;
    }
    
    
    // constructors
    fCiePix() {};
    
    
    fCiePix(const float v){
        CieX() = CieY() = CieZ() = v;
    }
    
    
    fCiePix(const float x, const float y, const float z) {
        CieX() = x;
        CieY() = y;
        CieZ() = z;
    }
    
    // copy constructor
    fCiePix(const fCiePix &pix){
        CieX() = pix.CieX();
        CieY() = pix.CieY(); 
        CieZ() = pix.CieZ();
    }
    
    // move constructor
    fCiePix(fCiePix &&pix){
        CieX() = pix.CieX();
        CieY() = pix.CieY(); 
        CieZ() = pix.CieZ();
    } 

    // move assignmnet
    fCiePix &operator=(fCiePix &&pix){
        CieX() = pix.CieX();
        CieY() = pix.CieY();
        CieZ() = pix.CieZ();
        return *this;
    }
    
};

//================================
// CIE-XYZ has no byte pixel type
//================================

} //namespace

#endif






