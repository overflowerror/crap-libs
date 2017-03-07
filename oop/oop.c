#include "oop.h"

#include <string.h>

class_id_t class_ids = 0;

meta_class_t classes[MAX_CLASSES];

class_id_t new_class(const char* name, class_id_t super, bool instanceable) {
	classes[class_ids] = (meta_class_t) {
		.name = name,
		.super = super,
		.instanceable = instanceable
	};
	return class_ids++;
}

bool instance_of_id(void* object, class_id_t id) {
	if (sizeof (object) < sizeof (object_t))
		return false; // not an object
	object_t* obj = (object_t*) object;
	return obj->meta_obj.class.id == id;
}

bool instance_of(void* object, class_t class) {
	return instance_of_id(object, class.id);	
}

const char* get_class_name_by_id(class_id_t id) {
	return classes[id].name;
}

const char* get_class_name(class_t class) {
	return get_class_name_by_id(class.id);
}

class_id_t id_from_name(const char* class_name) {
	for (int i = 0; i < class_ids; i++) {
		if (strcmp(class_name, classes[i].name) == 0)
			return i;
	}
	return NO_CLASS;
}

bool class_exists(const char* class_name) {
	return id_from_name(class_name) != NO_CLASS;
}
