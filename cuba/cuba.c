#include <stdio.h>
#include "cuba.h"
#include "lexer.c"

#define MAX_LINE_LENGTH 1000
CUBA_STRING readfile(const char* path) {
	// init builder
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 100);
	// init file
	FILE* ptr;
	ptr = fopen(path, "rb"); 
	if (ptr == NULL) { CUBA_PANIC_CODE("FILE ERROR"); }
	// get size of file
	long file_size;
	fseek(ptr, 0L, SEEK_END);
	file_size = ftell(ptr);
	fseek(ptr, 0L, SEEK_SET);
	// init buffer
	char* buffer = malloc(file_size);
	// read file
	fread(buffer, sizeof(char), file_size, ptr);
	// close file
	fclose(ptr);
	// get string from string builder
	CUBA_STRING str;
	CUBA_STRING_INIT(&str, buffer, file_size);
	// !!CUBA_STRING_BUILDER_PUSHC(&builder, buffer);
	// CUBA_STRING_BUILDER_SPLICE(&builder, 0, -1);
	// CUBA_STRING_BUILD_FINALIZE(&builder, str);
	// return
	return str;
}

int main(int argc, char** argv) {
	CUBA_STRING fcontent = readfile("E:/so2u/GITHUB/cuba/cuba-c/tests/cb/test1.cb");
	CUBA_LEXER lexer;
	tokenize(fcontent, &lexer);
	printTokens(&lexer);

	return 0;
}
