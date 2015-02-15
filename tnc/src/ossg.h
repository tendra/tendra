/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
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


#endif /* OSSG_H */
