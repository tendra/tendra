/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TDF_ENCODE_H
#define TDF_ENCODE_H


/*
    BITSTREAM ENCODING DECLARATIONS

    The routines in this module are concerned with low level output.
*/

extern BITSTREAM *extend_bitstream(BITSTREAM *bs);
extern BITSTREAM *enc_bits(BITSTREAM *, unsigned, unsigned);
extern BITSTREAM *enc_long_bits(BITSTREAM *, unsigned, unsigned long);
extern BITSTREAM *enc_bytes(BITSTREAM *, unsigned long, bitstream_byte *);
extern BITSTREAM *enc_extn(BITSTREAM *, unsigned, unsigned);
extern BITSTREAM *enc_int(BITSTREAM *, unsigned long);
extern BITSTREAM *enc_int_aux(BITSTREAM *, unsigned long);
extern BITSTREAM *enc_boundary(BITSTREAM *);
extern BITSTREAM *enc_bitstream(BITSTREAM *, BITSTREAM *);
extern BITSTREAM *join_bitstreams(BITSTREAM *, BITSTREAM *);


/*
    ENCODING MACROS

    These macros give shorthands for the main encoding routines which are
    used in this module.  Note that A is used at least twice in each
    definition.
*/

#define ENC_BITS(A, B, C)\
    (A) = enc_bits((A), (unsigned)(B), (unsigned)(C))

#define ENC_BITS_2(A, B, C)\
    (A) = enc_long_bits((A), (unsigned)(B), (ulong)(C))

#define ENC_EXTN(A, B, C)\
    (A) = enc_extn((A), (unsigned)(B), (unsigned)(C))

#define ENC_INT(A, B)\
    (A) = enc_int((A), (unsigned long)(B))

#define ENC_IDENT(A, B, C)\
    (A) = enc_ident((A), (B), (unsigned long)(C))

#define ENC_ALIGN(A)\
    (A) = enc_boundary((A))

#define ENC_BOOL(A, B)	ENC_BITS(A, 1, B)
#define ENC_ON(A)	ENC_BITS(A, 1, 1)
#define ENC_OFF(A)	ENC_BITS(A, 1, 0)
#define ENC_OFFS(A, B)	ENC_BITS(A, B, 0)


#endif
