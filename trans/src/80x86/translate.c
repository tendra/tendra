/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <local/diag_config.h>
#include <local/expmacs.h>
#include <local/out.h>
#include <local/codermacs.h>
#include <local/localflags.h>
#include <local/localtypes.h>

#ifdef NEWDWARF
#include <local/dw2_config.h>
#endif

#include <reader/externs.h>
#include <reader/readglob.h>
#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/shapemacs.h>
#include <construct/machine.h>
#include <construct/flpt.h>
#include <construct/flpttypes.h>

#include <main/flags.h>

#ifdef NEWDIAGS
#include <newdiag/diag_fns.h>
#else
#include <diag/diag_fns.h>
#endif

#include <refactor/optimise.h>

#include "coder.h"
#include "instr.h"
#include "scan2.h"
#include "weights.h"
#include "instr386.h"
#include "operand.h"
#include "assembler.h"
#include "cproc.h"
#include "evaluate.h"
#include "tv_callees.h"

#ifdef NEWDWARF
#include <dwarf2/dw2_iface.h>
#endif


#define ptg(x) ((x)->ptf.glob)		/* addition to expmacs */


static exp delayed_const_list = NULL;

static int const_ready
(exp e)
{
  unsigned char  n = name(e);
  if (n == env_size_tag)
    return brog(son(son(e))) -> dec_u.dec_val.processed;
  if (n == env_offset_tag)
    return name(son(e)) == 0;
  if (n == name_tag || son(e) == NULL)
    return 1;
  e = son(e);
  while (!last(e)) {
    if (!const_ready(e))
      return 0;
    e = bro(e);
  }
  return const_ready(e);
}

static void eval_if_ready
(exp t, int now)
{
  if (now || const_ready(son(t))) {
    if (isglob(t)) {
	dec * d = ptg(t);
	if (!writable_strings &&
	   (!isvar(t) || (d -> dec_u.dec_val.acc & f_constant)) &&
	    !PIC_code) {
          out_readonly_section();
	  outnl();
#ifdef NEWDWARF
	  if (diag == DIAG_DWARF2)
	    note_ro(d -> dec_u.dec_val.dec_id);
#endif
	}
	else {
	  if (do_prom)
	    failer("prom data");
	  outs(".data");
	  outnl();
#ifdef NEWDWARF
	  if (diag == DIAG_DWARF2)
	    note_data(d -> dec_u.dec_val.dec_id);
#endif
	};
	evaluate(son(t),
                 (-1),
                  d -> dec_u.dec_val.dec_id,
		 (!isvar(t)),
                 (int)(d -> dec_u.dec_val.extnamed),
                  d -> dec_u.dec_val.diag_info);
    }
    else {
	if (!writable_strings && name(son(t))!= res_tag) {
             out_readonly_section();
	     outnl();
	   }
	else {
	     if (do_prom)
	       failer("prom data");
	     outs(".data");
	     outnl();
	   };
	evaluate(son(t), no(t), (char *)0,
	       (name(son(t))!= res_tag), 0,(diag_global*)0);
    }
    retcell(t);
  }
  else {
    bro(t) = delayed_const_list;
    delayed_const_list = t;
  }
  return;
}


/* PROCEDURES */

void make_code
(dec * my_def)
{
  exp tg = my_def -> dec_u.dec_val.dec_exp;
  char *id = my_def -> dec_u.dec_val.dec_id;

  if (son(tg)!= NULL && shape_size(sh(son(tg))) == 0 && name(son(tg)) == asm_tag) {
    ash stack;
    stack.ashsize = stack.ashalign = 0;
    if (props(son(tg))!= 0)
      failer("~asm not in ~asm_sequence");
    check_asm_seq(son(son(tg)), 1);
    outs(".text");
    coder(zero, stack, son(tg));
    outnl();
  }

  if (son(tg)!= NULL && (my_def -> dec_u.dec_val.extnamed || no(tg)!= 0)) {
    if (name(son(tg)) == proc_tag || name(son(tg)) == general_proc_tag) {
      if (dyn_init && strncmp("__I.TDF", id+prefix_length, 7) ==0) {
	out_initialiser(id);
	set_proc_uses_external (son (tg));	/* for PIC_code, should be done in install_fns? */
      }
      outs(".text");
      outnl();
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
	cproc(son(tg), id,(-1), (int)(my_def -> dec_u.dec_val.extnamed),
                my_def -> dec_u.dec_val.diag_info);
      while (const_list != NULL) {
	/* put in the constants required by the procedure */
	exp t = const_list;
	const_list = bro(const_list);
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
	if (assembler == ASM_SUN) {
		outs(".local ");
		outs(id);
		outnl();
	} else if (assembler == ASM_GAS) {
		outs(".data");
		outnl();
		outs(id);
		outs(":");
		outnl();
	} else {
		outs(".set ");
		outs(id);
		outs(",");
		outn((long)0);
		outnl();
	}
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
	if (assembler == ASM_SUN) {
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
           DIAG_VAL_BEGIN(diag_props, is_ext, -1, id);
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
	   if (diag == DIAG_DWARF2)
	     note_data(id);
#endif
	 }
	 else
	 if (is_ext)
           out_dot_comm(id, sh(son(tg)));
	 else
           out_dot_lcomm(id, sh(son(tg)));
         if (diag_props) {
#ifdef NEWDWARF
           DIAG_VAL_END(diag_props);
#else
           diag_val_end(diag_props);
#endif
	 }
       }

      else {			/* global values */

	exp t = getexp(f_bottom, NULL, 0, son(tg), NULL, props(tg), -1, 0);
	ptg(t) = my_def;
	eval_if_ready(t, 0);

      };
     };
    };
  };

  if (son(tg)!= NULL) {
     my_def -> dec_u.dec_val.processed = 1;
  };
  return;
}

void mark_unaliased
(exp e)
{
  exp p = pt(e);
  int ca = 1;
  while (p != NULL && ca) {
#ifdef NEWDIAGS
    if ((bro(p) == NULL ||
#else
    if (bro(p) == NULL ||
#endif
       (!(last(p) && name(bro(p)) == cont_tag) &&
	 !(!last(p) && last(bro(p)) &&
                 name(bro(bro(p))) == ass_tag)))
#ifdef NEWDIAGS
	&& !isdiaginfo(p))
#endif
      ca = 0;
    p = pt(p);
  };
  if (ca)
    setcaonly(e);
  return;
}


void translate_capsule
(void)
{
  dec * my_def;

#ifdef STABS
#ifdef NEWDWARF
  if (diag != DIAG_NONE && diag != DIAG_DWARF2)
#else
  if (diag != DIAG_NONE)
#endif
    init_stab_aux();
#endif


  my_def = top_def;
  while (my_def != (dec *)0) {
    exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
    if (PIC_code) {
      exp idval = son(crt_exp);
      if (!(my_def -> dec_u.dec_val.dec_var) &&
	  (idval == NULL || (name(idval)!= val_tag && name(idval)!= real_tag &&
		name(idval) != null_tag )	/* optimised out in opt_all_exps/refactor_ext */
	  ) &&
	  (name(sh(crt_exp))!= prokhd ||
		(idval != NULL && name(idval)!= null_tag &&
		  name(idval)!= proc_tag && name(idval)!= general_proc_tag)
	  ))
      {
		/* make variable, and change all uses to contents */
	exp p = pt(crt_exp);
	if (my_def -> dec_u.dec_val.extnamed)
	  sh(crt_exp) = f_pointer(f_alignment(sh(crt_exp)));
	else
	  setvar(crt_exp);
	while (p != NULL) {
	  exp np = pt(p);
	  exp* ptr = refto(father(p), p);
	  exp c = getexp(sh(p), bro(p), last(p), p, NULL, 0, 0, cont_tag);
	  setfather(c, p);
	  if (no(p)!= 0) {
	    exp r = getexp(sh(p), c, 1, p, NULL, 0, no(p), reff_tag);
	    no(p) = 0;
	    son(c) = r;
	    setfather(r, p);
	  }
	  *ptr = c;
	  p = np;
	}
      }
    }
    else {	/* !PIC_code; make indirect global idents direct */
      exp tg = crt_exp;
      while (!isvar(tg) && son(tg)!= NULL && name(son(tg)) == name_tag && no(son(tg)) == 0)
	tg = son(son(tg));
      if (tg != crt_exp) {
	exp p = pt(crt_exp);
	while (p != NULL) {
	  exp np = pt(p);
	  if (son(p)!= crt_exp)
	    failer("not simple name");
	  son(p) = tg;
	  pt(p) = pt(tg);
	  pt(tg) = p;
	  ++no(tg);
	  p = np;
	}
	pt(crt_exp) = NULL;
	no(crt_exp) = 0;
      }
    };
    my_def = my_def -> def_next;
  }

  opt_all_exps();

  transform_var_callees();

      /* mark static unaliased */
    my_def = top_def;
    while (my_def != (dec *)0) {
      exp crt_exp = my_def -> dec_u.dec_val.dec_exp;
      if (son(crt_exp)!= NULL &&
	  !my_def -> dec_u.dec_val.extnamed &&
   	  isvar(crt_exp))
        mark_unaliased(crt_exp);
      my_def = my_def -> def_next;
    };


    extra_stack = 0;
    init_weights();
    initzeros();
    const_list = NULL;


#ifdef NEWDWARF
    if (diag == DIAG_DWARF2)
        init_dwarf2();
    else
#endif
        if (diag != DIAG_NONE)
            out_diagnose_prelude();

#ifdef NEWDWARF
    if (dump_abbrev) {
        outs(".text\n");
        do_abbreviations();
        dwarf2_prelude();
        make_dwarf_common();
        dwarf2_postlude();
    }
#endif



  /* compile procedures, evaluate constants, put in the .comm entries for
     undefined objects */

#ifdef NEWDWARF
  if (diag == DIAG_DWARF2) {
    outs(".text\n");
    dwarf2_prelude();
  }
#endif

  my_def = top_def;

  while (my_def != (dec *)0) {
    if (!my_def -> dec_u.dec_val.processed)
       make_code(my_def);
    my_def = my_def -> def_next;
  };

  while (delayed_const_list != NULL) {
    exp t = delayed_const_list;
    delayed_const_list = bro(delayed_const_list);
    eval_if_ready(t,1);
  }

  outs(".text\n");
#ifdef NEWDWARF
  if (diag == DIAG_DWARF2) {
    dwarf2_postlude();
  }
#endif
  return;

}

void translate_tagdef
(void)
{
  return;
}

void translate_unit
(void)
{
  return;
}
