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


#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED


/*
    ELEMENTARY TYPES

    A byte is used to represent a single 8-bit number read from the
    input file.  A pointer is a generic pointer.
*/

typedef unsigned char byte ;
#if FS_PTR_VOID
typedef void *pointer ;
#else
typedef char *pointer ;
#endif


/*
    INPUT FILE POSITION

    A place is used to record positions in the input file.  It consists
    of the byte number within the file, the bit number within that byte,
    and an 8-bit input buffer.
*/

typedef struct {
    long byte ;
    int bit ;
    unsigned worksp ;
} place ;


/*
    IDENTIFIER TYPES

    A string is used to represent TDF strings.  A unique is a null-terminated
    array of strings.  An external is either a string or a unique.
*/

typedef char *string ;
typedef string *unique ;

typedef struct {
    char simple ;
    union {
	string str ;
	unique uniq ;
    } val ;
} external ;


/*
    TYPES REPRESENTING SORTS

    Each TDF sort name is represented by an identifying integer.  A sort
    identifier consists of a name and a decode letter.  A foreign sort may
    also have an associated foreign sort name.
*/

typedef int sortname ;

typedef struct {
    char *name ;
    char *fname ;
    char decode ;
    sortname res ;
    char *args ;
} sortid ;


/*
    TYPE REPRESENTING TOKEN INFORMATION

    A token is represented by a structure giving the result sort,
    the argument sorts (if any) in the form of a decode string, and the
    implicit sort (for tokens which are used before they are declared
    or defined).
*/

typedef struct {
    sortname tok_res_sort ;
    char *tok_arg_sorts ;
    sortname tok_implicit_sort ;
} token_info ;


/*
    TYPE REPRESENTING VARIABLE SORTS

    All variable sorts, in particular tags and tokens, are represented
    by the same data structure.  This gives its external name (if any),
    its internal identifying number, plus extra information depending
    on the type of object represented (see below).
*/

typedef struct object_tag {
    int flag ;
    int named ;
    external name ;
    long id ;
    long order ;
    union {
	token_info tok ;
    } extra ;
    struct object_tag *aux ;
} object ;


/*
    TRANSLATIONS FOR TAGS

    These macros give the interpretation for the field of an object
    when that object represents a tag.
*/

#define var( X )		( ( X )->flag )


/*
    TRANSLATIONS FOR TOKENS

    These macros give the interpretation for the field of an object
    when that object represents a token.
*/

#define is_foreign( X )		( ( X )->flag )
#define res_sort( X )		( ( X )->extra.tok.tok_res_sort )
#define arg_sorts( X )		( ( X )->extra.tok.tok_arg_sorts )
#define implicit_sort( X )	( ( X )->extra.tok.tok_implicit_sort )



/*
    TYPE REPRESENTING BINDINGS

    A binding consists of a table of pointers to objects.  A binding table
    is an array of bindings.
*/

typedef struct {
    long max_no ;
    long sz ;
    object **table ;
} binding ;


#endif
