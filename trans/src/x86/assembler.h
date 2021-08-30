/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <reader/exp.h>

#include <construct/installtypes.h>

#include <main/flags.h>

void out_byte(void);
void out_short(void);
void out_long(void);

void out_align(int n);
void out_align_label(int f, exp jr);
void out_eval_postlude(char *s, exp c);
void out_sect(const char *sect);
void out_linkage(const char *linkage, const char *name);
void out_dot_comm(char *name, shape sha);
void out_dot_lcomm(char *name, shape sha);

void out_pic_prelude(void);

void out_switch_jump(int tab, where a, int min);
void out_switch_table (int tab, int min, int max, int *v, int absent);

void out_proc_size(char *s);
void out_proc_type(char *s);
void out_end(void);

void out_openbr(void);
void out_closebr(void);

void out_initialiser(char *name);
void out_main_prelude(void);
void out_main_postlude(void);

#endif /* ASSEMBLER_H */
