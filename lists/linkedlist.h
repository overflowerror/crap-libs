#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../oop.h"
#include "lists.h"

typedef struct LinkedListElement {
	void* data;
	struct LinkedListElement* next;
} LinkedListElement_t;

// #define LinkedList construct(LinkedList)
extern class(LinkedList, Object_class, (interfaces){4 namely {Cloneable_class and List_class and Countable_class and Stack_class}}, true) {
	extends(Object_t);
	implements(Cloneable);
	implements(List);
	implements(Countable);
	implements(Stack);
	void (*destruct)(defclass LinkedList*);

	LinkedListElement_t* first;
} LinkedList_t;

LinkedList_t* method(LinkedList, construct)(void);
void method(LinkedList, populate)(LinkedList_t*, class_t);

#endif
