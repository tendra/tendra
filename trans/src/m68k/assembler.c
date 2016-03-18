/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/bool.h>
#include <shared/error.h>

#include <main/flags.h>
#include <main/driver.h>
#include <main/print.h>

#include "output.h"

bool no_align_directives;

/*
 * 0 - instructions are movl etc
 * 1 - instructions are mov.l etc
 * TODO: get rid of this, and use HP/GAS assembler dialect instead
 */
int asm_dotty_instrs;

/*
 * 0 - registers are d0 etc
 * 1 - registers are %d0 etc
 * TODO: get rid of this, and use HP/GAS assembler dialect instead
 */
int asm_percent_regs;

int asm_data_first;
int asm_does_jump_lens;
int asm_uses_equals;
int asm_uses_lcomm;
int asm_no_btst_suffix;
int asm_cmp_reversed;


/*
 * This file is just a stopgap intermediate before all assembler dialect
 * interfaces are moved out to a central location.
 */

void asm_nprefix(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf("&");
		break;

	case ASM_GAS:
		asm_printf("#");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

static void
asm_fprefix(void)
{
	switch (assembler) {
	case ASM_HP:
		asm_printf("0f");
		break;

	case ASM_GAS:
		asm_printf("0r");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_ind_before(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf("(");
		break;

	case ASM_GAS:
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_ind_middle(void) {
	switch (assembler) {
	case ASM_HP:
		break;

	case ASM_GAS:
		asm_printf("@");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_ind_after(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(")");
		break;

	case ASM_GAS:
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_predec_before(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(" - (");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_predec_after(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(")");
		break;

	case ASM_GAS:
		asm_printf("@ - ");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_postinc_before(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf("(");
		break;

	case ASM_GAS:
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_postinc_after(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(") + ");
		break;

	case ASM_GAS:
		asm_printf("@ + ");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_scale_before(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(",");
		break;

	case ASM_GAS:
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_scale(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(".l*");
		break;

	case ASM_GAS:
		asm_printf(":l:");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_scale_1(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(".l");
		break;

	case ASM_GAS:
		asm_printf(":l");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_mem_before(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf("([");
		break;

	case ASM_GAS:
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_mem_second(void) {
	switch (assembler) {
	case ASM_HP:
		break;

	case ASM_GAS:
		asm_printf("@");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_mem_third(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf("]");
		break;

	case ASM_GAS:
		asm_printf("@");
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_mem_after(void) {
	switch (assembler) {
	case ASM_HP:
		asm_printf(")");
		break;

	case ASM_GAS:
		break;

	default:
		error(ERR_SERIOUS, "unsupported assembler dialect");
	}
}

void asm_bf_before(void) {
	asm_printf("{");
}

void asm_bf_middle(void) {
	asm_printf(":");
}

void asm_bf_after(void) {
	asm_printf("}");
}

void asm_rpair_sep(void) {
	asm_printf(":");
}

