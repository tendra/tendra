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

#define ARITH_char			0
#define ARITH_schar			4
#define ARITH_sshort			5
#define ARITH_sint			6
#define ARITH_slong			7
#define ARITH_uchar			8
#define ARITH_ushort			9
#define ARITH_uint			10
#define ARITH_ulong			11
#define ARITH_sllong			23
#define ARITH_ullong			27
#define ARITH_float			12
#define ARITH_double			13
#define ARITH_ldouble			14

#define ARITH_error			1
#define ARITH_void			2
#define ARITH_bottom			3
#define ARITH_bool			17
#define ARITH_ptrdiff_t			18
#define ARITH_size_t			19
#define ARITH_wchar_t			16
#define ARITH_ellipsis			20
#define ARITH_none			256


/*
    RUN-TIME TYPE INFORMATION CODES

    These values give the codes for the various information used in run-time
    type information.  The facts that the base class access codes are in
    ascending order and that zero corresponds to public are used.
*/

#define RTTI_integer			0
#define RTTI_float			1
#define RTTI_void			2
#define RTTI_class			3
#define RTTI_union			4
#define RTTI_enum			5
#define RTTI_ptr			6
#define RTTI_ref			7
#define RTTI_ptr_mem			8
#define RTTI_array			9
#define RTTI_bitfield			10
#define RTTI_func			11
#define RTTI_c_func			12
#define RTTI_other			13

#define INFO_const			1
#define INFO_volatile			2

#define INFO_public			0
#define INFO_protected			1
#define INFO_private			2


/*
    EXTRA VIRTUAL FUNCTION TABLE ENTRIES

    This value gives the base from which virtual function entries are
    calculated.
*/

#define VIRTUAL_EXTRA			1


#endif
