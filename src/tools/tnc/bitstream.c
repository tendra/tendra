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


#include "config.h"
#include "types.h"
#include "enc_types.h"
#include "file.h"
#include "utility.h"


/*
    BITMASKS

    The nth value in this array can be used to extract the bottom n
    bits of a value.
*/

static unsigned long mask [] = {
    0, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff
} ;


/*
    SIZE OF A STANDARD BITSTREAM

    Each bitstream contains BITSTREAM_SIZE bytes.  It is worth garbage
    collecting if it has CRITICAL_SIZE bytes free when it is closed.
*/

#define BITSTREAM_SIZE		100
#define CRITICAL_SIZE		50


/*
    LIST OF FREE BITSTREAMS

    Bitstreams are allocated from this list.
*/

static bitstream *free_bitstreams = null ;


/*
    CREATE A NEW BITSTREAM

    A new bitstream is allocated and initialized.
*/

bitstream *new_bitstream
    PROTO_Z ()
{
    unsigned i ;
    bitstream *p ;
    if ( free_bitstreams == null ) {
	p = alloc_nof ( bitstream, 1 ) ;
	p->length = BITSTREAM_SIZE ;
	p->source = alloc_nof ( byte, BITSTREAM_SIZE + 10 ) ;
    } else {
	p = free_bitstreams ;
	free_bitstreams = p->next ;
    }
    for ( i = 0 ; i < p->length ; i++ ) p->source [i] = 0 ;
    p->bytes = 0 ;
    p->bits = 0 ;
    p->next = null ;
    p->end = p ;
    return ( p ) ;
}


#if 0

/*
    CLOSE OFF A BITSTREAM

    The bitstream p is closed off and any free space is garbage collected.
    (Not currently used.)
*/

static void close_bitstream
    PROTO_N ( ( p ) )
    PROTO_T ( bitstream *p )
{
    bitstream *q ;
    int used = p->end->bytes + 4 ;
    int left = p->end->length - used ;
    if ( left < CRITICAL_SIZE ) return ;
    q = alloc_nof ( bitstream, 1 ) ;
    q->length = left ;
    q->source = p->end->source + used ;
    q->next = free_bitstreams ;
    free_bitstreams = q ;
    p->end->length = used ;
    return ;
}

#endif


/*
    PRINT A BITSTREAM

    The bitstream p is dumped to the output file.
*/

void print_bitstream
    PROTO_N ( ( p ) )
    PROTO_T ( bitstream *p )
{
    unsigned r = 0 ;
    unsigned long buff = 0 ;
    for ( ; p ; p = p->next ) {
	unsigned i ;
	for ( i = 0 ; i < p->bytes ; i++ ) {
	    byte b = p->source [i] ;
	    if ( r == 0 ) {
		IGNORE fputc ( ( int ) b, output ) ;
	    } else {
		buff = ( buff << BYTESIZE ) | ( ( unsigned long ) b ) ;
		IGNORE fputc ( ( int ) ( ( buff >> r ) & 0xff ), output ) ;
		buff &= mask [r] ;
	    }
	}
	if ( p->bits ) {
	    byte b = p->source [ p->bytes ] ;
	    b = ( byte ) ( ( unsigned ) b >> ( BYTESIZE - p->bits ) ) ;
	    buff = ( buff << p->bits ) | ( ( unsigned long ) b ) ;
	    r += p->bits ;
	    if ( r >= BYTESIZE ) {
		r -= BYTESIZE ;
		IGNORE fputc ( ( int ) ( ( buff >> r ) & 0xff ), output ) ;
		buff &= mask [r] ;
	    }
	}
    }
    if ( r ) {
	buff <<= ( BYTESIZE - r ) ;
	IGNORE fputc ( ( int ) buff, output ) ;
    }
    return ;
}


/*
    FIND THE LENGTH OF A BITSTREAM

    The length of the bitstream p (in bits) is returned.
*/

long bitstream_length
    PROTO_N ( ( p ) )
    PROTO_T ( bitstream *p )
{
    unsigned n = 0 ;
    for ( ; p ; p = p->next ) n += ( BYTESIZE * p->bytes ) + p->bits ;
    return ( ( long ) n ) ;
}


/*
    JOIN TWO BITSTREAMS

    The bitstream q is appended to p.
*/

void join_bitstreams
    PROTO_N ( ( p, q ) )
    PROTO_T ( bitstream *p X bitstream *q )
{
#if 0
    close_bitstream ( p ) ;
#endif
    p->end->next = q ;
    p->end = q->end ;
    return ;
}


/*
    ADD A NUMBER OF BITS TO THE END OF A BITSTREAM

    n bits of value v are added to the end of the bitstream p.
*/

void enc_bits
    PROTO_N ( ( p, n, v ) )
    PROTO_T ( bitstream *p X int n X long v )
{
    byte *t ;
    bitstream *q = p->end ;
    unsigned m = ( unsigned ) n ;
    unsigned left = BYTESIZE - q->bits ;
    unsigned long w = ( unsigned long ) v ;
    if ( left == 0 ) {
	left = BYTESIZE ;
	q->bits = 0 ;
	q->bytes++ ;
	if ( q->bytes >= q->length ) {
	    q->next = new_bitstream () ;
	    q = q->next ;
	    p->end = q ;
	}
	q->source [ q->bytes ] = 0 ;
    }
    if ( m > left ) {
	enc_bits ( p, ( int ) ( m - left ), ( long ) ( w >> left ) ) ;
	enc_bits ( p, ( int ) left, ( long ) ( w & mask [ left ] ) ) ;
	return ;
    }
    w <<= ( left - m ) ;
    t = q->source + q->bytes ;
    *t = ( byte ) ( *t | ( byte ) w ) ;
    q->bits += m ;
    return ;
}


/*
    ALIGN A BITSTREAM TO A BYTE BOUNDARY

    The bitstream p is aligned to a byte boundary.
*/

void align_bitstream
    PROTO_N ( ( p ) )
    PROTO_T ( bitstream *p )
{
    int bit = ( int ) ( bitstream_length ( p ) % BYTESIZE ) ;
    if ( bit ) enc_bits ( p, BYTESIZE - bit, ( long ) 0 ) ;
    return ;
}
