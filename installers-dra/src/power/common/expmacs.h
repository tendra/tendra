/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef expmacs_key
#define expmacs_key 1

#include "bitsmacs.h"
#include <construct/shapemacs.h>

#define nilexp NULL

/* main components of exp */

#define son(x) ((x)->sonf.e)
#define bro(x) ((x)->brof.e)
#define last(x) (x)->lastf
#define name(x) (x)->namef
#define sh(x) (x)->shf
#define pt(x) ((x)->ptf.e)
#define props(x) (x)->propsf
#define no(x) ((x)->numf.l)
#define parked(x) ((x)->park)

/* alternative components of exp */

#define brog(x) ((x)->brof.glob)
#define nostr(x) ((x)->numf.str)
#define ptno(x) ((x) ->ptf.l)
#define sonno(x) ((x) ->sonf.l)
#define fno(x) ((x) -> numf.f)
#define dno(x) ((x) -> numf.d)
#define uno(x) ((x) -> numf.ui)

/* ntests */
#define test_number(x) (props(x) & 0xf)
#define settest_number(x, t) props(x) = ((props(x) & ~0xf)|( t ))

/* rounding */
#define round_number(x) ((x)->propsf >> 3)
#define setround_number(x,r) (x)->propsf=(((x)->propsf & 0x7) | (r << 3))

/* error handling macros */
#define errhandle(x) ((x)->propsf & 0x7)
#define optop(x) ((int)errhandle(x) <= 2) 
#define seterrhandle(x,e) (x)->propsf= ((x)->propsf & 0xf8) | (e)

/* properties of constructions with EXCEPTIONS */
#define setjmp_dest(r,d) {(r)->ptf.e = (d); ++no(son(d));}
#define isov(x) (errhandle(x) == 0x4)

/* setting macros for components of exp */

#define setbro(x,b) (x)->brof.e = (b)
#define setsh(x,b) (x)->shf = (b)
#define setson(x,b) (x)->sonf.e = (b)
#define setpt(x,b) (x)->ptf.e = (b)
#define setlast(x) (x)->lastf = 1
#define clearlast(x) (x)->lastf = 0
#define setname(x,n) (x)->namef = (n)
#define setfather(f,s) (s)->brof.e = (f); (s)->lastf = 1

/* components of shapes */
#define shape_size(x)                   ((x)->numf.l)
#define shape_align(x)                  ((unsigned long)((x)->brof.ald->al.al_val.al))
#define align_of(x)                     ((x)->brof.ald)
#define al1(x)                          ((unsigned long)((x)->sonf.ald->al.al_val.al))
#define al1_of(x)                       ((x)->sonf.ald)
#define al2(x)                          ((unsigned long)((x)->ptf.ald->al.al_val.al))
#define al2_of(x)                       ((x)->ptf.ald)
#define is_signed( x )                  last( x )

/* 
 * MACROS FOR MANIPULATING PROPERTIES
 */
#define pset( x, m )	                props ( x ) = ( prop ) ( props ( x ) | ( m ) )
#define pclr( x, m )	                props ( x ) = ( prop ) ( props ( x ) & ~( m ) )
#define ptst( x, m )	                ( ( props ( x ) & ( m ) ) != 0)

/* 
 * PROPERTIES OF IDENT 
 */

#define setvar( x )                     pset( x , 0x01 )
#define clearvar( x )                   pclr( x , 0x01 )
#define isvar( x )                      ptst( x , 0x01 )
#define setid( x )                      clearvar( x )

#define setvis( x )                     pset( x , 0x02 )
#define clearvis( x )                   pclr( x , 0x02 )
#define isvis( x )                      ptst( x , 0x02 )

#define setenvoff( x )                  pset( x , 0x04 )
#define clearenvoff( x )                pclr( x , 0x04 )
#define isenvoff( x )                   ptst( x , 0x04 )

#define setcaonly( x )                  pset( x , 0x08 )
#define clearcaonly( x )                pclr( x , 0x08 )
#define iscaonly( x )                   ptst( x , 0x08 )

#define setusereg( x )                  pset( x , 0x10 )
#define clearusereg( x )                pclr( x , 0x10 )
#define isusereg( x )                   ptst( x , 0x10 )

#define setparam( x )                   pset( x , 0x20 )
#define clearparam( x )                 pclr( x , 0x20 )
#define isparam( x )                    ptst( x , 0x20 )

#define setglob( x )                    pset( x , 0x40 )
#define clearglob( x )                  pclr( x , 0x40 )
#define isglob( x )                     ptst( x , 0x40 )

#define setcopy( x )                    pset( x , 0x80 )
#define clearcopy( x )                  pclr( x , 0x80 )
#define copying( x )                    ptst( x , 0x80 )

#define setvarargparam( x )              pset( x, vararg_bit)
#define isvarargparam( x )               ptst( x ,vararg_bit)
#define clearvarargparam( x )            pclr( x ,vararg_bit)


#define setinlined( x )                 pset( x , inlined ) /* inlined defined in bitsmacs.h */
#define clearinlined( x )               pclr( x , inlined )
#define isinlined( x )                  ptst( x , inlined )

#define setoutpar( x )                  pset( x , 0x8000 )
#define isoutpar( x )                   ptst( x , 0x8000 )
#define clearoutpar( x )                pclr( x , 0x8000 )
/* 
 * PROPERTIES OF MAKE_PROC CONSTRUCTION
 */

#define set_struct_res( x )             pset( x , 0x01 )
#define has_struct_res( x )             ptst( x , 0x01 )

#define set_loc_address( x )            pset( x , 0x02 )
#define loc_address( x )                ptst( x , 0x02 )

#define set_proc_has_setjmp( x )        pset( x , 0x04 )
#define proc_has_setjmp( x )            ptst( x , 0x04 )

#define set_proc_has_alloca( x )        pset( x , 0x08 )
#define proc_has_alloca( x )            ptst( x , 0x08 )

#define set_proc_has_lv( x )            pset( x , 0x10 )
#define proc_has_lv( x )                ptst( x , 0x10 )


#define setrecursive( x )               pset( x , 0x20 )
#define isrecursive( x )                ptst( x , 0x20 )

#define set_proc_uses_crt_env( x )      pset( x , 0x40 )
#define proc_uses_crt_env( x )          ptst( x , 0x40 )

#define set_proc_uses_external( x )     pset( x , 0x80 )
#define proc_uses_external( x )         ptst( x , 0x80 )

/*
 * PROPERTIES OF SOLVE CONSTRUCT
 */

#define setcrtsolve( x )                props( x ) = 0x01
#define set_copying_solve( x )          pset( x , 0x01 )
#define clear_copying_solve( x )        pclr( x , 0x01 )
#define is_copying_solve( x )           ptst( x , 0x01 )

/*
 * PROPERTIES OF MOVE SOME CONSTRUCT 
 */

#define setnooverlap( x )               pset( x , 0x01 )
#define isnooverlap( x )                ptst( x , 0x01 )

/*
 * PROPERTIES OF CONT CONSTRUCT
 */

#define set_propagate( x )              pset( x , 0x01)
#define clear_propagate( x )		pclr( x , 0x01 )
#define to_propagate( x )		ptst( x , 0x01 )

/* 
 * PROPERTIES OF LABST CONSTRUCTION
 */

#define set_loaded_lv( x )		pset( x , 0x10 )
#define is_loaded_lv( x )		ptst( x , 0x10 )
#define setunroll( x ) 			pset( x , 0x04 )
#define clearunroll( x )  		pclr( x , 0x04 )
#define isunroll( x ) 			ptst( x , 0x04 )


/*
 * PROPERTIES OF NAME CONSTRUCT
 */

#define setlastuse( x )                 pset( x , 0x01 )
#define islastuse( x )                  ptst( x , 0x01 )

#define setloadparam( x )               pset( x , 0x02 )
#define isloadparam( x )                ptst( x , 0x02 )

#define setreallyass( x )               pset( x , 0x04 )
#define isreallyass( x )                ptst( x , 0x04 )

/* 
 * PROPERTIES OF STRING CONSTRUCT
 */

#define string_char_size( x )           props( x )

/*
 * PROPERTIES OF VAL CONSTRUCT
 */

#define setbigval( x )                  pset( x , 0x01 )
#define clearbigval( x )                pclr( x , 0x01 )
#define isbigval( x )                   ptst( x , 0x01 )

#define setconstovf( x )		pset ( x, 0x02 )
#define constovf( x )			ptst ( x, 0x02 )

/*
 * PROPERTIES OF REP CONSTRUCT
 */

#define setunrolled( x )                pset( x , 0x01 )
#define isunrolled( x )                 ptst( x , 0x01 )
#define setinnermost( x )               pset( x , 0x10 )
#define isinnermost( x )                ptst( x , 0x10 )
#define clearinnermost( x )             pclr( x , 0x10 )

/*
 * PROPERTIES OF TEST CONSTRUCT
 */
#define set_use_count_register( x )     pset( x , 0x100 )
#define is_use_count_register( x )      ptst( x , 0x100 )
#define clear_use_count_register( x )   pclr( x , 0x100 )
/*
 * PROPERTIES OF APPLY CONSTRUCT
 */

#define settoinline( x )                pset( x , 0x01 )
#define istoinline( x )                 ptst( x , 0x01 )
/* 
 * PROPERTIES OF ALLOCA CONSTRUCT
 */
#define set_checkalloc(x) props(x) |= 1;
#define checkalloc(x) (props(x) & 1)


/* 
 * PROPERTIES OF JUMP RECORD
 */
#define fstack_pos_of( x )              props( x )
/* PROPERTIES OF CALLER TAGS */
#define set_coded_caller( x )           pset( x , 0x01 )
#define is_coded_caller( x )            ptst( x , 0x01 )
#define clear_coded_caller( x )         pclr( x , 0x01 )


/* PROPERTIES FOR THINGS WHICH CAN HAVE RECORD BIT SET */
#define setrecordbit( x )               pset( x , 0x8000)
#define clearrecordbit( x )             pclr( x , 0x8000)
#define isrecordbit( x )                ptst( x , 0x8000)

/* 
 * ROUNDING FOR ALIGNMENT
 */

#define rounder( n , a )                ( ( ( n ) + ( a ) - 1 ) / ( a ) ) * ( a )

/*
 * USEFUL CONSTANTS
 */

#define align32                         ( ( unsigned long ) 32 )
#define align16                         ( ( unsigned long ) 16 )
#define align8                          ( ( unsigned long ) 8 )
#define align1                          ( ( unsigned long ) 1 )

#define size64                          ( ( long ) 64 )
#define size32                          ( ( long ) 32 )
#define size16                          ( ( long ) 16 )
#define size8                           ( ( long ) 8 )
#define Z                               ( long ) 0



/*
 * A few new macros for powertrans
 */
#define is_single_precision( x )        ( name( x ) == shrealhd )
#define is_double_precision( x )        ( name( x ) != shrealhd )


#define IS_A_PROC( x )         ( name(x)==proc_tag || name(x)==general_proc_tag)
/* These are used in TDF 3.1 for general_env_offset */
#define frame_al_of_ptr(x) (x)->sonf.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->sonf.ald->al.al_val.al_frame
#define includes_vcallees(x) (((x) & 16) != 0)
#define l_or_cees(x) (((x) &25) !=0)
#define i_reckon_its_a_general_proc(x) ( ((x)&24 )!=0)
/* extra tags needed */
#define locptr_tag 249
#define TEST_LE 1
#define TEST_LT 2
#define TEST_GE 3
#define TEST_GT 4
#define TEST_NE 5
#define TEST_EQ 6

/* extra_expmacs.h */
#define set_callee(id)  setname(son(id), formal_callee_tag)
#define set_make_procprops(e, p) props(e) |= ((p)<<8)
#define proc_has_vcallees(e) ((props(e) & 0x200)!=0)
#define postlude_has_call(e) (props(e) & 1)
#define call_has_vcallees(e) ((props(e) & 2) != 0)
#define proc_has_checkstack(e) ((props(e) & 0x800)!=0)
#define proc_has_vcallers(e) ((props(e) & 0x100) != 0)
#define proc_has_nolongj(e) ((props(e) & 0x1000) !=0)

#define call_is_untidy(e) ((props(e) & 4) != 0)
#define IS_AGGREGATE(s)  (name(s)==nofhd||name(s)==cpdhd||name(s)==s64hd||name(s)==u64hd)

#endif

