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


#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED


/*
    TYPE REPRESENTING A PORTABILITY TABLE ENTRY

    The portability table consists of an array of type PORT_ENTRY.  The
    PORT_* macros identify the various elements of this array.
*/

typedef struct {
    CONST char *name ;
    int set ;
    unsigned value ;
    BASE_TYPE type ;
} PORT_ENTRY ;

#define PORT_char_bits			0
#define PORT_short_bits			1
#define PORT_int_bits			2
#define PORT_long_bits			3
#define PORT_llong_bits			4
#define PORT_max_bits			5
#define PORT_signed_range		6
#define PORT_char_type			7
#define PORT_exact_range		8
#define PORT_ptr_int			9
#define PORT_ptr_fn			10
#define PORT_non_proto			11
#define PORT_multibyte			12
#define PORT_size			13


/*
    PORTABILITY TABLE DECLARATIONS

    The routines in this module are concerned with reading the portability
    table.
*/

extern void read_table PROTO_S ( ( string ) ) ;
extern PORT_ENTRY port_entry [] ;


#endif
