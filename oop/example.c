#include <stdlib.h>
#include <stdio.h>

#include "oop.h"

#define Test construct(Test)

class(Test, Object_class, (interfaces){1 namely {Cloneable_class}}, true) {
	extends(Object_t);
	implements(Cloneable);

	const char* string;

	void (*print)(defclass Test*);
	void (*destruct)(defclass Test*);
} Test_t;

void method(Test, print)(Test_t*);
void method(Test, destruct)(Test_t*);
void* method(Test, clone)(void*);
void method(Test, populate)(Test_t*, class_t);
Test_t* method(Test, construct)(const char*);


void method(Test, print)(Test_t* this) {
	printf("%s\n", this->string);
}
void method(Test, destruct)(Test_t* this) {
	this->super.destruct((Object_t*) this);
}

void* method(Test, clone)(void* obj) { // parameter void* because of interface
	Test_t* test = new Test("");
	test->string = ((Test_t*) obj)->string;
	return (void*) test;
}

void method(Test, populate)(Test_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);

	add_method(obj, Test, destruct);
	add_method(obj, Test, print);
	add_method(obj, Test, clone);
}

Test_t* method(Test, construct)(const char* string) {
	Test_t* obj = malloc(sizeof(Test_t));
	populate(Test)(obj, Test_class);

	obj->string = string;

	return obj;
}

int main(void) {
	Test_t* obj = new Test("Hallo Welt");

	class_t c = oop_get_class_from_obj((Object_t*) obj);
	printf("class: %s\n", oop_get_class_name(c));
	printf("superclass: %s\n", oop_get_class_name(oop_get_super_class(c)));
	printf("instanceof Test: %i\n", instanceof(obj, Test_class));
	printf("instanceof Object: %i\n", instanceof(obj, Object_class));
	printf("instanceof Cloneable: %i\n", instanceof(obj, Cloneable_class));

	obj->print(obj);
	obj->destruct(obj);
	return 0;
}
