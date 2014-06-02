/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef OSSG_INCLUDED
#define OSSG_INCLUDED


/*
 * OSSG STANDARD COMPILER HEADER, VERSION 1.1
 *
 * This headers defines feature switch macros for various compiler
 * features.  These can be 1, if the feature is allowed, or 0, otherwise.
 * These switches are used to define the PROTO macros described in the
 * OSSG C coding standard.  Standard versions of the TenDRA keywords
 * are also provided.
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


#endif
