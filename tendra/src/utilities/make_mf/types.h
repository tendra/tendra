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
    TYPE DECLARATIONS

    These types need to be declared before they are used.
*/

struct pathname_tag ;
struct dependency_tag ;
struct option_tag ;
struct directory_tag ;


/*
    TYPE REPRESENTING A FILE NAME

    This structure is used to represent a file or directory name.  Each
    such name is broken into components represented by a structure.  Files
    within a directory are listed under the sub field, linked together
    using the next field.  Each file contains a pointer to its parent
    directory in its up field.
*/

typedef struct pathname_tag {
    char *name ;
    char *suffix ;
    char *full ;
    char *quote ;
    char *alias ;
    int mark ;
    int exists ;
    struct dependency_tag *dep ;
    struct pathname_tag *up ;
    struct pathname_tag *sub ;
    struct pathname_tag *next ;
} PATHNAME ;


/*
    TYPE REPRESENTING A DEPENDENCY

    This structure is used to represent a dependency.  The file field gives
    the file depended on and next gives the next dependency in a list.
*/

typedef struct dependency_tag {
    PATHNAME *file ;
    struct dependency_tag *next ;
} DEPENDENCY ;


/*
    TYPE REPRESENTING A LIST OF OPTIONS

    This structure is used to represent a list of command-line options or
    other lists of strings.
*/

typedef struct option_tag {
    char *opt ;
    struct option_tag *next ;
} OPTION ;


/*
    TYPE REPRESENTING A LIST OF DIRECTORIES

    This structure is used to represent a list of directories, such as that
    to be searched in '#include' directives.
*/

typedef struct directory_tag {
    PATHNAME *dir ;
    int builtin ;
    struct directory_tag *next ;
} DIRECTORY ;


#endif
