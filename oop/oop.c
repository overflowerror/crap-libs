#include "oop.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class_id_t class_ids = 0;

meta_class_t classes[MAX_CLASSES];

class_id_t oop_add_class(const char* name, class_t super, bool instanceable) {
	if (oop_class_exists(name))
		return oop_id_from_name(name);

	classes[class_ids] = (meta_class_t) {
		.name = name,
		.super = super.id,
		.instanceable = instanceable
	};
	return class_ids++;
}

bool oop_instance_of_id(void* object, class_id_t id) {
	class_id_t cid = ((object_t*) object)->meta_obj.type.id;
	meta_class_t c = classes[cid];
	if (cid == id)
		return true;
	// iterate through superclasses of object
	for (; c.super != NO_CLASS_ID; c = classes[c.super]) {
		if (c.super == id)
			return true;
	}
	return false;
}

bool oop_instance_of(void* object, class_t type) {
	return oop_instance_of_id(object, type.id);
}

const char* oop_get_class_name_by_id(class_id_t id) {
	return classes[id].name;
}

const char* oop_get_class_name(class_t type) {
	return oop_get_class_name_by_id(type.id);
}

class_id_t oop_id_from_name(const char* class_name) {
	for (int i = 0; i < class_ids; i++) {
		if (strcmp(class_name, classes[i].name) == 0)
			return i;
	}
	return NO_CLASS_ID;
}

bool oop_class_exists(const char* class_name) {
	return oop_id_from_name(class_name) != NO_CLASS_ID;
}

class_t oop_class_from_id(class_id_t id) {
	return (class_t) {.id = id};
}

class_t oop_get_super_class(class_t type) {
	return oop_class_from_id(classes[type.id].super);
}

class_t oop_get_class_from_obj(object_t* obj) {
	return oop_class_from_id(((object_t*) obj)->meta_obj.type.id);
}


// defined by class macro in h-file
class_t object_class;

void method(object, destruct)(object_t* obj) {
	free(obj);
}

object_t* method(object, construct)() {
	object_t* obj = malloc(sizeof(object_t));
	populate(object)(obj, object_class);
	return obj;
}

void method(object, populate)(object_t* obj, class_t type) {
	obj->meta_obj.type = type;
	add_method(obj, object, destruct);
}
