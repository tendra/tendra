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


#ifndef ERROR_INCLUDED
#define ERROR_INCLUDED


/*
    ERROR SEVERITY LEVELS

    These macros give the various error types recognised by the error
    routines.  Their values are in order of increasing severity.
*/

#define ERROR_WHATEVER		0
#define ERROR_NONE		1
#define ERROR_WARNING		2
#define ERROR_OPTION		3
#define ERROR_SERIOUS		4
#define ERROR_INTERNAL		5
#define ERROR_FATAL		6


/*
    ERROR ROUTINE DECLARATIONS

    The routines in this module are concerned with error reporting and
    related areas.
*/

extern ERROR make_error PROTO_W ( ( int, ... ) ) ;
extern void error PROTO_W ( ( int, CONST char *, ... ) ) ;
extern void set_progname PROTO_S ( ( CONST char *, CONST char * ) ) ;
extern string report_version PROTO_S ( ( int ) ) ;
extern void error_option PROTO_S ( ( string ) ) ;
extern void print_error PROTO_S ( ( LOCATION *, ERROR ) ) ;
extern EXP install_error PROTO_S ( ( LOCATION *, ERROR ) ) ;
extern void commentary PROTO_S ( ( IDENTIFIER ) ) ;
extern void destroy_error PROTO_S ( ( ERROR, int ) ) ;
extern ERROR concat_error PROTO_S ( ( ERROR, ERROR ) ) ;
extern ERROR concat_warning PROTO_S ( ( ERROR, ERROR ) ) ;
extern void add_error PROTO_S ( ( ERROR *, ERROR ) ) ;
extern void term_error PROTO_S ( ( int ) ) ;
extern ERROR set_prefix PROTO_S ( ( ERROR ) ) ;
extern void restore_prefix PROTO_S ( ( ERROR ) ) ;

#define report( A, B )		print_error ( &( A ), ( B ) )
#define fail( A )		print_error ( NIL ( LOCATION ), ( A ) )
#define KILL_err		NIL ( ERROR )


/*
    ERROR REPORTING VARIABLES

    These variables are used in the configuration of the error reporting
    routines.
*/

extern CONST char *progname ;
extern CONST char *progvers ;
extern int exit_status ;
extern unsigned long number_errors ;
extern unsigned long number_warnings ;
extern unsigned long max_errors ;
extern int error_severity [] ;
extern int default_severity [] ;
extern int verbose ;
extern int error_threshold ;
extern int no_error_args ;
extern LOCATION crt_loc ;
extern LOCATION builtin_loc ;
extern FILE *error_file ;


/*
    ASSERTION ROUTINE DECLARATIONS

    These macros are used to define assertions for aiding program
    development.  If the macro ASSERTS is defined then code for checking
    these assertions is output, otherwise the macros have no effect.
    Note that ASSERTS is automatically defined if DEBUG is (see config.h).
    FAIL_COMPILER is intended as an alternative to #error blows up some
    compilers even if it is not on the main compilation path.
*/

#ifdef ASSERTS
extern int is_true PROTO_S ( ( int ) ) ;
extern void assertion PROTO_S ( ( CONST char *, CONST char *, int ) ) ;
#if FS_STDC_HASH
#define ASSERT( A )	if ( is_true ( !( A ) ) )\
			    assertion ( #A, __FILE__, __LINE__ )
#define FAIL( A )	assertion ( #A, __FILE__, __LINE__ )
#else
#define ASSERT( A )	if ( is_true ( !( A ) ) )\
			    assertion ( "A", __FILE__, __LINE__ )
#define FAIL( A )	assertion ( "A", __FILE__, __LINE__ )
#endif
#else
#if FS_LINT
#define ASSERT( A )	/* empty */
#define FAIL( A )	/* empty */
#else
#define ASSERT( A )	( IGNORE 0 )
#define FAIL( A )	( IGNORE 0 )
#endif
#endif

#define FAIL_COMPILER	ERROR [!]


#endif
