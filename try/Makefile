#
# Makefile for crap-libs/try
#
# Author: overflowerror
#

CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -B "../oop/"
CFLAGS = -Wall -Wextra -g -std=c99 -DENDEBUG $(DEFS) -fPIC
LDFLAGS = $(DEFS) -rdynamic
LIBFLAGS = -shared $(DEFS)

.PHONY: all clean

all: example libtry.so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

example: example.o try.o exceptions/exceptions.o ../oop/liboop.so
	$(CC) $(LDFLAGS) -o $@ $^

libtry.so: try.o exceptions/exceptions.o ../oop/liboop.so
	$(CC) $(LIBFLAGS) -o $@ $^

try.o: try.c try.h
example.o: example.c try.h 
exceptions/exceptions.o: exceptions/exceptions.c exceptions/exceptions.h

../oop/liboop.so:
	cd ../oop/ && $(MAKE) liboop.so

clean: 
	rm -f *.o example libtry.so
	cd ../oop/ && $(MAKE) clean
