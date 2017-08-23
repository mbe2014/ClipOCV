#include "copyright.h"

/*=================================================================*
 * pnm.c - pnm rutines
 *
 * Description:
 *   Creat, Free, Read, Write PNM raw file formats (pgm, ppm)
 *   and private extention for the PNM family.
 *
 *=================================================================*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "error_msg.h"
#include "pnm.h"

namespace clipocv {

/*
 * create_image - create new image according to input parameters
 */

pnm_t *create_image(int width, int height, int type)
{
    static pnm_t *newimg;
    
    if ((newimg = (pnm_t *) malloc(sizeof (pnm_t))) == NULL){
        error_msg("pnm: create_image - malloc failed",0);
        clip_exception(ERR_MALLOC);
    }
    
    newimg->type = type;
    newimg->width = width;
    newimg->height = height;
    newimg->maxval = 255;
    
    if ((newimg->data = (uint8_t *) malloc(width * height * PSIZE(type))) == NULL){
        error_msg("pnm: create_image - malloc failed",0);
        clip_exception(ERR_MALLOC);
    }
    
    return newimg;
}


/*
 * free image
 */

void free_image(pnm_t *img)
{
    if (img->data != NULL)
        free(img->data);
    free(img);
}


/*
 * read_image -  read pnm format image
 */

pnm_t *read_image(FILE *fp)
{
    static pnm_t *image;
    static char comment[1024]; // @@@ can crash
    
    if ((image = (pnm_t *) malloc(sizeof(pnm_t))) == NULL){
        error_msg("pnm: read_image - malloc failed",0);
        clip_exception(ERR_MALLOC);
    }
    
    
    if (fscanf(fp,"P%d\n", &image->type) !=1) {
        error_msg("Pnm: rw: Not A pnm file",0);
        clip_exception(ERR_UNKNOWN_FORMAT);
    }
    
    if (PSIZE(image->type) <= 0 ) {
        error_msg("Pnm: rw: Pnm type %d - not supported",image->type);
        clip_exception(ERR_UNKNOWN_FORMAT);
    }
    
    
    while(fscanf(fp,"#%[^\n]\n",comment) > 0);
    
    fscanf(fp,"%u%u\n", &image->width, &image->height);
    fscanf(fp,"%u%*c",   &image->maxval);   // force the new-line to be one char
    
    if((image->data = (uint8_t *)
        malloc(image->width * image->height * PSIZE(image->type))) == NULL){
        error_msg("pnm: read_image - malloc failed",0);
        clip_exception(ERR_MALLOC);
    }
    
    fread(image->data,
          image->width * image->height,
          PSIZE(image->type),
          fp);
    
    return image;
}


/*
 * write-image - write pnm format image
 */

void write_image(FILE *fp, pnm_t *image)
{
    fprintf(fp,"P%d\n", image->type);
    fprintf(fp,"%u %u\n", image->width, image->height);
    fprintf(fp,"%u%c", image->maxval,10);   // force a ^J newline
    
    fwrite(image->data,
           image->width * image->height,
           PSIZE(image->type),
           fp);
}


} // namespace
