#ifndef OOP_H
#define OOP_H

#include <stdbool.h>
#include <stdarg.h>

#define construct(name) name ##_method_construct

#define call(obj, method) (obj)->method((obj))
#define new

#define MAX_CLASSES 1024
#define NO_SUPER_CLASS -1
#define NO_CLASS -1

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
	class_t class;
} meta_object_t;

typedef struct object {
	meta_object_t meta_obj;
	void (*destruct)(struct object*);
} object_t;

class_id_t new_class(const char*, class_id_t, bool);
bool instance_of_id(void*, class_id_t);
bool instance_of(void*, class_t);
const char* get_class_name(class_t);
class_id_t id_from_name(const char*);
bool class_exists(const char*);

#endif
