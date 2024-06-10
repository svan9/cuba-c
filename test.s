	.file	"test.c"
	.intel_syntax noprefix
 # GNU C11 (MinGW.org GCC-6.3.0-1) version 6.3.0 (mingw32)
 #	compiled by GNU C version 6.3.0, GMP version 6.1.2, MPFR version 3.1.5, MPC version 1.0.3, isl version 0.15
 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: 
 # -iprefix e:\progs\libs\mingw\bin\../lib/gcc/mingw32/6.3.0/ test.c
 # -masm=intel -mtune=generic -march=i586 -O3 -fverbose-asm
 # options enabled:  -faggressive-loop-optimizations -falign-labels
 # -fasynchronous-unwind-tables -fauto-inc-dec -fbranch-count-reg
 # -fcaller-saves -fchkp-check-incomplete-type -fchkp-check-read
 # -fchkp-check-write -fchkp-instrument-calls -fchkp-narrow-bounds
 # -fchkp-optimize -fchkp-store-bounds -fchkp-use-static-bounds
 # -fchkp-use-static-const-bounds -fchkp-use-wrappers
 # -fcombine-stack-adjustments -fcommon -fcompare-elim -fcprop-registers
 # -fcrossjumping -fcse-follow-jumps -fdefer-pop
 # -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
 # -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-types
 # -fexpensive-optimizations -fforward-propagate -ffunction-cse -fgcse
 # -fgcse-after-reload -fgcse-lm -fgnu-runtime -fgnu-unique
 # -fguess-branch-probability -fhoist-adjacent-loads -fident
 # -fif-conversion -fif-conversion2 -findirect-inlining -finline
 # -finline-atomics -finline-functions -finline-functions-called-once
 # -finline-small-functions -fipa-cp -fipa-cp-alignment -fipa-cp-clone
 # -fipa-icf -fipa-icf-functions -fipa-icf-variables -fipa-profile
 # -fipa-pure-const -fipa-ra -fipa-reference -fipa-sra -fira-hoist-pressure
 # -fira-share-save-slots -fira-share-spill-slots
 # -fisolate-erroneous-paths-dereference -fivopts -fkeep-inline-dllexport
 # -fkeep-static-consts -fleading-underscore -flifetime-dse -flra-remat
 # -flto-odr-type-merging -fmath-errno -fmerge-constants
 # -fmerge-debug-strings -fmove-loop-invariants -fomit-frame-pointer
 # -foptimize-sibling-calls -foptimize-strlen -fpartial-inlining -fpeephole
 # -fpeephole2 -fplt -fpredictive-commoning -fprefetch-loop-arrays -free
 # -freg-struct-return -freorder-blocks -freorder-functions
 # -frerun-cse-after-loop -fsched-critical-path-heuristic
 # -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
 # -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
 # -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
 # -fschedule-insns2 -fsemantic-interposition -fset-stack-executable
 # -fshow-column -fshrink-wrap -fsigned-zeros -fsplit-ivs-in-unroller
 # -fsplit-paths -fsplit-wide-types -fssa-backprop -fssa-phiopt
 # -fstdarg-opt -fstrict-aliasing -fstrict-overflow
 # -fstrict-volatile-bitfields -fsync-libcalls -fthread-jumps
 # -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
 # -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
 # -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
 # -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-distribute-patterns
 # -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
 # -ftree-loop-optimize -ftree-loop-vectorize -ftree-parallelize-loops=
 # -ftree-partial-pre -ftree-phiprop -ftree-pre -ftree-pta -ftree-reassoc
 # -ftree-scev-cprop -ftree-sink -ftree-slp-vectorize -ftree-slsr
 # -ftree-sra -ftree-switch-conversion -ftree-tail-merge -ftree-ter
 # -ftree-vrp -funit-at-a-time -funswitch-loops -funwind-tables
 # -fverbose-asm -fzero-initialized-in-bss -m32 -m80387 -m96bit-long-double
 # -maccumulate-outgoing-args -malign-double -malign-stringops
 # -mavx256-split-unaligned-load -mavx256-split-unaligned-store
 # -mfancy-math-387 -mfp-ret-in-387 -mieee-fp -mlong-double-80
 # -mms-bitfields -mno-red-zone -mno-sse4 -mpush-args -msahf
 # -mstack-arg-probe -mstv -mvzeroupper

	.def	___main;	.scl	2;	.type	32;	.endef
	.section	.text.startup,"x"
	.p2align 4,,15
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB24:
	.cfi_startproc
	push	ebp	 #
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp	 #,
	.cfi_def_cfa_register 5
	and	esp, -16	 #,
	call	___main	 #
	xor	eax, eax	 #
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
