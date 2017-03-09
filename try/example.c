#include "try.h"

#include <stdio.h>

void function_with_throw(const char* e) {
	subtry();
	
	throw(e);
}

int main(void) {
	// simple try-catch
	try {
		throw("Hello World 1");
	} catch(const char* e) {
		printf("Catch 1: %s\n", e);
	} endtry;

	// try-catch from function
	try {
		trycall function_with_throw("Hello World 2");
	} catch(const char* e) {
		printf("Catch 2: %s\n", e);
	} endtry;

	// nested try-catch
	try {
		const char* string;

		try {
			throw("Hello World 3");
		} catch(const char* e) {
			string = e;
		} endtry;

		throw(string);
	} catch(const char* e) {
		printf("Catch 3: %s\n", e);
	} endtry;

	// nested try-catch with throw in catch-clause
	try {
		tpush();
		try {
			throw("Hello World 4");
		} catch(const char* e) {
			cthrow(e);
		} endtry;
	} catch(const char* e) {
		printf("Catch 4: %s\n", e);
	} endtry;

	return 0;
}
