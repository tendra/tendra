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
#include "high.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    ARRAY OF HIGH LEVEL SORTS

    All high level sorts are held in the table high_sorts.
*/

high_sort *high_sorts = null ;
int crt_high_sort = 0 ;
static int total_high_sort = 0 ;


/*
    ALLOCATE A NEW HIGH LEVEL SORT

    This routine allocates a new high level sort in the table high_sorts
    which is a copy of the local variable q.
*/

high_sort *new_high_sort
    PROTO_N ( ( q ) )
    PROTO_T ( high_sort *q )
{
    int c ;
    high_sort *p ;
    if ( find_high_sort ( q->name ) != SORT_unknown ) {
	is_fatal = 0 ;
	input_error ( "Sort %s already defined", q->name ) ;
    }
    c = crt_high_sort++ ;
    if ( c >= total_high_sort ) {
	total_high_sort += 100 ;
	high_sorts = realloc_nof ( high_sorts, high_sort, total_high_sort ) ;
    }
    p = high_sorts + c ;
    p->name = q->name ;
    p->id = c + high_start ;
    p->res = q->res ;
    p->no_args = q->no_args ;
    p->args = q->args ;
    return ( p ) ;
}


/*
    DEFINE A HIGH-LEVEL SORT FROM TOKEN INFORMATION

    This routine allocates a new high level sort in the table high_sorts
    which has name nm and sort given by the token information tok_info.
*/

void set_high_sort
    PROTO_N ( ( nm, info ) )
    PROTO_T ( char *nm X tok_info *info )
{
    high_sort h ;
    char *q = info->args ;
    h.name = nm ;
    h.res = info->res ;
    if ( q == null ) {
	h.no_args = 0 ;
	h.args = null ;
    } else {
	int i = 0 ;
	h.args = alloc_nof ( sortname, strlen ( q ) ) ;
	while ( *q ) {
	    sortname s ;
	    q = find_sortname ( q, &s ) ;
	    q++ ;
	    h.args [ i++ ] = s ;
	}
	h.no_args = i ;
    }
    IGNORE new_high_sort ( &h ) ;
    return ;
}


/*
    ENSURE THAT HIGH LEVEL SORTS ARE UNIQUELY NUMBERED

    This routine checks that two high level sorts with the same result
    and argument sorts are assigned the same sort number.  Given a
    high level sort h, it returns any equivalent sort.
*/

high_sort *unique_high_sort
    PROTO_N ( ( h ) )
    PROTO_T ( high_sort *h )
{
    int i, j ;
    for ( i = 0 ; i < crt_high_sort ; i++ ) {
	high_sort *p = high_sorts + i ;
	if ( p->res == h->res && p->no_args == h->no_args ) {
	    boolean ok = 1 ;
	    if ( p == h ) return ( h ) ;
	    for ( j = 0 ; j < p->no_args && ok ; j++ ) {
		if ( p->args [j] != h->args [j] ) ok = 0 ;
	    }
	    if ( ok ) {
		h->id = SORT_unknown ;
		return ( p ) ;
	    }
	}
    }
    return ( h ) ;
}


/*
    FIND A HIGH-LEVEL SORT FROM ITS NAME

    This routine searches for a sort named nm, firstly in the built-in
    sorts, then in the high level sort table.  The corresponding sort
    number is returned.
*/

sortname find_high_sort
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    int i ;
    construct *q = search_cons_hash ( nm, SORT_sortname ) ;
    if ( q ) {
	if ( get_char_info ( q ) ) {
	    is_fatal = 0 ;
	    input_error ( "Illegal sort name, %s", nm ) ;
	}
	return ( ( sortname ) q->encoding ) ;
    }
    for ( i = 0 ; i < crt_high_sort ; i++ ) {
	high_sort *p = high_sorts + i ;
	if ( streq ( nm, p->name ) ) return ( p->id ) ;
    }
    return ( SORT_unknown ) ;
}


/*
    FORM A DECODE STRING FOR A HIGH-LEVEL SORT

    This routine forms the decode string corresponding to the arguments
    of the high level sort p.
*/

char *find_decode_string
    PROTO_N ( ( p ) )
    PROTO_T ( high_sort *p )
{
    int i, n = p->no_args ;
    char abuff [100], *a = abuff ;
    if ( n == 0 ) return ( null ) ;
    for ( i = 0 ; i < n ; i++ ) {
	sortname s = p->args [i] ;
	if ( is_high ( s ) ) {
	    sprint_high_sort ( a, s ) ;
	    while ( *a ) a++ ;
	} else {
	    *( a++ ) = sort_letters [s] ;
	}
    }
    *a = 0 ;
    return ( string_copy_aux ( abuff ) ) ;
}


/*
    FIND THE SORTNAME CORRESPONDING TO A DECODE STRING

    This routine finds the sort corresponding to the decode string
    pointed to by p.  This is returned via the pointer q, the procedure
    returning a pointer to the character at the end of the sort encoding.
*/

char *find_sortname
    PROTO_N ( ( p, q ) )
    PROTO_T ( char *p X sortname *q )
{
    int n = 0 ;
    sortname s ;
    if ( *p == 'T' ) {
	while ( *( ++p ) != '#' ) n = 10 * n + ( *p - '0' ) ;
	s = ( sortname ) ( high_start + n ) ;
    } else {
	while ( *p != sort_letters [n] ) n++ ;
	s = ( sortname ) n ;
    }
    if ( q ) *q = s ;
    return ( p ) ;
}
