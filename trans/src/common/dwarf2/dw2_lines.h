/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef dw2_lines_key
#define dw2_lines_key

extern void do_statprog_prologue(long l_start, long l_end);
extern void dw2_source_mark(short_sourcepos pos, int is_stmt);
extern void dw2_start_basic_block(void);
extern void close_statprog(long l_end);

#endif
