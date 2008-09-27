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


#ifndef ZONE_INCLUDED
#define ZONE_INCLUDED

#include <stddef.h>

#include "group.h"

struct keyword_tag;
struct lexer_parse_tree_tag;


/*
    PARAMETERS
*/

#define GROUP_HASH_TABLE_SIZE     128


/* 
   Type of Zones indicate if a zone return terminals or not.

   If a zone never return terminal then it is possible to output 
   a more efficient code.
   
*/

typedef enum zone_type_tag {
    typezone_general_zone, /* A zone that can return more than one terminal */
    typezone_pseudo_token, /* A zone that returns only one terminal on zone exit*/
    typezone_pure_function /* A zone that never returns a terminal */ 
} zone_type;

/*
    TYPE REPRESENTING A ZONE
*/
typedef struct zone_tag zone;
struct zone_tag {
    char* zone_name;
    zone_type type;  

    struct character_tag *zone_pre_pass;
    struct character_tag *zone_main_pass;

    struct keyword_tag *keywords;
    char_group_list groups_hash_table [GROUP_HASH_TABLE_SIZE];  
    char_group* white_space;

    struct instructions_list_tag *default_instructions;

    struct instructions_list_tag* entering_instructions;
    struct instructions_list_tag* leaving_instructions;

    zone *opt; /*opt=brother*/
    zone *next;/* next=first son*/ 
    zone *up; 
    struct lexer_parse_tree_tag *top_level;
};

extern size_t zone_maxlength(zone* z, int in_prepass);
extern zone * new_zone (char* zid, struct lexer_parse_tree_tag *top_level);
extern zone* add_zone(zone*, char*,letter*, int);
extern zone * find_zone (zone*, char*); 

extern unsigned int hash_cstring (char*);
extern unsigned int hash_cstring_n(char*,size_t);

#endif
