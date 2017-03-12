#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <string.h>

#include "oop.h"
#include "try.h"
#include "exceptions/stdex.h"

#define allocate_object(type) allocate_o(type##_class, sizeof(type##_t));

#define clone_string(s) clone((void*) s, strlen(s) + 1)
#define clone_obj(obj, class) clone((void*) obj, sizeof(class))

void* allocate_o(class_t, size_t);
void* allocate(size_t);
void* reallocate(void*, size_t);
void* clone(const void*, size_t);

#endif
