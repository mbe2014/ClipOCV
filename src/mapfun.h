#include "copyright.h"

//=================================================================
// mapfun - useful map functions
//
// Description:
//  The following function can be used with .map() operator.
//  for C++11 functions can be provided as lambda expressions
//
//=================================================================

#pragma once
#ifndef MAPFUN_H
#define MAPFUN_H

#include <stdint.h>
#include <math.h>
#include "rgb.h"
#include "cie.h"
#include "complex.h"

namespace clipocv {

//------------------
// math functions
//------------------

inline fRgbPix sqrtPix(fRgbPix p)
{
    return fRgbPix(sqrtf(p[0]), sqrtf(p[1]), sqrtf(p[2]));
}

inline fRgbPix log10Pix(fRgbPix p)
{
    return fRgbPix(log10f(p[0]), log10f(p[1]), log10f(p[2]));
}

inline fRgbPix logPix(fRgbPix p)
{
    return fRgbPix(logf(p[0]), logf(p[1]), logf(p[2]));
}

inline fRgbPix powPix(fRgbPix p, float x)
{
    return fRgbPix(powf(p[0],x), powf(p[1],x), powf(p[2],x));
}

inline fRgbPix boundPix(fRgbPix p)
{
    return fRgbPix (p[0] < 0 ? 0 : (p[0] > 255 ? 255 : p[0]),
                    p[1] < 0 ? 0 : (p[1] > 255 ? 255 : p[1]),
                    p[2] < 0 ? 0 : (p[2] > 255 ? 255 : p[2]));
}

inline fRgbPix absPix(fRgbPix p)
{
    return fRgbPix(fabs(p[0]), fabs(p[1]), fabs(p[2]));
}


// Gemotric transfromations

inline float flipH(int x, int y, fMonoImgBasep(self))
{
    return self->aPix(self->GetWidth()-x-1, y);
}

inline float flipV(int x, int y, fMonoImgBasep(self))
{
    return self->aPix(x, self->GetHeight()-y-1);
}

inline fRgbPix flipH(int x, int y, fRgbImgBasep(self))
{
    return self->aPix(self->GetWidth()-x-1, y);
}

inline fRgbPix flipV(int x, int y, fRgbImgBasep(self))
{
    return self->aPix(x, self->GetHeight()-y-1);
}

} // namespace



#endif /* MAPFUN_H */
