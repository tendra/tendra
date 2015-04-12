/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef TYPES_H
#define TYPES_H


typedef unsigned char byte;


/*
    FORWARD STRUCTURE DECLARATION

    The structure representing a TDF construct is defined recursively.
*/

struct x_construct;


/*
    TYPE REPRESENTING A SORT NAME

    Each TDF construct has an associated sort.  This is represented
    by a value of type sortname.  It can take any of the values of
    the form sort_* in tdf.h.
*/

typedef int sortname;


/*
    TYPE REPRESENTING A TREE NODE

    TDF is represented as a tree structure.  Each node has a corresponding
    construct given by the cons field.  The son and bro fields give the
    tree its structure.  For shape checking there is also a shape field
    which is itself a node.
*/

typedef struct x_node {
	struct x_construct *cons;
	struct x_node *son;
	struct x_node *bro;
	struct x_node *shape;
} node;


/*
    TYPE REPRESENTING AN ALIGNMENT TAG

    The only information required about an alignment tag is its
    definition (if any).
*/

typedef struct x_al_tag_info {
	node *def;
} al_tag_info;


/*
    TYPE REPRESENTING A TAG

    A tag may be a variable or identity (indicated by the var field).
    It may also be declared and defined.  The vis field is used to
    try to catch variables declared with visible access.
*/

typedef struct x_tag_info {
	int var;
	bool vis;
	node *dec;
	node *def;
} tag_info;


/*
    TYPE REPRESENTING A TOKEN

    A token may be declared or defined.  Its result sort is represented
    by the res field, and its argument sorts by the args field.  The
    formal parameters for a defined token are given as an array of
    constructs by the pars field.
*/

typedef struct x_tok_info {
	bool dec;
	sortname res;
	char *args;
	node *sig;
	node *def;
	int depth;
	struct x_construct **pars;
} tok_info;


/*
    TYPE REPRESENTING A TDF CONSTRUCT

    A TDF construct (including user defined tokens and tags as well
    as the base constructs) is represented by the type construct.
    This consists of its sort, sortnum, its encoding, its internal
    and external names, plus space for extra information depending
    on its sort.  The next field enables us to form constructs into
    lists.
*/

typedef struct x_construct {
	sortname sortnum;
	long encoding;
	char *name;
	node *ename;
	struct x_construct *alias;
	struct x_construct *next;
	union {
		char *char_u;
		al_tag_info al_tag_u;
		tag_info tag_u;
		tok_info tok_u;
	} u;
} construct;


/*
    MACROS FOR ACCESSING INFO FIELDS OF A CONSTRUCT

    The following macros access the various field of the extra
    information union of a construct.  These macros should always
    be used - the fields should not be addressed directly.
*/

#define get_char_info(X)	((X) ->u.char_u)
#define get_al_tag_info(X)	(&((X) ->u.al_tag_u))
#define get_tag_info(X)		(&((X) ->u.tag_u))
#define get_tok_info(X)		(&((X) ->u.tok_u))


/*
    TYPE REPRESENTING A DIRECTORY

    In order to search for included files, the directory structure
    enables us to form lists of directory names.
*/

typedef struct x_directory {
	char *dirname;
	struct x_directory *next;
} directory;


#endif /* TYPES_H */
