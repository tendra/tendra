/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef HASH_INCLUDED
#define HASH_INCLUDED


/*
    HASH TABLE DECLARATIONS

    The routines in this module are concerned with the look-up of identifiers
    in the hash table.
*/

extern HASHID lookup_name(string, unsigned long, int, int);
extern HASHID lookup_conv(TYPE);
extern HASHID lookup_constr(TYPE, IDENTIFIER);
extern HASHID lookup_destr(TYPE, IDENTIFIER);
extern HASHID lookup_anon(void);
extern HASHID expand_name(HASHID, CLASS_TYPE);
extern HASHID next_expand_name(HASHID);
extern void prime_name(IDENTIFIER);

extern int find_hashid(HASHID);
extern void init_hash(void);
extern IDENTIFIER underlying_id(IDENTIFIER);
extern void set_hashid_loc(IDENTIFIER, IDENTIFIER);
extern unsigned long hash(string);
extern IDENTIFIER underlying_op;
extern HASHID *hash_ops_table;
extern HASHID hash_keyword[];
extern HASHID *hash_table;


/*
    LOOK UP AN OVERLOADED OPERATOR FUNCTION NAME

    This macro returns the hash table entry for the overloaded operator
    function name corresponding to the lexical token number T.  Note that
    the ISO keywords and digraphs have already been mapped onto their
    primary representations.
*/

#define lookup_op(T)		(hash_ops_table[(T)])


/*
    HASH TABLE SIZES

    These macros give the sizes of various hash tables.
*/

#define HASH_SIZE		((unsigned long)4096)
#define HASH_POWER		((unsigned long)37)
#define HASH_TYPE_SIZE		((unsigned long)256)


/*
    KEYWORD HASH TABLE ENTRIES

    The macro KEYWORD gives a convenient method of accessing the table
    hash_keyword.
*/

#define KEYWORD(T)		(hash_keyword[(T) - lex_auto])
#define EQ_KEYWORD(N, T)	EQ_hashid((N), KEYWORD(T))


#endif
