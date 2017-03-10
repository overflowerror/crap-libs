#include <stdlib.h>
#include <stdio.h>

#include "oop.h"

#define test construct(test)

class_t test_class;

class(test, test_class, object_class, true) {
	extends(object_t);	

	const char* string;

	void (*print)(defclass test*);
	void (*destruct)(defclass test*);
} test_t;

void method(test, print)(test_t* this) {
	printf("%s\n", this->string);
}
void method(test, destruct)(test_t* this) {
	this->super.destruct((object_t*) this);
}

void method(test, populate)(test_t* obj, class_t c) {
	populate(object)((object_t*) obj);

	add_method(obj, test, destruct);
	add_method(obj, test, print);
}

test_t* method(test, construct)(const char* string) {
	test_t* obj = malloc(sizeof(test_t));
	populate(test)(obj, test_class);

	obj->string = string;

	return obj;
}

int main(void) {
	test_t* obj = new test("Hallo Welt");

	class_t c = oop_get_class_from_obj((object_t*) obj);
	printf("class: %s\n", oop_get_class_name(c));
	printf("superclass: %s\n", oop_get_class_name(oop_get_super_class(c)));
	printf("instanceof test: %i\n", instanceof(obj, test_class));
	printf("instanceof object: %i\n", instanceof(obj, object_class));

	obj->print(obj);
	obj->destruct(obj);
	return 0;
}
