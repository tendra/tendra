/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>
#include <stddef.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>

#include <main/flags.h>

int redo_structfns = 0;		/* reorganise proc calls delivering
				   structures */
int redo_structparams = 0;	/* reorganise proc calls with struct
				   parameters */
int diagnose_registers = 1;	/* I have absolutely no idea what this does, but it was disabled for SCO */
int do_profile = 0;		/* put in profiling code */
int do_alloca = 1;		/* inline alloca */
int all_variables_visible = 0;	/* set vis flag for all declarations */
int promote_pars = 1;
int load_ptr_pars = 0;		/* Inline pointer parameters */
int trap_on_nil_contents = 1;	/* Let common code detect nil access */

int double_align = 32;		/* alignment for 64 bit flpt */
int stack_align = 32;		/* minimum alignment for stack */
int param_align = 32;		/* minimum alignment for parameters */
int needs_debug_align = 0;	/* alignment for dwarf2 */

int separate_units = 0;		/* translate units separately */

int writable_strings = 0;	/* string are writable */

int use_long_double = 1;
int target_dbl_maxexp = 16384;	/* maximum double exponent allowed */
int round_after_flop = 0;	/* round after each floating point
				   operation */
int strict_fl_div = 1;		/* do not replace divisions by
				   multiplication by the inverse */

int PIC_code = 0;		/* produce PIC code */
int keep_PIC_vars = 0;
int do_prom = 0;		/* produce PROM code (avoiding .data) */
int dyn_init = 0;		/* produce calls for dynamic initialisation */
int do_comment = 0;		/* produce comments in generated assembly */

#ifdef TDF_DIAG4
int diag_visible = 0;		/* additional visibility if doing diagnostics */
int extra_diags = 1;		/* option for extended diagnostics */
#endif

#ifdef DWARF2
int dump_abbrev = 1;
#endif

enum has     has;
enum optim   optim;
enum check   check;
enum builtin builtin;

enum endian    endian;
enum assembler assembler;
enum format    format;
enum diag      diag;
enum cconv     cconv;
enum abi       abi;

enum has
flags_has(enum has o, const char *s)
{
	const char *p;
	int v;

	v = 1;

	for (p = s; *p != '\0'; p++) {
		enum has e;

		switch (*p) {
		case '+': v = 1; continue;
		case '-': v = 0; continue;

		case 'a': e = ~0U;                break;
		case 'o': e = HAS_BYTEOPS;        break;
		case 'r': e = HAS_BYTEREGS;       break;
		case 'n': e = HAS_NEGSHIFT;       break;
		case 't': e = HAS_ROTATE;         break;
		case 'm': e = HAS_MAXMIN;         break;
		case 'c': e = HAS_CONDASSIGN;     break;
		case 'd': e = HAS_DIV0;           break;
		case 's': e = HAS_SETCC;          break;
		case 'i': e = HAS_COMPLEX;        break;
		case 'q': e = HAS_64_BIT;         break;

		default:
			error(ERROR_WARNING, "Unrecognised has flag %c. "
				"Valid flags are: [orntmcdsiq] and [a] for all.",
				*p);
			continue;
		}

		if (v) {
			o |=  e;
		} else {
			o &= ~e;
		}
	}

	return o;
}

enum optim
flags_optim(enum optim o, const char *s)
{
	const char *p;
	int v;

	v = 1;

	for (p = s; *p != '\0'; p++) {
		enum optim e;

		switch (*p) {
		case '+': v = 1; continue;
		case '-': v = 0; continue;

		case 'a': e = ~0U;                break;
		case 'c': e = OPTIM_LOOPCONSTS;   break;
		case 'd': e = OPTIM_DUMP;         break;
		case 'e': e = OPTIM_INLINE_EXPS;  break;
		case 'f': e = OPTIM_FORALLS;      break;
		case 'g': e = OPTIM_CASE;         break;
		case 'h': e = OPTIM_PEEPHOLE;     break;
		case 'i': e = OPTIM_INLINE_PROCS; break;
		case 'j': e = OPTIM_JUMPS;        break;
		case 'u': e = OPTIM_UNROLL;       break;
		case 'r': e = OPTIM_TAIL;         break;
		case 's': e = OPTIM_SHORTEN_OPS;  break;
		case 't': e = OPTIM_TEMPDEC;      break;
		case 'o': e = OPTIM_ZEROOFFSETS;  break;
		case 'p': e = OPTIM_SUBSTPARAMS;  break;
		case 'q': e = OPTIM_COMPOUNDS;    break;
		case 'y': e = OPTIM_UNPAD_APPLY;  break;

		default:
			error(ERROR_WARNING, "Unrecognised optimisation flag %c. "
				"Valid flags are: [cdefghijurstopqy] and [a] for all.",
				*p);
			continue;
		}

		if (v) {
			o |=  e;
		} else {
			o &= ~e;
		}
	}

	return o;
}

enum check
flags_check(enum check o, const char *s)
{
	const char *p;
	int v;

	v = 1;

	for (p = s; *p != '\0'; p++) {
		enum check e;

		switch (*p) {
		case '+': v = 1; continue;
		case '-': v = 0; continue;

		case 'a': e = ~0U;                 break;
		case 's': e = CHECK_SHAPE;         break;
		case 'e': e = CHECK_EXTRA;         break;
		case 'f': e = CHECK_FLPT_OVERFLOW; break;

		default:
			error(ERROR_WARNING, "Unrecognised check flag %c. "
				"Valid flags are: [sef] and [a] for all.",
				*p);
			continue;
		}

		if (v) {
			o |=  e;
		} else {
			o &= ~e;
		}
	}

	return o;
}

enum builtin
flags_builtin(enum builtin o, const char *s)
{
	const char *p;
	int v;

	v = 1;

	for (p = s; *p != '\0'; p++) {
		enum builtin e;

		switch (*p) {
		case '+': v = 1; continue;
		case '-': v = 0; continue;

		case 'a': e = ~0U;             break;
		case 'j': e = BUILTIN_LONGJMP; break;
		case 'p': e = BUILTIN_PROMOTE; break;
		case 'v': e = BUILTIN_VARARG;  break;
		case 'c': e = BUILTIN_ALLOCA;  break;
		case 'f': e = BUILTIN_FLOAT;   break;
		case 'g': e = BUILTIN_DIAG;    break;
		case 'l': e = BUILTIN_API;     break;
		case 'm': e = BUILTIN_ASM;     break;
		case 't': e = BUILTIN_DEBUG;   break;

		default:
			error(ERROR_WARNING, "Unrecognised builtin flag %c. "
				"Valid flags are: [sjcglmt] and [a] for all.",
				*p);
			continue;
		}

		if (v) {
			o |=  e;
		} else {
			o &= ~e;
		}
	}

	return o;
}

enum endian
switch_endian(const char *s, unsigned permitted)
{
	enum endian o;

	if (strlen(s) > 1) {
		error(ERROR_FATAL, "Unrecognised endian switch %s. "
			"Valid switches are: [bl].", s);
		return -1;
	}

	switch (*s) {
	case 'b': o = ENDIAN_BIG;    break;
	case 'l': o = ENDIAN_LITTLE; break;

	default:
		error(ERROR_FATAL, "Unrecognised endian switch %s. "
			"Valid switches are: [bl].", s);
		return -1;
	}

	if (~permitted & o) {
		error(ERROR_FATAL, "Endian switch %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return o;
}

enum assembler
switch_assembler(const char *s, unsigned permitted)
{
	size_t i;
	enum assembler o;

	struct {
		const char *name;
		enum assembler assembler;
	} a[] = {
		{ "gas",    ASM_GAS    },
		{ "sun",    ASM_SUN    },
		{ "ibm",    ASM_IBM    },
		{ "sgi",    ASM_SGI    },
		{ "ultrix", ASM_ULTRIX },
		{ "osf1",   ASM_OSF1   },
		{ "hp",     ASM_HP     }
	};

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, s)) {
			o = a[i].assembler;
			break;
		}
	}

	if (i >= sizeof a / sizeof *a) {
		error(ERROR_FATAL, "Unrecognised assembler dialect %s.", s);
		return -1;
	}

	if (~permitted & o) {
		error(ERROR_FATAL, "Assembler dialect %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return o;
}

enum format
switch_format(const char *s, unsigned permitted)
{
	size_t i;
	enum format o;

	struct {
		const char *name;
		enum format format;
	} a[] = {
		{ "aout",  FORMAT_AOUT  },
		{ "elf",   FORMAT_ELF   },
		{ "xcoff", FORMAT_XCOFF },
		{ "som",   FORMAT_SOM   },
		{ "macho", FORMAT_MACHO }
	};

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, s)) {
			o = a[i].format;
			break;
		}
	}

	if (i >= sizeof a / sizeof *a) {
		error(ERROR_FATAL, "Unrecognised executable format %s.", s);
		return -1;
	}

	if (~permitted & o) {
		error(ERROR_FATAL, "Executable format %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return o;
}

enum diag
switch_diag(const char *s, unsigned permitted)
{
	size_t i;
	enum diag o;

	struct {
		const char *name;
		enum diag diag;
	} a[] = {
		{ "none",    DIAG_NONE    },
		{ "stabs",   DIAG_STABS   },
		{ "stabx",   DIAG_STABX   },
		{ "xdb_old", DIAG_XDB_OLD },
		{ "xdb_new", DIAG_XDB_NEW },
		{ "dwarf",   DIAG_DWARF   },
		{ "dwarf2",  DIAG_DWARF2  },
		{ "gdb",     DIAG_GDB     }, /* TODO: name per its specific format */
		{ "xdb",     DIAG_XDB     }, /* TODO: name per its specific format */
		{ "cv",      DIAG_CV      }
	};

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, s)) {
			o = a[i].diag;
			break;
		}
	}

	if (i >= sizeof a / sizeof *a) {
		error(ERROR_FATAL, "Unrecognised diagnostic format %s.", s);
		return -1;
	}

	if (~permitted & o) {
		error(ERROR_FATAL, "Diagnostic format %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return o;
}

enum cconv
switch_cconv(const char *s, unsigned permitted)
{
	size_t i;
	enum cconv o;

	struct {
		const char *name;
		enum cconv cconv;
	} a[] = {
		{ "hp",    CCONV_HP    }, /* TODO: name for HPUX on m68k */
		{ "gcc",   CCONV_GCC   }, /* TODO: name for gcc for NeXT on m68k */
		{ "sun",   CCONV_SUN   }, /* TODO: name for Sun CC on m68k */
		{ "alpha", CCONV_ALPHA },
		{ "hppa",  CCONV_HPPA  },
		{ "o32",   CCONV_O32   },
		{ "xlc",   CCONV_XLC   }, /* TODO: name for 32-bit POWER */
		{ "sparc", CCONV_SPARC },
		{ "aout",  CCONV_AOUT  }  /* TODO: probably the wrong name */
	};

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, s)) {
			o = a[i].cconv;
			break;
		}
	}

	if (i >= sizeof a / sizeof *a) {
		error(ERROR_FATAL, "Unrecognised calling convention %s.", s);
		return -1;
	}

	if (~permitted & o) {
		error(ERROR_FATAL, "Calling convention %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return o;
}

enum abi
switch_abi(const char *s, unsigned permitted)
{
	size_t i;
	enum abi o;

	struct {
		const char *name;
		enum abi abi;
	} a[] = {
		/* TODO: most of these are not real ABI names */
		{ "hpux",    ABI_HPUX    },
		{ "next",    ABI_NEXT    },
		{ "sunos",   ABI_SUNOS   },
		{ "sco",     ABI_SCO     },
		{ "svr4",    ABI_SVR4    },
		{ "svsv",    ABI_SYSV    },
		{ "linux",   ABI_LINUX   },
		{ "solaris", ABI_SOLARIS },
		{ "osf1",    ABI_OSF1    },
		{ "icbs",    ABI_IBCS    },
		{ "mips",    ABI_MIPS    },
		{ "power",   ABI_POWER   }
	};

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, s)) {
			o = a[i].abi;
			break;
		}
	}

	if (i >= sizeof a / sizeof *a) {
		error(ERROR_FATAL, "Unrecognised ABI %s.", s);
		return -1;
	}

	if (~permitted & o) {
		error(ERROR_FATAL, "Calling convention %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return o;
}

