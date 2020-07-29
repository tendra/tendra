/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef READSTREAMS_INCLUDED
#define READSTREAMS_INCLUDED


#include "streams.h"

typedef struct{
	int byte_pos;
	int bit_pos;
	Chunk *ch;
} Instream;

extern Instream *curin;
extern unsigned int get_bit(void);
extern unsigned int get_basic_int(int bts, Bool e);
extern unsigned int get_tdfint(void);
extern unsigned int d_tdfint(int n);

extern unsigned int d_tdfstring(int n);
extern unsigned int d_tdfident(int n);
extern unsigned int d_bytestream(int n);
extern void consname(char *s, int n);
extern unsigned int d_tdfbool(int n);
extern void read_cur(unsigned int(*f)(int));
extern unsigned int d_bitstream(char *s, int n);
extern void print_res(void);

#endif
