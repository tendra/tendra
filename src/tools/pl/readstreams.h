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


#ifndef READSTREAMS_INCLUDED
#define READSTREAMS_INCLUDED


#include "streams.h"

typedef struct{int byte_pos; int bit_pos; Chunk * ch; } Instream;

extern Instream * curin;
extern unsigned int get_bit PROTO_S((void));
extern unsigned int get_basic_int PROTO_S((int bts, Bool e));
extern unsigned int get_tdfint PROTO_S((void));
extern unsigned int d_tdfint PROTO_S((int n));

extern unsigned int d_tdfstring PROTO_S((int n));
extern unsigned int d_tdfident PROTO_S((int n));
extern unsigned int d_bytestream PROTO_S((int n));
extern void consname PROTO_S((char * s, int n));
extern unsigned int d_tdfbool PROTO_S((int n));
extern void read_cur PROTO_S((unsigned int (*f) PROTO_S((int))));
extern unsigned int d_bitstream PROTO_S((char * s, int n));
extern void print_res PROTO_S((void));

#endif
