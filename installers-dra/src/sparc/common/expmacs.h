/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef EXPMACS_INCLUDED
#define EXPMACS_INCLUDED

#include "bitsmacs.h"

/*
    THE NIL EXPRESSION
*/

#define nilexp				NULL


/*
    MAIN COMPONENTS OF AN EXPRESSION
*/

#define son( x )			( ( x )->sonf.e )
#define bro( x )			( ( x )->brof.e )
#define last( x )			( ( x )->lastf )
#define name( x )			( ( x )->namef )
#define sh( x )				( ( x )->shf )
#define pt( x )				( ( x )->ptf.e )
#define props( x )			( ( x )->propsf )
#define no( x )				( ( x )->numf.l )
#define parked( x )			( ( x )->park )

#ifdef NEWDIAGS
#define dgf( x )			( ( x )->diagf)
#endif


/*
    ALTERNATIVE COMPONENTS OF AN EXPRESSION
*/

#define brog( x )			( ( x )->brof.glob )
#define nostr( x )			( ( x )->numf.str )
#define ptno( x )			( ( x )->ptf.l )
#define sonno( x )			( ( x )->sonf.l )
#define fno( x )			( ( x )->numf.f )

#ifndef NEWDIAGS
#define dno( x )			( ( x )->numf.d )
#endif

#define uno( x )			( ( x )->numf.ui )


/*
    MACROS FOR SETTING COMPONENTS OF AN EXPRESSION
*/

#define setbro( x, b )			bro ( x ) = ( b )
#define setsh( x, b )			sh ( x ) = ( b )
#define setson( x, b )			son ( x ) = ( b )
#define setpt( x, b )			pt ( x ) = ( b )
#define setlast( x )			last ( x ) = 1 
#define clearlast( x )			last ( x ) = 0 
#define setname( x, n )			name ( x ) = ( n )
#define setfather( f, s )		setbro ( s, f ) ; setlast ( s )


/*
    COMPONENTS OF SHAPES
*/

#define shape_size( x )			( ( x )->numf.l )
#define al2ul( x )			( ( unsigned long )\
					 ( ( x )->al.al_val.al ) )
#define align_of( x )			( ( x )->brof.ald )
#define shape_align( x )		al2ul ( align_of ( x ) )
#define al1_of( x )			( ( x )->sonf.ald )
#define al1( x )			al2ul ( al1_of ( x ) )
#define al2_of( x )			( ( x )->ptf.ald )
#define al2( x )			al2ul ( al2_of ( x ) )
#define is_signed( x )			( ( x )->lastf )


/*
    ALTERNATIVE USES OF PROPS FIELD
*/

#define test_number( x )		(props ( x ) & 0xf)
#define settest_number( x, t )		props ( x ) = ((props(x) & ~0xf) |\
						       ( t ))

#define round_number( x )		( props ( x ) >> 3 )
#define setround_number( x, r )		props ( x ) = ( props ( x ) & 0x7 ) |\
						      ( ( r ) << 3 )
#define fstack_pos_of( x )		props ( x )


/*
    MACROS FOR MANIPULATING PROPERTIES
*/

#define pset( x, m )	props ( x ) = ( prop ) ( props ( x ) | ( m ) )
#define pclr( x, m )	props ( x ) = ( prop ) ( props ( x ) & ~( m ) )
#define ptst( x, m )	(( props ( x ) & ( m ) ) != 0)


/*
    PROPERTIES OF CONSTRUCTS WITH EXCEPTIONS
*/

#define setjmp_dest( x, d )		{ setpt ( x, d ) ;\
					  no ( son ( d ) )++ ; }
#define seterr_code( x, d )		props ( x ) = ( d )
#define isov( x )			( props ( x ) == 0x4 )

#define errhandle( x )			( props ( x ) & 0x7 )
#define optop( x )			( ( int ) ( errhandle ( x ) <= 2 ) )
#define seterrhandle( x, r )		props ( x ) =\
					  ( props ( x ) & ~0x7 ) | ( r )

/*
    PROPERTIES OF IDENT CONSTRUCTS
*/

#define setvar( x )			pset ( x, 0x01 )
#define clearvar( x )			pclr ( x, 0x01 )
#define isvar( x )			ptst ( x, 0x01 )
#define setid( x )			clearvar ( x )

#define setvis( x )			pset ( x, 0x02 )
#define clearvis( x )			pclr ( x, 0x02 )
#define isvis( x )			ptst ( x, 0x02 )

#define setenvoff( x )			pset ( x, 0x04 )
#define clearenvoff( x )		pclr ( x, 0x04 )
#define isenvoff( x )			ptst ( x, 0x04 )

#define setcaonly( x )			pset ( x, 0x08 )
#define clearcaonly( x )		pclr ( x, 0x08 )
#define iscaonly( x )			ptst ( x, 0x08 )

#define setusereg( x )			pset ( x, 0x10 )
#define clearusereg( x )		pclr ( x, 0x10 )
#define isusereg( x )			ptst ( x, 0x10 )

#define setparam( x )			pset ( x, 0x20 )
#define clearparam( x )			pclr ( x, 0x20 )
#define isparam( x )			ptst ( x, 0x20 )

#define setglob( x )			pset ( x, 0x40 )
#define clearglob( x )			pclr ( x, 0x40 )
#define isglob( x )			ptst ( x, 0x40 )

#define setcopy( x )			pset ( x, 0x80 )
#define clearcopy( x )			pclr ( x, 0x80 )
#define copying( x )			ptst ( x, 0x80 )

#define set_intnl_call( x )		pset ( x, 0x80 )
#define has_intnl_call( x )		ptst ( x, 0x80 )

				/* inlined in bitmacs.h, note also used in
				 scan_cond() */
#define setinlined(x)			pset(x, inlined)
#define isinlined(x)			ptst(x, inlined)
#define clearinlined(x)			pclr(x, inlined)

#define setoutpar(x) props(x) |= 0x8000
#define isoutpar(x) ((props(x) & 0x8000) != 0)
#define clearoutpar(x) props(x) &= ~0x8000


/*
    PROPERTIES OF MAKE_PROC CONSTRUCTS
*/

#define set_struct_res( x )		pset ( x, 0x01 )
#define has_struct_res( x )		ptst ( x, 0x01 )

#define set_loc_address( x )		pset ( x, 0x02 )
#define loc_address( x )		ptst ( x, 0x02 )

#define set_proc_has_setjmp( x )	pset ( x, 0x04 )
#define proc_has_setjmp( x )		ptst ( x, 0x04 )

#define set_proc_has_alloca( x )	pset ( x, 0x08 )
#define proc_has_alloca( x )		ptst ( x, 0x08 )

#define set_proc_has_lv( x )		pset ( x, 0x10 )
#define proc_has_lv( x )		ptst ( x, 0x10 )

#define isrecursive( x )		ptst ( x, 0x20 )
#define setrecursive( x )		pset ( x, 0x20 )

#define set_proc_uses_crt_env( x )	pset ( x, 0x40 )
#define proc_uses_crt_env( x )		ptst ( x, 0x40 )

#define set_proc_uses_external( x )	pset ( x, 0x80 )
#define proc_uses_external( x )		ptst ( x, 0x80 )


/*
    PROPERTIES OF SOLVE CONSTRUCT
*/

#define setcrtsolve( x )		props ( x ) = 0x01
#define set_copying_solve( x )		pset ( x, 0x01 )
#define clear_copying_solve( x )	pclr ( x, 0x01 )
#define is_copying_solve( x )		ptst ( x, 0x01 )


/*
    PROPERTIES OF MOVE_SOME CONSTRUCT
*/

#define setnooverlap( x )		pset ( x, 0x01 )
#define isnooverlap( x )		ptst ( x, 0x01 )


/*
    PROPERTIES OF CONTENTS CONSTRUCT
*/

#define set_propagate( x )		pset ( x, 0x01 )
#define clear_propagate( x )		pclr ( x, 0x01 )
#define to_propagate( x )		ptst ( x, 0x01 )


/*
    PROPERTIES OF LABST CONSTRUCT
*/

#define set_loaded_lv( x )		pset ( x, 0x10 )
#define is_loaded_lv( x )		ptst ( x, 0x10 )
#define setunroll(x) 			pset ( x, 0x04)
#define clearunroll(x)  		pclr ( x, 0x04)
#define isunroll(x) 			ptst ( x, 0x04)


/*
    PROPERTIES OF NAME CONSTRUCT
*/

#define setlastuse( x )			pset ( x, 0x01 )
#define islastuse( x )			ptst ( x, 0x01 )

#define setloadparam( x )		pset ( x, 0x02 )
#define isloadparam( x )		ptst ( x, 0x02 )

#define setreallyass( x )		/* not used */
#define isreallyass( x )		( 0 )

#ifdef NEWDIAGS
#define setisdiaginfo( x )		pset ( x, 0x08 )
#define isdiaginfo( x )			ptst ( x, 0x08 )

#define setdiscarded( x )		pset ( x, 0x010 )
#define isdiscarded( x )		ptst ( x, 0x010 )
#endif


/*
    PROPERTIES OF VAL CONSTRUCT
*/

#define setbigval( x )			pset ( x, 0x01 )
#define clearbigval( x )		pclr ( x, 0x01 )
#define isbigval( x )			ptst ( x, 0x01 )

#define setconstovf( x )		pset ( x, 0x02 )
#define constovf( x )			ptst ( x, 0x02 )


/* properties of REP construction */
				/* from 80x86 */

#define setunrolled(x)  		pset(x, 0x01)
#define isunrolled(x)			ptst(x,0x01)

/* properties of APPLY construction */
#define settoinline(x)  		pset(x, 0x01)
#define istoinline(x) 			ptst(x, 0x01)


/* properties of ASM construction */
#define asm_string(x)			ptst(x, 0x01)
#define asm_in(x)			ptst(x, 0x02)
#define asm_out(x)			ptst(x, 0x04)
#define asm_ptr(x)			ptst(x, 0x08)
#define asm_var(x)			ptst(x, 0x0c)	/* out | ptr */


/*
    USEFUL CONSTANTS
*/

#define align1				( ( unsigned long ) 1 )
#define align8				( ( unsigned long ) 8 )
#define align16				( ( unsigned long ) 16 )
#define align32				( ( unsigned long ) 32 )

#define Z				( ( long ) 0 )
#define size8				( ( long ) 8 )
#define size16				( ( long ) 16 )
#define size32				( ( long ) 32 )
#define size64				( ( long ) 64 )


/*
    ROUNDING
*/

#define rounder( n, a ) ( ( ( ( n ) + ( a ) - 1 ) / ( a ) ) * ( a ) )

/* New operations for spec 3.1 */
#define set_callee(id)	setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)
#define proc_has_vcallees(e) ((props(e) & 0x200)!=0)
#define postlude_has_call(e) (props(e) & 1)
#define set_postlude_has_call(e) (props(e) |= 1)
#define clear_postlude_has_call(e) (props(e) &= ~1)
#define call_has_vcallees(e) ((props(e) & 2) != 0)
#define proc_has_checkstack(e) ((props(e) & 0x800)!=0)
#define proc_has_vcallers(e) ((props(e) & 0x100) != 0)
#define proc_has_nolongj(e) ((props(e) & 0x1000) !=0)

#ifdef GENCOMPAT
#define proc_may_have_callees(e) ((props(e) & 0x8000) != 0)
#define set_proc_may_have_callees(e) (props(e) |= 0x8000)
#endif

#define frame_al_of_ptr(e) (e)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(e) (e)->sonf.ald->al.al_val.al_frame
#define include_vcallees(e) (e & 16)
#define cees(e) (e & 24)
#define l_or_cees(e)	(e&25)

#define call_is_untidy(e) ((props(e) & 0x4) != 0)

#define set_checkalloc(x) props(x) |= 1
#define checkalloc(x) (props(x) & 1)

/* property of current_env */
#define setcallee_offset(x) (props(x) |= 1)
#define callee_offset(x) (props(x) & 1)

#endif /* EXPMACS_INCLUDED */





