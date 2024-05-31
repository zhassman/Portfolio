#ifndef _gray_HEADER_H_
#define _gray_HEADER_H_
#include <stdio.h>
#include <math.h>

typedef struct rgb {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} rgb;

typedef struct image {
  unsigned int width;
  unsigned int height;
  struct rgb *pixels;
} image;

typedef struct par_input{
  struct rgb *pixels;
  int count;
} par_input;

int luminance(struct rgb c);

struct rgb grayscale(struct rgb c);

int same_image(struct image *img1, struct image *img2);

int is_grayscale(struct image *img);

struct image *read_image(FILE *f);

void grayscale_seq(struct image *img);

void print_as_p3(image *img);

void *grayscale_par_helper(void *input);

void grayscale_par(struct image *img, unsigned int n_threads);

#endif
