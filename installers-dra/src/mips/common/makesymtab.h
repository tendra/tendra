/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/* procedure to make a symbol table using the stored tables from
   routines in new_symbol.c */

extern void makesymtab(STRINGS*, ESYMS*, DENSETAB*, pSYMFDR,
    long, char*, long, long, long, long, long, long, PROCSYM*, long);
