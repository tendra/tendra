/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef flags_key
#define flags_key

enum has {
	HAS_BYTEOPS    = 1 << 0, /* Has byte operations */
	HAS_BYTEREGS   = 1 << 1, /* Has byte registers */
	HAS_NEGSHIFT   = 1 << 2, /* Has negative shift */
	HAS_ROTATE     = 1 << 3, /* Has rotation */
	HAS_MAXMIN     = 1 << 4, /* Has max/min tags */
	HAS_CONDASSIGN = 1 << 5, /* Has condassign tag */
	HAS_DIV0       = 1 << 6, /* Has div0 and rem0 tags */
	HAS_SETCC      = 1 << 7  /* Has setcc (produces absbool tag) */
};

enum optim {
	OPTIM_UNROLL       = 1 <<  0, /* Unroll loops */
	OPTIM_INLINE_PROCS = 1 <<  1, /* Inlining of proc tokens */
	OPTIM_INLINE_EXPS  = 1 <<  2, /* Inlining of exp tokens */
	OPTIM_LOOPCONSTS   = 1 <<  3, /* Hoist constants out of loops */
	OPTIM_FORALLS      = 1 <<  4, /* Replace loop indexes by incremented pointers */
	OPTIM_DUMP         = 1 <<  5, /* Avoid register dumping */
	OPTIM_TAIL         = 1 <<  6, /* Tail recursion */
	OPTIM_PEEPHOLE     = 1 <<  7, /* Peephole substitions */
	OPTIM_CASE         = 1 <<  8, /* Perform case transforms */
	OPTIM_JUMPS        = 1 <<  9, /* Follow gotos and tests to their final destination */
	OPTIM_TEMPDEC      = 1 << 10  /* Use temporary registers for local values */
};

enum check {
	CHECK_SHAPE         = 1 << 0, /* Check shape-correctness */
	CHECK_EXTRA         = 1 << 1, /* Extra portability checks */
	CHECK_FLPT_OVERFLOW = 1 << 2  /* Constant floating point arithmetic fails installation on overflow */
};

enum builtin {
	BUILTIN_LONGJMP = 1 << 0,
	BUILTIN_PROMOTE = 1 << 1,
	BUILTIN_VARARG  = 1 << 2,
	BUILTIN_ALLOCA  = 1 << 3,
	BUILTIN_FLOAT   = 1 << 4,
	BUILTIN_DIAG    = 1 << 5,
	BUILTIN_DIV     = 1 << 6,
	BUILTIN_API     = 1 << 7,
	BUILTIN_ASM     = 1 << 8,
	BUILTIN_DEBUG   = 1 << 9
};

enum endian {
	ENDIAN_BIG    = 1 << 0,
	ENDIAN_LITTLE = 1 << 1
};

enum assembler {
	ASM_GAS    = 1 << 0,
	ASM_SUN    = 1 << 1,
	ASM_IBM    = 1 << 2,
	ASM_SGI    = 1 << 3,
	ASM_ULTRIX = 1 << 4,
	ASM_OSF1   = 1 << 5,
	ASM_HP     = 1 << 6
};

enum format {
	FORMAT_AOUT  = 1 << 0,
	FORMAT_ELF   = 1 << 1,
	FORMAT_XCOFF = 1 << 2,
	FORMAT_SOM   = 1 << 3,
	FORMAT_MACHO = 1 << 4
};

enum diag {
	DIAG_STABS   = 1 << 0,
	DIAG_STABX   = 1 << 1,
	DIAG_XDB_OLD = 1 << 2,
	DIAG_XDB_NEW = 1 << 3,
	DIAG_DWARF   = 1 << 4,
	DIAG_DWARF2  = 1 << 5
};

extern int redo_structfns;
extern int redo_structparams;
extern int diagnose;
extern int do_profile;
extern int do_alloca;
extern int double_align;
extern int stack_align;
extern int param_align;
extern int separate_units;
extern int writable_strings;
extern int PIC_code;
extern int all_variables_visible;
extern int round_after_flop;
extern int strict_fl_div;
extern int do_prom;
extern int dyn_init;

#ifdef NEWDIAGS
extern int diag_visible;
extern int extra_diags;
#endif

extern enum has     has;
extern enum optim   optim;
extern enum check   check;
extern enum builtin builtin;

extern enum endian    endian;
extern enum assembler assembler;
extern enum format    format;
extern enum diag      diag;

extern enum optim   flags_optim(const char *);
extern enum check   flags_check(const char *);
extern enum builtin flags_builtin(const char *);

extern enum endian    switch_endian(const char *, unsigned);
extern enum assembler switch_assembler(const char *, unsigned);
extern enum format    switch_format(const char *, unsigned);
extern enum diag      switch_diag(const char *, unsigned);

#endif /* flags_key */
