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


#ifndef STARTUP_INCLUDED
#define STARTUP_INCLUDED


/*
    PROCEDURE DECLARATIONS

    These procedures are concerned with the tcc startup and endup
    files.
*/

extern void add_to_startup PROTO_S ( ( char * ) ) ;
extern void add_to_endup PROTO_S ( ( char * ) ) ;
extern void close_startup PROTO_S ( ( void ) ) ;
extern void remove_startup PROTO_S ( ( void ) ) ;
extern void add_pragma PROTO_S ( ( char * ) ) ;
extern void add_token PROTO_S ( ( char * ) ) ;


/*
    COMMAND-LINE OPTIONS

    These variables give the command-line options necessary to pass the
    startup and endup files to the producer.
*/

extern char *startup_opt, *endup_opt ;
extern char *tokdef_name ;


#endif
