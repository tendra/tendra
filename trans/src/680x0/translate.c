/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <local/szs_als.h>

#include <reader/exp.h>

#include <construct/exp.h>
#include <construct/installglob.h>
#include <construct/shape.h>
#include <construct/machine.h>
#include <construct/tags.h>

#include <main/flags.h>

#include <refactor/optimise.h>

#include "instrs.h"
#include "evaluate.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "weights.h"
#include "mach.h"
#include "where.h"
#include "coder.h"
#include "codex.h"
#include "output.h"
#include "tests.h"
#include "utility.h"
#include "xdb_basics.h"
#include "localexpmacs.h"
#include "assembler.h"

extern dec *sort_decs(dec *);
static void output_all_exps(void);

/*
    INCLUDE DEBUGGING ROUTINES

    These are used to aid in debugging.

*/
#ifdef EBUG
/*
#include <misc/debug>
*/
void breakpoint(void) {}
#endif

#ifndef tdf3
#include "general_proc.h"
#include "68k_globals.h"
int need_dummy_double = 0;
#endif

/*
    EXTERNAL POSITIONS
*/

static long crt_ext_off = 64;
static long crt_ext_pt = 10;


/*
    MARK AN EXPRESSION AS BEING STATIC AND UNALIASED
*/

static void mark_unaliased
(exp e)
{
    exp p = pt(e);
    bool ca = 1;
    while (p != NULL && ca) {
	exp q = bro(p);
	if (q == NULL) {
	    ca = 0;
	} else if (!(last(p) && name(q) == cont_tag) &&
		    !(!last(p) && last(q) &&
		       name(bro(q)) == ass_tag)) {
	    ca = 0;
	}
	p = pt(p);
    }
    if (ca)setcaonly(e);
    return;
}


/*
    PROCESS THE TDF

    This routine gets all the TDF read into the correct operand form
    and applies the dead variable and register allocation analysis.
*/

void
translate_capsule(void)
{
    dec *d;

    /* Fix procedure handling (copied from trans386) */
    d = top_def;
#if 0
    while (d != (dec *)0) {
    exp crt_exp = d -> dec_u.dec_val.dec_exp;
    exp idval;
      if (!(d -> dec_u.dec_val.dec_var) && (name(sh(crt_exp))!= prokhd ||
          (idval = son(crt_exp),
             idval != NULL && name(idval)!= null_tag &&
               name(idval)!= proc_tag && name(idval)!= general_proc_tag))) {
	/* make variable, and change all uses to contents */
        exp p = pt(crt_exp);
        if (d -> dec_u.dec_val.extnamed)
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
      d = d->def_next;
    }
#endif


    make_transformations();

#ifndef EBUG
    opt_all_exps();
#endif

    /* Mark static unaliases declarations */
    if (!separate_units) {
	for (d = top_def; d; d = d->def_next) {
	    exp c = d->dec_u.dec_val.dec_exp;
	    if (son(c)!= NULL &&
		 !(d->dec_u.dec_val.extnamed) && isvar(c)) {
		mark_unaliased(c);
	    }
	}
    }

    /* Mark locations for all globals */
    for (d = top_def; d; d = d->def_next) {
	if (d->dec_u.dec_val.processed) {
	    exp c = d->dec_u.dec_val.dec_exp;
	    ptno(c) = crt_ext_pt++;
	    no(c) = crt_ext_off;
	    crt_ext_off += shape_size(d->dec_u.dec_val.dec_shape);
	}
    }


    /* Set up alignment rules */
    double_align = DBL_ALIGN;
    param_align = PARAM_ALIGN;
    stack_align = STACK_ALIGN;

    diagnose_registers = 0;

    MAX_BF_SIZE = (cconv != CCONV_HP ? MAX_BF_SIZE_CC : MAX_BF_SIZE_GCC);

    /* Call initialization routines */
    init_instructions();
    init_weights();
    init_wheres();

    /* Decode, optimize and process the input TDF */
    init_output();
    area(ptext);

    if (diag != DIAG_NONE) {
        diag_prologue();
    }


    /* Output all code */
    output_all_exps();

    return;
}


/*
    TRANSLATE A SINGLE TAG DEFINITION
*/

void translate_tagdef
(void)
{
    return;
}


/*
    TRANSLATE A SINGLE UNIT
*/

void translate_unit
(void)
{
    if (separate_units) {
	dec *d;
	translate_capsule();
	d = top_def;
	while (d) {
	    exp c = d->dec_u.dec_val.dec_exp;
	    no(c) = 0;
	    pt(c) = NULL;
	    d = d->def_next;
	}
	crt_repeat = NULL;
	repeat_list = NULL;
    }
    return;
}


/*
    ENCODE A PROCEDURE

    The procedure with declaration d, name id, definition c and body s
    is encoded.
*/

static void code_proc
(dec *d, char *id, exp c, exp s)
{
    diag_global *di = d->dec_u.dec_val.diag_info;
    int reg_res = (has_struct_res(s)? 0 : 1);
    int is_ext = (d->dec_u.dec_val.extnamed ? 1 : 0);

    area(ptext);

    cur_proc_dec = d;
    cur_proc_callees_size = 0;
    cur_proc_has_vcallees = 0;

    /* Code procedure body */
#if 0
    if (name(s) == proc_tag)
    cproc(s, id, -1, is_ext, reg_res, di);
    else
#endif
    gcproc(s, id, -1, is_ext, reg_res, di);


    d -> dec_u.dec_val.index = cur_proc_env_size ; /* for use in constant evaluation */

    output_env_size(d, cur_proc_env_size);
}


/*
    ENCODE A CONSTANT

    The constant with declaration d, name id, definition c and body s
    is encoded.
*/

static void code_const
(dec *d)
{
   exp c = d->dec_u.dec_val.dec_exp;
   exp s = son(c);
   char *id = d->dec_u.dec_val.dec_id;

   diag_global *di = d->dec_u.dec_val.diag_info;
   area(isvar(c)? pdata : ptext);
   if (!no_align_directives) {
     make_instr(m_as_align4, NULL, NULL, 0);
   }
   evaluate(s, -1L , id, !isvar(c), 1, di);
}


/*
    ENCODE THE CONSTANTS IN const_list

    All auxiliary constants are formed into a list, const_list.  This
    routine applies evaluate to each element of this list.
*/

static void code_const_list
(void)
{
    while (const_list != NULL) {
	exp t = const_list;
	exp s = son(t);
	bool b = (name(s)!= res_tag);
	const_list = bro(const_list);
	if (name(s) == proc_tag || name(s) == general_proc_tag) {
	    char *id = alloc_nof(char, 30);
	    sprintf(id, "%s%ld", local_prefix, no(t));
	    gcproc(s, NULL, no(t), 0, 1, NULL);
	} else {
	    area(b ? pdata : ptext);
	    evaluate(s, no(t), NULL, b, 0, NULL);
	}
    }
    return;
}

/*
   CONST_READY

   Returns TRUE if it is possible to evaluate the value of the constant now
*/

static int const_ready
(exp e)
{
  unsigned char  n = name(e);
  if (n == env_size_tag)
    return brog(son(son(e))) -> dec_u.dec_val.processed;
  if (n == env_offset_tag)
    return ismarked(son(e));
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

typedef struct delayedconst{
   dec* This;
   struct delayedconst* next;
} delayed_const;

static delayed_const* delayed_const_list = 0;

static void eval_if_ready
(dec *d)
{
   exp c = d->dec_u.dec_val.dec_exp;
   if (const_ready(c)) {
      code_const(d);
   }
   else {
      delayed_const* p = (delayed_const*)xmalloc(sizeof(delayed_const));
      p->This = d;
      p->next = delayed_const_list;
      delayed_const_list = p;
   }
}

void eval_delayed_const_list
(void)
{
   delayed_const* p;
   bool done = 0;
   while (! done) {
      done = 1;
      for (p = delayed_const_list; p; p = p->next) {
         dec* d = p->This;
         if (!d->dec_u.dec_val.processed) {
            exp c = d->dec_u.dec_val.dec_exp;
            if (const_ready(c)) {
               code_const(d);
               d->dec_u.dec_val.processed = 1;
            }
            done = 0;
         }
      }
   }
}


/*
    OUTPUT ALL THE ENCODED EXPRESSIONS

    This routine scans through all the declarations encoding suitably.
*/

static void output_all_exps
(void)
{
    dec *d = top_def;
    if (diag != DIAG_NONE) d = sort_decs(d);

    area(ptext);

    /* Clear any existing output */
    output_all();
    free_all_ins();

    /* Scan through the declarations */
    while (d) {

	if (!d->dec_u.dec_val.processed) {
	    exp c = d->dec_u.dec_val.dec_exp;
	    exp s = son(c);
	    char *id = d->dec_u.dec_val.dec_id;

	    init_output();

	    if (s != NULL) {
		if (name(s) == proc_tag ||
                    name(s) == general_proc_tag) {
		    code_proc(d, id, c, s);
		    code_const_list();
                    d->dec_u.dec_val.processed = 1;
		} else {
		    eval_if_ready(d);
		    code_const_list();
		}
	    } else {
		shape sha = d->dec_u.dec_val.dec_shape;
		long sz = round(shape_size(sha) / 8, 4);
		area(ptext);
		if (!is_local(id) && isvar(c) &&
		     varsize(sha) && !reserved(id)) {
		    if (sz) {
			mach_op *op1 = make_extern_data(id, 0);
			mach_op *op2 = make_int_data(sz);
			make_instr(m_as_common, op1, op2, 0);
		    }
		} else {
		    if (is_local(id) && no(c)) {
			mach_op *op1 = make_extern_data(id, 0);
			mach_op *op2 = make_int_data(sz);
			make_instr(m_as_local, op1, op2, 0);
		    }
		}
                d->dec_u.dec_val.processed = 1;
	    }

	    output_all();
	    free_all_ins();
	}
	d = d->def_next;
    }

    eval_delayed_const_list();
    output_all();
    free_all_ins();

    /* Add final touches */
    init_output();
    if (need_dummy_double) {
       mach_op *op1 = make_extern_data("___m68k_dummy_double", 0);
       mach_op *op2 = make_int_data(8);
       make_instr(m_as_common, op1, op2, 0);
    }

    if (do_profile)profile_hack();

    area(pdata);
    output_all();
    free_all_ins();
    return;
}
