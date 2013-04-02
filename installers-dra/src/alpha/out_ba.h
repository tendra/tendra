/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include "ibinasm.h"
#include "cross.h"

extern char *out_common(asmsym,unsigned);
extern char *out_ent(asmsym,unsigned,unsigned);
extern char *out_frame(asmsym,unsigned,asmint,asmreg,asmreg);
extern char *out_mask(asmsym,unsigned,unsigned,asmint);
extern char *out_verstamp(int,int);
extern void out_loc(int,unsigned);
extern char *out_chars(asmsym,unsigned,asmint,unsigned short);
extern char *out_option(int,int);
extern char *out_value(asmsym,unsigned,INT64,unsigned);
extern void out_alias(asmsym,unsigned,asmreg,asmreg);
extern char *out_rinst(asmsym,int,asmreg,asmreg,asmformat,asmreg);
extern char *out_linst(asmsym,int,asmreg,asmreg,asmformat,asmint);
extern char *out_data(char *,int);
extern char *out_iinst(asmsym,int,asmreg,asmreg,asmformat, unsigned int, int);
extern char *out_biinst(asmsym,int,asmreg,asmreg,asmformat, unsigned int, INT64);
extern  FILE * ba_file;
