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
#include "enc_nos.h"
#include "errors.h"
#include "readstreams.h"
#include "decodings.h"
@use all
@loop sort
@if sort.basic


/* DECODE %ST */

unsigned int d_%SN
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    unsigned int enc = get_basic_int ( %SB, %SE ) ;
    switch ( enc ) {
@loop sort.cons
	case e_%CN : {
	    consname ( "%CN", n ) ;
@loop cons.param
@if param.sort.eq.bitstream
	    IGNORE d_bitstream ( "%CN", n + 1 ) ;
@else
	    IGNORE d_%PSN ( n + 1 ) ;
@endif
@end
	    break ;
	}
@end
	default : {
	    fail ( "Bad %SN value, %u", enc ) ;
	    break ;
	}
    }
    return ( enc ) ;
}
@else
@if sort.dummy


/* DECODE %ST */

unsigned int d_%SN
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
@loop sort.cons
    consname ( "%CN", n ) ;
@loop cons.param
@if param.sort.eq.bitstream
    IGNORE d_bitstream ( "%CN", n + 1 ) ;
@else
    IGNORE d_%PSN ( n + 1 ) ;
@endif
@end
    return ( %CE ) ;
@end
}
@else
@if sort.option


/* DECODE OPTIONAL %SST */

unsigned int d_%SN
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    unsigned int nl = get_basic_int ( 1, 0 ) ;
    if ( nl ) IGNORE d_%SSN ( n ) ;
    return ( nl ) ;
}
@else
@if sort.slist


/* DECODE SIMPLE %SST LIST */

unsigned int d_%SN
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    unsigned int nl = get_tdfint () ;
    for ( ; nl != 0 ; nl-- ) IGNORE d_%SSN ( n + 1 ) ;
    return ( nl ) ;
}
@else
@if sort.list


/* DECODE %SST LIST */

unsigned int d_%SN
    PROTO_N ( ( n ) )
    PROTO_T ( int n )
{
    unsigned int nl ;
    IGNORE get_basic_int ( 1, 0 ) ;
    nl = get_tdfint () ;
    for ( ; nl != 0 ; nl-- ) IGNORE d_%SSN ( n + 1 ) ;
    return ( nl ) ;
}
@endif
@endif
@endif
@endif
@endif
@end
