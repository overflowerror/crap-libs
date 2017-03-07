#include "strbuilder.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

class_t strbuilder_class;

__attribute__ ((constructor)) 
static void add_strbuilder_class(void) {
	strbuilder_class.id = new_class("strbuilder", NO_SUPER_CLASS, true);
}

void strbuilder_method_clear(strbuilder_t* this) {
	for (int i = 0; i < this->nrstrings; i++) {
		free(this->strings[i]);
	}
	free(this->string);
	this->string = NULL;
	this->nrstrings = 0;
}

void strbuilder_method_destruct(strbuilder_t* this) {
	this->clear(this);
	free(this);
}

void strbuilder_method_add(strbuilder_t* this, const char* string) {
	this->strings = realloc(this->strings, ++this->nrstrings * sizeof(char*));
	this->strings[this->nrstrings - 1] = malloc(strlen(string) + 1);
	strcpy(this->strings[this->nrstrings - 1], string);
}

size_t strbuilder_method_length(strbuilder_t* this) {
	size_t length = 0;
	if (this->string != NULL)
		length = strlen(this->string);
	for (int i = 0; i < this->nrstrings; i++) {
		length += strlen(this->strings[i]);
	}
	return length;
}

void strbuilder_method_build(strbuilder_t* this) {
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

const char* strbuilder_method_get(strbuilder_t* this) {
	return this->string;
}

strbuilder_t* strbuilder_method_construct(const char* string) {
	strbuilder_t* obj = malloc(sizeof(strbuilder_t));
	obj->string = malloc(strlen(string) + 1);
	strcpy(obj->string, string);
	obj->strings = NULL;
	obj->nrstrings = 0;

	obj->destruct = strbuilder_method_destruct;
	obj->add = strbuilder_method_add;
	obj->build = strbuilder_method_build;
	obj->get = strbuilder_method_get;
	obj->clear = strbuilder_method_clear;
	obj->length = strbuilder_method_length;

	return obj;
}
