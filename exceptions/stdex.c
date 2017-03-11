#include "stdex.h"
#include "../memory.h"
#include "../try.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

class_t Exception_class;
void method(Exception, destruct)(Exception_t* this) {
	this->super.destruct((Object_t*) this);
}
void method(Exception, populate)(Exception_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);

	add_method(obj, Exception, destruct);
}
Exception_t* method(Exception, construct)(const char* msg) {
	throws(OutOfMemoryException_t);

	sr_(Exception_t* obj = allocate_object(Exception_t), NULL);
	populate(Exception)(obj, Exception_class);

	obj->msg = msg;

	return obj;
}


class_t NullPointerException_class;
void method(NullPointerException, destruct)(NullPointerException_t* this) {
	this->super.destruct((Exception_t*) this);
}
void method(NullPointerException, populate)(NullPointerException_t* obj, class_t c) {
	populate(Exception)((Exception_t*) obj, c);
	
	obj->super.msg = "Unexpected Null-pointer.";

	add_method(obj, NullPointerException, destruct);
}
NullPointerException_t* method(NullPointerException, construct)() {
	throws(OutOfMemoryException_t);

	sr_(NullPointerException_t* obj = allocate_object(NullPointerException_t), NULL);
	populate(NullPointerException)(obj, NullPointerException_class);

	return obj;
}


class_t OutOfMemoryException_class;
void method(OutOfMemoryException, destruct)(OutOfMemoryException_t* this) {
	this->super.destruct((Exception_t*) this);
}
void method(OutOfMemoryException, populate)(OutOfMemoryException_t* obj, class_t c) {
	populate(Exception)((Exception_t*) obj, c);
	
	obj->super.msg = "Could not allocate memory.";

	add_method(obj, OutOfMemoryException, destruct);
}
OutOfMemoryException_t* method(OutOfMemoryException, construct)() {
	OutOfMemoryException_t* obj =  malloc(sizeof(OutOfMemoryException_t));
	if (obj == NULL) {
		fprintf(stderr, "\nCritical error! Can not allocate memory for OutOfMemoryException: %s\n", strerror(errno));
		_print_backtrace(stderr, 1);
	}

	populate(OutOfMemoryException)(obj, OutOfMemoryException_class);

	return obj;
}
