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
#include "help.h"
#include "high.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    HASHING FUNCTION

    This routine is used to construct the hash tables.  It takes a
    string s and returns a value in the range 0 <= n < hash_size.
*/

static int hash
    PROTO_N ( ( s ) )
    PROTO_T ( char *s )
{
    int n = 0 ;
    for ( ; *s ; s++ ) n += *s ;
    return ( n % hash_size ) ;
}


/*
    CONSTRUCT TABLES

    There are a number of tables of constructs.  cons_table is the
    table of all built-in constructs (arranged by sort and encoding),
    and var_table of all user defined constructs.  The tables
    cons_hash_tables and var_hash_tables give the corresponding
    hash tables (arranged by sort).  The table cons_sizes gives
    the number of built-in constructs of each sort.
*/

construct **var_table ;
construct **cons_table ;
static int *cons_sizes ;
construct **cons_hash_tables ;
static construct **var_hash_tables ;


/*
    SORT INFORMATION TABLES

    These tables give information on the various sorts, namely, the
    number of them created, their decode letters, the number of bits
    in their encoding, the encoding of their "apply_token" construct,
    and the number of them removed from the hash tables.
*/

long *sort_count ;
char *sort_letters ;
int *sort_encoding ;
int *sort_extension ;
long *sort_tokens ;
long *sort_conds ;
long *sort_removed ;
decode_func *sort_decode ;
read_func *sort_read ;


/*
    CREATE A TABLE FOR A NEW SORT

    A table of sz constructs of sort s is created and cleared.
*/

void new_sort
    PROTO_N ( ( s, sz ) ) 
    PROTO_T ( sortname s X int sz )
{
    int i ;
    construct *p = alloc_nof ( construct, sz ) ;
    for ( i = 0 ; i < sz ; i++ ) {
	( p + i )->sortnum = s ;
	( p + i )->encoding = i ;
	( p + i )->name = null ;
	( p + i )->next = null ;
	get_char_info ( p + i ) = null ;
    }
    cons_table [s] = p ;
    cons_sizes [s] = ( int ) sz ;
    return ;
}


/*
    PUT A NAME INTO A CONSTRUCT

    The nth construct of sort s is set to have name nm and argument
    string args.
*/

void new_cons
    PROTO_N ( ( nm, s, n, args ) )
    PROTO_T ( char *nm X sortname s X int n X char *args )
{
    construct *p = cons_no ( s, n ) ;
    p->name = nm ;
    if ( add_to_cons_hash ( p, s ) ) {
	fatal_error ( "Construct %s already defined", nm ) ;
    }
    get_char_info ( p ) = args ;
    return ;
}


/*
    DUMMY DECODING FUNCTION

    This routine is a dummy which is used for uninitialised decode functions.
*/

static node *de_dummy
    PROTO_Z ()
{
    fatal_error ( "Invalid decode function" ) ;
    return ( null ) ;
}


/*
    DUMMY READING FUNCTION

    This routine is a dummy which is used for uninitialised read functions.
*/

static node *read_dummy
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    fatal_error ( "Invalid read function" ) ;
    UNUSED ( n ) ;
    return ( null ) ;
}


/*
    INITIALIZE CONSTRUCT TABLES

    The various construct and sort tables are initialized.
*/

void init_tables
    PROTO_Z ()
{
    int i ;

    /* Allocate tables */
    cons_table = alloc_nof ( construct *, SORT_no ) ;
    cons_sizes = alloc_nof ( int, SORT_no ) ;
    cons_hash_tables = alloc_nof ( construct *, SORT_no * hash_size ) ;
    var_table = alloc_nof ( construct *, SORT_no ) ;
    var_hash_tables = alloc_nof ( construct *, SORT_no * hash_size ) ;
    sort_count = alloc_nof ( long, SORT_no ) ;
    sort_letters = alloc_nof ( char, SORT_no + 1 ) ;
    sort_encoding = alloc_nof ( int, SORT_no ) ;
    sort_extension = alloc_nof ( int, SORT_no ) ;
    sort_tokens = alloc_nof ( long, SORT_no ) ;
    sort_conds = alloc_nof ( long, SORT_no ) ;
    sort_removed = alloc_nof ( long, SORT_no ) ;
    sort_decode = alloc_nof ( decode_func, SORT_no ) ;
    sort_read = alloc_nof ( read_func, SORT_no ) ;

    /* Clear out tables */
    for ( i = 0 ; i < SORT_no ; i++ ) {
	cons_table [i] = null ;
	cons_sizes [i] = 0 ;
	var_table [i] = null ;
	sort_count [i] = 0 ;
	sort_letters [i] = 'F' ;
	sort_encoding [i] = 0 ;
	sort_extension [i] = 0 ;
	sort_tokens [i] = -2 ;
	sort_conds [i] = -2 ;
	sort_removed [i] = 0 ;
	sort_decode [i] = de_dummy ;
	sort_read [i] = read_dummy ;
    }
    sort_letters [ SORT_no ] = 0 ;

    /* Initialize construct hash tables */
    for ( i = 0 ; i < SORT_no * hash_size ; i++ ) {
	cons_hash_tables [i] = null ;
	var_hash_tables [i] = null ;
    }
    return ;
}


/*
    SPECIAL CONSTRUCTS

    These constructs are predefined.
*/

construct bytestream_cons = { SORT_bytestream, 0, null, null, null } ;
construct false_cons = { SORT_tdfbool, 0, null, null, null } ;
construct optional_cons = { SORT_option, 0, null, null, null } ;
construct string_cons = { SORT_tdfstring, -1, null, null, null } ;
construct token_cons = { SORT_token, 0, null, null, null } ;
construct true_cons = { SORT_tdfbool, 1, null, null, null } ;
construct unknown_cons = { SORT_unknown, 0, "....", null, null } ;
construct exp_shape = { SORT_exp, 0, "~exp_with_shape", null, null } ;
construct shape_of = { SORT_shape, -1, "~shape_of", null, null } ;


/*
    OUTPUT OPTIONS

    These flags give information on the form of the output.
*/

boolean show_tokdecs = 1 ;
boolean show_tokdefs = 1 ;
boolean show_aldecs = 1 ;
boolean show_aldefs = 1 ;
boolean show_tagdecs = 1 ;
boolean show_tagdefs = 1 ;


/*
    FIND THE NAME OF A GIVEN SORT

    Given the sort s, this routine returns the name of s.
*/

char *sort_name
    PROTO_N ( ( s ) )
    PROTO_T ( sortname s )
{
    if ( is_high ( s ) ) {
	high_sort *h = high_sorts + high_no ( s ) ;
	return ( h->name ) ;
    } else if ( s == SORT_unknown || s < 0 ) {
	return ( "...." ) ;
    } else {
	construct *p = cons_no ( SORT_sortname, s ) ;
	return ( p->name ) ;
    }
}


/*
    ADD A NAME TO A CONSTRUCT HASH TABLE

    The construct p of sort s is added to the built-in construct hash
    table.  The routine returns a pointer to any existing entry of
    the same name, or null otherwise.
*/

construct *add_to_cons_hash
    PROTO_N ( ( p, s ) )
    PROTO_T ( construct *p X sortname s )
{
    construct *q ;
    int n = hash ( p->name ) ;
    construct *h = cons_hash_tables [ hash_size * s + n ] ;
    for ( q = h ; q != null ; q = q->next ) {
	if ( streq ( p->name, q->name ) ) return ( q ) ;
    }
    p->next = h ;
    cons_hash_tables [ hash_size * s + n ] = p ;
    return ( null ) ;
}


/*
    LOOK UP A NAME IN A CONSTRUCT HASH TABLE

    A construct with name p and sort s is looked up in the built-in
    construct hash table.  The routine returns a pointer to the
    construct if it is found, or null otherwise.
*/

construct *search_cons_hash
    PROTO_N ( ( p, s ) )
    PROTO_T ( char *p X sortname s )
{
    construct *q ;
    int n = hash ( p ) ;
    construct *h = cons_hash_tables [ hash_size * s + n ] ;
    for ( q = h ; q != null ; q = q->next ) {
	if ( streq ( p, q->name ) ) return ( q ) ;
    }
    return ( null ) ;
}


/*
    ADD A NAME TO A VARIABLE HASH TABLE

    The construct p of sort s is added to the user-defined construct
    hash table.  The routine returns a pointer to any existing entry
    of the same name, or null otherwise.
*/

construct *add_to_var_hash
    PROTO_N ( ( p, s ) )
    PROTO_T ( construct *p X sortname s )
{
    construct *q ;
    int n = hash ( p->name ) ;
    construct *h = var_hash_tables [ hash_size * s + n ] ;
    for ( q = h ; q != null ; q = q->next ) {
	if ( streq ( p->name, q->name ) ) return ( q ) ;
    }
    p->next = h ;
    var_hash_tables [ hash_size * s + n ] = p ;
    return ( null ) ;
}


/*
    LOOK UP A NAME IN A VARIABLE HASH TABLE

    A construct with name p and sort s is looked up in the user-defined
    construct hash table.  The routine returns a pointer to the construct
    if it is found, or null otherwise.
*/

construct *search_var_hash
    PROTO_N ( ( p, s ) )
    PROTO_T ( char *p X sortname s )
{
    construct *q ;
    int n = hash ( p ) ;
    construct *h = var_hash_tables [ hash_size * s + n ] ;
    for ( q = h ; q != null ; q = q->next ) {
	if ( streq ( p, q->name ) ) return ( q ) ;
    }
    return ( null ) ;
}


/*
    LIST OF ALL REMOVED CONSTRUCTS

    All constructs removed from the user-defined construct hash table
    are formed into a list.  This is used in node.c to form the
    completion of a node.
*/

construct *removals = null ;


/*
    REMOVE A NAME FROM A VARIABLE HASH TABLE

    The construct with name p and sort s is removed from the
    user-defined hash table and added to the removals list.  There
    is no error if the construct does not exist.
*/

void remove_var_hash
    PROTO_N ( ( p, s ) )
    PROTO_T ( char *p X sortname s )
{
    int n = hash ( p ) ;
    construct *h = var_hash_tables [ hash_size * s + n ] ;
    if ( h == null ) return ;
    if ( streq ( p, h->name ) ) {
	/* It is the first element */
	var_hash_tables [ hash_size * s + n ] = h->next ;
	h->next = removals ;
	removals = h ;
	( sort_removed [s] )++ ;
	return ;
    }
    while ( h->next ) {
	if ( streq ( p, h->next->name ) ) {
	    /* It is a subsequent element */
	    construct *q = h->next->next ;
	    h->next->next = removals ;
	    removals = h->next ;
	    h->next = q ;
	    ( sort_removed [s] )++ ;
	    return ;
	}
	h = h->next ;
    }
    /* Not found */
    return ;
}


/*
    SORT A HASH TABLE

    The constructs of sort s in the hash table tab are sorted into
    alphabetical order.  They are formed into a list where the
    constructs with hash value 0 should be.  After sorting the hash
    table cannot be used.
*/

void sort_table
    PROTO_N ( ( tab, s ) )
    PROTO_T ( construct **tab X sortname s )
{
    int i ;
    construct *q = null ;
    for ( i = 0 ; i < hash_size ; i++ ) {
	construct *p = tab [ hash_size * s + i ] ;
	tab [ hash_size * s + i ] = null ;
	while ( p ) {
	    construct *p_next = p->next ;
	    construct *r_last = null, *r = q ;
	    p->next = null ;
	    while ( r && strcmp ( r->name, p->name ) < 0 ) {
		r_last = r ;
		r = r->next ;
	    }
	    if ( r_last == null ) {
		p->next = q ;
		q = p ;
	    } else {
		r_last->next = p ;
		p->next = r ;
	    }
	    p = p_next ;
	}
    }
    tab [ hash_size * s ] = q ;
    return ;
}


/*
    FLAG

    This flag may be set to false to prevent sort_all sorting its
    tables.
*/

boolean order_names = 1 ;


/*
    SORTING ROUTINE

    The user-defined alignment tags, tags and tokens are sorted into
    alphabetical order.
*/

void sort_all
    PROTO_Z ()
{
    if ( order_names ) {
	sort_table ( var_hash_tables, SORT_al_tag ) ;
	sort_table ( var_hash_tables, SORT_tag ) ;
	sort_table ( var_hash_tables, SORT_token ) ;
    }
    return ;
}


/*
    APPLY A PROCEDURE TO ALL CONSTRUCTS

    The routine f is applied to all user-defined constructs of sort s
    by scanning across the hash table.
*/

void apply_to_all
    PROTO_N ( ( f, s ) )
    PROTO_T ( apply_func f X sortname s )
{
    int i ;
    for ( i = 0 ; i < hash_size ; i++ ) {
	construct *p = var_hash_tables [ hash_size * s + i ] ;
	while ( p ) {
	    construct *q = p->next ;
	    ( *f ) ( p ) ;
	    p = q ;
	}
    }
    return ;
}
