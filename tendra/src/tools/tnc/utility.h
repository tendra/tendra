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
    ERROR REPORTING ROUTINES
*/

extern boolean is_fatal ;
extern int exit_status ;
extern boolean text_input, text_output ;
extern void fatal_error PROTO_W ( ( char *, ... ) ) ;
extern void input_error PROTO_W ( ( char *, ... ) ) ;
extern void warning PROTO_W ( ( char *, ... ) ) ;


/*
    MEMORY ALLOCATION ROUTINES
*/

extern pointer xalloc PROTO_S ( ( int ) ) ;
extern pointer xrealloc PROTO_S ( ( pointer, int ) ) ;
extern char *string_copy PROTO_S ( ( char *, int ) ) ;
extern char *temp_copy PROTO_S ( ( char * ) ) ;


/*
    MACROS FOR ADDRESSING MEMORY ALLOCATION ROUTINES
*/

#define alloc_nof( TYPE, NO )\
    ( ( TYPE * ) xalloc ( ( ( int ) ( NO ) * ( int ) sizeof ( TYPE ) ) ) )

#define realloc_nof( PTR, TYPE, NO )\
    ( ( TYPE * ) xrealloc ( ( pointer ) ( PTR ),\
      ( ( int ) ( NO ) * ( int ) sizeof ( TYPE ) ) ) )

#define string_copy_aux( STR )\
    string_copy ( ( STR ), ( int ) strlen ( STR ) )


/*
    CONVERSION ROUTINES
*/

extern char *ulong_to_octal PROTO_S ( ( unsigned long ) ) ;
extern unsigned long octal_to_ulong PROTO_S ( ( char * ) ) ;
extern boolean fits_ulong PROTO_S ( ( char *, int ) ) ;


#endif
