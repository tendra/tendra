/*
    		 Crown Copyright (c) 1996

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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/trans.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: trans.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:31  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:43:00  ma
First version.

Revision 1.6  1997/10/13 08:50:13  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.5  1997/09/25 06:45:36  ma
All general_proc tests passed

Revision 1.4  1997/06/18 12:04:59  ma
Merged with Input Baseline changes.

Revision 1.3  1997/06/18 10:09:45  ma
Checking in before merging with Input Baseline changes.

Revision 1.2  1997/04/20 11:30:40  ma
Introduced gcproc.c & general_proc.[ch].
Added cases for apply_general_proc next to apply_proc in all files.

Revision 1.1.1.1  1997/03/14 07:50:19  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:59  john
 *
 * Revision 1.2  1996/07/05  14:28:02  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:18  john
 *
 * Revision 1.3  94/02/21  16:05:07  16:05:07  ra (Robert Andrews)
 * Just declare scan2 traditionally.
 *
 * Revision 1.2  93/11/19  16:23:34  16:23:34  ra (Robert Andrews)
 * Reformatted mark_unaliased.
 *
 * Revision 1.1  93/02/22  17:16:50  17:16:50  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "expmacs.h"
#include "exp.h"
#include "flags.h"
#include "instrs.h"
#include "installglob.h"
#include "shapemacs.h"
#include "evaluate.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "weights.h"
#include "mach.h"
#include "where.h"
#include "coder.h"
#include "codex.h"
#include "optimise.h"
#include "output.h"
#include "tests.h"
#include "tags.h"
#include "utility.h"
#if have_diagnostics
#include "xdb_basics.h"
#endif
extern dec *sort_decs PROTO_S ( ( dec * ) ) ;
static void output_all_exps PROTO_S ( ( void ) ) ;

/*
    INCLUDE DEBUGGING ROUTINES

    These are used to aid in debugging.

*/
#ifdef EBUG
/*
#include <misc/debug>
*/
void breakpoint PROTO_Z () {}
#endif

#ifndef tdf3
#include "general_proc.h"
#include "68k_globals.h"
int need_dummy_double = 0 ;
#endif

/*
    LOCAL AND GLOBAL NAME PREFIXES
*/

char *local_prefix = "L" ;
char *name_prefix = "_" ;


/*
    EXTERNAL POSITIONS
*/

static long crt_ext_off = 64 ;
static long crt_ext_pt = 10 ;


/*
    MARK AN EXPRESSION AS BEING STATIC AND UNALIASED
*/

static void mark_unaliased
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    exp p = pt ( e ) ;
    bool ca = 1 ;
    while ( p != nilexp && ca ) {
	exp q = bro ( p ) ;
	if ( q == nilexp ) {
	    ca = 0 ;
	} else if ( !( last ( p ) && name ( q ) == cont_tag ) &&
		    !( !last ( p ) && last ( q ) &&
		       name ( bro ( q ) ) == ass_tag ) ) {
	    ca = 0 ;
	}
	p = pt ( p ) ;
    }
    if ( ca ) setcaonly ( e ) ;
    return ;
}


/*
    PROCESS THE TDF

    This routine gets all the TDF read into the correct operand form
    and applies the dead variable and register allocation analysis.
*/

void translate_capsule
    PROTO_Z ()
{
    dec *d ;

    /* Fix procedure handling (copied from trans386) */
    d = top_def;
#if 0
    while (d != (dec *) 0) {
    exp crt_exp = d -> dec_u.dec_val.dec_exp;
    exp idval;
      if (!(d -> dec_u.dec_val.dec_var) && (name(sh(crt_exp)) != prokhd ||
           ( idval = son(crt_exp) ,
             idval != nilexp && name(idval) != null_tag &&
               name(idval) != proc_tag && name(idval) != general_proc_tag )) ){
	/* make variable, and change all uses to contents */
        exp p = pt(crt_exp);
        if (d -> dec_u.dec_val.extnamed)
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
      d = d->def_next;
    }
#endif


    make_transformations () ;

#ifndef EBUG
    opt_all_exps () ;
#endif

    /* Mark static unaliases declarations */
    if ( !separate_units ) {
	for ( d = top_def ; d ; d = d->def_next ) {
	    exp c = d->dec_u.dec_val.dec_exp ;
	    if ( son ( c ) != nilexp &&
		 !( d->dec_u.dec_val.extnamed ) && isvar ( c ) ) {
		mark_unaliased ( c ) ;
	    }
	}
    }

    /* Mark locations for all globals */
    for ( d = top_def ; d ; d = d->def_next ) {
	if ( d->dec_u.dec_val.processed ) {
	    exp c = d->dec_u.dec_val.dec_exp ;
	    ptno ( c ) = crt_ext_pt++ ;
	    no ( c ) = crt_ext_off ;
	    crt_ext_off += shape_size ( d->dec_u.dec_val.dec_shape ) ;
	}
    }

    /* Output all code */
    output_all_exps () ;

    return ;
}


/*
    TRANSLATE A SINGLE TAG DEFINITION
*/

void translate_tagdef
    PROTO_Z ()
{
    return ;
}


/*
    TRANSLATE A SINGLE UNIT
*/

void translate_unit
    PROTO_Z ()
{
    if ( separate_units ) {
	dec *d ;
	translate_capsule () ;
	d = top_def ;
	while ( d ) {
	    exp c = d->dec_u.dec_val.dec_exp ;
	    no ( c ) = 0 ;
	    pt ( c ) = nilexp ;
	    d = d->def_next ;
	}
	crt_repeat = nilexp ;
	repeat_list = nilexp ;
    }
    return ;
}


/*
    ENCODE A PROCEDURE

    The procedure with declaration d, name id, definition c and body s
    is encoded.
*/

static void code_proc
    PROTO_N ( ( d, id, c, s ) )
    PROTO_T ( dec *d X char *id X exp c X exp s )
{
    diag_global *di = d->dec_u.dec_val.diag_info ;
    int reg_res = ( has_struct_res ( s ) ? 0 : 1 ) ;
    int is_ext = ( d->dec_u.dec_val.extnamed ? 1 : 0 ) ;

    area ( ptext ) ;

    cur_proc_dec = d ;
    cur_proc_callees_size = 0 ;
    cur_proc_has_vcallees = 0 ;

    /* Code procedure body */
#if 0
    if ( name ( s ) == proc_tag )
    cproc ( s, id, -1, is_ext, reg_res, di ) ;
    else
#endif
    gcproc ( s, id, -1, is_ext, reg_res, di) ;


    d -> dec_u.dec_val.index = cur_proc_env_size ; /* for use in constant evaluation */

    output_env_size(d, cur_proc_env_size);
}


/*
    ENCODE A CONSTANT

    The constant with declaration d, name id, definition c and body s
    is encoded.
*/

static void code_const
    PROTO_N ( ( d ) )
    PROTO_T ( dec *d )
{
   exp c = d->dec_u.dec_val.dec_exp ;
   exp s = son ( c ) ;
   char *id = d->dec_u.dec_val.dec_id ;

   diag_global *di = d->dec_u.dec_val.diag_info ;
   area ( isvar ( c ) ? pdata : ptext ) ;
#ifndef no_align_directives
   make_instr ( m_as_align4, null, null, 0 ) ;
#endif
   evaluate ( s, L_1 , id, !isvar ( c ), 1, di ) ;
}


/*
    ENCODE THE CONSTANTS IN const_list

    All auxiliary constants are formed into a list, const_list.  This
    routine applies evaluate to each element of this list.
*/

static void code_const_list
    PROTO_Z ()
{
    while ( const_list != nilexp ) {
	exp t = const_list ;
	exp s = son ( t ) ;
	bool b = ( name ( s ) != res_tag ) ;
	const_list = bro ( const_list ) ;
	if ( name ( s ) == proc_tag || name ( s ) == general_proc_tag ) {
	    char *id = alloc_nof ( char, 30 ) ;
	    sprintf ( id, "%s%ld", local_prefix, no ( t ) ) ;
	    gcproc ( s, null, no ( t ), 0, 1, null ) ;
	} else {
	    area ( b ? pdata : ptext ) ;
	    evaluate ( s, no ( t ), null, b, 0, null ) ;
	}
    }
    return ;
}

/*
   CONST_READY

   Returns TRUE if it is possible to evaluate the value of the constant now
*/

static int const_ready
    PROTO_N ( (e) )
    PROTO_T ( exp e )
{
  unsigned char  n = name (e);
  if (n == env_size_tag)
    return (brog(son(son(e))) -> dec_u.dec_val.processed);
  if (n == env_offset_tag)
    return (ismarked(son(e)));
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

typedef struct delayedconst{
   dec* This;
   struct delayedconst* next;
} delayed_const ;

static delayed_const* delayed_const_list = 0;

static void eval_if_ready
    PROTO_N ( ( d ) )
    PROTO_T ( dec *d )
{
   exp c = d->dec_u.dec_val.dec_exp ;
   if ( const_ready( c ) ) {
      code_const ( d ) ;
   }
   else {
      delayed_const* p = (delayed_const*)xmalloc (sizeof(delayed_const));
      p->This = d;
      p->next = delayed_const_list;
      delayed_const_list = p;
   }
}

void eval_delayed_const_list
    PROTO_Z ()
{
   delayed_const* p;
   bool done = 0;
   while (! done) {
      done = 1;
      for (p = delayed_const_list; p; p = p->next) {
         dec* d = p->This;
         if ( !d->dec_u.dec_val.processed ) {
            exp c = d->dec_u.dec_val.dec_exp ;
            if ( const_ready( c ) ) {
               code_const ( d ) ;
               d->dec_u.dec_val.processed = 1 ;
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
    PROTO_Z ()
{
    dec *d = top_def ;
    if ( diagnose ) d = sort_decs ( d ) ;

    area ( ptext ) ;

    /* Clear any existing output */
    output_all () ;
    free_all_ins () ;

    /* Scan through the declarations */
    while ( d ) {

	if ( !d->dec_u.dec_val.processed ) {
	    exp c = d->dec_u.dec_val.dec_exp ;
	    exp s = son ( c ) ;
	    char *id = d->dec_u.dec_val.dec_id ;

	    init_output () ;

	    if ( s != nilexp ) {
		if ( name ( s ) == proc_tag ||
                    name ( s ) == general_proc_tag) {
		    code_proc ( d, id, c, s ) ;
		    code_const_list () ;
                    d->dec_u.dec_val.processed = 1 ;
		} else {
		    eval_if_ready ( d ) ;
		    code_const_list () ;
		}
	    } else {
		shape sha = d->dec_u.dec_val.dec_shape ;
		long sz = round ( shape_size ( sha ) / 8, 4 ) ;
		area ( ptext ) ;
		if ( !is_local ( id ) && isvar ( c ) &&
		     varsize ( sha ) && !reserved ( id ) ) {
		    if ( sz ) {
			mach_op *op1 = make_extern_data ( id, 0 ) ;
			mach_op *op2 = make_int_data ( sz ) ;
			make_instr ( m_as_common, op1, op2, 0 ) ;
		    }
		} else {
		    if ( is_local ( id ) && no ( c ) ) {
			mach_op *op1 = make_extern_data ( id, 0 ) ;
			mach_op *op2 = make_int_data ( sz ) ;
			make_instr ( m_as_local, op1, op2, 0 ) ;
		    }
		}
                d->dec_u.dec_val.processed = 1 ;
	    }

	    output_all () ;
	    free_all_ins () ;
	}
	d = d->def_next ;
    }

    eval_delayed_const_list();
    output_all () ;
    free_all_ins () ;

    /* Add final touches */
    init_output () ;
    if ( need_dummy_double )  {
       mach_op *op1 = make_extern_data ("___m68k_dummy_double", 0 ) ;
       mach_op *op2 = make_int_data ( 8 ) ;
       make_instr ( m_as_common, op1, op2, 0 ) ;
    }

    if ( do_profile ) profile_hack () ;

    area ( pdata ) ;
    output_all () ;
    free_all_ins () ;
    return ;
}
