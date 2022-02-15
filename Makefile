#
# Makefile for the crazy clock
#

CC = cc -Wall -Wextra -g

crazy-clock: crazy-clock.o display.o libcrazytime.o
	$(CC) crazy-clock.o display.o libcrazytime.o -o crazy-clock -lncurses

crazy-clock.o: crazy-clock.c crazy-clock.h constants.h display.h
	$(CC) -c crazy-clock.c

display.o: display.c display.h constants.h
	$(CC) -c display.c

libcrazytime.o: libcrazytime.c libcrazytime.h
	$(CC) -c libcrazytime.c
clean:
	rm -f *.o
	rm crazy-clock
