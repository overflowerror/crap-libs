#
# Makefile for crap-libs/try
#
# Author: overflowerror
#

CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE
CFLAGS = -Wall -Wextra -g -std=c99 -pedantic -DENDEBUG $(DEFS) -fPIC
LDFLAGS = $(DEFS)
LIBFLAGS = -shared $(DEFS)

.PHONY: all clean

all: example libtry.so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

example: example.o try.o 
	$(CC) $(LDFLAGS) -o $@ $^

libtry.so: try.o
	$(CC) $(LIBFLAGS) -o $@ $^

try.o: try.c try.h
example.o: example.c try.h 

clean: 
	rm -f *.o example libtry.so
