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


#include "implement.h"
#include "interface.h"


/*
    TYPE_INFO STRUCTURES FOR BUILT-IN TYPES

    The array __TCPPLUS_typeid gives the TYPE_INFO structures for the
    built-in types.  These correspond to the constants in interface.h.
*/

#define INFO( X, Y, Z )		{ ( Y ), ( X ), NULL, &__TCPPLUS_ti_vtbl }

TYPE_INFO __TCPPLUS_typeid [] = {
    INFO ( "char", RTTI_integer, ARITH_char ),
    INFO ( "<error>", RTTI_other, 2 ),
    INFO ( "void", RTTI_void, ARITH_void ),
    INFO ( "<bottom>", RTTI_void, ARITH_bottom ),
    INFO ( "signed char", RTTI_integer, ARITH_schar ),
    INFO ( "short", RTTI_integer, ARITH_sshort ),
    INFO ( "int", RTTI_integer, ARITH_sint ),
    INFO ( "long", RTTI_integer, ARITH_slong ),
    INFO ( "unsigned char", RTTI_integer, ARITH_uchar ),
    INFO ( "unsigned short", RTTI_integer, ARITH_ushort ),
    INFO ( "unsigned int", RTTI_integer, ARITH_uint ),
    INFO ( "unsigned long", RTTI_integer, ARITH_ulong ),
    INFO ( "float", RTTI_float, ARITH_float ),
    INFO ( "double", RTTI_float, ARITH_double ),
    INFO ( "long double", RTTI_float, ARITH_ldouble ),
    INFO ( "<error>", RTTI_other, 15 ),
    INFO ( "wchar_t", RTTI_integer, ARITH_wchar_t ),
    INFO ( "bool", RTTI_integer, ARITH_bool ),
    INFO ( "ptrdiff_t", RTTI_integer, ARITH_ptrdiff_t ),
    INFO ( "size_t", RTTI_integer, ARITH_size_t ),
    INFO ( "...", RTTI_void, ARITH_ellipsis ),
    INFO ( "<error>", RTTI_other, 21 ),
    INFO ( "<error>", RTTI_other, 22 ),
    INFO ( "long long", RTTI_integer, ARITH_sllong ),
    INFO ( "<error>", RTTI_other, 24 ),
    INFO ( "<error>", RTTI_other, 25 ),
    INFO ( "<error>", RTTI_other, 26 ),
    INFO ( "unsigned long long", RTTI_integer, ARITH_ullong ),
    INFO ( "<error>", RTTI_other, 28 ),
    INFO ( "<error>", RTTI_other, 29 ),
    INFO ( "<error>", RTTI_other, 30 ),
    INFO ( "<error>", RTTI_other, 31 )
} ;
