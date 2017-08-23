#include "copyright.h"

/*=================================================================*
 * pnm.h - pnm format header
 *
 * Description:
 *   PPM, PGM, and private PFM, PCM format definition.
 *
 *=================================================================*/

#pragma once
#ifndef PNM_H
#define PNM_H

#include <stdint.h>

namespace clipocv {

/*
 * define fomrat magic numbers
 */

#define PGM 5			/* gray scale raw format                 */
#define PPM 6			/* 24-bit color raw format               */
#define PFM 7			/* new (private) gray scale float format */
#define PCM 8			/* new (private) color float format      */

static unsigned s_psize[] = {
    /* 0 */ 0,
    /* 1 */ 0,
    /* 2 */ 0,
    /* 3 */ 0,
    /* 4 */ 0,
    /* 5 */ 1 * sizeof(char),
    /* 6 */ 3 * sizeof(char),
    /* 7 */ 1 * sizeof(float),
    /* 8 */ 3 * sizeof(float)
};

#define PSIZE(t)    (s_psize[t])

/*
 * define image structure
 */

typedef struct {
    int type;                         /* image type               */
    int width;                        /* image width              */
    int height;                       /* image height             */
    int maxval;                       /* max value for band       */
    uint8_t *data;              /* pixel data               */
} pnm_t;

/*
 * function prototypes
 */

pnm_t   *read_image(FILE *fp);
void    write_image(FILE *fp, pnm_t *image);
pnm_t   *create_image(int width, int height, int type);
void	free_image(pnm_t *img);

} // namespace

#endif










