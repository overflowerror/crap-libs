#include "try.h"

#include <stdlib.h>

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
	trys[id].used = false;
	trynr--;
}

try_t try_pop(void) {
	return stack[stack_position--];
}

void try_push(try_t id) {
	stack[++stack_position] = id;
}

void try_throw(try_t id, void* exception) {
	trys[id].exception = exception;
}
