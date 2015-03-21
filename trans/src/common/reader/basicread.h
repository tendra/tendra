/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef BASICREAD_H
#define BASICREAD_H

#include <stdio.h>

#include <tdf/tdfbool.h>

#include <construct/installtypes.h>
#include <reader/token.h>

extern int crt_lno;
extern char *crt_flnm;
extern int crt_charno;

/* start the input stream reading from the file f */
void initreader(FILE *f, const char *n);

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

/* reads a tdfstring from the input stream */
tdfstring d_tdfstring(void);

/* reads a tdfident from the input stream */
tdfstring d_tdfident(void);

/* reads a tdfbool from the input stream */
tdfbool d_tdfbool(void);

/* reads a tdfint from the input stream */
tdfint d_tdfint(void);

#endif /* BASICREAD_H */
