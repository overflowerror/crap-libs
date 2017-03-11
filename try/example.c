#include "try.h"

#include "../oop/oop.h"
#include "exceptions/exceptions.h"

#include <stdio.h>

void function(void) { throws(Exception_class)

	throw(new Exception("This is an uncaught exception."));
}

int main(void) {
	try {
		throw(new Exception("This is a caught exception."));
	} catch(Exception_class, Exception_t* e) {
		printf("Caught: %s\n", e->msg);
		e->destruct(e);
	} endtry;
	
	function();

	return 0;
}
