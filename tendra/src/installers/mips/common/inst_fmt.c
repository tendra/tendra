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


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:56:05 $
$Revision: 1.1.1.1 $
$Log: inst_fmt.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:05  release
 * First version to be checked into rolling release.
 *
 * Revision 1.5  1995/09/12  10:59:26  currie
 * gcc pedanttry
 *
 * Revision 1.4  1995/08/16  16:06:47  currie
 * Shortened some .h names
 *
 * Revision 1.3  1995/08/15  09:19:21  currie
 * Dynamic callees + trap_tag
 *
 * Revision 1.2  1995/08/09  10:53:38  currie
 * apply_general bug
 *
 * Revision 1.1  1995/04/13  09:08:06  currie
 * Initial revision
 *
***********************************************************************/
/******************************************************************
		inst_fmt.c

	Procs for outputting various MIPS instruction formats to the
files as_file and ba_file. Each procedure produces assembler for a family of
MIPS operations, the actual member is passed as the string understood
by the assembler. The string contains as its first element the binasm coding for
the instruction +1; see mips_ins.c. Each instruction which alters a register clears
any memory of its contents - see regexps.c

******************************************************************/

#include "config.h"
#include "addrtypes.h"
#include "psu_ops.h"
#include "regexps.h"
#include "mips_ins.h"
#include "ibinasm.h"
#include "out_ba.h"
#include "syms.h"
#include "common_types.h"
#include "main.h"
#include "basicread.h"
#include "inst_fmt.h"


/*******************************************************************
ls_ins
This procedure outputs asembler for load and store instructions.
These necessarily take a reg and a baseoff as parameters, the latter argument allowing
the address to be constructed formrom its base and offset field, see addressingtypes.h.
********************************************************************/


int   andpeep = 0;		/* used to do trivial peepholing of and
				   instructions */
long  andop = 0;




void ls_ins
    PROTO_N ( (ins, reg, a) )
    PROTO_T ( char *ins X int reg X baseoff a )
{
				/* load and store instructions */


  if (reg <0) {reg = 0; /* pathological load of clear_tag */ }

  clear_reg (reg);
  if (ins == i_lbu) {		/* for peepholing later ands */
    andpeep = reg;
    andop = 255;
  }
  else
    if (ins == i_lhu) {
      andpeep = reg;
      andop = 0xffff;
    }
    else {
      andpeep = 0;
    }

  if (a.base == 0 && ins[1]!='s') {		/* literal */
    if (as_file)
      fprintf (as_file, "\t%s\t$%d, %ld\n", ins + 1, reg, a.offset);
    out_iinst (0, ins[0] - 1, reg, xnoreg, formri, a.offset);
  }
  else
    if (a.base >= 0 && a.base <= 31) {/* base - offset */
      if (as_file)
	fprintf (as_file, "\t%s\t$%d, %ld($%d)\n", ins + 1, reg, a.offset, a.base);
      out_iinst (0, ins[0] - 1, reg, a.base, formrob, a.offset);
    }
    else
      if (a.base < 0) {		/* global named */
	char *extname = main_globals[-a.base - 1] -> dec_u.dec_val.dec_id;

	if (as_file) {
	  if (a.offset == 0) {
	    fprintf (as_file, "\t%s\t$%d, %s\n", ins + 1, reg, extname);
	  }
	  else
	    if (a.offset < 0) {
	      fprintf (as_file, "\t%s\t$%d, %s-%ld\n",
		  ins + 1, reg, extname, -a.offset);
	    }
	    else {
	      fprintf (as_file, "\t%s\t$%d, %s+%ld\n",
		  ins + 1, reg, extname, a.offset);
	    }
	}
	out_iinst (symnos[-a.base - 1], ins[0] - 1, reg, xnoreg, formra, a.offset);
      }
      else {
	if (as_file) {		/* global anonymous */
	  if (a.offset == 0) {
	    fprintf (as_file, "\t%s\t$%d, $$%d\n", ins + 1, reg, a.base);
	  }
	  else
	    if (a.offset < 0) {
	      fprintf (as_file, "\t%s\t$%d, $$%d- %ld\n", ins + 1, reg,
		  a.base, -a.offset);
	    }
	    else {
	      fprintf (as_file, "\t%s\t$%d, $$%d+ %ld\n", ins + 1, reg,
		  a.base, a.offset);
	    }
	}
	out_iinst (tempsnos[a.base - 32], ins[0] - 1, reg, xnoreg, formra, a.offset);
      }


}


/*************** monadic operations ***************************
e.g move, neg, abs
************************************************************/

void mon_ins
    PROTO_N ( (ins, dest, src) )
    PROTO_T ( char *ins X int dest X int src )
{
  clear_reg (dest);
  andpeep = 0;
  if (ins == i_neg) { setnoreorder();}
  if (as_file)
    fprintf (as_file, "\t%s\t$%d, $%d\n", ins + 1, dest, src);
  out_rinst (0, ins[0] - 1, dest, src, formrr, xnoreg);
  if (ins == i_neg) { setreorder(); }
  return;
}


/* 3 register operand instructions:- destination, source1, source2 */

void rrr_ins
    PROTO_N ( (ins,dest,src1,src2) )
    PROTO_T ( char *ins X int dest X int src1 X int src2 )
{
  int ex = (ins == i_add || ins == i_sub);
	/* scheduling wrong for exceptional instructions */
  clear_reg (dest);
  andpeep = 0;
  if (ex) { setnoreorder();}
  if (as_file)
    fprintf (as_file, "\t%s\t$%d, $%d, $%d\n", ins + 1, dest, src1, src2);
  out_rinst (0, ins[0] - 1, dest, src1, formrrr, src2);
  if (ex) { setreorder(); }
  return;
}



/* register, register, immediate instructions */

void rri_ins
    PROTO_N ( (ins, dest, src1, imm) )
    PROTO_T ( char *ins X int dest X int src1 X long imm )
{
  int ex = (ins == i_add || ins == i_sub);
	/* scheduling wrong for exceptional instructions */
  if (ins == i_and && dest == andpeep && (imm & andop) == andop) {
    return;
  }
  clear_reg (dest);
  if (ins == i_and) {
    andpeep = dest;
    andop = imm;
  }
  else {
    andpeep = 0;
  }
  if (ex) { setnoreorder();}
  if (as_file)
    fprintf (as_file, "\t%s\t$%d, $%d, %ld\n", ins + 1,
	dest, src1, imm);
  out_iinst (0, ins[0] - 1, dest, src1, formrri, imm);
  if (ex) { setreorder(); }
  return;
}

/* register, immediate instructions */

void ri_ins
    PROTO_N ( (ins, dest, imm) )
    PROTO_T ( char *ins X int dest X long imm )
{
  clear_reg (dest);
  andpeep = 0;
  if (as_file)
    fprintf (as_file, "\t%s\t$%d,%ld\n", ins + 1, dest, imm);
  out_iinst (0, ins[0] - 1, dest, xnoreg, formri, imm);
}


/******************************************************************************
Branch instructions. These have labels as destination.
******************************************************************************/

/* unconditional */

void uncond_ins
    PROTO_N ( (ins, lab) )
    PROTO_T ( char *ins X int lab )
{
  clear_all ();
  andpeep = 0;
  if (as_file)
    fprintf (as_file, "\t%s\t$%d\n", ins + 1, lab);
  if (lab >= 32)
    out_iinst (-lab, ins[0] - 1, xnoreg, xnoreg, forml, 0);
  else
    out_iinst (0, ins[0] - 1, lab, xnoreg, formr, 0);
}

/*conditional */

/* register comparisons */
void condrr_ins
    PROTO_N ( (ins, src1, src2, lab) )
    PROTO_T ( char *ins X int src1 X int src2 X int lab )
{
  if (as_file)
    fprintf (as_file, "\t%s\t$%d, $%d, $%d\n", ins + 1, src1, src2, lab);
  out_iinst (-lab, ins[0] - 1, src1, src2, formrrl, 0);

}

/* register, immediate comparison */
void condri_ins
    PROTO_N ( (ins, src1, imm, lab) )
    PROTO_T ( char *ins X int src1 X long imm X int lab )
{
  if (imm == 0 && ins[4] == 0) {/* optimise branch on zero test */
    if (as_file)
      fprintf (as_file, "\t%sz\t$%d, $%d\n", ins + 1, src1, lab);
    out_iinst (-lab, ins[0] - 1, src1, 0, formrrl, 0);
  }
  else {
    if (as_file)
      fprintf (as_file, "\t%s\t$%d, %ld, $%d\n", ins + 1,
	  src1, imm, lab);
    out_iinst (-lab, ins[0] - 1, src1, xnoreg, formril, imm);
  }
}

/* register comparison with zero*/
void condr_ins
    PROTO_N ( (ins, src1, lab) )
    PROTO_T ( char *ins X int src1 X int lab )
{
  if (as_file)
    fprintf (as_file, "\t%s\t$%d, $%d\n", ins + 1, src1, lab);
  out_iinst (-lab, ins[0] - 1, src1, xnoreg, formrl, 0);
}


/*******************************************************************************
coprocessor instructions
*******************************************************************************/

void cop_ins
    PROTO_N ( (ins, gr, fr) )
    PROTO_T ( char *ins X int gr X int fr )
{
  clear_reg (gr);
  andpeep = 0;
  if (ins == i_ctc1 || ins== i_cfc1) {
    if (as_file)
      fprintf (as_file, "\t%s\t$%d, $%d\n", ins + 1, gr, fr);
    out_rinst (0, ins[0] - 1, gr, fr, formrr, xnoreg);
  }
  else {
    clear_reg ((fr >> 1) + 32);
    if (as_file)
      fprintf (as_file, "\t%s\t$%d, $f%d\n", ins + 1, gr, fr);
    out_rinst (0, ins[0] - 1, gr, fr + float_register, formrr, xnoreg);
  }
}

/* floating point instructions */

void lsfp_ins
    PROTO_N ( (ins, reg, a) )
    PROTO_T ( char *ins X int reg X baseoff a )
{
  clear_reg ((reg >> 1) + 32);
  if (a.base == 0) {
    failer ("ZERO BASE in fp op");/* can't have literal operand */
    if (as_file)
      fprintf (as_file, "\t%s\t$f%d, %ld\n", ins + 1, reg, a.offset);
  }
  else
    if (a.base >= 0 && a.base <= 31) {/* base offset */
      if (as_file)
	fprintf (as_file, "\t%s\t$f%d, %ld($%d)\n",
	    ins + 1, reg, a.offset, a.base);
      out_iinst (0, ins[0] - 1, reg + float_register, a.base, formrob, a.offset);

    }
    else
      if (a.base < 0) {		/* global named */
	char *extname = main_globals[-a.base - 1] -> dec_u.dec_val.dec_id;
	if (as_file) {
	  if (a.offset == 0) {
	    fprintf (as_file, "\t%s\t$f%d, %s\n", ins + 1, reg, extname);
	  }
	  else
	    if (a.offset < 0) {
	      fprintf (as_file, "\t%s\t$f%d, %s-%ld\n",
		  ins + 1, reg, extname, -a.offset);
	    }
	    else {
	      fprintf (as_file, "\t%s\t$f%d, %s+%ld\n",
		  ins + 1, reg, extname, a.offset);
	    }
	}
	out_iinst (symnos[-a.base - 1], ins[0] - 1, reg + float_register, xnoreg,
	    formra, a.offset);

      }
      else {			/* global anonymous */
	if (as_file) {
	  if (a.offset == 0) {
	    fprintf (as_file, "\t%s\t$f%d, $$%d\n", ins + 1, reg, a.base);
	  }
	  else
	    if (a.offset < 0) {
	      fprintf (as_file, "\t%s\t$f%d, $$%d- %ld\n", ins + 1, reg,
		  a.base, -a.offset);
	    }
	    else {
	      fprintf (as_file, "\t%s\t$f%d, $$%d+ %ld\n", ins + 1, reg,
		  a.base, a.offset);
	    }
	}
	out_iinst (tempsnos[a.base - 32], ins[0] - 1, reg + float_register, xnoreg,
	    formra, a.offset);
      }
}


void rrfp_ins
    PROTO_N ( (ins, dest, src) )
    PROTO_T ( char *ins X int dest X int src )
{
  clear_reg ((dest >> 1) + 32);
  if (as_file)
    fprintf (as_file, "\t%s\t$f%d, $f%d\n", ins + 1, dest, src);
  out_rinst (0, ins[0] - 1, dest + float_register, src + float_register, formrr,
      xnoreg);
}

void rrfpcond_ins
    PROTO_N ( (ins, dest, src) )
    PROTO_T ( char *ins X int dest X int src )
{

  if (as_file)
    fprintf (as_file, "\t%s\t$f%d, $f%d\n", ins + 1, dest, src);
  out_rinst (0, ins[0] - 1, dest + float_register, src + float_register, formrr,
      xnoreg);
}

void rrrfp_ins
    PROTO_N ( (ins, dest, src1, src2) )
    PROTO_T ( char *ins X int dest X int src1 X int src2 )
{
  clear_reg ((dest >> 1) + 32);
  if (as_file)
    fprintf (as_file, "\t%s\t$f%d, $f%d, $f%d\n", ins + 1, dest, src1, src2);
  out_rinst (0, ins[0] - 1, dest + float_register, src1 + float_register, formrrr,
      src2 + float_register);
}


/******************************************************************************
jump to address given by register parameter dest
*******************************************************************************/

void br_ins
    PROTO_N ( (ins, dest) )
    PROTO_T ( char *ins X int dest )
{
   /* clear_all (); shouldnt be necessary*/
  andpeep = 0;
  if (as_file)
    fprintf (as_file, "\t%s\t$%d\n", ins + 1, dest);
  if (dest >= 32)
    out_iinst (-dest, ins[0] - 1, xnoreg, xnoreg, forml, 0);
  else
    out_iinst (0, ins[0] - 1, dest, xnoreg, formr, 0);
}


/* jump to external identifier */
void extj_ins
    PROTO_N ( (ins, b) )
    PROTO_T ( char *ins X baseoff b )
{
  char *extname = main_globals[-b.base - 1] -> dec_u.dec_val.dec_id;
  clear_all ();
  andpeep = 0;
  if (as_file)
    fprintf (as_file, "\t%s\t%s\n", ins + 1, extname);
  out_iinst (symnos[-b.base - 1], ins[0] - 1, xnoreg, xnoreg, forma, 0);
}

void tround_ins
    PROTO_N ( (ins, dfr, sfr, gpr) )
    PROTO_T ( char *ins X int dfr X int sfr X int gpr )
{
				/* round and truncate */
  clear_reg (gpr);
  clear_reg ((dfr >> 1) + 32);
  andpeep = 0;
  if (as_file)
    fprintf (as_file, "\t%s\t$f%d,$f%d,$%d\n", ins + 1, dfr, sfr, gpr);
  out_rinst (0, ins[0] - 1, dfr + float_register, sfr + float_register,
      formrrr, gpr);
}

/* hi lo register manipulation */
void hilo_ins
    PROTO_N ( (ins, dest) )
    PROTO_T ( char * ins X int dest )
{
  clear_reg(dest);
  andpeep = 0;
  if (as_file)
    fprintf (as_file, "\t%s\t$%d\n", ins + 1,dest);

  out_rinst(0, ins[0]-1, dest, 0, formr, 0);
}

/* mult & div instructions operating on hilo */
void multdiv_ins
    PROTO_N ( (ins, r1, r2) )
    PROTO_T ( char *ins X int r1 X int r2 )
{
	andpeep=0;
	if (as_file)
		fprintf(as_file, "\t%s\t$%d,$%d\n", ins+1, r1, r2);

	out_rinst (0, ins[0] - 1, r1, r2, formrr, xnoreg);
}
