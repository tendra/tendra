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


/* 80x86/translate.c */

/**********************************************************************
$Author$
$Date$
$Revision$*/



#include "config.h"
#include "common_types.h"
#include "installglob.h"
#include "tags.h"
#include "exp.h"
#include "expmacs.h"
#include "optimise.h"
#include "flags.h"
#include "coder.h"
#include "shapemacs.h"
#include "instr.h"
#include "out.h"
#include "scan2.h"
#include "weights.h"
#include "instr386.h"
#include "operand.h"
#include "machine.h"
#include "codermacs.h"
#include "flpt.h"
#include "flpttypes.h"
#include "localflags.h"
#include "localtypes.h"
#include "diag_fns.h"
#include "assembler.h"
#include "cproc.h"
#include "evaluate.h"
#include "externs.h"
#include "readglob.h"
#include "tv_callees.h"
#include "basicread.h"
#ifdef NEWDWARF
#include "dw2_iface.h"
#include "dw2_config.h"
#endif


#define ptg(x) ((x)->ptf.glob)		/* addition to expmacs */


static exp delayed_const_list = nilexp;

static int 
const_ready(exp e)
{
  unsigned char  n = name (e);
  if (n == env_size_tag)
    return (brog(son(son(e))) -> dec_u.dec_val.processed);
  if (n == env_offset_tag)
    return (name(son(e)) == 0);
  if (n == name_tag || son(e) == nilexp)
    return 1;
  e = son(e);
  while (!last(e)) {
    if (!const_ready(e))
      return 0;
    e = bro(e);
  }
  return (const_ready(e));
}

static void 
eval_if_ready(exp t, int now)
{
  if (now || const_ready(son(t))) {
    if (isglob(t)) {
	dec * d = ptg(t);
	if (!writable_strings &&
	    (!isvar (t) || (d -> dec_u.dec_val.acc & f_constant)) &&
	    !PIC_code) {
          out_readonly_section();
	  outnl ();
#ifdef NEWDWARF
	  if (dwarf2)
	    note_ro (d -> dec_u.dec_val.dec_id);
#endif
	}
	else {
	  if (do_prom)
	    failer ("prom data");
	  outs (".data");
	  outnl ();
#ifdef NEWDWARF
	  if (dwarf2)
	    note_data (d -> dec_u.dec_val.dec_id);
#endif
	};
	evaluate (son(t),
                  (-1),
                  d -> dec_u.dec_val.dec_id,
		  (!isvar (t)),
                  (int)(d -> dec_u.dec_val.extnamed),
                  d -> dec_u.dec_val.diag_info);
    }
    else {
	if (!writable_strings && name (son (t)) != res_tag) {
             out_readonly_section();
	     outnl ();
	   }
	else {
	     if (do_prom)
	       failer ("prom data");
	     outs (".data");
	     outnl ();
	   };
	evaluate (son (t), no (t), (char *) 0,
	        (name (son (t)) != res_tag), 0, (diag_global*)0);
    }
    retcell (t);
  }
  else {
    bro(t) = delayed_const_list;
    delayed_const_list = t;
  }
  return;
}


/* PROCEDURES */

void 
make_code(dec *my_def)
{
  exp tg = my_def -> dec_u.dec_val.dec_exp;
  char *id = my_def -> dec_u.dec_val.dec_id;

  if (son(tg) != nilexp && shape_size(sh(son(tg))) == 0 && name(son(tg)) == asm_tag) {
    ash stack;
    stack.ashsize = stack.ashalign = 0;
    if (props(son(tg)) != 0)
      failer ("~asm not in ~asm_sequence");
    check_asm_seq (son(son(tg)), 1);
    outs (".text");
    coder (zero, stack, son(tg));
    outnl ();
  }

  if (son (tg) != nilexp && (my_def -> dec_u.dec_val.extnamed || no(tg) != 0)) {
    if (name (son (tg)) == proc_tag || name (son (tg)) == general_proc_tag) {
      if (strncmp("__I.TDF", id+prefix_length, 7)==0) {
	out_initialiser (id);
	set_proc_uses_external (son (tg));	/* for PIC_code, should be done in install_fns? */
      }
      outs (".text");
      outnl ();
      if (isvar(tg)) {
        char * newid = make_local_name();
	if (my_def -> dec_u.dec_val.extnamed) {
	  my_def -> dec_u.dec_val.extnamed = 0;
	  outs(".globl ");
	  outs(id);
	  outnl();
	}
	dot_align(4);
        outs(id);
	outs(":");
	outnl();
	outlong();
	outs(newid);
	outnl();
	id = newid;
	my_def -> dec_u.dec_val.extnamed = 0;
      }
      my_def -> dec_u.dec_val.index =	/* for use in constant evaluation */
	cproc (son (tg), id, (-1), (int)(my_def -> dec_u.dec_val.extnamed),
                my_def -> dec_u.dec_val.diag_info);
      while (const_list != nilexp) {
	/* put in the constants required by the procedure */
	exp t = const_list;
	const_list = bro (const_list);
	eval_if_ready(t,0);
      };
    }
    else {			/* global values */
     diag_global * diag_props = my_def -> dec_u.dec_val.diag_info;

      if (shape_size(sh(son(tg))) == 0) {;
	if (my_def -> dec_u.dec_val.extnamed) {
	  outs(".globl ");
	  outs(id);
	  outnl();
	}
	else
	if (issol86) {
	  outs(".local ");
	  outs(id);
	  outnl();
	}
#if islinux || isfreebsd
	outs(".data");
	outnl();
	outs(id);
	outs(":");
	outnl();
#else
	outs(".set ");
	outs(id);
	outs(",");
	outn((long)0);
	outnl();
#endif
      }
      else
      if (!PIC_code && !isvar(tg) && name(son(tg)) == null_tag &&
	  name(sh(son(tg))) == prokhd) {
	if (my_def -> dec_u.dec_val.extnamed) {
	  outs(".globl ");
	  outs(id);
	  outnl();
	}
	else
	if (issol86) {
	  outs(".local ");
	  outs(id);
	  outnl();
	}
	outs(".set ");
	outs(id);
	outs(",");
	outn((long)no(son(tg)));
	outnl();
      }
      else {
      if (!my_def -> dec_u.dec_val.isweak &&
          is_comm(son(tg)))
       {
	 int is_ext = (my_def -> dec_u.dec_val.extnamed);
         if (diag_props)
#ifdef NEWDWARF
           DIAG_VAL_BEGIN (diag_props, is_ext, -1, id);
#else
           diag_val_begin(diag_props, is_ext, -1, id);
#endif
	 if (name(son(tg)) == clear_tag && no(son(tg)) == -1) {
				/* prom global data */
	   if (is_ext) {
	     outs(".globl ");
	     outs(id);
	     outnl();
	   }
           out_bss(id, sh(son(tg)));
#ifdef NEWDWARF
	   if (dwarf2)
	     note_data (id);
#endif
	 }
	 else
	 if (is_ext)
           out_dot_comm(id, sh(son(tg)));
	 else
           out_dot_lcomm(id, sh(son(tg)));
         if (diag_props) {
#ifdef NEWDWARF
           DIAG_VAL_END (diag_props);
#else
           diag_val_end(diag_props);
#endif
	 }
       }

      else {			/* global values */

	exp t = getexp (f_bottom, nilexp, 0, son(tg), nilexp, props(tg), -1, 0);
	ptg(t) = my_def;
	eval_if_ready (t, 0);

      };
     };
    };
  };

  if (son(tg) != nilexp)  {
     my_def -> dec_u.dec_val.processed = 1;
  };
  return;
}

void 
mark_unaliased(exp e)
{
  exp p = pt (e);
  int ca = 1;
  while (p != nilexp && ca) {
#ifdef NEWDIAGS
    if ((bro(p) == nilexp ||
#else
    if (bro(p) == nilexp ||
#endif
        (!(last (p) && name (bro (p)) == cont_tag) &&
	 !(!last (p) && last (bro (p)) &&
                 name (bro (bro (p))) == ass_tag)))
#ifdef NEWDIAGS
	&& !isdiaginfo(p))
#endif
      ca = 0;
    p = pt (p);
  };
  if (ca)
    setcaonly (e);
  return;
}


void 
translate_capsule(void)
{
  dec * my_def;

#ifdef STABS
#ifdef NEWDWARF
  if (diagnose && !dwarf2)
#else
  if (diagnose)
#endif
    init_stab_aux ();
#endif


  my_def = top_def;
  while (my_def != (dec *) 0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (PIC_code) {
      exp idval = son(crt_exp);
      if (!(my_def -> dec_u.dec_val.dec_var) &&
	   ( idval == nilexp || ( name(idval) != val_tag && name(idval) != real_tag &&
		name(idval) != null_tag )	/* optimised out in opt_all_exps/checkext */
	   ) &&
	   (name(sh(crt_exp)) != prokhd ||
		( idval != nilexp && name(idval) != null_tag &&
		  name(idval) != proc_tag && name(idval) != general_proc_tag )
	   ) )
      {
		/* make variable, and change all uses to contents */
	exp p = pt(crt_exp);
	if (my_def -> dec_u.dec_val.extnamed)
	  sh(crt_exp) = f_pointer(f_alignment(sh(crt_exp)));
	else
	  setvar(crt_exp);
	while (p != nilexp) {
	  exp np = pt(p);
	  exp* ptr = refto (father(p), p);
	  exp c = getexp (sh(p), bro(p), last(p), p, nilexp, 0, 0, cont_tag);
	  setfather (c, p);
	  if (no(p) != 0) {
	    exp r = getexp (sh(p), c, 1, p, nilexp, 0, no(p), reff_tag);
	    no(p) = 0;
	    son(c) = r;
	    setfather (r, p);
	  }
	  *ptr = c;
	  p = np;
	}
      }
    }
    else {	/* !PIC_code; make indirect global idents direct */
      exp tg = crt_exp;
      while (!isvar(tg) && son(tg) != nilexp && name(son(tg)) == name_tag && no(son(tg)) == 0)
	tg = son(son(tg));
      if (tg != crt_exp) {
	exp p = pt(crt_exp);
	while (p != nilexp) {
	  exp np = pt(p);
	  if (son(p) != crt_exp)
	    failer ("not simple name");
	  son(p) = tg;
	  pt(p) = pt(tg);
	  pt(tg) = p;
	  ++no(tg);
	  p = np;
	}
	pt(crt_exp) = nilexp;
	no(crt_exp) = 0;
      }
    };
    my_def = my_def -> def_next;
  }

  opt_all_exps ();

  transform_var_callees ();

      /* mark static unaliased */
    my_def = top_def;
    while (my_def != (dec *) 0) {
      exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
      if (son (crt_exp) != nilexp &&
	  !my_def -> dec_u.dec_val.extnamed &&
   	  isvar (crt_exp))
        mark_unaliased (crt_exp);
      my_def = my_def -> def_next;
    };

  /* compile procedures, evaluate constants, put in the .comm entries for
     undefined objects */

#ifdef NEWDWARF
  if (dwarf2) {
    outs (".text\n");
    dwarf2_prelude ();
  }
#endif

  my_def = top_def;

  while (my_def != (dec *) 0) {
    if (!my_def -> dec_u.dec_val.processed)
       make_code (my_def);
    my_def = my_def -> def_next;
  };

  while (delayed_const_list != nilexp) {
    exp t = delayed_const_list;
    delayed_const_list = bro (delayed_const_list);
    eval_if_ready(t,1);
  }

  outs (".text\n");
#ifdef NEWDWARF
  if (dwarf2) {
    dwarf2_postlude ();
  }
#endif
  return;

}

void 
translate_tagdef(void)
{
  return;
}

void 
translate_unit(void)
{
  return;
}

