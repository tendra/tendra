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


#ifndef HASH_INCLUDED
#define HASH_INCLUDED


/*
    TYPE REPRESENTING A HASH TABLE ELEMENT

    A hash table element consists of an object plus a version number.
*/

typedef struct hash_elem_tag {
    object *obj ;
    int vers ;
    struct hash_elem_tag *next ;
} hash_elem ;


/*
    TYPE REPRESENTING A HASH TABLE

    A hash table consists of a name, which is used in error reports,
    and an array of hash elements.
*/

#define hash_size		31

typedef struct {
    char *name ;
    hash_elem *array [ hash_size ] ;
} hash_table ;


/*
    SPECIAL VERSION NUMBERS

    Explicitly stated version numbers are always positive.  These are
    special version numbers for when no version number is given, or
    when a match with any version is permissable.
*/

#define no_version		-1
#define any_version		-2


/*
    PROCEDURE DECLARATIONS

    These routines are concerned with adding and looking up objects in
    hash tables.
*/

extern hash_table *make_hash_table PROTO_S ( ( char * ) ) ;
extern object *add_hash PROTO_S ( ( hash_table *, object *, int ) ) ;
extern object *search_hash PROTO_S ( ( hash_table *, char *, int ) ) ;
extern hash_elem *sort_hash PROTO_S ( ( hash_table * ) ) ;
extern void init_hash PROTO_S ( ( void ) ) ;


/*
    STANDARD HASH TABLES

    These hash tables represent the basic namespaces.
*/

extern hash_table *exps ;
extern hash_table *files ;
extern hash_table *keywords ;
extern hash_table *subsets ;
extern hash_table *tags ;
extern hash_table *tag_fields ;
extern hash_table *tokens ;
extern hash_table *types ;
extern hash_table *type_fields ;


#endif
