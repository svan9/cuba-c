// #include "nan.h"

// void print_dll_func(char* str) {
// 	NanStringBuilder builder = NanStringBuilderFromStr(str, strlen(str)+10);
// 	NanStringBuilderPrintX(&builder);
// }

// int main() {
// 	NanDll dll = NanLoadDll("kernel32.dll");
	
// 	// NanDefFuncDLL(char*, &dll, GetStdHandle);
// 	// print_dll_func(__GetStdHandle);
	
// 	NanDefFuncDLL(char*, &dll, WriteFile);
// 	print_dll_func(__WriteFile);
	
// 	NanDllDestroy(&dll);
// 	return 0;
// }

// #include <windows.h>
#include <stdio.h>

// static HINSTANCE chonst;


int main() {
	// chonst = GetStdHandle((DWORD)-11);
	// HINSTANCE module = LoadLibrary("kernel32.dll");
	// if ( module == NULL ) {  }

	// FARPROC __GetStdHandle = GetProcAddress(module, "GetStdHandle");
	
	// if(__GetStdHandle != 0) {
		// typedef HINSTANCE (__cdecl *fn)(DWORD);
		// char* message = "hellow\n";
		// DWORD dwBytesToWrite = (DWORD)strlen(message);
    // DWORD dwBytesWritten = 0;
		// WriteFile(((fn)__GetStdHandle)(-11), message, dwBytesToWrite, NULL, NULL);
	// }
	putchar('A');
	
	// FreeLibrary(module);
}