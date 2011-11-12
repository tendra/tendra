/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef USTRING_INCLUDED
#define USTRING_INCLUDED


/*
    UNSIGNED STRING HANDLING

    These macros are used to convert the normal string operations to the
    corresponding unsigned string operations.  The portability assumption,
    that char * and string are interchangeable in these operations is
    encapsulated in the tokens U2S and S2U.
*/

#if c_class_SPECIFICATION
#pragma token PROC ( EXP : string : ) EXP : char * : U2S #
#pragma token PROC ( EXP : const char * : ) EXP : string : S2U #
#pragma interface U2S S2U
#endif

#if c_class_IMPLEMENTATION
#define U2S( S )		( ( char * ) ( gen_ptr ) ( S ) )
#define S2U( S )		( ( string ) ( gen_ptr ) ( S ) )
#endif

#define ustrlit( S )		( S2U ( S ) )
#define strlit( S )		( U2S ( S ) )

#define ustrlen( S )		( strlen ( U2S ( S ) ) )
#define ustrcpy( S, T )		( S2U ( strcpy ( U2S ( S ), U2S ( T ) ) ) )
#define ustrcpy_v( S, T )	( strcpy_v ( U2S ( S ), U2S ( T ) ) )
#define ustrcmp( S, T )		( strcmp ( U2S ( S ), U2S ( T ) ) )
#define ustreq( S, T )		( strcmp ( U2S ( S ), U2S ( T ) ) == 0 )
#define ustrseq( S, T )		( strcmp ( U2S ( S ), ( T ) ) == 0 )
#define ustrchr( S, C )		( S2U ( strchr ( U2S ( S ), ( C ) ) ) )
#define ustrrchr( S, C )	( S2U ( strrchr ( U2S ( S ), ( C ) ) ) )


#endif
