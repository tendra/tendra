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


#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


/*
    BASIC API SPECIFICATION

    The API for this program is ANSI plus a few extensions from POSIX
    and XPG3.  The ANSI headers are included here, with the FS_* macros
    being used to control inclusion of the additional features.
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


/*
    CODING STANDARD MACROS

    The program is written to conform to the local OSSG coding standard.
    This header defines the standard macros used in the program.
*/


#include "ossg.h"


/*
    BASIC TYPES

    These types are so ubiquitous that this is the only suitable place
    for them.
*/

typedef int boolean ;
#if FS_PTR_VOID
typedef void *pointer ;
#else
typedef char *pointer ;
#endif


/*
    UTILITY MACROS

    These macros are just a matter of programming style.
*/

#define null			NULL
#define streq( X, Y )		( strcmp ( ( X ), ( Y ) ) == 0 )
#define strneq( X, Y, Z )	( strncmp ( ( X ), ( Y ), ( size_t ) ( Z ) ) == 0 )


#endif
