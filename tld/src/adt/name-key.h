/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * name-key.h - External name key ADT.
 *
 * See the file "name-key.c" for more information.
 */

#ifndef H_NAME_KEY
#define H_NAME_KEY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/cstring.h>
#include <exds/dstring.h>
#include <exds/ostream.h>

typedef enum {
    KT_STRING,
    KT_UNIQUE
} NameKeyTypeT;

typedef struct NameUniqueT {
    size_t			length;
    NStringT *		components;
} NameUniqueT;

typedef struct NameKeyT {
    NameKeyTypeT		type;
    union {
	NStringT		string;
	NameUniqueT		unique;
    } u;
} NameKeyT;

typedef struct NameKeyListEntryT {
    struct NameKeyListEntryT   *next;
    NameKeyT			key;
} NameKeyListEntryT;

typedef struct NameKeyListT {
    NameKeyListEntryT *	head;
} NameKeyListT;

typedef struct NameKeyPairListEntryT {
    struct NameKeyPairListEntryT *next;
    NameKeyT			  from;
    NameKeyT			  to;
} NameKeyPairListEntryT;

typedef struct NameKeyPairListT {
    NameKeyPairListEntryT *	head;
} NameKeyPairListT;

extern void			name_key_init_string
(NameKeyT *, NStringT *);
extern void			name_key_init_unique
(NameKeyT *, unsigned);
extern BoolT			name_key_parse_cstring
(NameKeyT *, char *);
extern void			name_key_set_component
(NameKeyT *, unsigned, NStringT *);
extern NameKeyTypeT		name_key_type
(NameKeyT *);
extern NStringT *		name_key_string
(NameKeyT *);
extern unsigned			name_key_components
(NameKeyT *);
extern NStringT *		name_key_get_component
(NameKeyT *, unsigned);
extern unsigned			name_key_hash_value
(NameKeyT *);
extern BoolT			name_key_equal
(NameKeyT *, NameKeyT *);
extern void			name_key_assign
(NameKeyT *, NameKeyT *);
extern void			name_key_copy
(NameKeyT *, NameKeyT *);
extern void			name_key_destroy
(NameKeyT *);

extern void			write_name_key
(OStreamT *, NameKeyT *);

extern void			name_key_list_init
(NameKeyListT *);
extern void			name_key_list_add
(NameKeyListT *, NameKeyT *);
extern NameKeyListEntryT *name_key_list_head
(NameKeyListT *);
extern NameKeyT *		name_key_list_entry_key
(NameKeyListEntryT *);
extern NameKeyListEntryT *name_key_list_entry_next
(NameKeyListEntryT *);

extern void			name_key_pair_list_init
(NameKeyPairListT *);
extern BoolT			name_key_pair_list_add
(NameKeyPairListT *, NameKeyT *, NameKeyT *);
extern NameKeyPairListEntryT *name_key_pair_list_head
(NameKeyPairListT *);
extern NameKeyT *		name_key_pair_list_entry_from
(NameKeyPairListEntryT *);
extern NameKeyT *		name_key_pair_list_entry_to
(NameKeyPairListEntryT *);
extern NameKeyPairListEntryT *name_key_pair_list_entry_next
(NameKeyPairListEntryT *);

#endif /* !defined (H_NAME_KEY) */
