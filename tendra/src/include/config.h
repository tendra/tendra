/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


/*
 *    BASIC API SPECIFICATION
 *
 *    The API for this program is ANSI plus a few extensions from POSIX
 *    and XPG3.  The ANSI headers are included here, with the FS_* macros
 *    being used to control inclusion of the additional features.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS		0
#define EXIT_FAILURE		1
#endif

#ifndef SEEK_SET
#define SEEK_SET		0
#define SEEK_CUR		1
#define SEEK_END		2
#endif

#ifndef FS_POSIX
#define FS_POSIX		1
#endif

#ifndef FS_XPG3
#define FS_XPG3			FS_POSIX
#endif

#ifndef FS_DIRENT
#define FS_DIRENT		FS_POSIX
#endif

#ifndef FS_FORK
#define FS_FORK			FS_POSIX
#endif

#ifndef FS_GETCWD
#define FS_GETCWD		FS_POSIX
#endif

#ifndef FS_STAT
#define FS_STAT			FS_POSIX
#endif

#ifndef FS_SYS_TYPES
#define FS_SYS_TYPES		FS_POSIX
#endif

#ifndef FS_TEMPNAM
#define FS_TEMPNAM		FS_XPG3
#endif

#ifndef FS_WAIT
#define FS_WAIT			FS_POSIX
#endif

#ifndef S_IRWXG
#define	S_IRWXG			0
#endif

#ifndef S_IRWXO
#define	S_IRWXO			0
#endif

#ifdef __WIN32__
#define	FS_PATH_SEP		'\\'
#else
#define	FS_PATH_SEP		'/'
#endif

/*
 *    CODING STANDARD MACROS
 *
 *    The program is written to conform to the local OSSG coding standard.
 *    This header defines the standard macros used in the program.
 */


#include "ossg.h"


/*
 *    BASIC TYPES
 *
 *    These types are so ubiquitous that this is the only suitable place
 *    for them.
 */

#define	FALSE	(0)
#define	TRUE	(1)


typedef unsigned char boolean;
typedef boolean BoolT, *BoolP;

typedef unsigned char ByteT, *ByteP;

typedef const char *ccp;

typedef char *CStringP;		/* may be removed */
typedef void *pointer;		/* to be removed */
typedef pointer gen_ptr;	/* to be removed */
typedef pointer GenericP;	/* to be removed */

/*
 * This is the type returned by comparison functions.  The values represent
 * the fact that the first argument is less than, equal to, or greater than
 * the second argument respectively.
 */
typedef enum {
    CMP_LT,
    CMP_EQ,
    CMP_GT
} CmpT, *CmpP;

/*
 * This is worth to get rid of
 */
#define	NIL(type) ((type)(0))


#ifdef __TenDRA__
#pragma TenDRA keyword SET for set
#else
#define	SET(name)
#endif

#ifdef __GNUC__
typedef __volatile__ void NoReturnT;
#else
# ifdef __TenDRA__
#  pragma TenDRA type NoReturnT for bottom
# else
#  define NoReturnT void
# endif /* defined (__TenDRA__) */
#endif /* defined (__GNUC__) */



/*
 *    UTILITY MACROS
 *
 *    These macros are just a matter of programming style.
 */

#define streq(X, Y)		(strcmp ((X), (Y)) == 0)
#define strneq(X, Y, Z)	(strncmp ((X), (Y), (size_t) (Z)) == 0)

/*
 * These defines should go away in future
 */
#define null			NULL
#define MAX_LINE 1024
#define BYTESIZE		8

#endif
