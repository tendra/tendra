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
 ** Type:	char *
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
 ** Function:	char *		cstring_duplicate
 *			(char * cstring)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified
 * cstring.
 *
 ** Function:	char *		cstring_duplicate_prefix
 *			(char * cstring, unsigned prefix)
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified prefix
 * of the specified cstring.  If the cstring is shorter than the prefix
 * length, then only the cstring is used.
 *
 ** Function:	unsigned		cstring_hash_value
 *			(char * cstring)
 ** Exceptions:
 *
 * This function returns the hash value associated with the specified
 * cstring.  This value is guaranteed to be identical for all cstrings
 * with the same content.
 *
 ** Function:	unsigned		cstring_length
 *			(char * cstring)
 ** Exceptions:
 *
 * This function returns the length of the specified cstring.
 *
 ** Function:	BoolT			cstring_equal
 *			(char * cstring1, char * cstring2)
 ** Exceptions:
 *
 * This function returns true if the specified cstrings have the same
 * content, and false otherwise.
 *
 ** Function:	BoolT			cstring_ci_equal
 *			(char * cstring1, char * cstring2)
 ** Exceptions:
 *
 * This function returns true if the specified cstrings have the same
 * content (ignoring differences in case), and false otherwise.
 *
 ** Function:	BoolT			cstring_to_unsigned
 *			(char * cstring, unsigned *num_ref)
 ** Exceptions:
 *
 * This function parses an unsigned number in cstring.  If there is a valid
 * number in the string, it is assigned to the number pointed to by num_ref,
 * and the function returns true; otherwise the function returns false.  The
 * function checks for overflow; it will return false if the number is too
 * big.
 *
 ** Function:	BoolT			cstring_contains
 *			(char * cstring, char c)
 ** Exceptions:
 *
 * This function returns true if the specified cstring contains the character
 * c, and false if it doesn't.
 *
 ** Function:	char *		cstring_find
 *			(char * cstring, char c)
 ** Exceptions:
 *
 * This function returns a pointer to the first occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 *
 ** Function:	char *		cstring_find_reverse
 *			(char * cstring, char c)
 ** Exceptions:
 *
 * This function returns a pointer to the last occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 *
 **** Change Log:
 * $Log: cstring.h,v $
 * Revision 1.2  1998/03/16  11:26:34  release
 * Modifications prior to version 4.1.2.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:45  release
 * First version to be checked into rolling release.
 *
 * Revision 1.2  1994/12/12  11:45:26  smf
 * Performing changes for 'CR94_178.sid+tld-update' - bringing in line with
 * OSSG C Coding Standards.
 *
 * Revision 1.1.1.1  1994/07/25  16:06:09  smf
 * Initial import of os-interface shared files.
 *
**/

/****************************************************************************/

#ifndef H_CSTRING
#define H_CSTRING

#include "os-interface.h"
#include "dalloc.h"

/*--------------------------------------------------------------------------*/

extern char *			cstring_duplicate(char *);
extern char *			cstring_duplicate_prefix(char *, unsigned);
extern unsigned			cstring_hash_value(char *);
extern unsigned			cstring_length(char *);
extern BoolT			cstring_equal(char *, char *);
extern BoolT			cstring_ci_equal(char *, char *);
extern BoolT			cstring_to_unsigned(char *, unsigned *);
extern BoolT			cstring_starts(char *, char *);
extern BoolT			cstring_contains(char *, char);
extern char *			cstring_find(char *, char);
extern char *			cstring_find_reverse(char *, char);
extern char *			cstring_find_basename(char *);

#endif /* !defined (H_CSTRING) */
