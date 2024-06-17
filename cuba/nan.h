#ifndef NAN_H
#define NAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#ifdef _WIN32
  #include <io.h>
#elif __linux__
  #include <inttypes.h>
  #include <unistd.h>
  #define __int64 int64_t
  #define _close close
  #define _read read
  #define _lseek64 lseek64
  #define _O_RDONLY O_RDONLY
  #define _open open
  #define _lseeki64 lseek64
  #define _lseek lseek
  #define stricmp strcasecmp
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#define GETCODELINE() __LINE__
#define GETCODEFILE() __FILE__
#define GETCODEFUNC() __func__
#define stringify(a) #a
#define callpoint() printf("called from: %s:%i\n",  GETCODEFILE(), GETCODELINE());
#define ppp callpoint()
#define pppp {callpoint()}

#include <string.h>
#include <ctype.h>

typedef unsigned char ubyte;
typedef void* NanObjectLink;
static ubyte ffbyte = 255U;

#ifndef ltrim
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
#endif

wchar_t* CharsToWChars(char* c) {
	size_t size = strlen(c)+1;
	wchar_t* wc = malloc(sizeof(wchar_t)*size);
	mbstowcs(wc, c, size);
	return wc;
}

char* string_format(char *fmt, ...) {
  size_t size = strlen(fmt);
  va_list list;
  va_start(list, fmt);
  for (
    char* next = va_arg(list, char*);
    next != NULL;
    next = va_arg(list, char*)
  ) {
    size += strlen(next);
  }
  char* buffer = malloc(size);
  vsnprintf(buffer, size, fmt, list);
  va_end(list);
  return buffer;
}


#define NAN_WARN_CODE(message) WENAN_WARN_CODE(GETCODELINE(), GETCODEFILE(), __func__ , message)
#define NAN_PANIC_CODE(message) WENAN_PANIC_CODE(GETCODELINE(), GETCODEFILE(), __func__ , message)
#define SNAN_PANIC_CODE(message) AENAN_PANIC_CODE(GETCODELINE(), GETCODEFILE(), __func__ , message)
#define NAN_PANIC_CODEF(...) \
  WENAN_PANIC_CODE(GETCODELINE(), GETCODEFILE(), __func__ , string_format(__VA_ARGS__))


char* READ_LINE_FROM_FILE(int line, const char* file) {
  const int MAX_LINE_LENGTH = 1000;
  FILE * fp;
  fp = fopen(file, "r");
  char* chunk = malloc(MAX_LINE_LENGTH);
  size_t nut = 0;
  while(fgets(chunk, MAX_LINE_LENGTH, fp) != NULL) {
    if ((nut++) >= (line-1)) { break; }
  }
  fclose(fp);
  return chunk;
}

void WNAN_PANIC_CODE(int line, const char* path, const char* message) {
  char* _line;
  _line = trim(READ_LINE_FROM_FILE(line, path));

  printf("error at %s:%i (%s)", path, line, message);
  printf("\n\t%s", _line);
  printf("\n\t^");
  exit(1);
}

void WENAN_PANIC_CODE(int line, const char* path, const char* func, const char* message) {
  char* _line;
  _line = trim(READ_LINE_FROM_FILE(line, path));

  printf("error in function `%s()` at %s:%i (%s)", func, path, line, message);
  printf("\n\t%s", _line);
  printf("\n\t^");
  exit(1);
}

void WENAN_WARN_CODE(int line, const char* path, const char* func, const char* message) {
  char* _line;
  _line = trim(READ_LINE_FROM_FILE(line, path));

  printf("warn in function `%s()` at %s:%i (%s)", func, path, line, message);
  printf("\n\t%s", _line);
  printf("\n\t^");
}

void AENAN_PANIC_CODE(int line, const char* path, const char* func, const char* message) {
  printf("error in function `%s()` at %s:%i (%s)", func, path, line, message);
  exit(1);
}

typedef struct {
  const size_t alignment;
  const size_t T_size;
  size_t capacity;
  size_t size;
  void* begin;
} NanDynamicArray;

void NanDynamicArrayRealloc(NanDynamicArray* self, size_t newSize) {
  size_t _aligned_size = newSize + self->alignment - self->alignment % newSize;
  self->capacity = _aligned_size;
  self->begin = realloc(self->begin, _aligned_size);

  if (self->begin == NULL) {
    SNAN_PANIC_CODE("can't allocate");
  }
}

#define NanDynamicArrayAlignment 5

NanDynamicArray NanDynamicArrayCreate(size_t element_size) {
  NanDynamicArray self = {
    .alignment = NanDynamicArrayAlignment,
    .T_size = element_size,
    .capacity = NanDynamicArrayAlignment,
    .size = 0,
    .begin = NULL
  };
  self.begin = malloc(NanDynamicArrayAlignment*element_size);
  if (self.begin == NULL) {
    SNAN_PANIC_CODE("can't allocate");
  }
  return self;
}

void NanDynamicArrayPush(NanDynamicArray* self, void* element) {
  size_t _new_size = self->size + 1;
  if (_new_size > self->capacity) {
    NanDynamicArrayRealloc(self, _new_size);
  }
  memcpy(self->begin+(self->size*self->T_size), element, self->T_size);
  self->size++;
}

void NanDynamicArrayDelete(NanDynamicArray* self, size_t index) {
  if (index > self->size) { NAN_PANIC_CODE("index out of size"); }
  memcpy(self->begin+index, self->begin+index+self->T_size, self->size-(index+1));
  self->size--;
}

void* NanDynamicArrayEnd(NanDynamicArray* self) {
  return self->begin+((self->size-1)*self->T_size);
}

void* NanDynamicArrayAt(NanDynamicArray* self, size_t index) {
  if (index > self->size || index < 0) {
    NAN_PANIC_CODE("index out of bounds");
  }
  return self->begin+(index*self->T_size);
}
void* NanDynamicArrayAt_s(NanDynamicArray* self, size_t index) {
  if (index >= self->size || index < 0) {
    return NULL;
  }
  return self->begin+(index*self->T_size);
}

bool NanDynamicArrayHasCMP(NanDynamicArray* self, void* element, size_t size) {
  for (int i = 0; i < self->size; i++) {
    void* __element = NanDynamicArrayAt_s(self, i);
    if (__element == element || memcmp(__element, element, size) == 0) { return true; }
  }
  return false;
}

void* NanDynamicArrayFindCMP(NanDynamicArray* self, void* element, size_t size) {
  for (int i = 0; i < self->size; i++) {
    void* __element = NanDynamicArrayAt_s(self, i);
    if (__element == element || memcmp(__element, element, size) == 0) { return __element; }
  }
  return NULL;
}

bool NanDynamicArrayHas(NanDynamicArray* self, void* element) {
  for (int i = 0; i < self->size; i++) {
    void* __element = NanDynamicArrayAt_s(self, i);
    if (__element == element) { return true; }
  }
  return false;
}

typedef struct {
  void* next;
  void* prev;
  void* content;
} NanTuple;

NanTuple NanTupleCreate() {
  NanTuple t = {NULL, NULL, NULL};
  return t;
}
NanTuple* NanTupleCreateP(NanTuple* prev, NanTuple* next, void* content) {
  NanTuple* t = malloc(sizeof(NanTuple));
  t->content = content;
  t->next = next;
  t->prev = prev;
  return t;
}

void NanTuplePush(NanTuple* self, void* content) {
  NanTuple* __self = self;
  while (__self->next != NULL) {
    __self = __self->next; 
  }
  __self->next = NanTupleCreateP(self, NULL, content);
}

void NanTuplePushHead(NanTuple* self, void* content) {
  NanTuple* __self = self;
  while (__self->prev != NULL) {
    __self = __self->prev; 
  }
  NanTuple __next = {
    .content = content,
    .prev = self,
    .content = content
  };
  __self->prev = NanTupleCreateP(NULL, self, content);
}

void NanTuplePushRemoveBack(NanTuple* self, size_t amount) {
  size_t counter = 0;
  NanTuple* __self = self;
  while (counter < amount || __self->prev != NULL) {
    __self = __self->prev; counter++;
  }
  ((NanTuple*)__self->next)->prev = __self->prev;
  ((NanTuple*)__self->prev)->next = __self->next;
  free(__self);
}

void NanTuplePushRemoveFront(NanTuple* self, size_t amount) {
  size_t counter = 0;
  NanTuple* __self = self;
  while (counter < amount || __self->next != NULL) {
    __self = __self->next; counter++;
  }
  ((NanTuple*)__self->next)->prev = __self->prev;
  ((NanTuple*)__self->prev)->next = __self->next;
  free(__self);
}

void NanTuplePushRemove(NanTuple* self, int offset) {
  NanTuple* __self = self;
  while (__self->prev != NULL) {
    __self = __self->prev; 
  }
  if (offset > 0) {
    NanTuplePushRemoveFront(self, (size_t)abs(offset));
  }
  else if (offset < 0) {
    NanTuplePushRemoveBack(self, (size_t)abs(offset));
  }
  else if (offset == 0) {
    ((NanTuple*)self->next)->prev = self->prev;
    ((NanTuple*)self->prev)->next = self->next;
  }
}

typedef struct {
  size_t size;
  char* content;
} NanString;

NanString NanStringCopy(NanString* root) {
  NanString self = {
    .content = NULL,
    .size = root->size
  };
  self.content = malloc(self.size);
  memcpy(self.content, root->content, root->size);
  return self;  
}

bool NanStringMatch(NanString* left, NanString* right) {
  if (left->size != right->size) {return false;}
  for (int i = 0; i < left->size; i++) {
    if (left->content[i] != right->content[i]) { return false; }
  }
  return true;
}

static NanString NanStringNull = {.size = 0, .content = NULL};

static bool NanStringIsNull(NanString* cl) {
  return cl->size == 0 && cl->content == NULL;
}



NanString NanStringFromChar(char c) {
  NanString str = {
    .size = 1,
    .content = NULL
  };
  str.content = malloc(1);
  str.content[0] = c;
  return str;
}
NanString NanStringFromStr(char* s) {
  NanString str = {
    .size = strlen(s),
    .content = NULL
  };
  str.content = malloc(str.size);
  if (str.content == NULL) { SNAN_PANIC_CODE("can't allocate memory"); }
  memcpy(str.content, s, str.size);
  return str;
}
NanString NanStringFromStrs(char* s, ...) {
  size_t size = 0;
  va_list list;
  va_start(list, s);
  for (
    char* next = va_arg(list, char*);
    next != NULL;
    next = va_arg(list, char*)
  ) {
    size+=strlen(next);
  }
  va_end(list);
  NanString str = {
    .size = size,
    .content = NULL
  };
  str.content = malloc(str.size);
  if (str.content == NULL) { SNAN_PANIC_CODE("can't allocate memory"); }
  size = strlen(s);
  memcpy(str.content+size, s, size);
  va_start(list, s);
  for (
    char* next = va_arg(list, char*);
    next != NULL;
    next = va_arg(list, char*)
  ) {
    size_t len = strlen(next);
    memcpy(str.content+size, next, len);
    size += len;
  }
  va_end(list);
  return str;
}
NanString NanStringFromS(char* s, size_t size) {
  NanString str = {
    .size = size,
    .content = NULL
  };
  str.content = malloc(size);
  if (str.content == NULL) { SNAN_PANIC_CODE("can't allocate memory"); }
  memcpy(str.content, s, size);
  return str;
}

void NanStringPrint(NanString* self) {
  for (int i = 0; i < self->size; i++) {
    putchar(self->content[i]);
  }
}

bool NanStringStartWithC(NanString* self, char c){
  return self->size > 1 && self->content[0] == c;
}
bool NanStringStartWith(NanString* self, char* c){
  size_t len = strlen(c);
  if (self->size < len) { return false; }
  for (size_t i = 0; i < len; i++) {
    if (self->content[i] != c[i]) { return false; }
  }
  return true;
}

void NanStringCutLeft(NanString* self, size_t count) {
  if (count >= self->size) { NAN_PANIC_CODE("almost"); }
  size_t cursor = 0;
  while (cursor < count) { self->content++; cursor++; }
}

char* NanStringC_Str(NanString* self) {
  char* buffer = malloc(self->size+1);
  memcpy(buffer, self->content, self->size);
  buffer[self->size] = '\0';
  return buffer;
}


typedef struct {
  const size_t alignment;
  size_t size;
  size_t capacity;
  char* begin;
} NanStringBuilder;

NanStringBuilder NanStringBuilderCreate(size_t alignment) {
  NanStringBuilder self = {
    .alignment = alignment,
    .capacity = alignment,
    .size = 0,
    .begin = 0
  };

  self.begin = malloc(alignment*sizeof(char));

  if (self.begin == NULL) {
    SNAN_PANIC_CODE("can't allocate");
  }

  return self;
}
NanStringBuilder NanStringBuilderFromStr(char* str, size_t size) {
  NanStringBuilder self = {
    .alignment = 10,
    .capacity = 10,
    .size = size,
    .begin = 0
  };
  self.begin = malloc(10*size);
  if (self.begin == NULL) { SNAN_PANIC_CODE("can't allocate"); }
  memcpy(self.begin, str, size);
  return self;
}

void NanStringBuilderPrintX(NanStringBuilder* self) {
  printf("{");
  for (int i = 0; i < self->size; i++) {
    ubyte n = self->begin[i] & 0xff;
    if (n < 0x10) {
      printf("\\x0%x", n);
    } else {
      printf("\\x%x", n);
    }
  }
  printf("}\n");
}

void NanStringBuilderRealloc(NanStringBuilder* self, size_t newSize) {
  size_t _aligned_size = newSize + self->alignment - self->alignment % newSize;
  self->capacity = _aligned_size;
  self->begin = realloc(self->begin, _aligned_size);

  if (self->begin == NULL) {
    SNAN_PANIC_CODE("can't allocate");
  }
}

void NanStringBuilderPushC(NanStringBuilder* self, char c) {
  size_t _new_size = self->size + 1;
  if (_new_size > self->capacity) {
    NanStringBuilderRealloc(self, _new_size);
  }
  *(self->begin+(self->size*sizeof(char))) = c;
  self->size++;
}
void NanStringBuilderPushB(NanStringBuilder* self, ubyte c) {
  size_t _new_size = self->size + 1;
  if (_new_size > self->capacity) {
    NanStringBuilderRealloc(self, _new_size);
  }
  *(self->begin+(self->size*sizeof(ubyte))) = c;
  self->size++;
}

void NanStringBuilderPushS(NanStringBuilder* self, char* str) {
  size_t _new_size = self->size + strlen(str);
  if (_new_size > self->capacity) {
    NanStringBuilderRealloc(self, _new_size);
  }
  memcpy(self->begin+(self->size*sizeof(char)), str, strlen(str));
  self->size += strlen(str);
}
void NanStringBuilderPushStr(NanStringBuilder* self, char* str, size_t size) {
  size_t _new_size = self->size + size;
  if (_new_size > self->capacity) {
    NanStringBuilderRealloc(self, _new_size);
  }
  memcpy(self->begin+(self->size*sizeof(char)), str, size);
  self->size += size;
}

void NanStringBuilderPushMany(NanStringBuilder* self, void* items, size_t size) {
  size_t _new_size = self->size+size;
  if (_new_size > self->capacity) {
    NanStringBuilderRealloc(self, _new_size);
  }
  memcpy(self->begin+self->size, items, size);
  self->size += size;
}

NanString NanStringBuilderFinalize(NanStringBuilder* self) {
  NanString str = {0};
  str.size = self->size;
  memcpy(str.content, self->begin, self->size);
  return str;
}

#pragma region NAN_FILE

NanString readfile(const char* path) {
	// init file
	FILE* ptr;
	ptr = fopen(path, "rb"); 
	if (ptr == NULL) { NAN_PANIC_CODE("FILE ERROR"); }
	// get size of file
	long file_size;
	fseek(ptr, 0L, SEEK_END);
	file_size = ftell(ptr);
	fseek(ptr, 0L, SEEK_SET);
	// init buffer
	char* buffer = malloc(file_size);
	// read file
	fread(buffer, sizeof(char), file_size, ptr);
	// close file
	fclose(ptr);
	// get string from string builder
	NanString str = NanStringFromStr(buffer);
  // free
	free(buffer); free(ptr);
	return str;
}

NanString NanReadFile(NanString* path) {
	// init builder
	NanStringBuilder builder = NanStringBuilderCreate(100);
	// init file
	FILE* ptr;
	ptr = fopen(NanStringC_Str(path), "rb"); 
	if (ptr == NULL) { NAN_PANIC_CODE("FILE ERROR"); }
	// get size of file
	long file_size;
	fseek(ptr, 0L, SEEK_END);
	file_size = ftell(ptr);
	fseek(ptr, 0L, SEEK_SET);
	// init buffer
	char* buffer = malloc(file_size);
	// read file
	fread(buffer, sizeof(char), file_size, ptr);
	// close file
	fclose(ptr);
	// get string from string builder
	NanString str = NanStringFromStr(buffer);
  // free
	free(buffer); free(ptr);
	return str;
}


bool isFilePath(const char* path) {
	return access(path, F_OK);
}
bool NanIsFilePath(NanString* str) {
	return access(NanStringC_Str(str), F_OK);
}

#pragma endregion NAN_FILE

#pragma region MMAN

/*
 * sys/mman.h
 * mman-win32
 */

#ifdef __linux__

#include <sys/mman.h>

#elif __WIN32

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif

/* All the headers include this file. */
#ifndef _MSC_VER
#include <_mingw.h>
#endif

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROT_NONE       0
#define PROT_READ       1
#define PROT_WRITE      2
#define PROT_EXEC       4

#define MAP_FILE        0
#define MAP_SHARED      1
#define MAP_PRIVATE     2
#define MAP_TYPE        0xf
#define MAP_FIXED       0x10
#define MAP_ANONYMOUS   0x20
#define MAP_ANON        MAP_ANONYMOUS

#define MAP_FAILED      ((void *)-1)

/* Flags for msync. */
#define MS_ASYNC        1
#define MS_SYNC         2
#define MS_INVALIDATE   4

void*   mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
int     munmap(void *addr, size_t len);
int     _mprotect(void *addr, size_t len, int prot);
int     msync(void *addr, size_t len, int flags);
int     mlock(const void *addr, size_t len);
int     munlock(const void *addr, size_t len);

#ifdef __cplusplus
};
#endif

#endif /*  _SYS_MMAN_H_ */

#include <windows.h>
#include <errno.h>
#include <io.h>

#ifndef FILE_MAP_EXECUTE
#define FILE_MAP_EXECUTE    0x0020
#endif /* FILE_MAP_EXECUTE */

static int __map_mman_error(const DWORD err, const int deferr)
{
    if (err == 0)
        return 0;
    //TODO: implement
    return err;
}

static DWORD __map_mmap_prot_page(const int prot)
{
    DWORD protect = 0;

    if (prot == PROT_NONE)
        return protect;

    if ((prot & PROT_EXEC) != 0)
    {
        protect = ((prot & PROT_WRITE) != 0) ?
                    PAGE_EXECUTE_READWRITE : PAGE_EXECUTE_READ;
    }
    else
    {
        protect = ((prot & PROT_WRITE) != 0) ?
                    PAGE_READWRITE : PAGE_READONLY;
    }

    return protect;
}

static DWORD __map_mmap_prot_file(const int prot)
{
    DWORD desiredAccess = 0;

    if (prot == PROT_NONE)
        return desiredAccess;

    if ((prot & PROT_READ) != 0)
        desiredAccess |= FILE_MAP_READ;
    if ((prot & PROT_WRITE) != 0)
        desiredAccess |= FILE_MAP_WRITE;
    if ((prot & PROT_EXEC) != 0)
        desiredAccess |= FILE_MAP_EXECUTE;

    return desiredAccess;
}

void* mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off)
{
    HANDLE fm, h;

    void * map = MAP_FAILED;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4293)
#endif

    const DWORD dwFileOffsetLow = (sizeof(off_t) <= sizeof(DWORD)) ?
                    (DWORD)off : (DWORD)(off & 0xFFFFFFFFL);
    const DWORD dwFileOffsetHigh = (sizeof(off_t) <= sizeof(DWORD)) ?
                    (DWORD)0 : (DWORD)((off >> 32) & 0xFFFFFFFFL);
    const DWORD protect = __map_mmap_prot_page(prot);
    const DWORD desiredAccess = __map_mmap_prot_file(prot);

    const off_t maxSize = off + (off_t)len;

    const DWORD dwMaxSizeLow = (sizeof(off_t) <= sizeof(DWORD)) ?
                    (DWORD)maxSize : (DWORD)(maxSize & 0xFFFFFFFFL);
    const DWORD dwMaxSizeHigh = (sizeof(off_t) <= sizeof(DWORD)) ?
                    (DWORD)0 : (DWORD)((maxSize >> 32) & 0xFFFFFFFFL);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

    errno = 0;

    if (len == 0
        /* Unsupported flag combinations */
        || (flags & MAP_FIXED) != 0
        /* Usupported protection combinations */
        || prot == PROT_EXEC)
    {
        errno = EINVAL;
        return MAP_FAILED;
    }

    h = ((flags & MAP_ANONYMOUS) == 0) ?
                    (HANDLE)_get_osfhandle(fildes) : INVALID_HANDLE_VALUE;

    if ((flags & MAP_ANONYMOUS) == 0 && h == INVALID_HANDLE_VALUE)
    {
        errno = EBADF;
        return MAP_FAILED;
    }

    fm = CreateFileMapping(h, NULL, protect, dwMaxSizeHigh, dwMaxSizeLow, NULL);

    if (fm == NULL)
    {
        errno = __map_mman_error(GetLastError(), EPERM);
        return MAP_FAILED;
    }

    map = MapViewOfFile(fm, desiredAccess, dwFileOffsetHigh, dwFileOffsetLow, len);

    CloseHandle(fm);

    if (map == NULL)
    {
        errno = __map_mman_error(GetLastError(), EPERM);
        return MAP_FAILED;
    }

    return map;
}

int munmap(void *addr, size_t len)
{
  if (UnmapViewOfFile(addr))
      return 0;

  errno =  __map_mman_error(GetLastError(), EPERM);

  return -1;
}

int _mprotect(void *addr, size_t len, int prot)
{
    DWORD newProtect = __map_mmap_prot_page(prot);
    DWORD oldProtect = 0;

    if (VirtualProtect(addr, len, newProtect, &oldProtect))
        return 0;

    errno =  __map_mman_error(GetLastError(), EPERM);

    return -1;
}

int msync(void *addr, size_t len, int flags)
{
    if (FlushViewOfFile(addr, len))
        return 0;

    errno =  __map_mman_error(GetLastError(), EPERM);

    return -1;
}

int mlock(const void *addr, size_t len)
{
    if (VirtualLock((LPVOID)addr, len))
        return 0;

    errno =  __map_mman_error(GetLastError(), EPERM);

    return -1;
}

int munlock(const void *addr, size_t len)
{
    if (VirtualUnlock((LPVOID)addr, len))
        return 0;

    errno =  __map_mman_error(GetLastError(), EPERM);

    return -1;
}

#pragma endregion MMAN

#endif

typedef void(*NanExecFuncMemoried)(void* memory);
typedef void(*NanExecFunc)(void);
typedef void(__stdcall *NanFarFunc)(void);

#define MEMORY_CAP (10*1000*1000)

typedef struct {
  NanExecFuncMemoried runnable;
  void* memory;
} NanExec;

void* NanStringBuilderToExecGetMemory() {
  void* memory = malloc(MEMORY_CAP);
  memset(memory, 0, MEMORY_CAP);
  return memory;
}

static void NanExecRun(NanExec* run) {
  run->runnable(run->memory);
}

NanExec NanStringBuilderToExec(NanStringBuilder* builder) {
  NanExec exec = {0};
  void* buffer;
  buffer = mmap(0,sizeof(builder->begin),PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON,-1,0);
  memcpy(buffer, builder->begin, builder->size);
  exec.runnable = (NanExecFuncMemoried)buffer;
  exec.memory = NanStringBuilderToExecGetMemory();
  return exec;
}

typedef struct {
  size_t cursor;
  size_t size;
  bool is_end;
  char* content;
} NanStringIterator;

NanStringIterator NanStringIteratorFromString(NanString* original) {
  NanStringIterator it = {
    .content = original->content,
    .cursor = 0,
    .size = original->size,
    .is_end = false
  };
  return it;
}

NanStringIterator NanStringIteratorFromStringBulder(NanStringBuilder* original) {
  NanStringIterator it = {
    .content = NULL,
    .cursor = 0,
    .size = original->size,
    .is_end = false
  };
  it.content = malloc(original->size*sizeof(char));
  memcpy(it.content, original->begin, original->size);
  return it;
}

char NanStringIteratorNext(NanStringIterator* self) {
  if (self->cursor < 0 || self->cursor >= self->size) {
    NAN_PANIC_CODE("index out of bounds");
  }
  if (self->cursor+1 >= self->size) {
    self->is_end = true;
  }
  return self->content[self->cursor++];
}

char NanStringIteratorGetNext(NanStringIterator* self) {
  if (self->cursor < 0 || self->cursor >= self->size) {
    NAN_PANIC_CODE("index out of bounds");
  }
  return self->content[self->cursor];
}

char NanStringIteratorGetNexts(NanStringIterator* self, size_t offset) {
  size_t _index = offset+self->size;
  if (_index < 0 || _index >= self->size) {
    NAN_PANIC_CODE("index out of bounds");
  }
  return self->content[_index];
}

typedef struct {
  size_t cursor;
  size_t size;
  void* content;
} NanIterator;

NanIterator NanIteratorFrom(void* row, size_t size) {
  NanIterator it = {
    .content = NULL,
    .cursor = 0,
    .size = size
  };
  memcpy(it.content, row, size);
  return it;
}

void* NanIteratorNext(NanIterator* self) {
  if (self->cursor < 0 || self->cursor >= self->size) {
    NAN_PANIC_CODE("index out of bounds");
  }
  return (self->content+self->cursor++);
}

bool isCharInNanString(NanString parent, char c) {
  for (int i = 0; i < parent.size; i++) {
    if (parent.content[i] == c) {
      return true;
    }
  }
  return false;
}

bool isCharInString(char* content, char c) {
  for (int i = 0; i < strlen(content); i++) {
    if (content[i] == c) {
      return true;
    }
  }
  return false;
}

#pragma region NAN_DLL
#ifdef _WIN32
typedef HINSTANCE NanHinstance;

typedef struct { 
	NanString name;
	NanFarFunc raw_func;
} NanDllFunc;

typedef struct {
	NanHinstance lib;
	NanString name;
	NanDynamicArray loadedfuncs;
} NanDll;

#define NanGetFuncFromDll(type, dll, name) ((type)NanGetFuncFromDll_raw(dll, name))
#define NanLoadFuncFromDll(dll, name) NanGetFuncFromDll_raw(dll, name)
#define NanDefFunc(type, name, right) type name = right
#define NanDefFuncDLL(type, dll, name) NanDefFunc(type, __##name, NanGetFuncFromDll(type, dll, #name))
#define NanDedFuncDLLStr(type, dll, name) NanDefFunc(type, __##name, NanGetFuncFromDll(type, dll, #name))

NanFarFunc NanGetFuncFromDll_raw(NanDll* dll, char* name) {
	if (dll->lib == NULL) { NAN_PANIC_CODE("dll not loaded"); }
	NanFarFunc _raw_func = (NanFarFunc)GetProcAddress(dll->lib, (LPCSTR)name);
	if (_raw_func == 0) { NAN_PANIC_CODEF("cannot loads func: `%s`", name); }
  NanDllFunc* func = NULL;
  NanString __name = NanStringFromStr(name);

  NanDllFunc* __temp;
  for (int i = 0; i < dll->loadedfuncs.size; i++) {
    func = NanDynamicArrayAt_s(&dll->loadedfuncs, i);
    if (NanStringMatch(&__temp->name, &__name)) { 
      return func->raw_func;
    }
  }

  if (func == NULL) {
    func = malloc(sizeof(NanDllFunc));
    func->name = __name;
    func->raw_func = _raw_func;
  }
  
	NanDynamicArrayPush(&dll->loadedfuncs, func);
  
	return _raw_func;
}

uint32_t NanGetFuncAdressFromDll(NanDll* dll, char* name) {
	if (dll->lib == NULL) { NAN_PANIC_CODE("dll not loaded"); }
	uint32_t adress = (uint32_t)GetProcAddress(dll->lib, (LPCSTR)name);
	return adress;
}

NanDll NanDllCreate() {
	NanDll dll = {
		.lib = NULL,
		.name = NanStringNull,
		.loadedfuncs = NanDynamicArrayCreate(sizeof(NanDllFunc))
	};
	return dll;
}

NanDll NanLoadDll(char* name) {
	NanDll dll = NanDllCreate();
	LPSTR __name = name;
	dll.lib = LoadLibrary(__name);
	if (dll.lib == NULL) { NAN_PANIC_CODE("dll not loaded"); }
	return dll;
}

void NanDllDestroy(NanDll* dll) {
  FreeLibrary(dll->lib);
}
#endif
#pragma endregion NAN_DLL

#pragma region NAN_ARGS
typedef struct {
  NanString flag;
  size_t value_i;
} NanArgument;

typedef struct {
  NanDynamicArray _with_flags;
  NanDynamicArray content;
} NanArgumentRow;

/// flag without `-` or `--`
bool NanArgumentIsInRow(NanArgumentRow* row, char* flag) {
  NanString _flag_short = NanStringFromStrs("-", flag);
  NanString _flag_long  = NanStringFromStrs("--", flag);

  for (int i = 0; i < row->_with_flags.size; i++) {
    NanArgument* arg = NanDynamicArrayAt(&row->_with_flags, i);
    if (
      NanStringMatch(&arg->flag, &_flag_short) ||
      NanStringMatch(&arg->flag, &_flag_long)
    ) {
      return true;
    }
  }
  return false;
}

/// flag with `-` or `--`
bool NanArgumentIsInRowAbs(NanArgumentRow* row, char* flag) {
  NanString _flag = NanStringFromStr(flag);
  for (int i = 0; i < row->_with_flags.size; i++) {
    NanArgument* arg = NanDynamicArrayAt(&row->_with_flags, i);
    if (NanStringMatch(&arg->flag, &_flag)) { return true; }
  }
  return false;
}

NanString* NanArgumentRowGet(NanArgumentRow* row, size_t index) {
  void* arg = NanDynamicArrayAt_s(&row->content, index);
  if (arg == NULL) { return &NanStringNull; }
  return arg;
}

NanString* NanArgumentRowFindPathOne(NanArgumentRow* row) {
  for (int i = 0; i < row->content.size; i++) { 
    NanString* arg = NanDynamicArrayAt(&row->content, i);
    if (NanIsFilePath(arg)) { return arg; }
  }
  return &NanStringNull;
}

NanArgumentRow NanParseArguments(int argc, char** argv) {
  NanDynamicArray _wflags = NanDynamicArrayCreate(sizeof(NanArgument));
  NanDynamicArray _args = NanDynamicArrayCreate(sizeof(NanString));
  size_t cursor = 0;
  while (cursor < argc) {
    NanString arg = NanStringFromStr(argv[cursor++]);
    if (
      NanStringStartWith(&arg, "-") ||
      NanStringStartWith(&arg, "--")
    ) {
      NanArgument* __arg = malloc(sizeof(NanArgument));
      __arg->flag = arg;
      if (cursor+1 < argc) {
        __arg->value_i = _args.size;
      } else {
        __arg->value_i = (size_t)-1;
      }
      NanDynamicArrayPush(&_wflags, __arg);
    }
    else {
      NanDynamicArrayPush(&_args, &arg);
    }
  }
  NanArgumentRow ar = {
    .content = _args,
    ._with_flags = _wflags
  };
  return ar;
}

#pragma endregion NAN_ARGS




typedef struct {
  NanString content;
  ubyte type;
} NanLexerUnit;

typedef struct {
  NanDynamicArray tokens;
  size_t cursor;
} NanLexer;

NanLexer NanLexerCreate() {
  NanLexer lexer = {
    .tokens = NanDynamicArrayCreate(sizeof(NanLexerUnit)),
    .cursor = 0
  };
  return lexer;
}

void NanLexerAppend(NanLexer* lexer, NanLexerUnit* unit) {
  NanDynamicArrayPush(&lexer->tokens, unit);
}

NanLexerUnit* NanLexerNext(NanLexer* lexer) {
  if (lexer->tokens.size < lexer->cursor) {
    return NULL;
  }
  return lexer->tokens.begin+(lexer->cursor++);
}

typedef struct {
  NanString content;
  const ubyte word_gap;
  const ubyte emptybyte;
  const ubyte nextbyte;
  const ubyte nextstring;
  const ubyte start;
  const ubyte end;
} NanDescryptor;


NanDescryptor NanDescryptorCreate() {
  NanDescryptor descr = {
    .word_gap = (ubyte)(8),
    .nextbyte = (ubyte)(1),
    .emptybyte = (ubyte)(2),
    .start = (ubyte)(3),
    .end = (ubyte)(4),
    .nextstring = (ubyte)(0),
    .content = (NanString){0}
  };
  return descr;
}

NanDescryptor NanDescryptorFromString(NanString* str) {
  NanDescryptor descr = {
    .word_gap = (ubyte)(8),
    .nextbyte = (ubyte)(1),
    .emptybyte = (ubyte)(2),
    .start = (ubyte)(3),
    .end = (ubyte)(4),
    .nextstring = (ubyte)(0),
    .content = NanStringCopy(str)
  };
  return descr;
}

void NanDescryptorFront(NanDescryptor* descr, NanLexer lexer, ubyte textTokenType) {
  NanStringBuilder builder = NanStringBuilderCreate(5);
  NanLexerUnit* unit;
  do {
    unit = NanLexerNext(&lexer);
    NanStringBuilderPushB(&builder, descr->nextbyte);
    ubyte final_token_type = unit->type+descr->word_gap;
    if (final_token_type >= ffbyte) {
      NanStringBuilderPushB(&builder, descr->nextbyte);
    }
    final_token_type = (ffbyte - unit->type)+descr->word_gap;
    if (final_token_type == 0) {
      final_token_type = descr->emptybyte;
    }
    NanStringBuilderPushB(&builder, final_token_type);

    NanStringBuilderPushB(&builder, descr->nextstring);
    if (unit->type == textTokenType) {
      int length = unit->content.size;
      while (length >= ffbyte) {
        length -= ffbyte;
        NanStringBuilderPushB(&builder, descr->nextbyte);
      }
      if (length == 0) {
        NanStringBuilderPushB(&builder, descr->emptybyte);
      }
      else if (length < 0) {
        length += ffbyte;
      }
      NanStringBuilderPushB(&builder, descr->emptybyte);
      NanStringIterator it = NanStringIteratorFromString(&unit->content);
      while (!it.is_end) {
        NanStringBuilderPushB(&builder, NanStringIteratorNext(&it));
      }
    }

  } while (unit != NULL);

  descr->content = NanStringBuilderFinalize(&builder);
}

NanLexer NanDescryptorBack(NanDescryptor* self) {
  NanStringIterator it = NanStringIteratorFromString(&self->content);
  NanLexer lexer = NanLexerCreate();
  while (!it.is_end) {
    ubyte c = NanStringIteratorNext(&it);
    if (c == self->nextbyte) {
      int counter = 0;
      while (c == ffbyte) {
        counter += ffbyte;
        c = NanStringIteratorNext(&it);
      }
      if (c != self->emptybyte) {
        counter += c;
      }
      NanLexerUnit unit = {
        .content = NanStringNull,
        .type = counter-self->word_gap
      };
      NanDynamicArrayPush(&lexer.tokens, &unit);
    }
    else if (c == self->nextstring) {
      c = NanStringIteratorNext(&it);
      int counter = 0;
      while (c == ffbyte) {
        counter += ffbyte;
        c = NanStringIteratorNext(&it);
      }
      if (c != self->emptybyte) {
        counter += c;
      }
      size_t size = counter;
      NanStringBuilder builder = NanStringBuilderCreate(5);
      for (int i = 0; i < size; i++) {
        c = NanStringIteratorNext(&it);
        NanStringBuilderPushB(&builder, c);
      }
      NanLexerUnit* last_unit = NanDynamicArrayEnd(&lexer.tokens);
      last_unit->content = NanStringBuilderFinalize(&builder);
    }
  }
}

typedef void(*NanEventCallback)(void*);

typedef struct {
  NanString name;
  NanEventCallback callback;
} NanEventRowElement;

NanDynamicArray NanEventRowCreate() {
  NanDynamicArray arr = NanDynamicArrayCreate(sizeof(NanEventRowElement));
  return arr;
}

NanEventRowElement* NanEventRowFindOne(NanDynamicArray* self, char* name) {
  NanString __name = NanStringFromStr(name);
  for (int i = 0; i < self->size; i++) {
    NanEventRowElement* el = NanDynamicArrayAt(self, i);
    if (NanStringMatch(&el->name, &__name)) {
      return el;
    }
  }
} 

NanDynamicArray NanEventRowFindAll(NanDynamicArray* self, char* name) {
  NanString __name = NanStringFromStr(name);
  NanDynamicArray matched = NanDynamicArrayCreate(sizeof(NanEventRowElement));
  for (int i = 0; i < self->size; i++) {
    NanEventRowElement* el = NanDynamicArrayAt(self, i);
    if (NanStringMatch(&el->name, &__name)) {
      NanDynamicArrayPush(&matched, el);
    }
  }
  return matched;
} 

void NanEventRowRun(NanDynamicArray* self, void* ev) {
  for (int i = 0; i < self->size; i++) {
    NanEventRowElement* el = NanDynamicArrayAt(self, i);
    el->callback(ev);
  }
}

void NanEventRowRunNamed(NanDynamicArray* self, char* name, void* ev) {
  NanDynamicArray __finded = NanEventRowFindAll(self, name);
  for (int i = 0; i < __finded.size; i++) {
    NanEventRowElement* el = NanDynamicArrayAt(&__finded, i);
    el->callback(ev);
  }
}

typedef struct {
  NanString name;
  int value;
} NanTypeAssociation;

typedef struct {
  size_t start;
  size_t end;
  void* content;
} NanMemoryCart;

typedef struct {
  size_t start;
  size_t size;
} NanRange;

typedef struct {
  NanDynamicArray frees;
  NanDynamicArray uses;
  size_t size;
} NanJitMemory;

NanJitMemory NanJitMemoryCreate() {
  NanJitMemory jm = {
    .frees = NanDynamicArrayCreate(sizeof(NanRange)),
    .uses = NanDynamicArrayCreate(sizeof(NanRange)),
    .size = 0
  };
  return jm; 
}

// todo:
// void NanJitMemoryClean(NanJitMemory* self) {
// 	if (self->frees.size == 0) { return; }
// 	for (int i = 0; i < self->frees.size; i++) {
    
// 	}
// }

NanRange* NanJitMemoryAllocate(NanJitMemory* self, size_t size) {
  NanRange* next_ = {0};
  if (self->frees.size != 0) {
    for (int i = 0; i < self->frees.size; i++) {
      NanRange* free_d = NanDynamicArrayAt(&self->frees, i); 
      if (free_d->size == size) {
        next_->start = free_d->start;
        next_->size = size;
        NanDynamicArrayDelete(&self->frees, i);
        return next_;
      }
      if (free_d->size > size) {
        next_->start = free_d->start;
        next_->size = size;
        next_->size -= size;
        return next_;
      }
    }
  }
  next_->start = self->size;
  next_->size = size;
  self->size += size;
  NanDynamicArrayPush(&self->uses, next_);
  return next_;
}

void NanJitMemoryFree(NanJitMemory* self, NanRange* range) {
  NanRange* next_ = {0};
  for (int i = 0; i < self->uses.size; i++) {
    NanRange* uses_d = NanDynamicArrayAt(&self->uses, i); 
    if (uses_d->size == range->size && uses_d->start == range->start) {
      next_->size = uses_d->size;
      next_->start = uses_d->start;
      NanDynamicArrayDelete(&self->uses, i);
      if (i+1 < self->uses.size) {
        uses_d = NanDynamicArrayAt(&self->uses, i+1); 
        if (uses_d->start-1 == next_->start+next_->size) {
          next_->size += uses_d->size;
          NanDynamicArrayDelete(&self->uses, i+1);
        }
      }
      if (i-1 > 0) {
        uses_d = NanDynamicArrayAt(&self->uses, i-1); 
        if (uses_d->start+uses_d->size == next_->start-1) {
          next_->start -= uses_d->size;
          next_->size += uses_d->size;
          NanDynamicArrayDelete(&self->uses, i-1);
        }
      }

      return;
    }
  }
  NAN_PANIC_CODE("range of code undefined");
}

typedef enum {
  NA_PRINT,
  NA_INPUT  
} NanJitActionKind;

typedef struct {
  NanJitActionKind kind;
  NanString content;
} NanJitToken;

typedef struct {
  // NanDescryptor descryptor;	
  NanDynamicArray tokens;
  NanJitMemory memory_observer;  
} NanJit;

// void NanJitAddEvent(NanJit* self, const char* name, NanEventCallback callback) {
//   NanEventRowElement* ev = malloc(sizeof(NanEventRowElement));
//   ev->callback = callback;
//   ev->name = NanStringFromStr(name);
//   NanDynamicArrayPush(&self->event_row, ev);
// }

// void NanJitAddAssotiation(NanJit* self, const char* name, int value) {
//   NanTypeAssociation* a__ = malloc(sizeof(NanTypeAssociation));
//   a__->name = NanStringFromStr(name);
//   a__->value = value;
//   NanDynamicArrayPush(&self->associations, a__);
// }

NanJit NanJitCreate() {
  NanJit __j = {
    // .associations = NanDynamicArrayCreate(sizeof(NanTypeAssociation)),
    .tokens = NanDynamicArrayCreate(sizeof(NanJitToken)),
    .memory_observer = NanJitMemoryCreate()
    // .event_row = NanDynamicArrayCreate(sizeof(NanEventRowElement))
  };	
  return __j;
}

void NanJitAppend(NanJit* self, NanJitActionKind kind) {
  NanJitToken* tk = malloc(sizeof(NanJitToken));
  tk->content = NanStringNull;
  tk->kind = kind; 
  NanDynamicArrayPush(&self->tokens, tk);
}
void NanJitAppendNS(NanJit* self, NanJitActionKind kind, NanString value) {  
  NanJitToken* tk = malloc(sizeof(NanJitToken));
  tk->content = value;
  tk->kind = kind;
  NanDynamicArrayPush(&self->tokens, tk);
}
void NanJitAppendCS(NanJit* self, NanJitActionKind kind, char* value) {
  NanJitToken* tk = malloc(sizeof(NanJitToken));
  tk->content = NanStringFromStr(value);
  tk->kind = kind;
  NanDynamicArrayPush(&self->tokens, tk);  
}

static void NanJitCall(NanStringBuilder* builder, int dist) {
  int32_t __dist = (int32_t)dist;
  NanStringBuilderPushS(builder, "\xE8"); // call ..
  int32_t __start_address = builder->size;
  NanStringBuilderPushS(builder, "\x00\x00\x00\x00");
  memcpy(builder->begin+__start_address, &__dist, sizeof(__dist));
}
static void NanJitAddRdi(NanStringBuilder* builder, uint32_t count) {
  NanStringBuilderPushS(builder, "\x48\x83\xC7"); // add rdi, ...
  NanStringBuilderPushMany(builder, &count, sizeof(count));
}
static void NanJitSubRdi(NanStringBuilder* builder, uint32_t count) {
  NanStringBuilderPushS(builder, "\x48\x83\xEF"); // sub rdi, ...
  NanStringBuilderPushMany(builder, &count, sizeof(count));
}
// rax*=rdi
static void NanJitMul(NanStringBuilder* builder) {
  NanStringBuilderPushS(builder, "\x48\xF7\xE7"); // mul rdi
}
// rdi*=const
static void NanJitIMul(NanStringBuilder* builder, int number) {
  uint32_t un = (uint32_t)number;
  NanStringBuilderPushS(builder, "\x48\x6B\xFF"); // imul rdi, ...
  NanStringBuilderPushMany(builder, &un, sizeof(un));
}
// rdi*=const
static void NanJitIMul2(NanStringBuilder* builder, int lnumber, int rnumber) {
  uint32_t un1 = (uint32_t)lnumber;
  uint32_t un2 = (uint32_t)rnumber;
  NanStringBuilderPushS(builder, "\x50");         // push rax
  NanStringBuilderPushS(builder, "\x48\xc7\xc0"); // mov rax, ...
  NanStringBuilderPushMany(builder, &un1, sizeof(un1));
  NanStringBuilderPushS(builder, "\x48\x6b\xf8"); // imul rdi, rax, ...
  NanStringBuilderPushMany(builder, &un2, sizeof(un2));
  NanStringBuilderPushS(builder, "\x58");         // pop rax
}
// rax/=rdi
static void NanJitDiv(NanStringBuilder* builder) {
  NanStringBuilderPushS(builder, "\x48\xF7\xF7"); // div rdi
}
static void NanJitIncRdi(NanStringBuilder* builder) {
  NanStringBuilderPushS(builder, "\x48\xff\xcf"); // dec rdi
}
static void NanJitDecRdi(NanStringBuilder* builder) {
  NanStringBuilderPushS(builder, "\x48\xff\xc7"); // inc rdi
}
static void NanJitMovRdi(NanStringBuilder* builder, char* word) {
  NanStringBuilderPushS(builder, "\x48\xc7\xc0"); // mov rax, ...
  NanStringBuilderPushMany(builder, word, strlen(word));
}

static void NanJitMovRbp(NanStringBuilder* builder, int offset, int number) {
  uint32_t __number = (uint32_t)number;
  uint32_t __offset = (uint32_t)offset;
  NanStringBuilderPushS(builder, "\x48\xC7\x45"); // mov QWORD PTR [rbp-<_offset>], 0x11
  NanStringBuilderPushMany(builder, &__offset, sizeof(__offset));
  NanStringBuilderPushMany(builder, &__number, sizeof(__number));
}

static void NanJitPushText(NanStringBuilder* builder, char* text) {
  for (int i = 0; i < strlen(text); i++) {
    ubyte __char = (ubyte)text[i];
    NanStringBuilderPushS(builder, "\x6a"); // push ...
    NanStringBuilderPushC(builder, __char);
  }
}

static void NanJitMovRbpRdi(NanStringBuilder* builder) {
  NanStringBuilderPushS(builder,  "\x48\x89\xe7" );
}

// use `rdi` for translate message
static void NanJitOutputChar(NanStringBuilder* builder) {
#ifdef __linux__
  NanStringBuilderPushS(builder,
    "\x48\xC7\xC0\x01\x00\x00\x00"  // mov	rax, 1
    "\x48\x89\xE6"                  // mov	rsi, rsp
    "\x48\xc7\xc7\x01\x00\x00\x00"  // mov	rdi, 1 ; stdout
    "\x48\xc7\xc2\x01\x00\x00\x00"  // mov	rdx, 1
    "\x0f\x05" 	                    // syscall
  );
#elif _WIN32
  NanStringBuilderPushS(builder,
    "\xba\x01\x00\x00\x00" 					// mov  edx, 0x1
    "\x89\xe1" 	                    // mov  ecx, esp
    "\xbb\x01\x00\x00\x00" 					// mov  ebx, 0x1
    "\xb8\x04\x00\x00\x00" 	        // mov  eax, 0x4
    "\x0f\x05" 	                    // syscall
  );
#endif
}

static void NanJitEOP(NanStringBuilder* builder) {
#ifdef  __linux__
  NanStringBuilderPushS(builder, "\x48\xC7\xC0\x3C\x00\x00\x00" ); // mov rax, 60
  NanStringBuilderPushS(builder, "\x48\xC7\xC7\x00\x00\x00\x00" ); // mov rdi, 0
  NanStringBuilderPushS(builder, "\x0f\x05" ); // syscall
#elif _WIN32
  // NAN_WARN_CODE("win in dev");
  NanStringBuilderPushStr(builder, "\x48\xC7\xC0\x00\x00\x00\x00",  7); // mov rax, 0
  NanStringBuilderPushS(builder, "\xC3"); // ret
#endif
}


#ifdef  __linux__
#define NanJitExtPutString(builder, text) \
  for (int i = 0; i < strlen(text); i++) {\
    uint32_t __char = (uint32_t)text[i];\
    NanStringBuilderPushS(builder, "\x68");\
    NanStringBuilderPushMany(builder, &__char, sizeof(__char));\
    NanStringBuilderPushStr(builder,  "\x48\xC7\xC0\x01\x00\x00\x00"  , 7);\
    NanStringBuilderPushStr(builder,  "\x48\x89\xE6"                  , 3);\
    NanStringBuilderPushStr(builder,  "\x48\xc7\xc7\x01\x00\x00\x00"  , 7);\
    NanStringBuilderPushStr(builder,  "\x48\xc7\xc2\x01\x00\x00\x00"  , 7);\
    NanStringBuilderPushStr(builder,  "\x0f\x05"                      , 2);\
  }
#elif _WIN32
#define NanJitExtPutString(builder, text)\
  for (int i = 0; i < strlen(text); i++) {\
    uint32_t __char = (uint32_t)text[i];\
    NanStringBuilderPushStr(builder,  "\x48\xC7\xC1"  , 3);\
    NanStringBuilderPushMany(builder, &__char, sizeof(__char));\
    NanStringBuilderPushStr(builder,  "\xFF\x14\x25"  , 3);\
    NanStringBuilderPushMany(builder, &adress_putchar, sizeof(adress_putchar));\
  }
#endif


#define NAN_DEBUG if(is_debug) 

void NanJitRun_RAW(NanJit* self, bool is_debug) {  
  NanStringBuilder builder = NanStringBuilderCreate(5);
#if _WIN32
  NanDll msvcrt_dll = NanLoadDll("msvcrt.dll");\
  uint32_t adress_putchar = NanGetFuncAdressFromDll(&msvcrt_dll, "putchar");
#endif
  for (int i = 0; i < self->tokens.size; i++) {
    NanJitToken* tk = NanDynamicArrayAt(&self->tokens, i);
    switch (tk->kind) {
      case NA_PRINT: {
        if (NanStringIsNull(&tk->content)) {
          NAN_PANIC_CODE("NA_PRINT must have `.content`");
        }
        NanJitExtPutString(&builder, NanStringC_Str(&tk->content));
      } break;
    };
  }
	NanJitEOP(&builder);
  NAN_DEBUG NanStringBuilderPrintX(&builder);
	NanExec exec = NanStringBuilderToExec(&builder);
	NanExecRun(&exec);
}

static void NanJitRun(NanJit* self) {
  NanJitRun_RAW(self, false);
}
static void NanJitDebug(NanJit* self) {
  NanJitRun_RAW(self, true);
}

static const ubyte NanLexerTEXT  = 2;
static const ubyte NanLexerWRITE = 3;
static const ubyte NanLexerINPUT = 4;

void NanJitLex(NanJit* self, NanLexer* lexer) {
  NanLexerUnit* unit; 
  while ((unit = NanLexerNext(lexer)) != NULL) {
    if (unit->type == NanLexerWRITE) {
      if ((unit = NanLexerNext(lexer)) == NULL || unit->type != NanLexerTEXT) {
        NAN_PANIC_CODE("after write operation must be a string");
      }
      NanJitAppendNS(self, NA_PRINT, unit->content);
    }
  }
}

static const char* NanCharConsoleClear = "\033[00m";
static const char* NanCharConsoleCyanFG = "\033[96m";
static const char* NanCharConsoleGrayFG = "\033[02m";

#define NanConsoleRC(a) a, NanCharConsoleClear

#ifdef __cplusplus
}
#endif

#endif