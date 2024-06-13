#include <stdio.h>
#include "nan.h"
#include "cuba.h"
#include "lexer.c"
#include "parser.c"

#define MAX_LINE_LENGTH 1000

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
