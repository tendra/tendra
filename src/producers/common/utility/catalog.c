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
#include "c_types.h"
#include "exp_ops.h"
#include "str_ops.h"
#include "error.h"
#include "extra.h"
#include "catalog.h"
#include "option.h"
#include "hash.h"
#include "lex.h"
#include "literal.h"
#include "syntax.h"
#include "ustring.h"
#include "xalloc.h"


/*
    ERROR CATALOGUE

    The error catalogue definition is automatically generated.  It consists
    of an array of ERR_DATA structures, ERR_CATALOG.
*/

#include "errors3.h"


/*
    NUMBER OF ERRORS

    This value gives the number of errors in the error catalogue.
*/

#define CATALOG_SIZE	array_size ( ERR_CATALOG )
unsigned catalog_size = ( unsigned ) CATALOG_SIZE ;


/*
    ERROR NAME HASH TABLE

    This hash table is used to hold the names of the various errors in
    the error catalogue.
*/

typedef struct err_hash_tag {
    int number ;
    ERR_DATA *entry ;
    struct err_hash_tag *next ;
} ERR_HASH ;

#define HASH_ERROR	128
static ERR_HASH *error_hash [ HASH_ERROR + 1 ] ;
static ERR_HASH *all_error_hash = NULL ;


/*
    INITIALISE THE ERROR NAME HASH TABLE

    This routine initialises the error hash table.
*/

static void init_err_hash
    PROTO_Z ()
{
    int i ;
    ERR_DATA *cat = ERR_CATALOG ;
    ERR_HASH *err = xmalloc_nof ( ERR_HASH, CATALOG_SIZE ) ;
    all_error_hash = err ;
    for ( i = 0 ; i <= HASH_ERROR ; i++ ) error_hash [i] = NULL ;
    for ( i = 0 ; i < CATALOG_SIZE ; i++ ) {
	unsigned long h ;
	CONST char *s = cat->name ;
	if ( s ) {
	    h = hash ( ustrlit ( s ) ) ;
	    h %= HASH_ERROR ;
	} else {
	    h = HASH_ERROR ;
	}
	err->number = i ;
	err->entry = cat ;
	err->next = error_hash [h] ;
	error_hash [h] = err ;
	cat++ ;
	err++ ;
    }
    return ;
}


/*
    FIND AN ERROR NUMBER

    This routine finds the error number corresponding to the string literal
    expression s.  n gives a likely value to try first.  It returns -1 if
    s is not the name of a known error.
*/

int find_error_no
    PROTO_N ( ( s, n ) )
    PROTO_T ( STRING s X int n )
{
    unsigned kind = DEREF_unsigned ( str_simple_kind ( s ) ) ;
    if ( kind == STRING_NONE ) {
	ERR_HASH *err ;
	unsigned long h ;
	string text = DEREF_string ( str_simple_text ( s ) ) ;
	ulong len = DEREF_ulong ( str_simple_len ( s ) ) ;
	if ( n >= 0 && n < CATALOG_SIZE ) {
	    string nm = ustrlit ( ERR_CATALOG [n].name ) ;
	    if ( nm && ustreq ( text, nm ) ) {
		if ( len == ( ulong ) ustrlen ( nm ) ) return ( n ) ;
	    }
	}
	if ( all_error_hash == NULL ) init_err_hash () ;
	h = hash ( text ) ;
	h %= HASH_ERROR ;
	for ( err = error_hash [h] ; err != NULL ; err = err->next ) {
	    string nm = ustrlit ( err->entry->name ) ;
	    if ( nm && ustreq ( text, nm ) ) {
		if ( len == ( ulong ) ustrlen ( nm ) ) {
		    return ( err->number ) ;
		}
	    }
	}
    }
    return ( -1 ) ;
}


/*
    SET AN ERROR SEVERITY LEVEL

    This routine sets the severity level of error number n to the error
    severity corresponding to the option number opt.
*/

void set_error_sev
    PROTO_N ( ( n, opt ) )
    PROTO_T ( int n X int opt )
{
    if ( n >= 0 && n < CATALOG_SIZE ) {
	ERR_CATALOG [n].usage = opt ;
    }
    return ;
}


/*
    LOOK UP A LANGUAGE DEPENDENT TERM

    Certain technical terms vary slightly between C and C++.  This routine
    looks up the term corresponding to the lexical token number t in the
    current language.  The default is the normal lexical token name.
*/

string find_vocab
    PROTO_N ( ( t ) )
    PROTO_T ( int t )
{
    CONST char *s = token_names [t] ;
#if LANGUAGE_C
    switch ( t ) {
	case lex_class : s = "struct/union" ; break ;
    }
#endif
    return ( ustrlit ( s ) ) ;
}


/*
    INITIALISE THE ERROR CATALOGUE

    This routine initialises the error catalogue.
*/

void init_catalog
    PROTO_Z ()
{
    ASSERT ( OPT_error == 0 ) ;
    return ;
}


/*
    TERMINATE THE ERROR CATALOGUE

    This routine terminates the error catalogue.
*/

void term_catalog
    PROTO_Z ()
{
    xfree_nof ( all_error_hash ) ;
    all_error_hash = NULL ;
    return ;
}
