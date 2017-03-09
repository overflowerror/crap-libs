#ifndef OOP_H
#define OOP_H

#include <stdbool.h>
#include <stdarg.h>


#define class(name, type, superclass, instanceable) __attribute__ ((constructor)) static void add_##name##_class(void) { type.id = oop_add_class(#name, superclass, instanceable); } typedef struct name
#define method(class, method) class ##_method_## method
#define add_method(object, class, method) object->method = class ##_method_## method

#define extends(type) type super

#define construct(name) name ##_method_construct
#define populate(name) name ##_method_populate


#define call(obj, method) (obj)->method((obj))
#define new

#define MAX_CLASSES 1024
#define NO_CLASS_ID -1
#define NO_SUPER_CLASS (class_t){.id = NO_CLASS_ID}



typedef int class_id_t;

typedef struct meta_class {
	const char* name;
	class_id_t super;
	bool instanceable;
} meta_class_t;

typedef struct class {
	class_id_t id;
} class_t;

typedef struct meta_object {
	class_t type;
} meta_object_t;

class_id_t oop_add_class(const char*, class_t, bool);

#define object construct(object)
extern class_t object_class;

class(object, object_class, NO_SUPER_CLASS, true) {
	meta_object_t meta_obj;
	void (*destruct)(struct object*);
} object_t;


bool oop_instance_of_id(void*, class_id_t);
bool oop_instance_of(void*, class_t);
const char* oop_get_class_name(class_t);
class_id_t oop_id_from_name(const char*);
bool oop_class_exists(const char*);

object_t* method(object, construct)(void);
void method(object, populate)(object_t* obj, class_t);

#endif
