#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include "gray.h" 

int luminance(struct rgb c){
// compute the luminance of the given color (see PDF for formula)
  float sum = (0.2126 * c.red) + (0.7152 * c.green) + (0.0722 * c.blue);
  return (int)floor(sum);
}

struct rgb grayscale(struct rgb c){
// compute the grayscale projection of given color (see PDF)
  int lum = luminance(c);
  rgb result = {0,0,0};
  result.red = lum;
  result.green = lum;
  result.blue = lum;
  return result;
}

int same_image(struct image *img1, struct image *img2){
// test if two images are logically the same
  if (img1->width != img2->width){
    return 0;
  }
  if (img1->height != img2->height){
    return 0;
  }
  int size = (img1->width) * (img1->height);
  for (int i = 0; i < size; i++){
    rgb curr_p1 = img1->pixels[i];
    rgb curr_p2 = img2->pixels[i];
    if (curr_p1.red != curr_p2.red){
      return 0;
    }
    if (curr_p1.green != curr_p2.green){
      return 0;
    }
    if (curr_p1.blue != curr_p2.blue){
      return 0;
    }
  }
  return 1;
}

int is_grayscale(struct image *img){
// return true if every pixel in image is a shade of gray
  int size = img->width * img->height;
  for (int i = 0; i < size; i++){
    rgb curr = img->pixels[i];
    int red = curr.red;
    if (red != curr.green){
      return 0;
    }
    if (red != curr.blue){
      return 0;
    }
  }
  return 1;
}

struct image *read_image(FILE *f){
// read a P3 or P6 from given file (possibly stdin)
// allocate and populate an image struct, return pointer to it
  char *type = (char*)malloc(3);
  int width;
  int height;
  int depth;
  fscanf(f, "%s %d %d %d ", type, &width, &height, &depth);
  image *img = (image*)malloc(sizeof(image));
  img->width = width;
  img->height = height;
  rgb *pixels = (rgb*)malloc(width * height * sizeof(rgb));
  img->pixels = pixels;

  int size = width * height;
  if (strcmp(type, "P3") == 0){
    for (int i = 0; i < size; i++){
      rgb pixel; 
      unsigned int r;
      unsigned int g;
      unsigned int b;
      fscanf(f, "%u %u %u", &r, &g, &b);
      pixel.red = (unsigned char)r;
      pixel.green = (unsigned char)g;
      pixel.blue = (unsigned char)b;
      img->pixels[i] = pixel;
    }
  }
  else if (strcmp(type, "P6") == 0){
    for (int i = 0; i < size; i++){
      rgb pixel;
      pixel.red = getc(f);
      pixel.green = getc(f);
      pixel.blue = getc(f);
      img->pixels[i] = pixel;
    }
  }
  free(type);
  return img;
}

void grayscale_seq(struct image *img){
// convert image to grayscale in place
// no allocations, no threads
  int size = img->width * img->height;
  for (int i = 0; i < size; i ++){
    img->pixels[i] = grayscale(img->pixels[i]);
  }
}

void print_as_p3(image *img){
// prints an image struct as a P3 file
  printf("P3\n%d %d\n255\n", img->width, img->height);
  for (int i = 0; i < img->width * img->height; i++){
    rgb curr = img->pixels[i];
    printf("%d %d %d\n", curr.red, curr.green, curr.blue);
  }
}

void *grayscale_par_helper(void *input){
// converts pixels to grayscale using a par_input struct
  par_input *in = (par_input*)input;
  for (int i = 0; i < in->count; i++){
    in->pixels[i] = grayscale(in->pixels[i]);
  }
  free(in);
  return NULL;
}

void grayscale_par(struct image *img, unsigned int n_threads){
// convert image to grayscale in place in parallel
// no allocations, as many threads as specified
  int size = img->width * img->height;
  pthread_t tids[n_threads];
  int iter_len = size / n_threads;
  int leftover = size % n_threads;
  int start = 0;
  for (int i = 0; i < n_threads; i++){
    int current_iter_len = iter_len;
    if (leftover > 0){
      current_iter_len++;
      leftover--;
    }
    par_input *in = (par_input*)malloc(sizeof(par_input));
    in->pixels = img->pixels + start;
    in->count = current_iter_len;
    start += current_iter_len;
    pthread_create(&tids[i], NULL, grayscale_par_helper, in);
  }
  for (int i = 0; i < n_threads; i++){
    pthread_join(tids[i], NULL);
  }
}
