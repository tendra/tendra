/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *   
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *   
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *   
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *   
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *   
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
*/


/*
   out_ba.c
  
   This file contains code to output a file of machine instructions
   in binary assembler format.

*/

/**/


#include "config.h"
#include "ibinasm.h"
#include "main.h"
#include "out_ba.h"
#include "xalloc.h"

static  binasm ba;

#define  OUT out_one(ba.data)
#define C(x)  ba.x.symno = symno; ba.x.fill0a =0;ba.x.asmtype = asmtype                 

/*
   output one binasm record and return a copy of the output.
*/
char *
out_one(char *d)
{
#if DO_SCHEDULE
  char * res = (char*)xcalloc(binasm_record_length,sizeof(char));
#endif
  int   i;
  for (i = 0; i < binasm_record_length; i++) {
#if DO_SCHEDULE
    res[i] = d[i];
#else
    if (ba_file != NULL)
      putc (d[i], ba_file);
#endif
    d[i] = 0;
  }
#if DO_SCHEDULE
  return res;
#endif
  return (char*)NULL;
}


/*
   output string as set of binasm records
*/
char *
out_data(char *s, int size)
{

  int i;
  int j = ((size+binasm_record_length-1)/binasm_record_length)
    *binasm_record_length;
#if DO_SCHEDULE
  char * res = (char*)xcalloc(j,sizeof(char));
#else
  char *res = (char*)NULL;
#endif
 
  for (i = 0; i < size; i++) {
#if DO_SCHEDULE
    res[i] = s[i];
#else   
    if (ba_file != NULL)
      putc (s[i], ba_file);
#endif
  }
  for (i = size; i < j; i++)
#if DO_SCHEDULE
    res[i] = ' ';
#else 
  if (ba_file != NULL)
    putc (' ', ba_file);
#endif
  return res;
}


char *
out_common(asmsym symno, unsigned asmtype)
{
  /* things like label settings */
  C (common);
  return OUT;
}	


/*
   output enter binasm record
*/
char *
out_ent(asmsym symno, unsigned asmtype, unsigned lexlev)
{
  C (ent);
  ba.ent.lexlev = lexlev;
  return OUT;
}


/*
   output frame binasm record
*/
char *
out_frame(asmsym symno, unsigned asmtype, asmint frameoffset, asmreg framereg, asmreg pcreg)
{
  C (frame);
  ba.frame.frameoffset = frameoffset;
  ba.frame.framereg = framereg;
  ba.frame.pcreg = pcreg;
  return OUT;
}



/*
   output mask binasm record
*/
char *
out_mask(asmsym symno, unsigned asmtype, unsigned regmask, asmint regoffset)
{
  C (mask);
  ba.mask.regmask = regmask;
  ba.mask.regoffset = regoffset;
  return OUT;
}


/*
   output version stamp binasm record
*/
char *
out_verstamp(int majornumber, int minornumber)
{
  ba.verstamp.symno = 0;
  ba.verstamp.fill0a = 0;
  ba.verstamp.asmtype = iverstamp;
  ba.verstamp.majornumber = majornumber;
  ba.verstamp.minornumber = minornumber;
  return OUT;
}


/*
   output line-no binasm record
*/
void
out_loc(int filenumber, unsigned linenumber)
{
  ba.loc.symno = 0;
  ba.loc.fill0a = 0;
  ba.loc.asmtype = iloc;
  ba.loc.filenumber = (filenumber<0)?2:filenumber;
  ba.loc.linenumber = linenumber;
  OUT;
#if !DO_SCHEDULE
  if (ba_file != NULL)
    fflush (ba_file);
#endif
}


/*
   output some data directive binasm record
*/
char *
out_chars(asmsym symno, unsigned asmtype, asmint expression, unsigned short repeat)
{
  C (value);
  ba.value.expression = expression;
  ba.value.repeat = repeat;
  return OUT;
}



/*
   output option binasm record
*/
char *
out_option(int optype, int opint)
{
 
  ba.voption.symno = 0;
  ba.voption.fill0a = 0;
  ba.voption.asmtype = ioption;
  ba.voption.option = optype;
  ba.voption.opt_int_value = opint;
  return OUT;
}


/*
   output some data directive binasm record
*/
char *
out_value(asmsym symno, unsigned asmtype, INT64 expression, unsigned int repeat)
{
  C (value);
  ba.value.expression = expression;
  /*ba.value.repeat = (repeat>0xffff)?0xffff:repeat;*/
  ba.value.repeat = repeat;
  return OUT;
  /*if (repeat>0xffff) out_value(symno, asmtype, expression, repeat-0xffff);*/
}



/*
   output alias binasm record
*/
void
out_alias(asmsym symno, unsigned asmtype, asmreg basereg1, asmreg basereg2)
{
 
  C (alias);
  ba.alias.basereg1 = basereg1;
  ba.alias.basereg2 = basereg2;
  OUT;
}



/*
   output binasm for instruction with no
   immediate operand
*/
char *
out_rinst(asmsym symno, int opcode, asmreg reg1, asmreg reg2, asmformat form, asmreg reg3)
{
  ba.rinst.symno = symno;
  ba.rinst.asmtype = iocode;
  ba.rinst.fill0a = 0;
  ba.rinst.fill03 = 0;
  ba.rinst.op = opcode;
  ba.rinst.reg1 = reg1;
  ba.rinst.reg2 = reg2;
  ba.rinst.form = form;
  ba.rinst.reg3 = reg3;
  return OUT;
}


/*
   output binasm for instruction with immediate operand
*/

char *
out_iinst(asmsym symno, int opcode, asmreg reg1, asmreg reg2, asmformat form, unsigned int mem_tag, int immediate)
{
  ba.iinst.symno = symno;
  ba.iinst.asmtype = iocode;
  ba.iinst.fill0a = 0;
  ba.iinst.fill03 = 0;
  ba.iinst.op = opcode;
  ba.iinst.reg1 = reg1;
  ba.iinst.reg2 = reg2;
  ba.iinst.mem_tag = mem_tag;
  ba.iinst.form = form;
  ba.iinst.immediate = immediate;
  return OUT;
}

char *
out_biinst(asmsym symno, int opcode, asmreg reg1, asmreg reg2, asmformat form, unsigned int mem_tag, INT64 immediate)
{
  ba.iinst.symno = symno;
  ba.iinst.asmtype = iocode;
  ba.iinst.fill0a = 0;
  ba.iinst.fill03 = 0;
  ba.iinst.op = opcode;
  ba.iinst.reg1 = reg1;
  ba.iinst.reg2 = reg2;
  ba.iinst.mem_tag = mem_tag;
  ba.iinst.form = form;
  ba.iinst.immediate = immediate;
  return OUT;
}


/*

*/

char *
out_linst(asmsym symno, int opcode, asmreg reg1, asmreg reg2, asmformat form, asmint imm)
{
  ba.linst.symno = symno;
  ba.linst.asmtype = iocode;
  ba.linst.fill0a = 0;
  ba.linst.fill03 = 0 ;
  ba.linst.op = opcode;
  ba.linst.reg1 = reg1;
  ba.linst.reg2 = reg2;
  ba.linst.form = form;
  ba.linst.imm = imm;
  return OUT;
}








