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
 *			PROTO_S ((CStringP cstring))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified
 * cstring.
 *
 ** Function:	CStringP		cstring_duplicate_prefix
 *			PROTO_S ((CStringP cstring, unsigned prefix))
 ** Exceptions:	XX_dalloc_no_memory
 *
 * This function returns a dynamically allocated copy of the specified prefix
 * of the specified cstring.  If the cstring is shorter than the prefix
 * length, then only the cstring is used.
 *
 ** Function:	unsigned		cstring_hash_value
 *			PROTO_S ((CStringP cstring))
 ** Exceptions:
 *
 * This function returns the hash value associated with the specified
 * cstring.  This value is guaranteed to be identical for all cstrings
 * with the same content.
 *
 ** Function:	unsigned		cstring_length
 *			PROTO_S ((CStringP cstring))
 ** Exceptions:
 *
 * This function returns the length of the specified cstring.
 *
 ** Function:	BoolT			cstring_equal
 *			PROTO_S ((CStringP cstring1, CStringP cstring2))
 ** Exceptions:
 *
 * This function returns true if the specified cstrings have the same
 * content, and false otherwise.
 *
 ** Function:	BoolT			cstring_ci_equal
 *			PROTO_S ((CStringP cstring1, CStringP cstring2))
 ** Exceptions:
 *
 * This function returns true if the specified cstrings have the same
 * content (ignoring differences in case), and false otherwise.
 *
 ** Function:	BoolT			cstring_to_unsigned
 *			PROTO_S ((CStringP cstring, unsigned *num_ref))
 ** Exceptions:
 *
 * This function parses an unsigned number in cstring.  If there is a valid
 * number in the string, it is assigned to the number pointed to by num_ref,
 * and the function returns true; otherwise the function returns false.  The
 * function checks for overflow; it will return false if the number is too
 * big.
 *
 ** Function:	BoolT			cstring_contains
 *			PROTO_S ((CStringP cstring, char c))
 ** Exceptions:
 *
 * This function returns true if the specified cstring contains the character
 * c, and false if it doesn't.
 *
 ** Function:	CStringP		cstring_find
 *			PROTO_S ((CStringP cstring, char c))
 ** Exceptions:
 *
 * This function returns a pointer to the first occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 *
 ** Function:	CStringP		cstring_find_reverse
 *			PROTO_S ((CStringP cstring, char c))
 ** Exceptions:
 *
 * This function returns a pointer to the last occurrence of the specified
 * character in the specified cstring, or nil if there is no occurrence.
 *
 **** Change Log:
 * $Log: cstring.h,v $
 * Revision 1.1.1.1  1998/01/17  15:57:17  release
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

extern CStringP			cstring_duplicate
	PROTO_S ((CStringP));
extern CStringP			cstring_duplicate_prefix
	PROTO_S ((CStringP, unsigned));
extern unsigned			cstring_hash_value
	PROTO_S ((CStringP));
extern unsigned			cstring_length
	PROTO_S ((CStringP));
extern BoolT			cstring_equal
	PROTO_S ((CStringP, CStringP));
extern BoolT			cstring_ci_equal
	PROTO_S ((CStringP, CStringP));
extern BoolT			cstring_to_unsigned
	PROTO_S ((CStringP, unsigned *));
extern BoolT			cstring_contains
	PROTO_S ((CStringP, char));
extern CStringP			cstring_find
	PROTO_S ((CStringP, char));
extern CStringP			cstring_find_reverse
	PROTO_S ((CStringP, char));

/*--------------------------------------------------------------------------*/

#ifdef FS_FAST
#define cstring_length(s) ((unsigned) strlen (s))
#define cstring_equal(s1, s2) (strcmp ((s1), (s2)) == 0)
#define cstring_contains(s, c) (strchr ((s), (c)) != NIL (CStringP))
#define cstring_find(s, c) (strchr ((s), (c)))
#define cstring_find_reverse(s, c) (strrchr ((s), (c)))
#endif /* defined (FS_FAST) */

#endif /* !defined (H_CSTRING) */
