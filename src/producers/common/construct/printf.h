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


#ifndef PRINTF_INCLUDED
#define PRINTF_INCLUDED


/*
    PRINTF AND SCANF ARGUMENT CHECKING

    The routines in this module are concerned with the checking of the
    arguments to functions like printf and scanf where a format string is
    used to specify a list of extra arguments.
*/

extern LIST ( TYPE ) find_printf_args PROTO_S ( ( STRING, unsigned, int ) ) ;
extern int is_printf_type PROTO_S ( ( TYPE ) ) ;
extern void init_printf PROTO_S ( ( void ) ) ;
extern TYPE type_printf ;
extern TYPE type_scanf ;
extern TYPE type_wprintf ;
extern TYPE type_wscanf ;


#endif
