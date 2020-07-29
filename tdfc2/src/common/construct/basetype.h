/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef BASETYPE_INCLUDED
#define BASETYPE_INCLUDED


/*
    BASE TYPE DECLARATIONS

    The routines in this module are concerned with the construction and
    manipulation of the basic C and C++ types.
*/

extern void init_types(void);
extern TYPE make_base_type(BASE_TYPE);
extern BASE_TYPE join_pre_types(BASE_TYPE, BASE_TYPE);
extern TYPE complete_pre_type(BASE_TYPE, TYPE, CV_SPEC, int);
extern TYPE empty_complete_pre_type(BASE_TYPE, TYPE, CV_SPEC, int);
extern TYPE inject_pre_type(TYPE, TYPE, int);
extern TYPE copy_typedef(IDENTIFIER, TYPE, CV_SPEC);
extern TYPE qualify_type(TYPE, CV_SPEC, int);
extern TYPE lvalue_type(TYPE);
extern TYPE rvalue_type(TYPE);
extern TYPE check_bitfield_type(CV_SPEC, TYPE, BASE_TYPE, NAT, int);
extern BASE_TYPE get_bitfield_rep(TYPE, BASE_TYPE);
extern TYPE find_bitfield_type(TYPE);
extern TYPE make_bitfield_type(TYPE, BASE_TYPE, EXP, int);
extern int check_int_type(TYPE, BASE_TYPE);
extern ERROR report_inferred_type(TYPE, int);
extern TYPE clean_inferred_type(TYPE);
extern int is_type_inferred(TYPE);
extern NAT check_array_dim(NAT);
extern NAT make_array_dim(EXP);
extern void accept_argument(TYPE, TYPE);
extern void accept_ellipsis(TYPE);
extern TYPE eq_argument(TYPE, TYPE, int);
extern TYPE eq_ellipsis(TYPE);
extern void set_compatible_type(TYPE, TYPE, unsigned);


/*
    BASE TYPES

    These variables give the built-in C and C++ types.
*/

extern TYPE type_builtin[ORDER_ntype];
extern TYPE ptr_type_builtin[ORDER_ntype];
extern TYPE type_func_void;
extern TYPE type_temp_func;
extern TYPE type_ellipsis;
extern TYPE type_error;

#define type_inferred		(type_builtin[ntype_none])
#define type_char		(type_builtin[ntype_char])
#define type_schar		(type_builtin[ntype_schar])
#define type_uchar		(type_builtin[ntype_uchar])
#define type_sshort		(type_builtin[ntype_sshort])
#define type_ushort		(type_builtin[ntype_ushort])
#define type_sint		(type_builtin[ntype_sint])
#define type_uint		(type_builtin[ntype_uint])
#define type_slong		(type_builtin[ntype_slong])
#define type_ulong		(type_builtin[ntype_ulong])
#define type_sllong		(type_builtin[ntype_sllong])
#define type_ullong		(type_builtin[ntype_ullong])
#define type_float		(type_builtin[ntype_float])
#define type_double		(type_builtin[ntype_double])
#define type_ldouble		(type_builtin[ntype_ldouble])
#define type_void		(type_builtin[ntype_void])
#define type_bottom		(type_builtin[ntype_bottom])
#define type_bool		(type_builtin[ntype_bool])
#define type_ptrdiff_t		(type_builtin[ntype_ptrdiff_t])
#define type_size_t		(type_builtin[ntype_size_t])
#define type_wchar_t		(type_builtin[ntype_wchar_t])
#define type_any		(type_builtin[ntype_ellipsis])

#define type_temp_star		(ptr_type_builtin[ntype_none])
#define type_char_star		(ptr_type_builtin[ntype_char])
#define type_void_star		(ptr_type_builtin[ntype_void])


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
