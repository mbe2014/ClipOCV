#include "copyright.h"

//=================================================================
// complex.cpp - complex only operators.
//
// Description:
//	This file contains fft related operations
//
//=================================================================

#include <stdint.h>
#include "image.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

namespace clipocv {

fCmpImg fCmpImg::fft()
{
    fCmpImg res(GetWidth(), GetHeight());
    cv::dft(mat, res.mat, cv::DFT_COMPLEX_OUTPUT);
    return res;
}

fCmpImg fCmpImg::ifft()
{
    fCmpImg res(GetWidth(), GetHeight());
    cv::idft(mat, res.mat, cv::DFT_COMPLEX_OUTPUT | cv::DFT_SCALE);
    return res;
}

// @@@ No OpenCV equivalent?
fCmpImg fCmpImg::fftShift()
{
    fCmpImg res(GetWidth(), GetHeight());
    for (int x=0; x < (int) GetWidth(); x++){
        for (int y=0; y < (int) GetHeight(); y++){
            int nx = x + GetWidth()/2;
            if (nx >= (int) GetWidth()) nx -= GetWidth();
            int ny = y + GetHeight()/2;
            if (ny >= (int) GetHeight()) ny -= GetHeight();
            
            res.Pix(x,y) = Pix(nx,ny);
        }
    }
    return res;
}

} // namespace
