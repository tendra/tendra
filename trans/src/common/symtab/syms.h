/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef SYMTAB_SYMS_H
#define SYMTAB_SYMS_H

#include <construct/installtypes.h>

int *symnos;
int *tempsnos;

int symnoforext(dec * t, int filen);
int symnoforstart(int i, int filen);
int symnoforend(dec * ex, int filen);
int symnofordata(int data_lab);

#endif

