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


#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with error reporting, memory allocation
    and system calls.
*/

extern void error PROTO_W ( ( int, char *, ... ) ) ;
extern pointer xalloc PROTO_S ( ( int ) ) ;
extern pointer xrealloc PROTO_S ( ( pointer, int ) ) ;
extern char *string_copy PROTO_S ( ( char * ) ) ;
extern char *string_concat PROTO_S ( ( char *, char * ) ) ;
extern char *string_printf PROTO_W ( ( char *, ... ) ) ;
extern void create_dir PROTO_S ( ( char * ) ) ;
extern void check_name PROTO_S ( ( char * ) ) ;
extern time_t date_stamp PROTO_S ( ( char * ) ) ;


/*
    INPUT BUFFER

    This buffer is used to store input in various contexts.
*/

extern char *buffer ;
#define buffsize		5000


/*
    ERROR VARIABLES

    These variables are concerned with error reporting.
*/

extern int exit_status ;
extern int no_errors ;
extern int warnings ;
extern char *progname ;
extern char *progvers ;
extern time_t progdate ;
extern char *filename ;
extern int line_no ;


/*
    ERROR TYPES

    These values give the severity levels for the error reporting
    routine, error.
*/

#define ERR_FATAL		0
#define ERR_INTERNAL		1
#define ERR_SERIOUS		2
#define ERR_WARNING		3
#define ERR_INFO		4


/*
    UTILITY MACROS

    These macros give convenient shorthands for various constructs.
*/

#define alloc_size( T, N )\
	( ( int ) ( N ) * ( int ) sizeof ( T ) )

#define alloc_nof( T, N )\
	( T * ) xalloc ( alloc_size ( T, N ) )

#define realloc_nof( P, T, N )\
	( T * ) xrealloc ( ( pointer ) ( P ), alloc_size ( T, N ) )

#define array_size( A )\
	( ( int ) sizeof ( A ) / ( int ) sizeof ( A [0] ) )


/*
    GENERAL ALLOCATION ROUTINE

    This routine allocates a variable V of type T, allocating N at a time.
*/

#define alloc_variable( V, T, N )\
    {\
	static int no_free = 0 ;\
	static T *free_list = null ;\
	if ( no_free == 0 ) {\
	    no_free = N ;\
	    free_list = alloc_nof ( T, N ) ;\
	}\
	V = free_list + ( --no_free ) ;\
    }


#endif
