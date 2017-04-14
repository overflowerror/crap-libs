#ifndef LISTS_H
#define LISTS_H

#include "../oop.h"

typedef Object_t Countable_t;
extern interface(Countable)
#define Countable_interface size_t (*length)(void*); 
#define Countable(...) NULL; _Pragma("GCC error \"Cannot make instance of interface Countable.\"");

typedef Object_t List_t;
extern interface(List)
#define List_interface void (*add)(void*, void*); void* (*get)(void*, size_t); void (*remove)(void*, size_t);
#define List(...) NULL; _Pragma("GCC error \"Cannot make instance of interface List.\"");

typedef Object_t Stack_t;
extern interface(Stack)
#define Stack_interface void (*push)(void*, void*); void* (*pop)(void*);
#define Stack(...) NULL; _Pragma("GCC error \"Cannot make instance of interface Stack.\"");

/*typedef Object_t Set_t;
extern interface(Set)
#define Set_interface void (*add)(void*, void*); void (*remove)(void*, void*); void* (*contains)(void*, void*);
#define Set(...) NULL; _Pragma("GCC error \"Cannot make instance of interface Set.\"");
*/

typedef struct iterator_args {
	void* list;
	void* parameter;
	void* obj;
	int num; // -1 if no id
} iterator_args;

typedef bool (*iterator)(iterator_args);

typedef Object_t Iterateable_t;
extern interface(Iterateable)
#define Iterateable_interface bool (*iterate)(void*, iterator, void*)
#define Iterateable(...) NULL; _Pragma("GCC error \"Cannot make instance of interface Iterateable.\"");

#endif
