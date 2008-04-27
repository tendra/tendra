/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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

#ifndef BASICREAD_H
#define BASICREAD_H

extern int crt_lno;
extern char *crt_flnm;
extern int crt_charno;

/* start the input stream reading from the file called n */
char initreader(char *n);
void endreader(void);

/* read n bits from the input stream */
int getcode(int n);

/* read construct encoding number (n bit pieces) from the input stream */
int get_big_code(int n);

/* deliver the current place in the input stream */
place keep_place(void);

/* form a place n bits further on in the input stream than pl */
place add_place(place pl, int n);

/* start reading from pl in the input stream */
void set_place(place pl);

/*
 * records bn bits from the input stream in a new place.
 * The input stream is stepped on over these bits
 */
place new_place(int bn);

/* records the failure message s and sets good_trans to false */
void failer(char *s);

int  small_dtdfint(void);

/* step the input stream on to the next byte boundary */
void to_boundary(void);

/*
 * delivers a new place for the bitstream in
 * the input stream and steps over it
 */
bitstream d_bitstream(void);

/* records in bytestream_pickup the end of a bytestream */
void start_bytestream(void);

/* returns bytestream_pickup */
bytestream d_bytestream(void);

/* steps over a bytestream */
void ignore_bytestream(void);

/* resets the input stream from bytestream_pickup */
void end_bytestream(void);

/* reads a tdfstring from the input stream */
tdfstring d_tdfstring(void);

/* reads a tdfident from the input stream */
tdfstring d_tdfident(void);

/* reads a tdfbool from the input stream */
tdfbool d_tdfbool(void);

/* reads a tdfint from the input stream */
tdfint d_tdfint(void);

void add_capsule_frees(void *vp);

#endif /* BASICREAD_H */
