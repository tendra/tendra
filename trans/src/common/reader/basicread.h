/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef READER_BASICREAD_H
#define READER_BASICREAD_H


#include <stdio.h>

#include <tdf/tdfbool.h>

#include <construct/installtypes.h>
#include <reader/token.h>


/* read n bits from the input stream */
int getcode(int n);

/* read construct encoding number (n bit pieces) from the input stream */
int get_big_code(int n);

/* deliver the current place in the input stream */
place keep_place(void);

/* start reading from pl in the input stream */
void set_place(place pl);

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


/*
 * The following functions read a tdfstring, tdfident, tdfbool and tdfint
 * from the input stream respectively.
 */
tdfstring d_tdfstring(void);
tdfstring d_tdfident(void);
tdfbool d_tdfbool(void);
tdfint d_tdfint(void);


#endif

