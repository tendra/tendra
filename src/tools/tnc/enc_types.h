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


#ifndef ENC_TYPES_INCLUDED
#define ENC_TYPES_INCLUDED


/*
    TYPE REPRESENTING A BITSTREAM

    A bitstream consists of a table, source, of length bytes.  The
    current position in the table is given by the bytes and bits fields.
    Bitstreams may be linked via the next field.  The end field of the
    first bitstream in a list points to the last bitstream in that list.
*/

typedef struct x_bitstream {
    unsigned bytes ;
    unsigned bits ;
    unsigned length ;
    byte *source ;
    struct x_bitstream *next ;
    struct x_bitstream *end ;
} bitstream ;


#endif
