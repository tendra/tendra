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

/*
 * cstring.h - C string manipulation.
 *
 * This file defines the C string type and specifies some functions that can
 * be used to manipulate C strings.
 *
 * Here we use char * to as the type for C strings. Origionally this code had
 * an abstraction specifically for strings, to distinguish from character
 * pointers, however this was cumbersome; it has been removed during transition
 * to use standard library functions.
 */

#ifndef H_CSTRING
#define H_CSTRING

#include "os-interface.h"
#include "dalloc.h"

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified
 * string.
 */
extern char *			cstring_duplicate(char *cstring);

/*
 * Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified prefix
 * of the specified string.  If the cstring is shorter than the prefix
 * length, then only the cstring is used.
 */
extern char *			cstring_duplicate_prefix(char *cstring,
	unsigned prefix);

/*
 * This function returns the hash value associated with the specified
 * string.  This value is guaranteed to be identical for all strings
 * with the same content.
 */
extern unsigned			cstring_hash_value(char *cstring);

/*
 * This function returns the length of the specified string.
 */
extern unsigned			cstring_length(char *cstring);

/*
 * This function returns true if the specified cstrings have the same
 * content, and false otherwise.
 */
extern BoolT			cstring_equal(char *cstring1, char *cstring2);

/*
 * This function returns true if the specified cstrings have the same
 * content (ignoring differences in case), and false otherwise.
 */
extern BoolT			cstring_ci_equal(char *cstring1, char *cstring2);

/*
 * This function parses an unsigned number in cstring.  If there is a valid
 * number in the string, it is assigned to the number pointed to by num_ref,
 * and the function returns true; otherwise the function returns false.  The
 * function checks for overflow; it will return false if the number is too
 * big.
 */
extern BoolT			cstring_to_unsigned(char *cstring, unsigned *num_ref);

extern BoolT			cstring_starts(char *cstring, char *s);

/*
 * This function returns true if the specified string contains the character
 * c, and false if it doesn't.
 */
extern BoolT			cstring_contains(char *cstring, char c);

/*
 * This function returns a pointer to the first occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 */
extern char *			cstring_find(char *cstring, char c);

/*
 * This function returns a pointer to the last occurrence of the specified
 * character in the specified cstring, or NULL if there is no occurrence.
 */
extern char *			cstring_find_reverse(char *cstring, char c);

extern char *			cstring_find_basename(char *cstring);

#endif /* !defined (H_CSTRING) */
