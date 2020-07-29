/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef HASH_H
#define HASH_H

#include <stddef.h>


/*
 * Hash implementation
 */

/* TODO: explain */
enum hash_precedence {
	HASH_DEFAULT = 0,
	HASH_SYSENV  = 1,
	HASH_TCCENV  = 2,
	HASH_CLI     = 3
};

enum hash_order {
	HASH_ASSIGN  = '+',
	HASH_APPEND  = '>',
	HASH_PREPEND = '<'
};

struct hash;


extern void reconcile_envopts(const struct hash *);
extern void dump_env(const struct hash *);
void
envvar_set(struct hash **, const char *, const char *,
	enum hash_order, enum hash_precedence);
extern const char *
envvar_get(struct hash *h, const char *name);

extern int
envvar_hash(const char *, size_t, size_t);



#endif /* HASH_H */
