#include "memory.h"
#include "../try/try.h"
#include "../try/exceptions/exceptions.h"

#include <errno.h>
#include <string.h>

void allocate_sub(size_t size, void** ptr) { throws(exception_t);
	*ptr = malloc(size);
	if (*ptr == NULL) {
		throw(new exception(strerror(errno)));
	}
}

void* allocate(size_t size) { throws(exception_t);
	void* ptr;
	s_(allocate_sub(size, &ptr));
	return ptr;
}

void reallocate_sub(size_t size, void** ptr, void* old) { throws(exception_t);
	*ptr = realloc(old, size);
	if (*ptr == NULL) {
		throw(new exception(strerror(errno)));
	}
}

void* reallocate(void* old, size_t size) { throws(exception_t);
	void* ptr;
	s_(reallocate_sub(size, &ptr, old));
	return ptr;
}

void* clone(const void* org, size_t size) { throws(exception_t);
	void* ptr;
	trycall allocate_sub(size, &ptr);
	memcpy(ptr, org, size);
	return ptr;
}
