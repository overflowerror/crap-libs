#include "crap.h"

#include <stdio.h>

int main(void) {
	ArrayList_t* list = new ArrayList();

	printf("adding some strings\n");
	list->add(list, "Hallo");
	list->add(list, "Welt");
	list->add(list, "Hello");
	list->add(list, "World");

	for (size_t i = 0; i < list->length(list); i++) {
		printf("%lu: %s\n", i, (const char*) list->get(list, i));
	}

	printf("\nremoving index 0\n");
	list->remove(list, 0);
	
	for (size_t i = 0; i < list->length(list); i++) {
		printf("%lu: %s\n", i, (const char*) list->get(list, i));
	}

	printf("\nremoving index %lu\n", list->length(list));
	list->remove(list, list->length(list));

	return 0;
}
