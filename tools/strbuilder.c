#include "strbuilder.h"
#include "../memory.h"
#include "../try.h"
#include "../exceptions/stdex.h"

#include <string.h>
#include <stdbool.h>

class_t Strbuilder_class;

void method(Strbuilder, clear)(Strbuilder_t* this) {
	throws(NullPointerException_t);

	if (this == NULL)
		throw(new (NullPointerException)());

	for (int i = 0; i < this->nrstrings; i++) {
		free(this->strings[i]);
	}
	free(this->string);
	this->string = NULL;
	this->nrstrings = 0;
}

void method(Strbuilder, destruct)(Strbuilder_t* this) {
	throws(NullPointerException_t);

	if (this == NULL)
		throw(new (NullPointerException)());

	this->clear(this);
	this->super.destruct((Object_t*) this);
}

void method(Strbuilder, add)(Strbuilder_t* this, const char* string) {
	throws(OutOfMemoryException_t, NullPointerException_t);

	if (this == NULL || string == NULL)
		throw(new (NullPointerException)());

	s_(this->strings = reallocate(this->strings, ++this->nrstrings * sizeof(char*)));
	s_(this->strings[this->nrstrings - 1] = allocate(strlen(string) + 1));
	strcpy(this->strings[this->nrstrings - 1], string);
}

size_t method(Strbuilder, length)(Strbuilder_t* this) {
	throws(NullPointerException_t);

	if (this == NULL)
		throwr(new (NullPointerException)(), 0);

	size_t length = 0;
	if (this->string != NULL)
		length = strlen(this->string);
	for (int i = 0; i < this->nrstrings; i++) {
		length += strlen(this->strings[i]);
	}
	return length;
}

void method(Strbuilder, build)(Strbuilder_t* this) {
	throws(OutOfMemoryException_t, NullPointerException_t);

	if (this == NULL)
		throw(new (NullPointerException)());

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
	throws(NullPointerException_t);

	if (this == NULL)
		throwr(new (NullPointerException)(), NULL);

	if (this->string == NULL)
		return "";
	
	return this->string;
}


Strbuilder_t* method(Strbuilder, construct)(const char* string) { 
	throws(OutOfMemoryException_t);

	sr_(Strbuilder_t* obj = allocate_object(Strbuilder), NULL);

	populate(Strbuilder)(obj, Strbuilder_class);

	if (string != NULL) {
		sr_(obj->string = allocate(strlen(string) + 1), NULL);
		strcpy(obj->string, string);
	}

	return obj;
}

int method(Strbuilder, hashCode)(void* obj) {
	throws(NullPointerException_t);
	if (obj == NULL)
		throwr(new (NullPointerException)(), 0);

	Strbuilder_t* builder = (Strbuilder_t*) obj;
	

	UNUSED(builder);
	
	return 0;
}

void method(Strbuilder, populate)(Strbuilder_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);
	
	obj->string = NULL;
	obj->strings = NULL;
	obj->nrstrings = 0;

	add_hashcode(obj);
	override_method(obj, Object, Strbuilder, hashCode);

	add_method(obj, Strbuilder, destruct);
	add_method(obj, Strbuilder, add);
	add_method(obj, Strbuilder, build);
	add_method(obj, Strbuilder, get);
	add_method(obj, Strbuilder, clear);
	add_method(obj, Strbuilder, length);
}
