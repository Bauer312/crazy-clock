#ifndef _LIBCRAZYCLOCK_H
#define _LIBCRAZYCLOCK_H

#include <string.h>
#include <time.h>

typedef struct ctime_t {
	char hours[6];
	char minutes[7];
	char seconds[7];
} ctime_t;

ctime_t getBinary(struct tm *curTime);
ctime_t getOctal(struct tm *curTime);
ctime_t getHexadecimal(struct tm *curTime);

#endif
