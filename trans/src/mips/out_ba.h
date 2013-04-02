/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include "ibinasm.h"

extern void out_common(asmsym symno, unsigned asmtype);
extern void out_ent(asmsym symno, unsigned asmtype, unsigned lexlev);
extern void out_frame (asmsym symno, unsigned asmtype, asmint frameoffset,
          asmreg framereg, asmreg pcreg);
extern void out_mask (asmsym symno, unsigned asmtype, unsigned regmask,
          asmint regoffsset);
extern void out_verstamp(int majornumber, int minornumber);
extern void out_loc(unsigned filenumber, unsigned linenumber);
extern void out_chars (asmsym symno, unsigned asmtype, asmint expression,
          unsigned short repeat);
extern void out_option(int x, int y);
extern void out_value (asmsym symno, unsigned asmtype, asmint expression,
          unsigned long repeat);
extern void out_alias (asmsym symno, unsigned asmtype, asmreg basereg1,
          asmreg basereg2);
extern void out_rinst (asmsym symno, unsigned char opcode, asmreg reg1, asmreg reg2,
          asmformat form, asmreg reg3);
extern void out_iinst (asmsym symno, unsigned char opcode, asmreg reg1, asmreg reg2,
          asmformat form, asmint immediate);

extern void out_data(char *data, int size);

extern void out_cpload(asmsym symno, asmreg reg);

extern  FILE * ba_file;
