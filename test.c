#include <stdio.h>
#include <stdlib.h>
#include "cuba/mman.c"
#include "cuba/mman.h"

int main() {
	FILE* ptr;
	ptr = fopen("asm/test1.asm", "r");
	char buffer[1000];
	if (ptr == NULL) {
		printf("err");
		exit(1);
	}

	if (fgets(buffer, 1000, ptr) != NULL) {
	  void* buf;
		buf = mmap(NULL, sizeof(buf), PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		memcpy(buf, buffer, sizeof(buffer));
		
		((void(*)(void))buf)();
	}

	fclose(ptr);

	return 0;
}