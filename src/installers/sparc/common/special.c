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
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/sparc/common/special.c,v 1.1.1.1 1998/01/17 15:55:55 release Exp $
--------------------------------------------------------------------------
$Log: special.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:55  release
 * First version to be checked into rolling release.
 *
 * Revision 1.10  1996/08/28  17:36:21  pwe
 * fixed local_alloc_check use of registers
 *
 * Revision 1.9  1996/03/29  14:41:54  john
 * Fixed for zero-sized alloca
 *
 * Revision 1.8  1996/01/17  12:04:41  john
 * Fix to local_alloc check
 *
 * Revision 1.7  1995/12/15  10:28:02  john
 * Changes local_alloc stack check
 *
 * Revision 1.6  1995/11/15  16:57:21  john
 * Stack check now uses unsigned test
 *
 * Revision 1.5  1995/09/22  15:58:42  john
 * Fix to stack check
 *
 * Revision 1.4  1995/09/20  12:40:28  john
 * Portability fix
 *
 * Revision 1.3  1995/09/19  14:32:37  john
 * Added checkstack to alloca_tag
 *
 * Revision 1.2  1995/09/15  16:18:43  john
 * New exception handling
 *
 * Revision 1.1.1.1  1995/03/13  10:18:58  john
 * Entered into CVS
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.2  1994/07/07  16:11:33  djch
 * Jul94 tape
 *
 * Revision 1.1  1994/05/03  14:49:58  djch
 * Initial revision
 *
 * Revision 1.8  93/09/27  14:56:39  14:56:39  ra (Robert Andrews)
 * Changed the names of a couple of my built-in functions.
 * 
 * Revision 1.7  93/08/27  11:39:21  11:39:21  ra (Robert Andrews)
 * A couple of lint-like changes.
 * 
 * Revision 1.6  93/08/13  14:47:14  14:47:14  ra (Robert Andrews)
 * Reformatted.
 * 
 * Revision 1.5  93/07/14  11:22:35  11:22:35  ra (Robert Andrews)
 * Add library_key to determine presence of TDF support library.
 * 
 * Revision 1.4  93/07/12  15:18:57  15:18:57  ra (Robert Andrews)
 * Added support for special_routines, which is used to handle built-in
 * system calls like .mul and TDF library calls like L.div1 (used to
 * implement div1).
 * 
 * Revision 1.3  93/07/05  18:28:48  18:28:48  ra (Robert Andrews)
 * Made distinction between the System V assembler and the System V ABI.
 * 
 * Revision 1.2  93/06/29  14:35:30  14:35:30  ra (Robert Andrews)
 * Have to include regexps.h.
 * 
 * Revision 1.1  93/06/24  14:59:27  14:59:27  ra (Robert Andrews)
 * Initial revision
 * 
--------------------------------------------------------------------------
*/


#define SPARCTRANS_CODE
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
#include "sparcins.h"
#include "labels.h"
#include "tags.h"
#include "proctypes.h"
#include "bitsmacs.h"
#include "comment.h"
#include "machine.h"
#include "proc.h"
#include "myassert.h"
#include "out.h"
#include "regexps.h"
#include "special.h"
#include "makecode.h"

/*
    LOOK FOR SPECIAL FUNCTIONS
*/

/* ARGSUSED */ speci special_fn 
    PROTO_N ( ( a1, a2, s ) )
    PROTO_T ( exp a1 X exp a2 X shape s )
{
    speci spr ;
    spr.is_special = 0 ;
    spr.special_exp = nilexp ;
    return ( spr ) ;
}


/*
    FIND SPECIAL PROCEDURE NUMBER

    A value of 0 indicates that the procedure name n is not special.  A
    value > 0 indicates a special procedure handled by specialmake.  A
    value < 0 indicates a special procedure handled bu specialneeds.
*/

static int specno 
    PROTO_N ( ( n ) )
    PROTO_T ( char * n )
{
    if ( strcmp ( n, "___builtin_strcpy" ) == 0 ||
	 strcmp ( n, "___TDF_builtin_strcpy" ) == 0 ) {
	return ( -1 ) ;
    }

    if ( strcmp ( n, "___builtin_asm" ) == 0 ||
	 strcmp ( n, "___TDF_builtin_asm" ) == 0 ) {
	return ( 4 ) ;
    }

    if ( strcmp ( n, "___builtin_alloca" ) == 0 ||
	 strcmp ( n, "___TDF_builtin_alloca" ) == 0 ) {
	return ( 5 ) ;
    }

#if 0
    /* Could be made special */
    if ( strcmp ( n, "strlen" ) == 0 ) return ( 2 ) ;
    if ( strcmp ( n, "strcmp" ) == 0 ) return ( -3 ) ;
#endif

    return ( 0 ) ;
}


/*
    FIND NAME OF A SPECIAL PROCEDURE
*/

char *special_call_name 
    PROTO_N ( ( i ) )
    PROTO_T ( int i )
{
    switch ( i ) {

	case -1 :
	case 1 : {
	    return ( sysV_assembler ? "strcpy" : "_strcpy" ) ;
	}

	case 5 : {
	    return ( sysV_assembler ? "alloca" : "_alloca" ) ;
	}

	default : {
	    fail ( "Attempting external call to builtin" ) ;
	    return ( "" ) ;
	}
    }
    /* NOT REACHED */
}


/*
    REGISTER REQUIREMENTS

    These indicate respectively needs of zero, one and two fixed register.
*/

static CONST needs zeroneeds = { 0, 0, 0, 0 } ;
#if 0
static CONST needs onefixneeds = { 1, 0, 0, 0 } ;
static CONST needs twofixneeds = { 2, 0, 0, 0 } ;
#endif


/*
    DEAL WITH THE NEEDS OF SPECIAL PROCEDURES
*/

/* ARGSUSED */ needs specialneeds 
    PROTO_N ( ( i, application, pars ) )
    PROTO_T ( int i X exp application X exp pars )
{
    switch ( i ) {

#if 0
	case -1 :
	case 1 : {
	    /* The library strcpy contains a number of tricks, so this
	       isn't really worthwhile */
	    exp par1 = pars ;
	    exp par2 = bro ( pars ) ;

	    if ( name ( par2 ) == eval_tag &&
		 name ( son ( par2 ) ) == pack_tag &&
		 name ( son ( son ( par2 ) ) ) == string_tag ) {
		/* strcpy of constant string */
		if ( no ( sh ( son ( son ( par2 ) ) ) ) > 7 ) {
		    break ;
		}

		/* apply_tag into ass_tag */
		setname ( application, ass_tag ) ;

		/* params of ass_tag as params of application */
		son ( application ) = pars ;
		bro ( bro ( pars ) ) = application ;	/* set father */

		/* loose pack_tag */
		son ( par2 ) = son ( son ( par2 ) ) ;
		bro ( son ( par2 ) ) = par2 ;		/* set father */

		/* shape of eval_tag from ptrhd to nofhd */
		sh ( par2 ) = sh ( son ( par2 ) ) ;

		return ( twofixneeds ) ;
	    }

	    /* otherwise leave TDF so strcpy is called */
	    return ( zeroneeds ) ;
	}
#endif

	case 4 : return ( zeroneeds ) ;	 /* asm */
	case 5 : return ( zeroneeds ) ;	 /* alloca */

	default : {
	    fail ( "Unimplemented builtin" ) ;
	    return ( zeroneeds ) ;
	}
    }
    /* NOT REACHED */
}


/*
    DOES fn REPRESENT A SPECIAL PROCEDURE?
*/

int specialfn 
    PROTO_N ( ( fn ) )
    PROTO_T ( exp fn )
{
    if ( name ( fn ) == name_tag && name ( son ( fn ) ) == ident_tag &&
	 isglob ( son ( fn ) ) && son ( son ( fn ) ) == nilexp ) {
	char *extname = brog ( son ( fn ) )->dec_u.dec_val.dec_id ;
	return ( specno ( extname ) ) ;
    }
    return ( 0 ) ;
}

/*
    IS A CALL TO fn REASON TO PROHIBIT OPTIMISATION OF THE CALLER?

    Some system calls have unexpected effects on the registers and should
    not be optimised.
*/

int specialopt 
    PROTO_N ( ( fn ) )
    PROTO_T ( exp fn )
{
    if ( name ( fn ) == name_tag && name ( son ( fn ) ) == ident_tag &&
	 isglob ( son ( fn ) ) && son ( son ( fn ) ) == nilexp ) {
	char *extname = brog ( son ( fn ) )->dec_u.dec_val.dec_id ;
	if ( extname == NULL ) return ( 0 ) ;
	extname += strlen ( name_prefix ) ;	/* get rid of any prefix */

	/* The following list corresponds to #pragma unknown_control_flow
	   in SunOS 4.1.1 /usr/include */
	if ( ( strcmp ( extname, "vfork" ) == 0 ) ||
	     ( strcmp ( extname, "setjmp" ) == 0 ) ||
	     ( strcmp ( extname, "_setjmp" ) == 0 ) ||
	     ( strcmp ( extname, "sigsetjmp" ) == 0 ) ) {
	    return ( 1 ) ;
	}
    }
    return ( 0 ) ;
}
extern int stackerr_lab;
extern int local_stackerr_lab;

/*
    INLINE SPECIAL FUNCTIONS
*/

int specialmake 
    PROTO_N ( ( i, par, sp, dest, exitlab ) )
    PROTO_T ( int i X exp par X space sp X where dest X int exitlab ){
  switch ( i ) {
    case 4 : {
      /* asm ( s ) - simply output s */
      exp e ;
      char *s ;
      e = son ( son ( par ) ) ;
      if ( name ( e ) != string_tag ) {
	fail ( "asm argument is not a string" ) ;
	return ( 0 ) ;
      }
      s = nostr ( e ) ;
      /* asm is dangerous : zap register tracking */
      clear_all () ;
      outs ( "! asm : \n" ) ;
      outs ( s ) ;
      outnl () ;
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
      if ( name ( par ) == val_tag ) {
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
      fail ( "Unimplemented builtin" ) ;
      return ( 0 ) ;
    }
  }
  return ( exitlab ) ;
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

void call_special_routine 
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    char *nm = special_routine [n].proc_name ;
    int r = special_routine [n].proc_regs ;
    special_routine [n].proc_used = 1 ;
    if ( library_key && nm [1] == 'L' ) nm += 2 ;
    extj_special_ins ( i_call, nm, r ) ;
    return ;
}


/*
    OUTPUT ALL SPECIAL ROUTINES
*/

void output_special_routines 
    PROTO_Z ()
{
    int i ;
    if ( library_key == 1 ) return ;
    for ( i = 0 ; i < no_special_routines ; i++ ) {
	if ( special_routine [i].proc_used || library_key == 2 ) {
	    if ( !special_routine [i].in_library ) {
		char *nm = special_routine [i].proc_name ;
		if ( library_key && nm [1] == 'L' ) nm += 2 ;
		insection ( text_section ) ;
		outs ( "!\tTDF support library routine\n" ) ;
		outs ( "\t.proc\t4\n" ) ;
		outs ( "\t.optim\t\"-O" ) ;
		outn ( optim_level ) ;
		outs ( "\"\n" ) ;
		outs ( nm ) ;
		outs ( ":\n" ) ;
		switch ( i ) {

		    case SPECIAL_DIV1 : {
			outs ( "\tsave\t%sp,-96,%sp\n" ) ;
			outs ( "\tmov\t%i0,%o0\n" ) ;
			outs ( "\tmov\t%i1,%o1\n" ) ;
			outs ( "\tcall\t.div,2\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tmov\t%o0,%i2\n" ) ;
			outs ( "\tmov\t%i0,%o0\n" ) ;
			outs ( "\tmov\t%i1,%o1\n" ) ;
			outs ( "\tcall\t.rem,2\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tcmp\t%o0,0\n" ) ;
			outs ( "\tbe\tLS.101\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "LS.102:\n" ) ;
			outs ( "\tcmp\t%o0,0\n" ) ;
			outs ( "\tble\tLS.103\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tcmp\t%i1,0\n" ) ;
			outs ( "\tbge\tLS.101\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tadd\t%i2,-1,%i2\n" ) ;
			outs ( "\tb\tLS.101\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "LS.103:\n" ) ;
			outs ( "\tcmp\t%i1,0\n" ) ;
			outs ( "\tble\tLS.101\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tadd\t%i2,-1,%i2\n" ) ;
			outs ( "LS.101:\n" ) ;
			outs ( "\tmov\t%i2,%i0\n" ) ;
			break ;
		    }

		    case SPECIAL_REM1 : {
			outs ( "\tsave\t%sp,-96,%sp\n" ) ;
			outs ( "\tmov\t%i0,%o0\n" ) ;
			outs ( "\tmov\t%i1,%o1\n" ) ;
			outs ( "\tcall\t.rem,2\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tcmp\t%o0,0\n" ) ;
			outs ( "\tbe\tLS.201\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "LS.202:\n" ) ;
			outs ( "\tcmp\t%o0,0\n" ) ;
			outs ( "\tble\tLS.203\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tcmp\t%i1,0\n" ) ;
			outs ( "\tbge\tLS.201\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tadd\t%o0,%i1,%o0\n" ) ;
			outs ( "\tb\tLS.201\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "LS.203:\n" ) ;
			outs ( "\tcmp\t%i1,0\n" ) ;
			outs ( "\tble\tLS.201\n" ) ;
			outs ( "\tnop\n" ) ;
			outs ( "\tadd\t%o0,%i1,%o0\n" ) ;
			outs ( "LS.201:\n" ) ;
			outs ( "\tmov\t%o0,%i0\n" ) ;
			break ;
		    }

		    default : {
			fail ( "Unimplemented special routine" ) ;
			break ;
		    }
		}
		outs ( "\tret\n" ) ;
		outs ( "\trestore\n" ) ;
	    }
	}
    }
    return ;
}
