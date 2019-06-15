#include "copyright.h"

//===========================================================
// color.h - color pixel type template
//
// Description:
//
//===========================================================

#pragma once
#ifndef COLOR_H
#define COLOR_H

namespace clipocv {

typedef uint8_t bMonoPix;
typedef float   fMonoPix;

// RGB709 <--> CIE XYZ 
const float RGB2XYZ[] = {
    0.412453,  0.357580,  0.180423,
    0.212671,  0.715160,  0.072169,
    0.019334,  0.119193,  0.950227
};

const float XYZ2RGB[] = {
    3.240479,   -1.537150,  -0.498535,
   -0.969256,    1.875992,   0.041556,
    0.055648,   -0.204043,   1.057311
};

// RGB709 <--> YUV 
const float RGB2YUV[] = {
    0.2126,     0.7152,     0.0722,
   -0.09991,   -0.33609,    0.436,
    0.615,     -0.55861,   -0.05639
};

const float YUV2RGB[] = {
    1.0,        0.0,        1.28033,
    1.0,       -0.21482,   -0.38059,
    1.0,        2.12798,    0
};


// YUV <--> CIE XYZ 
const float YUV2XYZ[] = {
    9.5046e-01,   3.0712e-01,   3.9198e-01,
    1.0000e+00,  -5.6483e-05,   1.0632e-04,
    1.0888e+00,   1.9965e+00,  -2.0610e-02
};

const float XYZ2YUV[] = {
   -2.6827e-04,   1.0002e+00,   7.0164e-05,
    2.6264e-02,  -5.6589e-01,   4.9683e-01,
    2.5312e+00,  -1.9818e+00,  -3.8943e-01
};

} // namespace

#endif







