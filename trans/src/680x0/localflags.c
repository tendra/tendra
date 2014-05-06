/* $Id$ */

/*
 * Copyright 2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <local/localflags.h>

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

