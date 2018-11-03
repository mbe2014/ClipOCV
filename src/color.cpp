#include "copyright.h"

//=================================================================
// color.cpp - color utilities
//
// Description:
//
//=================================================================

#include <stdint.h>
#include "rgb.h"
#include "cie.h"
#include "complex.h"

namespace clipocv {

//======= fCiePix =========


fCiePix &fCiePix::operator=(const fRgbPix &pix){
    CieX() = pix.GetCieX();
    CieY() = pix.GetCieY();
    CieZ() = pix.GetCieZ();
    return *this;
}

fCiePix &fCiePix::operator=(const bRgbPix &pix){
    CieX() = pix.GetCieX();
    CieY() = pix.GetCieY();
    CieZ() = pix.GetCieZ();
    return *this;
}

//@@@ is this a reasonable conversion
fCiePix &fCiePix::operator=(const fCmpPix &pix){
    CieX() = pix.GetNorm();
    CieY() = pix.GetNorm();
    CieZ() = pix.GetNorm();
    return *this;
}


// casting operators

fCiePix::operator fRgbPix() {
    fRgbPix tmp;
    tmp = *this;
    return tmp;
}

fCiePix::operator bRgbPix() {
    bRgbPix tmp;
    tmp = *this;
    return tmp;
}

fCiePix::operator fCmpPix() {
    fCmpPix tmp;
    tmp = *this;
    return tmp;
}

//======= fRgbPix =========

fRgbPix &fRgbPix::operator=(const fCiePix &pix){
    Red()   = pix.GetRed();
    Green() = pix.GetGreen();
    Blue()  = pix.GetBlue();
    return *this;
}

fRgbPix &fRgbPix::operator=(const bRgbPix &pix){
    Red()   = pix.Red();
    Green() = pix.Green();
    Blue()  = pix.Blue();
    return *this;
}

fRgbPix &fRgbPix::operator=( const fCmpPix &pix){
    Red()   = pix.GetNorm();
    Green() = pix.GetNorm();
    Blue()  = pix.GetNorm();
    return *this;
}


// casting operators

fRgbPix::operator fCiePix() {
    fCiePix tmp;
    tmp = *this;
    return tmp;
}

fRgbPix::operator bRgbPix() {
    bRgbPix tmp;
    tmp = *this;
    return tmp;
}

fRgbPix::operator fCmpPix() {
    fCmpPix tmp;
    tmp = *this;
    return tmp;
}

//======= bRgbPix =========

bRgbPix &bRgbPix::operator=(const fCiePix &pix){
    Red()   = (uint8_t) (pix.GetRed()   + 0.5);
    Green() = (uint8_t) (pix.GetGreen() + 0.5);
    Blue()  = (uint8_t) (pix.GetBlue()  + 0.5);
    return *this;
}

bRgbPix &bRgbPix::operator=(const fRgbPix &pix){
    Red()   = (uint8_t) (pix.Red()   + 0.5);
    Green() = (uint8_t) (pix.Green() + 0.5);
    Blue()  = (uint8_t) (pix.Blue()  + 0.5);
    return *this;
}

bRgbPix &bRgbPix::operator=(const fCmpPix &pix){
    Red()   = (uint8_t) (pix.GetNorm() + 0.5);
    Green() = (uint8_t) (pix.GetNorm() + 0.5);
    Blue()  = (uint8_t) (pix.GetNorm() + 0.5);
    return *this;
}

// casting operators

bRgbPix::operator fCiePix() {
    fCiePix tmp;
    tmp = *this;
    return tmp;
}

bRgbPix::operator fRgbPix() {
    fRgbPix tmp;
    tmp = *this;
    return tmp;
}

bRgbPix::operator fCmpPix() {
    fCmpPix tmp;
    tmp = *this;
    return tmp;
}

//======= fCmpPix =========


fCmpPix &fCmpPix::operator=(const fRgbPix &pix){
    Re()   = pix.GetCieY();
    Im()   = 0;
    return *this;
}


fCmpPix &fCmpPix::operator=(const fCiePix &pix){
    Re()   = pix.CieY();
    Im()   = 0;
    return *this;
}

fCmpPix &fCmpPix::operator=(const bRgbPix &pix){
    Re()   = pix.GetCieY();
    Im()   = 0;
    return *this;
}

// casting operators

fCmpPix::operator fRgbPix() {
    fRgbPix tmp;
    tmp = *this;
    return tmp;
}


fCmpPix::operator fCiePix() {
    fCiePix tmp;
    tmp = *this;
    return tmp;
}

fCmpPix::operator bRgbPix() {
    bRgbPix tmp;
    tmp = *this;
    return tmp;
}

fCmpPix::operator bMonoPix() {
    bMonoPix tmp;
    tmp = (bMonoPix) (GetNorm() + 0.5);
    return tmp;
}

fCmpPix::operator fMonoPix() {
    fMonoPix tmp;
    tmp = (fMonoPix) (GetNorm() + 0.5);
    return tmp;
}


} // namepsace

