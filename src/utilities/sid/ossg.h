/*
    		 Crown Copyright (c) 1997, 1998
    
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


#ifndef OSSG_INCLUDED
#define OSSG_INCLUDED


/*
    OSSG STANDARD COMPILER HEADER, VERSION 1.1

    This headers defines feature switch macros for various compiler
    features.  These can be 1, if the feature is allowed, or 0, otherwise.
    These switches are used to define the PROTO macros described in the
    OSSG C coding standard.  Standard versions of the TenDRA keywords
    are also provided.
*/


/* FS_CPLUSPLUS indicates a C++ compiler */

#ifndef FS_CPLUSPLUS
#ifdef __cplusplus
#define FS_CPLUSPLUS		1
#define FS_STDC			1
#else
#define FS_CPLUSPLUS		0
#endif
#endif


/* FS_STDC indicates an ISO C compliant compiler */

#ifndef FS_STDC
#ifdef __STDC__
#define FS_STDC			1
#else
#define FS_STDC			0
#endif
#endif


/* FS_TENDRA indicates the TenDRA C compiler */

#ifndef FS_TENDRA
#ifdef __TenDRA__
#define FS_TENDRA		1
#else
#define FS_TENDRA		0
#endif
#endif


/* FS_GNUC indicates the GNU C compiler */

#ifndef FS_GNUC
#ifdef __GNUC__
#define FS_GNUC			1
#else
#define FS_GNUC			0
#endif
#endif


/* FS_LINT indicates lint */

#ifndef FS_LINT
#if defined ( lint ) || defined ( __lint )
#define FS_LINT			1
#else
#define FS_LINT			0
#endif
#endif


/* FS_PROTOTYPES indicates whether the compiler has prototypes */

#ifndef FS_PROTOTYPES
#define FS_PROTOTYPES		FS_STDC
#endif


/* FS_WEAK_PROTOTYPES indicates whether the compiler has weak prototypes */

#ifndef FS_WEAK_PROTOTYPES
#define FS_WEAK_PROTOTYPES	( FS_TENDRA && !FS_CPLUSPLUS )
#endif


/* FS_STDARG indicates whether the compiler has <stdarg.h> */

#ifndef FS_STDARG
#define FS_STDARG		FS_STDC
#endif


/* Definitions of PROTO macros for weak prototypes */

#if FS_WEAK_PROTOTYPES
#ifndef PROTO_S
#pragma TenDRA keyword KW_WEAK_PROTOTYPE for weak
#define PROTO_S( types )	KW_WEAK_PROTOTYPE types
#define PROTO_N( names )	names
#define PROTO_T( params )	params ;
#define PROTO_Z()		()
#define PROTO_X			;
#endif
#endif


/* Definitions of PROTO macros for prototypes */

#if FS_PROTOTYPES
#ifndef PROTO_S
#define PROTO_S( types )	types
#define PROTO_N( names )
#define PROTO_T( params )	( params )
#define PROTO_Z()		( void )
#define PROTO_X			,
#endif
#endif


/* Definitions of PROTO macros for non-prototypes */

#ifndef PROTO_S
#define PROTO_S( types )	()
#define PROTO_N( names )	names
#define PROTO_T( params )	params ;
#define PROTO_Z()		()
#define PROTO_X			;
#endif


/* Definitions of PROTO_V macros */

#if FS_STDARG
#define PROTO_V( params )	params
#define PROTO_W( types )	types
#else
#define PROTO_V( parms )	( va_alist ) va_dcl
#define PROTO_W( types )	()
#endif


/* Definition of prototype separator macro */

#ifdef X
#undef X
#endif
#define X			PROTO_X


/* Definitions of TenDRA keywords */

#if FS_TENDRA
#pragma TenDRA keyword SET for set
#pragma TenDRA keyword UNUSED for discard variable
#pragma TenDRA keyword IGNORE for discard value
#pragma TenDRA keyword EXHAUSTIVE for exhaustive
#pragma TenDRA keyword REACHED for set reachable
#pragma TenDRA keyword UNREACHED for set unreachable
#define FALL_THROUGH
#endif


/* Definitions of TenDRA keywords for lint */

#if FS_LINT
#define SET( name )
#define UNUSED( name )		( name ) = ( name )
#define IGNORE			( void )
#define EXHAUSTIVE
#define REACHED
#define UNREACHED
#define FALL_THROUGH
#endif


/* Dummy definitions for TenDRA keywords */

#if !FS_TENDRA && !FS_LINT
#define SET( name )
#define UNUSED( name )
#define IGNORE			( void )
#define EXHAUSTIVE
#define REACHED
#define UNREACHED
#define FALL_THROUGH
#endif


/* FS_CONST indicates whether const is supported */

#ifndef FS_CONST
#define FS_CONST		FS_STDC
#endif


/* FS_VOLATILE indicates whether volatile is supported */

#ifndef FS_VOLATILE
#define FS_VOLATILE		FS_STDC
#endif


/* CONST is used in place of const */

#if FS_CONST
#define CONST			const
#else
#define CONST
#endif


/* VOLATILE is used in place of volatile */

#if FS_VOLATILE
#define VOLATILE		volatile
#else
#define VOLATILE
#endif


/* FS_STDC_HASH indicates whether # and ## are supported */

#ifndef FS_STDC_HASH
#define FS_STDC_HASH		FS_STDC
#endif


/* FS_STDC_IDENTIFIERS indicates __FILE__ etc. are defined */

#ifndef FS_STDC_IDENTIFIERS
#define FS_STDC_IDENTIFIERS	FS_STDC
#endif


/* FS_TRIGRAPH indicates whether trigraphs are supported */

#ifndef FS_TRIGRAPH
#define FS_TRIGRAPH		FS_STDC
#endif


/* FS_WIDE_STRING indicates whether wide strings are supported */

#ifndef FS_WIDE_STRING
#define FS_WIDE_STRING		FS_STDC
#endif


/* FS_NUMBER_SUFFIX indicates whether the L, U, F suffixes are supported */

#ifndef FS_NUMBER_SUFFIX
#define FS_NUMBER_SUFFIX	FS_STDC
#endif


/* FS_CONCAT_STRING indicates whether string concatenation is supported */

#ifndef FS_CONCAT_STRING
#define FS_CONCAT_STRING	FS_STDC
#endif


/* FS_PTR_VOID indicates whether void * is supported */

#ifndef FS_PTR_VOID
#define FS_PTR_VOID		FS_STDC
#endif


/* FS_SIGNED indicates whether signed is supported */

#ifndef FS_SIGNED
#define FS_SIGNED		FS_STDC
#endif


/* FS_LONG_DOUBLE indicates whether long double is supported */

#ifndef FS_LONG_DOUBLE
#define FS_LONG_DOUBLE		FS_STDC
#endif


/* FS_ENUMERATION indicates whether enumeration types are supported */

#ifndef FS_ENUMERATION
#define FS_ENUMERATION		FS_STDC
#endif


/* FS_TYPEDEF_VOID indicates whether typedef void is supported */

#ifndef FS_TYPEDEF_VOID
#define FS_TYPEDEF_VOID		FS_STDC
#endif


/* FS_UNION_INIT indicates whether initialisation of unions is supported */

#ifndef FS_UNION_INIT
#define FS_UNION_INIT		FS_STDC
#endif


/* FS_AUTO_STRUCT_INIT indicates whether initialisation of automatic
   compound variables is allowed */

#ifndef FS_AUTO_STRUCT_INIT
#define FS_AUTO_STRUCT_INIT	FS_STDC
#endif


#endif
