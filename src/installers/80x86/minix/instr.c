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


/* 80x86/instr.c */

/**********************************************************************
$Author: pwe $
$Date: 1998/03/15 16:00:19 $
$Revision: 1.2 $
$Log: instr.c,v $
 * Revision 1.2  1998/03/15  16:00:19  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.1.1.1  1998/01/17  15:55:51  release
 * First version to be checked into rolling release.
 *
 * Revision 1.28  1997/04/17  11:55:47  pwe
 * dwarf2 improvements
 *
 * Revision 1.27  1997/03/24  11:15:13  pwe
 * dwarf2 option/default
 *
 * Revision 1.26  1997/03/20  16:23:41  pwe
 * dwarf2
 *
 * Revision 1.25  1997/02/18  11:42:52  pwe
 * NEWDIAGS for debugging optimised code
 *
 * Revision 1.24  1996/12/13  14:39:27  pwe
 * prep NEWDIAGS
 *
 * Revision 1.23  1996/07/09  09:43:39  pwe
 * caller env_offset if callees present, and tidy
 *
 * Revision 1.22  1996/05/20  14:30:11  pwe
 * improved 64-bit handling
 *
 * Revision 1.21  1996/05/13  12:51:55  pwe
 * undo premature commit
 *
 * Revision 1.19  1996/01/17  11:24:31  pwe
 * resurrect performance
 *
 * Revision 1.18  1995/11/01  18:41:14  pwe
 * PIC tail_call and exception handling
 *
 * Revision 1.17  1995/10/24  17:02:43  pwe
 * local calls to avoid PLT, Solaris constraint
 *
 * Revision 1.16  1995/10/16  14:55:19  pwe
 * stack change v fpucon
 *
 * Revision 1.15  1995/09/26  16:46:48  pwe
 * compare with zero to ignore previous overflow
 *
 * Revision 1.14  1995/09/15  17:39:13  pwe
 * tidy and correct fistp
 *
 * Revision 1.13  1995/09/08  12:51:07  pwe
 * exceptions improved
 *
 * Revision 1.12  1995/09/06  16:29:20  pwe
 * exceptions now OK
 *
 * Revision 1.11  1995/09/05  16:24:51  pwe
 * specials and exception changes
 *
 * Revision 1.10  1995/09/01  17:30:05  pwe
 * traps and Build scripts
 *
 * Revision 1.9  1995/08/30  16:06:33  pwe
 * prepare exception trapping
 *
 * Revision 1.8  1995/08/23  09:42:42  pwe
 * track fpu control word for trap etc
 *
 * Revision 1.7  1995/08/14  13:53:36  pwe
 * several corrections, tail calls and error jumps
 *
 * Revision 1.6  1995/08/04  08:29:23  pwe
 * 4.0 general procs implemented
 *
 * Revision 1.5  1995/04/12  17:05:54  pwe
 * name_prefix required for call_libfn
 *
 * Revision 1.4  1995/02/16  18:47:08  pwe
 * transformed subtract inverts, sets and adds carry in case of error_jump
 *
 * Revision 1.3  1995/01/30  12:56:18  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.2  1994/11/08  09:55:03  jmf
 * Unknown?
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.4  1994/08/08  15:54:29  jmf
 * Dont keep_short after label
 *
 * Revision 1.3  1994/07/15  13:59:23  jmf
 * Change fstack popping to use fstp st(0).
 *
 * Revision 1.2  1994/07/12  15:19:18  jmf
 * No change
 *
 * Revision 1.1  1994/07/12  14:33:55  jmf
 * Initial revision
 *
**********************************************************************/


/**********************************************************************
                           instr.c


   defines the general routines for outputting instructions and labels:



**********************************************************************/


#include "config.h"
#include "common_types.h"
#include "out.h"
#include "operand.h"
#include "instrmacs.h"
#include "expmacs.h"
#include "exp.h"
#include "instr386.h"
#include "flags.h"
#include "tags.h"
#include "shapemacs.h"
#include "flpt.h"
#include "flpttypes.h"
#include "coder.h"
#include "basicread.h"
#include "reg_record.h"
#include "installglob.h"
#include "table_fns.h"
#include "codermacs.h"
#include "install_fns.h"
#include "machine.h"
#include "localflags.h"
#include "assembler.h"
#include "messages_8.h"
#include "readglob.h"
#include "check.h"
#include "label_ops.h"
#include "externs.h"
#include "xalloc.h"

#include "instr.h"

#ifdef NEWDWARF
#include "dw2_config.h"
#include "dw2_extra.h"
#endif


/* LOCAL TYPE */

typedef union eu_u {int i; exp e;} punner;

/* MACROS */

#define fstack_base 8

/* VARIABLES */
/* All variables initialised */

int  extra_stack = 0;	/* init by init_all */
int max_extra_stack = 0;	/* init by cproc */
int no_frame;		/* init by cproc */
#ifndef NEWDIAGS
static long  last_jump_pos;	/* set locally */
#endif
int  last_jump_label;	/* cleared to -1 by outnl */

static exp cont_err_handler = nilexp;


/* IDENTITIES */

char *margin = "";		/* instruction left margin */
char *spx = " ";		/* separates instruction from operands */
char *sep = ", ";		/* separates operands */

char *reg_name_long[8] = {
  "eax", "edx", "ecx", "ebx", "edi", "esi", "ebp", "esp"
};
char *reg_name_word[7] = {
  "ax", "dx", "cx", "bx", "di", "si", "bp"
};
char *reg_name_byte[7] = {
  "al", "dl", "cl", "bl", "??", "??", "??"
};

char *fl_reg_name[8] = {
  "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)"
};

/* PROCEDURES */

void temp_push_fl
    PROTO_Z ()
{
  ++fstack_pos;
  return;
}
void temp_pop_fl
    PROTO_Z ()
{
  --fstack_pos;
  return;
}


/***************************************************************

outreal outputs a floating point number

****************************************************************/

void outreal
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  flt * f = &flptnos[no(e)];
  int sw = name(sh(e)) - shrealhd;
  r2l longs;

  longs = real2longs_IEEE(f, sw);

  switch (sw) {
    case 0:
      outhex(longs.i1);
      outnl();
      break;
    case 1:
      outhex(longs.i1);
      outs(",");
      outhex(longs.i2);
      outnl();
      break;
    case 2:
      outhex(longs.i1);
      outs(",");
      outhex(longs.i2);
      outs(",");
      outhex(longs.i3);
      outnl();
      break;
  };

  return;
}

/* output operand i (in bytes) relative to
   stack pointer  uses address relative to
   frame pointer if it might be shorter */
void rel_sp
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
  int  n = i + (extra_stack / 8);
  if (!must_use_bp) {
				/* if we might use alloca all
				   displacements must be relative to frame
				   pointer */
    if (n == 0) {
      outs ("(esp)");
      return;
    };
    if (n <= 127 || no_frame || stack_aligned_8byte) {
				/* use stack pointer if displacement from
				   it is small */
      outn ((long)n);
      outs ("(esp)");
      return;
    };
  };
  /* otherwise use displacement from frame pointer */
  outn ((long)(i + (stack_dec / 8)));
  outs("-");
  outs(local_prefix);
  outs ("disp");
  outn ((long)crt_proc_id);
  outs ("(ebp)");
  return;
}

/* output operand i (in bytes) relative to
   stack pointer */
void rel_cp
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
  int  n = i + (extra_stack / 8);
  if (n == 0) {
    outs ("(esp)");
    return;
  };
  outn ((long)n);
  outs ("(esp)");
  return;
}

/* output operand relative to frame
   pointer */
void rel_ap
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
  if (no_frame) {
    outn ((long)(i + ((extra_stack - stack_dec) / 8)));
    outs("+");
    outs(local_prefix);
    outs ("disp");
    outn ((long)crt_proc_id);
    outs ("(esp)");
    return;
  }
  else {
    outn ((long)i + 4);
    outs ("(ebp)");
    return;
  };
}

/* output operand relative to frame
   pointer and push space*/
void rel_ap1
    PROTO_N ( (i) )
    PROTO_T ( int i )
{
  if (no_frame) {
    outn ((long)(i + ((extra_stack - stack_dec) / 8)));
    outs("+");
    outs(local_prefix);
    outs ("fcwdisp");
    outn ((long)crt_proc_id);
    outs ("(esp)");
    return;
  }
  else {
    outn ((long)i);
    outs("-");
    outs(local_prefix);
    outs ("fcwdisp");
    outn ((long)crt_proc_id);
    outs ("(ebp)");
    return;
  };
}

int  get_reg_no
    PROTO_N ( (regs) )
    PROTO_T ( int regs )
{
  frr fr;
  /* find the registers associated with the bit pattern regs */

  fr = first_reg (regs);
  if (regs == 0x10000 || fr.fr_no == (fstack_pos))
    return (fstack_pos);
  return (fr.fr_no);		/* this is the register number */
}

/* output a register address, regs is a
   bit pattern, rdisp is an offset in bit
   units. le tells us how to refer to the
   register (eg al or ax or eax) */
void regn
    PROTO_N ( (regs, rdisp, ldname, le) )
    PROTO_T ( int regs X int rdisp X exp ldname X int le )
{
  int  z;
  char **rn;
  UNUSED(rdisp);
  z = get_reg_no (regs);

  if (name (ldname) == name_tag && islastuse(ldname))
    regsinuse = regsinuse & ~regs;

  if (z >= first_fl_reg) {
    if (z == first_fl_reg) {
      outs (fl_reg_name[0]);
      return;
    };
    if (fstack_pos > 16) {
      failer (BAD_FSTACK);
      exit(EXIT_FAILURE);
    };
    outs (fl_reg_name[fstack_pos - z]);
    /* variables held in the floating point registers have to be addressed
       relative to the current stack position, because the registers are a
       stack as well as a register bank */
    return;
  };

  switch (le) {
    case 8:
      rn = reg_name_byte;
      break;
    case 16:
      rn = reg_name_word;
      break;
    default:
      rn = reg_name_long;
      break;
  };
  outs (rn[z]);			/* this outputs the register name */
  return;
}


/* output a displacement from register operand */
void ind_reg
    PROTO_N ( (regs, rdisp, offset, ldname) )
    PROTO_T ( int regs X int rdisp X int offset X exp ldname )
{
  if (regs == 128)
    offset += extra_stack;

  if (offset == 0) {
    outs ("(");
    regn (regs, rdisp, ldname, 32);
    outs (")");
  }
  else {
    outn ((long)offset / 8);
    outs ("(");
    regn (regs, rdisp, ldname, 32);
    outs (")");
  };
  return;
}

/* use indexed addressing */
void index_opnd
    PROTO_N ( (whmain, wh, sc) )
    PROTO_T ( where whmain X where wh X int sc )
{
  exp m = whmain.where_exp;
  if ((name (m) == name_tag && ptno (son (m)) == reg_pl) ||
      (name (m) == cont_tag && name (son (m)) == name_tag &&
	isvar (son (son (m))) && ptno (son (son (m))) == reg_pl)) {
    outs ("(");
    operand (32, whmain, 0, 0);  /* base register (operand will call regn) */
    outs (")");
  }
  else
    operand (32, whmain, 0, 0);  /* base register */
  outs ("(");
  operand (32, wh, 1, 0); /* index register */
  if (sc != 1) {
    outs ("*");
    outn ((long)sc);      /* scale */
  };
  outs (")");
  return;
}


/* output an external operand */
void extn
    PROTO_N ( (id, off, b) )
    PROTO_T ( exp id X int off X int b )
{
  dec * et = brog (id);

  if (b && isvar(id))
    outs ("("); /* ACK indirect */

  if (off == 0)
    outs (et -> dec_u.dec_val.dec_id);
  else {
    outs (et -> dec_u.dec_val.dec_id);
    outs ("+");
    outn ((long)off / 8);
  };

  if (b && isvar(id))
    outs (")"); /* ACK indirect */

  return;
}

/* an integer constant */
void int_operand
    PROTO_N ( (k, l) )
    PROTO_T ( int k X int l )
{
  int  mask;
  switch (l) {
    case 8:
      mask = 0xff;
      break;
    case 16:
      mask = 0xffff;
      break;
    default:
      mask = 0xffffffff;
  };
  outn ((long)k & mask);
  return;
}


/* an external literal */
void const_extn
    PROTO_N ( (id, off) )
    PROTO_T ( exp id X int off )
{
  extn (id, off, 0);
  return;
}

/* an external literal */
void proc_extn
    PROTO_N ( (id, off) )
    PROTO_T ( exp id X int off )
{
  extn (id, off, 0);
  return;
}

void ldisp
    PROTO_Z ()
{
   outs(local_prefix);
   outs("disp");
   outn((long)crt_proc_id);
}

void label_operand
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  punner l;
  l.e = pt(e);
  outs(local_prefix);
  outs("V");
  outn((long)l.i);
  return;
}

void set_lv_label
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  punner l;
  l.e = e;
  min_rfree |= 0x78;  /* save all callee registers */

  outs(local_prefix);
  outs("V");
  outn((long)l.i);
  outs(":");
  outnl();
  return;
}

void set_env_off
    PROTO_N ( (s, n) )
    PROTO_T ( int s X exp n )
{
  punner l;
  l.e = n;
  outs(local_prefix);
  outs("O");
  outn((long)l.i);		/* produce an identifying number */
  outs(" = ");
  if (s<4)
   {
    outn((long)-s/8);
    outs("-");
    outs(local_prefix);
    outs ("disp");
    outn ((long)crt_proc_id);
   }
  else
   outn((long)s/8);
  outnl();
}

void envoff_operand
    PROTO_N ( (e, off) )
    PROTO_T ( exp e X int off )
{
  punner l;
  l.e = e;
  if (off != 0)
   {
    outn((long)off);
    outs("+");
   };
  outs(local_prefix);
  outs("O");
  outn((long)l.i);		/* produce an identifying number */
  return;
}

void envsize_operand
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  dec * et = brog(e);
  outs (local_prefix);
  outs ("ESZ");
  outs (et -> dec_u.dec_val.dec_id);
  return;
}

/* 80386 instruction with no operands */
void ins0
    PROTO_N ( (i) )
    PROTO_T ( char *i )
{
  outs (margin);
  outs (i);
  outnl ();
  return;
}

/* one operand */
void ins1
    PROTO_N ( (i, le1, a1) )
    PROTO_T ( char *i X int le1 X where a1 )
{
  outs (margin);
  outs (i);
  outs (spx);
  operand (le1, a1, 1, 0);
  outnl ();
  return;
}

/* one operand, which is indirect */
void ins1ind
    PROTO_N ( (i, le1, a1) )
    PROTO_T ( char *i X int le1 X where a1 )
{
  outs (margin);
  outs (i);
  outs (spx);
  operand (le1, a1, 1, 0);
  outnl ();
  return;
}

/* one operand, which is immediate */
void ins1lit
    PROTO_N ( (i, le1, a1) )
    PROTO_T ( char *i X int le1 X where a1 )
{
  outs (margin);
  outs (i);
  outs (spx);
  operand (le1, a1, 1, 1);
  outnl ();
  return;
}

/* two operands */
void ins2
    PROTO_N ( (i, le1, le2, a1, a2) )
    PROTO_T ( char *i X int le1 X int le2 X where a1 X where a2 )
{
  outs (margin);
  outs (i);
  outs (spx);
  operand (le2, a2, 1, 0);
  outs (sep);
  operand (le1, a1, 1, 0);
  outnl ();
  return;
}

/* three operands */
void ins3
    PROTO_N ( (i, le1, le2, le3, a1, a2, a3) )
    PROTO_T ( char *i X int le1 X int le2 X int le3 X where a1 X where a2 X where a3 )
{
  outs (margin);
  outs (i);
  outs (spx);
  operand (le3, a3, 1, 0);
  outs (sep);
  operand (le2, a2, 1, 0);
  outs (sep);
  operand (le1, a1, 1, 0);
  outnl ();
  return;
}


void simplest_set_lab
    PROTO_N ( (labno) )
    PROTO_T ( int labno )
{
  outs(local_prefix);
  outn ((long)labno);
  outs (":");
  outnl ();
}


void simple_set_label
    PROTO_N ( (labno) )
    PROTO_T ( int labno )
{
#ifdef CHECKIMPROVE
  if (labno == last_jump_label)
    failer("redundant jump");
#endif
#ifndef NEWDIAGS
  int   st = 0;
  if (!diagnose && labno == last_jump_label) {
    st = fseek (fpout, last_jump_pos, 0);
  };
  /* eliminate immediately previous jump to this label */
  if (st == -1) {
    failer (SEEK_FAILURE);
    exit(EXIT_FAILURE);
  };
#endif

  cond1_set = 0;
  cond2_set = 0;
  outs(local_prefix);
  outn ((long)labno);		/* the label no is held in the ptr field
				*/
  outs (":");
  outnl ();
/* Removed for experiments: improves compress?
  keep_short = 1;
*/
  return;
}

/* set label described by the jump record jr */
void set_label
    PROTO_N ( (jr) )
    PROTO_T ( exp jr )
{
  simple_set_label (ptno (jr));
}

/*  jump record: exp
    pt - label;
    last - forward;
    son - stack_dec;
    prop - floating stack position
*/

void discard_fstack
    PROTO_Z ()
{
  outs ("fstp st(0)");
  outnl ();
  pop_fl;
  return;
}

void discard_st1
    PROTO_Z ()
{
  outs ("fstp st(1)");
  outnl ();
  pop_fl;
}


/* output a jump to the label described by
   jump record jr */
void jump
    PROTO_N ( (jr, with_fl_reg) )
    PROTO_T ( exp jr X int with_fl_reg )
{
  int  fs_dest = (int)fstack_pos_of (jr);
  int  good_fs = fstack_pos;
  int  good_sd = stack_dec;
  if (fs_dest < first_fl_reg)
    failer (FSTACK_UNSET);
  if (with_fl_reg) {		/* jumping with a floating value */
    /* clear off any unwanted stack registers */
    while (fstack_pos > (fs_dest + 1))
      discard_st1 ();
    fstack_pos = good_fs - 1;
  }
  else {
    /* clear off any unwanted stack registers */
    while (fstack_pos > fs_dest)
      discard_fstack ();
    fstack_pos = good_fs;
  };

  if (sonno(jr) > stack_dec) {
    add(slongsh, mw (zeroe, (sonno(jr)-stack_dec) / 8), sp, sp);
    stack_dec = sonno(jr);
  }

  reset_fpucon();
  stack_dec = good_sd;

#ifndef NEWDIAGS
  if (flush_before_tell)
    IGNORE fflush(fpout);
  last_jump_pos = ftell (fpout);
#endif
  outs (margin);
  outs (jmp);
  outs (spx);
  outs(local_prefix);
  outn ((long)ptno (jr));
  outnl ();
  last_jump_label = ptno (jr);
  return;
}

static char* xse = "<=0";	/* no corresponding jump instruction */
static char* xnse = ">0";


/* output code for a branch instruction
   determined by test_no. The test is
   signed if sg is true */
static char *out_branch
    PROTO_N ( (sg, test_no, shnm) )
    PROTO_T ( int sg X int test_no X int shnm )
{
  if (shnm >= shrealhd && shnm <= doublehd) {
    switch (test_no) {
      case 1:
	return (jne);

      case 2:
	return (jne);

      case 3:
	return (jpe);

      case 4:
	return (jpe);

      case 5:
	return (jpe);

      case 6:
	return (jpo);

      case 7:
	return (jpo);

      case 8:
	return (jpo);

      case 9:
	return (je);

      case 10:
	return (je);

      case 11:
	return (jne);

      case 12:
	return (je);

      case 13:
	return (jne);

      case 14:
	return (je);

      default:
	failer (BAD_TESTNO);
    };
  };

  if (sg) {
    switch (test_no) {
      case 1:
	return (sg<0 ? xse : jle);
      case 2:
	return (sg<0 ? js : jl);

      case 3:
	return (sg<0 ? jns : jge);

      case 4:
	return (sg<0 ? xnse : jg);

      case 5:
	return (jne);

      case 6:
	return (je);

      default:
	failer (BAD_TESTNO);
    };
  }
  else {
    switch (test_no) {
      case 1:
	return (jbe);

      case 2:
	return (jb);

      case 3:
	return (jae);

      case 4:
	return (ja);

      case 5:
	return (jne);

      case 6:
	return (je);

      default:
	failer (BAD_TESTNO);
    };
  };
  return ((char *) 0);
}

void simple_branch
    PROTO_N ( (j, labno) )
    PROTO_T ( char *j X int labno )
{
  outs (margin);
  outs (j);
  outs (spx);
  outs(local_prefix);
  outn ((long)labno);
  outnl ();

}


/* output conditional jump to jr. testno
   specifies kind of test. sg is 1 if
   signed arithmetic, 0 unsigned, -1 if
   signed vs zero (ignoring overflow).
   shnm name of shape */
void branch
    PROTO_N ( (test_no, jr, sg, shnm) )
    PROTO_T ( int test_no X exp jr X int sg X int shnm )
{
  int  fs_dest = (int)fstack_pos_of (jr);
  int  good_fs = fstack_pos;
  int  good_fpucon = fpucon;
  if (fs_dest < first_fl_reg)
    failer (FSTACK_UNSET);
  if (fstack_pos > fs_dest || sonno(jr) != stack_dec || fpucon != normal_fpucon
	|| cmp_64hilab >= 0) {
	/* floating point stack or call stack need attention */
    int  nl = next_lab ();
    int inv_test_no = (flpt_always_comparable ||
			 (shnm < shrealhd || shnm > doublehd))
				? (int)int_inverse_ntest[test_no]
				: (int)real_inverse_ntest[test_no];

    char* cj = out_branch ((cmp_64hilab >= 0 ? 0 : sg), inv_test_no, shnm);
    if (*cj == 'j') {
      simple_branch (cj, nl);
    }
    else	/* compare with zero, ignoring overflow */
    if (*cj == '>') {
      int nl1 = next_lab ();
      simple_branch (js, nl1);
      simple_branch (jne, nl);
      simplest_set_lab (nl1);
    }
    else {
      simple_branch (js, nl);
      simple_branch (je, nl);
    }

    if (cmp_64hilab >= 0) {
      int nl2 = ptno (jr);
      if (shnm != s64hd)
	failer ("uncompleted 64-bit comparison");
      if (fstack_pos > fs_dest || sonno(jr) != stack_dec || fpucon != normal_fpucon) {
	nl2 = next_lab ();
	simplest_set_lab (nl2);
      }
      jump (jr, 0);
      simplest_set_lab (cmp_64hilab);
      simple_branch (out_branch (1, test_no, shnm), nl2);
      cmp_64hilab = -1;
    }
    else
      jump (jr, 0);

    fstack_pos = good_fs;
    fpucon = good_fpucon;
    simplest_set_lab (nl);
    return;
  };

  {
    char* cj = out_branch (sg, test_no, shnm);
    if (*cj == 'j') {
      simple_branch (cj, ptno (jr));
    }
    else	/* compare with zero, ignoring overflow */
    if (*cj == '>') {
      int nl1 = next_lab ();
      simple_branch (js, nl1);
      simple_branch (jne, ptno (jr));
      simplest_set_lab (nl1);
    }
    else {
      simple_branch (js, ptno (jr));
      simple_branch (je, ptno (jr));
    }
  }
  return;
}

void setcc
    PROTO_N ( (test_no, sg, shnm) )
    PROTO_T ( int test_no X int sg X int shnm )
{
  char * b;
  if (cmp_64hilab >= 0) {
    int chl = cmp_64hilab;
    int nl = next_lab ();
    if (shnm != s64hd)
      failer ("uncompleted 64-bit comparison");
    cmp_64hilab = -1;
    setcc (test_no, 0, ulonghd);
    simple_branch (jmp, nl);
    simplest_set_lab (chl);
    setcc (test_no, sg, slonghd);
    simplest_set_lab (nl);
  }

  b = out_branch (sg, test_no, shnm);
  if (*b != 'j')
    failer(NO_SETCC);
  outs(margin);
  outs("set");
  outs(&b[1]);
  outs(spx);
  outs(reg_name_byte[0]);
  outnl();
  return;
}

/* output conditional jump to jr if overflow
   sg is 1 if signed arithmetic, 0 unsigned */
void jmp_overflow
    PROTO_N ( (jr, sg, inv) )
    PROTO_T ( exp jr X int sg X int inv )
{
  int  fs_dest = (int)fstack_pos_of (jr);
  int  good_fs = fstack_pos;
  int  good_fpucon = fpucon;
  if (fs_dest < first_fl_reg)
    failer (FSTACK_UNSET);
  if (fstack_pos > fs_dest || sonno(jr) != stack_dec || fpucon != normal_fpucon) {
	/* floating point stack or call stack need attention */
    int  nl = next_lab ();
    if (sg)
      simple_branch(jno, nl);
    else
      simple_branch((inv ? jb : jae), nl);
    jump (jr, 0);
    fstack_pos = good_fs;
    fpucon = good_fpucon;
    simplest_set_lab (nl);
    return;
  };
  if (sg)
    simple_branch(jo, ptno(jr));
  else
    simple_branch((inv ? jae : jb), ptno(jr));
  return;
}


/* software interrupt */
void trap_ins
    PROTO_N ( (s) )
    PROTO_T ( int s )
{
#ifndef AVOID_INTOV
  if (s == f_overflow) {
    ins0 ("int 4");	/* numeric interrupt */
    return;
  }
#else
#if (AVOID_INTOV == 16)
  if (s == f_overflow) {
    ins0 ("int 16");	/* mimic floating point interrupt */
    return;
  }
#endif
#endif
  if (cont_err_handler == nilexp) {
    cont_err_handler = make_extn ("__trans386_errhandler", f_proc, 1);
    if (!PIC_code)
      cont_err_handler = getexp (f_proc, nilexp, 1, cont_err_handler, nilexp, 0, 0, cont_tag);
  }
  ins1 (pushl, 32, mw (zeroe, s));
#ifdef NEWDWARF
  if (diagnose && dwarf2 && no_frame)
    dw2_track_push();
#endif
  ins2 (movl, 32, 32, mw(cont_err_handler, 0), reg0);
  if (PIC_code)
    ins1ind (call, 32, ind_reg0);
  else
    ins1ind (call, 32, reg0);
  return;
}


/* output software interrupt if overflow
   sg is 1 if signed arithmetic, 0 unsigned */
void trap_overflow
    PROTO_N ( (sg, inv) )
    PROTO_T ( int sg X int inv )
{
#ifdef AVOID_INTOV
    int nl = next_lab ();
    if (sg)
      simple_branch(jno, nl);
    else
      simple_branch((inv ? jb : jae), nl);
    trap_ins(f_overflow);
    simplest_set_lab (nl);
#else
  if (sg)
    ins0(into);
  else {
    int nl = next_lab ();
    simple_branch((inv ? jb : jae), nl);
    trap_ins(f_overflow);
    simplest_set_lab (nl);
  }
#endif
  return;
}


/* conditional software interrupt
   sg is 1 if signed arithmetic
   shnm name of shape */
void test_trap
    PROTO_N ( (test_no, sg, shnm) )
    PROTO_T ( int test_no X int sg X int shnm )
{
  int nl = next_lab ();
  int inv_test_no = (flpt_always_comparable ||
			 (shnm < shrealhd || shnm > doublehd))
				? (int)int_inverse_ntest[test_no]
				: (int)real_inverse_ntest[test_no];
  simple_branch (out_branch (sg, inv_test_no, shnm), nl);
  trap_ins(f_overflow);
  simplest_set_lab (nl);
  return;
}



/* special output for doing multiply by
   using index instructions */
void mult_op
    PROTO_N ( (inc, rmain, rind, sc, dest) )
    PROTO_T ( int inc X where rmain X where rind X int sc X where dest )
{
  outs (margin);
  outs ("lea");
  outs (spx);
  if (inmem (dest))
    operand (32, reg0, 1, 0);
  else
    operand (32, dest, 1, 0);
  outs (sep);

  if (inc != 0)
    outn ((long)inc);
  if (name (rmain.where_exp) != val_tag ||
      (no (rmain.where_exp) + rmain.where_off) != 0) {
    outs ("(");
    operand (32, rmain, 1, 0);
    outs (")");
  }
  outs ("(");
  operand (32, rind, 1, 0);
  if (sc != 1) {
    outs ("*");
    outn ((long)sc);
  };
  outs (")");
  outnl ();

  if (inmem (dest)) {
    invalidate_dest (reg0);
    end_contop ();
    move (slongsh, reg0, dest);
  }
  else
    end_contop ();

  return;
}

/* output the case switch jump and the jump table */
void caseins
    PROTO_N ( (sz, arg, min, max, v, exhaustive, in_eax, case_exp) )
    PROTO_T ( int sz X exp arg X int min X int max X int *v X int exhaustive X int in_eax X exp case_exp )
{
  int tab;
  int absent;
  where a;
  int need_label_flag=0;
  exp next= short_next_jump(case_exp);
  if (next != nilexp && name(next)==goto_tag)
  {
    exp lab=final_dest(pt(next));
    absent=ptno(pt(son(lab)));
  }
  else
  {
    absent = (exhaustive) ? -1 : next_lab ();
    need_label_flag=1;
  }

  tab = next_lab ();
  a = mw (arg, 0);

  if (inmem (mw (arg, 0)) || sz != 32) {
    if (!in_eax)
      change_var (slongsh, a, reg0);
    a = reg0;
  }

  /* the switch jump */
  out_switch_jump(tab, a, min);

  /* table of offsets */
  out_switch_table(tab, min, max, v, absent);

  if (!exhaustive && need_label_flag==1) {
    /*  label for default of switch; continue here */
    outs(local_prefix);
    outn ((long)absent);
    outs (":");
    outnl ();
#ifdef NEWDWARF
    START_BB ();
#endif
  };
  return;
}


void const_intnl
    PROTO_N ( (addr, lab, off) )
    PROTO_T ( int addr X int lab X int off )
{
  if (!addr)
    outs ("("); /* ACK indirect */

  outs(local_prefix);
  outn ((long)lab);
  if (off != 0) {
    outs ("+");
    outn ((long)off / 8);
  };

  if (!addr)
    outs (")"); /* ACK indirect */
  return;
}

void load_stack0
    PROTO_Z ()
{
  outs ("fld st(0)");
  outnl ();
  return;
}

void outbp
    PROTO_Z ()
{
  outs("ebp");
}

void set_stack_from_bp
    PROTO_Z ()
{
  outs (margin);
  outs (leal);
  outs (spx);
  outs("esp");
  outs (sep);
  outn((long)stack_dec/8);
  outs("-");
  outs(local_prefix);
  outs("disp");
  outn((long)crt_proc_id);
  outs ("(ebp)");
  outnl ();
  return;
}

void testah
    PROTO_N ( (mask) )
    PROTO_T ( int mask )
{
  outs("testb ah, ");
  outn((long)mask);
  outnl();
  return;
}

exp make_extn
    PROTO_N ( (n, s, v) )
    PROTO_T ( char * n X shape s X int v )
{
  dec * g = (dec *) (xmalloc (sizeof(dec)));
  exp id = getexp (s, nilexp, 1, nilexp, nilexp, 0, 0, ident_tag);
  exp nme = getexp (s, nilexp, 1, id, nilexp, 0, 0, name_tag);
  setglob (id);
  if (v) {
#if keep_PIC_vars
        setvar(id);
#else
        if (PIC_code)
          sh(id) = f_pointer(f_alignment(s));
        else
          setvar(id);
#endif
  }
  brog(id) = g;
  if (prefix_length != 0) {
    int nl = (int) strlen (n);
    int j;
    char * newn = (char *) xcalloc ((nl + prefix_length + 1), sizeof (char));
    for (j = 0; j < prefix_length; ++j)
      newn[j] = name_prefix[j];
    for (j = 0; j < nl; ++j)
      newn[j+prefix_length] = n[j];
    newn[nl+prefix_length] = 0;
    n = newn;
  }
  g -> dec_u.dec_val.dec_exp = id;
  g -> dec_u.dec_val.dec_id = n;
  g -> dec_u.dec_val.extnamed = 1;
  return (nme);
}



/* shift or rotate 64 bits in reg0/reg1 */
void rotshift64
    PROTO_N ( (shft, sig, wshift) )
    PROTO_T ( int shft X int sig X where wshift )
{
  if (name(wshift.where_exp) == val_tag) {	/* no of places is constant */
    int places = no (wshift.where_exp) + wshift.where_off;
    if (places >= 32) {
      places -= 32;
      switch (shft) {
	case 0:
	  if (places)
	    ins2 (shll, 8, 32, mw(zeroe,places), reg0);
	  move (ulongsh, reg0, reg1);
	  move (ulongsh, zero, reg0);
	  return;
	case 1:
	  move (ulongsh, reg1, reg0);
	  if (places)
	    ins2 ((sig ? sarl : shrl), 8, 32, mw(zeroe,places), reg0);
	  if (sig)
	    ins2 (sarl, 8, 32, mw(zeroe,31), reg1);
	  else
	    move (ulongsh, zero, reg1);
	  return;
	default: {
	  if (!places) {
	    ins2 (xchg, 32, 32, reg0, reg1);
	    return;
	  }
	  places = 32 - places;
	  shft = 5 - shft;	/* reverse rotate */
	}
      }
    };
    if (places == 0)
      return;
    switch (shft) {	/* between 1 and 31 places */
      case 0:
	ins3 (shldl, 8, 32, 32, mw(zeroe,places), reg0, reg1);
	ins2 (shll, 8, 32, mw(zeroe,places), reg0);
	return;
      case 1:
	ins3 (shrdl, 8, 32, 32, mw(zeroe,places), reg1, reg0);
	ins2 ((sig ? sarl : shrl), 8, 32, mw(zeroe,places), reg1);
	return;
      default: {
	char * dsh = (shft == 2 ? shrdl : shldl);
        extra_stack += 64;
	check_stack_max;
	ins0 (pushedx);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_push();
#endif
	ins0 (pusheax);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_push();
#endif
	ins3 (dsh, 8, 32, 32, mw(zeroe,places),
		reg1, mw(ind_sp.where_exp,-32));
	ins3 (dsh, 8, 32, 32, mw(zeroe,places),
		reg0, mw(ind_sp.where_exp,-64));
	ins0 (popeax);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_pop();
#endif
	ins0 (popedx);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest (ind_sp);
        extra_stack -= 64;
	return;
      }
    }
  };
  {				/* number of places in reg2 */
    int lablow = next_lab ();
    int labend = next_lab ();
    ins2 (cmpl, 32, 32, mw(zeroe,32), reg2);
    simple_branch (jl, lablow);
    switch (shft) {
      case 0:
	ins2 (subl, 32, 32, mw(zeroe,32), reg2);
	ins2 (shll, 8, 32, reg2, reg0);
	move (ulongsh, reg0, reg1);
	move (ulongsh, zero, reg0);
	break;
      case 1:
	ins2 (subl, 32, 32, mw(zeroe,32), reg2);
	move (ulongsh, reg1, reg0);
	ins2 ((sig ? sarl : shrl), 8, 32, reg2, reg0);
	if (sig)
	  ins2 (sarl, 8, 32, mw(zeroe,31), reg1);
	else
	  move (ulongsh, zero, reg1);
	break;
      default: {
	int labx = next_lab ();
	char * dsh = (shft == 2 ? shldl : shrdl);	/* reversed rotate */
	simple_branch (je, labx);
	ins2 (subl, 32, 32, mw(zeroe,64), reg2);
	ins1 (negl, 32, reg2);
        extra_stack += 64;
	check_stack_max;
	ins0 (pushedx);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_push();
#endif
	ins0 (pusheax);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_push();
#endif
	ins3 (dsh, 8, 32, 32, reg2, reg1, mw(ind_sp.where_exp,-32));
	ins3 (dsh, 8, 32, 32, reg2, reg0, mw(ind_sp.where_exp,-64));
	ins0 (popeax);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_pop();
#endif
	ins0 (popedx);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest (ind_sp);
        extra_stack -= 64;
	simple_branch (jmp, labend);
	simplest_set_lab (labx);
	ins2 (xchg, 32, 32, reg0, reg1);
      }
    }
    simple_branch (jmp, labend);
    simplest_set_lab (lablow);
    switch (shft) {	/* between 0 and 31 places */
      case 0:
	ins3 (shldl, 8, 32, 32, reg2, reg0, reg1);
	ins2 (shll, 8, 32, reg2, reg0);
	break;
      case 1:
	ins3 (shrdl, 8, 32, 32, reg2, reg1, reg0);
	ins2 ((sig ? sarl : shrl), 8, 32, reg2, reg1);
	break;
      default: {
	char * dsh = (shft == 2 ? shrdl : shldl);
        extra_stack += 64;
	check_stack_max;
	ins0 (pushedx);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_push();
#endif
	ins0 (pusheax);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_push();
#endif
	ins3 (dsh, 8, 32, 32, reg2, reg1, mw(ind_sp.where_exp,-32));
	ins3 (dsh, 8, 32, 32, reg2, reg0, mw(ind_sp.where_exp,-64));
	ins0 (popeax);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_pop();
#endif
	ins0 (popedx);
#ifdef NEWDWARF
	if (diagnose && dwarf2 && no_frame)
	  dw2_track_pop();
#endif
	invalidate_dest (ind_sp);
        extra_stack -= 64;
      }
    }
    simplest_set_lab (labend);
  };
  return;
}
