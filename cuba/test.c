#include "nan.h"

int main() {
	NanJit jit = NanJitCreate();
	NanJitAppendCS(&jit, NA_PRINT, "hellow, word\n");
	NanJitRun(&jit);
	NanJitDebug(&jit);
	return 0;
}