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
    INCLUDE BASIC CONFIGURATION FILES
*/

#include "ossg_api.h"
#include "ossg.h"


/*
    USEFUL MACROS

    Useful general utility macros (including discarded function returns)
    can be placed here.
*/

#define streq( A, B )	( strcmp ( ( A ), ( B ) ) == 0 )
#define array_size( A )	( ( int ) sizeof ( A ) / ( int ) sizeof ( *( A ) ) )

#define fclose_v	IGNORE fclose
#define fflush_v	IGNORE fflush
#define fprintf_v	IGNORE fprintf
#define fputc_v		IGNORE fputc
#define fputs_v		IGNORE fputs
#define printf_v	IGNORE printf
#define putchar_v	IGNORE putchar
#define putc_v		IGNORE putc
#define puts_v		IGNORE puts
#define sprintf_v	IGNORE sprintf
#define vfprintf_v	IGNORE vfprintf
#define memcpy_v	IGNORE memcpy
#define strcpy_v	IGNORE strcpy


/*
    ASSERTION MACROS

    These macros are used in connection with the assertion routines.
*/

#ifdef DEBUG
#define ASSERTS
#endif

#ifndef __FILE__
#define __FILE__	"unknown"
#endif

#ifndef __LINE__
#define __LINE__	0
#endif


#endif
