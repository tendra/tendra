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


#ifndef FILE_INCLUDED
#define FILE_INCLUDED


/*
    FILE HANDLING ROUTINES

    This file contains the low level file reading and writing routines.
*/

extern FILE *pp_file ;
extern place here ;
extern int printflag ;
extern int column ;
extern int maximum ;
extern int lastc ;
extern int read_error ;
extern int dump ;

extern void open_files PROTO_S ( ( char *, char * ) ) ;
extern long fetch PROTO_S ( ( int ) ) ;
extern void byte_align PROTO_S ( ( void ) ) ;
extern void set_place PROTO_S ( ( place * ) ) ;
extern void skip_bits PROTO_S ( ( long ) ) ;
extern void init_spaces PROTO_S ( ( int ) ) ;
extern void spaces PROTO_S ( ( int ) ) ;

#define posn( X )	( ( X ).byte * BYTESIZE + ( X ).bit )


#endif
