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


#ifndef CHECK_INCLUDED
#define CHECK_INCLUDED


/*
    TYPE REPRESENTING A NAME

    A name is represented by a name type plus up to three name components.
    Names may be formed into lists by means of the next field.
*/

typedef struct NAME_tag {
    int type ;
    char *text [3] ;
    CONST char *file ;
    int line ;
    struct NAME_tag *next ;
} NAME ;


/*
    NAME TYPES

    These macros give the various identified name types.
*/

#define NAME_TYPE		0
#define NAME_TYPE_AUX		1
#define NAME_ENUM_CONST		2
#define NAME_STRUCT_CMP		3
#define NAME_UNION_CMP		4
#define NAME_FIELD_CMP		5
#define NAME_MAP		6
#define NAME_MAP_ARG		7
#define NAME_LAST		8


/*
    DECLARATIONS FOR NAME CHECKING ROUTINES
*/

extern void check_names PROTO_S ( ( int ) ) ;


#endif
