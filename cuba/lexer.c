#include "cuba.h"


//$ ---- TOKENIZING ---- 

// skip white spaces
void tok_skip(CubaLexer* lexer, NanStringIterator* it) {
	while (it->cursor < it->size) {
		if (!isCharInString(TTK_SKIP, CUBA_SIT_GETCH(it))) { break; } 
		NanStringIteratorGetNext(it);
	}
	
	// CUBA_SIT_CPRINT(it);
}

// catch single line comments
void tok_scmm(CubaLexer* lexer, NanStringIterator* it) {
	NanStringBuilder builder = NanStringBuilderCreate(&builder);
	NanStringIteratorGetNext(it); NanStringIteratorGetNext(it);
	while (it->cursor < it->size) {
		if (isCharInString("\n\r", CUBA_SIT_GETCH(it))) { NanStringIteratorGetNext(it); break; } 
		else { NanStringBuilder_PUSHIT(&builder, it); }
		NanStringIteratorGetNext(it);
	}
	NanString content = NanStringBuilderFinalize(&builder);
	CubaToken tk = {
		.kind = TK_SINGLECMM,
		.content = content
	};
	CubaLexerAppendToken(lexer, &tk);
}

// catch multi line comments
void tok_mcmm(CubaLexer* lexer, NanStringIterator* it) {
	NanStringBuilder builder = NanStringBuilderCreate(&builder);
	NanStringIteratorGetNext(it); NanStringIteratorGetNext(it); NanStringIteratorGetNext(it);
	while (it->cursor < it->size) {
		if (
			isCharInString(TTK_MULTICMM, NanStringIteratorGetNexts(it, 0)) &&
			isCharInString(TTK_MULTICMM, NanStringIteratorGetNexts(it, 1)) &&
			isCharInString(TTK_MULTICMM, NanStringIteratorGetNexts(it, 2))
		) { NanStringIteratorGetNext(it); break; } 
		else { NanStringBuilder_PUSHIT(&builder, it); }
		NanStringIteratorGetNext(it);
	}
	NanString content = NanStringBuilderFinalize(&builder);
	CubaToken tk = {
		.kind = TK_MULTICMM,
		.content = content
	};
	CubaLexerAppendToken(lexer, &tk);
}

// catch ("string")
void tok_string(CubaLexer* lexer, NanStringIterator* it) {
	NanStringBuilder builder = NanStringBuilderCreate(&builder);
	NanStringIteratorGetNext(it);
	while (it->cursor < it->size) {
		if (
			isCharInString(CUBA_SIT_GETCH(it), TTK_QUOTE) &&
			NanStringIteratorGetNexts(it, -1) != TTK_ESC
		) { NanStringIteratorGetNext(it); break; } 
		else { NanStringBuilder_PUSHIT(&builder, it); }
		NanStringIteratorGetNext(it);
	}
	NanString content = NanStringBuilderFinalize(&builder);
	CubaToken tk = {
		.kind = TK_STRING,
		.content = content
	};
	CubaLexerAppendToken(lexer, &tk);
}

// catch any symbols
void tok_special(CubaLexer* lexer, NanStringIterator* it) {
	CubaLexerAppendToken(lexer, CubaTokenCreate(TK_SPECIAL, NanStringFromChar(NanStringIteratorNext(it))));
}

// catch number (fully only integer)
void tok_number(CubaLexer* lexer, NanStringIterator* it) {
	NanStringBuilder builder = NanStringBuilderCreate(&builder);
	while (it->cursor < it->size) {
		if (!isCharInString(CUBA_SIT_GETCH(it), TTK_NUMBER)) { break; } 
		else { NanStringBuilder_PUSHIT(&builder, it); }
		NanStringIteratorGetNext(it);
	}
	NanString content = NanStringBuilderFinalize(&builder);
	CubaToken tk = {
		.kind = TK_NUMBER,
		.content = content
	};
	CubaLexerAppendToken(lexer, &tk);
}

// catch any text
void tok_text(CubaLexer* lexer, NanStringIterator* it) {
	NanStringBuilder builder = NanStringBuilderCreate(&builder);
	while (it->cursor < it->size) {
		if ( CUBA_SIT_GETCH(it) < 0 || !(isCharInString(CUBA_SIT_GETCH(it), TTK_FTEXTSP))) { break; } 
		else { NanStringBuilder_PUSHIT(&builder, it); }
		NanStringIteratorGetNext(it);
	}
	NanString content = NanStringBuilderFinalize(&builder);
	CubaToken tk = {
		.kind = TK_TEXT,
		.content = content
	};
	CubaLexerAppendToken(lexer, &tk);
}

// token brackets
void tok_openfig(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_OPENFIG, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_closefig(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_CLOSEFIG, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_opensqu(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_OPENSQU, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_closesqu(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_CLOSESQU, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_opentri(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_OPENTRI, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_closetri(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_CLOSETRI, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_openrou(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_OPENROU, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_closerou(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_CLOSEROU, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}
// token brackets
void tok_endline(CubaLexer* lexer, NanStringIterator* it) {
	CubaToken* token = CubaTokenCreate(TK_ENDLINE, NanStringFromChar(CUBA_SIT_GETCH_N(it)));
	CubaLexerAppendToken(lexer, token);
}


//! bug string not catch '\0' (end of string) TK_TEXT ~ TK_<...>
void tokenize(NanString input, CubaLexer* lexer) {
	NanStringIterator it = NanStringIteratorFromString(&input); 

	while (it.cursor < it.size) {
		if (
			isCharInString(CUBA_SIT_GETCH(&it), TTK_SINGLECMM) && 
			isCharInString(NanStringIteratorGetNexts(&it, 1), TTK_SINGLECMM)
		) { tok_scmm(lexer, &it); } 
		else if (
			isCharInString(NanStringIteratorGetNexts(&it, 0), TTK_MULTICMM) &&
			isCharInString(NanStringIteratorGetNexts(&it, 1), TTK_MULTICMM) &&
			isCharInString(NanStringIteratorGetNexts(&it, 2), TTK_MULTICMM)
		) { tok_mcmm(lexer, &it); }
		else if (isCharInString(TTK_SKIP, NanStringIteratorGetNext(&it)))       { tok_skip(lexer, &it);      } //? string: (\S)   
		else if (isCharInString(TTK_QUOTE, NanStringIteratorGetNext(&it)))      { tok_string(lexer, &it);    } //? string: (".*") 
		else if (isCharInString(TTK_SPECIAL, NanStringIteratorGetNext(&it)))    { tok_special(lexer, &it);   } //? special ([\!@|/-=+_*&^:;`#~.?,])
		else if (isCharInString(TTK_NUMBER, NanStringIteratorGetNext(&it)))     { tok_number(lexer, &it);    } //? number ([0-9])
		else if (isCharInString(TTK_TEXT, NanStringIteratorGetNext(&it)))       { tok_text(lexer, &it);      } //? text ([a-zA-Z][a-zA-Z0-9_])
		else if (isCharInString(TTK_OPENFIG, NanStringIteratorGetNext(&it)))    { tok_openfig(lexer, &it);   } //? open fig (\{) 
		else if (isCharInString(TTK_CLOSEFIG, NanStringIteratorGetNext(&it)))   { tok_closefig(lexer, &it);  } //? close fig (\}) 
		else if (isCharInString(TTK_OPENSQU, NanStringIteratorGetNext(&it)))    { tok_opensqu(lexer, &it);   } //? open squ (\[) 
		else if (isCharInString(TTK_CLOSESQU, NanStringIteratorGetNext(&it)))   { tok_closesqu(lexer, &it);  } //? close squ (\]) 
		else if (isCharInString(TTK_OPENTRI, NanStringIteratorGetNext(&it)))    { tok_opentri(lexer, &it);   } //? open tri (\<) 
		else if (isCharInString(TTK_CLOSETRI, NanStringIteratorGetNext(&it)))   { tok_closetri(lexer, &it);  } //? close tri (\>) 
		else if (isCharInString(TTK_OPENROU, NanStringIteratorGetNext(&it)))    { tok_openrou(lexer, &it);   } //? open rou (\() 
		else if (isCharInString(TTK_CLOSEROU, NanStringIteratorGetNext(&it)))   { tok_closerou(lexer, &it);  } //? close rou (\)) 
		else if (isCharInString(TTK_ENDLINE, NanStringIteratorGetNext(&it)))    { tok_endline(lexer, &it);   } //? end line (;) 
		else { NanStringIteratorNext(&it); }
	}
}
