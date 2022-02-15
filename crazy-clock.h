#ifndef CRAZYCLOCK_H
#define CRAZYCLOCK_H

#include "constants.h"

void getTime(int signum);
int setInterval(int milliseconds);
void cleanup();

#endif
