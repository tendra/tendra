/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

extern int no_align_directives;

extern int asm_dotty_instrs;
extern int asm_percent_regs;

extern int asm_data_first;
extern int asm_does_jump_lens;
extern int asm_uses_equals;
extern int asm_uses_lcomm;
extern int asm_no_btst_suffix;
extern int asm_cmp_reversed;

void asm_nprefix(void);
void asm_fprefix(void);
void asm_ind_before(void);
void asm_ind_middle(void);
void asm_ind_after(void);
void asm_predec_before(void);
void asm_predec_after(void);
void asm_postinc_before(void);
void asm_postinc_after(void);
void asm_scale_before(void);
void asm_scale(void);
void asm_scale_1(void);
void asm_mem_before(void);
void asm_mem_second(void);
void asm_mem_third(void);
void asm_mem_after(void);
void asm_bf_before(void);
void asm_bf_middle(void);
void asm_bf_after(void);
void asm_rpair_sep(void);
void asm_comment(void);

#endif

