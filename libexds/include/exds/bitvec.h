/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bitvec.h - Bit vector manipulation.
 *
 * This file specifies the interface to a single size bit vector manipulation
 * facility.  It is necessary to call the ``bitvec_set_size'' function to set
 * the size of these bit vectors, before any are actually created.
 */

#ifndef H_BITVEC
#define H_BITVEC

#include <exds/common.h>
#include <exds/ostream.h>


/*
 * This is the bit vector type.
 * TODO is this private?
 */
typedef struct BitVecT BitVecT;
struct BitVecT {
	ByteT *bits;
};

/*
 * This function should be called once, before any bit vectors are
 * initialised.  Its argument should specify the number of bits in a bit
 * vector.  The bits will be numbered from zero to one less than the number
 * specified.
 */
void
bitvec_set_size(unsigned);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified bit vector.  Initially, all bits
 * are zero.
 */
void
bitvec_init(BitVecT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the to bit vector from the from bit vector.  It
 * is not necessary to have initialised the to bit vector with the
 * `bitvec_init' function previously.
 */
void
bitvec_copy(BitVecT *, BitVecT *);

/*
 * This function copies the from bit vector into the to bit vector.  The to
 * bit vector must have been initialised previously.
 */
void
bitvec_replace(BitVecT *, BitVecT *);

/*
 * This function sets all of the bits in the specified bit vector to zero.
 */
void
bitvec_empty(BitVecT *);

/*
 * This function returns true if all of the bits in the specified bit vector
 * are zero, and false otherwise.
 */
bool
bitvec_is_empty(BitVecT *);

/*
 * This function returns true if all of the bits in the specified bit vector
 * are set, and false otherwise.
 */
bool
bitvec_is_full(BitVecT *);

/*
 * This function sets the specified bit in the specified bit vector to one.
 * Bits are numbered from zero.  If the bit is out of range, then the effect
 * of this function is undefined.
 */
void
bitvec_set(BitVecT *, unsigned);

/*
 * This function returns true if the specified bit in the specified bit vector
 * is set to one, and false otherwise.  Bits are numbered from zero.  If the
 * bit is out of range, the effect of this function is undefined.
 */
bool
bitvec_is_set(BitVecT *, unsigned);

/*
 * This function performs an in-place bitwise or of the to bit vector and the
 * from bit vector, leaving the result in the to bit vector.
 */
void
bitvec_or(BitVecT *, BitVecT *);

/*
 * This function performs an in-place bitwise and of the to bit vector and the
 * from bit vector, leaving the result in the to bit vector.
 */
void
bitvec_and(BitVecT *, BitVecT *);

/*
 * This function performs an in-place bitwise negation of the to bit vector.
 */
void
bitvec_not(BitVecT *);

/*
 * This function returns true if both of the specified bit vectors are equal,
 * and false otherwise.
 */
bool
bitvec_equal(BitVecT *, BitVecT *);

/*
 * This function returns true if the bitwise and of the specified bit vectors
 * contains at least one bit that is set to one, and false otherwise.
 */
bool
bitvec_intersects(BitVecT *, BitVecT *);

/*
 * This function returns the number of bits in the bit vector that are set to
 * one.
 */
unsigned
bitvec_num_bits(BitVecT *);

/*
 * This function returns the index of the first bit in the specified bit
 * vector that is set to one.
 */
unsigned
bitvec_first_bit(BitVecT *);

/*
 * This function looks for the first bit set to one in the specified bit
 * vector with a higher index than that specified in the number pointed to by
 * next_ref.  If such a bit is found, then the index of that bit is written
 * back into next_ref, and the function returns true.  If no such bit is
 * found, then the function returns false.
 */
bool
bitvec_next_bit(BitVecT *, unsigned *);

/*
 * This function destroys the specified bit vector.  After this, it should be
 * reinitialised before it is used.
 */
void
bitvec_destroy(BitVecT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes out to the specified ostream the indices of all bits
 * in the specified bit vector that are set to one.
 */
void
write_bitvec_indices(OStreamT *, BitVecT *);

#endif /* !defined (H_BITVEC) */
