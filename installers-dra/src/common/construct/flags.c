/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/error.h>

#include "config.h"

#include "flags.h"

int redo_structfns = 0;		/* reorganise proc calls delivering
				   structures */
int redo_structparams = 0;	/* reorganise proc calls with struct
				   parameters */
int diagnose = 0;		/* do diagnostics */
int do_profile = 0;		/* put in profiling code */
int do_alloca = 1;		/* inline alloca */
int all_variables_visible = 0;	/* set vis flag for all declarations */

int double_align = 32;		/* alignment for 64 bit flpt */
int stack_align = 32;		/* minimum alignment for stack */
int param_align = 32;		/* minimum alignment for parameters */

int separate_units = 0;		/* translate units separately */

int writable_strings = 0;	/* string are writable */

int round_after_flop = 0;	/* round after each floating point
				   operation */
int strict_fl_div = 1;		/* do not replace divisions by
				   multiplication by the inverse */

int PIC_code = 0;		/* produce PIC code */

int do_prom = 0;		/* produce PROM code (avoiding .data) */

#ifdef NEWDIAGS
int diag_visible = 0;		/* additional visibility if doing diagnostics */
int extra_diags = 0;		/* option for extended diagnostics */
#endif

enum optim   optim;
enum check   check;
enum builtin builtin;

enum endian endian;

enum optim
flags_optim(const char *s)
{
	enum optim o;
	const char *p;

	o = 0;

	for (p = s; *p != '\0'; p++) {
		switch (*p) {
		case 'a': o = ~0U;                 continue;

		case 'c': o |= OPTIM_LOOPCONSTS;   continue;
		case 'd': o |= OPTIM_DUMP;         continue;
		case 'e': o |= OPTIM_INLINE_EXPS;  continue;
		case 'f': o |= OPTIM_FORALLS;      continue;
		case 'g': o |= OPTIM_CASE;         continue;
		case 'h': o |= OPTIM_PEEPHOLE;     continue;
		case 'i': o |= OPTIM_INLINE_PROCS; continue;
		case 'j': o |= OPTIM_JUMPS;        continue;
		case 'u': o |= OPTIM_UNROLL;       continue;
		case 'r': o |= OPTIM_TAIL;         continue;
		case 't': o |= OPTIM_TEMPDEC;      continue;

		default:
			error(ERROR_WARNING, "Unrecognised optimisation flag %c. "
				"Valid flags are: [cdefghijurt] and [a] for all.",
				*p);
		}
	}

	return o;
}

enum check
flags_check(const char *s)
{
	enum check o;
	const char *p;

	o = 0;

	for (p = s; *p != '\0'; p++) {
		switch (*p) {
		case 'a': o = ~0U;                  continue;

		case 's': o |= CHECK_SHAPE;         continue;
		case 'e': o |= CHECK_EXTRA;         continue;
		case 'f': o |= CHECK_FLPT_OVERFLOW; continue;

		default:
			error(ERROR_WARNING, "Unrecognised check flag %c. "
				"Valid flags are: [sef] and [a] for all.",
				*p);
		}
	}

	return o;
}

enum builtin
flags_builtin(const char *s)
{
	enum builtin o;
	const char *p;

	o = 0;

	for (p = s; *p != '\0'; p++) {
		switch (*p) {
		case 'a': o = ~0U;              continue;

		case 'j': o |= BUILTIN_LONGJMP; continue;
		case 'p': o |= BUILTIN_PROMOTE; continue;
		case 'v': o |= BUILTIN_VARARG;  continue;
		case 'c': o |= BUILTIN_ALLOCA;  continue;
		case 'f': o |= BUILTIN_FLOAT;   continue;
		case 'd': o |= BUILTIN_DIAG;    continue;
		case 'l': o |= BUILTIN_API;     continue;
		case 'm': o |= BUILTIN_ASM;     continue;
		case 't': o |= BUILTIN_DEBUG;   continue;

		default:
			error(ERROR_WARNING, "Unrecognised builtin flag %c. "
				"Valid flags are: [sjcdlmt] and [a] for all.",
				*p);
		}
	}

	return o;
}

enum endian
switch_endian(const char *s, unsigned permitted)
{
	enum endian o;

	if (strlen(s) > 1) {
		error(ERROR_WARNING, "Unrecognised endian switch %s. "
			"Valid switches are: [bl].", s);
		return -1;
	}

	switch (*s) {
	case 'b': o = ENDIAN_BIG;    break;
	case 'l': o = ENDIAN_LITTLE; break;
	}

	if (~permitted & o) {
		error(ERROR_WARNING, "Endian switch %s not permitted "
			"for this architecture.", s);
		return -1;
	}

	return 0;
}

