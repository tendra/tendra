/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


#ifndef HASH_INCLUDED
#define HASH_INCLUDED


/*
 *    TYPE REPRESENTING A HASH TABLE ELEMENT
 *
 *    A hash table element consists of an object plus a version number.
 */

typedef struct hash_elem_tag {
    object *obj;
    int vers;
    struct hash_elem_tag *next;
} hash_elem;


/*
 *    TYPE REPRESENTING A HASH TABLE
 *
 *    A hash table consists of a name, which is used in error reports,
 *    and an array of hash elements.
 */

#define hash_size		31

typedef struct {
    char *name;
    hash_elem *array [ hash_size ];
} hash_table;


/*
 *    SPECIAL VERSION NUMBERS
 *
 *    Explicitly stated version numbers are always positive.  These are
 *    special version numbers for when no version number is given, or
 *    when a match with any version is permissable.
 */

#define no_version		-1
#define any_version		-2


/*
 *    PROCEDURE DECLARATIONS
 *
 *    These routines are concerned with adding and looking up objects in
 *    hash tables.
 */

extern hash_table *make_hash_table(char *) ;
extern object *add_hash(hash_table *, object *, int) ;
extern object *search_hash(hash_table *, char *, int) ;
extern hash_elem *sort_hash(hash_table *) ;
extern void init_hash(void) ;


/*
 *    STANDARD HASH TABLES
 *
 *    These hash tables represent the basic namespaces.
 */

extern hash_table *exps;
extern hash_table *files;
extern hash_table *keywords;
extern hash_table *subsets;
extern hash_table *tags;
extern hash_table *tag_fields;
extern hash_table *tokens;
extern hash_table *types;
extern hash_table *type_fields;


#endif
