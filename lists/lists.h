#ifndef LISTS_H
#define LISTS_H

#include "../oop.h"

extern interface(Countable)
#define Countable_interface size_t (*length)(void*); 
extern interface(List)
#define List_interface void (*add)(void*, void*); void* (*get)(void*, size_t); void (*remove)(void*, size_t);
extern interface(Stack)
#define Stack_interface void (*push)(void*, void*); void* (*pop)(void*);

#endif
