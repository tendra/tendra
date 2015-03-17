/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED


#include <syntax/language.h>


/*
    USEFUL MACROS

    Useful general utility macros (including discarded function returns)
    can be placed here.
*/

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

typedef void *gen_ptr ;
typedef unsigned long gen_size ;


#endif
