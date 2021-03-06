#include "try.h"
#include "exceptions/stdex.h"

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
	if (id == NO_TRY_BODY)
		return;
	stack[++stack_position] = id;
}

#define BACKTRACE_BUFFER_SIZE 16
#define EXIT_BACKTRACE_FAILED 3
#define EXIT_UNCAUGHT 4
void _print_backtrace(FILE* file, int ignore) {
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
	for (int i = ignore; i < tmp; i++) {
		fprintf(file, "  at %s\n", strings[i]);
	}
	if (tmp < entries) {
		fprintf(file, "  ...\n");
	}
	exit(EXIT_UNCAUGHT);
}

void try_throw(try_t id, void* exception) {
	if (id == NO_TRY_BODY) {
		Exception_t* e = exception;

		#ifdef PTHREAD_SCOPE_SYSTEM
		// we are in a pthread environment
			pthread_id_np_t   tid;
			tid = pthread_getthreadid_np();	
			fprintf(stderr, "\nUncaught error %s_t in thread %i\n: %s\n", 
				oop_get_class_name(oop_get_class_from_obj((void*) e)),
				tid, e->msg);
		#else
			fprintf(stderr, "\nUncaught error %s_t: %s\n", 
				oop_get_class_name(oop_get_class_from_obj((void*) e)),
				e->msg);
		#endif

		e->destruct(e); // destruct of exception (not sub classes), because we don't know what this is

		_print_backtrace(stderr, 2);
	} else {
		trys[id].exception = exception;
	}
}

void try_reset(try_t id) {
	trys[id].exception = NULL;
}
