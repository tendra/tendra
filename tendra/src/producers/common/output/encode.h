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


#ifndef ENCODE_INCLUDED
#define ENCODE_INCLUDED


/*
    BITSTREAM ENCODING DECLARATIONS

    The routines in this module are concerned with low level output.
*/

extern BITSTREAM *start_bitstream PROTO_S ( ( FILE *, gen_ptr ) ) ;
extern void end_bitstream PROTO_S ( ( BITSTREAM *, int ) ) ;
extern BITSTREAM *enc_bits PROTO_S ( ( BITSTREAM *, unsigned, unsigned ) ) ;
extern BITSTREAM *enc_long_bits PROTO_S ( ( BITSTREAM *, unsigned, unsigned long ) ) ;
extern BITSTREAM *enc_bytes PROTO_S ( ( BITSTREAM *, unsigned long, string ) ) ;
extern BITSTREAM *enc_ascii PROTO_S ( ( BITSTREAM *, unsigned long, string ) ) ;
extern BITSTREAM *enc_extn PROTO_S ( ( BITSTREAM *, unsigned, unsigned ) ) ;
extern BITSTREAM *enc_int PROTO_S ( ( BITSTREAM *, unsigned long ) ) ;
extern BITSTREAM *enc_int_aux PROTO_S ( ( BITSTREAM *, unsigned long ) ) ;
extern BITSTREAM *enc_ident PROTO_S ( ( BITSTREAM *, string, unsigned long ) ) ;
extern BITSTREAM *enc_tdfstring PROTO_S ( ( BITSTREAM *, unsigned long, string ) ) ;
extern BITSTREAM *enc_ustring PROTO_S ( ( BITSTREAM *, string ) ) ;
extern BITSTREAM *enc_boundary PROTO_S ( ( BITSTREAM * ) ) ;
extern BITSTREAM *enc_bitstream PROTO_S ( ( BITSTREAM *, BITSTREAM * ) ) ;
extern BITSTREAM *join_bitstreams PROTO_S ( ( BITSTREAM *, BITSTREAM * ) ) ;
extern unsigned length_bitstream PROTO_S ( ( BITSTREAM * ) ) ;


/*
    BITSTREAM SIZES

    These macros give the number of bits in a byte and the number of
    bytes in a bitstream.
*/

#define BYTE_SIZE		( ( unsigned ) 8 )
#define CHUNK_SIZE		( ( unsigned ) 64 )
#define CHUNK_COPY		( ( unsigned ) 8 )
#define BYTE_MASK		( ( unsigned ) 0xff )


/*
    ENCODING MACROS

    These macros give shorthands for the main encoding routines which are
    used in this module.  Note that A is used at least twice in each
    definition.
*/

#define ENC_BITS( A, B, C )\
    ( A ) = enc_bits ( ( A ), ( unsigned ) ( B ), ( unsigned ) ( C ) )

#define ENC_BITS_2( A, B, C )\
    ( A ) = enc_long_bits ( ( A ), ( unsigned ) ( B ), ( ulong ) ( C ) )

#define ENC_EXTN( A, B, C )\
    ( A ) = enc_extn ( ( A ), ( unsigned ) ( B ), ( unsigned ) ( C ) )

#define ENC_INT( A, B )\
    ( A ) = enc_int ( ( A ), ( unsigned long ) ( B ) )

#define ENC_IDENT( A, B, C )\
    ( A ) = enc_ident ( ( A ), ( B ), ( unsigned long ) ( C ) )

#define ENC_ALIGN( A )\
    ( A ) = enc_boundary ( ( A ) )

#define ENC_BOOL( A, B )	ENC_BITS ( A, 1, B )
#define ENC_ON( A )		ENC_BITS ( A, 1, 1 )
#define ENC_OFF( A )		ENC_BITS ( A, 1, 0 )
#define ENC_OFFS( A, B )	ENC_BITS ( A, B, 0 )


#endif
