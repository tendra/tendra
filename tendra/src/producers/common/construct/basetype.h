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


#ifndef BASETYPE_INCLUDED
#define BASETYPE_INCLUDED


/*
    BASE TYPE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of the basic C and C++ types.
*/

extern void init_types PROTO_S ( ( void ) ) ;
extern TYPE make_base_type PROTO_S ( ( BASE_TYPE ) ) ;
extern BASE_TYPE join_pre_types PROTO_S ( ( BASE_TYPE, BASE_TYPE ) ) ;
extern TYPE complete_pre_type PROTO_S ( ( BASE_TYPE, TYPE, CV_SPEC, int ) ) ;
extern TYPE empty_complete_pre_type PROTO_S ( ( BASE_TYPE, TYPE, CV_SPEC, int ) ) ;
extern TYPE inject_pre_type PROTO_S ( ( TYPE, TYPE, int ) ) ;
extern TYPE copy_typedef PROTO_S ( ( IDENTIFIER, TYPE, CV_SPEC ) ) ;
extern TYPE qualify_type PROTO_S ( ( TYPE, CV_SPEC, int ) ) ;
extern TYPE lvalue_type PROTO_S ( ( TYPE ) ) ;
extern TYPE rvalue_type PROTO_S ( ( TYPE ) ) ;
extern TYPE check_bitfield_type PROTO_S ( ( CV_SPEC, TYPE, BASE_TYPE, NAT, int ) ) ;
extern BASE_TYPE get_bitfield_rep PROTO_S ( ( TYPE, BASE_TYPE ) ) ;
extern TYPE find_bitfield_type PROTO_S ( ( TYPE ) ) ;
extern TYPE make_bitfield_type PROTO_S ( ( TYPE, BASE_TYPE, EXP, int ) ) ;
extern int check_int_type PROTO_S ( ( TYPE, BASE_TYPE ) ) ;
extern ERROR report_inferred_type PROTO_S ( ( TYPE, int ) ) ;
extern TYPE clean_inferred_type PROTO_S ( ( TYPE ) ) ;
extern int is_type_inferred PROTO_S ( ( TYPE ) ) ;
extern NAT check_array_dim PROTO_S ( ( NAT ) ) ;
extern NAT make_array_dim PROTO_S ( ( EXP ) ) ;
extern void accept_argument PROTO_S ( ( TYPE, TYPE ) ) ;
extern void accept_ellipsis PROTO_S ( ( TYPE ) ) ;
extern TYPE eq_argument PROTO_S ( ( TYPE, TYPE, int ) ) ;
extern TYPE eq_ellipsis PROTO_S ( ( TYPE ) ) ;
extern void set_compatible_type PROTO_S ( ( TYPE, TYPE, unsigned ) ) ;


/*
    BASE TYPES

    These variables give the built-in C and C++ types.
*/

extern TYPE type_builtin [ ORDER_ntype ] ;
extern TYPE ptr_type_builtin [ ORDER_ntype ] ;
extern TYPE type_func_void ;
extern TYPE type_temp_func ;
extern TYPE type_ellipsis ;
extern TYPE type_error ;

#define type_inferred		( type_builtin [ ntype_none ] )
#define type_char		( type_builtin [ ntype_char ] )
#define type_schar		( type_builtin [ ntype_schar ] )
#define type_uchar		( type_builtin [ ntype_uchar ] )
#define type_sshort		( type_builtin [ ntype_sshort ] )
#define type_ushort		( type_builtin [ ntype_ushort ] )
#define type_sint		( type_builtin [ ntype_sint ] )
#define type_uint		( type_builtin [ ntype_uint ] )
#define type_slong		( type_builtin [ ntype_slong ] )
#define type_ulong		( type_builtin [ ntype_ulong ] )
#define type_sllong		( type_builtin [ ntype_sllong ] )
#define type_ullong		( type_builtin [ ntype_ullong ] )
#define type_float		( type_builtin [ ntype_float ] )
#define type_double		( type_builtin [ ntype_double ] )
#define type_ldouble		( type_builtin [ ntype_ldouble ] )
#define type_void		( type_builtin [ ntype_void ] )
#define type_bottom		( type_builtin [ ntype_bottom ] )
#define type_bool		( type_builtin [ ntype_bool ] )
#define type_ptrdiff_t		( type_builtin [ ntype_ptrdiff_t ] )
#define type_size_t		( type_builtin [ ntype_size_t ] )
#define type_wchar_t		( type_builtin [ ntype_wchar_t ] )
#define type_any		( type_builtin [ ntype_ellipsis ] )

#define type_temp_star		( ptr_type_builtin [ ntype_none ] )
#define type_char_star		( ptr_type_builtin [ ntype_char ] )
#define type_void_star		( ptr_type_builtin [ ntype_void ] )


/*
    RETURN VALUES FOR INFERRED TYPES

    These values are returned by is_type_inferred to describe the various
    categories of inferred types.
*/

#define INFERRED_NOT			0
#define INFERRED_SPEC			1
#define INFERRED_QUAL			2
#define INFERRED_EMPTY			3


#endif
