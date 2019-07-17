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
    cv::Mat mat;                            // OpenCV image  
    int orgX, orgY;                         // Image origin in absolute coordinates
    T *pix;                                 // Relative to origin !

    cv::Mat roi;                            // OpenCV roi instance
    unsigned roiX, roiY;                    // Roi top-left corner in absolute coordinates
    
private:
    
public:
    
    // Get attributes
    const cv::Mat &GetMat() const  { return mat;                                }
    unsigned  GetWidth()    const  { return mat.cols;                           }
    unsigned  GetHeight()   const  { return mat.rows;                           }
    unsigned  GetSize()     const  { return GetWidth() * GetHeight();           }
    T * GetData()           const  { return (T *) mat.data;                     }
    T * GetLine(unsigned y) const  { return ((T *) mat.data) + y*GetWidth();    }


    const cv::Mat &GetRoiMat() const  { return roi;                             }
    unsigned  GetRoiWidth()    const  { return roi.cols;                        }      
    unsigned  GetRoiHeight()   const  { return roi.rows;                        }
    unsigned  GetRoiSize()     const  { return GetRoiWidth() * GetRoiHeight();  }
    T * GetRoiData()           const  { return (T *) roi.data;                  }    
    T * GetRoiLine(unsigned y) const  { return ((T *) roi.data) + y*GetWidth(); }

    int GetOrgX()   const { return orgX; }
    int GetOrgY()   const { return orgY; }
    int GetRoiX()   const { return roiX; }
    int GetRoiY()   const { return roiY; }

    int GetXmin()   const { return  -orgX; }
    int GetYmin()   const { return  -orgY; }
    int GetXmax()   const { return  GetRoiWidth()  - orgX  - 1;      }
    int GetYmax()   const { return  GetRoiHeight() - orgY  - 1;      }
    
    
    
    // Set new origin.  (currently, origin must be inside the ROI)
    // note that Y coordinate positive direction is south
    // Origin is relative to ROI
    void SetOrigin(const int x, const int y) {
        orgX = x;
        orgY = y;
        
        if (GetRoiData() != (T *)0 ) {
            assert (orgX >= 0 && orgX < (int) GetRoiWidth());
            assert (orgY >= 0 && orgY < (int) GetRoiHeight());
            pix = (T *) &GetRoiData()[y*(int) GetWidth() + x];
        }
        else pix = (T *) 0;
    }

    // move origin 
    void MovOrigin(const int dx, const int dy) {
        SetOrigin(orgX + dx, orgY + dy);
    }
    

    // set ROI - ROI is a window within an image - not a new image instance
    // coordinates are alwase absolute coordinate of the image.
    void SetRoi(const unsigned x, const unsigned y, const unsigned w, const unsigned h){
        if (GetWidth() > 0 && GetHeight() > 0) {
		assert (x < GetWidth() && y < GetHeight());
        	assert (x+w <= GetWidth() && y+h <= GetHeight());

        	roi = mat(cv::Rect(x,y, w,h));
        	roiX = x;
        	roiY = y;
        	SetOrigin(0,0); // previous origin if any is not valid anymore
	}
	else {
	    roiX = 0;
	    roiY = 0;
	    roi = mat;
	}
    }

    void SetRoi(cv::Rect rect){
        SetRoi(rect.x, rect.y, rect.width, rect.height);
    }
 
    // move ROI, origin moves with ROI
    void MoveRoi(int dx, int dy) {
        SetRoi(roiX+dx, roiY+dy, GetRoiWidth(), GetRoiHeight());
        SetOrigin(orgX, orgY); // relative to new ROI
    }

    // indexing operator(s)

    //treat the image as a vector ignoring origin, ignoring ROI. index between 0 and GetSize()-1
    T &Pix(const unsigned i){
        assert(i < GetSize());
        return GetData()[i];
    }
    
    const T &Pix(const unsigned i) const{
        assert(i < GetSize());
        return GetData()[i];
    }
    
    // 2D absolute indexing ignoring origin, ignoring ROI, indexing operators
    T &aPix(const int x, const int y){
        assert(x >= 0 && x < (int) GetWidth());
        assert(y >= 0 && y < (int) GetHeight());
        return GetData()[y*(int)GetWidth() + x];
    }
    
    T &aPix(const int x, const int y) const {
        assert(x >= 0 && x < (int) GetWidth());
        assert(y >= 0 && y < (int) GetHeight());
        return GetData()[y*(int)GetWidth() + x];
    }

    
    // 2D relative to origin indexing operators, check against ROI
    T &Pix(const int x, const int y){
        assert(x >= GetXmin() && x <= GetXmax());
        assert(y >= GetYmin() && y <= GetYmax());
        return pix[y*(int)GetWidth() + x];
    }
    
    const T &Pix(const int x, const int y) const{
        assert(x >= GetXmin() && x <= GetXmax());
        assert(y >= GetYmin() && y <= GetYmax());
        return pix[y*(int)GetWidth() + x];
    }
    
    
    // Speical indexing operators
    
    T cPix (int x, int y) {
        if (x <  GetXmin()) x = GetXmin();
        else if (x > GetXmax()) x = GetXmax();
        
        if (y <  GetYmin()) y = GetYmin();
        else if (y > GetYmax()) y = GetYmax();
        
        return pix[y*(int)GetWidth() + x];
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
    
    
    // Data initialization operator. Only the ROI is assigned
    image_t &operator=(const T val){
        roi = val;
        return *this;
    }
    
    // Assignment operator deep copy. Entire image is assigned
    image_t &operator=(const image_t &src){
        mat = src.mat.clone();
        SetRoi(src.roiX,src.roiY,src.GetRoiWidth(),src.GetRoiHeight());
        SetOrigin(src.orgX, src.orgY);
        return *this;
    }
    
    
    // Constructor(s)
    image_t(){
        mat = cv::Mat();	// null image
        pix  = (T *)0 ;
        SetRoi(0,0,GetWidth(),GetHeight());
        SetOrigin(0, 0); 
    }
    
    image_t(const unsigned w, const unsigned h, const int ox=0, const int oy=0){
        mat = cv::Mat(h,w,ocvType);
        SetRoi(0,0, GetWidth(), GetHeight());
        SetOrigin(ox, oy); 
    }
    
    // types must match
    image_t(const cv::Mat &m, bool flip = true, bool clone = false) {
        assert(ocvType == m.type());  
        if ((ocvType == CV_8UC3 || ocvType == CV_32FC3) && flip) {
                cv::cvtColor(m, mat, cv::COLOR_RGB2BGR);
                SetRoi(0,0,GetWidth(),GetHeight());
        }   
        else if (clone) {
            mat = m.clone();
            SetRoi(0,0,GetWidth(),GetHeight());
        }
        else {
            mat = m;
            SetRoi(0,0,GetWidth(),GetHeight());
        }
        SetOrigin(0,0);
    }
    
    // copy constructor - deep copy - entire image is copied
    image_t(const image_t &img){
        mat = img.mat.clone();
        SetRoi(img.roiX,img.roiY,img.GetRoiWidth(),img.GetRoiHeight());
        SetOrigin(img.orgX, img.orgY);
    }
    
    // Distructor
    ~image_t(){
        mat.release();
        roi.release();
        orgX = 0;
        orgY = 0;
        roiX = 0;
        roiY = 0;
        pix = (T *)0;
    }

    // move constructor - no deep copy - Entire image is moved
    image_t(image_t &&img){
        mat = std::move(img.mat);
        SetRoi(img.roiX,img.roiY,img.GetRoiWidth(),img.GetRoiHeight());
        SetOrigin(img.orgX, img.orgY);
    }

    // move assignment operator - Entire image is moved
    image_t &operator=(image_t &&img){
        mat = std::move(img.mat);
        SetRoi(img.roiX,img.roiY,img.GetRoiWidth(),img.GetRoiHeight());
        SetOrigin(img.orgX,img.orgY);
        return *this;
    }

};

} // namespace

#endif


