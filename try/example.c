#include "try.h"

#include "../oop/oop.h"
#include "exceptions/exceptions.h"

#include <stdio.h>

void function(void) { throws(exception_class)

	throw(new exception("This is an uncaught exception."));
}

int main(void) {
	try {
		throw(new exception("This is a caught exception."));
	} catch(exception_class, exception_t* e) {
		printf("Caught: %s\n", e->msg);
		e->destruct(e);
	} endtry;
	
	function();

	return 0;
}
