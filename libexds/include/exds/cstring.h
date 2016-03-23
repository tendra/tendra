/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * cstring.h - C string manipulation.
 *
 * This file defines the C string type and specifies some functions that can
 * be used to manipulate C strings.
 *
 *
 * Here we use char * to as the type for C strings. Origionally this code had
 * an abstraction specifically for strings, to distinguish from character
 * pointers, however this was cumbersome; it has been removed during transition
 * to use standard library functions.
 *
 * The usual functions from string.h (strlen et al) will work for these.
 */

#ifndef H_CSTRING
#define H_CSTRING

#include <exds/common.h>


/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified
 * string.
 */
char *
cstring_duplicate(const char *cstring);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified prefix
 * of the specified string.  If the cstring is shorter than the prefix
 * length, then only the cstring is used.
 */
char *
cstring_duplicate_prefix(const char *cstring, size_t prefix);

/*
 * This function returns the hash value associated with the specified
 * string.  This value is guaranteed to be identical for all strings
 * with the same content.
 */
unsigned
cstring_hash_value(const char *cstring);

/*
 * This function returns true if the specified cstrings have the same
 * content (ignoring differences in case), and false otherwise.
 */
BoolT
cstring_ci_equal(const char *cstring1, const char *cstring2);

/*
 * This function parses an unsigned number in cstring.  If there is a valid
 * number in the string, it is assigned to the number pointed to by num_ref,
 * and the function returns true; otherwise the function returns false.  The
 * function checks for overflow; it will return false if the number is too
 * big.
 */
BoolT
cstring_to_unsigned(const char *cstring, unsigned *num_ref);

BoolT
cstring_starts(const char *cstring, const char *s);

const char *
cstring_find_basename(const char *cstring);

#endif /* !defined (H_CSTRING) */
