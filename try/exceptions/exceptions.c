#include "exceptions.h"

#include <stdlib.h>

class_t Exception_class;
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


class_t NullPointerException_class;
void method(NullPointerException, destruct)(NullPointerException_t* this) {
	this->super.destruct((Exception_t*) this);
}
void method(NullPointerException, populate)(NullPointerException_t* obj, class_t c) {
	populate(Exception)((Exception_t*) obj, c);
	
	add_method(obj, NullPointerException, destruct);
}
NullPointerException_t* method(NullPointerException, construct)() {
	NullPointerException_t* obj = malloc(sizeof(Exception_t));
	populate(NullPointerException)(obj, NullPointerException_class);

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
	OutOfMemoryException_t* obj = malloc(sizeof(Exception_t));
	populate(OutOfMemoryException)(obj, OutOfMemoryException_class);

	return obj;
}
