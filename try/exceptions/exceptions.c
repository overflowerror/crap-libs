#include "exceptions.h"

#include <stdlib.h>

void method(exception, destruct)(exception_t* this) {
	this->super.destruct((object_t*) this);
}

void method(exception, populate)(exception_t* obj, class_t c) {
	populate(object)((object_t*) obj, c);

	add_method(obj, exception, destruct);
}

exception_t* method(exception, construct)(const char* msg) {
	exception_t* obj = malloc(sizeof(exception_t));
	populate(exception)(obj, exception_class);

	obj->msg = msg;

	return obj;
}
