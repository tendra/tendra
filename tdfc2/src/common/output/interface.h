/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef INTERFACE_INCLUDED
#define INTERFACE_INCLUDED


/*
    INTERFACE WITH STANDARD LIBRARY

    The interface with the standard library is given primarily by the
    tokens declared in tok.c, however other information is passed via
    the constants defined in this header, which is common to both the
    compiler and the library.
*/


/*
    ARITHMETIC TYPE CODES

    These values give the codes used to encode the arithmetic types.
*/

enum {
	ARITH_char      =   0,
	ARITH_schar     =   4,
	ARITH_sshort    =   5,
	ARITH_sint      =   6,
	ARITH_slong     =   7,
	ARITH_uchar     =   8,
	ARITH_ushort    =   9,
	ARITH_uint      =  10,
	ARITH_ulong     =  11,
	ARITH_sllong    =  23,
	ARITH_ullong    =  27,
	ARITH_float     =  12,
	ARITH_double    =  13,
	ARITH_ldouble   =  14,

	ARITH_error     =   1,
	ARITH_void      =   2,
	ARITH_bottom    =   3,
	ARITH_bool      =  17,
	ARITH_ptrdiff_t =  18,
	ARITH_size_t    =  19,
	ARITH_wchar_t   =  16,
	ARITH_ellipsis  =  20,
	ARITH_none      = 256
};


/*
    RUN-TIME TYPE INFORMATION CODES

    These values give the codes for the various information used in run-time
    type information.  The facts that the base class access codes are in
    ascending order and that zero corresponds to public are used.
*/

enum {
	RTTI_integer    =  0,
	RTTI_float      =  1,
	RTTI_void       =  2,
	RTTI_class      =  3,
	RTTI_union      =  4,
	RTTI_enum       =  5,
	RTTI_ptr        =  6,
	RTTI_ref        =  7,
	RTTI_ptr_mem    =  8,
	RTTI_array      =  9,
	RTTI_bitfield   = 10,
	RTTI_func       = 11,
	RTTI_c_func     = 12,
	RTTI_other      = 13
};

enum {
	INFO_const      =  1,
	INFO_volatile   =  2,

	INFO_public     =  0,
	INFO_protected  =  1,
	INFO_private    =  2
};


/*
    EXTRA VIRTUAL FUNCTION TABLE ENTRIES

    This value gives the base from which virtual function entries are
    calculated.
*/

enum {
	VIRTUAL_EXTRA  =  1
};


#endif
