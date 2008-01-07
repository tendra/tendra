/*
 * Copyright (c) 2003-2004, Boris Popov.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $TenDRA$
 */

#ifndef TDF_TYPES_H
#define TDF_TYPES_H

/*
 * TDF format relies on byte size of 8 bits
 */
#define	TDF_BYTE_SIZE	8

/*
 * TDF_POS represents a bit position in the TDF stream.
 * On the machines with where sizeof(long) == 32, this limits maximum
 * size of TDF capsule to 512MBs.
 */
#define	tdf_pos_encode(off, bit)	((unsigned long)((off) << 3) | (bit))
#define	tdf_pos_offset(pos)			((pos) >> 3)
#define	tdf_pos_bit(pos)			((pos) & 7)
#define	tdf_pos_align(pos)			((pos) & ~7UL)

typedef unsigned long tdf_pos;

/*
 * TDFINT encodes non-negative integers of unbounded size.
 * Expected size of the TDFINT depends on context and it is worth
 * to provide different internal representations.
 */
#define	TDFINTL_MAX		ULONG_MAX
#define	TDFINT_MAXLEN	2048		/* maximum octets to be read */
typedef unsigned long TDFINTL;

/*
 * TDFEXTINT  - Extendable integer encoding.
 * n-bit extendable integer encoding enables an integer greater than
 * zero to be encoded given n, a number of bits.
 */
typedef unsigned long TDFEXTINT;

/*
 * TDFBOOL encodes boolean, true or false
 */
typedef unsigned int TDFBOOL;

/*
 * TDFSTRING encodes a sequence containing n non-negative integers,
 * each of k bits in size.
 */
typedef struct tdf_string {
	int			size;		/* size of single integer */
	TDFINTL		number;		/* number of integers */
	union tdf_string_dp {
		char		*chars;
		short		*shorts;
		long		*longs;
	} ints;
} TDFSTRING;

/*
 * TDFIDENT are identical to TDFSTRING
 */
typedef TDFSTRING TDFIDENT;

/*
 * Data used in the make_version construct
 */
struct tdf_version {
	int			major;
	int			minor;
};

/*
 * Some useful constants
 */
#define	TDF_MAGIC_LEN		4	/* length of signature in bytes */

extern const char tdf_ar_magic[TDF_MAGIC_LEN + 1];
extern const char tdf_cap_magic[TDF_MAGIC_LEN + 1];
extern const char tdf_gen_magic[4];
extern const char tdf_lib_magic[TDF_MAGIC_LEN + 1];
extern const char tdf_spec_magic[TDF_MAGIC_LEN + 1];

#endif /* !TDF_TYPES_H */
