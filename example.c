#include "crap.h"

#include <stdio.h>

int main(void) {
	//ArrayList_t* list = new (ArrayList)();
	LinkedList_t* list = new (LinkedList)();

	printf("adding some strings\n");
	list->add(list, "Hello");
	list->add(list, "World");
	list->add(list, "Foo");
	list->add(list, "Bar");

	for (size_t i = 0; i < list->length(list); i++) {
		printf("%lu: %s\n", i, (const char*) list->get(list, i));
	}

	printf("\nremoving index 0\n");
	list->remove(list, 0);
	
	for (size_t i = 0; i < list->length(list); i++) {
		printf("%lu: %s\n", i, (const char*) list->get(list, i));
	}

	printf("\npush new string\n");
	list->push(list, "Test");

	printf("poping string\n");
	const char* string = list->pop(list);
	printf(": %s\n", string);
	

	printf("\nremoving index %lu\n", list->length(list));

	list->remove(list, list->length(list));

	list->destruct(list);

	return 0;
}
