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
    static char *comment; 
    
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
    
    
    while(fscanf(fp,"#%m[^\n]\n",&comment) > 0) free(comment);
    
    if (fscanf(fp,"%d%d\n", &image->width, &image->height) != 2) {
        error_msg("Pnm: rw: Not A pnm file",0);
        clip_exception(ERR_UNKNOWN_FORMAT);
    }

    if (fscanf(fp,"%d%*c",   &image->maxval) != 1) {   // force the new-line to be one char
        error_msg("Pnm: rw: Not A pnm file",0);
        clip_exception(ERR_UNKNOWN_FORMAT);
    }
    
    if((image->data = (uint8_t *)
        malloc(image->width * image->height * PSIZE(image->type))) == NULL){
        error_msg("pnm: read_image - malloc failed",0);
        clip_exception(ERR_MALLOC);
    }
    
    if (fread(image->data,
              PSIZE(image->type),
              image->width * image->height,
              fp) != (unsigned) image->width * image->height) {
        error_msg("Pnm: rw: corrupted image file",0);
        clip_exception(ERR_UNKNOWN_FORMAT);
    }
    
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
           PSIZE(image->type),
           image->width * image->height,
           fp);
}


} // namespace
