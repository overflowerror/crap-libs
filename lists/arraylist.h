#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../oop.h"
#include "lists.h"

#define ArrayList construct(ArrayList)
extern class(ArrayList, Object_class, (interfaces){4 namely {Cloneable_class and List_class and Countable_class and Stack_class}}, true) {
	extends(Object_t);
	implements(Cloneable);
	implements(List);
	implements(Countable);
	implements(Stack);
	void (*destruct)(defclass ArrayList*);

	size_t currentSize;
	size_t sizeStep;
	int steps;
	void** data;
} ArrayList_t;

ArrayList_t* method(ArrayList, construct)(void);
void method(ArrayList, populate)(ArrayList_t*, class_t);

#endif
