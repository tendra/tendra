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
    INCLUDE THE BASIC SYSTEM HEADERS

    These headers are required in several places.  It is easiest to
    include them here.  These are the only system headers included.
    The program is ANSI compliant.  It uses the following objects :

	(a)  Types : FILE, size_t, va_list.

	(b)  Procedures or macros : exit, fclose, fgetc, fopen,
	     fprintf, fputc, fputs, fseek, ftell, getc, isprint,
	     malloc, printf, putchar, realloc, sprintf, strcmp,
	     strlen, strncmp, strncpy, va_end, va_start, vfprintf.

	(c)  Expressions : EOF, EXIT_FAILURE, EXIT_SUCCESS, NULL,
	     SEEK_SET, stderr, stdout.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
    HACKS

    These hacks are designed to aid compilation on non-compliant systems.
    SEEK_SET is not defined on, for example, SUN-OS.
*/

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS		0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE		1
#endif

#ifndef SEEK_SET
#define SEEK_SET		0
#endif


/*
    MACRO TO DEAL WITH PROCEDURE PROTOTYPES

    Procedure declarations are given by the macro procedure with is
    defined to either give the full prototype or the tradition declaration
    depending on the value of __STDC__.
*/

#include "ossg.h"


/*
    USEFUL MACROS

    These macros are used in several places.  They are defined here for
    convenience.
*/

#define null			NULL
#define BYTESIZE		8
#define hash_size		31
#define streq( X, Y )		( strcmp ( ( X ), ( Y ) ) == 0 )


/*
    MAGIC NUMBERS

    These macros give the magic numbers for TDF capsules and libraries.
*/

#define MAGIC_NUMBER		"TDFC"
#define MAGIC_LINK_NUMBER	"TDFL"


#endif
