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


/*
    BUILT IN TYPES

    These are the fundamental types which are built into the system.
*/

#ifdef BUILTIN
BUILTIN ( type_char, "char", no_version, TYPE_INT ) ;
BUILTIN ( type_schar, "signed char", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_uchar, "unsigned char", no_version, TYPE_UNSIGNED ) ;
BUILTIN ( type_short, "short", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_sshort, "signed short", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_ushort, "unsigned short", no_version, TYPE_UNSIGNED ) ;
BUILTIN ( type_int, "int", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_sint, "signed int", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_uint, "unsigned int", no_version, TYPE_UNSIGNED ) ;
BUILTIN ( type_long, "long", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_slong, "signed long", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_ulong, "unsigned long", no_version, TYPE_UNSIGNED ) ;
BUILTIN ( type_llong, "long long", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_sllong, "signed long long", no_version, TYPE_SIGNED ) ;
BUILTIN ( type_ullong, "unsigned long long", no_version, TYPE_UNSIGNED ) ;
BUILTIN ( type_float, "float", no_version, TYPE_FLOAT ) ;
BUILTIN ( type_double, "double", no_version, TYPE_FLOAT ) ;
BUILTIN ( type_ldouble, "long double", no_version, TYPE_FLOAT ) ;
BUILTIN ( type_void, "void", no_version, TYPE_VOID ) ;
BUILTIN ( type_bottom, "void", 1, TYPE_VOID ) ;
BUILTIN ( type_printf, "const char *", 1, TYPE_GENERIC ) ;
BUILTIN ( type_scanf, "const char *", 2, TYPE_GENERIC ) ;
BUILTIN ( type_ellipsis, "...", no_version, TYPE_GENERIC ) ;
BUILTIN ( type_none, "void", 2, TYPE_VOID ) ;
#undef BUILTIN
#endif
