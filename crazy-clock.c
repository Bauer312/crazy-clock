#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "crazy-clock.h"
#include "libcrazytime.h"

int style = 0;

int main(int argc, char **argv) {
	int freq = 4;

	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-freq") == 0) {
			freq = atoi(argv[i+1]);
			i++;
		}
		if(strcmp(argv[i], "-bin") == 0) {
			style += 1;
		}
		if(strcmp(argv[i], "-oct") == 0) {
			style += 2;
		}
		if(strcmp(argv[i], "-hex") == 0) {
			style += 4;
		}
	}
	if(style == 0) {
		style = 1;
	}

	// Register for the alarm signal
	signal(SIGALRM, getTime);
	
	// Set the alarm interval
	if(setInterval(1000/freq) == -1) {
		perror("setInterval");
	} else {
		// Infinitely pause this thread
		// and wait for the alarm signal
		// to wake us up.
		while(1) pause();
	}
}

void getTime(int signum) {
	if(signum != SIGALRM) return;

	// Get current UNIX time
	time_t currentTime = time(NULL);

	struct tm currentTimeStruct;

	// Convert UNIX time to local time
	localtime_r(&currentTime, &currentTimeStruct);
	printf("%02d:%02d:%02d ",
			currentTimeStruct.tm_hour,
			currentTimeStruct.tm_min,
			currentTimeStruct.tm_sec);

	if((style & 1) == 1) {
		// Convert the local time to binary
		ctime_t bin = getBinary(&currentTimeStruct);
		printf("(B) %s:%s:%s ", bin.hours, bin.minutes, bin.seconds);
	}

	if((style & 2) == 2) {
		// Convert the local time to octal
		ctime_t oct = getOctal(&currentTimeStruct);
		printf("(O) %s:%s:%s ", oct.hours, oct.minutes, oct.seconds);
	}

	if((style & 4) == 4) {
		// Convert the local time to hexadecimal
		ctime_t hex = getHexadecimal(&currentTimeStruct);
		printf("(H) %s:%s:%s ", hex.hours, hex.minutes, hex.seconds);
	}
	printf("\n");
}

int setInterval(int milliseconds) {
	struct itimerval newInterval;

	newInterval.it_interval.tv_sec = milliseconds / 1000;
	newInterval.it_interval.tv_usec = (milliseconds % 1000) * 1000L;

	newInterval.it_value.tv_sec = milliseconds / 1000;
	newInterval.it_value.tv_usec = (milliseconds % 1000) * 1000L;

	return setitimer(ITIMER_REAL, &newInterval, NULL);
}
