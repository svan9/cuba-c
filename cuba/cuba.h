#ifndef CUBA_H
#define CUBA_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "dictionary.h"
#include <stdbool.h>
#include "nan.h"

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif

#define TTK_TEXT     		  ENGL
#define TTK_NUMBER    		"0123456789" 
#define TTK_QUOTE     		"\""
#define TTK_OPENFIG   		"{" 
#define TTK_CLOSEFIG  		"}" 
#define TTK_OPENSQU   		"[" 
#define TTK_CLOSESQU  		"]" 
#define TTK_OPENROU   		"(" 
#define TTK_CLOSEROU  		")" 
#define TTK_OPENTRI   		"<" 
#define TTK_CLOSETRI  		">" 
#define TTK_ENDLINE    		";"
#define TTK_SPECIAL   		"\\!@|/-=+_*&^:`#~.?,$" // TTK_ENDLINE
#define TTK_SKIP      		" \t\n\r\v\b" 
#define TTK_SINGLECMM     "//"
#define TTK_MULTICMM      "***"
#define TTK_ESC						'\\'
#define TTK_FTEXTSP       TTK_TEXT TTK_NUMBER "_$"

#define CUBA_LEXER_TOKEN_LIST_AL 5

char* ctos(char c) {
	char* _new_string = malloc(2);
	_new_string[0] = c;
	_new_string[1] = '\0';
	return _new_string;
}

typedef enum {
	// 0123456789
	TK_NUMBER,
	// "~(\")*"
	TK_STRING,
	// '{' '}'
	TK_OPENFIG, TK_CLOSEFIG, 
	// '[' ']'
	TK_OPENSQU, TK_CLOSESQU,
	// '(' ')'
	TK_OPENROU, TK_CLOSEROU, 
	// '<' '>'
	TK_OPENTRI, TK_CLOSETRI,
	// [a-zA-Z]
	TK_TEXT,
	// '\\!@|/-=+_*&^:;`#~.?,'
	TK_SPECIAL,
	// ";"
	TK_ENDLINE,
	// '//.*'
	TK_SINGLECMM,
	// '***[.*]***'
	TK_MULTICMM
} CubaTokenKind;

typedef enum {
	// '{.*}'	
	EL_BLOCK,
	// '(.*)'
	EL_ARRAY,
	// '.*;'
	EL_LINE,

	EL_TEXT,
	
} CubaElementKind;

typedef struct {
	NanString content;
	CubaTokenKind kind;
} CubaToken;

CubaToken* CubaTokenCreate(CubaTokenKind kind, NanString content) {
	CubaToken* _token = malloc(sizeof(CubaToken));
	_token->content = content;
	_token->kind = kind;
	return _token;
}

typedef struct {
	void* content;
	CubaElementKind kind;
} CubaElement;


typedef struct {
	NanDynamicArray tokens;
	NanDynamicArray elements;
} CubaLexer;

void CubaLexerAppendToken(CubaLexer* self, CubaToken* tk) {
	NanDynamicArrayPush(&self->tokens, tk);
}

CubaLexer CubaLexerCreate() {
	CubaLexer lexer = {
		.tokens = NanDynamicArrayCreate(sizeof(CubaToken)),
		.elements = NanDynamicArrayCreate(sizeof(CubaElement))
	};
	return lexer;
}

char* stringifyTokenKind(CubaTokenKind kind) {
#define stringifyTokenKindLine(a) case a: return stringify(a);
	switch (kind) {
		stringifyTokenKindLine(TK_NUMBER)
		stringifyTokenKindLine(TK_STRING)
		stringifyTokenKindLine(TK_OPENFIG)
		stringifyTokenKindLine(TK_CLOSEFIG)
		stringifyTokenKindLine(TK_OPENSQU)
		stringifyTokenKindLine(TK_CLOSESQU)
		stringifyTokenKindLine(TK_OPENROU)
		stringifyTokenKindLine(TK_CLOSEROU)
		stringifyTokenKindLine(TK_OPENTRI)
		stringifyTokenKindLine(TK_CLOSETRI)
		stringifyTokenKindLine(TK_TEXT)
		stringifyTokenKindLine(TK_SPECIAL)
		stringifyTokenKindLine(TK_ENDLINE)
		stringifyTokenKindLine(TK_SINGLECMM)
		stringifyTokenKindLine(TK_MULTICMM)
	}

#undef stringifyTokenKindLine
}

void printTokens(CubaLexer* lexer) {
	for (int i = 0; i < lexer->tokens.size; i++) {
		CubaToken* tk = NanDynamicArrayAt(&lexer->tokens, i);
		char* kind = stringifyTokenKind(tk->kind);
		if (tk->content.size == 1) {
			printf("[kind='%s',  value='%c']\n", kind, *NanStringC_Str(tk->content.content));
		} else {
			printf("[kind='%s',  value='%s']\n", kind, NanStringC_Str(tk->content.content));
		}
	}
}

typedef struct {
	NanDynamicArray content;
} CubaLine;

typedef struct {
	NanDynamicArray content;
} CubaBlock;

typedef struct {
	bool is_allocator;
	CubaElement first;
	CubaElement second;
} CubaArrayElement;

typedef struct {
	NanString name;
	NanDynamicArray content;
} CubaKeyWord;

typedef NanDynamicArray CubaArray;

CubaBlock parse_block(CubaLexer* lexer, NanIterator* it);
CubaLine parse_line(CubaLexer* lexer, NanIterator* it);
CubaArray parse_array(CubaLexer* lexer, NanIterator* it);
void parse(CubaLexer* lexer);

#endif