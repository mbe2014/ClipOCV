#include "copyright.h"

//======================================================================
// gui.h - OpenCV high gui wrapper
//
// Description:
//  This file provide OpenCV HIGHGUI functionality (excluding video IO
//  which is noty really GUI and QT extentions).
//  The GUI functionality is not provided as part of the image class
//  so it can be removed.
//
//======================================================================
//

#pragma once
#ifndef GUI_H
#define GUI_H

#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "image.h"

namespace clipocv {

void imshow(const char *winname, bMonoImg &img);
void imshow(const char *winname, bRgbImg  &img);
void imshow(const char *winname, fMonoImg &img);
void imshow(const char *winname, fRgbImg  &img);
void imshow(const char *winname, fCieImg  &img);
void imshow(const char *winname, fCmpImg  &img);

} // namespace

#endif /* GUI_H */

