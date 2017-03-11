#include "strbuilder.h"
#include "../memory.h"

#include <string.h>
#include <stdbool.h>

class_t Strbuilder_class;

void method(Strbuilder, clear)(Strbuilder_t* this) {
	for (int i = 0; i < this->nrstrings; i++) {
		free(this->strings[i]);
	}
	free(this->string);
	this->string = NULL;
	this->nrstrings = 0;
}

void method(Strbuilder, destruct)(Strbuilder_t* this) {
	this->clear(this);
	this->super.destruct((Object_t*) this);
}

void method(Strbuilder, add)(Strbuilder_t* this, const char* string) {
	throws(OutOfMemoryException_t);

	s_(this->strings = reallocate(this->strings, ++this->nrstrings * sizeof(char*)));
	s_(this->strings[this->nrstrings - 1] = allocate(strlen(string) + 1));
	strcpy(this->strings[this->nrstrings - 1], string);
}

size_t method(Strbuilder, length)(Strbuilder_t* this) {
	size_t length = 0;
	if (this->string != NULL)
		length = strlen(this->string);
	for (int i = 0; i < this->nrstrings; i++) {
		length += strlen(this->strings[i]);
	}
	return length;
}

void method(Strbuilder, build)(Strbuilder_t* this) {
	throws(OutOfMemoryException_t);

	size_t length = this->length(this);
	bool empty = this->string == NULL;
	s_(this->string = reallocate(this->string, length + 1));
	if (empty)
		this->string[0] = '\0';
	for (int i = 0; i < this->nrstrings; i++) {
		strcat(this->string, this->strings[i]);
		free(this->strings[i]);
	}
	this->nrstrings = 0;
}

const char* method(Strbuilder, get)(Strbuilder_t* this) {
	return this->string;
}

Strbuilder_t* method(Strbuilder, construct)(const char* string) { 
	throws(OutOfMemoryException_t);

	sr_(Strbuilder_t* obj = allocate_object(Strbuilder_t), NULL);

	populate(Strbuilder)(obj, Strbuilder_class);

	sr_(obj->string = allocate(strlen(string) + 1), NULL);
	strcpy(obj->string, string);

	return obj;
}


void method(Strbuilder, populate)(Strbuilder_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);
	
	obj->string = NULL;
	obj->strings = NULL;
	obj->nrstrings = 0;

	add_method(obj, Strbuilder, destruct);
	add_method(obj, Strbuilder, add);
	add_method(obj, Strbuilder, build);
	add_method(obj, Strbuilder, get);
	add_method(obj, Strbuilder, clear);
	add_method(obj, Strbuilder, length);
}
