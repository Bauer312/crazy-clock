#
# Makefile for the crazy clock
#

CC = cc -Wall -Wextra -g

crazy-clock: crazy-clock.o libcrazytime.o
	$(CC) crazy-clock.o libcrazytime.o -o crazy-clock -lncurses

crazy-clock.o: crazy-clock.c crazy-clock.h
	$(CC) -c crazy-clock.c

libcrazytime.o: libcrazytime.c libcrazytime.h
	$(CC) -c libcrazytime.c
clean:
	rm -f *.o
	rm crazy-clock
