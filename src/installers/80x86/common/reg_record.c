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


/* 80x86/reg_record.c */

/**********************************************************************
$Author: pwe $
$Date: 1998/03/15 16:00:22 $
$Revision: 1.3 $

$Log: reg_record.c,v $
 * Revision 1.3  1998/03/15  16:00:22  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.2  1998/02/02  11:18:25  pwe
 * 80x86 shape_overlap correction
 *
 * Revision 1.1.1.1  1998/01/17  15:55:52  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/12/10  15:41:17  pwe
 * check condition at invalidate_dest
 *
 * Revision 1.3  1995/04/03  08:30:28  pwe
 * invalidate regs if overlap, eg if bitfield on byte boundaries
 *
 * Revision 1.2  1995/01/30  12:56:44  pwe
 * Ownership -> PWE, tidy banners
 *
 * Revision 1.1  1994/10/27  14:15:22  jmf
 * Initial revision
 *
 * Revision 1.1  1994/07/12  14:39:53  jmf
 * Initial revision
 *
**********************************************************************/



#include "config.h"
#include "common_types.h"
#include "operand.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "instr386.h"
#include "shapemacs.h"
#include "codermacs.h"
#include "flags.h"

#ifdef NEWDWARF
#include "dw2_extra.h"
#endif

#include "reg_record.h"


/* This collection of routines maintains a record of what is known to
   to be in each register during code production
*/

/* VARIABLES */
/* All variables initialised */

reg_record crt_reg_record;
				/* init by cproc */

/* PROCEDURES */

/* clear out all the register records */
void clear_reg_record
    PROTO_N ( (s) )
    PROTO_T ( regcell * s )
{
  int   i;
  for (i = 0; i < no_fixed_regs; ++i) {
    s[i].regcell_key = 4;
#ifdef NEWDWARF
    if (dwarf2) {
      dw_close_regassn (i, 0);
      dw_close_regassn (i, 1);
    }
#endif
  }
  return;
}

/* clear out the registers not preserved
   over procedure calls */
void clear_low_reg_record
    PROTO_N ( (s) )
    PROTO_T ( regcell * s )
{
  int   i;
  for (i = 0; i < no_fixed_regs; ++i) {
    s[i].regcell_key = 4;
#ifdef NEWDWARF
    if (dwarf2) {
      dw_close_regassn (i, 0);
      dw_close_regassn (i, 1);
    }
#endif
  }
  return;
}


/* true if changing d invalidates r */
static  int inval
    PROTO_N ( (d, r) )
    PROTO_T ( exp d X exp r )
{
  if ((d == nilexp || name (d) == cont_tag) &&
      (name (r) == cont_tag || (name (r) == name_tag && isglob (son (r)))))
    return (1);
  if ((name (r) == name_tag && !isvar (son (r))) ||
	name (r) == cont_tag)
    return (eq_where (mw (d, 0), mw (r, 0)));

  if (name (r) == reff_tag)
    return (inval (d, son (r)));

  if (name (r) == addptr_tag) {
    if (name (bro (son (r))) == offset_mult_tag)
      return (inval (d, son (r)) || inval (d, son (bro (son (r)))));
    return (inval (d, son (r)) || inval (d, bro (son (r))));
  };

  if (name (r) == ident_tag)
    return (inval (d, son (r)) || inval (d, bro (son (r))));

  return (0);
}

/* true if changing d invalidates r */
int invalidates
    PROTO_N ( (d, r) )
    PROTO_T ( exp d X exp r )
{
  if (name (r) == cont_tag || name (r) == ass_tag)
    return (inval (d, son (r)));
  return (0);
}

/* convert register mask to register number */
static int  get_regno
    PROTO_N ( (mask) )
    PROTO_T ( int mask )
{
  int   m = 1;
  int   res;
  for (res = 0; res < no_fixed_regs && (mask & m) == 0; res++)
    m = m + m;
  return (res);
}

/* if there is a register holding the same
   value as is in w, return this register
   (as a where), otherwise the where_exp
   field of the result will be nilexp */
where equiv_reg
    PROTO_N ( (w, sz) )
    PROTO_T ( where w X int sz )
{
  int   i;
  where res;
  res.where_exp = nilexp;

  if (w.where_off != 0)
    return (res);
  for (i = 0; i < no_fixed_regs; i++) {
    regcell * p = &crt_reg_record[i];
    if ((p -> regcell_key & 1) &&
	(sz == 0 || sz == p -> first_size) &&
	eq_where_exp (p -> first_dest, w.where_exp, 1, (sz==0))) {
#ifdef NEWDWARF
      if (dwarf2)
	dw_used_regassn (i, 0);
#endif
      return (reg_wheres[i]);
    }
    if ((p -> regcell_key & 2) &&
	(sz == 0 || sz == p -> second_size) &&
	eq_where_exp (p -> second_dest, w.where_exp, 1, (sz==0))) {
#ifdef NEWDWARF
      if (dwarf2)
	dw_used_regassn (i, 1);
#endif
      return (reg_wheres[i]);
    }
  };
  res.where_exp = nilexp;
  return (res);
}

static int is_aliased
    PROTO_N ( (dest) )
    PROTO_T ( exp dest )
{
  if (dest == nilexp)
    return 0;
  if (name (dest) != cont_tag &&
      name (dest) != ass_tag)
    return (0);

  if (name (son (dest)) == name_tag &&
      isvar (son (son (dest))) &&
      iscaonly (son (son (dest))))
    return (0);
  return (1);
}

static  int shape_overlap
    PROTO_N ( (e1, e2) )
    PROTO_T ( exp e1 X exp e2 )
{
  shape s1 = sh (e1);
  shape s2 = sh (e2);
  if (name (s1) <= doublehd && name (s1) > tophd && name (s2) == ptrhd)
    return (0);
  if (name (s2) <= doublehd && name (s2) > tophd && name (s1) == ptrhd)
    return (0);
  return (1);
}


/* make changes to the register record
   needed when dest receives an unknown
   value */
void invalidate_dest
    PROTO_N ( (dest) )
    PROTO_T ( where dest )
{
  exp d = dest.where_exp;
  int  regmask = (d == nilexp) ? 0 : (in_reg (d) & 0x7fffffff);
  int  regno;
  where weq;
  int   i;

	/* this repeats the condition state check at start of move,
	   in case contop has reset it */

  if ((cond1_set && (eq_where (dest, cond1) ||
	  invalidates (dest.where_exp, cond1.where_exp))) ||
      (cond2_set &&
	(eq_where (dest, cond2a) || eq_where (dest, cond2b) ||
	  invalidates (dest.where_exp, cond2a.where_exp) ||
	  invalidates (dest.where_exp, cond2b.where_exp)))) {
    cond1_set = 0;
    cond2_set = 0;
  };

  if (is_aliased (dest.where_exp)) {
    for (i = 0; i < no_fixed_regs; ++i) {
      regcell * pr = &crt_reg_record[i];
      switch (pr -> regcell_key) {
	case 1:
	  if (is_aliased (pr -> first_dest) &&
	      shape_overlap (dest.where_exp, pr -> first_dest)) {
	    pr -> regcell_key = 4;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 0);
#endif
	  }
	  break;
	case 2:
	  if (is_aliased (pr -> second_dest) &&
	      shape_overlap (dest.where_exp, pr -> second_dest)) {
	    pr -> regcell_key = 4;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 1);
#endif
	  }
	  break;
	case 3:
	  if (is_aliased (pr -> first_dest) &&
	      shape_overlap (dest.where_exp, pr -> first_dest)) {
	    pr -> regcell_key &= 2;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 0);
#endif
	  }
	  if (is_aliased (pr -> second_dest) &&
	      shape_overlap (dest.where_exp, pr -> second_dest)) {
	    pr -> regcell_key &= 1;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 1);
#endif
	  }
	  if (pr -> regcell_key == 0)
	    pr -> regcell_key = 4;
	default: ;
      };
    };
  };

  if (regmask) {
    regno = get_regno (regmask);
    if (regno < no_fixed_regs)
      crt_reg_record[regno].regcell_key = 4;
  };

  if (regmask || d == nilexp) {
    for (i = 0; i < no_fixed_regs; ++i) {
      regcell * pr = &crt_reg_record[i];
      switch (pr -> regcell_key) {
	case 1:
	  if (invalidates (d, pr -> first_dest)) {
	    pr -> regcell_key = 4;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 0);
#endif
	  }
	  break;
	case 2:
	  if (invalidates (d, pr -> second_dest)) {
	    pr -> regcell_key = 4;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 1);
#endif
	  }
	  break;
	case 3:
	  if (invalidates (d, pr -> first_dest)) {
	    pr -> regcell_key &= 2;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 0);
#endif
	  }
	  if (invalidates (d, pr -> second_dest)) {
	    pr -> regcell_key &= 1;
#ifdef NEWDWARF
	    if (dwarf2)
	      dw_close_regassn (i, 1);
#endif
	  }
	  if (pr -> regcell_key == 0)
	    pr -> regcell_key = 4;
	default: ;
      };
    };
    return;
  };
#ifdef NEWDWARF
  dw_ignore_used_regassn = 1;
#endif
  while (1) {
    weq = equiv_reg (dest, 0);
    if (weq.where_exp == nilexp)
      break;
    regmask = (in_reg (weq.where_exp) & 0x7fffffff);
    regno = get_regno (regmask);
    if (regno < no_fixed_regs)
      crt_reg_record[regno].regcell_key = 4;
  };
#ifdef NEWDWARF
  dw_ignore_used_regassn = 0;
#endif
  return;
}

/* from is being moved to to. Make changes
   to the register records accordingly */
void move_reg
    PROTO_N ( (from, to, sha) )
    PROTO_T ( where from X where to X shape sha )
{
  int  regmask_to = in_reg (to.where_exp);
  int  regmask_from = in_reg (from.where_exp);
  int sz = shape_size(sha);
  if (name(sha) == shrealhd)
    return;
  if (regmask_from != 0 && regmask_to != 0)
    return;
  if ((regmask_from & (int)0x80000000) || (regmask_to & (int)0x80000000))
    return;
  if (from.where_off != 0 || to.where_off != 0)
    return;
  if (regmask_to && invalidates (to.where_exp, from.where_exp))
    return;
  if (regmask_to && regmask_to < 64) {
    int   regno_to = get_regno (regmask_to);
    regcell * p = &crt_reg_record[regno_to];
    switch (p -> regcell_key) {
      case 1:
	{
	  p -> regcell_key = 3;
	  p -> second_dest = from.where_exp;
	  p -> second_size = sz;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_init_regassn (regno_to, 1);
#endif
	  break;
	};
      case 2:
	{
	  p -> regcell_key = 3;
	  p -> first_dest = from.where_exp;
	  p -> first_size = sz;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_init_regassn (regno_to, 0);
#endif
	  break;
	};
      case 3:
	break;
      default:
	{
	  p -> regcell_key = 1;
	  p -> first_dest = from.where_exp;
	  p -> first_size = sz;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_init_regassn (regno_to, 0);
#endif
	  break;
	};
    };
  };
  if (regmask_from && regmask_from < 64) {
    int   regno_from = get_regno (regmask_from);
    regcell * p = &crt_reg_record[regno_from];
    switch (p -> regcell_key) {
      case 1:
	{
	  p -> regcell_key = 3;
	  p -> second_dest = to.where_exp;
	  p -> second_size = sz;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_init_regassn (regno_from, 1);
#endif
	  break;
	};
      case 2:
	{
	  p -> regcell_key = 3;
	  p -> first_dest = to.where_exp;
	  p -> first_size = sz;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_init_regassn (regno_from, 0);
#endif
	  break;
	};
      case 3:
	break;
      default:
	{
	  p -> regcell_key = 1;
	  p -> first_dest = to.where_exp;
	  p -> first_size = sz;
#ifdef NEWDWARF
	  if (dwarf2)
	    dw_init_regassn (regno_from, 0);
#endif
	  break;
	};
    };
  };
}
