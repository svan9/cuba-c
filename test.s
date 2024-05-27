	.file	"test.c"
	.text
Ltext0:
	.def	___map_mman_error;	.scl	3;	.type	32;	.endef
___map_mman_error:
LFB26:
	.file 1 "cuba/mman.c"
	.loc 1 13 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 14 0
	cmpl	$0, 8(%ebp)
	jne	L2
	.loc 1 15 0
	movl	$0, %eax
	jmp	L3
L2:
	.loc 1 17 0
	movl	8(%ebp), %eax
L3:
	.loc 1 18 0
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.def	___map_mmap_prot_page;	.scl	3;	.type	32;	.endef
___map_mmap_prot_page:
LFB27:
	.loc 1 21 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 22 0
	movl	$0, -4(%ebp)
	.loc 1 24 0
	cmpl	$0, 8(%ebp)
	jne	L5
	.loc 1 25 0
	movl	-4(%ebp), %eax
	jmp	L6
L5:
	.loc 1 27 0
	movl	8(%ebp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	L7
	.loc 1 29 0
	movl	8(%ebp), %eax
	andl	$2, %eax
	.loc 1 30 0
	testl	%eax, %eax
	je	L8
	.loc 1 30 0 is_stmt 0 discriminator 1
	movl	$64, %eax
	jmp	L9
L8:
	.loc 1 30 0 discriminator 2
	movl	$32, %eax
L9:
	.loc 1 29 0 is_stmt 1
	movl	%eax, -4(%ebp)
	jmp	L10
L7:
	.loc 1 34 0
	movl	8(%ebp), %eax
	andl	$2, %eax
	.loc 1 35 0
	testl	%eax, %eax
	je	L11
	.loc 1 35 0 is_stmt 0 discriminator 1
	movl	$4, %eax
	jmp	L12
L11:
	.loc 1 35 0 discriminator 2
	movl	$2, %eax
L12:
	.loc 1 34 0 is_stmt 1
	movl	%eax, -4(%ebp)
L10:
	.loc 1 38 0
	movl	-4(%ebp), %eax
L6:
	.loc 1 39 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE27:
	.def	___map_mmap_prot_file;	.scl	3;	.type	32;	.endef
___map_mmap_prot_file:
LFB28:
	.loc 1 42 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 43 0
	movl	$0, -4(%ebp)
	.loc 1 45 0
	cmpl	$0, 8(%ebp)
	jne	L14
	.loc 1 46 0
	movl	-4(%ebp), %eax
	jmp	L15
L14:
	.loc 1 48 0
	movl	8(%ebp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	L16
	.loc 1 49 0
	orl	$4, -4(%ebp)
L16:
	.loc 1 50 0
	movl	8(%ebp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	L17
	.loc 1 51 0
	orl	$2, -4(%ebp)
L17:
	.loc 1 52 0
	movl	8(%ebp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	L18
	.loc 1 53 0
	orl	$32, -4(%ebp)
L18:
	.loc 1 55 0
	movl	-4(%ebp), %eax
L15:
	.loc 1 56 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE28:
	.globl	_mmap
	.def	_mmap;	.scl	2;	.type	32;	.endef
_mmap:
LFB29:
	.loc 1 59 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$84, %esp
	.cfi_offset 3, -12
	.loc 1 62 0
	movl	$-1, -12(%ebp)
	.loc 1 69 0
	movl	28(%ebp), %eax
	movl	%eax, -16(%ebp)
	.loc 1 71 0
	movl	$0, -20(%ebp)
	.loc 1 73 0
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	___map_mmap_prot_page
	movl	%eax, -24(%ebp)
	.loc 1 74 0
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	___map_mmap_prot_file
	movl	%eax, -28(%ebp)
	.loc 1 76 0
	movl	12(%ebp), %edx
	movl	28(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -32(%ebp)
	.loc 1 78 0
	movl	-32(%ebp), %eax
	movl	%eax, -36(%ebp)
	.loc 1 80 0
	movl	$0, -40(%ebp)
	.loc 1 87 0
	call	__errno
	movl	$0, (%eax)
	.loc 1 89 0
	cmpl	$0, 12(%ebp)
	je	L20
	.loc 1 91 0
	movl	20(%ebp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	jne	L20
	.loc 1 93 0
	cmpl	$4, 16(%ebp)
	jne	L21
L20:
	.loc 1 95 0
	call	__errno
	movl	$22, (%eax)
	.loc 1 96 0
	movl	$-1, %eax
	jmp	L22
L21:
	.loc 1 99 0
	movl	20(%ebp), %eax
	andl	$32, %eax
	.loc 1 100 0
	testl	%eax, %eax
	jne	L23
	.loc 1 100 0 is_stmt 0 discriminator 1
	movl	24(%ebp), %eax
	movl	%eax, (%esp)
	call	__get_osfhandle
	jmp	L24
L23:
	.loc 1 100 0 discriminator 2
	movl	$-1, %eax
L24:
	.loc 1 99 0 is_stmt 1
	movl	%eax, -44(%ebp)
	.loc 1 102 0
	movl	20(%ebp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	jne	L25
	.loc 1 102 0 is_stmt 0 discriminator 1
	cmpl	$-1, -44(%ebp)
	jne	L25
	.loc 1 104 0 is_stmt 1
	call	__errno
	movl	$9, (%eax)
	.loc 1 105 0
	movl	$-1, %eax
	jmp	L22
L25:
	.loc 1 108 0
	movl	$0, 20(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-40(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	-44(%ebp), %eax
	movl	%eax, (%esp)
	call	_CreateFileMappingA@24
	subl	$24, %esp
	movl	%eax, -48(%ebp)
	.loc 1 110 0
	cmpl	$0, -48(%ebp)
	jne	L26
	.loc 1 112 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 113 0
	movl	$-1, %eax
	jmp	L22
L26:
	.loc 1 116 0
	movl	12(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	_MapViewOfFile@20
	subl	$20, %esp
	movl	%eax, -12(%ebp)
	.loc 1 118 0
	movl	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	_CloseHandle@4
	subl	$4, %esp
	.loc 1 120 0
	cmpl	$0, -12(%ebp)
	jne	L27
	.loc 1 122 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 123 0
	movl	$-1, %eax
	jmp	L22
L27:
	.loc 1 126 0
	movl	-12(%ebp), %eax
L22:
	.loc 1 127 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE29:
	.globl	_munmap
	.def	_munmap;	.scl	2;	.type	32;	.endef
_munmap:
LFB30:
	.loc 1 130 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	.loc 1 131 0
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_UnmapViewOfFile@4
	subl	$4, %esp
	testl	%eax, %eax
	je	L29
	.loc 1 132 0
	movl	$0, %eax
	jmp	L30
L29:
	.loc 1 134 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 136 0
	movl	$-1, %eax
L30:
	.loc 1 137 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE30:
	.globl	__mprotect
	.def	__mprotect;	.scl	2;	.type	32;	.endef
__mprotect:
LFB31:
	.loc 1 140 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	.loc 1 141 0
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	___map_mmap_prot_page
	movl	%eax, -12(%ebp)
	.loc 1 142 0
	movl	$0, -16(%ebp)
	.loc 1 144 0
	leal	-16(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_VirtualProtect@16
	subl	$16, %esp
	testl	%eax, %eax
	je	L32
	.loc 1 145 0
	movl	$0, %eax
	jmp	L34
L32:
	.loc 1 147 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 149 0
	movl	$-1, %eax
L34:
	.loc 1 150 0 discriminator 1
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE31:
	.globl	_msync
	.def	_msync;	.scl	2;	.type	32;	.endef
_msync:
LFB32:
	.loc 1 153 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	.loc 1 154 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_FlushViewOfFile@8
	subl	$8, %esp
	testl	%eax, %eax
	je	L36
	.loc 1 155 0
	movl	$0, %eax
	jmp	L37
L36:
	.loc 1 157 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 159 0
	movl	$-1, %eax
L37:
	.loc 1 160 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE32:
	.globl	_mlock
	.def	_mlock;	.scl	2;	.type	32;	.endef
_mlock:
LFB33:
	.loc 1 163 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	.loc 1 164 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_VirtualLock@8
	subl	$8, %esp
	testl	%eax, %eax
	je	L39
	.loc 1 165 0
	movl	$0, %eax
	jmp	L40
L39:
	.loc 1 167 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 169 0
	movl	$-1, %eax
L40:
	.loc 1 170 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE33:
	.globl	_munlock
	.def	_munlock;	.scl	2;	.type	32;	.endef
_munlock:
LFB34:
	.loc 1 173 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	.loc 1 174 0
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_VirtualUnlock@8
	subl	$8, %esp
	testl	%eax, %eax
	je	L42
	.loc 1 175 0
	movl	$0, %eax
	jmp	L43
L42:
	.loc 1 177 0
	call	__errno
	movl	%eax, %ebx
	call	_GetLastError@0
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	___map_mman_error
	movl	%eax, (%ebx)
	.loc 1 179 0
	movl	$-1, %eax
L43:
	.loc 1 180 0
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE34:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "r\0"
LC1:
	.ascii "asm/test1.asm\0"
LC2:
	.ascii "err\0"
LC3:
	.ascii "%i\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB35:
	.file 2 "test.c"
	.loc 2 6 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$1056, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	.loc 2 6 0
	call	___main
LVL0:
	.loc 2 8 0
	movl	$LC0, 4(%esp)
	movl	$LC1, (%esp)
	call	_fopen
	movl	%eax, 1052(%esp)
	.loc 2 10 0
	cmpl	$0, 1052(%esp)
	jne	L45
	.loc 2 11 0
	movl	$LC2, (%esp)
	call	_printf
	.loc 2 12 0
	movl	$1, (%esp)
	call	_exit
L45:
	.loc 2 15 0
	movl	1052(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$1000, 4(%esp)
	leal	44(%esp), %eax
	movl	%eax, (%esp)
	call	_fgets
	testl	%eax, %eax
	je	L46
LBB2:
	.loc 2 17 0
	movl	$0, 20(%esp)
	movl	$-1, 16(%esp)
	movl	$34, 12(%esp)
	movl	$7, 8(%esp)
	movl	$1000, 4(%esp)
	movl	$0, (%esp)
	call	_mmap
	movl	%eax, 1048(%esp)
	.loc 2 20 0
	movl	1048(%esp), %eax
	movl	%eax, %edx
	leal	44(%esp), %eax
	movl	$1000, %ecx
	movl	(%eax), %ebx
	movl	%ebx, (%edx)
	movl	-4(%eax,%ecx), %ebx
	movl	%ebx, -4(%edx,%ecx)
	leal	4(%edx), %ebx
	andl	$-4, %ebx
	subl	%ebx, %edx
	subl	%edx, %eax
	addl	%edx, %ecx
	andl	$-4, %ecx
	shrl	$2, %ecx
	movl	%ecx, %edx
	movl	%ebx, %edi
	movl	%eax, %esi
	movl	%edx, %ecx
	rep movsl
	.loc 2 23 0
	movl	1048(%esp), %eax
	call	*%eax
LVL1:
	movl	%eax, 1044(%esp)
	.loc 2 24 0
	movl	1044(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	_printf
	.loc 2 26 0
	movl	1044(%esp), %eax
	jmp	L48
L46:
LBE2:
	.loc 2 29 0
	movl	1052(%esp), %eax
	movl	%eax, (%esp)
	call	_fclose
	.loc 2 31 0
	movl	$0, %eax
L48:
	.loc 2 32 0 discriminator 1
	leal	-12(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE35:
Letext0:
	.file 3 "e:/progs/libs/mingw/lib/gcc/mingw32/6.3.0/include/stddef.h"
	.file 4 "e:/progs/libs/mingw/include/sys/types.h"
	.file 5 "e:/progs/libs/mingw/include/stdio.h"
	.file 6 "e:/progs/libs/mingw/include/stdlib.h"
	.file 7 "e:/progs/libs/mingw/include/windef.h"
	.file 8 "e:/progs/libs/mingw/include/winnt.h"
	.file 9 "e:/progs/libs/mingw/include/basetyps.h"
	.file 10 "e:/progs/libs/mingw/include/unknwn.h"
	.file 11 "e:/progs/libs/mingw/include/objidl.h"
	.file 12 "e:/progs/libs/mingw/include/cguid.h"
	.file 13 "e:/progs/libs/mingw/include/olectlid.h"
	.file 14 "e:/progs/libs/mingw/include/oaidl.h"
	.section	.debug_info,"dr"
Ldebug_info0:
	.long	0x1cda
	.word	0x4
	.secrel32	Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.ascii "GNU C11 6.3.0 -mtune=generic -march=i586 -g\0"
	.byte	0xc
	.ascii "test.c\0"
	.ascii "E:\\so2u\\GITHUB\\cuba\\cuba-c\0"
	.long	Ltext0
	.long	Letext0-Ltext0
	.secrel32	Ldebug_line0
	.uleb128 0x2
	.ascii "size_t\0"
	.byte	0x3
	.byte	0xd8
	.long	0x75
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "unsigned int\0"
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.ascii "short unsigned int\0"
	.uleb128 0x2
	.ascii "__off32_t\0"
	.byte	0x4
	.byte	0x3e
	.long	0xac
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii "long int\0"
	.uleb128 0x2
	.ascii "_off_t\0"
	.byte	0x4
	.byte	0x43
	.long	0x9b
	.uleb128 0x2
	.ascii "off_t\0"
	.byte	0x4
	.byte	0x4b
	.long	0xb8
	.uleb128 0x4
	.long	0xc6
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.ascii "long long int\0"
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.ascii "int\0"
	.uleb128 0x4
	.long	0xe9
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "char\0"
	.uleb128 0x5
	.ascii "_iobuf\0"
	.byte	0x20
	.byte	0x5
	.byte	0xd2
	.long	0x184
	.uleb128 0x6
	.ascii "_ptr\0"
	.byte	0x5
	.byte	0xd4
	.long	0x184
	.byte	0
	.uleb128 0x6
	.ascii "_cnt\0"
	.byte	0x5
	.byte	0xd5
	.long	0xe9
	.byte	0x4
	.uleb128 0x6
	.ascii "_base\0"
	.byte	0x5
	.byte	0xd6
	.long	0x184
	.byte	0x8
	.uleb128 0x6
	.ascii "_flag\0"
	.byte	0x5
	.byte	0xd7
	.long	0xe9
	.byte	0xc
	.uleb128 0x6
	.ascii "_file\0"
	.byte	0x5
	.byte	0xd8
	.long	0xe9
	.byte	0x10
	.uleb128 0x6
	.ascii "_charbuf\0"
	.byte	0x5
	.byte	0xd9
	.long	0xe9
	.byte	0x14
	.uleb128 0x6
	.ascii "_bufsiz\0"
	.byte	0x5
	.byte	0xda
	.long	0xe9
	.byte	0x18
	.uleb128 0x6
	.ascii "_tmpfname\0"
	.byte	0x5
	.byte	0xdb
	.long	0x184
	.byte	0x1c
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0xf5
	.uleb128 0x2
	.ascii "FILE\0"
	.byte	0x5
	.byte	0xdc
	.long	0xfd
	.uleb128 0x8
	.long	0x18a
	.long	0x1a1
	.uleb128 0x9
	.byte	0
	.uleb128 0xa
	.ascii "_iob\0"
	.byte	0x5
	.byte	0xef
	.long	0x196
	.uleb128 0xa
	.ascii "_argc\0"
	.byte	0x6
	.byte	0x63
	.long	0xe9
	.uleb128 0xa
	.ascii "_argv\0"
	.byte	0x6
	.byte	0x64
	.long	0x1c7
	.uleb128 0x7
	.byte	0x4
	.long	0x184
	.uleb128 0xa
	.ascii "__mb_cur_max\0"
	.byte	0x6
	.byte	0x8e
	.long	0xe9
	.uleb128 0xa
	.ascii "_sys_nerr\0"
	.byte	0x6
	.byte	0xca
	.long	0xe9
	.uleb128 0x8
	.long	0x184
	.long	0x1fd
	.uleb128 0x9
	.byte	0
	.uleb128 0xa
	.ascii "_sys_errlist\0"
	.byte	0x6
	.byte	0xe3
	.long	0x1f2
	.uleb128 0xa
	.ascii "_osver\0"
	.byte	0x6
	.byte	0xfa
	.long	0x75
	.uleb128 0xa
	.ascii "_winver\0"
	.byte	0x6
	.byte	0xfb
	.long	0x75
	.uleb128 0xa
	.ascii "_winmajor\0"
	.byte	0x6
	.byte	0xfc
	.long	0x75
	.uleb128 0xa
	.ascii "_winminor\0"
	.byte	0x6
	.byte	0xfd
	.long	0x75
	.uleb128 0xb
	.ascii "_fmode\0"
	.byte	0x6
	.word	0x145
	.long	0xe9
	.uleb128 0x2
	.ascii "DWORD\0"
	.byte	0x7
	.byte	0xf5
	.long	0x271
	.uleb128 0x4
	.long	0x25f
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "long unsigned int\0"
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.ascii "unsigned char\0"
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.ascii "float\0"
	.uleb128 0x7
	.byte	0x4
	.long	0x2a6
	.uleb128 0xc
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.ascii "short int\0"
	.uleb128 0xd
	.byte	0x4
	.uleb128 0x2
	.ascii "LPVOID\0"
	.byte	0x8
	.byte	0x64
	.long	0x2b4
	.uleb128 0x2
	.ascii "HANDLE\0"
	.byte	0x8
	.byte	0xa2
	.long	0x2b4
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.ascii "long long unsigned int\0"
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.ascii "signed char\0"
	.uleb128 0xe
	.ascii "_GUID\0"
	.byte	0x10
	.byte	0x8
	.word	0x704
	.long	0x347
	.uleb128 0xf
	.ascii "Data1\0"
	.byte	0x8
	.word	0x705
	.long	0x271
	.byte	0
	.uleb128 0xf
	.ascii "Data2\0"
	.byte	0x8
	.word	0x706
	.long	0x85
	.byte	0x4
	.uleb128 0xf
	.ascii "Data3\0"
	.byte	0x8
	.word	0x707
	.long	0x85
	.byte	0x6
	.uleb128 0xf
	.ascii "Data4\0"
	.byte	0x8
	.word	0x708
	.long	0x347
	.byte	0x8
	.byte	0
	.uleb128 0x8
	.long	0x286
	.long	0x357
	.uleb128 0x10
	.long	0x357
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.ascii "sizetype\0"
	.uleb128 0x11
	.ascii "GUID\0"
	.byte	0x8
	.word	0x709
	.long	0x2fb
	.uleb128 0x4
	.long	0x363
	.uleb128 0x2
	.ascii "IID\0"
	.byte	0x9
	.byte	0x81
	.long	0x363
	.uleb128 0x4
	.long	0x375
	.uleb128 0x2
	.ascii "CLSID\0"
	.byte	0x9
	.byte	0x83
	.long	0x363
	.uleb128 0x4
	.long	0x385
	.uleb128 0x2
	.ascii "FMTID\0"
	.byte	0x9
	.byte	0x88
	.long	0x363
	.uleb128 0x4
	.long	0x397
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.ascii "double\0"
	.uleb128 0xa
	.ascii "IID_IUnknown\0"
	.byte	0xa
	.byte	0x13
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IClassFactory\0"
	.byte	0xa
	.byte	0x14
	.long	0x380
	.uleb128 0xb
	.ascii "FMTID_SummaryInformation\0"
	.byte	0xb
	.word	0x1c2
	.long	0x3a4
	.uleb128 0xb
	.ascii "FMTID_DocSummaryInformation\0"
	.byte	0xb
	.word	0x1c3
	.long	0x3a4
	.uleb128 0xb
	.ascii "FMTID_UserDefinedProperties\0"
	.byte	0xb
	.word	0x1c4
	.long	0x3a4
	.uleb128 0xb
	.ascii "IID_ISequentialStream\0"
	.byte	0xb
	.word	0x1d0
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IStream\0"
	.byte	0xb
	.word	0x1dc
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IMarshal\0"
	.byte	0xb
	.word	0x1f1
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IStdMarshalInfo\0"
	.byte	0xb
	.word	0x201
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IMalloc\0"
	.byte	0xb
	.word	0x20c
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IMallocSpy\0"
	.byte	0xb
	.word	0x21c
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IMessageFilter\0"
	.byte	0xb
	.word	0x232
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPersist\0"
	.byte	0xb
	.word	0x23f
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPersistStream\0"
	.byte	0xb
	.word	0x24a
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IRunningObjectTable\0"
	.byte	0xb
	.word	0x259
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IBindCtx\0"
	.byte	0xb
	.word	0x26a
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IMoniker\0"
	.byte	0xb
	.word	0x27e
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPersistStorage\0"
	.byte	0xb
	.word	0x29c
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPersistFile\0"
	.byte	0xb
	.word	0x2ad
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IAdviseSink\0"
	.byte	0xb
	.word	0x2bd
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IAdviseSink2\0"
	.byte	0xb
	.word	0x2cc
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IDataObject\0"
	.byte	0xb
	.word	0x2dc
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IDataAdviseHolder\0"
	.byte	0xb
	.word	0x2ef
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IStorage\0"
	.byte	0xb
	.word	0x2fd
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IRootStorage\0"
	.byte	0xb
	.word	0x316
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IRpcChannelBuffer\0"
	.byte	0xb
	.word	0x321
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IRpcProxyBuffer\0"
	.byte	0xb
	.word	0x330
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IRpcStubBuffer\0"
	.byte	0xb
	.word	0x33d
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPSFactoryBuffer\0"
	.byte	0xb
	.word	0x34e
	.long	0x380
	.uleb128 0xb
	.ascii "IID_ILockBytes\0"
	.byte	0xb
	.word	0x35b
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IExternalConnection\0"
	.byte	0xb
	.word	0x36c
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IRunnableObject\0"
	.byte	0xb
	.word	0x378
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IROTData\0"
	.byte	0xb
	.word	0x387
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IChannelHook\0"
	.byte	0xb
	.word	0x392
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPropertyStorage\0"
	.byte	0xb
	.word	0x3a2
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IPropertySetStorage\0"
	.byte	0xb
	.word	0x3b8
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IClientSecurity\0"
	.byte	0xb
	.word	0x3c6
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IServerSecurity\0"
	.byte	0xb
	.word	0x3d3
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IClassActivator\0"
	.byte	0xb
	.word	0x3e1
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IFillLockBytes\0"
	.byte	0xb
	.word	0x3ec
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IProgressNotify\0"
	.byte	0xb
	.word	0x3fa
	.long	0x380
	.uleb128 0xb
	.ascii "IID_ILayoutStorage\0"
	.byte	0xb
	.word	0x405
	.long	0x380
	.uleb128 0xb
	.ascii "IID_IGlobalInterfaceTable\0"
	.byte	0xb
	.word	0x413
	.long	0x380
	.uleb128 0xa
	.ascii "GUID_NULL\0"
	.byte	0xc
	.byte	0xa
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IRpcChannel\0"
	.byte	0xc
	.byte	0xb
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IRpcStub\0"
	.byte	0xc
	.byte	0xc
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IStubManager\0"
	.byte	0xc
	.byte	0xd
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IRpcProxy\0"
	.byte	0xc
	.byte	0xe
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IProxyManager\0"
	.byte	0xc
	.byte	0xf
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IPSFactory\0"
	.byte	0xc
	.byte	0x10
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IInternalMoniker\0"
	.byte	0xc
	.byte	0x11
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IDfReserved1\0"
	.byte	0xc
	.byte	0x12
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IDfReserved2\0"
	.byte	0xc
	.byte	0x13
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IDfReserved3\0"
	.byte	0xc
	.byte	0x14
	.long	0x380
	.uleb128 0xa
	.ascii "CLSID_StdMarshal\0"
	.byte	0xc
	.byte	0x15
	.long	0x392
	.uleb128 0xa
	.ascii "IID_IStub\0"
	.byte	0xc
	.byte	0x16
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IProxy\0"
	.byte	0xc
	.byte	0x17
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IEnumGeneric\0"
	.byte	0xc
	.byte	0x18
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IEnumHolder\0"
	.byte	0xc
	.byte	0x19
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IEnumCallback\0"
	.byte	0xc
	.byte	0x1a
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IOleManager\0"
	.byte	0xc
	.byte	0x1b
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IOlePresObj\0"
	.byte	0xc
	.byte	0x1c
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IDebug\0"
	.byte	0xc
	.byte	0x1d
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IDebugStream\0"
	.byte	0xc
	.byte	0x1e
	.long	0x380
	.uleb128 0xa
	.ascii "CLSID_PSGenObject\0"
	.byte	0xc
	.byte	0x1f
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSClientSite\0"
	.byte	0xc
	.byte	0x20
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSClassObject\0"
	.byte	0xc
	.byte	0x21
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSInPlaceActive\0"
	.byte	0xc
	.byte	0x22
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSInPlaceFrame\0"
	.byte	0xc
	.byte	0x23
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSDragDrop\0"
	.byte	0xc
	.byte	0x24
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSBindCtx\0"
	.byte	0xc
	.byte	0x25
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_PSEnumerators\0"
	.byte	0xc
	.byte	0x26
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_StaticMetafile\0"
	.byte	0xc
	.byte	0x27
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_StaticDib\0"
	.byte	0xc
	.byte	0x28
	.long	0x392
	.uleb128 0xa
	.ascii "CID_CDfsVolume\0"
	.byte	0xc
	.byte	0x29
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDFormKrnl\0"
	.byte	0xc
	.byte	0x2a
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDPropertyPage\0"
	.byte	0xc
	.byte	0x2b
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDFormDialog\0"
	.byte	0xc
	.byte	0x2c
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDCommandButton\0"
	.byte	0xc
	.byte	0x2d
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDComboBox\0"
	.byte	0xc
	.byte	0x2e
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDTextBox\0"
	.byte	0xc
	.byte	0x2f
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDCheckBox\0"
	.byte	0xc
	.byte	0x30
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDLabel\0"
	.byte	0xc
	.byte	0x31
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDOptionButton\0"
	.byte	0xc
	.byte	0x32
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDListBox\0"
	.byte	0xc
	.byte	0x33
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDScrollBar\0"
	.byte	0xc
	.byte	0x34
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDGroupBox\0"
	.byte	0xc
	.byte	0x35
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDGeneralPropertyPage\0"
	.byte	0xc
	.byte	0x36
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDGenericPropertyPage\0"
	.byte	0xc
	.byte	0x37
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDFontPropertyPage\0"
	.byte	0xc
	.byte	0x38
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDColorPropertyPage\0"
	.byte	0xc
	.byte	0x39
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDLabelPropertyPage\0"
	.byte	0xc
	.byte	0x3a
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDCheckBoxPropertyPage\0"
	.byte	0xc
	.byte	0x3b
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDTextBoxPropertyPage\0"
	.byte	0xc
	.byte	0x3c
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDOptionButtonPropertyPage\0"
	.byte	0xc
	.byte	0x3d
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDListBoxPropertyPage\0"
	.byte	0xc
	.byte	0x3e
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDCommandButtonPropertyPage\0"
	.byte	0xc
	.byte	0x3f
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDComboBoxPropertyPage\0"
	.byte	0xc
	.byte	0x40
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDScrollBarPropertyPage\0"
	.byte	0xc
	.byte	0x41
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDGroupBoxPropertyPage\0"
	.byte	0xc
	.byte	0x42
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CCDXObjectPropertyPage\0"
	.byte	0xc
	.byte	0x43
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CStdPropertyFrame\0"
	.byte	0xc
	.byte	0x44
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CFormPropertyPage\0"
	.byte	0xc
	.byte	0x45
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CGridPropertyPage\0"
	.byte	0xc
	.byte	0x46
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CWSJArticlePage\0"
	.byte	0xc
	.byte	0x47
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_CSystemPage\0"
	.byte	0xc
	.byte	0x48
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_IdentityUnmarshal\0"
	.byte	0xc
	.byte	0x49
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_InProcFreeMarshaler\0"
	.byte	0xc
	.byte	0x4a
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_Picture_Metafile\0"
	.byte	0xc
	.byte	0x4b
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_Picture_EnhMetafile\0"
	.byte	0xc
	.byte	0x4c
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_Picture_Dib\0"
	.byte	0xc
	.byte	0x4d
	.long	0x392
	.uleb128 0xa
	.ascii "CLSID_StdGlobalInterfaceTable\0"
	.byte	0xc
	.byte	0x4e
	.long	0x392
	.uleb128 0xa
	.ascii "GUID_TRISTATE\0"
	.byte	0xc
	.byte	0x4f
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IDispatch\0"
	.byte	0xd
	.byte	0xb
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPropertyNotifySink\0"
	.byte	0xd
	.byte	0xc
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IClassFactory2\0"
	.byte	0xd
	.byte	0xd
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IProvideClassInfo\0"
	.byte	0xd
	.byte	0xe
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IProvideClassInfo2\0"
	.byte	0xd
	.byte	0xf
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IConnectionPointContainer\0"
	.byte	0xd
	.byte	0x10
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumConnectionPoints\0"
	.byte	0xd
	.byte	0x11
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IConnectionPoint\0"
	.byte	0xd
	.byte	0x12
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumConnections\0"
	.byte	0xd
	.byte	0x13
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleControl\0"
	.byte	0xd
	.byte	0x14
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleControlSite\0"
	.byte	0xd
	.byte	0x15
	.long	0x370
	.uleb128 0xa
	.ascii "IID_ISimpleFrameSite\0"
	.byte	0xd
	.byte	0x16
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPersistStreamInit\0"
	.byte	0xd
	.byte	0x17
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPersistMemory\0"
	.byte	0xd
	.byte	0x18
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPersistPropertyBag\0"
	.byte	0xd
	.byte	0x19
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPropertyBag\0"
	.byte	0xd
	.byte	0x1a
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IErrorLog\0"
	.byte	0xd
	.byte	0x1b
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPropertyFrame\0"
	.byte	0xd
	.byte	0x1c
	.long	0x370
	.uleb128 0xa
	.ascii "IID_ISpecifyPropertyPages\0"
	.byte	0xd
	.byte	0x1d
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPerPropertyBrowsing\0"
	.byte	0xd
	.byte	0x1e
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPropertyPageSite\0"
	.byte	0xd
	.byte	0x1f
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPropertyPage\0"
	.byte	0xd
	.byte	0x20
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPropertyPage2\0"
	.byte	0xd
	.byte	0x21
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_CFontPropPage\0"
	.byte	0xd
	.byte	0x22
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_CColorPropPage\0"
	.byte	0xd
	.byte	0x23
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_CPicturePropPage\0"
	.byte	0xd
	.byte	0x24
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_PersistPropset\0"
	.byte	0xd
	.byte	0x25
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_ConvertVBX\0"
	.byte	0xd
	.byte	0x26
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_StdFont\0"
	.byte	0xd
	.byte	0x27
	.long	0x370
	.uleb128 0xa
	.ascii "CLSID_StdPicture\0"
	.byte	0xd
	.byte	0x28
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IFont\0"
	.byte	0xd
	.byte	0x29
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IFontDisp\0"
	.byte	0xd
	.byte	0x2a
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPicture\0"
	.byte	0xd
	.byte	0x2b
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IPictureDisp\0"
	.byte	0xd
	.byte	0x2c
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_HIMETRIC\0"
	.byte	0xd
	.byte	0x2d
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_COLOR\0"
	.byte	0xd
	.byte	0x2e
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_XPOSPIXEL\0"
	.byte	0xd
	.byte	0x2f
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_YPOSPIXEL\0"
	.byte	0xd
	.byte	0x30
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_XSIZEPIXEL\0"
	.byte	0xd
	.byte	0x31
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_YSIZEPIXEL\0"
	.byte	0xd
	.byte	0x32
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_XPOS\0"
	.byte	0xd
	.byte	0x33
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_YPOS\0"
	.byte	0xd
	.byte	0x34
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_XSIZE\0"
	.byte	0xd
	.byte	0x35
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_YSIZE\0"
	.byte	0xd
	.byte	0x36
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_OPTIONVALUEEXCLUSIVE\0"
	.byte	0xd
	.byte	0x38
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_CHECKVALUEEXCLUSIVE\0"
	.byte	0xd
	.byte	0x39
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_FONTNAME\0"
	.byte	0xd
	.byte	0x3a
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_FONTSIZE\0"
	.byte	0xd
	.byte	0x3b
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_FONTBOLD\0"
	.byte	0xd
	.byte	0x3c
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_FONTITALIC\0"
	.byte	0xd
	.byte	0x3d
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_FONTUNDERSCORE\0"
	.byte	0xd
	.byte	0x3e
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_FONTSTRIKETHROUGH\0"
	.byte	0xd
	.byte	0x3f
	.long	0x370
	.uleb128 0xa
	.ascii "GUID_HANDLE\0"
	.byte	0xd
	.byte	0x40
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumUnknown\0"
	.byte	0xd
	.byte	0x41
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumString\0"
	.byte	0xd
	.byte	0x42
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumMoniker\0"
	.byte	0xd
	.byte	0x43
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumFORMATETC\0"
	.byte	0xd
	.byte	0x44
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumOLEVERB\0"
	.byte	0xd
	.byte	0x45
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumSTATDATA\0"
	.byte	0xd
	.byte	0x46
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IEnumSTATSTG\0"
	.byte	0xd
	.byte	0x47
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IViewObject\0"
	.byte	0xd
	.byte	0x4f
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleAdviseHolder\0"
	.byte	0xd
	.byte	0x53
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleObject\0"
	.byte	0xd
	.byte	0x54
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleInPlaceObject\0"
	.byte	0xd
	.byte	0x55
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleWindow\0"
	.byte	0xd
	.byte	0x56
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleInPlaceUIWindow\0"
	.byte	0xd
	.byte	0x57
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleInPlaceFrame\0"
	.byte	0xd
	.byte	0x58
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleInPlaceActiveObject\0"
	.byte	0xd
	.byte	0x59
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleClientSite\0"
	.byte	0xd
	.byte	0x5a
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleInPlaceSite\0"
	.byte	0xd
	.byte	0x5b
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IParseDisplayName\0"
	.byte	0xd
	.byte	0x5c
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleContainer\0"
	.byte	0xd
	.byte	0x5d
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleItemContainer\0"
	.byte	0xd
	.byte	0x5e
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleLink\0"
	.byte	0xd
	.byte	0x5f
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleCache\0"
	.byte	0xd
	.byte	0x60
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IDropSource\0"
	.byte	0xd
	.byte	0x63
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IDropTarget\0"
	.byte	0xd
	.byte	0x64
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IViewObject2\0"
	.byte	0xd
	.byte	0x69
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleCache2\0"
	.byte	0xd
	.byte	0x6a
	.long	0x370
	.uleb128 0xa
	.ascii "IID_IOleCacheControl\0"
	.byte	0xd
	.byte	0x6b
	.long	0x370
	.uleb128 0xa
	.ascii "IID_ITypeLib\0"
	.byte	0xe
	.byte	0x52
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ITypeLib2\0"
	.byte	0xe
	.byte	0x53
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ICreateTypeInfo\0"
	.byte	0xe
	.byte	0x54
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ICreateTypeInfo2\0"
	.byte	0xe
	.byte	0x55
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ICreateTypeLib\0"
	.byte	0xe
	.byte	0x56
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ICreateTypeLib2\0"
	.byte	0xe
	.byte	0x57
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ITypeInfo\0"
	.byte	0xe
	.byte	0x58
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ITypeInfo2\0"
	.byte	0xe
	.byte	0x59
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IErrorInfo\0"
	.byte	0xe
	.byte	0x5a
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IEnumVARIANT\0"
	.byte	0xe
	.byte	0x5c
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ICreateErrorInfo\0"
	.byte	0xe
	.byte	0x5d
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ISupportErrorInfo\0"
	.byte	0xe
	.byte	0x5e
	.long	0x380
	.uleb128 0xa
	.ascii "IID_IRecordInfo\0"
	.byte	0xe
	.byte	0x5f
	.long	0x380
	.uleb128 0xa
	.ascii "IID_ITypeMarshal\0"
	.byte	0xe
	.byte	0x60
	.long	0x380
	.uleb128 0x12
	.ascii "main\0"
	.byte	0x2
	.byte	0x6
	.long	0xe9
	.long	LFB35
	.long	LFE35-LFB35
	.uleb128 0x1
	.byte	0x9c
	.long	0x1956
	.uleb128 0x13
	.ascii "ptr\0"
	.byte	0x2
	.byte	0x7
	.long	0x1956
	.uleb128 0x3
	.byte	0x74
	.sleb128 1052
	.uleb128 0x13
	.ascii "buffer\0"
	.byte	0x2
	.byte	0x9
	.long	0x195c
	.uleb128 0x2
	.byte	0x74
	.sleb128 44
	.uleb128 0x14
	.long	LBB2
	.long	LBE2-LBB2
	.uleb128 0x13
	.ascii "buf\0"
	.byte	0x2
	.byte	0x10
	.long	0x2b4
	.uleb128 0x3
	.byte	0x74
	.sleb128 1048
	.uleb128 0x13
	.ascii "i\0"
	.byte	0x2
	.byte	0x17
	.long	0xe9
	.uleb128 0x3
	.byte	0x74
	.sleb128 1044
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x18a
	.uleb128 0x8
	.long	0xf5
	.long	0x196d
	.uleb128 0x15
	.long	0x357
	.word	0x3e7
	.byte	0
	.uleb128 0x16
	.ascii "munlock\0"
	.byte	0x1
	.byte	0xac
	.long	0xe9
	.long	LFB34
	.long	LFE34-LFB34
	.uleb128 0x1
	.byte	0x9c
	.long	0x19a7
	.uleb128 0x17
	.secrel32	LASF0
	.byte	0x1
	.byte	0xac
	.long	0x2a0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "len\0"
	.byte	0x1
	.byte	0xac
	.long	0x67
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x16
	.ascii "mlock\0"
	.byte	0x1
	.byte	0xa2
	.long	0xe9
	.long	LFB33
	.long	LFE33-LFB33
	.uleb128 0x1
	.byte	0x9c
	.long	0x19df
	.uleb128 0x17
	.secrel32	LASF0
	.byte	0x1
	.byte	0xa2
	.long	0x2a0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "len\0"
	.byte	0x1
	.byte	0xa2
	.long	0x67
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x16
	.ascii "msync\0"
	.byte	0x1
	.byte	0x98
	.long	0xe9
	.long	LFB32
	.long	LFE32-LFB32
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a27
	.uleb128 0x17
	.secrel32	LASF0
	.byte	0x1
	.byte	0x98
	.long	0x2b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "len\0"
	.byte	0x1
	.byte	0x98
	.long	0x67
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x18
	.ascii "flags\0"
	.byte	0x1
	.byte	0x98
	.long	0xe9
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0x16
	.ascii "_mprotect\0"
	.byte	0x1
	.byte	0x8b
	.long	0xe9
	.long	LFB31
	.long	LFE31-LFB31
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a9c
	.uleb128 0x17
	.secrel32	LASF0
	.byte	0x1
	.byte	0x8b
	.long	0x2b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "len\0"
	.byte	0x1
	.byte	0x8b
	.long	0x67
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x18
	.ascii "prot\0"
	.byte	0x1
	.byte	0x8b
	.long	0xe9
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x13
	.ascii "newProtect\0"
	.byte	0x1
	.byte	0x8d
	.long	0x25f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x13
	.ascii "oldProtect\0"
	.byte	0x1
	.byte	0x8e
	.long	0x25f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x16
	.ascii "munmap\0"
	.byte	0x1
	.byte	0x81
	.long	0xe9
	.long	LFB30
	.long	LFE30-LFB30
	.uleb128 0x1
	.byte	0x9c
	.long	0x1ad5
	.uleb128 0x17
	.secrel32	LASF0
	.byte	0x1
	.byte	0x81
	.long	0x2b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "len\0"
	.byte	0x1
	.byte	0x81
	.long	0x67
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x16
	.ascii "mmap\0"
	.byte	0x1
	.byte	0x3a
	.long	0x2b4
	.long	LFB29
	.long	LFE29-LFB29
	.uleb128 0x1
	.byte	0x9c
	.long	0x1c07
	.uleb128 0x17
	.secrel32	LASF0
	.byte	0x1
	.byte	0x3a
	.long	0x2b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "len\0"
	.byte	0x1
	.byte	0x3a
	.long	0x67
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x18
	.ascii "prot\0"
	.byte	0x1
	.byte	0x3a
	.long	0xe9
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x18
	.ascii "flags\0"
	.byte	0x1
	.byte	0x3a
	.long	0xe9
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x18
	.ascii "fildes\0"
	.byte	0x1
	.byte	0x3a
	.long	0xe9
	.uleb128 0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x18
	.ascii "off\0"
	.byte	0x1
	.byte	0x3a
	.long	0xc6
	.uleb128 0x2
	.byte	0x91
	.sleb128 20
	.uleb128 0x13
	.ascii "fm\0"
	.byte	0x1
	.byte	0x3c
	.long	0x2c4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x13
	.ascii "h\0"
	.byte	0x1
	.byte	0x3c
	.long	0x2c4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x13
	.ascii "map\0"
	.byte	0x1
	.byte	0x3e
	.long	0x2b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x13
	.ascii "dwFileOffsetLow\0"
	.byte	0x1
	.byte	0x45
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x13
	.ascii "dwFileOffsetHigh\0"
	.byte	0x1
	.byte	0x47
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x13
	.ascii "protect\0"
	.byte	0x1
	.byte	0x49
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x19
	.secrel32	LASF1
	.byte	0x1
	.byte	0x4a
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x13
	.ascii "maxSize\0"
	.byte	0x1
	.byte	0x4c
	.long	0xd3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x13
	.ascii "dwMaxSizeLow\0"
	.byte	0x1
	.byte	0x4e
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x13
	.ascii "dwMaxSizeHigh\0"
	.byte	0x1
	.byte	0x50
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x1a
	.ascii "__map_mmap_prot_file\0"
	.byte	0x1
	.byte	0x29
	.long	0x25f
	.long	LFB28
	.long	LFE28-LFB28
	.uleb128 0x1
	.byte	0x9c
	.long	0x1c4f
	.uleb128 0x18
	.ascii "prot\0"
	.byte	0x1
	.byte	0x29
	.long	0xf0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x19
	.secrel32	LASF1
	.byte	0x1
	.byte	0x2b
	.long	0x25f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x1a
	.ascii "__map_mmap_prot_page\0"
	.byte	0x1
	.byte	0x14
	.long	0x25f
	.long	LFB27
	.long	LFE27-LFB27
	.uleb128 0x1
	.byte	0x9c
	.long	0x1c9b
	.uleb128 0x18
	.ascii "prot\0"
	.byte	0x1
	.byte	0x14
	.long	0xf0
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.ascii "protect\0"
	.byte	0x1
	.byte	0x16
	.long	0x25f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x1b
	.ascii "__map_mman_error\0"
	.byte	0x1
	.byte	0xc
	.long	0xe9
	.long	LFB26
	.long	LFE26-LFB26
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x18
	.ascii "err\0"
	.byte	0x1
	.byte	0xc
	.long	0x26c
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x18
	.ascii "deferr\0"
	.byte	0x1
	.byte	0xc
	.long	0xf0
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.byte	0
	.section	.debug_abbrev,"dr"
Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"dr"
	.long	0x1c
	.word	0x2
	.secrel32	Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	Ltext0
	.long	Letext0-Ltext0
	.long	0
	.long	0
	.section	.debug_line,"dr"
Ldebug_line0:
	.section	.debug_str,"dr"
LASF1:
	.ascii "desiredAccess\0"
LASF0:
	.ascii "addr\0"
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	__errno;	.scl	2;	.type	32;	.endef
	.def	__get_osfhandle;	.scl	2;	.type	32;	.endef
	.def	_CreateFileMappingA@24;	.scl	2;	.type	32;	.endef
	.def	_GetLastError@0;	.scl	2;	.type	32;	.endef
	.def	_MapViewOfFile@20;	.scl	2;	.type	32;	.endef
	.def	_CloseHandle@4;	.scl	2;	.type	32;	.endef
	.def	_UnmapViewOfFile@4;	.scl	2;	.type	32;	.endef
	.def	_VirtualProtect@16;	.scl	2;	.type	32;	.endef
	.def	_FlushViewOfFile@8;	.scl	2;	.type	32;	.endef
	.def	_VirtualLock@8;	.scl	2;	.type	32;	.endef
	.def	_VirtualUnlock@8;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
