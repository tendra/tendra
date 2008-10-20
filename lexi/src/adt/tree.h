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


#ifndef TREE_INCLUDED
#define TREE_INCLUDED

#include "../adt.h"

#include "letter.h"

struct character_tag;


/* 
   THE LEXER PARSE TREE OF THE LXI FILE
*/

typedef struct lexer_parse_tree_tag lexer_parse_tree;


extern lexer_parse_tree *init_lexer_parse_tree(void);
extern int tree_zoneisglobal(lexer_parse_tree *, struct zone_tag *);
extern struct zone_tag *tree_get_globalzone(lexer_parse_tree *);
extern EntryT **tree_get_table(lexer_parse_tree *);
extern letter tree_get_lastlettercode(lexer_parse_tree *t);
extern letter tree_get_eoflettercode(lexer_parse_tree *t);
extern struct char_group_tag *tree_get_grouplist(lexer_parse_tree *t);
extern unsigned int tree_get_totalnogroups(lexer_parse_tree *t);
extern letter_translation *tree_get_translation(lexer_parse_tree *t, struct character_tag *c);
extern letter_translation *tree_get_translationl(lexer_parse_tree *t, letter l);


/*
    ARE ALL GROUPS EMPTY?
*/
extern int all_groups_empty(lexer_parse_tree *t);

/*
   ADD LETTER TRANSLATION TO TABLE
*/
extern void tree_add_translation(lexer_parse_tree *t, letter_translation *trans);

/*
   GET LETTER TRANSLATION FROM TABLE
*/
extern letter_translation *tree_get_lettertranslation(lexer_parse_tree *t, struct character_tag *c);
extern letter_translation *tree_get_translationl(lexer_parse_tree *t, letter l);

extern void tree_add_translation(lexer_parse_tree *t, letter_translation *trans);
extern letter tree_add_generated_key(lexer_parse_tree *t);
extern void tree_add_group(lexer_parse_tree *t, struct char_group_tag *g);

extern void set_predefined_char_lexi_type(struct lexer_parse_tree_tag *, char*, char*);
extern void set_predefined_string_lexi_type(struct lexer_parse_tree_tag *, char*, char*);
extern void set_predefined_int_lexi_type(struct lexer_parse_tree_tag *, char*, char*);
extern void set_predefined_terminal_lexi_type(struct lexer_parse_tree_tag *, char*);

extern EntryT* lexer_char_type(struct lexer_parse_tree_tag *);
extern EntryT* lexer_string_type(struct lexer_parse_tree_tag *);
extern EntryT* lexer_int_type(struct lexer_parse_tree_tag *);
extern EntryT* lexer_terminal_type(struct lexer_parse_tree_tag *);

#endif
