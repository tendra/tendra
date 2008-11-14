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


#ifndef GROUP_INCLUDED
#define GROUP_INCLUDED

struct zone_tag;


/*
    TYPE REPRESENTING A CHARACTER GROUP

    A character group is a named unordered set of letters.
*/

typedef struct char_group_name_tag char_group_name;
typedef struct char_group_defn_tag char_group_defn;


struct char_group_defn_tag {
	/*
	 * The set of characters present in a group, expressed as a bitmap. Each
	 * element is true if the index is a character in the group, and false
	 * otherwise. Since EOF is not a character, it may not be present in groups.
	 */
	int defn[256];

	/*
	 * Groups definition are maintained in a global list. This is
	 * used for numbering group definitions at output.
	 */
	char_group_defn *next_in_groups_list;
};


struct char_group_name_tag {
	char *name;

	/*
	 * The zone within which this group is defined.
	 */
	struct zone_tag *z;

	/*
	 * A pointer to the group definition. Several groups can point to the same definition.
	 */

	char_group_defn* def;
	/*
	 * char_group_name elements appear in a list of group within one zone in the tree of zones
	 */
	char_group_name *next;
};


extern char_group_name *make_group(struct zone_tag *, char *, char *);
extern int in_group(char_group_defn *, char);
extern int is_group_empty(char_group_defn *);
extern int is_group_equal(char_group_defn *a, char_group_defn *b);
extern char_group_name *find_group(const struct zone_tag *z, const char *name);

#endif
