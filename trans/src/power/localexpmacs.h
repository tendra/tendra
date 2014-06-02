/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALEXPMACS_H
#define LOCALEXPMACS_H

#include "bitsmacs.h"

#include <construct/shapemacs.h>


/*
 * PROPERTIES OF IDENT
 */

#define setvarargparam( x )              pset( x, vararg_bit)
#define isvarargparam( x )               ptst( x ,vararg_bit)
#define clearvarargparam( x )            pclr( x ,vararg_bit)


/*
 * PROPERTIES OF STRING CONSTRUCT
 */

#define string_char_size( x )           props( x )


/*
 * PROPERTIES OF REP CONSTRUCT
 */

#define setinnermost( x )               pset( x , 0x10 )
#define isinnermost( x )                ptst( x , 0x10 )
#define clearinnermost( x )             pclr( x , 0x10 )


/*
 * PROPERTIES OF TEST CONSTRUCT
 */
#define set_use_count_register( x )     pset( x , 0x100 )
#define is_use_count_register( x )      ptst( x , 0x100 )
#define clear_use_count_register( x )   pclr( x , 0x100 )

/* PROPERTIES OF CALLER TAGS */
#define set_coded_caller( x )           pset( x , 0x01 )
#define is_coded_caller( x )            ptst( x , 0x01 )
#define clear_coded_caller( x )         pclr( x , 0x01 )

/* PROPERTIES FOR THINGS WHICH CAN HAVE RECORD BIT SET */
#define setrecordbit( x )               pset( x , 0x8000)
#define clearrecordbit( x )             pclr( x , 0x8000)
#define isrecordbit( x )                ptst( x , 0x8000)


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

#define IS_AGGREGATE(s)  (name(s)==nofhd||name(s)==cpdhd||name(s)==s64hd||name(s)==u64hd)

#endif

