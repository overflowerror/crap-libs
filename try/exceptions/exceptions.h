#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "../../oop/oop.h"

#define exception construct(exception)
class(exception, object_class, true) {
	extends(object_t);	

	const char* msg;

	void (*destruct)(defclass exception*);
} exception_t;

void method(exception, populate)(exception_t*, class_t);
exception_t* method(exception, construct)(const char*);

/*#define exception construct(exception)
class_t exception_class;
class(exception, exception_class, object_class, true) {
	extends(object_t);	

	const char* msg;

	void (*destruct)(defclass exception*);
} exception_t;

void method(exception, populate)(exception_t*);
exception_t* method(exception, construct)(const char*);
*/

#endif
