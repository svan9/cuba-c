#include "nan.h"

int main() {
	NanStringBuilder builder = NanStringBuilderCreate(5);
	NanJitExtPutString(&builder, "hellow, world");
	NanJitEOP(&builder);
	// NanStringBuilderPrintX(&builder);
	NanExec exec = NanStringBuilderToExec(&builder);
	NanExecRun(&exec);
	return 0;
}