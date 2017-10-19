#include "copyright.h"
#include "error_msg.h"

//=================================================================
// pnm_env.cxx - C++ envelope portable 'any' file format.
//
// Description:
//	This file encapsulate the pnm C code. This method is
//      applicable for existing C code for other formats as well.
//
//=================================================================

#include <stdio.h>
#include <stdlib.h>

#include "pnm_env.h"

namespace clipocv {


//===============================
// Read - read Pnm format files
//================================

pnm &pnm::Read(FILE *fp)
{
    if ((pnm_img = read_image(fp)) == NULL) {
        error_msg("pnm::Read(FILE *) - failed",0);
        clip_exception(ERR_READ);
    }
    return *this;
}


pnm &pnm::Read(const char *fname)
{
    FILE *fp;
    
    if ((fp = fopen(fname,"rb")) == NULL){
        error_msg("pnm::Read - open(%s) failed", (unsigned long) fname);
        clip_exception(ERR_OPEN);
    }
    
    pnm &retval = Read(fp);
    fclose(fp);
    
    return retval;
}


//================================
// Write - write pnm format image
//================================

void pnm::Write(FILE *fp)
{
    write_image(fp,pnm_img);
}

void pnm::Write(const char *fname)
{
    FILE *fp;
    
    if ((fp = fopen(fname,"wb")) == NULL){
        error_msg("pnm::Write - open(%s) failed", (unsigned long) fname);
        clip_exception(ERR_OPEN);
    }
    Write(fp);
    fclose(fp);
}

} // namespace

