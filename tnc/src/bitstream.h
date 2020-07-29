/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef BITSTREAM_H
#define BITSTREAM_H


/*
    LOW-LEVEL ENCODING ROUTINES
*/

bitstream *new_bitstream(void);
long bitstream_length(bitstream *);
void join_bitstreams(bitstream *, bitstream *);
void enc_bits(bitstream *, int, long);
void align_bitstream(bitstream *);
void print_bitstream(bitstream *);


#endif /* BITSTREAM_H */
