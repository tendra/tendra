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

