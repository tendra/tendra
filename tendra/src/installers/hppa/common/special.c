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


/*
$Log: special.c,v $
 * Revision 1.1.1.1  1998/01/17  15:56:03  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1996/11/25  13:43:27  wfs
 *    Fixed the comm_op register tracking bug in "oprators.c" and removed a
 * few superfluous "#if 0"s.
 *
 * Revision 1.3  1996/04/18  11:09:17  wfs
 * Fixed a bug in "needscan.c" where "locptr_tag" was being wrapped around
 * the wrong exps.
 *
 * Revision 1.2  1995/12/18  13:12:34  wfs
 * Put hppatrans uder cvs control. Major Changes made since last release
 * include:
 * (i) PIC code generation.
 * (ii) Profiling.
 * (iii) Dynamic Initialization.
 * (iv) Debugging of Exception Handling and Diagnostics.
 *
 * Revision 5.1  1995/10/20  14:12:03  wfs
 * gcc compilation changes.
 *
 * Revision 5.0  1995/08/25  13:42:58  wfs
 * Preperation for August 25 Glue release
 *
 * Revision 3.4  1995/08/25  10:32:18  wfs
 * Register synonyms changed. Minor change to "extj_special_ins"
 * required for tail_call's
 *
 * Revision 3.4  1995/08/25  10:32:18  wfs
 * Register synonyms changed. Minor change to "extj_special_ins"
 * required for tail_call's
 *
 * Revision 3.1  95/04/10  16:28:11  16:28:11  wfs (William Simmonds)
 * Apr95 tape version.
 * 
 * Revision 3.0  95/03/30  11:18:59  11:18:59  wfs (William Simmonds)
 * Mar95 tape version with CRCR95_178 bug fix.
 * 
 * Revision 2.0  95/03/15  15:28:49  15:28:49  wfs (William Simmonds)
 * spec 3.1 changes implemented, tests outstanding.
 * 
 * Revision 1.2  95/01/17  17:30:49  17:30:49  wfs (William Simmonds)
 * Changed name of an included header file.
 * 
 * Revision 1.1  95/01/11  13:18:45  13:18:45  wfs (William Simmonds)
 * Initial revision
 * 
*/


#define HPPATRANS_CODE
#include "config.h"
#include "common_types.h"
#include "exptypes.h"
#include "expmacs.h"
#include "codetypes.h"
#include "const.h"
#include "installtypes.h"
#include "exp.h"
#include "translat.h"
#include "addrtypes.h"
#include "shapemacs.h"
#include "move.h"
#include "regmacs.h"
#include "getregs.h"
#include "guard.h"
#include "codehere.h"
#include "inst_fmt.h"
#include "hppains.h"
#include "labels.h"
#include "tags.h"
#include "proctypes.h"
#include "bitsmacs.h"
#include "comment.h"
#include "machine.h"
#include "proc.h"
#include "myassert.h"
#include "out.h"
#include "frames.h"
#include "regexps.h"
#include "flags.h"
#include "special.h"

speci special_fn 
    PROTO_N ( ( a1, a2, s ) )
    PROTO_T ( exp a1 X exp a2 X shape s )
{				/* look for special functions */
  speci spr;

  /* +++ implement special fns handling */
  spr.is_special = 0;
  spr.special_exp = nilexp;

  return spr;
}

/* these are the procs I could do something about */
static int specno 
    PROTO_N ( ( n ) )
    PROTO_T ( char * n )
{

  /*
   * specno: >0 special, handle inline in specialmake 0 not special <0
   * special, rewrite TDF in specialneeds, no call to specialmake
   */

  FULLCOMMENT1("specno(%s)", (long) n);

  if (strcmp(n, "___builtin_strcpy") == 0 || strcmp(n, "___TDF_builtin_strcpy") == 0)
    return -1;

  if (strcmp(n, "___builtin_asm") == 0 || strcmp(n, "___TDF_builtin_asm") == 0)
    return 4;

  if (strcmp(n, "___builtin_alloca") == 0 || strcmp(n, "___TDF_builtin_alloca") == 0)
    return 5;

#if 0
  /* +++ use special maybe */
  if (strcmp(n, "strlen") == 0)
    return 2;
  if (strcmp(n, "strcmp") == 0)
    return -3;
#endif

  return 0;
}


/* what name to use with call instruction for specials */
char *special_call_name 
    PROTO_N ( ( i ) )
    PROTO_T ( int i )
{
  switch (i)
  {
    case -1:
    case 1:
    return ("_strcpy");

  case 5:
    return ("_alloca");

  default:
    fail("attempting external call to builtin");
    return "";
  }
  /* NOTREACHED */
}



static needs zeroneeds = {0, 0, 0, 0};	/* has no needs */
#if 0
static CONST needs onefixneeds = {1, 0, 0, 0};	/* one fix reg needs */
static CONST needs twofixneeds = {2, 0, 0, 0};	/* two fix reg needs */
#endif


/* these are the needs for their expansion */
needs specialneeds 
    PROTO_N ( ( i, application, pars ) )
    PROTO_T ( int i X exp application X exp pars )
{
  FULLCOMMENT1("specialneeds(%d,...)", i);

  switch (i)
  {
/* +++ implement special fuinction handling */

  case 4:
  {   return zeroneeds;		/* asm(string) */ }

  case 5:
    return zeroneeds;		/* alloca(n) */

  default:
    comment1("specialneeds: unimplemented builtin %d", i);
    fail("unimplemented builtin");
    return zeroneeds;
  }
  /* NOTREACHED */
}


/* could I treat this function load specially ? */
int specialfn 
    PROTO_N ( ( fn ) )
    PROTO_T ( exp fn )
{
  if (name(fn) == name_tag && name(son(fn)) == ident_tag &&
      isglob(son(fn)) && son(son(fn)) == nilexp)
  {
    char *extname = brog(son(fn))->dec_u.dec_val.dec_id;

    return specno(extname);
  }
  return 0;
}

/* Is a call to this function reason to prohibit optmisation of caller? */
int specialopt 
    PROTO_N ( ( fn ) )
    PROTO_T ( exp fn )
{
  if (name(fn) == name_tag && name(son(fn)) == ident_tag &&
      isglob(son(fn)) && son(son(fn)) == nilexp)
  {
    char *extname = brog(son(fn))->dec_u.dec_val.dec_id;

    if (extname == 0)
      return 0;

    extname += strlen(name_prefix); /* Normalise "_foo" -> "foo" */
    
    FULLCOMMENT1("specialopt: %s", (int)extname);

    if ((strcmp(extname, "vfork") == 0) ||
	(strcmp(extname, "setjmp") == 0) ||
	(strcmp(extname, "_setjmp") == 0) ||
	(strcmp(extname, "sigsetjmp") == 0)
	)
    {
      FULLCOMMENT("specialopt: return 1");
      return 1;
    }
  }
  return 0;
}


int specialmake 
    PROTO_N ( ( i, par, sp, dest, exitlab ) )
    PROTO_T ( int i X exp par X space sp X where dest X int exitlab )
{
  switch (i)
  {
  case 4:
    {
      /* asm(s) - simply output s */
      exp e;
      char *s;

      /* "par" is (eval_tag (pack_tag (string_tag no=string-table-index))) */
      e = son(son(par));
      if (name(e) != string_tag)
      {
	fail("asm argument not string");
	return 0;
      }
      s = nostr(e);

      /* asm is dangerous; as the least precaution, zap register tracking. */
      clear_all();
      fprintf(outf,"!  asm:\n" ) ;
      fprintf(outf,s) ;
      fputc('\n',outf);
      break;
    }

  case 5:
    {

       /* alloca(n) - grow stack frame by n bytes and then grab 
	  grab n bytes */

       int maxargbytes = max_args>>3;
       int dreg;
       ans aa;

       dreg = ((discrim(dest.answhere)==inreg) ? regalt(dest.answhere) : getreg(sp.fixed));

       if (name(par) == val_tag)
       {
	  /* n is a constant */
	  int n = no(par);

	  /* adjust n to be multiple of 64 so stack stays 64 byte aligned */
	  n = (n+63) & ~(63);

	  if (n != 0)
	  {
	     /* alloca(n) = %sp - maxargbytes */
	     if (SIMM14(-maxargbytes))
		ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,-maxargbytes,SP,dreg);
	     else
	     {
		ir_ins(i_addil,fs_L,empty_ltrl,-maxargbytes,SP);
		ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,-maxargbytes,GR1,dreg);
	     }
	     /* grow stack frame, i.e. %sp -> %sp + n */             
	     if (SIMM14(n))
		ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,n,SP,SP);
	     else
	     {
		/* grow stack frame by more than 8192 bytes */
		ir_ins(i_addil,fs_L,empty_ltrl,n,SP);
		ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,n,GR1,SP);
	     }
	  }
       }
       else
       {
	  int nreg = reg_operand(par, sp);

 	  /* adjust nreg so that stack stays 64 byte aligned */
	  ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,63,nreg,GR1);
	  riir_ins(i_dep,c_,0,31,6,GR1);

	  /* alloca(n) = %sp - maxargbytes */
	  if (SIMM14(-maxargbytes))
	     ld_ir_ins(i_ldo,cmplt_,fs_,empty_ltrl,-maxargbytes,SP,dreg);
	  else
	  {
	     ir_ins(i_addil,fs_L,empty_ltrl,-maxargbytes,SP);
	     ld_ir_ins(i_ldo,cmplt_,fs_R,empty_ltrl,-maxargbytes,GR1,dreg);
	  }
	  /* %sp -> %sp + nreg */
	  rrr_ins(i_add,c_,SP,GR1,SP);
       }

      setregalt(aa, dreg);
      move(aa, dest, guardreg(dreg, sp).fixed, 0);
      break;
    }

  default:
    comment1("specialmake: unimplemented builtin %d", i);
    fail("unimplemented builtin");
    return 0;
  }

  return exitlab;		/* for most cases */
}


/*
    TDF LIBRARY KEY

    A value of 0 means that the library is not present, 1 that it is, and
    2 that it should be generated.
*/

int library_key = 0 ;


/*
    SPECIAL ROUTINES
*/

#define sz_millicode_lib 7

static struct {
		  CONST char *proc_name ;
		  bool called ;
		  bool in_library ;
	      } millicode_lib [ sz_millicode_lib ] =
	      {
		  { milli_mulU, 0, 1 },	        /* $$mulU    */
		  { milli_mulI, 0, 1 },	        /* $$mulI    */
		  { milli_divU, 0, 1 },	        /* $$mulU    */
		  { milli_divI, 0, 1 },    	/* $$divI    */
		  { milli_remU, 0, 1 },	        /* $$remU    */
		  { milli_remI, 0, 1 },  	/* $$remI    */
		  { milli_dyncall, 0, 1 },	/* $$dyncall */
	      } ;


/*
    OUTPUT A MILLICODE LIBRARY CALL
*/

void call_millicode
    PROTO_N ( ( n, r, stub, restore_linkage_ptr_reg ) )
    PROTO_T ( int n X int r X char *stub X bool restore_linkage_ptr_reg )
{
    CONST char *nm = millicode_lib[n].proc_name ;
    millicode_lib[n].called = 1 ;
    extj_special_ins ( nm, r, stub, 0 ) ;
    if (PIC_code && restore_linkage_ptr_reg)
       rr_ins(i_copy,GR5,GR19);
    return ;

}

void import_millicode
    PROTO_Z ()
{
   int n;
   for(n=0; n<sz_millicode_lib; n++)
      if ( millicode_lib[n].called )
	 fprintf(outf,"\t.IMPORT\t%s,MILLICODE\n",millicode_lib[n].proc_name);
}
