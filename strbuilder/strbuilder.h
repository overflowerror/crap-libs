#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stdlib.h>
#include "../oop/oop.h"

#define strbuilder construct(strbuilder)

extern class_t strbuilder_class;

class(strbuilder, strbuilder_class, object_class, true) {
	extends(object_t);

	char* string;
	char** strings;
	int nrstrings;

	void (*destruct)(struct strbuilder*);
	void (*add)(struct strbuilder*, const char*);
	void (*build)(struct strbuilder*);
	const char* (*get)(struct strbuilder*);
	void (*clear)(struct strbuilder*);
	size_t (*length)(struct strbuilder*);
} strbuilder_t;

strbuilder_t* method(strbuilder, construct)(const char*);
void method(strbuilder, populate)(strbuilder_t*);

#endif
