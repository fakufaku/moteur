#include "microtime.h"

double microtime (void) {

  struct timeval tp;
  long sec = 0L;
  double msec = 0.0;

  if (gettimeofday((struct timeval *)&tp, NULL) == -1) {
    perror("gettimeofday");
    exit(-1);
  }

  if (msec >= 1.0) msec -= (long)msec;

  sec = tp.tv_sec;
  msec = (double)(tp.tv_usec) / (double)MICRO_IN_SEC;

  return (double)sec + msec;

}
