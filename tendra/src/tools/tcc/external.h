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


#ifndef EXTERNAL_INCLUDED
#define EXTERNAL_INCLUDED


/*
    EXTERNAL INTERFACE SPECIFICATION

    This header describes the non-ANSI component of the program API.
    The various components are controlled by the FS_* macros defined
    in config.h.
*/

#include <sys/types.h>
#if FS_DIRENT
#include <dirent.h>
#endif
#include <errno.h>
#if FS_STAT
#include <sys/stat.h>
#endif
#include <unistd.h>
#if FS_WAIT
#include <sys/wait.h>
#endif

#if !FS_SYS_TYPES
typedef int pid_t ;
typedef unsigned short mode_t ;
#endif

#ifndef errno
extern int errno ;
#endif

#ifndef environ
extern char **environ ;
#endif

#ifndef S_ISDIR
#define S_ISDIR( X )			( ( X ) & S_IFDIR )
#endif

#ifndef S_IRWXU
#ifdef S_IREAD
#define S_IRWXU				S_IREAD
#define S_IRWXG				S_IWRITE
#define S_IRWXO				S_IEXEC
#else
#define S_IRWXU				0700
#define S_IRWXG				0070
#define S_IRWXO				0007
#endif
#endif

#if FS_TEMPNAM
#define temp_name( X, Y )		( char * ) tempnam ( ( X ), ( Y ) )
#else
extern char *like_tempnam PROTO_S ( ( char *, char * ) ) ;
#define temp_name( X, Y )		like_tempnam ( ( X ), ( Y ) )
#endif

#if FS_GETCWD
#define get_cwd( X, Y )			getcwd ( ( X ), ( Y ) )
#else
#define get_cwd( X, Y )			NULL
#endif

#if FS_WAIT
typedef int wait_type ;
#define process_wait( X )		wait ( ( X ) )
#define process_return( X, Y )		( ( X ) = ( Y ) )
#define process_exited( X )		WIFEXITED ( ( X ) )
#define process_signaled( X )		WIFSIGNALED ( ( X ) )
#define process_exit_value( X )		WEXITSTATUS ( ( X ) )
#define process_signal_value( X )	WTERMSIG ( ( X ) )
#endif


#endif
