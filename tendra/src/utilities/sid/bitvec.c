/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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
 *
 *    		 Crown Copyright (c) 1997
 *
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**** bitvec.c --- Bit vector manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the bit vector manipulation routines specified in
 * "bitvec.h".  See that file for more details.
 */

/****************************************************************************/

#include "bitvec.h"

/*--------------------------------------------------------------------------*/

static unsigned			bitvec_size;
static unsigned			bitvec_valid_bits;
static ByteT			bitvec_mask;

#define NUM_BITS ((unsigned) (CHAR_BIT))

/*--------------------------------------------------------------------------*/

void
bitvec_set_size(unsigned size)
{
	bitvec_valid_bits = size;
	bitvec_size       = ((size + NUM_BITS - (unsigned) 1) / NUM_BITS);
	bitvec_mask       = (ByteT) 0;
	if (size % NUM_BITS) {
		unsigned i;
		unsigned mask =0;
		
		for (i = (NUM_BITS - (size % NUM_BITS)); i; i --) {
			mask >>= 1;
			mask  |= ((unsigned) 1 << (NUM_BITS - (unsigned) 1));
		}
		bitvec_mask = (ByteT) mask;
	}
	bitvec_mask = (~bitvec_mask);
}

void
bitvec_init(BitVecP bitvec)
{
	bitvec->bits = ALLOCATE_VECTOR (ByteT, bitvec_size);
}

void
bitvec_copy(BitVecP to, BitVecP from)
{
	to->bits = ALLOCATE_VECTOR (ByteT, bitvec_size);
	(void) memcpy ((GenericP) (to->bits), (GenericP) (from->bits),
				   (size_t) bitvec_size);
}

void
bitvec_replace(BitVecP to, BitVecP from)
{
	(void) memcpy ((GenericP) (to->bits), (GenericP) (from->bits),
				   (size_t) bitvec_size);
}

void
bitvec_empty(BitVecP bitvec)
{
	(void) memset ((GenericP) (bitvec->bits), 0, (size_t) bitvec_size);
}

BoolT
bitvec_is_empty(BitVecP bitvec)
{
	ByteP    bitvec_bits = (bitvec->bits);
	unsigned bytes       = bitvec_size;
	
	while (bytes--) {
		if (*bitvec_bits++) {
			return (FALSE);
		}
	}
	return (TRUE);
}

BoolT
bitvec_is_full(BitVecP bitvec)
{
	ByteP    bitvec_bits = (bitvec->bits);
	unsigned bytes       = bitvec_size;
	
	while (bytes --) {
		ByteT byte = (*bitvec_bits ++);
		
		if (bytes == 0) {
			byte |= (ByteT) ~bitvec_mask;
		}
		byte = ~byte;
		if (byte) {
			return (FALSE);
		}
	}
	return (TRUE);
}

void
bitvec_set(BitVecP bitvec, unsigned bit)
{
	ASSERT (bit < bitvec_valid_bits);
	(bitvec->bits) [bit / NUM_BITS] |= (ByteT) (1 << (bit % NUM_BITS));
}

BoolT
bitvec_is_set(BitVecP bitvec, unsigned bit)
{
	ASSERT (bit < bitvec_valid_bits);
	return ((bitvec->bits) [bit / NUM_BITS] & ((ByteT) 1 << (bit % NUM_BITS)));
}

void
bitvec_or(BitVecP to, BitVecP from)
{
	ByteP    to_bits   = (to->bits);
	ByteP    from_bits = (from->bits);
	unsigned bytes     = bitvec_size;
	
	while (bytes--) {
		(*to_bits++) |= (*from_bits++);
	}
}

void
bitvec_and(BitVecP to, BitVecP from)
{
	ByteP    to_bits   = (to->bits);
	ByteP    from_bits = (from->bits);
	unsigned bytes     = bitvec_size;
	
	while (bytes--) {
		(*to_bits++) &= (*from_bits++);
	}
}

void
bitvec_not(BitVecP to)
{
	ByteP    to_bits = (to->bits);
	unsigned bytes   = bitvec_size;
	
	while (bytes--) {
		(*to_bits) = (~(*to_bits));
		to_bits++;
	}
	(to->bits) [bitvec_size - 1] &= bitvec_mask;
}

BoolT
bitvec_equal(BitVecP bitvec1, BitVecP bitvec2)
{
	ByteP    bitvec1_bits = (bitvec1->bits);
	ByteP    bitvec2_bits = (bitvec2->bits);
	unsigned bytes        = bitvec_size;
	
	while (bytes --) {
		if ((*bitvec1_bits++) != (*bitvec2_bits++)) {
			return (FALSE);
		}
	}
	return (TRUE);
}

BoolT
bitvec_intersects(BitVecP bitvec1, BitVecP bitvec2)
{
	ByteP    bitvec1_bits = (bitvec1->bits);
	ByteP    bitvec2_bits = (bitvec2->bits);
	unsigned bytes        = bitvec_size;
	
	while (bytes--) {
		if ((*bitvec1_bits++) & (*bitvec2_bits++)) {
			return (TRUE);
		}
	}
	return (FALSE);
}

unsigned
bitvec_num_bits(BitVecP bitvec)
{
	unsigned i;
	unsigned num_bits = 0;
	
	for (i = 0; i < bitvec_valid_bits; i ++) {
		if (bitvec_is_set (bitvec, i)) {
			num_bits ++;
		}
	}
	return (num_bits);
}

unsigned
bitvec_first_bit(BitVecP bitvec)
{
	unsigned i;
	
	for (i = 0; i < bitvec_valid_bits; i ++) {
		if (bitvec_is_set (bitvec, i)) {
			return (i);
		}
	}
	return (bitvec_valid_bits);
}

BoolT
bitvec_next_bit(BitVecP bitvec, unsigned *next_ref)
{
	unsigned i;
	
	for (i = ((*next_ref) + 1); i < bitvec_valid_bits; i ++) {
		if (bitvec_is_set (bitvec, i)) {
			*next_ref = i;
			return (TRUE);
		}
	}
	return (FALSE);
}

void
bitvec_destroy(BitVecP bitvec)
{
	DEALLOCATE (bitvec->bits);
}

void
write_bitvec_indices(OStreamP ostream, BitVecP bitvec)
{
	unsigned num_bits_set = 0;
	unsigned i;
	
	for (i = 0; i < bitvec_valid_bits; i ++) {
		if (bitvec_is_set (bitvec, i)) {
			num_bits_set ++;
		}
	}
	for (i = 0; i < bitvec_valid_bits; i ++) {
		if (bitvec_is_set (bitvec, i)) {
			write_unsigned (ostream, i);
			num_bits_set --;
			if (num_bits_set == 1) {
				write_cstring (ostream, " & ");
			} else if (num_bits_set != 0) {
				write_cstring (ostream, ", ");
			}
		}
	}
}
