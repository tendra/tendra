/* $Id$ */

/*
 * Copyright 2002-2015, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ENCODE_INCLUDED
#define ENCODE_INCLUDED


/*
    BITSTREAM ENCODING DECLARATIONS

    The routines in this module are concerned with low level output.
*/

extern BITSTREAM *enc_ascii(BITSTREAM *, unsigned long, string);
extern BITSTREAM *enc_ident(BITSTREAM *, string, unsigned long);
extern BITSTREAM *enc_tdfstring(BITSTREAM *, unsigned long, string);
extern BITSTREAM *enc_ustring(BITSTREAM *, string);


#endif
