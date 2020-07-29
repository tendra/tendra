/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef PSEUDO_H
#define PSEUDO_H

extern void setnoreorder(void);
extern void setreorder(void);
extern void setvolatile(void);
extern void setnovolatile(void);
extern void setnoat(void);
extern void setat(void);
extern void setframe(int32,int32);
extern void set_text_section(void);
extern void set_file(char *,int);
extern void setprologue(int);
extern void set_align(int);
extern void set_lineno(int,int);

#endif
