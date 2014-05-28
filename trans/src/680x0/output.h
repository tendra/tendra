/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OUTPUT_INCLUDED
#define OUTPUT_INCLUDED

#include <stdio.h>

extern FILE *as_file;
extern int no_align_directives;

#define  outh(X)	fprintf(as_file, "0x%lx",(unsigned long)(X))

extern void init_instructions(void);
extern void init_output(void);
extern void output_all(void);

extern char *reg_names[];
extern char *instr_names_dotty[];
extern char *instr_names_simple[];

#define instr_names ((asm_dotty_instrs) ? (instr_names_dotty) : (instr_names_simple))
#define glob_reg_names ((asm_percent_regs) ? (glob_reg_names_percent) : (glob_reg_names_simple))

#ifdef EBUG
#define debug_warning(X)        error(ERROR_WARNING, X)
#else
#define debug_warning(X)
#endif

#endif
