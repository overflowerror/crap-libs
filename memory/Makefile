#
# Makefile for crap-libs/memory
#
# Author: overflowerror
#

CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -B "../try/" -B "../oop/"
CFLAGS = -Wall -Wextra -g -std=c99 -pedantic -DENDEBUG $(DEFS) -fPIC
LDFLAGS = $(DEFS)
LIBFLAGS = -shared $(DEFS)

.PHONY: all clean

all: example libmemory.so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

example: example.o memory.o ../try/libtry.so ../oop/liboop.so
	$(CC) $(LDFLAGS) -o $@ $^

libmemory.so: memory.o ../try/libtry.so ../oop/liboop.so
	$(CC) $(LIBFLAGS) -o $@ $^

memory.o: memory.c memory.h
example.o: example.c memory.h 

../try/libtry.so:
	cd ../try/ && $(MAKE) libtry.so

../oop/liboop.so:
	cd ../oop/ && $(MAKE) liboop.so

clean:
	rm -f *.o example memory.so
	cd ../try/ && $(MAKE) clean
	cd ../oop/ && $(MAKE) clean
