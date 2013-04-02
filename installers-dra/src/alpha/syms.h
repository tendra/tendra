/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

extern int *symnos;
extern int *tempsnos;

#include <construct/installtypes.h>

extern int  symnoforext(dec * t, int filen);
extern int  symnoforstart(int i, int filen);
extern int  symnoforend(dec * ex, int filen);
extern int  symnofordata(int data_lab);
