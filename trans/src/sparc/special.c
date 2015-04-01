/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>

#include <tdf/nat.h>
#include <tdf/shape.h>
#include <tdf/tag.h>

#include <reader/exp.h>

#include <construct/installtypes.h>
#include <construct/dec.h>
#include <construct/exp.h>
#include <construct/machine.h>

#include <refactor/const.h>

#include <main/driver.h>
#include <main/print.h>

#include "translate.h"
#include "addrtypes.h"
#include "move.h"
#include "regmacs.h"
#include "getregs.h"
#include "guard.h"
#include "code_here.h"
#include "inst_fmt.h"
#include "sparcins.h"
#include "labels.h"
#include "proctypes.h"
#include "bitsmacs.h"
#include "proc.h"
#include "regexps.h"
#include "special.h"
#include "make_code.h"

/*
    A value of 0 indicates that the procedure name n is not special.  A
    value > 0 indicates a special procedure handled by specialmake.  A
    value < 0 indicates a special procedure handled bu specialneeds.
*/

static int 
specno ( char * n )
{
    if ( streq( n, "___builtin_strcpy" ) ||
	 streq( n, "___TDF_builtin_strcpy" ) ) {
	return -1;
    }

    if ( streq( n, "___builtin_asm" ) ||
	 streq( n, "___TDF_builtin_asm" ) ) {
	return 4;
    }

    if ( streq( n, "___builtin_alloca" ) ||
	 streq( n, "___TDF_builtin_alloca" ) ) {
	return 5;
    }

#if 0
    /* Could be made special */
    if ( streq( n, "strlen" ) ) return 2;
    if ( streq( n, "strcmp" ) ) return -3;
#endif

    return 0;
}


/*
    FIND NAME OF A SPECIAL PROCEDURE
*/

char *
special_call_name ( int i )
{
    switch ( i ) {
	case -1:
	case 1: return sysV_assembler ? "strcpy" : "_strcpy";
	case 5: return sysV_assembler ? "alloca" : "_alloca";

	default:
	    error(ERR_SERIOUS,  "Attempting external call to builtin" ) ;
	    return "";
    }

	UNREACHED;
}


/*
    These indicate respectively needs of zero, one and two fixed register.
*/

static const needs zeroneeds = { 0, 0, 0, 0 } ;
#if 0
static const needs onefixneeds = { 1, 0, 0, 0 } ;
static const needs twofixneeds = { 2, 0, 0, 0 } ;
#endif


/*
    DEAL WITH THE NEEDS OF SPECIAL PROCEDURES
*/

/* ARGSUSED */ 
static needs 
specialneeds ( int i, exp application, exp pars )
{
	UNUSED(application);
	UNUSED(pars);

    switch ( i ) {

#if 0
	case -1 :
	case 1 : {
	    /* The library strcpy contains a number of tricks, so this
	       isn't really worthwhile */
	    exp par1 = pars ;
	    exp par2 = bro ( pars ) ;

	    if ( par2->tag == eval_tag &&
		 son ( par2 ) -> tag == pack_tag &&
		 son ( son ( par2 ) ) -> tag == string_tag ) {
		/* strcpy of constant string */
		if ( no ( sh ( son ( son ( par2 ) ) ) ) > 7 ) {
		    break ;
		}

		/* apply_tag into ass_tag */
		 application->tag = ass_tag  ;

		/* params of ass_tag as params of application */
		son ( application ) = pars ;
		bro ( bro ( pars ) ) = application ;	/* set father */

		/* loose pack_tag */
		son ( par2 ) = son ( son ( par2 ) ) ;
		bro ( son ( par2 ) ) = par2 ;		/* set father */

		/* shape of eval_tag from ptrhd to nofhd */
		sh ( par2 ) = sh ( son ( par2 ) ) ;

		return twofixneeds;
	    }

	    /* otherwise leave TDF so strcpy is called */
	    return zeroneeds;
	}
#endif

	case 4: return zeroneeds;	 /* asm */
	case 5: return zeroneeds;	 /* alloca */

	default : {
	    error(ERR_SERIOUS,  "Unimplemented builtin" ) ;
	    return zeroneeds;
	}
    }

	UNREACHED;
}


/*
    DOES fn REPRESENT A SPECIAL PROCEDURE?
*/

int 
specialfn ( exp fn )
{
    if ( fn->tag == name_tag && son ( fn ) -> tag == ident_tag &&
	 isglob ( son ( fn ) ) && son ( son ( fn ) ) == NULL ) {
	char *extname = brog ( son ( fn ) )->dec_id ;
	return specno ( extname ) ;
    }
    return 0;
}

/*
    IS A CALL TO fn REASON TO PROHIBIT OPTIMISATION OF THE CALLER?

    Some system calls have unexpected effects on the registers and should
    not be optimised.
*/

int 
specialopt ( exp fn )
{
    if ( fn->tag == name_tag && son ( fn ) -> tag == ident_tag &&
	 isglob ( son ( fn ) ) && son ( son ( fn ) ) == NULL ) {
	char *extname = brog ( son ( fn ) )->dec_id ;
	if ( extname == NULL ) return 0;
	extname += strlen ( name_prefix ) ;	/* get rid of any prefix */

	/* The following list corresponds to #pragma unknown_control_flow
	   in SunOS 4.1.1 /usr/include */
	if ( ( streq( extname, "vfork" ) ) ||
	     ( streq( extname, "setjmp" ) ) ||
	     ( streq( extname, "_setjmp" ) ) ||
	     ( streq( extname, "sigsetjmp" ) ) ) {
	    return 1;
	}
    }
    return 0;
}
extern int stackerr_lab;
extern int local_stackerr_lab;

/*
    INLINE SPECIAL FUNCTIONS
*/

int 
specialmake ( int i, exp par, space sp, where dest, int exitlab ){
  switch ( i ) {
    case 4 : {
      /* asm ( s ) - simply output s */
      exp e ;
      char *s ;
      e = son ( son ( par ) ) ;
      if ( e->tag != string_tag ) {
	error(ERR_SERIOUS,  "asm argument is not a string" ) ;
	return 0;
      }
      s = nostr ( e ) ;
      /* asm is dangerous : zap register tracking */
      clear_all () ;
      asm_comment("asm: ");
      asm_printf("%s\n", s);
      break ;
    }
    
    case 5 :
    case 6 : {    
      /* 5 == alloca_tag, 6 = alloca_tag with checkstack */
      /* alloca ( n ) - grab n bytes from stack frame */
      int maxargbytes = ( int ) ( proc_state.maxargs / 8 ) ;
      int safety_below = 0 ;     /* safety zone in bytes */
      int safety_above = 0 ;     /* on each side of allocation */
      int dreg ;
      ans aa ;
      int rd ;
      /* Sparctrans does not use %sp relative temps, so we need not
	 move them to grow the stack frame in the middle for alloca.
	 %sp relative addresses may be used in building param lists,
	 but scan () brings forward alloca () as for function calls
	 so we will not be invoked during that sequence */
      if(i == 6) {
	rd =  getreg(sp.fixed); /* R_SP;*/
	sp = guardreg (rd, sp);	
      }
      else {
	rd = R_SP;
      }
      /* grow the stack frame */
      if ( par->tag == val_tag ) {
	/* n is a constant */
	int n = no ( par ) ;
	/* adjust n to be multiple of 8 */
	n = ( n + 8 - 1 ) & ~( 8 - 1 ) ;
	n += safety_below + safety_above ;
	if ( n != 0 ) {
	  rir_ins ( i_sub, R_SP, ( long ) n, rd ) ;
	}
	else {
	  rd = R_SP;
	}
      } 
      else {
	int nreg = reg_operand ( par, sp ) ;
	/* adjust nreg to be multiple of 8 */
	int m = ( 8 - 1 ) + ( safety_below + safety_above ) ;
	rir_ins ( i_add, nreg, ( long ) m, R_TMP ) ;
	rir_ins ( i_and, R_TMP, ~( 8 - 1 ), R_TMP ) ;
	rrr_ins ( i_sub, R_SP, R_TMP, rd ) ;
      }

      dreg = ( ( discrim ( dest.answhere ) == inreg ) ?
	       regalt ( dest.answhere ) : getreg ( sp.fixed ) ) ;
      sp = guardreg (dreg, sp);

      /* stack frame beyond reg dump area is the space to use */
      assert ( maxargbytes >= 16 * 4 ) ;
      rir_ins ( i_add, rd, ( long ) ( maxargbytes + safety_below ),
		dreg ) ;
      if (i == 6) {
	int rt = getreg(sp.fixed);
	/* checkalloc */
	baseoff b;
	b = find_tag(TDF_STACKLIM);
	if(stackerr_lab == 0) stackerr_lab = new_label();
	if(local_stackerr_lab == 0) local_stackerr_lab = new_label();
	ld_ins(i_ld,b,rt);
	condrr_ins(i_bgtu,rt,rd,local_stackerr_lab);
	if(rd != R_SP) {
	  rr_ins(i_mov,rd,R_SP);
	}
      }
      setregalt ( aa, dreg ) ;
      ( void ) move ( aa, dest, sp.fixed, 0 ) ;
      break ;
    }
    
    default : {
      error(ERR_SERIOUS,  "Unimplemented builtin" ) ;
      return 0;
    }
  }
  return exitlab;
}


/*
    A value of 0 means that the library is not present, 1 that it is, and
    2 that it should be generated.
*/

int library_key = 0 ;


/*
    SPECIAL ROUTINES
*/

#define no_special_routines 8

static struct {
    char *proc_name ;
    int proc_regs ;
    bool proc_used ;
    bool in_library ;
} special_routine [ no_special_routines ] = {
    { ".mul", 2, 0, 1 },	/* SPECIAL_MUL */
    { ".umul", 2, 0, 1 },	/* SPECIAL_UMUL */
    { ".div", 2, 0, 1 },	/* SPECIAL_DIV2 */
    { ".udiv", 2, 0, 1 },	/* SPECIAL_UDIV2 */
    { ".rem", 2, 0, 1 },	/* SPECIAL_REM2 */
    { ".urem", 2, 0, 1 },	/* SPECIAL_UREM2 */
    { ".L.div1", 2, 0, 0 },	/* SPECIAL_DIV1 */
    { ".L.rem1", 2, 0, 0 }	/* SPECIAL_REM1 */
} ;


/*
    OUTPUT A CALL TO A SPECIAL ROUTINE
*/

void 
call_special_routine ( int n )
{
    char *nm = special_routine [n].proc_name ;
    int r = special_routine [n].proc_regs ;
    special_routine [n].proc_used = 1 ;
    if ( library_key && nm [1] == 'L' ) nm += 2 ;
    extj_special_ins ( i_call, nm, r ) ;
}


/*
    OUTPUT ALL SPECIAL ROUTINES
*/

void 
output_special_routines (void)
{
    int i ;
    if ( library_key == 1 ) return ;
    for ( i = 0 ; i < no_special_routines ; i++ ) {
	if ( special_routine [i].proc_used || library_key == 2 ) {
	    if ( !special_routine [i].in_library ) {
		char *nm = special_routine [i].proc_name ;
		if ( library_key && nm [1] == 'L' ) nm += 2 ;
		insection ( text_section ) ;
		asm_comment( "TDF support library routine" ) ;
		asm_printop(".proc 4") ;
		asm_printop(".optim \"-O%d\"", optim_level);
		asm_label("%s", nm);
		switch ( i ) {

		    case SPECIAL_DIV1 : {
			asm_printop("save %s,-96,%s", "%sp", "%sp") ;
			asm_printop("mov %s,%s", "%i0", "%o0") ;
			asm_printop("mov %s,%s", "%i1", "%o1") ;
			asm_printop("call .div,2") ;
			asm_printop("nop") ;
			asm_printop("mov %s,%s", "%o0", "%i2") ;
			asm_printop("mov %s,%s", "%i0", "%o0") ;
			asm_printop("mov %s,%s", "%i1", "%o1") ;
			asm_printop("call .rem,2") ;
			asm_printop("nop") ;
			asm_printop("cmp %s,0", "%o0") ;
			asm_printop("be LS.101") ;
			asm_printop("nop") ;
			asm_label("LS.102") ;
			asm_printop("cmp %s,0", "%o0") ;
			asm_printop("ble LS.103") ;
			asm_printop("nop") ;
			asm_printop("cmp %s,0", "%i1") ;
			asm_printop("bge LS.101") ;
			asm_printop("nop") ;
			asm_printop("add %s,-1,%s", "%i2", "%i2") ;
			asm_printop("b LS.101") ;
			asm_printop("nop") ;
			asm_label("LS.103" ) ;
			asm_printop("cmp %s,0", "%i1") ;
			asm_printop("ble LS.101") ;
			asm_printop("nop") ;
			asm_printop("add %s,-1,%s", "%i2", "%i2") ;
			asm_label("LS.101") ;
			asm_printop("mov %s,%s", "%i2", "%i0") ;
			break ;
		    }

		    case SPECIAL_REM1 : {
			asm_printop("save %s,-96,%s", "%sp", "%sp") ;
			asm_printop("mov %s,%s", "%i0", "%o0") ;
			asm_printop("mov %s,%s", "%i1", "%o1") ;
			asm_printop("call .rem,2") ;
			asm_printop("nop") ;
			asm_printop("cmp %s,0", "%o0") ;
			asm_printop("be LS.201") ;
			asm_printop("nop") ;
			asm_label("LS.202") ;
			asm_printop("cmp %s,0", "%o0") ;
			asm_printop("ble LS.203") ;
			asm_printop("nop") ;
			asm_printop("cmp %s,0", "%i1") ;
			asm_printop("bge LS.201") ;
			asm_printop("nop") ;
			asm_printop("add %s,%s,%s", "%o0", "%i1", "%o0") ;
			asm_printop("b LS.201") ;
			asm_printop("nop") ;
			asm_label("LS.203") ;
			asm_printop("cmp %s,0", "%i1") ;
			asm_printop("ble LS.201") ;
			asm_printop("nop") ;
			asm_printop("add %s,%s,%s", "%o0", "%i1", "%o0") ;
			asm_label("LS.201") ;
			asm_printop("mov %s,%s", "%o0", "%i0") ;
			break ;
		    }

		    default : {
			error(ERR_SERIOUS,  "Unimplemented special routine" ) ;
			break ;
		    }
		}
		asm_printop("ret") ;
		asm_printop("restore") ;
	    }
	}
    }
}
