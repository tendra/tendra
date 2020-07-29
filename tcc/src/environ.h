/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef ENVIRON_H
#define ENVIRON_H

#include "utility.h"
#include "hash.h"

/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with reading tcc environments.
 */

extern void	read_env(const char *);


#define TCC_TBLSIZE 119
#define TCC_KEYSIZE  27

extern struct hash *envvars;	/* global set of env keys/values */


/*
 * CHARACTER TYPES
 *
 * These macros identify various character types.
 */
/* XXX: use ctype.h instead */
#define is_alphanum(X)		(((X) >= 'A' && (X) <= 'Z') ||\
				 ((X) >= '0' && (X) <= '9') ||\
				 ((X) == '_'))
#define is_whitespace(X)	((X) == ' ' || (X) == '\t')
#define is_newline(X)		((X) == '\n')


#endif /* ENVIRON_H */
