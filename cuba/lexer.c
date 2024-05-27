#include "cuba.h"

void tok_skip(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	while (it->cursor < it->size) {
		if (!IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_SKIP)) { break; } 
		CUBA_SIT_NEXT(it);
	}
	
	// CUBA_SIT_CPRINT(it);
}

void tok_scmm(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	CUBA_SIT_NEXT(it); CUBA_SIT_NEXT(it);
	while (it->cursor < it->size) {
		if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), "\n\r")) { CUBA_SIT_NEXT(it); break; } 
		else { CUBA_STRING_BUILDER_PUSHIT(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	CUBA_TOKEN tk = {
		.kind = TK_SINGLECMM,
		.value = content
	};
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
	
	// while (it->cursor < it->size) {
	// 	if (!IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), "\n")) { break; } 
	// 	CUBA_SIT_NEXT(it);
	// }
}

void tok_mcmm(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	CUBA_SIT_NEXT(it); CUBA_SIT_NEXT(it); CUBA_SIT_NEXT(it);
	while (it->cursor < it->size) {
		if (
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(it, 0), TTK_MULTICMM) &&
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(it, 1), TTK_MULTICMM) &&
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(it, 2), TTK_MULTICMM)
		) { CUBA_SIT_NEXT(it); break; } 
		else { CUBA_STRING_BUILDER_PUSHIT(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	CUBA_TOKEN tk = {
		.kind = TK_MULTICMM,
		.value = content
	};
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
	
	// while (it->cursor < it->size) {
	// 	if (!IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), "\n")) { break; } 
	// 	CUBA_SIT_NEXT(it);
	// }
}

void tok_string(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	CUBA_SIT_NEXT(it);
	while (it->cursor < it->size) {
		if (
			IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_QUOTE) &&
			CUBA_SIT_GETCHS(it, -1) != TTK_ESC
		) { CUBA_SIT_NEXT(it); break; } 
		else { CUBA_STRING_BUILDER_PUSHIT(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	CUBA_TOKEN tk = {
		.kind = TK_STRING,
		.value = content
	};
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}

void tok_special(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_LEXER_APPEND_TOKEN(lexer, CUBA_TOKEN_INIT(TK_SPECIAL, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it))));
}

void tok_number(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	while (it->cursor < it->size) {
		if (!IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_NUMBER)) { break; } 
		else { CUBA_STRING_BUILDER_PUSHIT(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	CUBA_TOKEN tk = {
		.kind = TK_NUMBER,
		.value = content
	};
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}

void tok_text(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_STRING_BUILDER builder;
	CUBA_STRING_BUILDER_INIT(&builder, 5);
	while (it->cursor < it->size) {
		if ( CUBA_SIT_GETCH(it) < 0 || !(IS_CHAR_IN_STRING(CUBA_SIT_GETCH(it), TTK_FTEXTSP))) { break; } 
		else { CUBA_STRING_BUILDER_PUSHIT(&builder, it); }
		CUBA_SIT_NEXT(it);
	}
	CUBA_STRING content;
	CUBA_STRING_BUILD_FINALIZE(&builder, &content);
	CUBA_TOKEN tk = {
		.kind = TK_TEXT,
		.value = content
	};
	CUBA_LEXER_APPEND_TOKEN(lexer, tk);
}

void tok_openfig(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_OPENFIG, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_closefig(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_CLOSEFIG, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_opensqu(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_OPENSQU, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_closesqu(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_CLOSESQU, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_opentri(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_OPENTRI, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_closetri(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_CLOSETRI, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_openrou(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_OPENROU, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_closerou(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_CLOSEROU, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}
void tok_endline(CUBA_LEXER* lexer, CUBA_STRING_IT* it) {
	CUBA_TOKEN token = CUBA_TOKEN_INIT(TK_ENDLINE, CUBA_STRING_FROM_CHAR(CUBA_SIT_GETCH_N(it)));
	CUBA_LEXER_APPEND_TOKEN(lexer, token);
}


void tokenize(CUBA_STRING input, CUBA_LEXER* lexer) {
	CUBA_STRING_IT it = CUBA_STRING_GETIT(&input);
	CUBA_LEXER_INIT(lexer);

	while (it.cursor < it.size) {
		// if (CUBA_SIT_GETCH(&it) <= 0) {
		// 	CUBA_SIT_NEXT(&it);
		// }
		// else 
		if (
			IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_SINGLECMM) && 
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(&it, 1), TTK_SINGLECMM)
		) { tok_scmm(lexer, &it); } 
		else if (
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(&it, 0), TTK_MULTICMM) &&
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(&it, 1), TTK_MULTICMM) &&
			IS_CHAR_IN_STRING(CUBA_SIT_GETCHS(&it, 2), TTK_MULTICMM)
		) { tok_mcmm(lexer, &it); }
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_SKIP))       { tok_skip(lexer, &it);      } //? string: (\S)   
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_QUOTE))      { tok_string(lexer, &it);    } //? string: (".*") 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_SPECIAL))    { tok_special(lexer, &it);   } //? special ([\!@|/-=+_*&^:;`#~.?,])
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_NUMBER))     { tok_number(lexer, &it);    } //? number ([0-9])
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_TEXT))       { tok_text(lexer, &it);      } //? text ([a-zA-Z][a-zA-Z0-9_])
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_OPENFIG))    { tok_openfig(lexer, &it);   } //? open fig (\{) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_CLOSEFIG))   { tok_closefig(lexer, &it);  } //? close fig (\}) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_OPENSQU))    { tok_opensqu(lexer, &it);   } //? open squ (\[) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_CLOSESQU))   { tok_closesqu(lexer, &it);  } //? close squ (\]) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_OPENTRI))    { tok_opentri(lexer, &it);   } //? open tri (\<) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_CLOSETRI))   { tok_closetri(lexer, &it);  } //? close tri (\>) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_OPENROU))    { tok_openrou(lexer, &it);   } //? open rou (\() 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_CLOSEROU))   { tok_closerou(lexer, &it);  } //? close rou (\)) 
		else if (IS_CHAR_IN_STRING(CUBA_SIT_GETCH(&it), TTK_ENDLINE))    { tok_endline(lexer, &it);   } //? end line (;) 
		else { CUBA_SIT_NEXT(&it); }
	}

}
