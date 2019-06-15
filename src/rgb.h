#include "copyright.h"

//============================================================
// rgb.h - rgb pixel type class
//
// Description:
//
// fRgbPix  - rgb color space pixel class
//
//============================================================

#ifndef RGB_H
#define RGB_H

#include <stdint.h>
#include "opencv2/core.hpp"
#include "color.h"

namespace clipocv {

const uint8_t RED   = 0;
const uint8_t GREEN = 1;
const uint8_t BLUE  = 2;

class fCiePix;
class bRgbPix;
class fCmpPix;
class fYuvPix;

class fRgbPix : public cv::Vec3f {
    
public:
    float &Red() {return operator[](RED);}
    const float &Red() const {return operator[](RED);}
    float &Green() {return operator[] (GREEN);}
    const float &Green() const {return operator[](GREEN);}
    float &Blue() {return operator[] (BLUE);}
    const float &Blue() const {return operator[](BLUE);}
    
    float GetCieX() const {
        return	Red()   * RGB2XYZ[0]   +
                Green() * RGB2XYZ[1] +
                Blue()  * RGB2XYZ[2];
    }
    float GetCieY() const {
        return	Red()   * RGB2XYZ[3]   +
                Green() * RGB2XYZ[4] +
                Blue()  * RGB2XYZ[5];
    }
    float GetCieZ() const {
        return	Red()   * RGB2XYZ[6]  +
                Green() * RGB2XYZ[7] +
                Blue()  * RGB2XYZ[8];
    }
    
    float GetYuvY() const {
        return	Red()   * RGB2YUV[0]   +
                Green() * RGB2YUV[1] +
                Blue()  * RGB2YUV[2];
    }
    float GetYuvU() const {
        return	Red()   * RGB2YUV[3]   +
                Green() * RGB2YUV[4] +
                Blue()  * RGB2YUV[5];
    }
    float GetYuvV() const {
        return	Red()   * RGB2YUV[6]  +
                Green() * RGB2YUV[7] +
                Blue()  * RGB2YUV[8];
    }
    

    fCiePix GetCiePix() { return fCiePix(GetCieX(), GetCieY(), GetCieZ());  }
    fCiePix GetYuvPix() { return fYuvPix(GetYuvY(), GetYuvU(), GetYuvV());  }
    
    // assign and cast operators.
    
    fRgbPix &operator=(const float v){	// float level
        Red()   = v;
        Green() = v;
        Blue()  = v;
        return *this;
    }
    
    fRgbPix &operator=(const fRgbPix &pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
        return *this;
    }
    
    
    fRgbPix &operator=(const bRgbPix &pix);
    fRgbPix &operator=(const fCiePix &pix);
    fRgbPix &operator=(const fCmpPix &pix);
    fRgbPix &operator=(const fYuvPix &pix);
    
    
    // casting operators
    operator fCiePix();
    operator fYuvPix();
    operator bRgbPix();
    operator fCmpPix();
    
    // Pixel Constant reflexive operators
    
    fRgbPix &operator+= (const float c){
        Red()   += c;
        Green() += c;
        Blue()  += c;
        return *this;
    }
    
    fRgbPix &operator-= (const float c){
        Red()   -= c;
        Green() -= c;
        Blue()  -= c;
        return *this;
    }
    
    fRgbPix &operator*= (const float c){
        Red()   *= c;
        Green() *= c;
        Blue()  *= c;
        return *this;
    }
    
    fRgbPix &operator/= (const float c){
        Red()   /= c;
        Green() /= c;
        Blue()  /= c;
        return *this;
    }
    
    // Pixel Constant non-reflexive operators
    
    fRgbPix operator+ (const float c){
        fRgbPix tmp;
        tmp.Red()   = Red()   + c;
        tmp.Green() = Green() + c;
        tmp.Blue()  = Blue()  + c;
        return tmp;
    }
    
    fRgbPix operator- (const float c){
        fRgbPix tmp;
        tmp.Red()   = Red()   - c;
        tmp.Green() = Green() - c;
        tmp.Blue()  = Blue()  - c;
        return tmp;
    }
    
    fRgbPix operator* (const float c){
        fRgbPix tmp;
        tmp.Red()   = Red()   * c;
        tmp.Green() = Green() * c;
        tmp.Blue()  = Blue()  * c;
        return tmp;
    }
    
    fRgbPix operator/ (const float c){
        fRgbPix tmp;
        tmp.Red()   = Red()   / c;
        tmp.Green() = Green() / c;
        tmp.Blue()  = Blue()  / c;
        return tmp;
    }
    
    
    // Pixel Pixel reflexive operators
    
    fRgbPix &operator+= (const fRgbPix &pix){
        Red()   += pix.Red();
        Green() += pix.Green();
        Blue()  += pix.Blue();
        return *this;
    }
    
    fRgbPix &operator-= (const fRgbPix &pix){
        Red()   -= pix.Red();
        Green() -= pix.Green();
        Blue()  -= pix.Blue();
        return *this;
    }
    
    fRgbPix &operator*= (const fRgbPix &pix){
        Red()   *= pix.Red();
        Green() *= pix.Green();
        Blue()  *= pix.Blue();
        return *this;
    }
    
    fRgbPix &operator/= (const fRgbPix &pix){
        Red()   /= pix.Red();
        Green() /= pix.Green();
        Blue()  /= pix.Blue();
        return *this;
    }
    
    // Pixel Pixel non-reflexive operators
    
    fRgbPix operator+ (const fRgbPix &pix){
        fRgbPix tmp;
        tmp.Red()   = Red()   + pix.Red();
        tmp.Green() = Green() + pix.Green();
        tmp.Blue()  = Blue()  + pix.Blue();
        return tmp;
    }
    
    fRgbPix operator- (const fRgbPix &pix){
        fRgbPix tmp;
        tmp.Red()   = Red()   - pix.Red();
        tmp.Green() = Green() - pix.Green();
        tmp.Blue()  = Blue()  - pix.Blue();
        return tmp;
    }
    
    fRgbPix operator* (const fRgbPix &pix){
        fRgbPix tmp;
        tmp.Red()   = Red()   * pix.Red();
        tmp.Green() = Green() * pix.Green();
        tmp.Blue()  = Blue()  * pix.Blue();
        return tmp;
    }
    
    fRgbPix operator/ (const fRgbPix &pix){
        fRgbPix tmp;
        tmp.Red()   = Red()   / pix.Red();
        tmp.Green() = Green() / pix.Green();
        tmp.Blue()  = Blue()  / pix.Blue();
        return tmp;
    }
    
    
    // constructors
    fRgbPix() {};
    
    fRgbPix(const float v){
        Red() = Green() = Blue() = v;
    }
    
    fRgbPix(const float r, const float g, const float b) {
        Red()   = r;
        Green() = g;
        Blue()  = b;
    }
    
    // copy constructor  
    fRgbPix(const fRgbPix &pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
    }
    
    // move constructor  
    fRgbPix(fRgbPix &&pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
    }

    // move assignmnet
    fRgbPix &operator=(fRgbPix &&pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
        return *this;
    }

};


//=========================================
// Brgb is not template - to allow casting
// and to diffeenciate in operation sematics.
//=========================================


class bRgbPix : public cv::Vec3b {
    
public:
    uint8_t &Red() {return operator[](RED);}
    const uint8_t &Red() const {return operator[](RED);}
    uint8_t &Green() {return operator[] (GREEN);}
    const uint8_t &Green() const {return operator[](GREEN);}
    uint8_t &Blue() {return operator[] (BLUE);}
    const uint8_t &Blue() const {return operator[](BLUE);}
    
    float GetCieX() const {
        return	(float) Red()   * RGB2XYZ[0] +
                (float) Green() * RGB2XYZ[1] +
                (float) Blue()  * RGB2XYZ[2];
    }
    float GetCieY() const {
        return	(float) Red()   * RGB2XYZ[3] +
                (float) Green() * RGB2XYZ[4] +
                (float) Blue()  * RGB2XYZ[5];
    }
    float GetCieZ() const {
        return	(float) Red()   * RGB2XYZ[6] +
                (float) Green() * RGB2XYZ[7] +
                (float) Blue()  * RGB2XYZ[8];
    }
    
    float GetYuvY() const {
        return	(float) Red()   * RGB2YUV[0]   +
                (float) Green() * RGB2YUV[1] +
                (float) Blue()  * RGB2YUV[2];
    }
    float GetYuvU() const {
        return	(float) Red()   * RGB2YUV[3]   +
                (float) Green() * RGB2YUV[4] +
                (float) Blue()  * RGB2YUV[5];
    }
    float GetYuvV() const {
        return	(float) Red()   * RGB2YUV[6]  +
                (float) Green() * RGB2YUV[7] +
                (float) Blue()  * RGB2YUV[8];
    }
    
    fCiePix GetCiePix() { return fCiePix(GetCieX(), GetCieY(), GetCieZ());  }
    fCiePix GetYuvPix() { return fYuvPix(GetYuvY(), GetYuvU(), GetYuvV());  }

    // assign and cast operators.
    
    bRgbPix &operator=(const uint8_t v){	 
        Red()   = v;
        Green() = v;
        Blue()  = v;
        return *this;
    }
    
    bRgbPix &operator=(const bRgbPix &pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
        return *this;
    }
    
    
    bRgbPix &operator=(const fRgbPix &pix);
    bRgbPix &operator=(const fCiePix &pix);
    bRgbPix &operator=(const fYuvPix &pix);
    bRgbPix &operator=(const fCmpPix &pix);
    
    
    // casting operators
    operator fCiePix();
    operator fYuvPix();
    operator fRgbPix();
    operator fCmpPix();
    
    // Pixel Constant reflexive operators
    
    bRgbPix &operator+= (const uint8_t c){
        Red()   += c;
        Green() += c;
        Blue()  += c;
        return *this;
    }
    
    bRgbPix &operator-= (const uint8_t c){
        Red()   -= c;
        Green() -= c;
        Blue()  -= c;
        return *this;
    }
    
    bRgbPix &operator*= (const uint8_t c){
        Red()   *= c;
        Green() *= c;
        Blue()  *= c;
        return *this;
    }
    
    bRgbPix &operator/= (const uint8_t c){
        Red()   /= c;
        Green() /= c;
        Blue()  /= c;
        return *this;
    }
    
    // Pixel Constant non-reflexive operators
    
    bRgbPix operator+ (const uint8_t c){
        bRgbPix tmp;
        tmp.Red()   = Red()   + c;
        tmp.Green() = Green() + c;
        tmp.Blue()  = Blue()  + c;
        return tmp;
    }
    
    bRgbPix operator- (const uint8_t c){
        bRgbPix tmp;
        tmp.Red()   = Red()   - c;
        tmp.Green() = Green() - c;
        tmp.Blue()  = Blue()  - c;
        return tmp;
    }
    
    bRgbPix operator* (const uint8_t c){
        bRgbPix tmp;
        tmp.Red()   = Red()   * c;
        tmp.Green() = Green() * c;
        tmp.Blue()  = Blue()  * c;
        return tmp;
    }
    
    bRgbPix operator/ (const uint8_t c){
        bRgbPix tmp;
        tmp.Red()   = Red()   / c;
        tmp.Green() = Green() / c;
        tmp.Blue()  = Blue()  / c;
        return tmp;
    }
    
    
    // Pixel Pixel reflexive operators
    
    bRgbPix &operator+= (const bRgbPix &pix){
        Red()   += pix.Red();
        Green() += pix.Green();
        Blue()  += pix.Blue();
        return *this;
    }
    
    bRgbPix &operator-= (const bRgbPix &pix){
        Red()   -= pix.Red();
        Green() -= pix.Green();
        Blue()  -= pix.Blue();
        return *this;
    }
    
    bRgbPix &operator*= (const bRgbPix &pix){
        Red()   *= pix.Red();
        Green() *= pix.Green();
        Blue()  *= pix.Blue();
        return *this;
    }
    
    bRgbPix &operator/= (const bRgbPix &pix){
        Red()   /= pix.Red();
        Green() /= pix.Green();
        Blue()  /= pix.Blue();
        return *this;
    }
    
    // Pixel Pixel non-reflexive operators
    
    bRgbPix operator+ (const bRgbPix &pix){
        bRgbPix tmp;
        tmp.Red()   = Red()   + pix.Red();
        tmp.Green() = Green() + pix.Green();
        tmp.Blue()  = Blue()  + pix.Blue();
        return tmp;
    }
    
    bRgbPix operator- (const bRgbPix &pix){
        bRgbPix tmp;
        tmp.Red()   = Red()   - pix.Red();
        tmp.Green() = Green() - pix.Green();
        tmp.Blue()  = Blue()  - pix.Blue();
        return tmp;
    }
    
    bRgbPix operator* (const bRgbPix &pix){
        bRgbPix tmp;
        tmp.Red()   = Red()   * pix.Red();
        tmp.Green() = Green() * pix.Green();
        tmp.Blue()  = Blue()  * pix.Blue();
        return tmp;
    }
    
    bRgbPix operator/ (const bRgbPix &pix){
        bRgbPix tmp;
        tmp.Red()   = Red()   / pix.Red();
        tmp.Green() = Green() / pix.Green();
        tmp.Blue()  = Blue()  / pix.Blue();
        return tmp;
    }
    
    
    // constructors
    bRgbPix() {};
    
    bRgbPix(const uint8_t v){
        Red() = Green() = Blue() = v;
    }
    
    bRgbPix(const uint8_t r, const uint8_t g, const uint8_t b) {
        Red()   = r;
        Green() = g;
        Blue()  = b;
    }
    
    // copy constructor
    bRgbPix(const bRgbPix &pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
    }

    // move constructor
    bRgbPix(bRgbPix &&pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
    }

    // move assignmnet
    bRgbPix &operator=(bRgbPix &&pix){
        Red()   = pix.Red();
        Green() = pix.Green();
        Blue()  = pix.Blue();
        return *this;
    }
};

} // namespace

#endif






