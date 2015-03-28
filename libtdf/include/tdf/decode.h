/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TDF_DECODE_H
#define TDF_DECODE_H


/*
    BITSTREAM DECODING DECLARATIONS

    The routines in this module are concerned with low level input.
*/

extern unsigned de_bits(BITSTREAM *, unsigned);
extern unsigned long de_long_bits(BITSTREAM *, unsigned);
extern unsigned long de_int(BITSTREAM *);
extern void de_boundary(BITSTREAM *);
extern int de_eof(BITSTREAM *);


/*
    DECODING MACROS

    These macros give shorthands for the main decoding routines which are
    used in this module.
*/

#define DE_BITS(A, B)		de_bits((A), (unsigned)(B))
#define DE_BITS_2(A, B)		de_long_bits((A), (unsigned)(B))
#define DE_INT(A)		de_int((A))
#define DE_ALIGN(A)		de_boundary((A))
#define DE_BOOL(A)		((int)DE_BITS(A, 1))


#endif
