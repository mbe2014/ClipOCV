#include "copyright.h"

//=================================================================
// pnm_env.h - C++ envelope for portable 'PNM' file format.
//
// Description:
//
//=================================================================


#pragma once
#ifndef PNM_ENV_H
#define PNM_ENV_H

#include <stdint.h>
#include "image.h"
#include "pnm.h"

namespace clipocv {

class pnm {
    pnm_t *pnm_img;
    
public:
    
    // I/O
    
    pnm &Read(const char *fname);
    pnm &Read(FILE *fp);
    void Write(const char *fname);
    void Write(FILE *fp);
    
    // Operators - from internal data type to pnm
    
    // PFM - float float scale image.
    
    pnm &operator= (const fMonoImg &img) {
        pnm_img->width = img.GetWidth();
        pnm_img->height = img.GetHeight();
        pnm_img->type = PFM;
        pnm_img->maxval = 0;  // not applicable
        
        pnm_img->data = (uint8_t *) realloc(pnm_img->data, img.GetSize()*PSIZE(PFM));
        
        float *p = (float *) pnm_img->data;
        for(unsigned i=0; i<img.GetSize(); i++)
            *p++ = (float) img.Pix(i);
        
        return *this;
    }
    
    // PCM - float color image.
    
    pnm &operator= (const fRgbImg &img) {
        pnm_img->width = img.GetWidth();
        pnm_img->height = img.GetHeight();
        pnm_img->type = PCM;
        pnm_img->maxval = 0; // not applicable
        
        pnm_img->data = (uint8_t *) realloc(pnm_img->data, img.GetSize()*PSIZE(PCM));
        
        float *p = (float *) pnm_img->data;
        for(unsigned i=0; i<img.GetSize(); i++){
            *p++ = img.Pix(i).Red();
            *p++ = img.Pix(i).Green();
            *p++ = img.Pix(i).Blue();
        }
        return *this;
    }
    
    
    // byte image assignment
    
    // PGM - byte color image.
    
    pnm &operator= (const bMonoImg &img) {
        pnm_img->width = img.GetWidth();
        pnm_img->height = img.GetHeight();
        pnm_img->type = PGM;
        pnm_img->maxval = 255;
        
        pnm_img->data = (uint8_t *) realloc(pnm_img->data, img.GetSize()*PSIZE(PGM));
        
        uint8_t *p = (uint8_t *) pnm_img->data;
        for(unsigned i=0; i<img.GetSize(); i++)
            *p++ = (uint8_t) img.Pix(i);
        
        return *this;
    }
    
    // PPM - byte color image.
    
    pnm &operator= (const bRgbImg &img) {
        pnm_img->width = img.GetWidth();
        pnm_img->height = img.GetHeight();
        pnm_img->type = PPM;
        pnm_img->maxval = 255;
        
        pnm_img->data = (uint8_t *) realloc(pnm_img->data, img.GetSize()*PSIZE(PPM));
        
        uint8_t *p = (uint8_t *) pnm_img->data;
        for(unsigned i=0; i<img.GetSize(); i++){
            *p++ = img.Pix(i)[0];
            *p++ = img.Pix(i)[1];
            *p++ = img.Pix(i)[2];
        }
        return *this;
    }
    
    
    // casting operators - from all types of PNM to
    // fMonoImg , fRgbImg, bMonoImg, bRgmImg, fCieImg, fCmpImg.
    
    
    // ========= Float images ============
    
    // cast to float scale image.
    
    operator fMonoImg(){
        unsigned i;
        float *fltp;
        uint8_t *chrp;
        
        fMonoImg tmp(pnm_img->width, pnm_img->height);
        
        switch (pnm_img->type) {
            case PGM:  // byte float-scale.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i) = (float) *chrp++;
                break;
                
            case PFM: // float float-scale
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i) =  *fltp++;
                break;
                
            case PPM: // byte rgb - get Y component on CIE XYZ system.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, chrp+=3)
                    tmp.Pix(i) = (float)*chrp     * RedToY   + // red
                    (float)*(chrp+1) * GreenToY + // green;
                    (float)*(chrp+2) * BlueToY;   // blue
                break;
                
            case PCM: // float rgb - get Y component on CIE XYZ system.
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, fltp+=3)
                    tmp.Pix(i) = *fltp     * RedToY   + // red
                    *(fltp+1) * GreenToY + // green;
                    *(fltp+2) * BlueToY;   // blue
                break;
                
            default :
                assert(0);
                break;
        }
        return tmp;
    }
    
    
    // cast to color image
    
    operator fRgbImg(){
        unsigned i;
        float *fltp;
        uint8_t *chrp;
        
        fRgbImg tmp(pnm_img->width, pnm_img->height);
        
        switch (pnm_img->type) {
            case PGM:  // byte float-scale.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i)   = fRgbPix((float) *chrp++);
                break;
                
            case PFM:  // float float-scale
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i)   = fRgbPix(*fltp++);
                break;
                
            case PPM: // byte rgb
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, chrp+=3)
                    tmp.Pix(i) = fRgbPix((float) *chrp,			// red
                                         (float) *(chrp+1),		// green;
                                         (float) *(chrp+2));		// blue
                break;
                
            case PCM: // float rgb
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++,fltp+=3)
                    tmp.Pix(i) = fRgbPix(*fltp,					// red
                                         *(fltp+1),				// green;
                                         *(fltp+2));				// blue
                break;
                
            default :
                assert(0);
                break;
        }
        
        return tmp;
    }
    
    // cast to CIE color image (through fRgbPix).
    
    operator fCieImg(){
        unsigned i;
        float *fltp;
        uint8_t *chrp;
        
        fCieImg tmp(pnm_img->width, pnm_img->height);
        
        switch (pnm_img->type) {
            case PGM:  // byte float-scale.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++){
                    tmp.Pix(i)   = fRgbPix((float) *chrp++);
                }
                break;
                
            case PFM:  // float float-scale
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i)   = fRgbPix(*fltp++);
                break;
                
            case PPM: // byte rgb
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, chrp+=3)
                    tmp.Pix(i) = fRgbPix((float) *chrp,			// red
                                         (float) *(chrp+1),		// green;
                                         (float) *(chrp+2));		// blue
                break;
                
            case PCM: // float rgb
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++,fltp+=3)
                    tmp.Pix(i) = fRgbPix(*fltp,					// red
                                         *(fltp+1),				// green;
                                         *(fltp+2));				// blue
                break;
                
            default :
                assert(0);
                break;
        }
        
        return tmp;
    }
    
    // cast to complex image
    
    operator fCmpImg(){
        unsigned i;
        float *fltp;
        uint8_t *chrp;
        
        fCmpImg tmp(pnm_img->width, pnm_img->height);
        
        switch (pnm_img->type) {
            case PGM:  // byte float-scale.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i) = (float) *chrp++;
                break;
                
            case PFM: // float float-scale
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i) =  *fltp++;
                break;
                
            case PPM: // byte rgb - get Y component on CIE XYZ system.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, chrp+=3)
                    tmp.Pix(i) = (float)*chrp     * RedToY   + // red
                    (float)*(chrp+1) * GreenToY + // green;
                    (float)*(chrp+2) * BlueToY;   // blue
                break;
                
            case PCM: // float rgb - get Y component on CIE XYZ system.
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, fltp+=3)
                    tmp.Pix(i) = *fltp     * RedToY   + // red
                    *(fltp+1) * GreenToY + // green;
                    *(fltp+2) * BlueToY;   // blue
                break;
                
            default :
                assert(0);
                break;
        }
        return tmp;
    }
    

    
    // ========= Byte images ============
    
    // cast to byte  image.
    
    operator bMonoImg(){
        unsigned i;
        float *fltp;
        uint8_t *chrp;
        
        bMonoImg tmp(pnm_img->width, pnm_img->height);
        
        switch (pnm_img->type) {
            case PGM:  // byte gray-scale.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i) = (uint8_t) *chrp++;
                break;
                
            case PFM: // float gray-scale
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i) =  (uint8_t) (*fltp++ + 0.5);
                break;
                
            case PPM: // byte rgb - get Y component on CIE XYZ system.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, chrp+=3)
                    tmp.Pix(i) = (uint8_t)
                    ((float)* chrp    * RedToY   + // red
                     (float)*(chrp+1) * GreenToY + // green;
                     (float)*(chrp+2) * BlueToY);   // blue
                break;
                
            case PCM: // float rgb - get Y component on CIE XYZ system.
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, fltp+=3)
                    tmp.Pix(i) = (uint8_t)
                    (* fltp    * RedToY   + // red
                     *(fltp+1) * GreenToY + // green;
                     *(fltp+2) * BlueToY);   // blue
                break;
                
            default :
                assert(0);
                break;
        }
        return tmp;
    }
    
    
    // cast to color image
    
    operator bRgbImg(){
        unsigned i;
        float *fltp;
        uint8_t *chrp;
        
        bRgbImg tmp(pnm_img->width, pnm_img->height);
        
        switch (pnm_img->type) {
            case PGM:  // byte float-scale.
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i)   = bRgbPix(*chrp++);
                break;
                
            case PFM:  // float float-scale
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++)
                    tmp.Pix(i)   = bRgbPix((uint8_t) (*(fltp++) + 0.5));
                break;
                
            case PPM: // byte rgb
                chrp = (uint8_t *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++, chrp+=3)
                    tmp.Pix(i) = bRgbPix(* chrp,			// red
                                         *(chrp+1),		// green;
                                         *(chrp+2));		// blue
                break;
                
            case PCM: // float rgb
                fltp = (float *) pnm_img->data;
                for(i=0; i<tmp.GetSize(); i++,fltp+=3)
                    tmp.Pix(i) = bRgbPix((uint8_t) (*fltp + 0.5),		// red
                                         (uint8_t) (*(fltp+1)+0.5),	// green;
                                         (uint8_t) (*(fltp+2)+0.5));	// blue
                break;
                
            default :
                assert(0);
                break;
        }
        
        return tmp;
    }
    
    // constructors
    
    pnm(char *fname) {
        Read(fname);
    }
    
    pnm(FILE *fp) {
        Read(fp);
    }
    
    // constructors - per supported outpur type !
    pnm(const fMonoImg &img){
        pnm_img = create_image(img.GetWidth(), img.GetHeight(), PFM);
        *this = img;
    }
    
    pnm(const fRgbImg &img){
        pnm_img = create_image(img.GetWidth(), img.GetHeight(), PCM);
        *this = img;
    }
    
    // byte images - used for exporting only.
    
    pnm(const bMonoImg &img){
        pnm_img = create_image(img.GetWidth(), img.GetHeight(), PGM);
        *this = img;
    }
    
    pnm(const bRgbImg &img){
        pnm_img = create_image(img.GetWidth(), img.GetHeight(), PPM);
        *this = img;
    }
    
    
    // distructor
    
    ~pnm() {
        free_image(pnm_img);
    }
    
};

} // namespace

#endif






