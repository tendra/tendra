/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONFIG_H
#define CONFIG_H


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

	(c)  Expressions : EOF, NULL,
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

#ifndef SEEK_SET
#define SEEK_SET		0
#endif


/*
    MACRO TO DEAL WITH PROCEDURE PROTOTYPES

    Procedure declarations are given by the macro procedure with is
    defined to either give the full prototype or the tradition declaration
    depending on the value of __STDC__.
*/


/*
    USEFUL MACROS

    These macros are used in several places.  They are defined here for
    convenience.
*/

#define null			NULL
#define hash_size		31


/*
    MAGIC NUMBERS

    These macros give the magic numbers for TDF capsules and libraries.
*/

#define MAGIC_NUMBER		"TDFC"
#define MAGIC_LINK_NUMBER	"TDFL"


#endif /* CONFIG_H */
