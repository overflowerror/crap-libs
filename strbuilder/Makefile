#
# Makefile for crap-libs/strbuilder
#
# Author: overflowerror
#

CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -B "../oop/"
CFLAGS = -Wall -Wextra -g -std=c99 -pedantic -DENDEBUG $(DEFS) -fPIC
LDFLAGS = $(DEFS)
LIBFLAGS = -shared $(DEFS)

.PHONY: all clean

all: example libstrbuilder.so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

example: example.o strbuilder.o ../oop/liboop.so
	$(CC) $(LDFLAGS) -o $@ $^

../oop/liboop.so:
	cd ../oop/ && $(MAKE) liboop.so

libstrbuilder.so: strbuilder.o
	$(CC) $(LIBFLAGS) -o $@ $^

strbuilder.o: strbuilder.c strbuilder.h
example.o: example.c strbuilder.h 

clean:
	rm -f *.o example libstrbuilder.so
	cd ../oop/ && $(MAKE) clean
