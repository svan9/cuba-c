// #include "mman.c"
// #include "mman.h"
#include <string.h>
#include <ctype.h>

char *ltrim(char *s) {
	while(isspace(*s)) s++;
	return s;
}

char *rtrim(char *s) {
	char* back = s + strlen(s);
	while(isspace(*--back));
	*(back+1) = '\0';
	return s;
}
char *trim(char *s) {
	return rtrim(ltrim(s));
}

// void* execute(char code[]) {
// 	void* buf;
// 	buf = mmap(0,sizeof(code),PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON,-1,0);

// 	memcpy (buf, code, sizeof(code));
	
// 	((void(*)(void))buf)();
// 	return buf;
// }