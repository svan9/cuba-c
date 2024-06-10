#include "cuba.h"
#include "nan.h"

// work with some block like a marker labal in assembler code... I think that
CubaBlock parse_block(CubaLexer* lexer, NanIterator* it) {
	// init list
	NanDynamicArray content = NanDynamicArrayCreate(sizeof(CubaLine));
	CubaToken* tk;
	// some cycyel
	while (it->cursor < it->size) {
		// get next token
		tk = NanIteratorNext(it);
		// out in our mind
		if (tk->kind == TK_CLOSEFIG) { break; }
		// put in outself
		CubaLine line = parse_line(lexer, &it);
		// push append and as like smell of jaja
		NanDynamicArrayPush(&content, &line);
	}
	// init self
	CubaBlock self = {
		.content = content
	};
	return self;
}

// todo features
// work with some block like a marker labal in assembler code... I think that
CubaArray parse_array(CubaLexer* lexer, NanIterator* it) {
	// init self
	CubaArray self = NanDynamicArrayCreate(sizeof(CubaArrayElement));
	CubaToken* tk;
	// some cycyel
	while (it->cursor < it->size) {
		// get next token
		tk = NanIteratorNext(it);
		// out in our mind
		if (tk->kind == TK_CLOSEROU) { break; }
		// catch elements by comma 
 		if (tk->kind == TK_TEXT) {
			// init own of `array` element 
			CubaArrayElement el = {0};
			// init multi typed element
			el.is_allocator = false;
			el.first.kind  = EL_TEXT;
			el.first.content = &tk;
			// get next token
			tk = NanIteratorNext(it);
			// catch second element if it allocator
			if (tk->kind == TK_TEXT) {
				// is allocator
				el.is_allocator = true;
				// init multi typed element
				el.second.kind  = EL_TEXT;
				el.second.content = &tk;
			}
			// exit
			NanDynamicArrayPush(&self, &el);
		}
	}
	return self;
}

// todo features
// work with some block like a marker labal in assembler code... I think that
CubaArray parse_sqarray(CubaLexer* lexer, NanIterator* it) {
	// init self
	CubaArray self = NanDynamicArrayCreate(sizeof(CubaArrayElement));
	CubaToken* tk;
	// some cycyel
	while (it->cursor < it->size) {
		// get next token
		tk = NanIteratorNext(it);
		// out in our mind
		if (tk->kind == TK_CLOSEROU) { break; }
		// catch elements by comma 
 		if (tk->kind == TK_TEXT) {
			// init own of `array` element 
			CubaArrayElement el = {0};
			// init multi typed element
			el.first.kind  = EL_TEXT;
			memcpy(el.first.content, tk, sizeof(tk));
			// get next token
			tk = NanIteratorNext(it);
			// catch second element if it allocator
			if (tk->kind == TK_TEXT) {
				// is allocator
				el.is_allocator = true;
				// init multi typed element
				el.second.kind  = EL_TEXT;
				memcpy(el.second.content, tk, sizeof(tk));
			}
			// exit
			NanDynamicArrayPush(&self, &el);
		}
	}
	return self;
}

// CubaKeyWord parse_keywords(CubaLexer* lexer, NanIterator* it) {
	
// }

/*// Todo: 
//*	 [01]  block type [needs: all] 
//*	 [02]  plain text 
//#	 [03]  native method of var
//#	 [04]  get field of var
//#	 [05]  flag row
//#	 [06]  squared array
//*	 [07]  array type
//#	 [08]  program entry
//#	 [09]  token-named lambda func
//#	 [10]  block event function [needs: 9]
*/
CubaLine parse_line(CubaLexer* lexer, NanIterator* it) {
	// init self
	NanDynamicArray self = NanDynamicArrayCreate(sizeof(CubaElement));
	CubaToken* tk;
	// soke soke
	while (it->cursor < it->size) {
		// get next token
		tk = NanIteratorNext(it);
		CubaElement element = {0};
		// exit if exits
		if (tk->kind == TK_ENDLINE) { break; }
		// allocate and eq some steave
		element.kind = EL_TEXT;
		element.content = &tk;
		// [1] work with block type 
		if (tk->kind == TK_OPENFIG) {
			// get next step
			NanIteratorNext(it);
			// get parsed block
			CubaBlock _block = parse_block(lexer, it);
			// eq some stuff
			element.kind = EL_BLOCK;
			element.content = &_block;
		}
		// [7] array type 
		else if (tk->kind == TK_OPENROU) {
			// get next step
			NanIteratorNext(it);
			// get parsed block
			CubaArray _block = parse_array(lexer, it);
			// eq some stuff
			element.kind = EL_BLOCK;
			element.content = &_block;
		}

		// [2] plain text `else` 
		// push back
		NanDynamicArrayPush(&self, &element);
	}

	CubaLine line = {
		.content = self
	};

	return line;
}

// parse some lexer stuff
void parse(CubaLexer* lexer) {
	NanIterator it = NanIteratorFrom(lexer->tokens.begin, lexer->tokens.size);
	NanDynamicArray content = NanDynamicArrayCreate(sizeof(CubaLine));
	
	// some cycle
	while (it.cursor < it.size) {
		// allocate a line pointer
		// push into allocated paresed line
		CubaLine line = parse_line(lexer, &it);
		// push_back
		NanDynamicArrayPush(&content, &line);
	}
}
