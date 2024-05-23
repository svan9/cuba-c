#ifndef CUBA_H
#define CUBA_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "utils.h"
#include "dictionary.h"

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
#define TTK_SPECIAL   		"\\!@|/-=+_*&^:;`#~.?,$" 
#define TTK_SKIP      		" \t\n\r\v\b" 
#define TTK_ESC						'\\'

#define GETCODELINE() __LINE__
#define GETCODEFILE() __FILE__

#define true 1
#define false 0


void* execute(char code[]);

typedef struct {
	char* content;
	size_t size;
} CUBA_STRING;
typedef struct {
	char* content;
	size_t size;
	size_t cursor;
} CUBA_STRING_IT;
typedef struct {
	size_t alignment;
	size_t capacity;
	size_t size;
	char* begin;
} CUBA_STRING_BUILDER;

CUBA_STRING CUBA_STRING_FROM_CHAR(char c) {
	CUBA_STRING str;
	str.content = malloc(1);
	str.content[0] = c;
	str.size = 1;
	return str;
}

void CUBA_STRING_BUILDER_INIT(CUBA_STRING_BUILDER* parent, size_t alignment) {
	parent->alignment = alignment;
	char* _new_begin;
	size_t _aligned_size = parent->alignment;
	_new_begin = realloc(parent->begin, _aligned_size);
	parent->capacity = _aligned_size;
}
void CUBA_STRING_BUILDER_REALOC(CUBA_STRING_BUILDER* parent, size_t newsize) {
	char* _new_begin;
	size_t _aligned_size = newsize + parent->alignment - newsize % parent->alignment;
	_new_begin = realloc(parent->begin, _aligned_size);
	parent->capacity = _aligned_size;
}

void CUBA_STRING_BUILDER_PUSHC(CUBA_STRING_BUILDER* parent, char c) {
	if (parent->size+1 > parent->capacity) {
		CUBA_STRING_BUILDER_REALOC(parent, parent->size+1);
	}
	parent->begin[parent->size++] = c;
}
void CUBA_STRING_BUILDER_PUSHIT(CUBA_STRING_BUILDER* parent, CUBA_STRING_IT* it) {
	if (parent->size+1 > parent->capacity) {
		CUBA_STRING_BUILDER_REALOC(parent, parent->size+1);
	}
	parent->begin[parent->size++] = CUBA_SIT_GETCH(it);
}

void CUBA_STRING_BUILDER_PUSHS(CUBA_STRING_BUILDER* parent, const char* str) {
	size_t len = strlen(str);
	if (parent->size+len > parent->capacity) {
		CUBA_STRING_BUILDER_REALOC(parent, parent->size+len);
	}
	for (int i = 0; i < len; i++) {
		parent->begin[parent->size+i] = str[i];
	}
}

CUBA_STRING CUBA_STRING_BUILD_FINALIZE(CUBA_STRING_BUILDER* parent, CUBA_STRING* str) {
	str->size = parent->size;
	str->content = parent->begin;
	return *str;
}

CUBA_STRING WCUBA_STRING_BUILD_FINALIZE(CUBA_STRING_BUILDER* parent) {
	CUBA_STRING _out_str;
	_out_str.size = parent->size;
	_out_str.content = parent->begin;
	return _out_str;
}


void CUBA_STRING_PUSH(CUBA_STRING* ori, const char* next) {
	CUBA_STRING* cr_ = {0};
	cr_->size = (ori->size+strlen(next));
	cr_->content = malloc(cr_->size);
	size_t it;
	it = 0;
	while (it < ori->size) {
		cr_->content[it] = ori->content[it]; it++;
	}
	it = 0;
	while (it < strlen(next)) {
		cr_->content[(ori->size-1)+it] = next[it]; it++;
	}

	ori->size = cr_->size;
	ori->content = cr_->content;
}

void CUBA_STRING_PUSHC(CUBA_STRING* ori, char next) {
	CUBA_STRING* cr_ = {0};
	cr_->size = (ori->size+1);
	cr_->content = malloc(cr_->size);
	size_t it;
	it = 0;
	while (it < ori->size) {
		cr_->content[it] = ori->content[it]; it++;
	}
	cr_->content[ori->size] = next;

	ori->size = cr_->size;
	ori->content = cr_->content;
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
} CUBA_TOKEN_KIND;

typedef struct {
	CUBA_TOKEN_KIND kind;
	CUBA_STRING value;
} CUBA_TOKEN;

typedef struct {
	size_t alignment;
	size_t capacity;
	size_t size;
	CUBA_TOKEN* begin;
} CUBA_TOKEN_LIST;


char* READ_LINE_FROM_FILE(int line, const char* file) {
	const int MAX_LINE_LENGTH = 1000; 	
	FILE * fp;
	fp = fopen(file, "r");
  char* chunk = malloc(MAX_LINE_LENGTH);
	size_t nut = 0;
	while(fgets(chunk, MAX_LINE_LENGTH, fp) != NULL) {
		if ((nut++) >= (line-1)) { break; }
	}
	fclose(fp);
	return chunk;
}


#define CUBA_PANIC_CODE(message) WCUBA_PANIC_CODE(GETCODELINE(), GETCODEFILE(), message)

void WCUBA_PANIC_CODE(int line, const char* path, const char* message) {
	char* _line;
	_line = trim(READ_LINE_FROM_FILE(line, path));

	printf("error at %s:%i (%s)", path, line, message);
	printf("\n\t%s", _line);
	printf("\n\t^");
	exit(1);
}

void CUBA_TOKEN_LIST_INIT(CUBA_TOKEN_LIST* parent, size_t alignment) {
	parent->alignment = alignment;
	CUBA_TOKEN* _new_begin;
	size_t _aligned_size = parent->alignment;
	_new_begin = realloc(parent->begin, sizeof(CUBA_TOKEN)*_aligned_size);
	parent->capacity = _aligned_size;
}

void CUBA_TOKEN_LIST_REALOC(CUBA_TOKEN_LIST* parent, size_t newsize) {
	CUBA_TOKEN* _new_begin;
	size_t _aligned_size = newsize + parent->alignment - newsize % parent->alignment;
	_new_begin = realloc(parent->begin, sizeof(CUBA_TOKEN)*_aligned_size);
	parent->capacity = _aligned_size;
}

void CUBA_TOKEN_LIST_PUSH(CUBA_TOKEN_LIST* parent, CUBA_TOKEN token) {
	if (parent->size+1 > parent->capacity) {
		CUBA_TOKEN_LIST_REALOC(parent, parent->size+1);
	}
	parent->begin[parent->size++] = token;
}

int CUBA_TOKEN_LIST_IS_VALID_INDEX(CUBA_TOKEN_LIST* parent, size_t index) {
	return (index < parent->size && index >= 0);
}

#ifdef NO_PUT_ERROR
	#define CUBA_TOKEN_LIST_AT(parent, index) \
		ACUBA_TOKEN_LIST_AT(parent, index)
#else
	#define CUBA_TOKEN_LIST_AT(parent, index) \
		WCUBA_TOKEN_LIST_AT(parent, index, GETCODELINE(), GETCODEFILE())
#endif


CUBA_TOKEN ACUBA_TOKEN_LIST_AT(CUBA_TOKEN_LIST* parent, size_t index) {
	if (!CUBA_TOKEN_LIST_IS_VALID_INDEX(parent, index)) {
		WCUBA_PANIC_CODE(GETCODELINE(), GETCODEFILE(), "index is invalid");
	}
	return parent->begin[index];
}

CUBA_TOKEN WCUBA_TOKEN_LIST_AT(CUBA_TOKEN_LIST* parent, size_t index, int line, const char* file) {
	if (!CUBA_TOKEN_LIST_IS_VALID_INDEX(parent, index)) {
		WCUBA_PANIC_CODE(line, file, "index is invalid");
	}
	return parent->begin[index];
}

typedef struct {
	CUBA_TOKEN_LIST tokens;
} CUBA_LEXER;

void CUBA_LEXER_APPEND_TOKEN(CUBA_LEXER* lexer, CUBA_TOKEN token) {
	CUBA_TOKEN_LIST_PUSH(&lexer->tokens, token);
}


char CUBA_SIT_GETCH(CUBA_STRING_IT* it) {
	return it->content[it->cursor];
}

char CUBA_SIT_GETCHS(CUBA_STRING_IT* it, int s) {
	if (it->cursor+s < 0 && it->cursor+s > it->size) {
		return it->content[it->cursor];
	}
	return it->content[it->cursor+s];
}

void CUBA_SIT_NEXT(CUBA_STRING_IT* it) {
	it->cursor++;
}

boolean IS_CHAR_IN_STRING(char c, const char* str) {
	size_t len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == c) return true;
	}
	return false;
}


CUBA_STRING_IT CUBA_STRING_GETIT(CUBA_STRING* str) {
	CUBA_STRING_IT it;
	it.content = str->content;
	it.size    = str->size;
	it.cursor  = 0;
	return it;
}



#endif