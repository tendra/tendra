/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
$Log: out_ba.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:00  release
 * First version to be checked into rolling release.
 *
 * Revision 1.3  1995/05/23  13:24:09  john
 * Change for 64 bit support
 *
 * Revision 1.2  1995/04/10  14:13:34  john
 * Minor changes
 *
 * Revision 1.1.1.1  1995/03/23  10:39:33  john
 * Entered into CVS
 *
 * Revision 1.2  1995/03/23  10:10:12  john
 * Changed prototypes (part of change to support scheduler).
 *
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
