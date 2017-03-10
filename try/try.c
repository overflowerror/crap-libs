#include "try.h"
#include "exceptions/exceptions.h"

#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>
#include <string.h>
#include <errno.h>

struct tryc {
	bool used;
	void* exception;
};

#define MAX_TRY 10

int trynr = 0;

struct tryc trys[MAX_TRY] = {0};

int stack_position = -1;
try_t stack[MAX_TRY] = {-1};

try_t find_free_id(void) {
	for (int i = 0; i < MAX_TRY; i++) {
		if (!trys[i].used)
			return i;
	}
	return -1;
}

try_t try_new(void) {
	if (trynr >= MAX_TRY)
		return -1;
	try_t t = find_free_id();
	trys[t].used = true;
	trys[t].exception = NULL;
	return t;
}

bool try_has_catch(try_t id) {
	return trys[id].exception != NULL;
}

void* try_catch(try_t id) {
	return trys[id].exception;
}


void try_remove(try_t id) {
	if (trys[id].used) {
		trys[id].used = false;
		trynr--;
	}
}

try_t try_pop(void) {
	if (stack_position < 0)
		return NO_TRY_BODY;
	return stack[stack_position--];
}

void try_push(try_t id) {
	stack[++stack_position] = id;
}

#define BACKTRACE_BUFFER_SIZE 16
#define EXIT_BACKTRACE_FAILED 3
#define EXIT_UNCAUGHT 4
void print_backtrace(FILE* file) {
	void* buffer[BACKTRACE_BUFFER_SIZE];
	char** strings;
	int entries = backtrace(buffer, BACKTRACE_BUFFER_SIZE);
	strings = backtrace_symbols(buffer, entries);
	
	if (strings == NULL) {
		fprintf(file, "  Error while backtracing: %s\n", strerror(errno));
		exit(EXIT_BACKTRACE_FAILED);
	}

	int tmp = (entries < BACKTRACE_BUFFER_SIZE) ? entries : entries - 1;

	// from 2, because of print_backtrace and try_throw
	for (int i = 2; i < tmp; i++) {
		fprintf(file, "  at %s\n", strings[i]);
	}
	if (tmp < entries) {
		fprintf(file, "  ...\n");
	}
	exit(EXIT_UNCAUGHT);
}

void try_throw(try_t id, void* exception) {
	if (id == NO_TRY_BODY) {
		exception_t* e = exception;
		fprintf(stderr, "\nUncaught exception '%s_t' (\"%s\")\n", 
			oop_get_class_name(oop_get_class_from_obj((void*) e)),
			e->msg);
		print_backtrace(stderr);
	} else {
		trys[id].exception = exception;
	}
}

void try_reset(try_t id) {
	trys[id].exception = NULL;
}
