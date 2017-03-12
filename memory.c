#include "memory.h"
#include "try.h"
#include "exceptions/stdex.h"

#include <errno.h>
#include <string.h>

void allocate_sub(size_t size, void** ptr) { throws(OutOfMemoryException_t);
	*ptr = malloc(size);
	if (*ptr == NULL) {
		throw(new OutOfMemoryException());
	}
}

void* allocate_o(class_t c, size_t size) { throws(OutOfMemoryException_t, ClassNotInstanceableException_t);
	if (!oop_is_instanceable(c))
		throwr(new ClassNotInstanceableException(oop_get_class_name(c)), NULL);
	void* ptr;
	sr_(allocate_sub(size, &ptr), NULL);
	return ptr;
}

void* allocate(size_t size) { throws(OutOfMemoryException_t);
	void* ptr;
	sr_(allocate_sub(size, &ptr), NULL);
	return ptr;
}

void reallocate_sub(size_t size, void** ptr, void* old) { throws(OutOfMemoryException_t);
	*ptr = realloc(old, size);
	if (*ptr == NULL) {
		throw(new OutOfMemoryException());
	}
}

void* reallocate(void* old, size_t size) { throws(OutOfMemoryException_t);
	void* ptr;
	sr_(reallocate_sub(size, &ptr, old), NULL);
	return ptr;
}

void* clone(const void* org, size_t size) { throws(OutOfMemoryException_t);
	void* ptr;
	sr_(allocate_sub(size, &ptr), NULL);
	memcpy(ptr, org, size);
	return ptr;
}
