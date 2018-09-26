#ifndef _MICROTIME_
#define _MICROTIME_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#define MICRO_IN_SEC 1000000.00

double microtime (void);

#endif
