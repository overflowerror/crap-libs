#include "memory.h"

#include <stdio.h>

int main(void) {

	const char* str = "Hallo Welt";
	
	char* tmp = clone_string(str);

	printf("%s\n", tmp);

	free(tmp);

	tmp = allocate((size_t) 1 << 63);

	free(tmp);

	return 0; 
}
