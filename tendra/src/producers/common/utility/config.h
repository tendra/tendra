/*
    		 Crown Copyright (c) 1997, 1998
    
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

    The basic compiler configuration macros are defined in the standard
    header ossg.h.  The basic API headers are included from ossg_api.h.
    Other API headers are included by individual modules.  The basic
    compiler configuration (i.e. C or C++) header is also included.
*/

#include "ossg_api.h"
#include "ossg.h"
#include "language.h"


/*
    USEFUL MACROS

    Useful general utility macros (including discarded function returns)
    can be placed here.
*/

#define streq( A, B )	( strcmp ( ( A ), ( B ) ) == 0 )
#define array_size( A )	( ( int ) sizeof ( A ) / ( int ) sizeof ( *( A ) ) )
#define NIL( A )	( ( A * ) NULL )
#define NULL_gen_ptr	( ( gen_ptr ) NULL )

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
    GENERIC POINTER AND SIZE TYPES

    The type gen_ptr is used to represent the generic pointer.  The type
    gen_size is used to represent a generic size type (it is equivalent
    to size_t).
*/

#if FS_PTR_VOID
typedef void *gen_ptr ;
#else
typedef char *gen_ptr ;
#endif

typedef unsigned long gen_size ;


/*
    ASSERTION MACROS

    These macros are used in connection with the assertion routines.  If
    the macro DEBUG is defined then assertions will be included in the
    program along with other aids to program development.  The standard
    __FILE__ and __LINE__ macros are defined to dummy values for the
    benefit of compilers which do not define them.
*/

#ifdef DEBUG
#define ASSERTS		1
#define RUNTIME		1
#endif

#ifndef __FILE__
#define __FILE__	"unknown"
#endif

#ifndef __LINE__
#define __LINE__	1
#endif


#endif
