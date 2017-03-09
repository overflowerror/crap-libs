#include <stdlib.h>
#include <stdio.h>

#include "oop.h"

#define test construct(test)

class_t test_class;

class(test, test_class, object_class, true) {
	extends(object_t);	

	const char* string;

	void (*print)(struct test*);
	void (*destruct)(struct test*);
} test_t;

void method(test, print)(test_t* this) {
	printf("%s\n", this->string);
}
void method(test, destruct)(test_t* this) {
	this->super.destruct((object_t*) this);
}

void method(test, populate)(test_t* obj, const char* string) {
	populate(object)((object_t*) obj, test_class);

	obj->string = string;

	add_method(obj, test, destruct);
	add_method(obj, test, print);
}

test_t* method(test, construct)(const char* string) {
	test_t* obj = malloc(sizeof(test_t));
	populate(test)(obj, string);

	return obj;
}

int main(void) {
	test_t* obj = new test("Hallo Welt");

	obj->print(obj);

	obj->destruct(obj);

	return 0;
}
