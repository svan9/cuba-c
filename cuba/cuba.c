#include <stdio.h>
#include "nan.h"
#include "cuba.h"
#include "lexer.c"
#include "parser.c"

#define MAX_LINE_LENGTH 1000
// read file by path
NanString readfile(const char* path) {
	// init builder
	NanStringBuilder builder = NanStringBuilderCreate(100);
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
	NanString str;
	NanString_INIT(&str, buffer, file_size);
	free(buffer); free(ptr);
	return str;
}

// check is valid file path
bool isFilePath(const char* path) {
	return access(path, F_OK);
}

// compile program
CubaLexer compileProgram(const char* path) {
	// read file
	NanString fcontent = readfile(path);
	// allocate lexer
	CubaLexer lexer = CubaLexerCreate();
	// tokenize
	tokenize(fcontent, &lexer);
	// parse @CUBA_LEXER::elements
	parse(&lexer);
	// return lexer cast
	return lexer;
}

/* // todo flags 
*  [0] catch file path & compile file
#  [1] -l --Lang <string>  (use keywords on spec lang [ENGL|TURT]) & default - TURT ?
#  [2] -i --Interpret      (use interpreter)
*/
void parseArguments(int argc, char** argv) {
	// ignore argv[0] (- is program name)
	for (int i = 1; i < argc; i++) {
		// [0] 
		if (isFilePath(argv[i])) { compileProgram(argv[i]); }
		
	}
}


// after label `_start`
int main(int argc, char** argv) {
	// parse program arguments
	parseArguments(argc, argv);	
	// standart exit of program
	return 0;
}
