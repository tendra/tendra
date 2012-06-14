/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"

#include "output.h"

/*
 * This file is just a stopgap intermediate before all assembler dialect
 * interfaces are moved out to a central location.
 */

void asm_nprefix(void) {
#if defined(HP_ASSEMBLER)
	outc(' & ');
#else /* GAS (SUN or NEXT) */
	outc('#');
#endif
}

void asm_fprefix(void) {
#if defined(HP_ASSEMBLER)
	outs("0f");
#endif
#if defined(GAS_ASSEMBLER)
	outs("0r");
#endif
}

void asm_ind_before(void) {
#if defined(HP_ASSEMBLER)
	outc('(')
#endif
}

void asm_ind_middle(void) {
#if defined(GAS_ASSEMBLER)
	outc('@')
#endif
}

void asm_ind_after(void) {
#if defined(HP_ASSEMBLER)
	outc(')')
#endif
}

void asm_predec_before(void) {
#if defined(HP_ASSEMBLER)
	outs(" - (");
#endif
}

void asm_predec_after(void) {
#if defined(HP_ASSEMBLER)
	outc(")");
#endif
#if defined(GAS_ASSEMBLER)
	outs("@ - ");
#endif
}

void asm_postinc_before(void) {
#if defined(HP_ASSEMBLER)
	outc('(');
#endif
}

void asm_postinc_after(void) {
#if defined(HP_ASSEMBLER)
	outs(") + ");
#endif
#if defined(GAS_ASSEMBLER)
	outs("@ + ");
#endif
}

void asm_scale_before(void) {
#if defined(HP_ASSEMBLER)
	outc(',')
#endif
}

void asm_scale(void) {
#if defined(HP_ASSEMBLER)
	outs(".l*");
#endif
#if defined(GAS_ASSEMBLER)
	outs(":l:");
#endif
}

void asm_scale_1(void) {
#if defined(HP_ASSEMBLER)
	outs(".l");
#endif
#if defined(GAS_ASSEMBLER)
	outs(":l");
#endif
}

void asm_mem_before(void) {
#if defined(HP_ASSEMBLER)
	outs("([");
#endif
}

void asm_mem_second(void) {
#if defined(GAS_ASSEMBLER)
	outc('@');
#endif
}

void asm_mem_third(void) {
#if defined(HP_ASSEMBLER)
	outc(']');
#endif
#if defined(GAS_ASSEMBLER)
	outc('@');
#endif
}

void asm_mem_after(void) {
#if defined(HP_ASSEMBLER)
	outc(')');
#endif
}

void asm_bf_before(void) {
	outc('{');
}

void asm_bf_middle(void) {
	outc(':');
}

void asm_bf_after(void) {
	outc('}');
}

void asm_rpair_sep(void) {
	outc(':');
}

void asm_comment(void) {
	outc('#');
}



/*
    HP ASSEMBLER DETAILS
*/

#ifdef HP_ASSEMBLER

#define  asm_data_first			/* true */
#define  asm_nprefix			outc(' & ')
#define  asm_fprefix			outs("0f")
#define  asm_ind_before			outc('(')
#define  asm_ind_middle			/* empty */
#define  asm_ind_after			outc(')')
#define  asm_predec_before		outs(" - (")
#define  asm_predec_after		outc(')')
#define  asm_postinc_before		outc('(')
#define  asm_postinc_after		outs(") + ")
#define  asm_scale_before		outc(',')
#define  asm_scale			outs(".l*")
#define  asm_scale_1			outs(".l")
#define  asm_mem_before			outs("([")
#define  asm_mem_second			/* empty */
#define  asm_mem_third			outc(']')
#define  asm_mem_after			outc(')')
#define  asm_bf_before			outc('{')
#define  asm_bf_middle			outc(':')
#define  asm_bf_after			outc('}')
#define  asm_rpair_sep			outc(':')
#define  asm_comment			outc('#')

#define  asm_cmp_reversed		/* cmp instructions are reversed */
#define  asm_version			outs("\tversion 2")
#define  asm_version_aux		outs("\tversion 3")

#endif /* HP_ASSEMBLER */


/*
    HP DEBUGGER DETAILS
*/

#ifdef XDB_DEBUGGER
#define default_diag			DIAG_UNKNOWN
#endif /* XDB_DEBUGGER */


/*
    HP OPERATING SYSTEM INTERFACE
*/

#ifdef HP_INTERFACE

#define hp_cc_conventions		/* use HP conventions */
#define float_to_unsigned		"___fixu"
#define unsigned_to_float		"___floatu"
#define profiling_routine		"mcount"
#define profiling_reg			REG_A0
#define profiling_uses_lea		0

#endif /* HP_INTERFACE */


/*
    GAS (NEXT) ASSEMBLER DETAILS
*/

#ifdef GAS_ASSEMBLER

#define asm_simple_instrs		/* instructions are movl etc */
#define asm_simple_regs			/* registers are d0 etc */

#undef 	asm_data_first			/* false */
#define asm_nprefix			outc('#')
#define asm_fprefix			outs("0r")
#define asm_ind_before			/* empty */
#define asm_ind_middle			outc('@')
#define asm_ind_after			/* empty */
#define asm_predec_before		/* empty */
#define asm_predec_after			outs("@ - ")
#define asm_postinc_before		/* empty */
#define asm_postinc_after		outs("@ + ")
#define asm_scale_before			/* empty */
#define asm_scale			outs(":l:")
#define asm_scale_1			outs(":l")
#define asm_mem_before			/* empty */
#define asm_mem_second			outc('@')
#define asm_mem_third			outc('@')
#define asm_mem_after			/* empty */
#define asm_bf_before			outc('{')
#define asm_bf_middle			outc(':')
#define asm_bf_after			outc('}')
#define asm_rpair_sep			outc(':')
#define asm_comment			outc('#')

#define asm_does_jump_lens		/* calculates jump lengths */
#define asm_uses_equals			/* uses = rather than set */
#define asm_uses_lcomm			/* uses lcomm rather than bss */
#define asm_no_btst_suffix		/* doesn't understand btst.[bl] */

#endif /* GAS_ASSEMBLER */


/*
    GNU DEBUGGER DETAILS
*/

#ifdef GDB_DEBUGGER
#define default_diag			DIAG_STAB
#endif /* GDB_DEBUGGER */


/*
    NEXT OPERATING SYSTEM INTERFACE, or SunOS.
*/

#ifdef NEXT_INTERFACE

#define gcc_conventions			/* use gcc conventions */
#define float_to_unsigned		"__fixunsdfsi"
#undef  unsigned_to_float		/* use built-in version */
#define profiling_routine		"mcount"
#define profiling_reg			REG_A0
#define profiling_uses_lea		1

#endif /* NEXT_INTERFACE */

#ifdef SUN_INTERFACE

#define gcc_conventions
#undef float_to_unsigned
#undef unsigned_to_float
#define profiling_routine "mcount"  /* all the defines for profiling */
#define profiling_reg REG_A0        /* are probably wrong. */
#define profiling_uses_lea 1
#endif
