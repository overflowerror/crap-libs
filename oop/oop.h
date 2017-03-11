#ifndef OOP_H
#define OOP_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#define interface(name) class_t name##_class; __attribute__ ((constructor)) static void add_##name##_interface(void) { name##_class.id = oop_add_class(#name, true, NO_SUPER_CLASS, NO_INTERFACES, false);}
#define class(name, superclass, interfaces, instanceable) class_t name##_class; __attribute__ ((constructor)) static void add_##name##_class(void) { name##_class.id = oop_add_class(#name, false, superclass, interfaces, instanceable);} typedef struct name
#define method(class, method) class ##_method_## method
#define add_method(object, class, method) object->method = class ##_method_## method

#define implements(i) i##_interface
#define extends(type) type super

#define construct(name) name ##_method_construct
#define populate(name) name ##_method_populate

#define instanceof(obj, class) oop_instance_of(obj, class)

#define call(obj, method) (obj)->method((obj))
#define new
#define defclass	struct

#define MAX_CLASSES 1024
#define MAX_INTERFACES 20 // per class
#define NO_CLASS_ID -1
#define NO_SUPER_CLASS (class_t){.id = NO_CLASS_ID}
#define NO_INTERFACES (interfaces){.nr = 0}

#define namely ,
#define and ,

typedef int class_id_t;

typedef struct meta_class {
	const char* name;
	bool interface;
	class_id_t super;
	class_id_t interfaces[MAX_INTERFACES];
	int nrinterfaces;
	bool instanceable;
} meta_class_t;

typedef struct class {
	class_id_t id;
} class_t;

typedef struct iflist {
	int nr;
	class_t interfaces[MAX_INTERFACES];
} iflist_t;
typedef iflist_t interfaces;

typedef struct meta_object {
	class_t type;
} meta_object_t;

class_id_t oop_add_class(const char*, bool, class_t, iflist_t, bool);

#define Object construct(Object)
extern class(Object, NO_SUPER_CLASS, NO_INTERFACES, true) {
	meta_object_t meta_obj;
	void (*destruct)(defclass Object*);
} Object_t;

extern interface(Cloneable)
#define Cloneable_interface void*(*clone)(void*)

bool oop_instance_of_id(void*, class_id_t);
bool oop_instance_of(void*, class_t);
const char* oop_get_class_name(class_t);
class_id_t oop_id_from_name(const char*);
bool oop_class_exists(const char*);
class_t oop_class_from_id(class_id_t);
class_t oop_get_super_class(class_t);
class_t oop_get_class_from_obj(Object_t*);

Object_t* method(Object, construct)(void);
void method(Object, populate)(Object_t* obj, class_t);

#endif
