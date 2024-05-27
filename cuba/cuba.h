#ifndef CUBA_H
#define CUBA_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "utils.h"
#include "dictionary.h"
#include <stdbool.h>

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

#define GETCODELINE() __LINE__
#define GETCODEFILE() __FILE__
#define stringify(a) #a
#define callpoint() printf("called from: %s:%i\n",  GETCODEFILE(), GETCODELINE());
#define ppp callpoint()
#define pppp {callpoint()}

#define CUBA_PANIC_CODE(message) WCUBA_PANIC_CODE(GETCODELINE(), GETCODEFILE(), message)

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

void WCUBA_PANIC_CODE(int line, const char* path, const char* message) {
	char* _line;
	_line = trim(READ_LINE_FROM_FILE(line, path));

	printf("error at %s:%i (%s)", path, line, message);
	printf("\n\t%s", _line);
	printf("\n\t^");
	exit(1);
}

#define CUBA_LEXER_TOKEN_LIST_AL 5

void* execute(char code[]);

typedef struct {
	size_t size;
	char* content;
} CUBA_STRING;
typedef struct {
	size_t size;
	size_t cursor;
	char* content;
} CUBA_STRING_IT;
typedef struct {
	size_t alignment;
	size_t capacity;
	size_t size;
	char* begin;
} CUBA_STRING_BUILDER;

char* ctos(char c) {
	char* _new_string = malloc(2);
	_new_string[0] = c;
	_new_string[1] = '\0';
	return _new_string;
}

CUBA_STRING CUBA_STRING_FROM_CHAR(char c) {
	CUBA_STRING str = {
		.size = 1u,
		.content = ctos(c)
	};
	return str;
}
CUBA_STRING CUBA_STRING_COPY(CUBA_STRING original) {
	CUBA_STRING _new_object;
	_new_object.size = original.size;
	_new_object.content = malloc(original.size);
	memcpy(_new_object.content, original.content, original.size);
	return _new_object;
}

CUBA_STRING CUBA_STRING_INIT(CUBA_STRING* str, char* content, size_t size) {
	str->content = content;
	if (content[size] != '\0') {
		str->content = malloc(size+1);
		content[size] = '\0';
		memcpy(str->content, content, size);
		str->size = size+1;
	} else {
		str->size = size;
	}
	return *str;
}

void CUBA_STRING_BUILDER_INIT(CUBA_STRING_BUILDER* parent, size_t alignment) {
	parent->size = 0;
	parent->alignment = alignment;
	parent->capacity = alignment;
	parent->begin = malloc(alignment);
	if (parent->begin == NULL) {
		CUBA_PANIC_CODE("cannot allocate memory");
	}
}

void* CUBA_REALOC(void* old, size_t oldsize, size_t newsize) {
	void* _new_obj = malloc(newsize);
	memcpy(_new_obj, old, oldsize);
	free(old);
	return _new_obj;
}

void CUBA_STRING_BUILDER_REALOC(CUBA_STRING_BUILDER* parent, size_t newsize) {
	size_t _aligned_size = newsize + parent->alignment - newsize % parent->alignment;
	parent->capacity = _aligned_size;
	parent->begin = realloc(parent->begin, _aligned_size);
	if (parent->begin == NULL) {
		CUBA_PANIC_CODE("cannot allocate memory");
	}
}

void CUBA_STRING_BUILDER_SPLICE(CUBA_STRING_BUILDER* parent, size_t start, int end) {
	size_t _end = end;
	if (parent->size == 0) { CUBA_PANIC_CODE("string is empty"); }
	if (end < 0) { _end = parent->size-(end % parent->size); }
	if (start > _end) { CUBA_PANIC_CODE("bad configuration"); }
	char* _clip = malloc(_end-start);
	if (_clip == NULL) { CUBA_PANIC_CODE("cannot allocate memory"); }
	for (int i = start; i < _end; i++) {
		parent->begin[i];
		_clip[i-start] = parent->begin[i];
	}
	free(parent->begin);
	parent->begin = _clip;
}

void CUBA_STRING_BUILDER_PUSHC(CUBA_STRING_BUILDER* parent, char c) {
	size_t _new_size = parent->size+1;
	if (_new_size >= parent->capacity) {
		CUBA_STRING_BUILDER_REALOC(parent, _new_size);
	}
	parent->begin[parent->size++] = c;
}

void CUBA_STRING_BUILDER_PUSHS(CUBA_STRING_BUILDER* parent, const char* str) {
	size_t len = strlen(str);
	size_t _new_size = parent->size+len;
	if (_new_size > parent->capacity) {
		CUBA_STRING_BUILDER_REALOC(parent, _new_size);
	}
	for (int i = 0; i < len; i++) {
		parent->begin[parent->size+i] = str[i]; parent->size++;
	}
}

CUBA_STRING CUBA_STRING_BUILD_FINALIZE(CUBA_STRING_BUILDER* parent, CUBA_STRING* str) {
	CUBA_STRING_INIT(str, parent->begin, parent->size);
	return *str;
}
CUBA_STRING CUBA_STRING_BUILD_FINALIZE_FULLEND(CUBA_STRING_BUILDER* parent, CUBA_STRING* str) {
	CUBA_STRING_INIT(str, parent->begin, parent->size);
	free(parent->begin);
	free(parent);
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

typedef enum Cuba_Token_Kind {
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
} CUBA_TOKEN_KIND;

typedef struct Cuba_Token {
	CUBA_STRING value;
	CUBA_TOKEN_KIND kind;
} CUBA_TOKEN;

typedef struct Cuba_Token_List {
	size_t alignment;
	size_t capacity;
	size_t size;
	CUBA_TOKEN** begin;
} CUBA_TOKEN_LIST;

void CUBA_TOKEN_LIST_INIT(CUBA_TOKEN_LIST* parent, size_t alignment) {
	parent->alignment = alignment;
	parent->size = 0;
	parent->capacity = alignment;
	parent->begin = realloc(parent->begin, sizeof(CUBA_TOKEN*)*alignment);
}

void CUBA_TOKEN_LIST_REALOC(CUBA_TOKEN_LIST* parent, size_t newsize) {
	size_t _aligned_size = newsize + parent->alignment - newsize % parent->alignment;
	parent->capacity = _aligned_size;
	parent->begin = realloc(parent->begin, sizeof(CUBA_TOKEN*)*_aligned_size);
}

void CUBA_TOKEN_LIST_PUSH(CUBA_TOKEN_LIST* parent, CUBA_TOKEN* token) {
	size_t _new_size = parent->size+1;
	if (_new_size >= parent->capacity) {
		CUBA_TOKEN_LIST_REALOC(parent, _new_size);
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
	return *parent->begin[index];
}

CUBA_TOKEN* WCUBA_TOKEN_LIST_AT(CUBA_TOKEN_LIST* parent, size_t index, int line, const char* file) {
	if (!CUBA_TOKEN_LIST_IS_VALID_INDEX(parent, index)) {
		WCUBA_PANIC_CODE(line, file, "index is invalid");
	}
	return (parent->begin[index]);
}

typedef struct {
	CUBA_TOKEN_LIST tokens;
} CUBA_LEXER;

void CUBA_LEXER_INIT(CUBA_LEXER* lexer) {
	CUBA_TOKEN_LIST_INIT(&lexer->tokens, CUBA_LEXER_TOKEN_LIST_AL);
}


char* stringifyTokenKind(CUBA_TOKEN_KIND kind) {
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

void printTokens(CUBA_LEXER* lexer) {
	for (int i = 0; i < lexer->tokens.size; i++) {
		CUBA_TOKEN* tk = CUBA_TOKEN_LIST_AT(&lexer->tokens, i);
		char* kind = stringifyTokenKind(tk->kind);
		if (tk->value.size == 1) {
			printf("[kind='%s',  value='%c']\n", kind, *tk->value.content);
		} else {
			printf("[kind='%s',  value='%s']\n", kind, tk->value.content);
		}
	}
}

CUBA_TOKEN* CUBA_TOKEN_COPY(CUBA_TOKEN original) {
	CUBA_TOKEN* _new_object = malloc(sizeof(CUBA_TOKEN));
	_new_object->kind = original.kind;
	_new_object->value = CUBA_STRING_COPY(original.value);
	return _new_object;
}

CUBA_TOKEN CUBA_TOKEN_INIT(CUBA_TOKEN_KIND kind, CUBA_STRING value) {
	CUBA_TOKEN _new_object = {
		.kind  = kind,
		.value = value
	};
	return _new_object;
}

void CUBA_LEXER_APPEND_TOKEN(CUBA_LEXER* lexer, CUBA_TOKEN token) {
	CUBA_TOKEN_LIST_PUSH(&lexer->tokens, CUBA_TOKEN_COPY(token));
}

void CUBA_SIT_NEXT(CUBA_STRING_IT* it) {
	it->cursor += 1;
}

char CUBA_SIT_GETCH(CUBA_STRING_IT* it) {
	return it->content[it->cursor];
}

void CUBA_SIT_CPRINT(CUBA_STRING_IT* it) {
	printf("[current='%c',size='%u',cursor='%u']\n", it->content[it->cursor], it->size, it->cursor);
}
void CUBA_SIT_PRINT(CUBA_STRING_IT* it) {
	printf("[content='%s',size='%u',cursor='%u']\n", it->content, it->size, it->cursor);
}

char CUBA_SIT_GETCH_N(CUBA_STRING_IT* it) {
	char out = it->content[it->cursor];
	CUBA_SIT_NEXT(it);
	return out;
}

void CUBA_STRING_BUILDER_PUSHIT(CUBA_STRING_BUILDER* parent, CUBA_STRING_IT* it) {
	size_t _new_size = parent->size + 1;
	if (_new_size >= parent->capacity) {
		CUBA_STRING_BUILDER_REALOC(parent, _new_size);
	}
	char c = CUBA_SIT_GETCH(it);
	parent->begin[parent->size++] = c;
}

char CUBA_SIT_GETCHS(CUBA_STRING_IT* it, int s) {
	if (it->cursor+s < 0 && it->cursor+s > it->size) {
		return -1;
	}
	return it->content[it->cursor+s];
}

boolean IS_CHAR_IN_STRING(char c, const char* str) {
	if (c == -1) { return false; }
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