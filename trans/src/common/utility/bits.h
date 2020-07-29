/*
 * Copyright 2002-2014, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef UTILITY_BITS_H
#define UTILITY_BITS_H

typedef unsigned long bitpattern;

extern bitpattern lsb_mask[33];
extern bitpattern msb_mask[33];

/*
 * Count the bits set.
 */
int
bits_in(bitpattern);

/*
 * Find the first non-zero bit
 *
 * Returns the bit number of the least significant set bit.
 * For 0 it returns -1.
 */
int
bit_one(bitpattern);

#endif

