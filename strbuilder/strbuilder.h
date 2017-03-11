#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stdlib.h>
#include "../oop/oop.h"

#define Strbuilder construct(Strbuilder)
extern class(Strbuilder, Object_class, NO_INTERFACES, true) {
	extends(Object_t);

	char* string;
	char** strings;
	int nrstrings;

	void (*destruct)(defclass Strbuilder*);
	void (*add)(defclass Strbuilder*, const char*);
	void (*build)(defclass Strbuilder*);
	const char* (*get)(defclass Strbuilder*);
	void (*clear)(defclass Strbuilder*);
	size_t (*length)(defclass Strbuilder*);
} Strbuilder_t;

Strbuilder_t* method(Strbuilder, construct)(const char*);
void method(Strbuilder, populate)(Strbuilder_t*, class_t);

#endif
