/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ENCODE_H
#define ENCODE_H


/*
    BASIC ENCODING ROUTINES
*/

void enc_bits_extn(bitstream *, int, long);
void enc_tdf_int(bitstream *, long);
void enc_aligned_string(bitstream *, char *, long);
void enc_external(bitstream *, construct *);
void enc_aldef(bitstream *, construct *);
void enc_tagdec(bitstream *, construct *);
int enc_tagdef(bitstream *, construct *);
void enc_tokdec(bitstream *, construct *);
void enc_tokdef(bitstream *, construct *);
void enc_node(bitstream *, node *);

#define enc_list_start(p)	enc_bits(p, 1, (long)0)


#endif /* ENCODE_H */
