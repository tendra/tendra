/* $Id$ */

/*
 * Copyright 2012, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "localflags.h"

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

