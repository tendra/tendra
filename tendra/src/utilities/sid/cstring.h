/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.ten15.org/>
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


/**** cstring.h --- C string manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 ***=== INTRODUCTION =========================================================
 *
 * This file defines the C string type and specifies some functions that can
 * be used to manipulate C strings.
 *
 ***=== TYPES ================================================================
 *
 ** Type:	CStringP
 ** Repr:	char *
 *
 * This is the C string type.  It should be used for objects that are
 * strings, not for references to character objects.  It is actually defined
 * in the file "os-interface.h" to avoid a circularity in the header files
 * in this directory, but all files outside of this directory should get the
 * type definition by including this file.
 *
 ***=== FUNCTIONS ============================================================
 *
 ** Function:	CStringP		cstring_duplicate
 *			(CStringP cstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified
 * cstring.
 *
 ** Function:	CStringP		cstring_duplicate_prefix
 *			(CStringP cstring, unsigned prefix))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified prefix
 * of the specified cstring.  If the cstring is shorter than the prefix
 * length, then only the cstring is used.
 *
 ** Function:	unsigned		cstring_hash_value
 *			(CStringP cstring))
 ** Exceptions:
 *
 * This function returns the hash value associated with the specified
 * cstring.  This value is guaranteed to be identical for all cstrings
 * with the same content.
 *
 ** Function:	unsigned		cstring_length
 *			(CStringP cstring))
 ** Exceptions:
 *
 * This function returns the length of the specified cstring.
 *
 ** Function:	BoolT			cstring_equal
 *			(CStringP cstring1, CStringP cstring2))
 ** Exceptions:
 *
 * This function returns true if the specified cstrings have the same
 * content, and false otherwise.
 *
 ** Function:	BoolT			cstring_ci_equal
 *			(CStringP cstring1, CStringP cstring2))
 ** Exceptions:
 *
 * This function returns true if the specified cstrings have the same
 * content (ignoring differences in case), and false otherwise.
 *
 ** Function:	BoolT			cstring_to_unsigned
 *			(CStringP cstring, unsigned *num_ref))
 ** Exceptions:
 *
 * This function parses an unsigned number in cstring.  If there is a valid
 * number in the string, it is assigned to the number pointed to by num_ref,
 * and the function returns true; otherwise the function returns false.  The
 * function checks for overflow; it will return false if the number is too
 * big.
 *
 ** Function:	BoolT			cstring_contains
 *			(CStringP cstring, char c))
 ** Exceptions:
 *
 * This function returns true if the specified cstring contains the character
 * c, and false if it doesn't.
 *
 ** Function:	CStringP		cstring_find
 *			(CStringP cstring, char c))
 ** Exceptions:
 *
 * This function returns a pointer to the first occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 *
 ** Function:	CStringP		cstring_find_reverse
 *			(CStringP cstring, char c))
 ** Exceptions:
 *
 * This function returns a pointer to the last occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 */

/****************************************************************************/

#ifndef H_CSTRING
#define H_CSTRING

#include "os-interface.h"
#include "dalloc.h"

/*--------------------------------------------------------------------------*/

CStringP	cstring_duplicate(CStringP);
CStringP	cstring_duplicate_prefix(CStringP, unsigned);
unsigned	cstring_hash_value(CStringP);
unsigned	cstring_length(CStringP);
BoolT		cstring_equal(CStringP, CStringP);
BoolT		cstring_ci_equal(CStringP, CStringP);
BoolT		cstring_to_unsigned(CStringP, unsigned *);
BoolT		cstring_starts(CStringP, CStringP);
BoolT		cstring_contains(CStringP, char);
CStringP	cstring_find(CStringP, char);
CStringP	cstring_find_reverse(CStringP, char);
CStringP	cstring_find_basename(CStringP);

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define cstring_length(s) ((unsigned) strlen (s))
#define cstring_equal(s1, s2) (strcmp ((s1), (s2)) == 0)
#define cstring_contains(s, c) (strchr ((s), (c)) != NIL (CStringP))
#define cstring_find(s, c) (strchr ((s), (c)))
#define cstring_find_reverse(s, c) (strrchr ((s), (c)))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_CSTRING) */
