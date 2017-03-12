#
# Makefile for crap-libs
#
# Author: overflowerror
#

CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE
CFLAGS = -Wall -Wextra -g -std=c99 -DENDEBUG $(DEFS) -fPIC
LDFLAGS = $(DEFS) -rdynamic
LIBFLAGS = -shared $(DEFS)

.PHONY: all clean

all: example libcrap.so

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

example: example.o memory.o try.o oop.o exceptions/stdex.o tools/strbuilder.o lists/lists.o lists/arraylist.o
	$(CC) $(LDFLAGS) -o $@ $^

libcrap.so: memory.o try.o oop.o exceptions/stdex.o tools/strbuilder.o lists/lists.o lists/arraylist.o
	$(CC) $(LIBFLAGS) -o $@ $^

example.o: example.c try.h
memory.o: memory.c memory.h oop.h exceptions/stdex.h
try.o: try.c try.h oop.h exceptions/stdex.h
oop.o: oop.h misc.h

exceptions/stdex.o: exceptions/stdex.c exceptions/stdex.h

tools/strbuilder.o: tools/strbuilder.c tools/strbuilder.h exceptions/stdex.h

lists/lists.o: lists/lists.c lists/lists.h oop.h
lists/arraylist.o: lists/arraylist.c lists/arraylist.h oop.h

clean:
	rm -f *.o exceptions/*.o tools/*.o lists/*.o example
