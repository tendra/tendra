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


#ifndef READ_INCLUDED
#define READ_INCLUDED


/*
    CONFIGURATION CONSTANTS

    These macros describe the number of bits in a byte, how to mask N
    bits etc.
*/

#ifndef NO_LIMITS_H
#include <limits.h>
#endif

#ifndef CHAR_BIT
#define CHAR_BIT		8
#endif

#define MASK( N )	( ( unsigned long ) ( ( 1 << ( N ) ) - 1 ) )


/*
    DECLARATIONS FOR DISK READING ROUTINES
*/

extern unsigned long bitmask [] ;
extern void init_bitmask PROTO_S ( ( void ) ) ;
extern void read_file PROTO_S ( ( char * ) ) ;


#endif
