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
#include "object.h"
#include "hash.h"
#include "type.h"
#include "utility.h"


/*
    STANDARD HASH TABLES

    These hash tables represent the various namespaces permitted in C
    plus the TDF token namespace.
*/

hash_table *exps ;
hash_table *files ;
hash_table *keywords ;
hash_table *subsets ;
hash_table *tags ;
hash_table *tag_fields ;
hash_table *tokens ;
hash_table *types ;
hash_table *type_fields ;


/*
    INITIALISATION ROUTINE

    This routine initialises the standard hash tables and sets a few
    miscellaneous variables.
*/

void init_hash
    PROTO_Z ()
{
    buffer = alloc_nof ( char, buffsize + 100 ) ;
    exps = make_hash_table ( "Expression" ) ;
    files = make_hash_table ( "Output file" ) ;
    keywords = make_hash_table ( "Keyword" ) ;
    subsets = make_hash_table ( "Set" ) ;
    tags = make_hash_table ( "Tag" ) ;
    tag_fields = make_hash_table ( "Field selector struct/union" ) ;
    tokens = make_hash_table ( "Token" ) ;
    types = make_hash_table ( "Type" ) ;
    type_fields = make_hash_table ( "Field selector" ) ;
    return ;
}


/*
    HASHING ROUTINE

    This routine finds the hash value of the string nm.  This value must
    lie in the range [ 0, hash_size ).
*/

static int hash
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    char *s ;
    int n = 0 ;
    for ( s = nm ; *s ; s++ ) n += *s ;
    return ( n % hash_size ) ;
}


/*
    CREATE A NEW HASH TABLE

    This routine creates a new hash table called nm.
*/

hash_table *make_hash_table
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    int i ;
    hash_table *t = alloc_nof ( hash_table, 1 ) ;
    t->name = nm ;
    for ( i = 0 ; i < hash_size ; i++ ) t->array [i] = null ;
    return ( t ) ;
}


/*
    LOOK UP A NAME IN A HASH TABLE

    This routine looks up the object nm (version v) in the hth column
    of hash table t.  It returns the object if it is found, or null
    otherwise.
*/

static object *lookup_hash
    PROTO_N ( ( t, nm, v, h ) )
    PROTO_T ( hash_table *t X char *nm X int v X int h )
{
    hash_elem *e = t->array [h] ;
    while ( e ) {
	if ( streq ( nm, e->obj->name ) ) {
	    if ( v == e->vers || v == any_version ) return ( e->obj ) ;
	}
	e = e->next ;
    }
    return ( null ) ;
}


/*
    ADD AN OBJECT TO A HASH TABLE

    This routine adds the object p (version v) to the hash table t,
    reporting an error and returning the old value if it is already
    defined.  Otherwise it returns p.
*/

object *add_hash
    PROTO_N ( ( t, p, v ) )
    PROTO_T ( hash_table *t X object *p X int v )
{
    hash_elem *e ;
    char *nm = p->name ;
    int h = hash ( nm ) ;
    object *q = lookup_hash ( t, nm, v, h ) ;
    if ( q != null ) {
	char *fn = q->filename ;
	if ( fn ) {
	    char *err = "%s '%s' already defined (%s, line %d)" ;
	    error ( ERR_SERIOUS, err, t->name, nm, fn, q->line_no ) ;
	} else {
	    error ( ERR_SERIOUS, "%s '%s' already defined", t->name, nm ) ;
	}
	return ( q ) ;
    }
    alloc_variable ( e, hash_elem, 1000 ) ;
    e->obj = p ;
    e->vers = v ;
    e->next = t->array [h] ;
    t->array [h] = e ;
    return ( p ) ;
}


/*
    SEARCH A HASH TABLE FOR AN OBJECT

    This routine searches the hash table t for the object named nm
    (version v), returning it if it is found.  If it is not found then
    null is returned.
*/

object *search_hash
    PROTO_N ( ( t, nm, v ) )
    PROTO_T ( hash_table *t X char *nm X int v )
{
    int h = hash ( nm ) ;
    return ( lookup_hash ( t, nm, v, h ) ) ;
}


/*
    SORT THE ELEMENTS OF A HASH LIST

    This routine sorts the elements of the hash table t into a single
    alphabetical list.  The table cannot be used subsequently.
*/

hash_elem *sort_hash
    PROTO_N ( ( t ) )
    PROTO_T ( hash_table *t )
{
    int i ;
    hash_elem *r = null ;
    for ( i = 0 ; i < hash_size ; i++ ) {
	hash_elem *p = t->array [i]  ;
	while ( p ) {
	    hash_elem *pn = p->next ;
	    hash_elem *q = r, *s = null ;
	    while ( q ) {
		if ( strcmp ( p->obj->name, q->obj->name ) <= 0 ) break ;
		s = q ;
		q = q->next ;
	    }
	    if ( s == null ) {
		p->next = r ;
		r = p ;
	    } else {
		p->next = s->next ;
		s->next = p ;
	    }
	    p = pn ;
	}
    }
    return ( r ) ;
}
