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


#ifndef FETCH_INCLUDED
#define FETCH_INCLUDED


/*
    LOW-LEVEL DECODING ROUTINES
*/

extern void byte_align PROTO_S ( ( void ) ) ;
extern long fetch PROTO_S ( ( int ) ) ;
extern long input_posn PROTO_S ( ( void ) ) ;
extern void input_goto PROTO_S ( ( long ) ) ;
extern void input_skip PROTO_S ( ( long ) ) ;
extern unsigned bits_in_buff ;
extern long bytes_read ;


#endif
