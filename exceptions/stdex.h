#ifndef STDEX_H
#define STDEX_H

#include "../oop.h"

#define Exception construct(Exception)
extern class(Exception, Object_class, NO_INTERFACES, true) {
	extends(Object_t);	

	const char* msg;

	void (*destruct)(defclass Exception*);
} Exception_t;

void method(Exception, populate)(Exception_t*, class_t);
Exception_t* method(Exception, construct)(const char*);

#define NullPointerException construct(NullPointerException)
extern class(NullPointerException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass NullPointerException*);
} NullPointerException_t;

void method(NullPointerException, populate)(NullPointerException_t*, class_t);
NullPointerException_t* method(NullPointerException, construct)(void);

#define OutOfMemoryException construct(OutOfMemoryException)
extern class(OutOfMemoryException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass OutOfMemoryException*);
} OutOfMemoryException_t;

void method(OutOfMemoryException, populate)(OutOfMemoryException_t*, class_t);
OutOfMemoryException_t* method(OutOfMemoryException, construct)(void);

#endif
