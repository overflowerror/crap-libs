#
# Makefile for crap-libs/oop
#
# Author: overflowerror
#

CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE
CFLAGS = -Wall -Wextra -g -std=c99 -pedantic -DENDEBUG $(DEFS) -fPIC
LDFLAGS = $(DEFS)
LIBFLAGS = -shared $(DEFS)

.PHONY: all clean

all: example liboop.so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

example: example.o oop.o 
	$(CC) $(LDFLAGS) -o $@ $^

liboop.so: oop.o
	$(CC) $(LIBFLAGS) -o $@ $^

oop.o: oop.c oop.h
example.o: example.c oop.h 

clean: 
	rm -f *.o example liboop.so
