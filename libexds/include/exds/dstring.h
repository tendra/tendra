/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * dstring.h - String manipulation.
 *
 * This file specifies the interface to a string manipulation facility.  There
 * are two types of strings supported: nstrings (strings are stored as a
 * length, and a vector of characters), and dstrings which are only of use
 * when it is necessary to append characters to a string one at a time with
 * reasonable efficiency.
 *
 *
 * Null pointers are not valid as nstrings or dstrings. Passing a null pointer
 * as the argument to a function will have an undefined effect (on many
 * machines the program will abort, but this is not guaranteed).
 */

#ifndef H_DSTRING
#define H_DSTRING

#include <exds/common.h>
#include <exds/ostream.h>


/*
 * This is the nstring type.  These strings may contain null characters.
 * TODO are these private?
 */
typedef struct NStringT NStringT;
struct NStringT {
	size_t length;
	char *contents;
};

/*
 * This is the dstring type.  It is only for appending characters and C
 * strings to.  Once it has been completely initialised, it should be
 * converted to one of the other string types.
 */
typedef struct DStringT DStringT;
struct DStringT {
	size_t length;
	size_t max_length;
	char *contents;
};

/*
 * This function initialises the specified nstring to be an empty nstring.
 */
void
nstring_init(NStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified nstring to be an nstring of the
 * specified length.  The initial contents are unspecified.
 */
void
nstring_init_length(NStringT *, size_t);

/*
 * This function assigns the from nstring to the to nstring.  The from nstring
 * should not be used afterwards, without reinitialising it.
 */
void
nstring_assign(NStringT *, NStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified nstring from the content of the
 * specified cstring.
 */
void
nstring_copy_cstring(NStringT *, const char *);

/*
 * This function inserts the specified cstring into the specified nstring.
 * Sufficient characters are copied to fill up the nstring.
 */
void
nstring_insert_cstring(NStringT *, const char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the specified from nstring into the specified to
 * nstring.
 */
void
nstring_copy(NStringT *, NStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated cstring copy of the specified
 * nstring.  If the nstring contains null characters, then the characters
 * after the first null will be ignored in the cstring (although they will
 * still be part of it).
 */
char *
nstring_to_cstring(NStringT *);

/*
 * This function returns the hash value associated with the specified nstring.
 * This value is guaranteed to be identical for all nstrings with the same
 * content.
 */
unsigned
nstring_hash_value(NStringT *);

/*
 * This function returns the length of the specified nstring.
 */
size_t
nstring_length(NStringT *);

/*
 * This function returns the contents of the specified nstring.
 */
char *
nstring_contents(NStringT *);

/*
 * This function returns ``CMP_LT'', ``CMP_EQ'', or ``CMP_GT'', depending on
 * whether the content of nstring1 is lexicographically less than, equal to,
 * or greater than the content of nstring2.
 */
CmpT
nstring_compare(NStringT *, NStringT *);

/*
 * This function returns true if the specified nstrings have the same content,
 * and false otherwise.
 */
BoolT
nstring_equal(NStringT *, NStringT *);

/*
 * This function returns true if the specified nstrings have the same content
 * (ignoring differences in case), and false otherwise.
 */
BoolT
nstring_ci_equal(NStringT *, NStringT *);

/*
 * This function returns true if the specified nstring contains the specified
 * character, and false otherwise.
 */
BoolT
nstring_contains(NStringT *, char);

/*
 * This function returns true if the second nstring is a prefix of the first
 * nstring, and false otherwise.
 */
BoolT
nstring_is_prefix(NStringT *, NStringT *);

/*
 * This function deallocates the contents of the specified nstring.
 */
void
nstring_destroy(NStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory, XX_ostream_write_error
 *
 * This function writes the content of the specified nstring to the specified
 * ostream.
 */
void
write_nstring(OStreamT *, NStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function initialises the specified dstring to be an empty dstring.
 */
void
dstring_init(DStringT *);

size_t
dstring_length(DStringT *);

/*
 * This function assigns the from dstring to the to dstring.  The from dstring
 * should not be used afterwards, without reinitialising it.
 */
void
dstring_assign(DStringT *, DStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the specified character to the specified dstring.
 */
void
dstring_append_char(DStringT *, char);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the content of the specified cstring to the specified
 * dstring.
 */
void
dstring_append_cstring(DStringT *, const char *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function appends the content of the specified nstring to the specified
 * dstring.
 */
void
dstring_append_nstring(DStringT *, NStringT *);

/*
 * This function returns true if the last character of the specified dstring
 * is the same as the specified character, and false otherwise.  If the
 * dstring is empty, then false is always returned.
 */
BoolT
dstring_last_char_equal(DStringT *, char);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the content of the specified dstring into the
 * specified nstring.
 */
void
dstring_to_nstring(DStringT *, NStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function copies the content of the specified dstring into a
 * dynamically allocated cstring, and returns it.
 */
char *
dstring_to_cstring(DStringT *);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function does the equivalent of a call to ``dstring_to_cstring''
 * followed by a call to ``dstring_destroy''.  It returns a cstring that is
 * normally the internal cstring of the dstring (if there isn't enough room
 * for a null character at the end, then the cstring will need to be
 * reallocated).
 */
char *
dstring_destroy_to_cstring(DStringT *);

/*
 * This function deallocates the contents of the specified dstring.
 */
void
dstring_destroy(DStringT *);

#endif /* !defined (H_DSTRING) */
