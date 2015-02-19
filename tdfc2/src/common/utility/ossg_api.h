/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OSSG_API_INCLUDED
#define OSSG_API_INCLUDED


/*
    STANDARD API HEADER

    This header contains the basic API headers used by the program
    software.  The flag FS_POSIX is set to indicate that POSIX features
    should be enabled (see system.h).  Some likely values for objects
    which are not defined by all systems are provided.  Also any
    unwarranted namespace pollution is removed.
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FS_EXTENDED_CHAR
#define FS_EXTENDED_CHAR	0
#endif

#ifndef FS_POSIX
#define FS_POSIX		1
#endif

#ifndef FS_UTSNAME
#define FS_UTSNAME		FS_POSIX
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS		0
#define EXIT_FAILURE		1
#endif

#ifndef SEEK_SET
#define SEEK_SET		0
#define SEEK_CUR		1
#define SEEK_END		2
#endif

#ifndef BUFSIZ
#define BUFSIZ			1024
#endif

#ifdef index
#undef index
#endif

#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif


#endif
