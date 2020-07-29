/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * key.h - Key ADT.
 *
 * See the file "key.c" for more information.
 */

#ifndef H_KEY
#define H_KEY

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/dstring.h>

typedef enum {
    KT_STRING,
    KT_NUMERIC
} KeyTypeT;

typedef struct KeyT {
    KeyTypeT			type;
    NStringT			string;
    unsigned			number;
} KeyT;

void		key_init_from_string(KeyT *, NStringT *, unsigned);
void		key_init_from_number(KeyT *, unsigned);
CmpT		key_compare(KeyT *, KeyT *);
bool		key_is_string(KeyT *);
NStringT *		key_get_string(KeyT *);
unsigned		key_get_number(KeyT *);
unsigned		key_hash_value(KeyT *);

void		write_key(OStreamT *, KeyT *);

#endif /* !defined (H_KEY) */
