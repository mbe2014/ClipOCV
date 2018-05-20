#include "copyright.h"

//=================================================================
// img_dat.h - image data class templates.
//
// Description:
// image_t - Root image template class.
//           All images are derived from this class.
//
//
// Assumptions:
//  The pixel type T doesn't contain pointers.
//  Image data is continous (no implicit padding)
//
//=================================================================

#pragma once
#ifndef IMAGE_C_H
#define IMAGE_C_H

#include <string.h>
#include <assert.h>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

namespace clipocv {

//--------------------------------------------
// image_t defintion
// T is the pixel class
// ocvType is OpenCV type (e.g. CV_8UC3)
//--------------------------------------------
template<class T, int ocvType> class image_t {
    
protected:
    cv::Mat mat;                    // OpenCV matte
    unsigned width, height;     // effective width and height
    int orgX, orgY;             // Origin location
    T *pix;                     // Relative to origin !
    
private:
    
public:
    
    // Get attributes
    const cv::Mat &GetMat() const  { return mat;              }
    unsigned  GetWidth()    const  { return width;            }
    unsigned  GetHeight()   const  { return height;           }
    unsigned  GetSize()     const  { return width * height;   }
    T * GetData()           const  { return (T *) mat.data;   }
    
    int GetOrgX()   const { return orgX; }
    int GetOrgY()   const { return orgY; }
    int GetXmin()   const { return  -orgX; }
    int GetYmin()   const { return  -orgY; }
    int GetXmax()   const { return  width  - orgX - 1;      }
    int GetYmax()   const { return  height - orgY - 1;      }
    
    
    
    // Set attributes.
    // Set new origin.  (origin must be inside the image)
    // note that Y coordinate positive direction is south ...
    // note compiler was changed unsignd+signed behviour
    void SetOrigin(const int x, const int y) {
        orgX = x;
        orgY = y;
        
        if (GetData() != (T *)0 ) {
            assert ((orgX >= 0 && orgX < (int) width &&
                     orgY >= 0 && orgY < (int) height));
            pix = (T *) &GetData()[y*(int)width + x];
        }
        else pix = (T *) 0;
    }
    
    void MovOrigin(const int x, const int y) {
        SetOrigin(orgX + x, orgY + y);
    }
    
    
    // indexing operator(s)

    //treat the image as a vector ignoring origin. index between 0 and GetSize()-1
    T &Pix(const unsigned i){
        assert(i < GetSize());
        return GetData()[i];
    }
    
    const T &Pix(const unsigned i) const{
        assert(i < GetSize());
        return GetData()[i];
    }
    
    // 2D ignoring origin indexing operators
    T &aPix(const int x, const int y){
        assert(x >= 0 && x < GetWidth());
        assert(y >= 0 && y < GetHeight());
        return GetData()[y*(int)width + x];
    }
    
    T &aPix(const int x, const int y) const {
        assert(x >= 0 && x < GetWidth());
        assert(y >= 0 && y < GetHeight());
        return GetData()[y*(int)width + x];
    }

    
    // 2D relative to origin indexing operators
    T &Pix(const int x, const int y){
        assert(x >= GetXmin() && x <= GetXmax());
        assert(y >= GetYmin() && y <= GetYmax());
        return pix[y*(int)width + x];
    }
    
    const T &Pix(const int x, const int y) const{
        assert(x >= GetXmin() && x <= GetXmax());
        assert(y >= GetYmin() && y <= GetYmax());
        return pix[y*(int)width + x];
    }
    
    
    // Speical indexing operators
    
    T cPix (int x, int y) {
        if (x <  GetXmin()) x = GetXmin();
        else if (x > GetXmax()) x = GetXmax();
        
        if (y <  GetYmin()) y = GetYmin();
        else if (y > GetYmax()) y = GetYmax();
        
        return pix[y*(int)width + x];
    }
    
    // float subscript indexing - bilinear interpolation.
    T bPix(const float x, const float y) {
        int x1, x2;
        int y1, y2;
        float u, v;
        T a, b, c, d;
        T t1, t2, ret_val;
        
        x1 = (int) x;
        if (x < x1) x1--;
        x2 = x1 + 1;
        u = x - x1;
        
        y1 = (int) y;
        if (y < y1) y1--;
        y2 = y1 + 1;
        v = y - y1;
        
        a = cPix(x1, y1);
        b = cPix(x2, y1);
        c = cPix(x1, y2);
        d = cPix(x2, y2);
        
        t1 = a * (1 - u) + b * u;
        t2 = c * (1 - u) + d * u;
        
        ret_val = t1 * (1 - v) + t2 * v;
        
        return ret_val;
    }
    
    
    // Data initialization operator.
    image_t &operator=(const T val){
        mat = val;
        return *this;
    }
    
    // Assignment operator deep copy.
    image_t &operator=(const image_t &src){
        mat = src.mat.clone();
        width  = src.width;
        height = src.height;
        SetOrigin(src.orgX,src.orgY);
        return *this;
    }
    
    
    // Constructor(s)
    image_t(){
        mat = cv::Mat();	// null image
        width = 0;
        height = 0;
        pix  = (T *)0 ;
        orgX = 0;
        orgY = 0;
    }
    
    image_t(const unsigned w, const unsigned h, const int ox=0, const int oy=0){
        mat = cv::Mat(h,w,ocvType);
        width = w;
        height = h;
        SetOrigin(ox, oy);
        
    }
    
    // types must match
    image_t(const cv::Mat &m, bool flip = true, bool clone = false) {
        assert(ocvType == m.type());  
        if ((ocvType == CV_8UC3 || ocvType == CV_32FC3) && flip) {
                cv::cvtColor(m, mat, cv::COLOR_RGB2BGR);
        }   
        else if (clone) {
            mat = m.clone();
        }
        else {
            mat = m;
        }
        width = mat.cols;
        height = mat.rows;
        SetOrigin(0,0);
    }
    
    // copy constructor - deep copy
    image_t(const image_t &img){
        width  = img.width;
        height = img.height;
        mat = img.mat.clone();
        SetOrigin(img.orgX, img.orgY);
    }
    
    // Distructor
    ~image_t(){
        mat.release();
        width = 0;
        height = 0;
        orgX = 0;
        orgY = 0;
        pix = (T *)0;
    }

    // move constructor - no deep copy
    image_t(image_t &&img){
        width  = img.width;
        height = img.height;
        mat = std::move(img.mat);
        SetOrigin(img.orgX, img.orgY);
    }

    // move assignment operator - no deep copy.
    image_t &operator=(image_t &&src){
        width  = src.width;
        height = src.height;
        mat = std::move(src.mat);
        SetOrigin(src.orgX,src.orgY);
        return *this;
    }

};

} // namespace

#endif


