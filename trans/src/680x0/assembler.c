/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <construct/flags.h>

#include "output.h"

/*
 * This file is just a stopgap intermediate before all assembler dialect
 * interfaces are moved out to a central location.
 */

void asm_nprefix(void) {
	switch (assembler) {
	case ASM_HP:
		outc('&');
		break;

	case ASM_GAS:
		outc('#');
		break;
	}
}

void asm_fprefix(void) {
	switch (assembler) {
	case ASM_HP:
		outs("0f");
		break;

	case ASM_GAS:
		outs("0r");
		break;
	}
}

void asm_ind_before(void) {
	switch (assembler) {
	case ASM_HP:
		outc('(');
		break;
	}
}

void asm_ind_middle(void) {
	switch (assembler) {
	case ASM_GAS:
		outc('@');
		break;
	}
}

void asm_ind_after(void) {
	switch (assembler) {
	case ASM_HP:
		outc(')');
		break;
	}
}

void asm_predec_before(void) {
	switch (assembler) {
	case ASM_HP:
		outs(" - (");
		break;
	}
}

void asm_predec_after(void) {
	switch (assembler) {
	case ASM_HP:
		outc(')');
		break;

	case ASM_GAS:
		outs("@ - ");
		break;
	}
}

void asm_postinc_before(void) {
	switch (assembler) {
	case ASM_HP:
		outc('(');
		break;
	}
}

void asm_postinc_after(void) {
	switch (assembler) {
	case ASM_HP:
		outs(") + ");
		break;

	case ASM_GAS:
		outs("@ + ");
		break;
	}
}

void asm_scale_before(void) {
	switch (assembler) {
	case ASM_HP:
		outc(',');
		break;
	}
}

void asm_scale(void) {
	switch (assembler) {
	case ASM_HP:
		outs(".l*");
		break;

	case ASM_GAS:
		outs(":l:");
		break;
	}
}

void asm_scale_1(void) {
	switch (assembler) {
	case ASM_HP:
		outs(".l");
		break;

	case ASM_GAS:
		outs(":l");
		break;
	}
}

void asm_mem_before(void) {
	switch (assembler) {
	case ASM_HP:
		outs("([");
		break;
	}
}

void asm_mem_second(void) {
	switch (assembler) {
	case ASM_GAS:
		outc('@');
		break;
	}
}

void asm_mem_third(void) {
	switch (assembler) {
	case ASM_HP:
		outc(']');
		break;

	case ASM_GAS:
		outc('@');
		break;
	}
}

void asm_mem_after(void) {
	switch (assembler) {
	case ASM_HP:
		outc(')');
		break;
	}
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

