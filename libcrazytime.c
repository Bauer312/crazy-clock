#include <stdio.h>
#include "libcrazytime.h"

ctime_t getBinary(struct tm *curTime) {
	ctime_t bin;
	memset(&bin, 0, sizeof(ctime_t));

	bin.hours[4] = curTime->tm_hour & 1 ? '1' : '0';
	bin.hours[3] = curTime->tm_hour & 2 ? '1' : '0';
	bin.hours[2] = curTime->tm_hour & 4 ? '1' : '0';
	bin.hours[1] = curTime->tm_hour & 8 ? '1' : '0';
	bin.hours[0] = curTime->tm_hour & 16 ? '1' : '0';

	bin.minutes[5] = curTime->tm_min & 1 ? '1' : '0';
	bin.minutes[4] = curTime->tm_min & 2 ? '1' : '0';
	bin.minutes[3] = curTime->tm_min & 4 ? '1' : '0';
	bin.minutes[2] = curTime->tm_min & 8 ? '1' : '0';
	bin.minutes[1] = curTime->tm_min & 16 ? '1' : '0';
	bin.minutes[0] = curTime->tm_min & 32 ? '1' : '0';

	bin.seconds[5] = curTime->tm_sec & 1 ? '1' : '0';
	bin.seconds[4] = curTime->tm_sec & 2 ? '1' : '0';
	bin.seconds[3] = curTime->tm_sec & 4 ? '1' : '0';
	bin.seconds[2] = curTime->tm_sec & 8 ? '1' : '0';
	bin.seconds[1] = curTime->tm_sec & 16 ? '1' : '0';
	bin.seconds[0] = curTime->tm_sec & 32 ? '1' : '0';

	return bin;
}

ctime_t getOctal(struct tm *curTime) {
	ctime_t oct;
	memset(&oct, 0, sizeof(ctime_t));

	// ASCII 48 == '0'
	oct.hours[0] = 48 + (curTime->tm_hour >> 3);
	oct.hours[1] = 48 + (curTime->tm_hour & 7);
	oct.minutes[0] = 48 + (curTime->tm_min >> 3);
	oct.minutes[1] = 48 + (curTime->tm_min & 7);
	oct.seconds[0] = 48 + (curTime->tm_sec >> 3);
	oct.seconds[1] = 48 + (curTime->tm_sec & 7);

	return oct;
}

ctime_t getHexadecimal(struct tm *curTime) {
	ctime_t hex;
	memset(&hex, 0, sizeof(ctime_t));

	int high = curTime->tm_hour >> 4;
	int low = curTime->tm_hour & 15;

	// ASCII 48 == '0', ASCII 65 == 'A'
	hex.hours[0] = high > 9 ? high + 55 : high + 48;
	hex.hours[1] = low > 9 ? low + 55 : low + 48;
	
	high = curTime->tm_min >> 4;
	low = curTime->tm_min & 15;

	hex.minutes[0] = high > 9 ? high + 55 : high + 48;
	hex.minutes[1] = low > 9 ? low + 55 : low + 48;

	high = curTime->tm_sec >> 4;
	low = curTime->tm_sec & 15;

	hex.seconds[0] = high > 9 ? high + 55 : high + 48;
	hex.seconds[1] = low > 9 ? low + 55 : low + 48;

	return hex;
}

ctime_t getDecimal(struct tm *curTime) {
	ctime_t dec;
	memset(&dec, 0, sizeof(ctime_t));

	sprintf(dec.hours, "%02d", curTime->tm_hour);
	sprintf(dec.minutes, "%02d", curTime->tm_min);
	sprintf(dec.seconds, "%02d", curTime->tm_sec);

	return dec;
}
