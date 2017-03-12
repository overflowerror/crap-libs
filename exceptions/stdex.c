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

	add_method(obj, NullPointerException, destruct);
}
NullPointerException_t* method(NullPointerException, construct)() {
	throws(OutOfMemoryException_t);

	sr_(NullPointerException_t* obj = allocate_object(NullPointerException_t), NULL);
	populate(NullPointerException)(obj, NullPointerException_class);
	
	obj->super.msg = "Unexpected Null-pointer.";

	return obj;
}


class_t OutOfMemoryException_class;
void method(OutOfMemoryException, destruct)(OutOfMemoryException_t* this) {
	this->super.destruct((Exception_t*) this);
}
void method(OutOfMemoryException, populate)(OutOfMemoryException_t* obj, class_t c) {
	populate(Exception)((Exception_t*) obj, c);

	add_method(obj, OutOfMemoryException, destruct);
}
OutOfMemoryException_t* method(OutOfMemoryException, construct)() {
	OutOfMemoryException_t* obj =  malloc(sizeof(OutOfMemoryException_t));
	if (obj == NULL) {
		fprintf(stderr, "\nCritical error! Can not allocate memory for OutOfMemoryException: %s\n", strerror(errno));
		_print_backtrace(stderr, 1);
	}

	populate(OutOfMemoryException)(obj, OutOfMemoryException_class);

	obj->super.msg = "Could not allocate memory.";

	return obj;
}

class_t IndexOutOfBoundsException_class;
void method(IndexOutOfBoundsException, destruct)(IndexOutOfBoundsException_t* this) {
	free((void*) this->super.msg); // I don't like C.
	this->super.destruct((Exception_t*) this);
}
void method(IndexOutOfBoundsException, populate)(IndexOutOfBoundsException_t* obj, class_t c) {
	populate(Exception)((Exception_t*) obj, c);

	add_method(obj, IndexOutOfBoundsException, destruct);
}
IndexOutOfBoundsException_t* method(IndexOutOfBoundsException, construct)(size_t index, size_t length) {
	throws(OutOfMemoryException_t);

	sr_(IndexOutOfBoundsException_t* obj = allocate_object(IndexOutOfBoundsException_t), NULL);
	populate(IndexOutOfBoundsException)(obj, IndexOutOfBoundsException_class);

	const char* format = "Requested index %i is out of bounds (%i).";

	size_t len = strlen(format) - 4; // 2x "%i"
	for(int i = index; i > 0; i /= 10)
		len++;
	for(int i = length; i > 0; i /= 10)
		len++;

	sr_(char* msg = allocate(len + 1), NULL);
	snprintf(msg, len + 1, format, index, length);

	obj->super.msg = msg;

	return obj;
}
