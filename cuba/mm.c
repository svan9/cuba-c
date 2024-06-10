// // 64

// NanStringBuilderPushStr(builder, "\xba\x01\x00\x00\x00"     , 5); // mov    edx,0x1
// NanStringBuilderPushStr(builder, "\x8b\x0d\x00\x00\x00\x00" , 6); // mov    ecx,DWORD PTR ds:0x0
// NanStringBuilderPushStr(builder, "\xbb\x01\x00\x00\x00"     , 5); // mov    ebx,0x1
// NanStringBuilderPushStr(builder, "\xb8\x04\x00\x00\x00"     , 5); // mov    eax,0x4
// NanStringBuilderPushStr(builder, "\x0f\x05"      					 , 2); // syscall

// // 86

// NanStringBuilderPushStr(builder, "\xba\x01\x00\x00\x00"     , 5); // mov    edx,0x1
// NanStringBuilderPushStr(builder, "\x89\xe1"       	         , 2); // mov    ecx,esp
// NanStringBuilderPushStr(builder, "\xbb\x01\x00\x00\x00"     , 5); // mov    ebx,0x1
// NanStringBuilderPushStr(builder, "\xb8\x04\x00\x00\x00"     , 5); // mov    eax,0x4
// NanStringBuilderPushStr(builder, "\x0f\x05"       	         , 2); // syscall


// // 64
// NanStringBuilderPushStr(builder,  "\xba\x01\x00\x00\x00", 5); // mov  edx, 0x1
// NanStringBuilderPushStr(builder,  "\x89\xe1" 	          , 2); // mov  ecx, esp
// NanStringBuilderPushStr(builder,  "\xbb\x01\x00\x00\x00", 5); // mov  ebx, 0x1
// NanStringBuilderPushStr(builder,  "\xb8\x04\x00\x00\x00", 5); // mov  eax, 0x4
// NanStringBuilderPushStr(builder,  "\x0f\x05" 	          , 2); // syscall