/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SYMTAB_MAKESYMTAB_H
#define SYMTAB_MAKESYMTAB_H

/*
 * Make a symbol table using the stored tables from routines in symbol.c
 */
void makesymtab(STRINGS *, ESYMS *, DENSETAB *, pSYMFDR,
	int, char *, int, int, int, int, int, int, PROCSYM *, int);

#endif

