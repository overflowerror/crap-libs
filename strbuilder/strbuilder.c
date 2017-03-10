#include "strbuilder.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

class_t strbuilder_class;

void method(strbuilder, clear)(strbuilder_t* this) {
	for (int i = 0; i < this->nrstrings; i++) {
		free(this->strings[i]);
	}
	free(this->string);
	this->string = NULL;
	this->nrstrings = 0;
}

void method(strbuilder, destruct)(strbuilder_t* this) {
	this->clear(this);
	this->super.destruct((object_t*) this);
}

void method(strbuilder, add)(strbuilder_t* this, const char* string) {
	this->strings = realloc(this->strings, ++this->nrstrings * sizeof(char*));
	this->strings[this->nrstrings - 1] = malloc(strlen(string) + 1);
	strcpy(this->strings[this->nrstrings - 1], string);
}

size_t method(strbuilder, length)(strbuilder_t* this) {
	size_t length = 0;
	if (this->string != NULL)
		length = strlen(this->string);
	for (int i = 0; i < this->nrstrings; i++) {
		length += strlen(this->strings[i]);
	}
	return length;
}

void method(strbuilder, build)(strbuilder_t* this) {
	size_t length = this->length(this);
	bool empty = this->string == NULL;
	this->string = realloc(this->string, length + 1);
	if (empty)
		this->string[0] = '\0';
	for (int i = 0; i < this->nrstrings; i++) {
		strcat(this->string, this->strings[i]);
		free(this->strings[i]);
	}
	this->nrstrings = 0;
}

const char* method(strbuilder, get)(strbuilder_t* this) {
	return this->string;
}

strbuilder_t* method(strbuilder, construct)(const char* string) {
	strbuilder_t* obj = malloc(sizeof(strbuilder_t));

	populate(strbuilder)(obj, strbuilder_class);

	obj->string = malloc(strlen(string) + 1);
	strcpy(obj->string, string);

	return obj;
}


void method(strbuilder, populate)(strbuilder_t* obj, class_t c) {
	populate(object)((object_t*) obj, c);
	
	obj->string = NULL;
	obj->strings = NULL;
	obj->nrstrings = 0;

	add_method(obj, strbuilder, destruct);
	add_method(obj, strbuilder, add);
	add_method(obj, strbuilder, build);
	add_method(obj, strbuilder, get);
	add_method(obj, strbuilder, clear);
	add_method(obj, strbuilder, length);
}
