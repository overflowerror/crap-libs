#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stdlib.h>
#include "../oop/oop.h"

#define strbuilder construct(strbuilder)
extern class(strbuilder, object_class, true) {
	extends(object_t);

	char* string;
	char** strings;
	int nrstrings;

	void (*destruct)(defclass strbuilder*);
	void (*add)(defclass strbuilder*, const char*);
	void (*build)(defclass strbuilder*);
	const char* (*get)(defclass strbuilder*);
	void (*clear)(defclass strbuilder*);
	size_t (*length)(defclass strbuilder*);
} strbuilder_t;

strbuilder_t* method(strbuilder, construct)(const char*);
void method(strbuilder, populate)(strbuilder_t*);

#endif
