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


#ifndef INTTYPE_INCLUDED
#define INTTYPE_INCLUDED


/*
    TYPE REPRESENTING FUNDAMENTAL TYPE INFORMATION

    This type is used to represent the fundamental information about a
    built-in type.
*/

typedef struct {
    BASE_TYPE rep ;
    unsigned min_bits ;
    unsigned max_bits ;
    BASE_TYPE sign ;
    int key ;
    TYPE set ;
} BASE_INFO ;


/*
    INTEGRAL TYPE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of the integral C and C++ types.
*/

extern void init_itypes PROTO_S ( ( int ) ) ;
extern void term_itypes PROTO_S ( ( void ) ) ;
extern void set_char_sign PROTO_S ( ( BASE_TYPE ) ) ;
extern void set_promote_type PROTO_S ( ( TYPE, TYPE, BUILTIN_TYPE ) ) ;
extern void compute_promote_type PROTO_S ( ( IDENTIFIER ) ) ;
extern void set_builtin_type PROTO_S ( ( BASE_TYPE, TYPE ) ) ;
extern void set_long_long_type PROTO_S ( ( int ) ) ;
extern void set_exact_types PROTO_S ( ( void ) ) ;
extern unsigned find_type_size PROTO_S ( ( TYPE, unsigned *, BASE_TYPE * ) ) ;
extern BUILTIN_TYPE is_builtin_type PROTO_S ( ( TYPE, int ) ) ;
extern TYPE make_itype PROTO_S ( ( INT_TYPE, INT_TYPE ) ) ;
extern TYPE make_ftype PROTO_S ( ( FLOAT_TYPE, FLOAT_TYPE ) ) ;
extern TYPE arith_itype PROTO_S ( ( TYPE, TYPE, EXP, EXP ) ) ;
extern TYPE arith_ftype PROTO_S ( ( TYPE, TYPE ) ) ;
extern TYPE promote_itype PROTO_S ( ( INT_TYPE, INT_TYPE ) ) ;
extern TYPE promote_ftype PROTO_S ( ( FLOAT_TYPE, FLOAT_TYPE ) ) ;
extern TYPE apply_itype_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ) ) ) ;
extern TYPE apply_ftype_token PROTO_S ( ( IDENTIFIER, LIST ( TOKEN ) ) ) ;
extern INT_TYPE expand_itype PROTO_S ( ( INT_TYPE ) ) ;
extern BASE_TYPE key_type PROTO_S ( ( int ) ) ;

extern LIST ( TYPE ) all_llong_types ;
extern LIST ( TYPE ) all_prom_types ;
extern LIST ( TYPE ) all_int_types ;
extern BASE_INFO basetype_info [] ;

extern int min_builtin_cast ;
extern int safe_builtin_cast ;
extern int max_builtin_cast ;

extern unsigned char builtin_casts [ ORDER_ntype ] [ ORDER_ntype ] ;
#define builtin_cast( A, B )	( ( int ) builtin_casts [A] [B] )


#endif
