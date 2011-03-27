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


#ifndef OSSG_H
#define OSSG_H


/*
    OSSG STANDARD COMPILER HEADER, VERSION 1.1

    This headers defines feature switch macros for various compiler
    features.  These can be 1, if the feature is allowed, or 0, otherwise.
    These switches are used to define the PROTO macros described in the
    OSSG C coding standard.  Standard versions of the TenDRA keywords
    are also provided.
*/


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


/* Definitions of TenDRA keywords */

#if FS_TENDRA
#pragma TenDRA keyword SET for set
#pragma TenDRA keyword UNUSED for discard variable
#pragma TenDRA keyword IGNORE for discard value
#pragma TenDRA keyword REACHED for set reachable
#pragma TenDRA keyword UNREACHED for set unreachable
#define FALL_THROUGH
#endif


/* Definitions of TenDRA keywords for lint */

#if FS_LINT
#define SET( name )
#define UNUSED( name )		( name ) = ( name )
#define IGNORE			( void )
#define REACHED
#define UNREACHED
#define FALL_THROUGH
#endif


/* Dummy definitions for TenDRA keywords */

#if !FS_TENDRA && !FS_LINT
#define SET( name )
#define UNUSED( name )
#define IGNORE			( void )
#define REACHED
#define UNREACHED
#define FALL_THROUGH
#endif


#endif /* OSSG_H */
