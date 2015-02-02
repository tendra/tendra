/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OUT_H
#define OUT_H

#include <stdio.h>

FILE *out_get_stream(void);
void outs(char *str);
void out_comment(void);
void outc(char c);
void outn(long n);
void outhex(int n);
void outnl(void);
void out_hook_nl(void);
long out_tell_pos(void);
void out_set_pos(long pos);

#endif /* OUT_H */
