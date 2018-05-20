#include "copyright.h"

//=================================================================
// image.h - Incore image definition.
//
// Description:
// 	This file contains predfrined image types and operators
//	The types are subclasses not typedefs to allow extentions
//      and modifications for specific types.
//
//=================================================================

#pragma once
#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>

#include "rgb.h"
#include "cie.h"
#include "complex.h"
#include "img_op.h"

namespace clipocv {

typedef uint8_t bMonoPix;
typedef float   fMonoPix;

// following defines are syntactic sugar for map function

#define bMonoImgBasep(x) image_t<bMonoPix,   CV_8UC1> *(x)
#define bRgbImgBasep(x)  image_t<bRgbPix, CV_8UC3> *(x)

#define fMonoImgBasep(x) image_t<fMonoPix,   CV_32FC1> *(x)
#define fRgbImgBasep(x)  image_t<fRgbPix, CV_32FC3> *(x)

#define fCieImgBasep(x)  image_t<fCiePix, CV_32FC3> *(x)
#define fCmpImgBasep(x)  image_t<fCmpPix, CV_32FC2> *(x)



//-------------------------
// define actual data types
//-------------------------

class fMonoImg ;
class fRgbImg ;

class bMonoImg;
class bRgbImg;

class fCieImg;
class fCmpImg;

class fKernel;

// some predefinded kefnels.
extern fKernel Di2Dx3;
extern fKernel Di2Dy3;
extern fKernel Di2Dx5;
extern fKernel Di2Dy5;
extern fKernel Di2Dx7;
extern fKernel Di2Dy7;
extern fKernel Gx3;
extern fKernel Gy3;
extern fKernel Gx5;
extern fKernel Gy5;
extern fKernel Gx7;
extern fKernel Gy7;
//---------------------------


//========================================================
// fMonoPix classes are the incore classes all operators
// are defined on fMonoPix classes.
//========================================================


class fMonoImg : public img_t<fMonoPix, CV_32FC1> {
    
public:
    
    // casting
    operator fRgbImg();
    operator bMonoImg();
    operator bRgbImg();
    operator fCieImg();
    operator fCmpImg();
    
    // operators
    fMonoImg &operator=(const fMonoPix val){
        img_t<fMonoPix, CV_32FC1>::operator=(val);
        return *this;
    }
    fMonoImg &operator+=(const fMonoPix val){
        img_t<fMonoPix, CV_32FC1>::operator+=(val);
        return *this;
    }
    fMonoImg &operator-=(const fMonoPix val){
        img_t<fMonoPix, CV_32FC1>::operator-=(val);
        return *this;
    }
    fMonoImg &operator*=(const fMonoPix val){
        img_t<fMonoPix, CV_32FC1>::operator*=(val);
        return *this;
    }
    fMonoImg &operator/=(const fMonoPix val){
        img_t<fMonoPix, CV_32FC1>::operator/=(val);
        return *this;
    }
    fMonoImg operator+(const fMonoPix val){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator+(val);
    }
    fMonoImg operator-(const fMonoPix val){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator-(val);
    }
    fMonoImg operator*(const fMonoPix val){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator*(val);
    }
    fMonoImg operator/(const fMonoPix val){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator/(val);
    }
    fMonoImg &operator=(const fMonoImg &img){
        img_t<fMonoPix, CV_32FC1>::operator=(img);
        return *this;
    }
    fMonoImg &operator+=(const fMonoImg &img){
        img_t<fMonoPix, CV_32FC1>::operator+=(img);
        return *this;
    }
    fMonoImg &operator-=(const fMonoImg &img){
        img_t<fMonoPix, CV_32FC1>::operator-=(img);
        return *this;
    }
    fMonoImg &operator*=(const fMonoImg &img){
        img_t<fMonoPix, CV_32FC1>::operator*=(img);
        return *this;
    }
    fMonoImg &operator/=(const fMonoImg &img){
        img_t<fMonoPix, CV_32FC1>::operator/=(img);
        return *this;
    }
    fMonoImg operator+(const fMonoImg &img){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator+(img);
    }
    fMonoImg operator-(const fMonoImg &img){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator-(img);
    }
    fMonoImg operator*(const fMonoImg &img){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator*(img);
    }
    fMonoImg operator/(const fMonoImg &img){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator/(img);
    }
    fMonoImg operator*(fKernel &ker){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator*(ker);
    }
    fMonoImg operator-(){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::operator-();
    }
    
    fMonoImg map(fMonoPix f(fMonoPix x)){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::map(f);
    }
    
    template <typename A> fMonoImg map(fMonoPix f(fMonoPix x, A arg), A arg){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::map(f, arg);
    }
    
    fMonoImg map(fMonoPix f(int x, int y, image_t<fMonoPix, CV_32FC1> *self)){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::map(f);
    }
    
    template<typename A> fMonoImg map(fMonoPix f(int x, int y, image_t<fMonoPix, CV_32FC1> *self, A arg), A arg){
        return (fMonoImg) img_t<fMonoPix, CV_32FC1>::map(f, arg);
    }

    
    
    // contructor
    fMonoImg() : img_t<fMonoPix, CV_32FC1>(){};

    fMonoImg(const unsigned w, const unsigned h,
             const int ox=0,   const int oy=0) : img_t<fMonoPix, CV_32FC1>(w, h,ox,oy){};

    fMonoImg(const cv::Mat &mat, bool flip=true, bool clone = false) : img_t<fMonoPix, CV_32FC1>(mat, flip, clone){};

    // copy constructor
    fMonoImg(const fMonoImg &img) : img_t<fMonoPix, CV_32FC1>(img){};

    fMonoImg(const img_t<fMonoPix, CV_32FC1> &img) : img_t<fMonoPix, CV_32FC1>(img){};

    // move constructor
    fMonoImg(fMonoImg &&img) : img_t<fMonoPix, CV_32FC1>(std::move(img)){
    };

    fMonoImg(img_t<fMonoPix, CV_32FC1> &&img) : img_t<fMonoPix, CV_32FC1>(std::move(img)){};

    // move assignmnet
    fMonoImg &operator=(fMonoImg &&img){
        img_t<fMonoPix, CV_32FC1>::operator=(std::move(img));
        return *this;
    }

};


class fRgbImg : public img_t<fRgbPix, CV_32FC3>{
    
public:
    
    //operatores
    
    // casting
    operator fMonoImg() ;
    operator bMonoImg();
    operator bRgbImg() ;
    operator fCieImg() ;
    operator fCmpImg();

    
    // operators
    fRgbImg &operator=(const fRgbPix &val){
        img_t<fRgbPix, CV_32FC3>::operator=(val);
        return *this;
    }
    
    fRgbImg &operator+=(const fRgbPix &val){
        img_t<fRgbPix, CV_32FC3>::operator+=(val);
        return *this;
    }
    fRgbImg &operator-=(const fRgbPix &val){
        img_t<fRgbPix, CV_32FC3>::operator-=(val);
        return *this;
    }
    
    fRgbImg &operator*=(const fRgbPix &val){
        img_t<fRgbPix, CV_32FC3>::operator*=(val);
        return *this;
    }
    fRgbImg &operator/=(const fRgbPix &val){
        img_t<fRgbPix, CV_32FC3>::operator/=(val);
        return *this;
    }
    fRgbImg operator+(const fRgbPix &val){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator+(val);
    }
    fRgbImg operator-(const fRgbPix &val){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator-(val);
    }
    fRgbImg operator*(const fRgbPix &val){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator*(val);
    }
    fRgbImg operator/(const fRgbPix &val){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator/(val);
    }
    fRgbImg &operator=(const fRgbImg &img){
        img_t<fRgbPix, CV_32FC3>::operator=(img);
        return *this;
    }
    fRgbImg &operator+=(const fRgbImg &img){
        img_t<fRgbPix, CV_32FC3>::operator+=(img);
        return *this;
    }
    fRgbImg &operator-=(const fRgbImg &img){
        img_t<fRgbPix, CV_32FC3>::operator-=(img);
        return *this;
    }
    fRgbImg &operator*=(const fRgbImg &img){
        img_t<fRgbPix, CV_32FC3>::operator*=(img);
        return *this;
    }
    fRgbImg &operator/=(const fRgbImg &img){
        img_t<fRgbPix, CV_32FC3>::operator/=(img);
        return *this;
    }
    fRgbImg operator+(const fRgbImg &img){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator+(img);
    }
    fRgbImg operator-(const fRgbImg &img){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator-(img);
    }
    fRgbImg operator*(const fRgbImg &img){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator*(img);
    }
    fRgbImg operator/(const fRgbImg &img){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator/(img);
    }
    fRgbImg operator*(fKernel &ker){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator*(ker);
    }
    
    fRgbImg operator-(){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::operator-();
    }
    
    
    fRgbImg map(fRgbPix f(fRgbPix x)){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::map(f);
    }

    template<typename A> fRgbImg map(fRgbPix f(fRgbPix x, A arg), A arg){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::map(f, arg);
    }
    
    fRgbImg map(fRgbPix f(int x, int y, image_t<fRgbPix, CV_32FC3> *self)){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::map(f);
    }

    template<typename A> fRgbImg map(fRgbPix f(int x, int y, image_t<fRgbPix, CV_32FC3> *self, A arg), A arg){
        return (fRgbImg) img_t<fRgbPix, CV_32FC3>::map(f, arg);
    }
    
    // constructors
    fRgbImg() : img_t<fRgbPix, CV_32FC3>(){};
    fRgbImg(const unsigned w, const unsigned h,
            const int ox=0,   const int oy=0) : img_t<fRgbPix, CV_32FC3>(w, h,ox,oy){};
    
    fRgbImg(const cv::Mat &mat, bool flip=true, bool clone = false) : img_t<fRgbPix, CV_32FC3>(mat, flip, clone){};
    
    // copy constructor
    fRgbImg(const fRgbImg &img) : img_t<fRgbPix, CV_32FC3>(img){};

    fRgbImg(const img_t<fRgbPix, CV_32FC3> &img) : img_t<fRgbPix, CV_32FC3>(img){};
    
    // move constructor
    fRgbImg(fRgbImg &&img) : img_t<fRgbPix, CV_32FC3>(std::move(img)){};

    fRgbImg(img_t<fRgbPix, CV_32FC3> &&img) : img_t<fRgbPix, CV_32FC3>(std::move(img)){};

    // move assignmnet
    fRgbImg &operator=(fRgbImg &&img){
        img_t<fRgbPix, CV_32FC3>::operator=(std::move(img));
        return *this;
    }
};




//==================================================================
// bMonoPix classes 
//==================================================================


class bMonoImg : public img_t<bMonoPix, CV_8UC1> {
    
public:
    
    // casting
    operator fRgbImg();
    operator fMonoImg();
    operator bRgbImg();
    operator fCieImg();
    operator fCmpImg();

    
    // operators
    bMonoImg &operator=(const bMonoPix val){
        img_t<bMonoPix, CV_8UC1>::operator=(val);
        return *this;
    }


    bMonoImg &operator+=(const bMonoPix val){
        img_t<bMonoPix, CV_8UC1>::operator+=(val);
        return *this;
    }
    bMonoImg &operator-=(const bMonoPix val){
        img_t<bMonoPix, CV_8UC1>::operator-=(val);
        return *this;
    }
    bMonoImg &operator*=(const bMonoPix val){
        img_t<bMonoPix, CV_8UC1>::operator*=(val);
        return *this;
    }
    bMonoImg &operator/=(const bMonoPix val){
        img_t<bMonoPix, CV_8UC1>::operator/=(val);
        return *this;
    }
    bMonoImg operator+(const bMonoPix val){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator+(val);
    }
    bMonoImg operator-(const bMonoPix val){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator-(val);
    }
    bMonoImg operator*(const bMonoPix val){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator*(val);
    }
    bMonoImg operator/(const bMonoPix val){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator/(val);
    }
    bMonoImg &operator=(const bMonoImg &img){
        img_t<bMonoPix, CV_8UC1>::operator=(img);
        return *this;
    }
    bMonoImg &operator+=(const bMonoImg &img){
        img_t<bMonoPix, CV_8UC1>::operator+=(img);
        return *this;
    }
    bMonoImg &operator-=(const bMonoImg &img){
        img_t<bMonoPix, CV_8UC1>::operator-=(img);
        return *this;
    }
    bMonoImg &operator*=(const bMonoImg &img){
        img_t<bMonoPix, CV_8UC1>::operator*=(img);
        return *this;
    }
    bMonoImg &operator/=(const bMonoImg &img){
        img_t<bMonoPix, CV_8UC1>::operator/=(img);
        return *this;
    }
    bMonoImg operator+(const bMonoImg &img){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator+(img);
    }
    bMonoImg operator-(const bMonoImg &img){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator-(img);
    }
    bMonoImg operator*(const bMonoImg &img){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator*(img);
    }
    bMonoImg operator/(const bMonoImg &img){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator/(img);
    }
    bMonoImg operator*(fKernel &ker){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator*(ker);
    }
    bMonoImg operator-(){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::operator-();
    }
    
    bMonoImg map(bMonoPix f(bMonoPix x)){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::map(f);
    }
    
    template <typename A> bMonoImg map(bMonoPix f(bMonoPix x, A arg), A arg){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::map(f, arg);
    }
    
    bMonoImg map(bMonoPix f(int x, int y, image_t<bMonoPix, CV_8UC1> *self)){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::map(f);
    }
    
    template<typename A> bMonoImg map(bMonoPix f(int x, int y, image_t<bMonoPix, CV_8UC1> *self, A arg), A arg){
        return (bMonoImg) img_t<bMonoPix, CV_8UC1>::map(f, arg);
    }

        
    // contructor
    bMonoImg() : img_t<bMonoPix, CV_8UC1>(){};
    bMonoImg(const unsigned w, const unsigned h,
             const int ox=0,   const int oy=0) : img_t<bMonoPix, CV_8UC1>(w, h,ox,oy){};
    bMonoImg(const cv::Mat &mat, bool flip=true, bool clone = false) : img_t<bMonoPix, CV_8UC1>(mat, flip, clone){};
    
    // copy constructor
    bMonoImg(const bMonoImg &img) : img_t<bMonoPix, CV_8UC1>(img){};
    bMonoImg(const img_t<bMonoPix, CV_8UC1> &img) : img_t<bMonoPix, CV_8UC1>(img){};

    // move constructor
    bMonoImg(bMonoImg &&img) : img_t<bMonoPix, CV_8UC1>(std::move(img)){};
    bMonoImg(img_t<bMonoPix, CV_8UC1> &&img) : img_t<bMonoPix, CV_8UC1>(std::move(img)){};

    // move assignmnet
    bMonoImg &operator=(bMonoImg &&img){
        img_t<bMonoPix, CV_8UC1>::operator=(std::move(img));
        return *this;
    }

};


class bRgbImg : public img_t<bRgbPix, CV_8UC3>{
    
public:
    
    //operatores
    
    // casting
    operator fMonoImg() ;
    operator bMonoImg();
    operator fRgbImg() ;
    operator fCieImg() ;
    operator fCmpImg();

    
    // operators
    bRgbImg &operator=(const bRgbPix &val){
        img_t<bRgbPix, CV_8UC3>::operator=(val);
        return *this;
    }
    

    bRgbImg &operator+=(const bRgbPix &val){
        img_t<bRgbPix, CV_8UC3>::operator+=(val);
        return *this;
    }
    bRgbImg &operator-=(const bRgbPix &val){
        img_t<bRgbPix, CV_8UC3>::operator-=(val);
        return *this;
    }
    
    bRgbImg &operator*=(const bRgbPix &val){
        img_t<bRgbPix, CV_8UC3>::operator*=(val);
        return *this;
    }
    bRgbImg &operator/=(const bRgbPix &val){
        img_t<bRgbPix, CV_8UC3>::operator/=(val);
        return *this;
    }
    bRgbImg operator+(const bRgbPix &val){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator+(val);
    }
    bRgbImg operator-(const bRgbPix &val){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator-(val);
    }
    bRgbImg operator*(const bRgbPix &val){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator*(val);
    }
    bRgbImg operator/(const bRgbPix &val){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator/(val);
    }
    bRgbImg &operator=(const bRgbImg &img){
        img_t<bRgbPix, CV_8UC3>::operator=(img);
        return *this;
    }
    bRgbImg &operator+=(const bRgbImg &img){
        img_t<bRgbPix, CV_8UC3>::operator+=(img);
        return *this;
    }
    bRgbImg &operator-=(const bRgbImg &img){
        img_t<bRgbPix, CV_8UC3>::operator-=(img);
        return *this;
    }
    bRgbImg &operator*=(const bRgbImg &img){
        img_t<bRgbPix, CV_8UC3>::operator*=(img);
        return *this;
    }
    bRgbImg &operator/=(const bRgbImg &img){
        img_t<bRgbPix, CV_8UC3>::operator/=(img);
        return *this;
    }
    bRgbImg operator+(const bRgbImg &img){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator+(img);
    }
    bRgbImg operator-(const bRgbImg &img){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator-(img);
    }
    bRgbImg operator*(const bRgbImg &img){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator*(img);
    }
    bRgbImg operator/(const bRgbImg &img){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator/(img);
    }
    bRgbImg operator*(fKernel &ker){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator*(ker);
    }
    
    bRgbImg operator-(){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::operator-();
    }
    
    
    bRgbImg map(bRgbPix f(bRgbPix x)){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::map(f);
    }

    template<typename A> bRgbImg map(bRgbPix f(bRgbPix x, A arg), A arg){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::map(f, arg);
    }
    
    bRgbImg map(bRgbPix f(int x, int y, image_t<bRgbPix, CV_8UC3> *self)){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::map(f);
    }

    template<typename A> bRgbImg map(bRgbPix f(int x, int y, image_t<bRgbPix, CV_8UC3> *self, A arg), A arg){
        return (bRgbImg) img_t<bRgbPix, CV_8UC3>::map(f, arg);
    }
    
    
    // constructors
    bRgbImg() : img_t<bRgbPix, CV_8UC3>(){};
    bRgbImg(const unsigned w, const unsigned h,
            const int ox=0,   const int oy=0) : img_t<bRgbPix, CV_8UC3>(w, h,ox,oy){};
    
    bRgbImg(const cv::Mat &mat, bool flip=true, bool clone = false) : img_t<bRgbPix, CV_8UC3>(mat, flip, clone){};
    
    // copy constructors
    bRgbImg(const bRgbImg &img) : img_t<bRgbPix, CV_8UC3>(img){};
    bRgbImg(const img_t<bRgbPix, CV_8UC3> &img) : img_t<bRgbPix, CV_8UC3>(img){};

    // move constructors
    bRgbImg(bRgbImg &&img) : img_t<bRgbPix, CV_8UC3>(std::move(img)){};
    bRgbImg(img_t<bRgbPix, CV_8UC3> &&img) : img_t<bRgbPix, CV_8UC3>(std::move(img)){};

    // move assignmnet
    bRgbImg &operator=(bRgbImg &&img){
        img_t<bRgbPix, CV_8UC3>::operator=(std::move(img));
        return *this;
    }
};




class fCieImg : public img_t<fCiePix, CV_32FC3>{
    
public:
    
    //operatores
    
    // casting
    operator fMonoImg() ;
    operator bMonoImg();
    operator fRgbImg() ;
    operator bRgbImg();
    operator fCmpImg();

    
    // operators
    fCieImg &operator=(const fCiePix &val){
        img_t<fCiePix, CV_32FC3>::operator=(val);
        return *this;
    }
    fCieImg &operator+=(const fCiePix &val){
        img_t<fCiePix, CV_32FC3>::operator+=(val);
        return *this;
    }
    fCieImg &operator-=(const fCiePix &val){
        img_t<fCiePix, CV_32FC3>::operator-=(val);
        return *this;
    }
    fCieImg &operator*=(const fCiePix &val){
        img_t<fCiePix, CV_32FC3>::operator*=(val);
        return *this;
    }
    fCieImg &operator/=(const fCiePix &val){
        img_t<fCiePix, CV_32FC3>::operator/=(val);
        return *this;
    }
    fCieImg operator+(const fCiePix &val){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator+(val);
    }
    fCieImg operator-(const fCiePix &val){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator-(val);
    }
    fCieImg operator*(const fCiePix &val){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator*(val);
    }
    fCieImg operator/(const fCiePix &val){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator/(val);
    }
    fCieImg &operator=(const fCieImg &img){
        img_t<fCiePix, CV_32FC3>::operator=(img);
        return *this;
    }
    fCieImg &operator+=(const fCieImg &img){
        img_t<fCiePix, CV_32FC3>::operator+=(img);
        return *this;
    }
    fCieImg &operator-=(const fCieImg &img){
        img_t<fCiePix, CV_32FC3>::operator-=(img);
        return *this;
    }
    fCieImg &operator*=(const fCieImg &img){
        img_t<fCiePix, CV_32FC3>::operator*=(img);
        return *this;
    }
    fCieImg &operator/=(const fCieImg &img){
        img_t<fCiePix, CV_32FC3>::operator/=(img);
        return *this;
    }
    fCieImg operator+(const fCieImg &img){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator+(img);
    }
    fCieImg operator-(const fCieImg &img){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator-(img);
    }
    fCieImg operator*(const fCieImg &img){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator*(img);
    }
    fCieImg operator/(const fCieImg &img){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator/(img);
    }
    
    fCieImg operator*(fKernel &ker){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator*(ker);
    }
    
    fCieImg operator-(){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::operator-();
    }
    
    fCieImg map(fCiePix f(fCiePix x)){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::map(f);
    }
    
    template<typename A> fCieImg map(fCiePix f(fCiePix x, A arg), A arg){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::map(f, arg);
    }
    
    fCieImg map(fCiePix f(int x, int y, image_t<fCiePix, CV_32FC3> *self)){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::map(f);
    }

    template<typename A> fCieImg map(fCiePix f(int x, int y, image_t<fCiePix, CV_32FC3> *self, A arg), A arg){
        return (fCieImg) img_t<fCiePix, CV_32FC3>::map(f, arg);
    }
    
    // constructors
    fCieImg() : img_t<fCiePix, CV_32FC3>(){};
    fCieImg(const unsigned w, const unsigned h,
            const int ox=0,   const int oy=0) : img_t<fCiePix, CV_32FC3>(w, h,ox,oy){};
    
    fCieImg(const cv::Mat &mat) : img_t<fCiePix, CV_32FC3>(mat){};
    
    // copy constructors
    fCieImg(const fCieImg &img) : img_t<fCiePix, CV_32FC3>(img){};
    fCieImg(const img_t<fCiePix, CV_32FC3> &img) : img_t<fCiePix, CV_32FC3>(img){};

    // move constructors
    fCieImg(fCieImg &&img) : img_t<fCiePix, CV_32FC3>(std::move(img)){};
    fCieImg(img_t<fCiePix, CV_32FC3> &&img) : img_t<fCiePix, CV_32FC3>(std::move(img)){};

    // move assignment
    fCieImg &operator=(fCieImg &&img){
        img_t<fCiePix, CV_32FC3>::operator=(std::move(img));
        return *this;
    }
    
};


// complex image

class fCmpImg : public img_t<fCmpPix, CV_32FC2>{
    
public:
    
    // casting
    operator fMonoImg() ;
    operator bMonoImg();
    operator fRgbImg() ;
    operator bRgbImg() ;
    operator fCieImg() ;
    
    // operators
    fCmpImg &operator=(const fCmpPix &val){
        img_t<fCmpPix, CV_32FC2>::operator=(val);
        return *this;
    }
    
    fCmpImg &operator+=(const fCmpPix &val){
        img_t<fCmpPix, CV_32FC2>::operator+=(val);
        return *this;
    }
    fCmpImg &operator-=(const fCmpPix &val){
        img_t<fCmpPix, CV_32FC2>::operator-=(val);
        return *this;
    }
    
    fCmpImg &operator*=(const fCmpPix &val){
        img_t<fCmpPix, CV_32FC2>::operator*=(val);
        return *this;
    }
    fCmpImg &operator/=(const fCmpPix &val){
        img_t<fCmpPix, CV_32FC2>::operator/=(val);
        return *this;
    }
    fCmpImg operator+(const fCmpPix &val){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator+(val);
    }
    fCmpImg operator-(const fCmpPix &val){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator-(val);
    }
    fCmpImg operator*(const fCmpPix &val){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator*(val);
    }
    fCmpImg operator/(const fCmpPix &val){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator/(val);
    }
    fCmpImg &operator=(const fCmpImg &img){
        img_t<fCmpPix, CV_32FC2>::operator=(img);
        return *this;
    }
    fCmpImg &operator+=(const fCmpImg &img){
        img_t<fCmpPix, CV_32FC2>::operator+=(img);
        return *this;
    }
    fCmpImg &operator-=(const fCmpImg &img){
        img_t<fCmpPix, CV_32FC2>::operator-=(img);
        return *this;
    }
    fCmpImg &operator*=(const fCmpImg &img){
        img_t<fCmpPix, CV_32FC2>::operator*=(img);
        return *this;
    }
    fCmpImg &operator/=(const fCmpImg &img){
        img_t<fCmpPix, CV_32FC2>::operator/=(img);
        return *this;
    }
    fCmpImg operator+(const fCmpImg &img){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator+(img);
    }
    fCmpImg operator-(const fCmpImg &img){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator-(img);
    }
    fCmpImg operator*(const fCmpImg &img){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator*(img);
    }
    fCmpImg operator/(const fCmpImg &img){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator/(img);
    }
    fCmpImg operator*(fKernel &ker){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator*(ker);
    }
    
    fCmpImg operator-(){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::operator-();
    }
    
    
    fCmpImg map(fCmpPix f(fCmpPix x)){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::map(f);
    }
    
    template<typename A> fCmpImg map(fCmpPix f(fCmpPix x, A arg), A arg){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::map(f, arg);
    }
    
    fCmpImg map(fCmpPix f(int x, int y, image_t<fCmpPix, CV_32FC2> *self)){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::map(f);
    }

    template<typename A> fCmpImg map(fCmpPix f(int x, int y, image_t<fCmpPix, CV_32FC2> *self, A arg), A arg){
        return (fCmpImg) img_t<fCmpPix, CV_32FC2>::map(f, arg);
    }
    
    // Complex specific functions
    
    fCmpImg fft();
    fCmpImg ifft();
    fCmpImg fftShift();
    
    
    // constructors
    fCmpImg() : img_t<fCmpPix, CV_32FC2>(){};
    fCmpImg(const unsigned w, const unsigned h, 
            const int ox=0,   const int oy=0) : img_t<fCmpPix, CV_32FC2>(w, h,ox,oy){};
    
    fCmpImg(const cv::Mat &mat) : img_t<fCmpPix, CV_32FC2>(mat){};
    
    // copy constructor
    fCmpImg(const fCmpImg &img) : img_t<fCmpPix, CV_32FC2>(img){};
    fCmpImg(const img_t<fCmpPix, CV_32FC2> &img) : img_t<fCmpPix, CV_32FC2>(img){};

    // move constructor
    fCmpImg(fCmpImg &&img) : img_t<fCmpPix, CV_32FC2>(std::move(img)){};
    fCmpImg(img_t<fCmpPix, CV_32FC2> &&img) : img_t<fCmpPix, CV_32FC2>(std::move(img)){};

    // move assignmnet
    fCmpImg &operator=(fCmpImg &&img){
        img_t<fCmpPix, CV_32FC2>::operator=(std::move(img));
        return *this;
    }
};

} // namespace

#endif

