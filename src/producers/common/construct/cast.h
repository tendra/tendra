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


#ifndef CAST_INCLUDED
#define CAST_INCLUDED


/*
    TYPE CAST DECLARATIONS

    The routines in this module are concerned with casting types.
*/

extern EXP make_cast_exp PROTO_S ( ( TYPE, EXP, int ) ) ;
extern EXP make_static_cast_exp PROTO_S ( ( TYPE, EXP, int ) ) ;
extern EXP make_reinterp_cast_exp PROTO_S ( ( TYPE, EXP, int ) ) ;
extern EXP make_const_cast_exp PROTO_S ( ( TYPE, EXP, int ) ) ;
extern EXP make_new_cast_exp PROTO_S ( ( int, TYPE, EXP, int ) ) ;
extern EXP make_func_cast_exp PROTO_S ( ( TYPE, LIST ( EXP ) ) ) ;
extern EXP make_base_cast PROTO_S ( ( TYPE, EXP, OFFSET ) ) ;

extern EXP cast_exp PROTO_S ( ( TYPE, EXP, ERROR *, unsigned ) ) ;
extern EXP cast_int_int PROTO_S ( ( TYPE, EXP, ERROR *, unsigned, int ) ) ;
extern EXP cast_int_float PROTO_S ( ( TYPE, EXP, ERROR *, unsigned ) ) ;
extern EXP cast_float_float PROTO_S ( ( TYPE, EXP, ERROR *, unsigned ) ) ;
extern EXP cast_ptr_ptr PROTO_S ( ( TYPE, EXP, ERROR *, unsigned, int, int ) ) ;
extern EXP cast_ptr_mem_ptr_mem PROTO_S ( ( TYPE, EXP, ERROR *, unsigned, int, int ) ) ;
extern EXP cast_class_class PROTO_S ( ( TYPE, EXP, ERROR *, unsigned, int ) ) ;
extern EXP cast_templ_type PROTO_S ( ( TYPE, EXP, unsigned ) ) ;
extern void cast_away_const PROTO_S ( ( unsigned, ERROR *, unsigned ) ) ;
extern EXP cast_token PROTO_S ( ( TYPE, EXP, ERROR *, ERROR, unsigned ) ) ;
extern void allow_conversion PROTO_S ( ( IDENTIFIER ) ) ;


/*
    CAST IDENTIFIERS

    These values are used to identify the various classes of cast expressions
    in cast_exp and related routines.  They form a bitpattern for the static,
    reinterpret and const casts.
*/

#define CAST_IMPLICIT			( ( unsigned ) 0x00 )
#define CAST_STATIC			( ( unsigned ) 0x01 )
#define CAST_REINTERP			( ( unsigned ) 0x02 )
#define CAST_CONST			( ( unsigned ) 0x04 )
#define CAST_BAD			( ( unsigned ) 0x08 )
#define CAST_EXPLICIT			( ( unsigned ) 0x0f )
#define CAST_DYNAMIC			( ( unsigned ) 0x10 )
#define CAST_STANDARD			( ( unsigned ) 0x20 )


#endif
