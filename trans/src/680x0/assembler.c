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
		fputc('&', as_file);
		break;

	case ASM_GAS:
		fputc('#', as_file);
		break;
	}
}

void asm_fprefix(void) {
	switch (assembler) {
	case ASM_HP:
		fputs("0f", as_file);
		break;

	case ASM_GAS:
		fputs("0r", as_file);
		break;
	}
}

void asm_ind_before(void) {
	switch (assembler) {
	case ASM_HP:
		fputc('(', as_file);
		break;
	}
}

void asm_ind_middle(void) {
	switch (assembler) {
	case ASM_GAS:
		fputc('@', as_file);
		break;
	}
}

void asm_ind_after(void) {
	switch (assembler) {
	case ASM_HP:
		fputc(')', as_file);
		break;
	}
}

void asm_predec_before(void) {
	switch (assembler) {
	case ASM_HP:
		fputs(" - (", as_file);
		break;
	}
}

void asm_predec_after(void) {
	switch (assembler) {
	case ASM_HP:
		fputc(')', as_file);
		break;

	case ASM_GAS:
		fputs("@ - ", as_file);
		break;
	}
}

void asm_postinc_before(void) {
	switch (assembler) {
	case ASM_HP:
		fputc('(', as_file);
		break;
	}
}

void asm_postinc_after(void) {
	switch (assembler) {
	case ASM_HP:
		fputs(") + ", as_file);
		break;

	case ASM_GAS:
		fputs("@ + ", as_file);
		break;
	}
}

void asm_scale_before(void) {
	switch (assembler) {
	case ASM_HP:
		fputc(',', as_file);
		break;
	}
}

void asm_scale(void) {
	switch (assembler) {
	case ASM_HP:
		fputs(".l*", as_file);
		break;

	case ASM_GAS:
		fputs(":l:", as_file);
		break;
	}
}

void asm_scale_1(void) {
	switch (assembler) {
	case ASM_HP:
		fputs(".l", as_file);
		break;

	case ASM_GAS:
		fputs(":l", as_file);
		break;
	}
}

void asm_mem_before(void) {
	switch (assembler) {
	case ASM_HP:
		fputs("([", as_file);
		break;
	}
}

void asm_mem_second(void) {
	switch (assembler) {
	case ASM_GAS:
		fputc('@', as_file);
		break;
	}
}

void asm_mem_third(void) {
	switch (assembler) {
	case ASM_HP:
		fputc(']', as_file);
		break;

	case ASM_GAS:
		fputc('@', as_file);
		break;
	}
}

void asm_mem_after(void) {
	switch (assembler) {
	case ASM_HP:
		fputc(')', as_file);
		break;
	}
}

void asm_bf_before(void) {
	fputc('{', as_file);
}

void asm_bf_middle(void) {
	fputc(':', as_file);
}

void asm_bf_after(void) {
	fputc('}', as_file);
}

void asm_rpair_sep(void) {
	fputc(':', as_file);
}

void asm_comment(void) {
	fputc('#', as_file);
}

