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
#include "file.h"
#include "types.h"
#include "utility.h"


/*
    CURRENT FILE POINTER

    As they are read from the input file bits are stored in input_buff.
    The current number of bits in the buffer is bits_in_buff.  bytes_read
    records the position in the input file.
*/

unsigned bits_in_buff = 0 ;
long bytes_read = 0 ;
static unsigned long input_buff = 0 ;


/*
    ALIGN TO NEXT BYTE BOUNDARY

    Any bits remaining in the current byte are ignored.
*/

void byte_align
    PROTO_Z ()
{
    bits_in_buff = 0 ;
    return ;
}


/*
    FETCH A NUMBER OF BITS

    This routine reads the next n bits from the input file and returns
    them as a long.
*/

long fetch
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    unsigned long s ;
    unsigned long r = 0 ;
    unsigned b = ( unsigned ) n ;
    while ( b ) {
	unsigned m ;
	if ( bits_in_buff == 0 ) {
	    int c = getc ( input ) ;
	    bytes_read++ ;
	    if ( c == EOF ) {
		input_error ( "Premature end of file" ) ;
		c = 0xff ;
	    }
	    bits_in_buff = BYTESIZE ;
	    input_buff = ( unsigned long ) ( c & 0xff ) ;
	}
	m = ( b <= bits_in_buff ? b : bits_in_buff ) ;
	s = ( input_buff << m ) ;
	r = ( ( r << m ) | ( ( s >> BYTESIZE ) & 0xff ) ) ;
	b -= m ;
	bits_in_buff -= m ;
	input_buff = ( s & 0xff ) ;
    }
    return ( ( long ) r ) ;
}


/*
    FIND CURRENT POSITION IN FILE

    The current position in the input file (in bits) is returned.
*/

long input_posn
    PROTO_Z ()
{
    return ( BYTESIZE * bytes_read - ( long ) bits_in_buff ) ;
}


/*
    GO TO A POSITION IN FILE

    The position in the input file is set to the nth bit.
*/

void input_goto
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    int b = ( int ) ( n % BYTESIZE ) ;
    bytes_read = ( n / BYTESIZE ) ;
    bits_in_buff = 0 ;
    if ( fseek ( input, bytes_read, SEEK_SET ) ) {
	bits_in_buff = ( unsigned ) b ;
	input_error ( "Illegal seek command" ) ;
	return ;
    }
    if ( b ) IGNORE fetch ( b ) ;
    return ;
}


/*
    SKIP A NUMBER OF BITS

    The next n bits in the input file are ignored.
*/

void input_skip
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    if ( n <= 4 * BYTESIZE ) {
	IGNORE fetch ( ( int ) n ) ;
    } else {
	long m = input_posn () + n ;
	input_goto ( m ) ;
    }
    return ;
}
