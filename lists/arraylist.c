#include "arraylist.h"
#include "lists.h"
#include "../oop.h"
#include "../try.h"
#include "../exceptions/stdex.h"
#include "../memory.h"

#include <stdlib.h>

#define DEFAULT_SIZE_STEP 64

#define to_list(name, obj) ArrayList_t* name = (ArrayList_t*) obj 

class_t ArrayList_class;

ArrayList_t* method(ArrayList, construct)(void) {
	throws(OutOfMemoryException_t);

	sr_(ArrayList_t* list = allocate_object(ArrayList), NULL);
	populate(ArrayList)(list, ArrayList_class);

	return list;
}

size_t method(ArrayList, length)(void* this) {
	to_list(list, this);
	return list->currentSize;
}

void method(ArrayList, add)(void* this, void* obj) {	
	throws(NullPointerException_t, OutOfMemoryException_t);
	if (this == NULL)
		throw(new NullPointerException());
	
	to_list(list, this);

	if (list->data == NULL) {
		s_(list->data = allocate(++list->steps * list->sizeStep * sizeof(void*)));
	}
	if (list->currentSize + 1 >= list->steps * list->sizeStep) {
		s_(list->data = reallocate(list->data, ++list->steps * list->sizeStep * sizeof(void*)));
	}
	list->data[list->currentSize++] = obj;
}

void* method(ArrayList, get)(void* this, size_t index) {
	throws(NullPointerException_t, IndexOutOfBoundsException_t);
	if (this == NULL)
		throwr(new NullPointerException(), NULL);
	
	to_list(list, this);

	if (index >= list->currentSize)
		throwr(new IndexOutOfBoundsException(index, list->currentSize), NULL);

	return list->data[index];

}
void method(ArrayList, remove)(void* this, size_t index) {
	throws(NullPointerException_t, OutOfMemoryException_t);
	if (this == NULL)
		throw(new NullPointerException());
	
	to_list(list, this);

	if (index >= list->currentSize)
		throw(new IndexOutOfBoundsException(index, list->currentSize));

	for(size_t i = index; i < list->currentSize - 1; i++) {
		list->data[i] = list->data[i + 1];
	}

	if (--list->currentSize < (list->steps - 1) * list->sizeStep) {
		s_(list->data = reallocate(list->data, --list->steps * list->sizeStep * sizeof(void*)));
	}
}

void method(ArrayList, push)(void* this, void* obj) {
	throws(NullPointerException_t);
	if (this == NULL)
		throw(new NullPointerException());
	
	to_list(list, this);

	list->add(list, obj);
}

void* method(ArrayList, pop)(void* this) {
	throws(NullPointerException_t, OutOfMemoryException_t);
	if (this == NULL)
		throwr(new NullPointerException(), NULL);
	
	to_list(list, this);

	int size = list->currentSize;
	sr_(void* element = list->get(this, size - 1), NULL);
	sr_(list->remove(this, size - 1), NULL);

	return element;
}

void method(ArrayList, destruct)(ArrayList_t* this) {
	throws(NullPointerException_t);
	if (this == NULL)
		throw(new NullPointerException());
	
	
}

void method(ArrayList, populate)(ArrayList_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);

	obj->data = NULL;
	obj->currentSize = 0;
	obj->steps = 0;
	obj->sizeStep = DEFAULT_SIZE_STEP;

	add_method(obj, ArrayList, destruct);
	add_method(obj, ArrayList, length);
	add_method(obj, ArrayList, add);
	add_method(obj, ArrayList, get);
	add_method(obj, ArrayList, remove);
	add_method(obj, ArrayList, push);
	add_method(obj, ArrayList, pop);
}

