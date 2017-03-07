#include <stdlib.h>
#include <stdio.h>

#include "oop.h"

#define test construct(test)

class_t test_class;

__attribute__ ((constructor)) 
static void add_test_class(void) {
	test_class.id = new_class("test", NO_SUPER_CLASS, true);
}

typedef struct test {
	meta_object_t meta;
	void (*destruct)(struct test*);
	const char* string;
	void (*print)(struct test*);
} test_t;

void test_method_print(test_t* this) {
	printf("%s\n", this->string);
}
void test_method_destruct(test_t* this) {
	free(this);
}

test_t* test_method_construct(const char* string) {
	test_t* obj = malloc(sizeof(test_t));
	obj->string = string;
	obj->destruct = test_method_destruct;
	obj->print = test_method_print;

	return obj;
}

int main(void) {
	test_t* obj = new test("Hallo Welt");

	obj->print(obj);

	obj->destruct(obj);

	return 0;
}
