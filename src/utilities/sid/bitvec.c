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


/**** bitvec.c --- Bit vector manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the bit vector manipulation routines specified in
 * "bitvec.h".  See that file for more details.
 *
 **** Change Log:
 * $Log: bitvec.c,v $
 * Revision 1.1.1.1  1998/01/17  15:57:43  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/15  09:56:59  smf
 * Brought into line with OSSG C Coding Standards Document, as per
 * "CR94_178.sid+tld-update".
 *
 * Revision 1.1.1.1  1994/07/25  16:05:47  smf
 * Initial import of library shared files.
 *
**/

/****************************************************************************/

#include "bitvec.h"

/*--------------------------------------------------------------------------*/

static unsigned			bitvec_size;
static unsigned			bitvec_valid_bits;
static ByteT			bitvec_mask;

#define NUM_BITS ((unsigned) (CHAR_BIT))

/*--------------------------------------------------------------------------*/

void
bitvec_set_size PROTO_N ((size))
		PROTO_T (unsigned size)
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
bitvec_init PROTO_N ((bitvec))
	    PROTO_T (BitVecP bitvec)
{
    bitvec->bits = ALLOCATE_VECTOR (ByteT, bitvec_size);
}

void
bitvec_copy PROTO_N ((to, from))
	    PROTO_T (BitVecP to X
		     BitVecP from)
{
    to->bits = ALLOCATE_VECTOR (ByteT, bitvec_size);
    (void) memcpy ((GenericP) (to->bits), (GenericP) (from->bits),
		   (SizeT) bitvec_size);
}

void
bitvec_replace PROTO_N ((to, from))
	       PROTO_T (BitVecP to X
			BitVecP from)
{
    (void) memcpy ((GenericP) (to->bits), (GenericP) (from->bits),
		   (SizeT) bitvec_size);
}

void
bitvec_empty PROTO_N ((bitvec))
	     PROTO_T (BitVecP bitvec)
{
    (void) memset ((GenericP) (bitvec->bits), 0, (SizeT) bitvec_size);
}

BoolT
bitvec_is_empty PROTO_N ((bitvec))
		PROTO_T (BitVecP bitvec)
{
    ByteP    bitvec_bits = (bitvec->bits);
    unsigned bytes       = bitvec_size;

    while (bytes --) {
	if (*bitvec_bits ++) {
	    return (FALSE);
	}
    }
    return (TRUE);
}

BoolT
bitvec_is_full PROTO_N ((bitvec))
	       PROTO_T (BitVecP bitvec)
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
bitvec_set PROTO_N ((bitvec, bit))
	   PROTO_T (BitVecP  bitvec X
		    unsigned bit)
{
    ASSERT (bit < bitvec_valid_bits);
    (bitvec->bits) [bit / NUM_BITS] |= (ByteT) (1 << (bit % NUM_BITS));
}

BoolT
bitvec_is_set PROTO_N ((bitvec, bit))
	      PROTO_T (BitVecP  bitvec X
		       unsigned bit)
{
    ASSERT (bit < bitvec_valid_bits);
    return ((bitvec->bits) [bit / NUM_BITS] & ((ByteT) 1 << (bit % NUM_BITS)));
}

void
bitvec_or PROTO_N ((to, from))
	  PROTO_T (BitVecP to X
		   BitVecP from)
{
    ByteP    to_bits   = (to->bits);
    ByteP    from_bits = (from->bits);
    unsigned bytes     = bitvec_size;

    while (bytes --) {
	(*to_bits ++) |= (*from_bits ++);
    }
}

void
bitvec_and PROTO_N ((to, from))
	   PROTO_T (BitVecP to X
		    BitVecP from)
{
    ByteP    to_bits   = (to->bits);
    ByteP    from_bits = (from->bits);
    unsigned bytes     = bitvec_size;

    while (bytes --) {
	(*to_bits ++) &= (*from_bits ++);
    }
}

void
bitvec_not PROTO_N ((to))
	   PROTO_T (BitVecP to)
{
    ByteP    to_bits = (to->bits);
    unsigned bytes   = bitvec_size;

    while (bytes --) {
	(*to_bits) = (~(*to_bits));
	to_bits ++;
    }
    (to->bits) [bitvec_size - 1] &= bitvec_mask;
}

BoolT
bitvec_equal PROTO_N ((bitvec1, bitvec2))
	     PROTO_T (BitVecP bitvec1 X
		      BitVecP bitvec2)
{
    ByteP    bitvec1_bits = (bitvec1->bits);
    ByteP    bitvec2_bits = (bitvec2->bits);
    unsigned bytes        = bitvec_size;

    while (bytes --) {
	if ((*bitvec1_bits ++) != (*bitvec2_bits ++)) {
	    return (FALSE);
	}
    }
    return (TRUE);
}

BoolT
bitvec_intersects PROTO_N ((bitvec1, bitvec2))
		  PROTO_T (BitVecP bitvec1 X
			   BitVecP bitvec2)
{
    ByteP    bitvec1_bits = (bitvec1->bits);
    ByteP    bitvec2_bits = (bitvec2->bits);
    unsigned bytes        = bitvec_size;

    while (bytes --) {
	if ((*bitvec1_bits ++) & (*bitvec2_bits ++)) {
	    return (TRUE);
	}
    }
    return (FALSE);
}

unsigned
bitvec_num_bits PROTO_N ((bitvec))
		PROTO_T (BitVecP  bitvec)
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
bitvec_first_bit PROTO_N ((bitvec))
		 PROTO_T (BitVecP  bitvec)
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
bitvec_next_bit PROTO_N ((bitvec, next_ref))
		PROTO_T (BitVecP   bitvec X
			 unsigned *next_ref)
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
bitvec_destroy PROTO_N ((bitvec))
	       PROTO_T (BitVecP bitvec)
{
    DEALLOCATE (bitvec->bits);
}

void
write_bitvec_indices PROTO_N ((ostream, bitvec))
		     PROTO_T (OStreamP ostream X
			      BitVecP  bitvec)
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

/*
 * Local variables(smf):
 * eval: (include::add-path-entry "../os-interface" "../generated")
 * end:
**/
