#include "exceptions.h"

#include <stdlib.h>

void method(Exception, destruct)(Exception_t* this) {
	this->super.destruct((Object_t*) this);
}

void method(Exception, populate)(Exception_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);

	add_method(obj, Exception, destruct);
}

Exception_t* method(Exception, construct)(const char* msg) {
	Exception_t* obj = malloc(sizeof(Exception_t));
	populate(Exception)(obj, Exception_class);

	obj->msg = msg;

	return obj;
}
