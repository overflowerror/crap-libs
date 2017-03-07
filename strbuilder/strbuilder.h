#ifndef STRBUILDER_H
#define STRBUILDER_H

#include <stdlib.h>
#include "../oop/oop.h"

#define strbuilder construct(strbuilder)

extern class_t strbuilder_class;

typedef struct strbuilder {
	meta_object_t meta;
	void (*destruct)(struct strbuilder*);
	void (*add)(struct strbuilder*, const char*);
	void (*build)(struct strbuilder*);
	const char* (*get)(struct strbuilder*);
	void (*clear)(struct strbuilder*);
	size_t (*length)(struct strbuilder*);
	char* string;
	char** strings;
	int nrstrings;
} strbuilder_t;

strbuilder_t* strbuilder_method_construct(const char*);

#endif
