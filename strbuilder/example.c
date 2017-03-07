#include <stdlib.h>
#include <stdio.h>

#include "../oop/oop.h"
#include "strbuilder.h"

int main(void) {
	strbuilder_t* builder = new strbuilder("Hallo");

	builder->add(builder, " Welt");
	builder->add(builder, "!");
	builder->build(builder);

	const char* string = builder->get(builder);
	printf("%s\n", string);
	
	builder->destruct(builder);	

	return 0; 
}
