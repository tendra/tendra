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
#include "list.h"
#include "utility.h"


/*
    SPARE LISTS

    This is a list of list structures which have been freed using
    free_list.  new_list trys to allocate new list structures from
    this list before using its internal array.
*/

static list *spare_lists = null ;


/*
    CREATE A NEW LIST

    This routine allocates a new list structure.
*/

static list *new_list
    PROTO_Z ()
{
    if ( spare_lists ) {
	list *p = spare_lists ;
	spare_lists = p->next ;
	return ( p ) ;
    } else {
	static int no_free = 0 ;
	static list *free_objs = null ;
	if ( no_free == 0 ) {
	    no_free = 1000 ;
	    free_objs = alloc_nof ( list, no_free ) ;
	}
	return ( free_objs + ( --no_free ) ) ;
    }
}


/*
    FREE A LIST

    This list returns p to free.
*/

void free_list
    PROTO_N ( ( p ) )
    PROTO_T ( list *p )
{
    spare_lists = add_list ( p, spare_lists ) ;
    return ;
}


/*
    JOIN TWO LISTS

    This routine joins two lists, p and q, and returns the result.
*/

list *add_list
    PROTO_N ( ( p, q ) )
    PROTO_T ( list *p X list *q )
{
    list *r ;
    if ( p == null ) return ( q ) ;
    if ( q == null ) return ( p ) ;
    for ( r = p ; r->next != null ; r = r->next ) /* empty */ ;
    r->next = q ;
    return ( p ) ;
}


/*
    ADD AN ITEM TO A LIST

    This routine adds a new item, s, to the end of the list p and returns
    the result.
*/

list *add_item
    PROTO_N ( ( p, s ) )
    PROTO_T ( list *p X char *s )
{
    list *q, *r ;
    q = new_list () ;
    q->item = s ;
    q->next = null ;
    if ( p == null ) return ( q ) ;
    for ( r = p ; r->next != null ; r = r->next ) /* empty */ ;
    r->next = q ;
    return ( p ) ;
}


/*
    INSERT AN ITEM INTO A LIST

    This routine adds a new item, s, to the start of the list p and
    returns the result.
*/

list *insert_item
    PROTO_N ( ( s, p ) )
    PROTO_T ( char *s X list *p )
{
    list *q = new_list () ;
    q->item = s ;
    q->next = p ;
    return ( q ) ;
}


/*
    CONVERT A STRING TO A LIST

    This routine converts a string to a list by breaking it at all white
    spaces (spaces and tabs).
*/

list *make_list
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    list *r = null ;
    char *p = string_copy ( s ) ;
    while ( 1 ) {
	while ( *p == ' ' || *p == '\t' ) *( p++ ) = 0 ;
	if ( *p == 0 ) break ;
	r = add_item ( r, p ) ;
	while ( *p && *p != ' ' && *p != '\t' ) p++ ;
    }
    return ( r ) ;
}
