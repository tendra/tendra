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
    routines.
*/

#define ERROR_NONE		0x00
#define ERROR_WARNING		0x01
#define ERROR_SERIOUS		0x02
#define ERROR_FATAL		0x03


/*
    DECLARATIONS FOR ERROR ROUTINES
*/

extern void error PROTO_W ( ( int, CONST char *, ... ) ) ;
extern void error_posn PROTO_W ( ( int, CONST char *, int, CONST char *, ... ) ) ;
extern void set_progname PROTO_S ( ( CONST char *, CONST char * ) ) ;
extern void report_version PROTO_S ( ( void ) ) ;

extern CONST char *progname ;
extern CONST char *progvers ;
extern int exit_status ;
extern int maximum_errors ;
extern int crt_line_no ;
extern CONST char *crt_file_name ;


/*
    DECLARATIONS FOR ASSERTION ROUTINES
*/

#ifdef ASSERTS
extern void assertion PROTO_S ( ( CONST char *, CONST char *, int ) ) ;
#if FS_STDC_HASH
#define ASSERT( A )	if ( !( A ) ) assertion ( #A, __FILE__, __LINE__ )
#define FAIL( A )	assertion ( #A, __FILE__, __LINE__ )
#else
#define ASSERT( A )	if ( !( A ) ) assertion ( "A", __FILE__, __LINE__ )
#define FAIL( A )	assertion ( "A", __FILE__, __LINE__ )
#endif
#else
#define ASSERT( A )	( ( void ) 0 )
#define FAIL( A )	( ( void ) 0 )
#endif


#endif
