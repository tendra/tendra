/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OUTPUT_INCLUDED
#define OUTPUT_INCLUDED

extern FILE *fpout;

#define  outc(X)	fputc((X), fpout)
#define  outs(X)	fputs((X), fpout)
#define  outn(X)	fprintf(fpout, "%ld",(long)(X))
#define  outh(X)	fprintf(fpout, "0x%lx",(unsigned long)(X))

#ifdef EBUG
extern void outnl(void);
#else
#define  outnl()	fputc('\n', fpout)
#endif

extern void open_output(char *);
extern void init_instructions(void);
extern void init_output(void);
extern void output_all(void);

extern char *reg_names[];
extern char *instr_names[];

#endif
