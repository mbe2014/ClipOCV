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

// RGB709 to CIE XYZ system
const float RedToX	= 0.412453F;
const float GreenToX	= 0.357580F;
const float BlueToX    	= 0.180423F;

const float RedToY     	= 0.212671F;
const float GreenToY	= 0.715160F;
const float BlueToY    	= 0.072169F;

const float RedToZ     	= 0.019334F;
const float GreenToZ	= 0.119193F;
const float BlueToZ    	= 0.950227F;


// CIE XYZ to RGB709 system
const float XtoRed     	=  3.240479F;
const float YtoRed     	= -1.537150F;
const float ZtoRed     	= -0.498535F;

const float XtoGreen	= -0.969256F;
const float YtoGreen	=  1.875992F;
const float ZtoGreen	=  0.041556F;

const float XtoBlue    	=  0.055648F;
const float YtoBlue    	= -0.204043F;
const float ZtoBlue    	=  1.057311F;

} // namespace

#endif







