/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* ****************************************************************
                              out_ba.c
   Procs for outputting binary assembly files.
   Each record in binasm is 16 bytes, coded in various ways depending
   on class of instruction or directtive.
*****************************************************************/
#include "config.h"
#include "ibinasm.h"
#include "out_ba.h"

extern  FILE * ba_file;

static  binasm ba;



#define  OUT out_one(  ba.data)
#define C(x)  ba.x.symno = symno; ba.x.fill07 =0;\
ba.x.formextn = 0; ba.x.asmtype = asmtype

void out_one
    PROTO_N ( (d) )
    PROTO_T ( char *d )
{	/* output one binasm record */
  int   i;
  for (i = 0; i < 16; i++) {
    putc (d[i], ba_file);
    d[i] = 0;
  }
  return;
}

void out_data
    PROTO_N ( (s, size) )
    PROTO_T ( char *s X int size )
{
				/* output string as set of binasm records
				*/
  int   i;
  int   j = ((size + 15) >> 4) << 4;
  for (i = 0; i < size; i++) {
    putc (s[i], ba_file);
  }
  for (i = size; i < j; i++)
    putc (' ', ba_file);
}




void out_common
    PROTO_N ( (symno, asmtype) )
    PROTO_T ( asmsym symno X unsigned asmtype )
{
				/* things like label settings */
  C (common);
  OUT;
}

void out_ent
    PROTO_N ( (symno, asmtype, lexlev) )
    PROTO_T ( asmsym symno X unsigned asmtype X unsigned lexlev )
{
				/* output enter binasm record */
  C (ent);
  ba.ent.lexlev = lexlev;
  OUT;
}

void out_frame
    PROTO_N ( (symno,asmtype, frameoffset, framereg, pcreg) )
    PROTO_T ( asmsym symno X unsigned asmtype X asmint frameoffset X asmreg framereg X asmreg pcreg )
{/* output frame binasm record */
  C (frame);
  ba.frame.frameoffset = frameoffset;
  ba.frame.framereg = framereg;
  ba.frame.pcreg = pcreg;
  OUT;
}

void out_mask
    PROTO_N ( (symno, asmtype, regmask, regoffset) )
    PROTO_T ( asmsym symno X unsigned asmtype X unsigned regmask X asmint regoffset )
{		/* output mask binasm record */
  C (mask);
  ba.mask.regmask = regmask;
  ba.mask.regoffset = regoffset;
  OUT;
}


void out_verstamp
    PROTO_N ( ( majornumber, minornumber) )
    PROTO_T ( int majornumber X int minornumber )
{
				/* output version stamp binasm record */
  ba.verstamp.symno = 0;
  ba.verstamp.fill07 = 0; ba.verstamp.formextn = 0;
  ba.verstamp.asmtype = iverstamp;
  ba.verstamp.majornumber = majornumber;
  ba.verstamp.minornumber = minornumber;
  OUT;
}

void out_loc
    PROTO_N ( (filenumber, linenumber) )
    PROTO_T ( unsigned filenumber X unsigned linenumber )
{
				/* output line-no binasm record */
  ba.loc.symno = 0;
  ba.loc.fill07 = 0; ba.loc.formextn = 0;
  ba.loc.asmtype = iloc;
  ba.loc.filenumber = filenumber;
  ba.loc.linenumber = linenumber;
  OUT;
  fflush (ba_file);
}

void out_chars
    PROTO_N ( (symno, asmtype, expression, repeat) )
    PROTO_T ( asmsym symno X unsigned asmtype X asmint expression X unsigned short repeat )
{	/* output some data directive binasm
				   record */
  C (value);
  ba.value.expression = expression;
  ba.value.repeat = repeat;
  OUT;
}

void out_option
    PROTO_N ( (optype, opint) )
    PROTO_T ( int optype X int opint )
{
				/* output option binasm record */
  ba.voption.symno = 0;
  ba.voption.fill07 = 0; ba.voption.formextn = 0;
  ba.voption.asmtype = ioption;
  ba.voption.option = optype;
  ba.voption.opt_int_value = opint;
  OUT;
}

void out_value
    PROTO_N ( ( symno, asmtype, expression, repeat) )
    PROTO_T ( asmsym symno X unsigned asmtype X asmint expression X unsigned long repeat )
{	/* output some data directive binasm
  				   record */
    C (value);
    ba.value.expression = expression;
    ba.value.repeat = (repeat>0xffff)?0xffff:repeat;
    OUT;
    if (repeat>0xffff) out_value(symno, asmtype, expression, repeat-0xffff);
}

void out_alias
    PROTO_N ( ( symno, asmtype, basereg1, basereg2) )
    PROTO_T ( asmsym symno X unsigned asmtype X asmreg basereg1 X asmreg basereg2 )
{		/* output alias binasm record */
  C (alias);
  ba.alias.basereg1 = basereg1;
  ba.alias.basereg2 = basereg2;
  OUT;
}

void out_cpload
    PROTO_N ( (symno, reg) )
    PROTO_T ( asmsym symno X asmreg reg )
{
  ba.rinst.symno = symno;
  ba.rinst.asmtype = icpload;
  ba.rinst.fill07 = 0; ba.rinst.formextn = 0;
  ba.rinst.fill03 = 0;
  ba.rinst.op = 0;
  ba.rinst.reg1 = reg;
  ba.rinst.reg2 = 0;
  ba.rinst.form = 0;
  ba.rinst.reg3 = 0;
  OUT;
}
void out_rinst
    PROTO_N ( ( symno, opcode, reg1, reg2, form, reg3) )
    PROTO_T ( asmsym symno X unsigned char opcode X asmreg reg1 X asmreg reg2 X asmformat form X asmreg reg3 )
{/* output binasm for instruction with no
				   immediate operand */
  ba.rinst.symno = symno;
  ba.rinst.asmtype = iocode;
  ba.rinst.fill07 = 0; ba.rinst.formextn = 0;
  ba.rinst.fill03 = 0;
  ba.rinst.op = opcode;
  ba.rinst.reg1 = reg1;
  ba.rinst.reg2 = reg2;
  ba.rinst.form = form;
  ba.rinst.reg3 = reg3;
  OUT;
}

void out_iinst
    PROTO_N ( ( symno, opcode, reg1, reg2, form, immediate) )
    PROTO_T ( asmsym symno X unsigned char opcode X asmreg reg1 X asmreg reg2 X asmformat form X asmint immediate )
{
				/* output binasm for instruction with
				   immediate operand */
  ba.iinst.symno = symno;
  ba.iinst.asmtype = iocode;
  ba.iinst.fill07 = 0; ba.iinst.formextn = 0;
  ba.iinst.fill03 = 0;
  ba.iinst.op = opcode;
  ba.iinst.reg1 = reg1;
  ba.iinst.reg2 = reg2;
  ba.iinst.form = form;
  ba.iinst.mem_tag = 0; /*????*/
  ba.iinst.immediate = immediate;
  OUT;
}
