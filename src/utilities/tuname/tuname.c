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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef FS_UTSNAME
#define FS_UTSNAME	1
#endif

#if FS_UTSNAME
#include <sys/types.h>
#include <sys/utsname.h>
#endif

#include "ossg.h"


/*
    CONVERT A STRING TO LOWER CASE

    This routine converts the string s to lower case, returning the result.
*/

static char *to_lower_case
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    int c ;
    char *t = s ;
    while ( c = ( int ) *t, c != 0 ) {
	if ( isascii ( c ) && isupper ( c ) ) {
	    *t = ( char ) tolower ( c ) ;
	}
	t++ ;
    }
    return ( s ) ;
}


/*
    PRINT A MACRO DEFINITION

    This routine prints a macro definition consisting of the prefix p
    followed by s, suitably transformed by replacing each non-alphanumeric
    character by an underscore.
*/

static void define_macro
    PROTO_N ( ( p, s ) )
    PROTO_T ( CONST char *p X CONST char *s )
{
    int c ;
    IGNORE printf ( "#define %s", p ) ;
    while ( c = ( int ) *( s++ ), c != 0 ) {
	if ( !isascii ( c ) || !isalnum ( c ) ) c = '_' ;
	IGNORE fputc ( c, stdout ) ;
    }
    IGNORE printf ( " 1\n" ) ;
    return ;
}


/*
    FIND A MACHINE TYPE

    These routines map the machine type as returned by uname (mapped to
    lower case), m, to the standard machine type used in the build.
*/

static CONST char *find_aix_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( m [8] == '7' && m [9] == '6' ) return ( "power" ) ;
    if ( m [8] == '7' && m [9] == '7' ) return ( "power" ) ;
    if ( m [8] == '4' && m [9] == '6' ) return ( "ppc601" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_hpux_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( strncmp ( m, "9000/", 5 ) == 0 ) {
	if ( m [5] == '7' || m [5] == '8' ) return ( "hppa" ) ;
	if ( m [5] == '3' || m [5] == '4' ) return ( "680x0" ) ;
    }
    return ( "unknown" ) ;
}

static CONST char *find_irix_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( strcmp ( m, "ip22" ) == 0 ) return ( "mips" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_linux_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( m [0] == 'i' && strstr ( m, "86" ) ) return ( "80x86" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_osf1_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( strcmp ( m, "alpha" ) == 0 ) return ( "alpha" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_sco_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( m [0] == 'i' && strstr ( m, "86" ) ) return ( "80x86" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_sunos_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( strcmp ( m, "i86pc" ) == 0 ) return ( "80x86" ) ;
    if ( strncmp ( m, "sun3", 4 ) == 0 ) return ( "680x0" ) ;
    if ( strncmp ( m, "sun4", 4 ) == 0 ) return ( "sparc" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_ultrix_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( strcmp ( m, "risc" ) == 0 ) return ( "mips" ) ;
    if ( strcmp ( m, "vax" ) == 0 ) return ( "vax" ) ;
    return ( "unknown" ) ;
}

static CONST char *find_unix_sv_machine
    PROTO_N ( ( m ) )
    PROTO_T ( CONST char *m )
{
    if ( m [0] == 'i' && m [2] == '8' && m [3] == '6' ) return ( "80x86" ) ;
    return ( "unknown" ) ;
}


/*
    FIND SCO RELEASE NUMBER

    On SCO the release number is not returned by uname.  Instead there is
    a function __scoinfo which returns the necessary information.  This
    routine finds the release number.
*/

static CONST char *find_sco_release
    PROTO_N ( ( buff ) )
    PROTO_T ( char *buff )
{
#if defined ( _M_XENIX ) && defined ( _TWO_USER )
    struct scoutsname us ;
    extern int __scoinfo PROTO_S ( ( struct scoutsname *, int ) ) ;
    if ( __scoinfo ( &us, ( int ) sizeof ( us ) ) != -1 ) {
	char *v = strchr ( us.release, 'v' ) ;
	if ( v ) {
	    /* The release is the part following the 'v' */
	    IGNORE strcpy ( buff, v + 1 ) ;
	    return ( buff ) ;
	}
    }
#endif
    UNUSED ( buff ) ;
    return ( "unknown" ) ;
}


/*
    FIND LINUX EXECUTABLE FORMAT

    This routine finds whether the given version of linux supports the ELF
    or the a.out executable format.  It does this by examining the magic
    number at the start of an executable file, nm.
*/

static CONST char *find_linux_format
    PROTO_N ( ( nm ) )
    PROTO_T ( CONST char *nm )
{
    FILE *f = fopen ( nm, "rb" ) ;
    if ( f != NULL ) {
	char m [4] ;
	if ( fread ( m, sizeof ( char ), sizeof ( m ), f ) == 4 ) {
	    if ( m [0] == 0x7f ) {
		if ( m [1] == 'E' && m [2] == 'L' && m [3] == 'F' ) {
		    IGNORE fclose ( f ) ;
		    return ( "elf" ) ;
		}
	    }
	}
	IGNORE fclose ( f ) ;
    }
    return ( "aout" ) ;
}


/*
    MAIN ROUTINE

    This program is a rationalised form of uname which tries to give the
    operating system type, the operating system version and the processor
    type in a consistent form.  It may need extending to cover new
    operating systems.
*/

int main
    PROTO_N ( ( argc, argv ) )
    PROTO_T ( int argc X char **argv )
{
    char buff [50] ;
    CONST char *sysname = "unknown" ;
    CONST char *nodename = "anonymous" ;
    CONST char *release = "unknown" ;
    CONST char *version = "unknown" ;
    CONST char *machine = "unknown" ;
    CONST char *execform = "default" ;

    /* Call uname to find system information */
#if FS_UTSNAME
    struct utsname un ;
    if ( uname ( &un ) != -1 ) {
	sysname = to_lower_case ( un.sysname ) ;
	nodename = to_lower_case ( un.nodename ) ;
	release = un.release ;
	version = un.version ;
	machine = to_lower_case ( un.machine ) ;
    }
#endif

#ifdef DEBUG
    /* Print debugging information */
    IGNORE fprintf ( stderr, "sysname = \"%s\"\n", sysname ) ;
    IGNORE fprintf ( stderr, "nodename = \"%s\"\n", nodename ) ;
    IGNORE fprintf ( stderr, "release = \"%s\"\n", release ) ;
    IGNORE fprintf ( stderr, "version = \"%s\"\n", version ) ;
    IGNORE fprintf ( stderr, "machine = \"%s\"\n", machine ) ;
#endif

    /* Examine system information */
    if ( strcmp ( sysname, "aix" ) == 0 ) {
	machine = find_aix_machine ( machine ) ;
	IGNORE sprintf ( buff, "%s.%s", version, release ) ;
	release = buff ;

    } else if ( strcmp ( sysname, "freebsd" ) == 0 ) {
	machine = find_linux_machine ( machine ) ;

    } else if ( strcmp ( sysname, "hp-ux" ) == 0 ) {
	sysname = "hpux" ;
	machine = find_hpux_machine ( machine ) ;

    } else if ( strcmp ( sysname, "irix" ) == 0 ) {
	machine = find_irix_machine ( machine ) ;

    } else if ( strcmp ( sysname, "linux" ) == 0 ) {
	machine = find_linux_machine ( machine ) ;
	execform = find_linux_format ( argv [0] ) ;
	if ( strcmp ( execform, "aout" ) == 0 ) {
	    /* Mark a.out versions */
	    IGNORE sprintf ( buff, "%sA", release ) ;
	    release = buff ;
	}

    } else if ( strcmp ( sysname, "msdos" ) == 0 ) {
	machine = find_sco_machine ( machine ) ;

    } else if ( strcmp ( sysname, "osf1" ) == 0 ) {
	machine = find_osf1_machine ( machine ) ;

    } else if ( strcmp ( sysname, "sco" ) == 0 ) {
	/* This doesn't actually happen - see below */
	release = find_sco_release ( buff ) ;
	machine = find_sco_machine ( machine ) ;

    } else if ( strcmp ( sysname, "sunos" ) == 0 ) {
	if ( release [0] == '5' ) {
	    /* SunOS 5.x is really Solaris 2.x */
	    sysname = "solaris" ;
	    IGNORE sprintf ( buff, "2%s", release + 1 ) ;
	    release = buff ;
	}
	machine = find_sunos_machine ( machine ) ;

    } else if ( strcmp ( sysname, "ultrix" ) == 0 ) {
	machine = find_ultrix_machine ( machine ) ;

    } else if ( strcmp ( sysname, "unix_sv" ) == 0 ) {
	IGNORE sprintf ( buff, "svr%s", release ) ;
	sysname = buff ;
	release = version ;
	machine = find_unix_sv_machine ( machine ) ;

    } else if ( strcmp ( sysname, nodename ) == 0 ) {
	/* This is a bug on SCO */
	sysname = "sco" ;
	release = find_sco_release ( buff ) ;
	machine = find_sco_machine ( machine ) ;

    } else if ( strncmp ( sysname, "cygwin32", 8 ) == 0 ) {
	sysname = "cygwin32" ;
	machine = find_linux_machine ( machine ) ;

    } else if ( strncmp ( sysname, "minix", 5 ) == 0 ) {
	machine = find_linux_machine ( machine ) ;
	execform = "aout" ;

    } else {
	/* Unknown operating system */
	sysname = "unknown" ;
	machine = "unknown" ;
	release = "unknown" ;
    }

    /* Print host type */
    if ( argc > 2 ) {
	IGNORE fprintf ( stderr, "tcc_host: Too many arguments.\n" ) ;
	argc = 2 ;
    }
    if ( argc == 2 ) {
	char *arg = argv [1] ;
	if ( strcmp ( arg, "-a" ) == 0 ) {
	    IGNORE printf ( "%s %s %s\n", sysname, release, machine ) ;
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-d" ) == 0 ) {
	    IGNORE printf ( "%s/%s/%s\n", sysname, release, machine ) ;
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-e" ) == 0 ) {
	    IGNORE printf ( "%s\n", execform ) ;
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-h" ) == 0 ) {
	    IGNORE printf ( "%s\n", nodename ) ;
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-m" ) == 0 ) {
	    IGNORE printf ( "%s\n", machine ) ;
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-r" ) == 0 ) {
#ifdef __minix
	    IGNORE printf ( "%s.%s\n", release, version ) ;
#else
	    IGNORE printf ( "%s\n", release ) ;
#endif
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-s" ) == 0 ) {
	    IGNORE printf ( "%s\n", sysname ) ;
	    return ( 0 ) ;
	}
	if ( strcmp ( arg, "-D" ) == 0 ) {
	    define_macro ( "FS_OS_", sysname ) ;
	    define_macro ( "FS_OS_VERS_", release ) ;
	    define_macro ( "FS_CPU_", machine ) ;
	    define_macro ( "FS_EXEC_", execform ) ;
	    return ( 0 ) ;
	}
	IGNORE fprintf ( stderr, "tcc_host: Unknown argument '%s'.\n", arg ) ;
    }
    IGNORE printf ( "%s %s %s\n", sysname, release, machine ) ;
    return ( 0 ) ;
}
