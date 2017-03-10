#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <string.h>

#define clone_string(s) clone((void*) s, strlen(s) + 1)
#define clone_obj(obj, class) clone((void*) obj, sizeof(class))

void* allocate(size_t);
void* reallocate(void*, size_t);
void* clone(const void*, size_t);

#endif
