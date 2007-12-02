/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
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


#ifndef TYPES_H
#define TYPES_H


/*
    ELEMENTARY TYPES

    The types boolean, byte and pointer are defined.
*/

typedef char boolean;
typedef unsigned char byte;
typedef void *pointer;


/*
    FORWARD STRUCTURE DECLARATION

    The structure representing a TDF construct is defined recursively.
*/

struct x_construct;


/*
    TYPE REPRESENTING A SORT NAME

    Each TDF construct has an associated sort.  This is represented
    by a value of type sortname.  It can take any of the values of
    the form sort_* in tags.h.
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
    boolean var;
    boolean vis;
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
    boolean dec;
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
