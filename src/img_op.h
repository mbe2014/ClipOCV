#include "copyright.h"

//=================================================================
// img_op.h - image operator class template.
//
// Description:
// img_t -  Incore root image template class.
//          All image manipulations are done on this class (and its
//          derivatives).
//
// Assumption: The pixel type T doesn't contain pointers.
//
//=================================================================

#pragma once
#ifndef IMG_H
#define IMG_H

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "img_dat.h"

#include "opencv2/core.hpp"
#include <opencv2/imgproc.hpp>

namespace clipocv {

//----------
// fkernel
//----------

// Kernel images are used for convolution
// they limited version of img_t

class fKernel : public image_t<float, CV_32FC1> {
    
protected:
    using image_t<float, CV_32FC1>::mat;
    using image_t<float, CV_32FC1>::width;
    using image_t<float, CV_32FC1>::height;
    
public:
    using image_t<float, CV_32FC1>::GetWidth;
    using image_t<float, CV_32FC1>::GetHeight;
    using image_t<float, CV_32FC1>::GetSize;
    using image_t<float, CV_32FC1>::GetData;
    
    // disallow origin change
    void MovOrigin(const int, const int) {
        assert(0);
    }
    
    void SetOrigin(const int, const int){
        assert(0);
    }
    
    //(no casting of kernel)
    fKernel &operator=(const fKernel &ker){
        image_t<float, CV_32FC1>::operator=(ker);
        return *this;
    }
    
    // kernel to kernel convolution
    // extrapolation: 0 outside suppot
    fKernel operator*(const fKernel &ker){
        fKernel res(width, height);
        cv::Mat flipKer;
        cv::flip(ker.mat, flipKer, -1); // opencv 2D filter is correlation
        cv::filter2D(mat,res.mat,-1,flipKer, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
        return res;
    }
    
    // Kernel constructor
    fKernel(const unsigned w, const unsigned h,
            const float *init) : image_t<float, CV_32FC1>(w,h,w/2,h/2) {
        memcpy((void *) GetData(), (void *) init, w * h * sizeof(float));
    }
    
    // allow manual setting of kernel values
    fKernel(const unsigned w, const unsigned h) : image_t<float, CV_32FC1>(w,h,w/2,h/2) {
        memset((void *) GetData(), '\0', w * h * sizeof(float));
    }
    
    // kernel copy constructor
    fKernel(const fKernel &ker) : image_t<float, CV_32FC1>(ker) {}

    // kernel move constructor
    fKernel(fKernel &&ker) : image_t<float, CV_32FC1>(std::move(ker)) {}

    // kernel move assigmnet
     fKernel &operator=(fKernel &&ker){
        image_t<float, CV_32FC1>::operator=(std::move(ker));
        return *this;
    }
};


//------------
// img_t
//------------

extern fKernel Di2Dx3, Di2Dy3, Di2Dx5, Di2Dy5, Di2Dx7, Di2Dy7;
extern fKernel Gx3, Gy3, Gx5, Gy5, Gx7, Gy7;

template<class T, int ocvType> class img_t : public image_t<T, ocvType> {
    
public:
    
    using image_t<T, ocvType>::mat;
    using image_t<T, ocvType>::width;
    using image_t<T, ocvType>::height;
    using image_t<T, ocvType>::orgX;
    using image_t<T, ocvType>::orgY;
    using image_t<T, ocvType>::pix;
    
    using image_t<T, ocvType>::GetWidth;
    using image_t<T, ocvType>::GetHeight;
    using image_t<T, ocvType>::GetSize;
    using image_t<T, ocvType>::GetData;
    using image_t<T, ocvType>::GetXmin;
    using image_t<T, ocvType>::GetYmin;
    using image_t<T, ocvType>::GetXmax;
    using image_t<T, ocvType>::GetYmax;
    using image_t<T, ocvType>::Pix;
    using image_t<T, ocvType>::cPix;
    using image_t<T, ocvType>::bPix;
    
    // -- reflexive Image scalar operators --
    
    img_t &operator=(const T val){
        image_t<T, ocvType>::operator=(val);
        return *this;
    }
    
    img_t &operator+=(const T val){
        mat += val;
        return *this;
    }
    
    img_t &operator-=(const T val){
        mat -= val;
        return *this;
    }
    
    img_t &operator*=(const T val){
        //mat *= val;  // @@@ OpenCV does not overload *= operator
        multiply(mat,cv::Scalar(val),mat);
        return *this;
    }
    
    img_t &operator/=(const T val){
        // mat /= val; // @@@ OpenCV does not overload /= operator
        divide(mat,cv::Scalar(val),mat);
        return *this;
    }
    
    // -- non reflexive Image scalar operators
    
    // need to define friend functions. @@@ why?
    // friend img_t &operator+<T>(const T &val, const img_t &img){
    //    img.operator+(val);
    // }
    
    
    img_t operator+(const T val){
        img_t res(width, height, orgX, orgY);
        res.mat = mat + val;
        return res;
    }
    
    img_t operator-(const T val){
        img_t res(width, height, orgX, orgY);
        res.mat = mat - val;
        return res;
    }
    
    img_t operator*(const T val){
        img_t res(width, height, orgX, orgY);
        // res.mat = mat * val; // OpenCV does not overload the * operator
        multiply(mat,cv::Scalar(val),res.mat);
        return res;
    }
    
    img_t operator/(const T val){
        img_t res(width, height, orgX, orgY);
        //res.mat = mat / val; // OpenCV does not overload the / operator
        divide(mat,cv::Scalar(val),res.mat);
        return res;
    }
    
    // reflexive Image <-> Image operators
    
    img_t &operator=(const img_t &img){
        image_t<T, ocvType>::operator=(img);
        return *this;
    }
    
    img_t &operator+=(const img_t &img){
        assert(width == img.width && height == img.height);
        mat += img.mat;
        return *this;
    }
    
    img_t &operator-=(const img_t &img){
        assert(width == img.width && height == img.height);
        mat -= img.mat;
        return *this;
    }
    
    img_t &operator*=(const img_t &img){
        assert(width == img.width && height == img.height);
        //mat *= img.mat;  // this is matrix multiplication not what we want here
        multiply(mat,img.mat,mat);
        return *this;
    }
    
    img_t &operator/=(const img_t &img){
        assert(width == img.width && height == img.height);
        //mat /= img.mat;
        divide(mat,img.mat,mat);
        return *this;
    }
    
    // -- non reflexive Image <-> Image operators--
    // OpenCV doe not overload non reflexive ops
    
    img_t operator+(const img_t &img){
        assert(width == img.width && height == img.height);
        img_t res(width, height, orgX, orgY);
        res.mat = mat + img.mat;
        return res;
    }
    
    img_t operator-(const img_t &img){
        assert(width == img.width && height == img.height);
        img_t res(width, height, orgX, orgY);
        res.mat = mat - img.mat;
        return res;
    }
    
    img_t operator*(const img_t &img){
        assert(width == img.width && height == img.height);
        img_t res(width, height, orgX, orgY);
        // res/mat = mat * img.mat
        multiply(mat,img.mat,res.mat);
        return res;
    }
    
    img_t operator/(const img_t &img){
        assert(width == img.width && height == img.height);
        img_t res(width, height, orgX, orgY);
        //res.mat = mat / img.mat
        divide(mat,img.mat,res.mat);
        return res;
    }
    
    // convolution image kernel
    // border is replicated (prevents discontinuity)
    
    img_t operator*(const fKernel &ker){
        img_t res(width, height, orgX, orgY);
        cv::Mat flipKer;
        flip(ker.GetMat(), flipKer, -1); // opencv 2D filter is correlation
        filter2D(mat,res.GetMat(),-1,flipKer, cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
        return res;
    }
    
    
    // ---unary operators---
    
    // Map functions.
    // @@@ need to consider ROI
    img_t map(T f(T x)){
        img_t res(width, height, orgX, orgY);
        unsigned i;
        T *p = GetData();
        T *q = res.GetData();
        for (i = 0 ; i < GetSize()-8 ; i+=8) {
            *(q+0) = f(*(p+0));
            *(q+1) = f(*(p+1));
            *(q+2) = f(*(p+2));
            *(q+3) = f(*(p+3));
            *(q+4) = f(*(p+4));
            *(q+5) = f(*(p+5));
            *(q+6) = f(*(p+6));
            *(q+7) = f(*(p+7));
            p+=8;
            q+=8;
        }
        while(i<GetSize()) {
            *(q++) = f(*(p++));
            i++;
        }
        return res;
    }
    
    template<typename A> img_t map(T f(T x, A arg), A arg){
        img_t res(width, height, orgX, orgY);
        unsigned i;
        T *p = GetData();
        T *q = res.GetData();
        for (i = 0 ; i < GetSize()-8 ; i+=8) {
            *(q+0) = f(*(p+0), arg);
            *(q+1) = f(*(p+1), arg);
            *(q+2) = f(*(p+2), arg);
            *(q+3) = f(*(p+3), arg);
            *(q+4) = f(*(p+4), arg);
            *(q+5) = f(*(p+5), arg);
            *(q+6) = f(*(p+6), arg);
            *(q+7) = f(*(p+7), arg);
            p+=8;
            q+=8;
        }
        while(i<GetSize()) {
            *(q++) = f(*(p++), arg);
            i++;
        }
        return res;
    }

    
    // map with image data self (this) pointer
    
    //@@@ need to consider ROI
    img_t map(T f(int x, int y, image_t<T, ocvType> *self)){
        
        img_t res(width, height, orgX, orgY);
        
        int y,x;
        for (y = GetYmin() ; y <= GetYmax() ; y++){
            T *p = &Pix(GetXmin(),y);
            T *q = &res.Pix(res.GetXmin(),y);
            for (x = GetXmin() ; x <= GetXmax()-8 ; x+=8){
                *(q+0) = f(x+0,y, this);
                *(q+1) = f(x+1,y, this);
                *(q+2) = f(x+2,y, this);
                *(q+3) = f(x+3,y, this);
                *(q+4) = f(x+4,y, this);
                *(q+5) = f(x+5,y, this);
                *(q+6) = f(x+6,y, this);
                *(q+7) = f(x+7,y, this);
                p+=8;
                q+=8;
            }
            while(x <= GetXmax()) {
                *(q++) = f(x,y, this);
                x++;
            }
        }
        return res;
    }

    //@@@ need to consider ROI
    template<typename A> img_t map(T f(int x, int y, image_t<T, ocvType> *self), A arg){
        
        img_t res(width, height, orgX, orgY);
        
        int y,x;
        for (y = GetYmin() ; y <= GetYmax() ; y++){
            T *p = &Pix(GetXmin(),y);
            T *q = &res.Pix(res.GetXmin(),y);
            for (x = GetXmin() ; x <= GetXmax()-8 ; x+=8){
                *(q+0) = f(x+0,y, this, arg);
                *(q+1) = f(x+1,y, this, arg);
                *(q+2) = f(x+2,y, this, arg);
                *(q+3) = f(x+3,y, this, arg);
                *(q+4) = f(x+4,y, this, arg);
                *(q+5) = f(x+5,y, this, arg);
                *(q+6) = f(x+6,y, this, arg);
                *(q+7) = f(x+7,y, this, arg);
                p+=8;
                q+=8;
            }
            while(x <= GetXmax()) {
                *(q++) = f(x,y, this, arg);
                x++;
            }
        }
        return res;
    }
    
    // inverse.
    // inverse of unsigned is the complement. 
    img_t operator-(){
            if (ocvType == CV_8UC1 || ocvType == CV_8UC3) {
                mat = cv::Scalar::all(255) - mat;
                return *this;
            }
            return (*this * (T)(-1));
    }
    
    //@@@ need to add flip / transpose / rot 90 180
    
    // Derivatives.
    img_t dx(const uint8_t filt_len = 5) {
        switch(filt_len){
            case 3: return (*this * Di2Dx3);
            case 5: return (*this * Di2Dx5);
            case 7: return (*this * Di2Dx7);
            default:
                assert(0);
                return *this; // prevent compilation warning
        }
    }
    
    img_t dy(const uint8_t filt_len = 5) {
        switch(filt_len){
            case 3: return (*this * Di2Dy3);
            case 5: return (*this * Di2Dy5);
            case 7: return (*this * Di2Dy7);
            default:
                assert(0);
                return *this; // prevent compilation warning
        }
    }
    
    
    // Blur
    img_t gx(const uint8_t filt_len = 5) {
        switch(filt_len){
            case 3: return (*this * Gx3);
            case 5: return (*this * Gx5);
            case 7: return (*this * Gx7);
            default:
                assert(0);
                return *this; // prevent compilation warning
        }
    }
    
    img_t gy(const uint8_t filt_len = 5) {
        switch(filt_len){
            case 3: return (*this * Gy3);
            case 5: return (*this * Gy5);
            case 7: return (*this * Gy7);
            default:
                assert(0);
                return *this; // prevent compilation warning
        }
    }
    
    
    // contructor/distructor  
    
    img_t() : image_t<T,ocvType>(){}
    
    img_t(const unsigned w, const unsigned h,
          const int ox=0, const int oy=0) : image_t<T, ocvType>(w, h,ox,oy){}
    
    img_t(const cv::Mat &mat) : image_t<T, ocvType>(mat){}
   
    img_t(const img_t &img) : image_t<T, ocvType>(img){}
   
    // move semantics
    img_t(img_t &&img) : image_t<T, ocvType>(std::move(img)){}
        
    img_t &operator=(img_t &&img){
        image_t<T, ocvType>::operator=(std::move(img));
        return *this;
    }

    
    // image_t distructor is called to free data.
    
};

} // namespace

#endif







