/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef HASH_H
#define HASH_H

#ifndef OBJECT_H
#include "object.h"
#endif

/*
 * TYPE REPRESENTING A HASH TABLE ELEMENT
 *
 * A hash table element consists of an object plus a version number.
 */
typedef struct hash_elem_tag {
	object *obj;
	int vers;
	struct hash_elem_tag *next;
} hash_elem;

/*
 * TYPE REPRESENTING A HASH TABLE
 *
 * A hash table consists of a name, which is used in error reports,
 * and an array of hash elements.
 */

#define hash_size 31

typedef struct {
	char *name;
	hash_elem *array [ hash_size ];
} hash_table;

/*
 * SPECIAL VERSION NUMBERS
 *
 * Explicitly stated version numbers are always positive.  These are
 * special version numbers for when no version number is given, or
 * when a match with any version is permissable.
 */
#define no_version  -1
#define any_version -2

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with adding and looking up objects in
 * hash tables.
 */
hash_table *make_hash_table(char *);
object *add_hash(hash_table *, object *, int);
object *search_hash(hash_table *, char *, int);
hash_elem *sort_hash(hash_table *);
void init_hash(void);

/*
 * STANDARD HASH TABLES
 *
 * These hash tables represent the basic namespaces.
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

