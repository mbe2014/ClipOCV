#include "copyright.h"

//======================================================================
// gui.cpp - OpenCV high gui wrapper
//
// Description:
//  This file provide OpenCV HIGHGUI functionality (excluding video IO
//  which is noty really GUI and QT extentions).
//  The GUI functionality is not provided as part of the image class
//  so it can be removed.
//
//======================================================================

#include "gui.h"

namespace clipocv {

void imshow(const char *winname, bMonoImg &img)
{
    cv::imshow(winname,img.GetMat());
}

void imshow(const char *winname, bRgbImg  &img)
{
    cv::Mat m;
    cv::cvtColor(img.GetMat(), m, cv::COLOR_RGB2BGR);
    cv::imshow(winname,m);
}

void imshow(const char *winname, fMonoImg &img)
{
    cv::Mat m;
    img.GetMat().convertTo(m,CV_8UC1);
    cv::imshow(winname,m);
}

void imshow(const char *winname, fRgbImg  &img)
{
    cv::Mat m;
    img.GetMat().convertTo(m,CV_8UC3);
    cv::cvtColor(m, m, cv::COLOR_RGB2BGR);
    cv::imshow(winname,m);
}


void imshow(const char *winname, fCieImg  &img)
{
    bRgbImg img1 = img;
    cv::imshow(winname,img1.GetMat());
}

void imshow(const char *winname, fCmpImg  &img)
{
    bMonoImg img1 = img;
    cv::imshow(winname,img1.GetMat());
}

} // namespace

