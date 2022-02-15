#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "crazy-clock.h"
#include "display.h"
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
		if(strcmp(argv[i], "-dec") == 0) {
			style += 8;
		}
	}
	if(style == 0) {
		style = 1;
	}

	// Register for the alarm signal
	signal(SIGALRM, getTime);
	
	// Initialize the screen for ncurses
  initialize_display();

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
	char tempDisplay[32];

	// Convert UNIX time to local time
	localtime_r(&currentTime, &currentTimeStruct);

	if((style & 1) == 1) {
		// Print the local time in binary
		ctime_t bin = getBinary(&currentTimeStruct);
		sprintf(tempDisplay, "(B) %s:%s:%s\n",
				bin.hours, bin.minutes, bin.seconds);
    add_display_text(tempDisplay);
	}

	if((style & 2) == 2) {
		// Print the local time in octal
		ctime_t oct = getOctal(&currentTimeStruct);
		sprintf(tempDisplay, "(O) %s:%s:%s\n",
				oct.hours, oct.minutes, oct.seconds);
    add_display_text(tempDisplay);
	}

	if((style & 4) == 4) {
		// Print the local time in hexadecimal
		ctime_t hex = getHexadecimal(&currentTimeStruct);
		sprintf(tempDisplay, "(H) %s:%s:%s\n",
				hex.hours, hex.minutes, hex.seconds);
    add_display_text(tempDisplay);
	}

	if((style & 8) == 8) {
		// Print the local time in decimal
		ctime_t dec = getDecimal(&currentTimeStruct);
		sprintf(tempDisplay, "(D) %s:%s:%s\n",
				dec.hours, dec.minutes, dec.seconds);
    add_display_text(tempDisplay);
	}

  display_clock();
}

int setInterval(int milliseconds) {
	struct itimerval newInterval;

	newInterval.it_interval.tv_sec = milliseconds / 1000;
	newInterval.it_interval.tv_usec = (milliseconds % 1000) * 1000L;

	newInterval.it_value.tv_sec = milliseconds / 1000;
	newInterval.it_value.tv_usec = (milliseconds % 1000) * 1000L;

	return setitimer(ITIMER_REAL, &newInterval, NULL);
}
