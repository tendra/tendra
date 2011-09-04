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

#include <assert.h>
#include <string.h>

#include <shared/xalloc.h>
#include <shared/error.h>

#include "zone.h"
#include "char.h"
#include "instruction.h"
#include "tree.h"	/* XXX */


/*
    FIND A ZONE

    This routine finds a zone within the current zone. This does not include
	searching in parent zones.
*/

static zone * 
find_zone(zone *z, char *name) 
{
	zone *q;

	assert(z != NULL);
	assert(name != NULL);

	for (q = z->next; q != NULL; q = q->opt) {
		if (q->zone_name == NULL) {
			continue;
		}

		if (strcmp(q->zone_name, name) == 0) {
			return q;
		}
	}

	return NULL;
}

/*
	COUNT MAXIMUM TOKEN LENGTH

	Find the maximum token length necessary for a given zone
*/
size_t
zone_maxlength(zone* z, int in_prepass)
{
	size_t max;
	zone *p;

	assert(z != NULL);

	{
		character *pass;

		pass = in_prepass ? z->zone_pre_pass : z->zone_main_pass;
		max  = pass == NULL ? 0 : char_maxlength(pass);
	}

	for (p = z->next; p != NULL; p = p->opt) {
		size_t l;

		l = zone_maxlength(p, in_prepass);
		if (l > max) {
			max = l;
		}
	}

	return max;
}


/*
    ALLOCATE A NEW ZONE

    This routine allocates a new zone.

    TODO: make this private, and provide a add_globalzone() instead.
*/

zone * 
new_zone(lexer_parse_tree *top_level) 
{
	zone *new;

	assert(top_level != NULL);

	new = xmalloc(sizeof *new);
	new->zone_name = NULL;
	new->type = typezone_pure_function; 

	new->zone_main_pass = NULL;
	new->zone_pre_pass  = NULL;

	new->keywords    = NULL;
	new->groups      = NULL;
	new->white_space = NULL;

	new->default_instructions  = NULL;
	new->entering_instructions = NULL;
	new->leaving_instructions  = NULL;

	new->opt  = NULL;
	new->next = NULL;
	new->up   = NULL;

	new->top_level = top_level;

	return new;
}

/*
    ADD A ZONE

    This routine adds a new zone named zid under the current zone z
*/
zone * 
add_zone(zone *z, char *name, const char *e, int endmarkerclosed)
{
	zone *new;
	instruction *inst; 
	instructions_list *inst_list; 

	assert(z != NULL);
	assert(name != NULL);
	assert(e != NULL);

	if (find_zone(z, name)) {
		error(ERROR_SERIOUS, "Zone %s already exists in this scope", name);
		return NULL;
	}

	new = new_zone(z->top_level);
	new->zone_name = name;
	new->opt = z->next;
	z->next = new;
	new->up = z;

	inst = add_instruction_popzone(z, endmarkerclosed);
	inst_list = add_instructions_list();
	*inst_list->tail = inst;
	inst_list->tail = &inst->next;

	add_mainpass(new, e, inst_list);

	return new;
}

character *
add_mainpass(zone *z, const char *s, instructions_list *l)
{
	character *new;

	assert(z != NULL);
	assert(s != NULL);
	assert(l != NULL);

	new = add_string(z, &z->zone_main_pass, s);
	if (new == NULL) {
		return NULL;
	}

	if (new->u.definition != NULL) {
		error(ERROR_SERIOUS, "Token \"%s\" already exists in zone %s", s, zone_name(z));
		return NULL;
	}

	new->u.definition = l;

	return new;
}

character *
add_prepass(zone *z, const char *s, char *m)
{
	character *new;

	assert(z != NULL);
	assert(s != NULL);
	assert(m != NULL);

	new = add_string(z, &z->zone_pre_pass, s);
	assert(new != NULL);

	if (new->u.map != NULL) {
		error(ERROR_SERIOUS, "Mapping \"%s\" already exists in zone %s", s, zone_name(z));
		return NULL;
	}

	new->u.map = m;

	return new;
}

int
zone_isglobal(zone *z)
{
	assert(z != NULL);

	return z == tree_get_globalzone(z->top_level);
}

const char *
zone_name(zone *z)
{
	assert(z != NULL);

	if (z->zone_name == NULL) {
		return "the global zone";
	}

	return z->zone_name;
}

