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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/where.c,v 1.1.1.1 1998/01/17 15:55:50 release Exp $
--------------------------------------------------------------------------
$Log: where.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:50  release
 * First version to be checked into rolling release.
 *
Revision 1.3  1997/11/09 14:07:59  ma
Removed issigned function.

Revision 1.2  1997/10/29 10:22:32  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:43:01  ma
First version.

Revision 1.5  1997/10/13 08:50:19  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.4  1997/09/25 06:45:41  ma
All general_proc tests passed

Revision 1.3  1997/06/18 10:09:46  ma
Checking in before merging with Input Baseline changes.

Revision 1.2  1997/04/20 11:30:43  ma
Introduced gcproc.c & general_proc.[ch].
Added cases for apply_general_proc next to apply_proc in all files.

Revision 1.1.1.1  1997/03/14 07:50:21  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:57:00  john
 *
 * Revision 1.2  1996/07/05  14:30:14  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:19  john
 *
 * Revision 1.3  94/02/21  16:06:54  16:06:54  ra (Robert Andrews)
 * Change the argument to find_reg_ind to an int.
 *
 * Revision 1.2  93/03/03  14:51:05  14:51:05  ra (Robert Andrews)
 * Use correct number of registers in initialization routine.
 *
 * Revision 1.1  93/02/22  17:17:05  17:17:05  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "exp.h"
#include "expmacs.h"
#include "externs.h"
#include "install_fns.h"
#include "shapemacs.h"
#include "tags.h"
#include "fbase.h"
#include "flpt.h"
#include "mach.h"
#include "tests.h"
#include "where.h"
#include "coder.h"
#include "utility.h"
#include "translate.h"
#include "evaluate.h"
#define REGISTER_SIZES
#include "instr_aux.h"
#include "special_exps.h"
static int find_where PROTO_S ( ( exp ) ) ;

/*
    MACROS

    These are used as convenient shorthands.
*/

#define  new_exp( A, B, C, D )	getexp ( A, nilexp, 0, B, nilexp, L0, C, D )
#define  ptrsh		 	ptr_shape ( slongsh )


/*
    WHAT SORT OF REGISTER SHOULD WE PUT SOMETHING OF A GIVEN SHAPE IN?

    The shape sha is examined and the appropriate register type -
    Dreg, Areg or Freg is returned.
*/

int shtype
    PROTO_N ( ( sha ) )
    PROTO_T ( shape sha )
{
    char n = name ( sha ) ;
    if ( n >= scharhd && n <= ulonghd ) return ( Dreg ) ;
    if ( n >= shrealhd && n <= doublehd ) return ( Freg ) ;
    if ( n != bitfhd && n != nofhd && n != cpdhd ) return ( Areg ) ;
    return ( shape_size ( sha ) <= 32 ? Dreg : Areg ) ;
}


/*
    REGISTERS USED IN OPERAND

    This is a bitmask of all the registers used in an operand.  It is
    built up by find_where.
*/

static bitpattern where_regmsk ;


/*
    FIND ADDRESSING TYPE OF A REGISTER INDIRECT WITH DISPLACEMENT

    The addressing type of a register indirect operand with register
    mask rgs is returned.  This is RegInd if rgs corresponds to an
    A-register, and Other otherwise.
*/

static int find_reg_ind
    PROTO_N ( ( r ) )
    PROTO_T ( int r )
{
    bitpattern rgs = ( bitpattern ) r ;
    where_regmsk |= rgs ;
    /* If rgs corresponds to an A register, we have an effective address */
    if ( rgs & areg_msk ) return ( RegInd ) ;
    return ( Other ) ;
}


/*
    FIND ADDRESSING TYPE OF AN INDEX OPERAND

    The addressing type of the operand given by e1 indexed by e2 times
    some constant is returned.
*/

static int find_ind
    PROTO_N ( ( e1, e2 ) )
    PROTO_T ( exp e1 X exp e2 )
{
    int f1 = find_where ( e1 ) ;
    int f2 = find_where ( e2 ) ;
    if ( f1 == Other ) return ( Other ) ;
    if ( f2 == Dreg || f2 == Areg ) return ( EffAddr ) ;
    return ( Other ) ;
}


/*
    FIND ADDRESSING TYPE OF AN OPERAND

    The addressing type of the operand e is returned.  Meanwhile the
    bitmask of all the registers used in e is built up in where_regmsk.
    This routine should be compared with operand.
*/

static int find_where
    PROTO_N ( ( e ) )
    PROTO_T ( exp e )
{
    bitpattern rm ;
    switch ( name ( e ) ) {

	case val_tag :
	case null_tag :
	    return ( Value ) ;

	case real_tag :
	case string_tag :
	case res_tag :
	    return ( External ) ;

	case regpair_tag :
	    return ( RegPair ) ;

	case apply_general_tag :
	case tail_call_tag :
	case apply_tag :
	    return ( EffAddr ) ;

	case field_tag :
	    return ( find_where ( son ( e ) ) ) ;

	case ident_tag :
	case labst_tag : {
	    switch ( ptno ( e ) ) {
#ifndef tdf3
                case par2_pl :
                case par3_pl :
#endif

		case par_pl : return ( Parameter ) ;
		case var_pl : return ( Variable ) ;
		case reg_pl : {
		    rm = ( bitpattern ) no ( e ) ;
		    where_regmsk |= rm ;
		    /* A register, but what type? */
		    if ( rm & dreg_msk ) return ( Dreg ) ;
		    if ( rm & areg_msk ) return ( Areg ) ;
		    return ( Freg ) ;
		}
	    }
	    break ;
	}

	case name_tag : {
	    exp id = son ( e ) ;
#if 0
	    if((name(sh(e)) == prokhd) &&
	       ((son(id) == nilexp) || (name(son(id)) == proc_tag) ||
		(name(son(id)) == general_proc_tag))){
	      exp proc_cont = getexp(sh(e),nilexp,0,e,nilexp,0,
				     0,cont_tag);
	      /*return find_where(proc_cont);*/
	      e = proc_cont;
	      /*return EffAddr;*/
	      id = son(e);
/*	      return find_where(e);*/
	    }
#endif

	    if ( isglob ( id ) ) return ( External ) ;
	    switch ( ptno ( id ) ) {
#ifndef tdf3
		case par2_pl :
		case par3_pl :
#endif

		case par_pl :
		case var_pl : return ( EffAddr ) ;
		case reg_pl : {
		    rm = ( bitpattern ) no ( id ) ;
		    where_regmsk |= rm ;
		    /* A register, but what type? */
		    if ( rm & dreg_msk ) return ( Dreg ) ;
		    if ( rm & areg_msk ) return ( Areg ) ;
		    return ( Freg ) ;
		}
	    }
	    break ;
	}

	case cont_tag :
	case ass_tag : {
	    exp r = son ( e ) ;
	    switch ( name ( r ) ) {

		case name_tag : {
		    exp id = son ( r ) ;
		    long pt_id = ptno ( id ) ;
		    if ( isvar ( id ) ) return ( find_where ( r ) ) ;
		    if ( isglob ( id ) ) {
			if ( name ( sh ( e ) ) == prokhd ) return ( External ) ;
			return ( Other ) ;
		    }
		    switch ( pt_id ) {
#ifndef tdf3
                        case par2_pl :
                        case par3_pl :
#endif

			case par_pl :
			case var_pl : return ( EffAddr ) ;
			case reg_pl : return ( find_reg_ind ( no ( id ) ) ) ;
		    }
		    break ;
		}

		case cont_tag : {
		    exp rr = son ( r ) ;
		    if ( name ( rr ) == name_tag ) {
			exp id = son ( rr ) ;
			if ( !isvar ( id ) ) break ;
			if ( isglob ( id ) ) return ( Other ) ;
			switch ( ptno ( id ) ) {
#ifndef tdf3
                            case par2_pl :
                            case par3_pl :
#endif

			    case par_pl :
			    case var_pl : return ( EffAddr ) ;
			    case reg_pl : {
				return ( find_reg_ind ( no ( id ) ) ) ;
			    }
			}
		    }
		    break ;
		}

		case reff_tag : {
		    exp rr = son ( r ) ;
		    switch ( name ( rr ) ) {

			case name_tag : {
			    exp id = son ( rr ) ;
			    if ( ptno ( id ) == reg_pl ) {
				return ( find_reg_ind ( no ( id ) ) ) ;
			    }
			    return ( Other ) ;
			}

			case cont_tag : {
			    exp id = son ( son ( rr ) ) ;
			    if ( ptno ( id ) == reg_pl ) {
				return ( find_reg_ind ( no ( id ) ) ) ;
			    }
			    return ( Other ) ;
			}

			case addptr_tag : return ( find_where ( rr ) ) ;
		    }
		    break ;
		}

		case addptr_tag : {
		    exp rr = son ( r ) ;
		    exp eb = bro ( rr ) ;
		    exp ec = simple_exp ( cont_tag ) ;
		    son ( ec ) = rr ;
		    switch ( name ( eb ) ) {
			case name_tag :
			case cont_tag : return ( find_ind ( eb, ec ) ) ;
			case offset_mult_tag : {
			    return ( find_ind ( son ( eb ), ec ) ) ;
			}
		    }
		    break ;
		}
	    }
	    break ;
	}

	case reff_tag :
	case dummy_tag : {
	    exp r = son ( e ) ;
	    switch ( name ( r ) ) {

		case ident_tag : {
		    if ( ptno ( r ) == reg_pl ) {
			return ( find_reg_ind ( no ( r ) ) ) ;
		    }
		    break ;
		}

		case name_tag : {
		    exp id = son ( r ) ;
		    if ( isglob ( id ) ) return ( External ) ;
		    if ( ptno ( r ) == reg_pl ) {
			return ( find_reg_ind ( no ( id ) ) ) ;
		    }
		    break ;
		}

		case cont_tag :
		case ass_tag : {
		    exp id = son ( son ( r ) ) ;
		    if ( isglob ( id ) ) return ( External ) ;
		    if ( ptno ( r ) == reg_pl ) {
			return ( find_reg_ind ( no ( id ) ) ) ;
		    }
		    break ;
		}

		case addptr_tag : return ( find_where ( r ) ) ;
	    }
	    break ;
	}

	case addptr_tag : {
	    exp r = son ( e ) ;
	    exp eb = bro ( r ) ;
	    exp ec = simple_exp ( cont_tag ) ;
	    son ( ec ) = r ;
	    switch ( name ( eb ) ) {
		case name_tag :
		case cont_tag : return ( find_ind ( eb, ec ) ) ;
		case offset_mult_tag : {
		    return ( find_ind ( son ( eb ), ec ) ) ;
		}
	    }
	    break ;
	}

	case diagnose_tag : {
	    exp r = son ( e ) ;
	    return ( find_where ( r ) ) ;
	}
    }
    /* Allow all other operands through */
    return ( Other ) ;
}


/*
    CREATE A WHERE

    A where is created from an expression e and an offset d.  The routine
    find_where is used to calculate the wh_is and wh_regs fields.
*/

where mw
    PROTO_N ( ( e, d ) )
    PROTO_T ( exp e X long d )
{
  where w ;
#if 0

  if ((name(e)==name_tag && name(sh(e)) == prokhd) &&
      !(((son (son(e)) == nilexp || name (son (son(e))) == proc_tag ||
	  name(son(son(e))) == apply_tag ||
	  name(son(son(e))) == apply_general_tag)))) {
    exp proc_cont = getexp(sh(e),nilexp,0,e,nilexp,0,0,cont_tag);
    e = proc_cont;
  }
#endif
  w.wh_exp = e ;
  w.wh_off = d ;
  where_regmsk = 0 ;
  w.wh_is = find_where ( e ) ;
  w.wh_regs = where_regmsk ;
  return ( w ) ;
}


/*
    CREATE A WHERE REPRESENTING A NUMBER

    A where is created corresponding to the integer constant d.
*/

where mnw
    PROTO_N ( ( d ) )
    PROTO_T ( long d )
{
    where w ;
    w.wh_exp = zeroe ;
    w.wh_off = d ;
    w.wh_is = Value ;
    w.wh_regs = 0 ;
    return ( w ) ;
}


/*
    CREATE A WHERE REPRESENTING A FLOATING POINT NUMBER

    A where is created corresponding to the floating point number with
    sign sg (+1, 0 or -1), digits v and exponent e.
*/

where mfw
    PROTO_N ( ( sg, v, e ) )
#if ( FBASE == 10 )
    PROTO_T ( int sg X char *v X int e )
#else
    PROTO_T ( int sg X long *v X int e )
#endif
{
    where w ;
    int i, lv ;
    long lab = next_lab () ;
    exp fe, ft = simple_exp ( internal_tag ) ;
    long fm = new_flpt () ;
    flt *f = &flptnos [ fm ] ;
    f->sign = sg ;
    f->exp = e ;
#if ( FBASE == 10 )
    lv = strlen ( v ) ;
    for ( i = 0 ; i < lv ; i++ ) f->mant [i] = v [i] - '0' ;
#else
    i = 0 ;
    while ( v [i] != -1 ) {
	f->mant [i] = v [i] ;
	i++ ;
    }
    lv = i ;
#endif
    for ( i = lv ; i < MANT_SIZE ; i++ ) f->mant [i] = 0 ;
    fe = new_exp ( realsh, nilexp, fm, real_tag ) ;
    make_constant ( lab, fe ) ;
    no ( ft ) = lab ;
    w.wh_exp = ft ;
    w.wh_off = 0 ;
    w.wh_is = Value ;
    w.wh_regs = 0 ;
    return ( w ) ;
}


/*
    CONSTRUCT A REGISTER PAIR

    A where is created corresponding to the register pair a:b.  Both
    a and b must represent registers.
*/

where regpair
    PROTO_N ( ( a, b ) )
    PROTO_T ( where a X where b )
{
    where w ;
    exp ea = a.wh_exp ;
    exp eb = b.wh_exp ;
    w.wh_exp = getexp ( realsh, eb, 0, ea, nilexp, 0, 0, regpair_tag ) ;
    w.wh_off = 0 ;
    w.wh_is = RegPair ;
    where_regmsk = 0 ;
    if ( find_where ( ea ) != Dreg || find_where ( eb ) != Dreg ) {
	error ( "Illegal register pair" ) ;
    }
    w.wh_regs = where_regmsk ;
    return ( w ) ;
}


/*
    CONSTANT WHERE'S

    These represent commonly used numerical constants and registers.
    zero is the integer 0.  RW[] is the array of all registers.  A6_4
    represents a position on the stack.  A0_p, A1_p, SP_p and A6_4_p
    represent pointers.  D0_D1 is a register pair.
*/

where zero ;
where fzero ;
where RW [ NO_OF_REGS ] ;
where A6_4, A0_p, A1_p, SP_p, A6_4_p, D0_D1 ;
where dummy_double_dest ;
where firstlocal;


/*
    CONSTANT EXP'S

    These expressions are the wh_exp fields of the where's above.
*/

exp zeroe ;
static exp fzeroe ;
static exp RE [ NO_OF_REGS ] ;
static exp E_long, E_float, E_ptr, E_A6_4 ;
static exp firstlocalid;

/*
    SET UP CONSTANTS WHERE'S

    The constant where's are initialized.
*/

void init_wheres
    PROTO_Z ()
{
    int i ;

    /* Set up the exps corresponding to 0 */
    zeroe = new_exp ( botsh, nilexp, 0, val_tag ) ;
    fzeroe = new_exp ( realsh, nilexp, fzero_no, real_tag ) ;

    /* Set up the corresponding wheres */
    zero = zw ( zeroe ) ;
    fzero = zw ( fzeroe ) ;

    /* Create some dummy exp's */
    E_long = new_exp ( slongsh, nilexp, 0, val_tag ) ;
    E_float = new_exp ( realsh, nilexp, 0, real_tag ) ;
    E_ptr = new_exp ( ptrsh, E_long, 0, cont_tag ) ;
    E_A6_4 = new_exp ( botsh, E_ptr, 0, ident_tag ) ;
    ptno ( E_A6_4 ) = var_pl ;

    /* Set up the exp's corresponding to the utility registers */
    for ( i = 0 ; i < NO_OF_REGS ; i++ ) {
	exp t = E_float ;
	if ( is_dreg ( i ) ) t = E_long ;
	if ( is_areg ( i ) ) t = E_ptr ;
	RE [i] = new_exp ( botsh, t, regmsk ( i ), ident_tag ) ;
	ptno ( RE [i] ) = reg_pl ;
	RW [i] = zw ( new_exp ( slongsh, RE [i], 0, name_tag ) ) ;
    }

    /* Set up some pointer where's */
    A0_p = zw ( new_exp ( ptrsh, A0.wh_exp, 0, cont_tag ) ) ;
    A1_p = zw ( new_exp ( ptrsh, A1.wh_exp, 0, cont_tag ) ) ;
    SP_p = zw ( new_exp ( ptrsh, SP.wh_exp, 0, cont_tag ) ) ;
    A6_4 = zw ( new_exp ( slongsh, E_A6_4, -32, name_tag ) ) ;
    A6_4_p = zw ( new_exp ( ptrsh, A6_4.wh_exp, 0, cont_tag ) ) ;

    /* Set up the register pair D0:D1 */
    D0_D1 = regpair ( D0, D1 ) ;

    dummy_double_dest = zw(get_dummy_double_dest()) ;

    firstlocalid = new_exp (f_bottom, E_long, 0, ident_tag);
    ptno(firstlocalid) = var_pl;
    firstlocal = zw (new_exp (slongsh, firstlocalid, -32, name_tag));
}


/*
    ARE TWO WHERE'S EQUAL?

    This is actually an auxiliary routine.  eq_where ( a, b ) is a macro
    defined to be eq_where_a ( a, b, 1 ).  It returns 1 if the where's
    a and b are equal, but 0 otherwise.
*/

bool eq_where_a
    PROTO_N ( ( wa, wb, first ) )
    PROTO_T ( where wa X where wb X int first )
{
    where sa, sb ;
    exp a = wa.wh_exp ;
    exp b = wb.wh_exp ;
    char na = name ( a ) ;
    char nb = name ( b ) ;

    if ( wa.wh_off != wb.wh_off ) return ( 0 ) ;
    if ( a == b ) return ( 1 ) ;

    if ( na == nb ) {

	switch ( na ) {

	    case val_tag : {
		return ( no ( a ) == no ( b ) ? 1 : 0 ) ;
	    }

	    case ident_tag : {
		if ( no ( a ) != no ( b ) ) return ( 0 ) ;
		return ( ptno ( a ) == ptno ( b ) ? 1 : 0 ) ;
	    }

	    case name_tag :
	    case field_tag :
	    case reff_tag : {
		if ( no ( a ) != no ( b ) ) return ( 0 ) ;
		sa.wh_exp = son ( a ) ;
		sa.wh_off = 0 ;
		sb.wh_exp = son ( b ) ;
		sb.wh_off = 0 ;
		return ( eq_where_a ( sa, sb, 0 ) ) ;
	    }

	    case cont_tag : {
		sa.wh_exp = son ( a ) ;
		sa.wh_off = 0 ;
		sb.wh_exp = son ( b ) ;
		sb.wh_off = 0 ;
		return ( eq_where_a ( sa, sb, 0 ) ) ;
	    }

	    case real_tag : {
		int i ;
		bool z = 1 ;
		flt fa, fb ;
		fa = flptnos [ no ( a ) ] ;
		fb = flptnos [ no ( b ) ] ;

		for ( i = 0 ; i < MANT_SIZE ; i++ ) {
		    if ( fa.mant [i] != fb.mant [i] ) return ( 0 ) ;
		    if ( fa.mant [i] ) z = 0 ;
		}

		if ( z ) return ( 1 ) ;
		if ( fa.exp != fb.exp ) return ( 0 ) ;
		if ( fa.sign != fb.sign ) return ( 0 ) ;
		return ( 1 ) ;
	    }
	}
	return ( 0 ) ;
    }

    if ( first && na == name_tag && nb == ident_tag ) {
	if ( no ( a ) ) return ( 0 ) ;
	sa.wh_exp = son ( a ) ;
	sa.wh_off = 0 ;
	return ( eq_where_a ( sa, wb, 0 ) ) ;
    }

    if ( first && nb == name_tag && na == ident_tag ) {
	if ( no ( b ) ) return ( 0 ) ;
	sb.wh_exp = son ( b ) ;
	sb.wh_off = 0 ;
	return ( eq_where_a ( wa, sb, 0 ) ) ;
    }

    if ( ( na == cont_tag || na == ass_tag ) &&
	 name ( son ( a ) ) == name_tag &&
	 isvar ( son ( son ( a ) ) ) &&
	 ( nb == ident_tag || nb == name_tag ) ) {
	if ( no ( son ( a ) ) ) return ( 0 ) ;
	sa.wh_exp = son ( son ( a ) ) ;
	sa.wh_off = 0 ;
	return ( eq_where_a ( sa, wb, 0 ) ) ;
    }

    if ( ( nb == cont_tag || nb == ass_tag ) &&
	 name ( son ( b ) ) == name_tag &&
	 isvar ( son ( son ( b ) ) ) &&
	 ( na == ident_tag || na == name_tag ) ) {
	if ( no ( son ( b ) ) ) return ( 0 ) ;
	sb.wh_exp = son ( son ( b ) ) ;
	sb.wh_off = 0 ;
	return ( eq_where_a ( wa, sb, 0 ) ) ;
    }


    if ( ( na == ass_tag && nb == cont_tag ) ||
	 ( nb == ass_tag && na == cont_tag ) ) {
	sa.wh_exp = son ( a ) ;
	sa.wh_off = 0 ;
	sb.wh_exp = son ( b ) ;
	sb.wh_off = 0 ;
	return ( eq_where_a ( sa, sb, 0 ) ) ;
    }

    return ( 0 ) ;
}
