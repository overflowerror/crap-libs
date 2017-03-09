#ifndef TRY_H
#define TRY_H

#include <stdbool.h>

typedef int try_t;

#define try do { try_t _try_id = try_new(); void _try_f(void)
#define catch(e) ; _try_f(); if (try_has_catch(_try_id)) { e = try_catch(_try_id); try_remove(_try_id); do 
#define endtry while(false); } } while(false);
#define throw(e) try_throw(_try_id, (void*) e); return;
#define subtry() try_t _try_id = try_pop();
#define tpush() try_push(_try_id)
#define cthrow(e) _try_id = try_pop(); throw(e);
#define trycall try_push(_try_id);


try_t try_new(void);
bool try_has_catch(try_t);
void* try_catch(try_t);
void try_remove(try_t);
void try_throw(try_t, void*);
try_t try_pop(void);
void try_push(try_t);

#endif
