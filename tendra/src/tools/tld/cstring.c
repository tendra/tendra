/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
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


/**** cstring.c --- C string manipulation.
 *
 ** Author: Steve Folkes <smf@hermes.mod.uk>
 *
 **** Commentary:
 *
 * This file implements the C string manipulation facility specified in the
 * file "cstring.h".  See that file for more details.
 *
 **** Change Log:*/

/****************************************************************************/

#include "cstring.h"
#include "syntax.h"

/*--------------------------------------------------------------------------*/

CStringP
cstring_duplicate(CStringP cstring)
{
    unsigned length = cstring_length (cstring);
    CStringP tmp    = ALLOCATE_VECTOR (char, length + 1);
	
    (void) strcpy (tmp, cstring);
    return (tmp);
}

CStringP
cstring_duplicate_prefix(CStringP cstring,
						 unsigned prefix)
{
    unsigned length = cstring_length (cstring);
	
    if (length <= prefix) {
		CStringP tmp = ALLOCATE_VECTOR (char, length + 1);
		
		(void) strcpy (tmp, cstring);
		return (tmp);
    } else {
		CStringP tmp = ALLOCATE_VECTOR (char, prefix + 1);
		
		(void) memcpy ((GenericP) tmp, (GenericP) cstring, (SizeT) prefix);
		tmp [prefix] = '\0';
		return (tmp);
    }
}

unsigned
cstring_hash_value(CStringP cstring)
{
    unsigned value = 0;
	
    while (*cstring) {
		value += ((unsigned) (*cstring ++));
    }
    return (value);
}

#ifdef FS_FAST
#undef cstring_length
#endif /* defined (FS_FAST) */
unsigned
cstring_length(CStringP cstring)
{
    return ((unsigned) strlen (cstring));
}
#ifdef FS_FAST
#define cstring_length(s) ((unsigned) strlen (s))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef cstring_equal
#endif /* defined (FS_FAST) */
BoolT
cstring_equal(CStringP cstring1, CStringP cstring2)
{
    return (strcmp (cstring1, cstring2) == 0);
}
#ifdef FS_FAST
#define cstring_equal(s1, s2) (strcmp ((s1), (s2)) == 0)
#endif /* defined (FS_FAST) */

BoolT
cstring_ci_equal(CStringP cstring1, CStringP cstring2)
{
    char c1;
    char c2;
	
    do {
		c1 = syntax_upcase (*cstring1 ++);
		c2 = syntax_upcase (*cstring2 ++);
    } while ((c1) && (c2) && (c1 == c2));
    return (c1 == c2);
}

BoolT
cstring_to_unsigned(CStringP cstring, unsigned *num_ref)
{
    unsigned number = 0;
	
    if (*cstring == '\0') {
		return (FALSE);
    }
    do {
		int value = syntax_value (*cstring);
		
		if ((value == SYNTAX_NO_VALUE) || (value >= 10) ||
			(((UINT_MAX - (unsigned) value) / (unsigned) 10) < number)) {
			return (FALSE);
		}
		number *= (unsigned) 10;
		number += (unsigned) value;
    } while (*++ cstring);
    *num_ref = number;
    return (TRUE);
}

#ifdef FS_FAST
#undef cstring_contains
#endif /* defined (FS_FAST) */
BoolT
cstring_contains(CStringP cstring, char c)
{
    return (strchr (cstring, c) != NIL (CStringP));
}
#ifdef FS_FAST
#define cstring_contains(s, c) (strchr ((s), (c)) != NIL (CStringP))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef cstring_find
#endif /* defined (FS_FAST) */
CStringP
cstring_find(CStringP cstring, char c)
{
    return (strchr (cstring, c));
}
#ifdef FS_FAST
#define cstring_find(s, c) (strchr ((s), (c)))
#endif /* defined (FS_FAST) */

#ifdef FS_FAST
#undef cstring_find_reverse
#endif /* defined (FS_FAST) */
CStringP
cstring_find_reverse(CStringP cstring, char c)
{
    return (strrchr (cstring, c));
}
#ifdef FS_FAST
#define cstring_find_reverse(s, c) (strrchr ((s), (c)))
#endif /* defined (FS_FAST) */
