#include "linkedlist.h"
#include "lists.h"
#include "../oop.h"
#include "../try.h"
#include "../exceptions/stdex.h"
#include "../memory.h"

#include <stdlib.h>

#define DEFAULT_SIZE_STEP 64

#define to_list(name, obj) LinkedList_t* name = (LinkedList_t*) obj 

class_t LinkedList_class;

LinkedList_t* method(LinkedList, construct)(void) {
	throws(OutOfMemoryException_t);

	sr_(LinkedList_t* list = allocate_object(LinkedList), NULL);
	populate(LinkedList)(list, LinkedList_class);

	return list;
}

size_t method(LinkedList, length)(void* this) {
	to_list(list, this);
	
	LinkedListElement_t* elem = list->first;
	
	size_t size; 
	for(size = 0; elem != NULL; size++) 
		elem = elem->next;

	return size;
}

void method(LinkedList, add)(void* this, void* obj) {	
	throws(NullPointerException_t, OutOfMemoryException_t);
	if (this == NULL)
		throw(new (NullPointerException)());
	
	to_list(list, this);

	s_(LinkedListElement_t* entry = allocate(sizeof(LinkedListElement_t)));

	entry->next = NULL;
	entry->data = obj;

	if (list->first == NULL) {
		list->first = entry;
		return;
	}

	LinkedListElement_t* last = list->first;

	for(; last->next != NULL; last = last->next);
	
	last->next = entry;
}

void* method(LinkedList, get)(void* this, size_t index) {
	throws(NullPointerException_t, IndexOutOfBoundsException_t, IndexOutOfBoundsException_t);
	if (this == NULL)
		throwr(new (NullPointerException)(), NULL);
	
	to_list(list, this);

	size_t size;
	LinkedListElement_t* next;
	
	for(next = list->first, size = 0; next != NULL; size++, next = next->next) {
		if (size == index)
			return next->data;
	}

	throwr(new (IndexOutOfBoundsException)(index, size), NULL);
}
void method(LinkedList, remove)(void* this, size_t index) {
	throws(NullPointerException_t, OutOfMemoryException_t, IndexOutOfBoundsException_t);
	if (this == NULL)
		throw(new (NullPointerException)());
	
	to_list(list, this);

	size_t size;
	LinkedListElement_t** next;

	for(next = &(list->first), size = 0; (*next) != NULL; size++, next = &((*next)->next)) {
		if (size == index) {
			LinkedListElement_t* tmp;
			tmp = *next;
			*next = (*next)->next;
			free(tmp);
			return;
		}
	}

	throw(new (IndexOutOfBoundsException)(index, size));
}

void method(LinkedList, push)(void* this, void* obj) {
	throws(NullPointerException_t);
	if (this == NULL)
		throw(new (NullPointerException)());
	
	to_list(list, this);

	list->add(list, obj);
}

void* method(LinkedList, pop)(void* this) {
	throws(NullPointerException_t, OutOfMemoryException_t);
	if (this == NULL)
		throwr(new (NullPointerException)(), NULL);
	
	to_list(list, this);

	if (list->first == NULL) {
		return NULL; // TODO NoElementException?
	}

	if (list->first->next == NULL) {
		void* value = list->first->data;
		free(list->first);
		list->first = NULL;
		return value;
	}

	LinkedListElement_t* current;
	LinkedListElement_t* prev;

	for(prev = NULL, current = list->first; current->next != NULL; prev = current, current = current->next);

	void* data = current->data;
	free(current);
	prev->next = NULL;
	return data;
	
}

void method(LinkedList, destruct)(LinkedList_t* this) {
	throws(NullPointerException_t);
	if (this == NULL)
		throw(new (NullPointerException)());
	
	to_list(list, this);

	for(LinkedListElement_t* next = list->first; next != NULL;) {
		next = next->next;
		free(next);
	}

	this->super.destruct((Object_t*) list);
}

void method(LinkedList, populate)(LinkedList_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);

	obj->first = NULL;

	add_method(obj, LinkedList, destruct);
	add_method(obj, LinkedList, length);
	add_method(obj, LinkedList, add);
	add_method(obj, LinkedList, get);
	add_method(obj, LinkedList, remove);
	add_method(obj, LinkedList, push);
	add_method(obj, LinkedList, pop);
}

