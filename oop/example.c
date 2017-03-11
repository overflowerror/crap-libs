#include <stdlib.h>
#include <stdio.h>

#include "oop.h"

#define Test construct(Test)

class(Test, Object_class, true) {
	extends(Object_t);	

	const char* string;

	void (*print)(defclass Test*);
	void (*destruct)(defclass Test*);
} Test_t;

void method(Test, print)(Test_t* this) {
	printf("%s\n", this->string);
}
void method(Test, destruct)(Test_t* this) {
	this->super.destruct((Object_t*) this);
}

void method(Test, populate)(Test_t* obj, class_t c) {
	populate(Object)((Object_t*) obj, c);

	add_method(obj, Test, destruct);
	add_method(obj, Test, print);
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
	printf("instanceof test: %i\n", instanceof(obj, Test_class));
	printf("instanceof object: %i\n", instanceof(obj, Object_class));

	obj->print(obj);
	obj->destruct(obj);
	return 0;
}
