#include "copyright.h"

//============================================================
// complex.h - complex data type class
//
// Description:
//
// fCmpPix  - complex number data type
//
//
//============================================================

#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

#include <math.h>

namespace clipocv {

const uint8_t REAL = 0;
const uint8_t IMAG = 1;

class fRgbPix;
class bRgbPix;
class fCiePix;


class fCmpPix : public cv::Vec2f {
    
public:
    
    // access oprrators
    float &Re() {return operator[](REAL);}
    const float &Re() const {return operator[](REAL);}
    float &Im() {return operator[](IMAG);}
    const float &Im() const {return operator[](IMAG);}
    
    
    // complex norm (modulus) and phase (argument)
    float  GetNorm()  {return sqrtf(Re()*Re() + Im()*Im());}
    const float GetNorm() const {return sqrtf(Re()*Re() + Im()*Im());}
    
    float  GetPhase() {return atan2f(Im(), Re());}
    const float GetPhase() const {return atan2f(Im(), Re());}
    
    fCmpPix  GetConj() {return fCmpPix(Re(), -Im());}
    const fCmpPix GetConj() const {return fCmpPix(Re(), -Im());}
    
    // assign operators.
    fCmpPix  &operator=(const float v){
        Re() = v;
        Im() = 0;
        return *this;
    }
    
    fCmpPix &operator=(const fCmpPix &pix){
        Re() = pix.Re();
        Im() = pix.Im();
        return *this;
    }
    
    fCmpPix &operator=(const fRgbPix &pix);
    fCmpPix &operator=(const bRgbPix &pix);
    fCmpPix &operator=(const fCiePix &pix);
    
    
    // casting operators
    operator fRgbPix();
    operator bRgbPix();
    operator fCiePix();
    
    // Arithmetic operators
    // Pixel Constant reflexive operators
    
    fCmpPix &operator+= (const float c){
        Re()   += c;
        return *this;
    }
    
    fCmpPix &operator-= (const float c){
        Re()   -= c;
        return *this;
    }
    
    
    fCmpPix &operator*= (const float c){
        Re() *= c;
        Im() *= c;
        return *this;
    }
    
    fCmpPix &operator/= (const float c){
        Re() /= c;
        Im() /= c;
        return *this;
    }
    
    
    // Pixel Constant non-reflexive operators
    
    fCmpPix operator+ (const float c){
        fCmpPix tmp;
        tmp.Re() = Re() + c;
        tmp.Im() = Im();
        return tmp;
    }
    
    fCmpPix operator- (const float c){
        fCmpPix tmp;
        tmp.Re() = Re() - c;
        tmp.Im() = Im();
        return tmp;
    }
    
    
    fCmpPix operator* (const float c){
        fCmpPix tmp;
        tmp.Re() = Re() * c;
        tmp.Im() = Im() * c;
        return tmp;
    }
    
    fCmpPix operator/ (const float c){
        fCmpPix tmp;
        tmp.Re() = Re() / c;
        tmp.Im() = Im() / c;
        return tmp;
    }
    
    
    // Pixel Pixel reflexive operators
    fCmpPix  &operator+= (const fCmpPix &pix){
        Re() += pix.Re();
        Im() += pix.Im();
        return *this;
    }
    
    fCmpPix &operator-= (const fCmpPix &pix){
        Re() -= pix.Re();
        Im() -= pix.Im();
        return *this;
    }
    
    fCmpPix &operator*= (const fCmpPix &pix){
        Re() = Re() * pix.Re() - Im() * pix.Im();
        Im() = Re() * pix.Im() + Im() * pix.Re();
        return *this;
    }
    
    fCmpPix &operator/= (const fCmpPix &pix){
        float denom = Im() * Im() + pix.Im() * pix.Im();
        Re() = (Re() * pix.Re() + Im() * pix.Im()) / denom;
        Im() = (Im() * pix.Re() - Re() * pix.Im()) / denom;
        return *this;
    }
    
    // Pixel Pixel non-reflexive operators
    
    fCmpPix operator+ (const fCmpPix &pix){
        fCmpPix tmp;
        tmp.Re() = Re() + pix.Re();
        tmp.Im() = Im() + pix.Im();
        return tmp;
    }
    
    fCmpPix operator- (const fCmpPix &pix){
        fCmpPix tmp;
        tmp.Re() = Re() - pix.Re();
        tmp.Im() = Im() - pix.Im();
        return tmp;
    }
    
    fCmpPix operator* (const fCmpPix &pix){
        fCmpPix tmp;
        tmp.Re() = Re() * pix.Re() - Im() * pix.Im();
        tmp.Im() = Re() * pix.Im() + Im() * pix.Re();
        return tmp;
    }
    
    fCmpPix operator/ (const fCmpPix &pix){
        fCmpPix tmp;
        float denom = Im() * Im() + pix.Im() * pix.Im();
        tmp.Re() = (Re() * pix.Re() + Im() * pix.Im()) / denom;
        tmp.Im() = (Im() * pix.Re() - Re() * pix.Im()) / denom;
        return tmp;
    }
    
    
    // constructors
    fCmpPix() {};
    
    fCmpPix(const float v){
        Re() = v;
        Im() = 0;
    }
    
    fCmpPix(const float v, const float w) {
        Re() = v;
        Im() = w;
    }
    
    // copy constructor
    
    fCmpPix(const fCmpPix &pix){
        Re() = pix.Re();
        Im() = pix.Im();
    }
};

//================================
// Complex has no byte pixel type
//================================

} // namespace

#endif






