#include "cuba.h"

CUBA_LEXER tokenize(CUBA_STRING input) {
	CUBA_STRING_IT it = CUBA_STRING_GETIT(&input); 
	CUBA_LEXER lexer;
	while (it.cursor < it.size) {
		char c = CUBA_SIT_GETCH(&it);

		if (IS_CHAR_IN_STRING(c, TTK_SKIP))      {   tok_skip(&lexer, &it);      } //? string: (\S)   
		if (IS_CHAR_IN_STRING(c, TTK_QUOTE))     {   tok_string(&lexer, &it);    } //? string: (".*") 
		if (IS_CHAR_IN_STRING(c, TTK_SPECIAL))   {   tok_special(&lexer, &it);   } //? special ([\!@|/-=+_*&^:;`#~.?,])
		if (IS_CHAR_IN_STRING(c, TTK_NUMBER))    {   tok_number(&lexer, &it);    } //? number ([0-9])
		if (IS_CHAR_IN_STRING(c, TTK_TEXT))      {   tok_text(&lexer, &it);      } //? text ([a-zA-Z][a-zA-Z0-9_])
		if (IS_CHAR_IN_STRING(c, TTK_OPENFIG))   {   tok_openfig(&lexer, &it);   } //? open fig (\{) 
		if (IS_CHAR_IN_STRING(c, TTK_CLOSEFIG))  {   tok_closefig(&lexer, &it);  } //? close fig (\}) 
		if (IS_CHAR_IN_STRING(c, TTK_OPENSQU))   {   tok_opensqu(&lexer, &it);   } //? open squ (\[) 
		if (IS_CHAR_IN_STRING(c, TTK_CLOSESQU))  {   tok_closesqu(&lexer, &it);  } //? close squ (\]) 
		if (IS_CHAR_IN_STRING(c, TTK_OPENTRI))   {   tok_opentri(&lexer, &it);   } //? open tri (\<) 
		if (IS_CHAR_IN_STRING(c, TTK_CLOSETRI))  {   tok_closetri(&lexer, &it);  } //? close tri (\>) 
		if (IS_CHAR_IN_STRING(c, TTK_OPENROU))   {   tok_openrou(&lexer, &it);   } //? open rou (\() 
		if (IS_CHAR_IN_STRING(c, TTK_CLOSEROU))  {   tok_closerou(&lexer, &it);  } //? close rou (\)) 
		
		CUBA_SIT_NEXT(&it);
	}

	return lexer;
}

void tok_skip(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	while (it->cursor < it->size) {
		if (!IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_SKIP)) { break; } 
		CUBA_SIT_NEXT(it);
	}
}

void tok_string(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_STRING;
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	while (it->cursor < it->size) {
		if ( CUBA_SIT_GETCH(it) == TTK_QUOTE && CUBA_SIT_GETCHS(it, -1) != TTK_ESC ) { break; } 
		else { CUBA_STRING_BUILDER_PUSHC(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	tk.value = content;
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}

void tok_secial(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_SPECIAL;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}

void tok_number(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_NUMBER;
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	while (it->cursor < it->size) {
		if (!IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_NUMBER)) { break; } 
		else { CUBA_STRING_BUILDER_PUSHC(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	tk.value = content;
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}

void tok_text(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_TEXT;
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	while (it->cursor < it->size) {
		if (!(IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_TEXT TTK_NUMBER "_"))) { break; } 
		else { CUBA_STRING_BUILDER_PUSHC(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	tk.value = content;
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}


void tok_openfig(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_OPENFIG;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_closefig(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_CLOSEFIG;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_opensqu(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_OPENSQU;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_closesqu(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_CLOSESQU;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_opentri(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_OPENTRI;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_closetri(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_CLOSETRI;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_openrou(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_OPENROU;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
void tok_closerou(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN tk;
	tk.kind = TK_CLOSEROU;
	tk.value = CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH(it));
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}
