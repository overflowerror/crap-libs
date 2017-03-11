#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "../../oop/oop.h"

#define Exception construct(Exception)
class(Exception, Object_class, true) {
	extends(Object_t);	

	const char* msg;

	void (*destruct)(defclass Exception*);
} Exception_t;

void method(Exception, populate)(Exception_t*, class_t);
Exception_t* method(Exception, construct)(const char*);

#endif
