#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "gray.h"

int main(int argc, char *argv[])
{
  FILE *f = stdin;
  if (argc == 3){
    f = fopen(argv[2], "r");
  }
  image *img = read_image(f);
  int num_threads = atoi(argv[1]);

  struct timeval start;
  struct timeval stop;
  gettimeofday(&start, NULL);
  grayscale_par(img, num_threads);
  gettimeofday(&stop, NULL);
  unsigned long int t0 = start.tv_sec * 1000000 + start.tv_usec;
  unsigned long int t1 = stop.tv_sec * 1000000 + stop.tv_usec;
  fprintf(stderr, "image processing time (usec): %lu\n", t1-t0);

  print_as_p3(img);
  free(img->pixels);
  free(img);
  fclose(f);
  return 0;
}
