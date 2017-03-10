#ifndef TRY_H
#define TRY_H

#include <stdbool.h>

#include "../oop/oop.h"
#include "../misc/unused.h"

typedef int try_t;

#define throws(...) subtry();

#define try { bool _try_catch = false, _try_body = false; void* _try_data = NULL; try_t _try_id = try_new(); void _try_f(void)
#define pcatch(e) ; _try_f(); if (try_has_catch(_try_id)) { e = try_catch(_try_id); try_remove(_try_id); do 

#define catch(c, ex) ; if (!_try_body) { _try_f(); _try_body = true; _try_data = try_catch(_try_id); _try_catch = try_has_catch(_try_id); try_remove(_try_id); } if (_try_catch && instanceof(_try_data, c)) { _try_catch = false; ex = _try_data; do  

#define endtry while(false); } if (_try_catch) { UNUSED(_try_body); UNUSED(_try_data); }};
#define throw(e) { try_throw(_try_id, (void*) e); return; }

#define until(condition) ; do { try_reset(_try_id); _try_f(); } while(try_has_catch(_try_id) == condition); void* _try_result = try_catch(_try_id); try_remove(_try_id); if(true) { do
#define get_thrown() (_try_result)
#define failed false
#define succeeded true

#define subtry() try_t _try_id = try_pop();
#define s_(f) try_push(_try_id); f; if(_try_has_catch(_try_id)) return;

#define tpush() try_push(_try_id)
#define cthrow(e) _try_id = try_pop(); throw(e);

#define NO_TRY_BODY -1

try_t try_new(void);
bool try_has_catch(try_t);
void* try_catch(try_t);
void try_remove(try_t);
void try_throw(try_t, void*);
try_t try_pop(void);
void try_push(try_t);
void try_reset(try_t);

#endif
