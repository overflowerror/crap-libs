#ifndef STDEX_H
#define STDEX_H

#include "../oop.h"

//#define Exception construct(Exception)
extern class(Exception, Object_class, NO_INTERFACES, true) {
	extends(Object_t);	

	const char* msg;

	void (*destruct)(defclass Exception*);
} Exception_t;

void method(Exception, populate)(Exception_t*, class_t);
Exception_t* method(Exception, construct)(const char*);

//#define NullPointerException construct(NullPointerException)
extern class(NullPointerException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass NullPointerException*);
} NullPointerException_t;

void method(NullPointerException, populate)(NullPointerException_t*, class_t);
NullPointerException_t* method(NullPointerException, construct)(void);

//#define OutOfMemoryException construct(OutOfMemoryException)
extern class(OutOfMemoryException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass OutOfMemoryException*);
} OutOfMemoryException_t;

void method(OutOfMemoryException, populate)(OutOfMemoryException_t*, class_t);
OutOfMemoryException_t* method(OutOfMemoryException, construct)(void);

//#define IndexOutOfBoundsException construct(IndexOutOfBoundsException)
extern class(IndexOutOfBoundsException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass IndexOutOfBoundsException*);
} IndexOutOfBoundsException_t;

void method(IndexOutOfBoundsException, populate)(IndexOutOfBoundsException_t*, class_t);
IndexOutOfBoundsException_t* method(IndexOutOfBoundsException, construct)(size_t, size_t);

//#define IllegalArgumentException construct(IllegalArgumentException)
extern class(IllegalArgumentException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass IllegalArgumentException*);
} IllegalArgumentException_t;

void method(IllegalArgumentException, populate)(IllegalArgumentException_t*, class_t);
IllegalArgumentException_t* method(IllegalArgumentException, construct)(const char*);

//#define ClassNotInstanceableException construct(ClassNotInstanceableException)
extern class(ClassNotInstanceableException, Exception_class, NO_INTERFACES, true) {
	extends(Exception_t);

	void (*destruct)(defclass ClassNotInstanceableException*);
} ClassNotInstanceableException_t;

void method(ClassNotInstanceableException, populate)(ClassNotInstanceableException_t*, class_t);
ClassNotInstanceableException_t* method(ClassNotInstanceableException, construct)(const char*);

#endif
