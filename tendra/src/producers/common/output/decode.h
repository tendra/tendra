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


#ifndef DECODE_INCLUDED
#define DECODE_INCLUDED


/*
    BITSTREAM DECODING DECLARATIONS

    The routines in this module are concerned with low level input.
*/

extern unsigned de_bits PROTO_S ( ( BITSTREAM *, unsigned ) ) ;
extern unsigned long de_long_bits PROTO_S ( ( BITSTREAM *, unsigned ) ) ;
extern unsigned long de_int PROTO_S ( ( BITSTREAM * ) ) ;
extern void de_tdfstring PROTO_S ( ( BITSTREAM *, BUFFER * ) ) ;
extern void de_boundary PROTO_S ( ( BITSTREAM * ) ) ;
extern int de_eof PROTO_S ( ( BITSTREAM * ) ) ;


/*
    DECODING MACROS

    These macros give shorthands for the main decoding routines which are
    used in this module.
*/

#define DE_BITS( A, B )		de_bits ( ( A ), ( unsigned ) ( B ) )
#define DE_BITS_2( A, B )	de_long_bits ( ( A ), ( unsigned ) ( B ) )
#define DE_INT( A )		de_int ( ( A ) )
#define DE_ALIGN( A )		de_boundary ( ( A ) )
#define DE_BOOL( A )		( ( int ) DE_BITS ( A, 1 ) )


#endif
