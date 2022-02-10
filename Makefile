#
# Makefile for the more03 extension to more02.c
#   This is a minimal Makefile.  If you know more about make
#   feel free to add fancier features.
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
