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


#ifndef EXECUTE_INCLUDED
#define EXECUTE_INCLUDED


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with building up the current command
    and then executing it.
*/

extern void enable_delayed_signal PROTO_S ( ( void ) ) ;
extern void disable_delayed_signal PROTO_S ( ( void ) ) ;
extern void process_delayed_signal PROTO_S ( ( void ) ) ;
extern void reset_exec_error PROTO_S ( ( void ) ) ;
extern void cmd_string PROTO_S ( ( char * ) ) ;
extern void cmd_filename PROTO_S ( ( filename * ) ) ;
extern void cmd_list PROTO_S ( ( list * ) ) ;
extern void kill_stray PROTO_S ( ( void ) ) ;
extern void remove_junk PROTO_S ( ( void ) ) ;
extern filename *execute PROTO_S ( ( filename *, filename * ) ) ;


/*
    LAST COMMAND

    These variables give the details of the last command executed.
*/

extern char *last_command ;
extern int last_return ;
extern boolean exec_error ;


#endif
