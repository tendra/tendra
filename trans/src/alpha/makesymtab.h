/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


/* procedure to make a symbol table using the stored tables from routines in symbol.c */

extern void makesymtab(STRINGS*, ESYMS*, DENSETAB*, pSYMFDR,
	int, char*, int, int, int, int, int, int, PROCSYM*, int);
