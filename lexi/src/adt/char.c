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

#include <stddef.h>

#include "xalloc/xalloc.h"
#include "error/error.h"

#include "char.h"

#include "group.h"	/* XXX */
#include "zone.h"	/* XXX */
#include "instruction.h"	/* XXX */
#include "tree.h"	/* XXX */


/*
	COUNT MAXIMUM TOKEN LENGTH

	Find the maximum token length within the given lexical pass.
*/
size_t
char_maxlength(character *c, letter lastlettercode)
{
	character *p;
	size_t maxopt;

	maxopt = 0;
	for(p = c->next; p; p = p->opt) {
		size_t l;

		if(p->ch == lastlettercode) {
			continue;
		}

		l = char_maxlength(p, lastlettercode) + 1;

		if(l > maxopt) {
			maxopt = l;
		}
	}

	return maxopt;
}


/*
    ALLOCATE A NEW CHARACTER

    This routine allocates a new character with value c.
*/

character *
new_char(letter c)
{
    character *p;
	p = xmalloc(sizeof *p);
    p->ch = c;
    p->opt = NULL;
    p->next = NULL;
    p->u.definition = NULL;
    return p;
}


/*
    ADD A CHARACTER

    This routine adds the string s (defined using data) to the lexical
    pass p.
*/

void
add_char(zone* z, character *p, letter *s, instructions_list* instlist, char* map)
{
    character *q;
    letter c = *s;
    if (p->next == NULL) {
	q = new_char(c);
	p->next = q;
    } else {
	character *r = NULL;
	for (q = p->next; q && (q->ch < c); q = q->opt)r = q;
	if (q && q->ch == c) {
	    /* already exists */
	} else {
	    q = new_char(c);
	    if (r == NULL) {
		q->opt = p->next;
		p->next = q;
	    } else {
		q->opt = r->opt;
		r->opt = q;
	    }
	}
    }
    if (c == tree_get_lastlettercode(z->top_level)) {
        if ((instlist && q->u.definition) || (map && q->u.map))
	    error(ERROR_SERIOUS, "TOKEN already defined");
        if(instlist) 
	    q->u.definition=instlist;
        else
	    q->u.map=map;
    }
    else 
      add_char(z, q, s + 1, instlist, map);
    
    return;
}

