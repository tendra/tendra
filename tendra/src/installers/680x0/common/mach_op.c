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
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/mach_op.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: mach_op.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.2  1997/10/29 10:22:21  ma
Replaced use_alloca with has_alloca.

Revision 1.1.1.1  1997/10/13 12:42:55  ma
First version.

Revision 1.3  1997/09/25 06:45:15  ma
All general_proc tests passed

Revision 1.2  1997/06/18 10:09:37  ma
Checking in before merging with Input Baseline changes.

Revision 1.1.1.1  1997/03/14 07:50:15  ma
Imported from DRA

 * Revision 1.2  1996/09/20  13:51:39  john
 * *** empty log message ***
 *
 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.1  93/02/22  17:16:07  17:16:07  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "utility.h"

#ifndef tdf3
#define  par2_pl        4       /* procedure argument accessed by use of A5 */
#define  par3_pl        5       /* procedure argument accessed by use of SP */
#endif


/*
    LIST OF FREE OPERANDS

    A list of free mach_op's, linked by the plus field.
*/

static mach_op *mach_op_list = null ;


/*
    ALLOCATE A NEW OPERAND

    This routine returns a pointer to a mach_op.  This is taken from the
    list of free mach_op's.
*/
#ifndef tdf3
#ifdef EBUG
static int next_id = 0 ;
#endif
#endif

mach_op *new_mach_op
    PROTO_Z ()
{
    mach_op *p ;
    if ( mach_op_list == null ) {
	int i, n = 1000 ;
	p = alloc_nof ( mach_op, n ) ;
	for ( i = 0 ; i < n - 1 ; i++ ) {
	    ( p + i )->plus = p + ( i + 1 ) ;
	    ( p + i )->of = null ;
	}
	( p + ( n - 1 ) )->plus = null ;
	( p + ( n - 1 ) )->of = null ;
	mach_op_list = p ;
    }
    p = mach_op_list ;
    if ( p->of ) {
	mach_op *q = p->of ;
	mach_op_list = q ;
	while ( q->plus ) q = q->plus ;
	q->plus = p->plus ;
    } else {
	mach_op_list = p->plus ;
    }
    p->def.num = 0 ;
    p->plus = null ;
    p->of = null ;
#ifndef tdf3
#ifdef EBUG
    if (next_id == 70) {
       int dummy = next_id ;
    }

    p->id = next_id ++ ;
#endif
#endif
    return ( p ) ;
}


/*
    FREE AN OPERAND

    A mach_op is freed by adding it to the list of free mach_op's.
*/

void free_mach_op
    PROTO_N ( ( ptr ) )
    PROTO_T ( mach_op *ptr )
{
    mach_op *p = ptr ;
    if ( p == null ) return ;
    while ( p->plus ) p = p->plus ;
    p->plus = mach_op_list ;
    mach_op_list = ptr ;
    return ;
}


/*
    SPECIAL LABELS INFORMATION

    A special label consists of the label prefix, "L", followed by the
    special label identifier, followed by the value of special_no for
    the current procedure.  A particular special label is that with
    identifier special_str.
*/

long special_no = 0 ;
char *special_str = "S" ;


/*
    TEMPORARY REGISTER STATUS

    This records the number of temporary registers which have been allocated
    at any given moment, any temporary register preferences and the last
    temporary register used.
*/

int tmp_reg_status = 0 ;
int tmp_reg_prefer = 0 ;
static int last_reg = 0 ;


/*
    FIND THE NUMBER OF THE NEXT TEMPORARY REGISTER

    This is a look-ahead routine to find what the next temporary register
    allocated will be.  Let X denote the prefered temporary register
    (if specified) and Y denote any A-register used in the procedure
    but not currently active.

    If X is specified, it will always be the first temporary register
    returned.  The second will be Y, if that exists, or A1, unless
    this equals X, if which case A0 is used.

    If X is not specified, the first temporary register will be Y,
    if that exists, or A1.  The second will be A1 if Y exists, or
    A0 otherwise.

    Under very rare conditions a third temporary register is required.
    In these cases D0 always suffices.
*/

int next_tmp_reg
    PROTO_Z ()
{
    int r ;
    int t = tmp_reg_status ;
    if ( t > 1 ) {
	debug_warning ( "Temporary D-register used" ) ;
	r = REG_D0 ;
    } else if ( tmp_reg_prefer ) {
	if ( t == 0 ) {
	    r = tmp_reg_prefer ;
	    last_reg = r ;
	} else {
	    bitpattern na = ( regsinuse | reuseables | regsindec ) ;
	    bitpattern a = regsinproc & ~na & 0x3c00 ;
	    r = ( a ? reg ( a ) : REG_A1 ) ;
	    if ( r == last_reg ) r = REG_A0 ;
	}
    } else {
	bitpattern na = ( regsinuse | reuseables | regsindec ) ;
	bitpattern a = regsinproc & ~na & 0x3c00 ;
	if ( t == 0 ) {
	    r = ( a ? reg ( a ) : REG_A1 ) ;
	    last_reg = r ;
	} else {
	    r = ( a ? REG_A1 : REG_A0 ) ;
	    if ( r == last_reg ) r = ( r == REG_A0 ? REG_A1 : REG_A0 ) ;
	}
    }
    return ( r ) ;
}


/*
    AVOID A GIVEN TEMPORARY REGISTER

    This marks the given register number as to be avoided by pretending
    that it was the previous temporary register.
*/

void avoid_tmp_reg
    PROTO_N ( ( r ) )
    PROTO_T ( int r )
{
    last_reg = r ;
    tmp_reg_status++ ;
    return ;
}


/*
    MOVE AN OPERAND INTO A TEMPORARY REGISTER

    It is sometimes necessary to move an operand into a temporary address
    register.  A move instruction (given by instr) is output, and the
    number of the temporary register is returned.
*/

int tmp_reg
    PROTO_N ( ( instr, ptr ) )
    PROTO_T ( int instr X mach_op *ptr )
{
    int t = tmp_reg_status ;
    int r = next_tmp_reg () ;
    mach_op *p = new_mach_op () ;
    p->type = MACH_REG ;
    p->def.num = ( long ) r ;
    make_instr_aux ( instr, ptr, p, regmsk ( r ), 1 ) ;
    regsinproc |= regmsk ( r ) ;
    tmp_reg_status = t + 1 ;
    return ( r ) ;
}


/*
    TEST IF A REGISTER IS USED IN AN OPERAND

    This routine returns 1 if register r is used in the operand op.
*/

bool check_op
    PROTO_N ( ( op, r ) )
    PROTO_T ( mach_op *op X int r )
{
    if ( op == null ) return ( 0 ) ;
    switch ( op->type ) {

	case MACH_CONT : return ( ( op->def.num ) & regmsk ( r ) ? 1 : 0 ) ;

	case MACH_REG :
	case MACH_DEC :
	case MACH_INC : return ( op->def.num == r ? 1 : 0 ) ;

	case MACH_BF : return ( check_op ( op->of, r ) ) ;

	case MACH_RPAIR : {
	    if ( op->def.num == r ) return ( 1 ) ;
	    return ( op->plus->def.num == r ? 1 : 0 ) ;
	}
    }
    return ( 0 ) ;
}


/*
    TEST IF TWO OPERANDS ARE EQUAL

    This returns 1 if the two operands have equal effect.  Note that,
    for example, consecutive uses of the same pre-decremented register,
    although having the same representation, are not equal in this
    context.
*/

bool equal_op
    PROTO_N ( ( op1, op2 ) )
    PROTO_T ( mach_op *op1 X mach_op *op2 )
{
    mach_op *p1 = op1, *p2 = op2 ;
    while ( p1 && p2 ) {
	if ( p1->type != p2->type ) return ( 0 ) ;
	if ( p1->type == MACH_DEC || p1->type == MACH_INC ) return ( 0 ) ;
	if ( p1->def.num != p2->def.num ) return ( 0 ) ;
	if ( p1->plus ) {
	    if ( p2->plus == null ) return ( 0 ) ;
	    if ( !equal_op ( p1->plus, p2->plus ) ) return ( 0 ) ;
	} else {
	    if ( p2->plus ) return ( 0 ) ;
	}
	p1 = p1->of ;
	p2 = p2->of ;
    }
    return ( p1 == p2 ? 1 : 0 ) ;
}


/*
    MAKE AN INTEGER CONSTANT OPERAND

    This and the subsequent routines are used to allocate machine operands.
    The constructions are simple applications of the descriptions given
    in mach.h.  They need very little other comment.
*/

mach_op *make_value
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_VAL ;
    p->def.num = n ;
    return ( p ) ;
}


/*
    MAKE AN INTEGER DATA OPERAND
*/

mach_op *make_int_data
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_VALQ ;
    p->def.num = n ;
    return ( p ) ;
}


/*
    MAKE A HEXADECIMAL INTEGER CONSTANT OPERAND
*/

mach_op *make_hex_value
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_HEX ;
    p->def.num = n ;
    return ( p ) ;
}


/*
    MAKE A HEXADECIMAL INTEGER CONSTANT DATA OPERAND
*/

mach_op *make_hex_data
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_HEXQ ;
    p->def.num = n ;
    return ( p ) ;
}


/*
    MAKE A FLOATING POINT DATA OPERAND
*/

mach_op *make_float_data
    PROTO_N ( ( f ) )
    PROTO_T ( flt *f )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_FLOATQ ;
    p->def.fp = f ;
    return ( p ) ;
}


/*
    MAKE A LABEL OPERAND
*/

mach_op *make_lab
    PROTO_N ( ( n, d ) )
    PROTO_T ( long n X long d )
{
    mach_op *p1 = new_mach_op () ;
    p1->type = MACH_LAB ;
    p1->def.num = n ;
    if ( d ) {
	mach_op *p2 = new_mach_op () ;
	p2->type = MACH_VAL ;
	p2->def.num = d ;
	p1->plus = p2 ;
    }
    return ( p1 ) ;
}


/*
    MAKE A LABEL DATA OPERAND
*/

mach_op *make_lab_data
    PROTO_N ( ( n, d ) )
    PROTO_T ( long n X long d )
{
    mach_op *p1 = new_mach_op () ;
    p1->type = MACH_LABQ ;
    p1->def.num = n ;
    if ( d ) {
	mach_op *p2 = new_mach_op () ;
	p2->type = MACH_VAL ;
	p2->def.num = d ;
	p1->plus = p2 ;
    }
    return ( p1 ) ;
}


/*
    MAKE AN OPERAND CORRESPONDING TO THE DIFFERENCE OF TWO LABELS
*/

mach_op *make_lab_diff
    PROTO_N ( ( a, b ) )
    PROTO_T ( long a X long b )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    mach_op *p3 = new_mach_op () ;
    p1->type = MACH_LABQ ;
    p1->def.num = a ;
    p1->plus = p2 ;
    p2->type = MACH_NEG ;
    p2->plus = p3 ;
    p3->type = MACH_LABQ ;
    p3->def.num = b ;
    return ( p1 ) ;
}


/*
    MAKE AN EXTERNAL OPERAND
*/

mach_op *make_extern
    PROTO_N ( ( nm, d ) )
    PROTO_T ( char *nm X long d )
{
    mach_op *p1 = new_mach_op () ;
    p1->type = MACH_EXT ;
    p1->def.str = nm ;
    if ( d ) {
	mach_op *p2 = new_mach_op () ;
	p2->type = MACH_VAL ;
	p2->def.num = d ;
	p1->plus = p2 ;
    }
    return ( p1 ) ;
}


/*
    MAKE AN EXTERNAL DATA OPERAND
*/

mach_op *make_extern_data
    PROTO_N ( ( nm, d ) )
    PROTO_T ( char *nm X long d )
{
    mach_op *p1 = new_mach_op () ;
    p1->type = MACH_EXTQ ;
    p1->def.str = nm ;
    if ( d ) {
	mach_op *p2 = new_mach_op () ;
	p2->type = MACH_VAL ;
	p2->def.num = d ;
	p1->plus = p2 ;
    }
    return ( p1 ) ;
}


/*
    MAKE A SPECIAL LABEL OPERAND
*/

mach_op *make_special
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_SPEC ;
    p->def.str = nm ;
    return ( p ) ;
}


/*
    MAKE A SPECIAL LABEL DATA OPERAND
*/

mach_op *make_special_data
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_SPECQ ;
    p->def.str = nm ;
    return ( p ) ;
}


/*
    MAKE A LABEL INDIRECT OPERAND
*/

mach_op *make_lab_ind
    PROTO_N ( ( n, d ) )
    PROTO_T ( long n X long d )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    p1->type = MACH_CONT ;
    p1->def.num = 0 ;
    p1->of = p2 ;
    p2->type = MACH_LAB ;
    p2->def.num = n ;
    if ( d ) {
	mach_op *p3 = new_mach_op () ;
	p3->type = MACH_VAL ;
	p3->def.num = d ;
	p2->plus = p3 ;
    }
    return ( p1 ) ;
}


/*
    MAKE AN EXTERNAL INDIRECT OPERAND
*/

mach_op *make_extern_ind
    PROTO_N ( ( nm, d ) )
    PROTO_T ( char *nm X long d )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    p1->type = MACH_CONT ;
    p1->def.num = 0 ;
    p1->of = p2 ;
    p2->type = MACH_EXT ;
    p2->def.str = nm ;
    if ( d ) {
	mach_op *p3 = new_mach_op () ;
	p3->type = MACH_VAL ;
	p3->def.num = d ;
	p2->plus = p3 ;
    }
    return ( p1 ) ;
}


/*
    MAKE A REGISTER DIRECT OPERAND
*/

mach_op *make_register
    PROTO_N ( ( r ) )
    PROTO_T ( int r )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_REG ;
    p->def.num = ( long ) r ;
    return ( p ) ;
}

/*
    MAKE PSEUDO OPERAND REPRESENTING LDISP
    (the space between sp and the parameters at procedure entry)
*/

mach_op *make_ldisp
    PROTO_N ( ( offset ) )
    PROTO_T ( long offset )
{
    mach_op *p1 = new_mach_op () ;
    p1->type = MACH_SPEC ;
    p1->def.str = special_str ;
    if (offset) {
       p1->plus = new_mach_op () ;
       p1->plus->type = MACH_VAL ;
       p1->plus->def.num = offset ;
    }
    return ( p1 ) ;
}


/*
    MAKE A REGISTER INDIRECT WITH DISPLACEMENT OPERAND

    This is the first example where a temporary register may be required.
    Under very rare circumstances, we may be trying to address relative
    to a D-register, if which case we need to use a temporary A-register
    instead.
*/

mach_op *make_indirect
    PROTO_N ( ( r, d ) )
    PROTO_T ( int r X long d )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    p1->type = MACH_CONT ;
    p1->def.num = regmsk ( r ) ;
    p2->type = MACH_REG ;
    p2->def.num = ( long ) r ;
    if ( is_dreg ( r ) ) {
	int t = tmp_reg ( m_movl, p2 ) ;
	p2 = new_mach_op () ;
	p2->type = MACH_REG ;
	p2->def.num = ( long ) t ;
	p1->def.num = regmsk ( t ) ;
    }
    p1->of = p2 ;
    if ( d ) {
	mach_op *p3 = new_mach_op () ;
	p3->type = MACH_VAL ;
	p3->def.num = d ;
	p2->plus = p3 ;
    }
    return ( p1 ) ;
}


/*
    MAKE A APPLICATION POINTER INDIRECT WITH DISPLACEMENT OPERAND

    Since we don't want to use an applications pointer unless absolutely
    necessary, this is often changed into a stack pointer indirect
    with displacement operand.
*/

mach_op *make_rel_ap
    PROTO_N ( ( d ) )
    PROTO_T ( long d )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    p1->type = MACH_CONT ;
    p1->def.num = 0 ;
    p2->type = MACH_REG ;
    p1->of = p2 ;
    if ( d > 0 ) {
	if ( !used_stack ) {
	    /* Use stack pointer instead of application pointer */
	    long s = stack_size + stack_change ;
	    mach_op *p3 = new_mach_op () ;
	    mach_op *p4 = new_mach_op () ;
	    p2->def.num = ( long ) REG_SP ;
	    p3->type = MACH_SPEC ;
	    p3->def.str = special_str ;
	    p2->plus = p3 ;
	    p4->type = MACH_VAL ;
	    p4->def.num = d - s / 8 ;
	    p3->plus = p4 ;
	    used_ldisp = 1 ;
	    return ( p1 ) ;
	}
	d += 4 ;
    }
    p2->def.num = ( long ) REG_AP ;
    if ( d ) {
	mach_op *p3 = new_mach_op () ;
	p3->type = MACH_VAL ;
	p3->def.num = d ;
	p2->plus = p3 ;
    }
    used_stack = 1 ;
    return ( p1 ) ;
}

#ifndef tdf3
/*
    MAKE A 2. APPLICATION POINTER INDIRECT WITH DISPLACEMENT OPERAND

    This application pointer A5 is used by general proc. to access
    the caller parameters, when there are a dynamic number of callees.
*/

mach_op *make_rel_ap2
    PROTO_N ( ( d ) )
    PROTO_T ( long d )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    mach_op *p3 = new_mach_op () ;

    p1->type = MACH_CONT ;
    p1->def.num = 0 ;
    p2->type = MACH_REG ;
    p1->of = p2 ;
    p2->def.num = ( long ) REG_A5 ;

    p3->type = MACH_VAL ;
    p3->def.num = d ;
    p2->plus = p3 ;

    used_stack = 1 ;
    return ( p1 ) ;
}
/*
   Used to access caller parrameters in the postlude.
 */

mach_op *make_rel_sp
    PROTO_N ( ( d ) )
    PROTO_T ( long d )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    mach_op *p3 = new_mach_op () ;
    long s = stack_size + stack_change ;

    p1->type = MACH_CONT ;
    p1->def.num = 0 ;
    p1->of = p2 ;

    p2->type = MACH_REG ;
    p2->def.num = ( long ) REG_SP ;
    p2->plus = p3 ;

    p3->type = MACH_VAL ;
    p3->def.num = d - s / 8 ;

    return ( p1 ) ;
}

#endif

/*
    MAKE A REGISTER INDIRECT WITH INDEX OPERAND

    Again we have to be careful, in case r1 is a D-register.
*/

mach_op *make_reg_index
    PROTO_N ( ( r1, r2, d, sf ) )
    PROTO_T ( int r1 X int r2 X long d X int sf )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    mach_op *p3 = new_mach_op () ;
    mach_op *p4 = new_mach_op () ;
    p1->type = MACH_CONT ;
    p2->type = MACH_REG ;
    p2->def.num = ( long ) r1 ;
    if ( is_dreg ( r1 ) ) {
	int t = tmp_reg ( m_movl, p2 ) ;
	p2 = new_mach_op () ;
	p2->type = MACH_REG ;
	p2->def.num = ( long ) t ;
	p1->def.num = ( regmsk ( t ) | regmsk ( r2 ) ) ;
    } else {
	p1->def.num = ( regmsk ( r1 ) | regmsk ( r2 ) ) ;
    }
    p1->of = p2 ;
    p2->plus = p3 ;
    p3->type = MACH_SCALE ;
    p3->def.num = ( long ) sf ;
    p3->of = p4 ;
    p4->type = MACH_REG ;
    p4->def.num = ( long ) r2 ;
    if ( d ) {
	mach_op *p5 = new_mach_op () ;
	p5->type = MACH_VAL ;
	p5->def.num = d ;
	p3->plus = p5 ;
    }
    return ( p1 ) ;
}


/*
    MAKE A APPLICATION POINTER INDEXED WITH DISPLACEMENT OPERAND

    It is always quicker to do this using a temporary register rather
    than using the complex addressing mode.  However we do use the
    latter course when temporary registers are short.

    Typ determines the type of the application pointer.
*/

mach_op *_make_ind_rel_ap
    PROTO_N ( ( d, e, typ ) )
    PROTO_T ( long d X long e X int typ )
{
    mach_op *p1, *p2 ;

    switch (typ) {
    case par2_pl :
      p2 = make_rel_ap2 ( d ) ;
      break ;
    case par3_pl :
      p2 = make_rel_sp ( d ) ;
      break ;
    default :
      p2 = make_rel_ap ( d ) ;
    }

    if ( tmp_reg_status < 2 ) {
	int t = tmp_reg ( m_movl, p2 ) ;
	return ( make_indirect ( t, e ) ) ;
    }

    debug_warning ( "Complex operand" ) ;

    p1 = new_mach_op () ;
    p1->type = MACH_CONT ;
    p1->def.num = 0 ;
    p1->of = p2 ;
    if ( e ) {
	mach_op *p3 = new_mach_op () ;
	p3->type = MACH_VAL ;
	p3->def.num = e ;
	p2->plus = p3 ;
    }
    return ( p1 ) ;
}

mach_op *make_ind_rel_ap
    PROTO_N ( ( d, e) )
    PROTO_T ( long d X long e )
{
   return _make_ind_rel_ap ( d, e, 0 ) ;
}

mach_op *make_ind_rel_ap2
    PROTO_N ( ( d, e) )
    PROTO_T ( long d X long e )
{
   return _make_ind_rel_ap ( d, e, par2_pl ) ;
}
mach_op *make_ind_rel_ap3
    PROTO_N ( ( d, e) )
    PROTO_T ( long d X long e )
{
   return _make_ind_rel_ap ( d, e, par3_pl ) ;
}



/*
    MAKE A PRE-DECREMENT STACK POINTER OPERAND
*/

mach_op *make_dec_sp
    PROTO_Z ()
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_DEC ;
    p->def.num = ( long ) REG_SP ;
    return ( p ) ;
}


/*
    MAKE A POST-INCREMENT STACK POINTER OPERAND
*/

mach_op *make_inc_sp
    PROTO_Z ()
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_INC ;
    p->def.num = ( long ) REG_SP ;
    return ( p ) ;
}

#ifndef tdf3
/*
    MAKE A PRE-DECREMENT REGISTER OPERAND
*/

mach_op *make_predec
    PROTO_N ( ( r ) )
    PROTO_T ( int r )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_DEC ;
    p->def.num = ( long ) r ;
    return ( p ) ;
}
#endif

/*
    MAKE A POSTINCREMENT REGISTER OPERAND
*/

mach_op *make_postinc
    PROTO_N ( ( r ) )
    PROTO_T ( int r )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_INC ;
    p->def.num = ( long ) r ;
    return ( p ) ;
}


/*
    MAKE A REGISTER PAIR
*/

mach_op *make_reg_pair
    PROTO_N ( ( r1, r2 ) )
    PROTO_T ( int r1 X int r2 )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    p1->type = MACH_RPAIR ;
    p1->def.num = ( long ) r1 ;
    p1->plus = p2 ;
    p2->type = MACH_REG ;
    p2->def.num = ( long ) r2 ;
    return ( p1 ) ;
}


/*
    MAKE AN INDEX OPERAND

    The machine operands op1 and op2 are turned into an index operand
    with scale factor sf.  Unless op1 is very simple or temporary
    registers are short, it is always quicker to move the contents of
    op1 into a temporary register.  A temporary register may also be
    required for op2, but hopefully not too often.
*/

mach_op *make_index_op
    PROTO_N ( ( op1, op2, sf ) )
    PROTO_T ( mach_op *op1 X mach_op *op2 X int sf )
{
    bitpattern u ;
    bool use_tmp = 1 ;
    mach_op *p1, *p2 = new_mach_op () ;

    if ( op1->type != MACH_CONT ) {
	error ( "Illegal indexing operand" ) ;
	return ( null ) ;
    }

    p1 = op1->of ;
    u = op1->def.num ;
    if ( p1->type == MACH_REG ) {
	use_tmp = is_dreg ( p1->def.num ) ;
    } else if ( tmp_reg_status && op2->type != MACH_REG ) {
	if ( p1->type == MACH_EXT && p1->plus == null ) {
	    p1->type = MACH_EXTQ ;
	    use_tmp = 0 ;
	} else if ( p1->type == MACH_CONT ) {
	    mach_op *q = p1->of ;
	    if ( q->type == MACH_REG ) {
		q = q->plus ;
		if ( q == null || q->type != MACH_SCALE ) use_tmp = 0 ;
	    }
	}
    }

    if ( use_tmp ) {
	int t = tmp_reg ( m_movl, p1 ) ;
	p1 = new_mach_op () ;
	p1->type = MACH_REG ;
	p1->def.num = ( long ) t ;
	u = regmsk ( t ) ;
    }
    op1->of = p1 ;
    p2->type = MACH_SCALE ;
    p2->def.num = ( long ) sf ;
    p2->plus = p1->plus ;
    p1->plus = p2 ;
    if ( op2->type == MACH_REG ) {
	u |= regmsk ( op2->def.num ) ;
    } else {
	int t = tmp_reg ( m_movl, op2 ) ;
	op2 = new_mach_op () ;
	op2->type = MACH_REG ;
	op2->def.num = ( long ) t ;
	u |= regmsk ( t ) ;
    }
    p2->of = op2 ;
    op1->def.num = u ;
    return ( op1 ) ;
}


/*
    MAKE A BITFIELD OPERAND

    The machine operand op is turned into the corresponding bitfield
    operand.
*/

mach_op *make_bitfield_op
    PROTO_N ( ( op, bf_off, bf_bits ) )
    PROTO_T ( mach_op *op X int bf_off X int bf_bits )
{
    mach_op *p1 = new_mach_op () ;
    mach_op *p2 = new_mach_op () ;
    p1->type = MACH_BF ;
    p1->def.num = ( long ) bf_off ;
    p1->plus = p2 ;
    p1->of = op ;
    p2->type = MACH_VAL ;
    p2->def.num = ( long ) bf_bits ;
    return ( p1 ) ;
}
