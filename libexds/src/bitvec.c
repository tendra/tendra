/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bitvec.c - Bit vector manipulation.
 *
 * This file implements the bit vector manipulation routines specified in
 * "bitvec.h".  See that file for more details.
 */

#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/ostream.h>
#include <exds/bitvec.h>
#include <exds/dalloc.h>

/*
 * XXX These need to move into some ctx struct
 */
static unsigned		bitvec_size;
static unsigned		bitvec_valid_bits;
static ByteT		bitvec_mask;

#define NUM_BITS ((unsigned) CHAR_BIT)

void
bitvec_set_size(unsigned size)
{
	bitvec_valid_bits = size;
	bitvec_size       = (size + NUM_BITS - (unsigned) 1) / NUM_BITS;
	bitvec_mask       = 0;

	if (size % NUM_BITS) {
		unsigned i;
		unsigned mask = 0;

		for (i = (NUM_BITS - (size % NUM_BITS)); i; i--) {
			mask >>= 1;
			mask  |= (unsigned) 1 << (NUM_BITS - (unsigned) 1);
		}
		bitvec_mask = (ByteT) mask;
	}
	bitvec_mask = ~bitvec_mask;
}

void
bitvec_init(BitVecT *bitvec)
{
	bitvec->bits = ALLOCATE_VECTOR(ByteT, bitvec_size);
}

void
bitvec_copy(BitVecT *to, BitVecT *from)
{
	to->bits = ALLOCATE_VECTOR(ByteT, bitvec_size);
	IGNORE memcpy(to->bits, from->bits, (size_t) bitvec_size);
}

void
bitvec_replace(BitVecT *to, BitVecT *from)
{
	IGNORE memcpy(to->bits, from->bits, (size_t) bitvec_size);
}

void
bitvec_empty(BitVecT *bitvec)
{
	IGNORE memset(bitvec->bits, 0, (size_t) bitvec_size);
}

BoolT
bitvec_is_empty(BitVecT *bitvec)
{
	ByteT *bitvec_bits = bitvec->bits;
	unsigned bytes       = bitvec_size;

	while (bytes--) {
		if (*bitvec_bits++) {
			return FALSE;
		}
	}

	return TRUE;
}

BoolT
bitvec_is_full(BitVecT *bitvec)
{
	ByteT *bitvec_bits = bitvec->bits;
	unsigned bytes       = bitvec_size;

	while (bytes--) {
		ByteT byte = *bitvec_bits++;

		if (bytes == 0) {
			byte |= (ByteT) ~bitvec_mask;
		}
		byte = ~byte;
		if (byte) {
			return FALSE;
		}
	}

	return TRUE;
}

void
bitvec_set(BitVecT *bitvec, unsigned bit)
{
	assert(bit < bitvec_valid_bits);
	bitvec->bits[bit / NUM_BITS] |= (ByteT) (1 << (bit % NUM_BITS));
}

BoolT
bitvec_is_set(BitVecT *bitvec, unsigned bit)
{
    assert(bit < bitvec_valid_bits);
	/* XXX check cast and parenthesis wrt bitvec_set() */
    return bitvec->bits[bit / NUM_BITS] & ((ByteT) 1 << (bit % NUM_BITS));
}

void
bitvec_or(BitVecT *to, BitVecT *from)
{
	ByteT *to_bits   = to->bits;
	ByteT *from_bits = from->bits;
	unsigned bytes     = bitvec_size;

	while (bytes--) {
		*to_bits++ |= *from_bits++;
	}
}

void
bitvec_and(BitVecT *to, BitVecT *from)
{
	ByteT *to_bits   = to->bits;
	ByteT *from_bits = from->bits;
	unsigned bytes     = bitvec_size;

	while (bytes--) {
		*to_bits++ &= *from_bits++;
	}
}

void
bitvec_not(BitVecT *to)
{
	ByteT *to_bits = to->bits;
	unsigned bytes   = bitvec_size;

	while (bytes--) {
		*to_bits = ~(*to_bits);
		to_bits++;
	}
	to->bits[bitvec_size - 1] &= bitvec_mask;
}

BoolT
bitvec_equal(BitVecT *bitvec1, BitVecT *bitvec2)
{
	ByteT *bitvec1_bits = bitvec1->bits;
	ByteT *bitvec2_bits = bitvec2->bits;
	unsigned bytes        = bitvec_size;

	while (bytes--) {
		if (*bitvec1_bits++ != *bitvec2_bits++) {
			return FALSE;
		}
	}

	return TRUE;
}

BoolT
bitvec_intersects(BitVecT *bitvec1, BitVecT *bitvec2)
{
	ByteT *bitvec1_bits = bitvec1->bits;
	ByteT *bitvec2_bits = bitvec2->bits;
	unsigned bytes        = bitvec_size;

	while (bytes--) {
		if (*bitvec1_bits++ & *bitvec2_bits++) {
			return TRUE;
		}
	}

	return FALSE;
}

unsigned
bitvec_num_bits(BitVecT *bitvec)
{
	unsigned i;
	unsigned num_bits = 0;

	/*
	 * There's a much niftier way to find the next bit set, if this ever needs
	 * optimising.
	 */
	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			num_bits++;
		}
	}

	return num_bits;
}

unsigned
bitvec_first_bit(BitVecT *bitvec)
{
	unsigned i;

	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			return i;
		}
	}

	return bitvec_valid_bits;
}

BoolT
bitvec_next_bit(BitVecT *bitvec, unsigned *next_ref)
{
	unsigned i;

	for (i = *next_ref + 1; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			*next_ref = i;
			return TRUE;
		}
	}

	return FALSE;
}

void
bitvec_destroy(BitVecT *bitvec)
{
	DEALLOCATE(bitvec->bits);
}

void
write_bitvec_indices(OStreamT *ostream, BitVecT *bitvec)
{
	unsigned num_bits_set = 0;
	unsigned i;

	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			num_bits_set++;
		}
	}

	for (i = 0; i < bitvec_valid_bits; i++) {
		if (bitvec_is_set(bitvec, i)) {
			write_unsigned(ostream, i);
			num_bits_set--;
			if (num_bits_set == 1) {
				write_cstring(ostream, " & ");
			} else if (num_bits_set != 0) {
				write_cstring(ostream, ", ");
			}
		}
	}
}
