#include "oop.h"
#include "memory.h"
#include "try.h"
#include "exceptions/stdex.h"
#include "misc.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class_id_t class_ids = 0;

meta_class_t classes[MAX_CLASSES];

class_id_t oop_add_class(const char* name, bool interface, class_t super, iflist_t iflist, bool instanceable) {
	if (oop_class_exists(name))
		return oop_id_from_name(name);

	classes[class_ids] = (meta_class_t) {
		.name = name,
		.interface = interface,
		.super = super.id,
		.nrinterfaces = iflist.nr,
		.instanceable = instanceable
	};

	for(int i = 0; i < iflist.nr; i++) {
		classes[class_ids].interfaces[i] = iflist.interfaces[i].id;
	}

	return class_ids++;
}

bool oop_instance_of_id(void* object, class_id_t id) {
	class_id_t cid = ((Object_t*) object)->meta_obj.type.id;
	meta_class_t c = classes[cid];

	if (cid == id)
		return true;
	for (int i = 0; i < c.nrinterfaces; i++) {
		if (c.interfaces[i] == id)
			return true;
	}

	// iterate through superclasses of object
	while (c.super != NO_CLASS_ID) {
		if (c.super == id)
			return true;
		c = classes[c.super];
		for (int i = 0; i < c.nrinterfaces; i++) {
			if (c.interfaces[i] == id)
				return true;
		}
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

bool oop_is_instanceable(class_t c) {
	return classes[c.id].instanceable;
}

class_t oop_class_from_id(class_id_t id) {
	return (class_t) {.id = id};
}

class_t oop_get_super_class(class_t type) {
	return oop_class_from_id(classes[type.id].super);
}

class_t oop_get_class_from_obj(Object_t* obj) {
	return oop_class_from_id(((Object_t*) obj)->meta_obj.type.id);
}

void oop_check_interface(class_t c, Object_t* obj) {
	throws(IllegalArgumentException_t);

	if (!instanceof(obj, c))
		throw(new (IllegalArgumentException)("Object is not instance of interface."));
}


// defined by class macro in h-file
class_t Object_class;

// defined by interface macro in h-file
class_t Cloneable_class;
class_t Compareable_class;


void method(Object, destruct)(Object_t* obj) {
	free(obj);
}

Object_t* method(Object, construct)() { throws(OutOfMemoryException_t);
	sr_(Object_t* obj = allocate_object(Object), NULL);
	populate(Object)(obj, Object_class);
	return obj;
}

int method(Object, hashCode)(Object_t* obj) {
	UNUSED(obj);
	return 0;
}

void method(Object, populate)(Object_t* obj, class_t type) {
	obj->meta_obj.type = type;
	add_method(obj, Object, destruct);
}


int method(DefMethods, hashCode)(void* obj) {
	return ((Object_t*) obj)->hashCode(obj);
}
