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

#include <string.h>

#include "xalloc/xalloc.h"
#include "error/error.h"

#include "letter.h"
#include "zone.h"
#include "char.h"
#include "instruction.h"
#include "tree.h"	/* XXX */


/*
	COUNT MAXIMUM TOKEN LENGTH

	Find the maximum token length necessary for a given zone
*/
size_t
zone_maxlength(zone* z, int in_prepass)
{
	zone *p;
	size_t maxopt;

	if(in_prepass)
		maxopt = char_maxlength(z->zone_pre_pass,  z->top_level->last_letter_code) ;
	else
		maxopt = char_maxlength(z->zone_main_pass,  z->top_level->last_letter_code) ;
	for (p = z->next ; p; p = p->opt) {
		size_t k = zone_maxlength(p, in_prepass);
		maxopt = k > maxopt ? k : maxopt ; 
	}
	return maxopt;
}


/*
    ALLOCATE A NEW ZONE

    This routine allocates a new zone
*/

zone * 
new_zone (char* zid, lexer_parse_tree* top_level) 
{
    zone *p;
    int i;
    static int zones_left = 0;
    static zone *zones_free = NULL;
    if (zones_left == 0) {
	zones_left = 100;
	zones_free = xmalloc_nof(zone, zones_left);
    }
    p = zones_free + (--zones_left);
    p->zone_name=zid;
    p->zone_main_pass=new_char(top_level->last_letter_code);
    p->zone_pre_pass=new_char(top_level->last_letter_code);

    p->keywords=NULL;

    for(i=0; i<GROUP_HASH_TABLE_SIZE;i++) {
        p->groups_hash_table[i].head=NULL;
        p->groups_hash_table[i].tail=&(p->groups_hash_table[i].head);
    }
    p->white_space=NULL;

    p->type=typezone_pure_function; 

    p->default_instructions=NULL;

    p->entering_instructions=NULL;
    p->leaving_instructions=NULL;

    p->opt=NULL;
    p->next=NULL;
    p->up=NULL;
    p->top_level=top_level;
    return p;
}

/*
    FIND A  ZONE

    This routine finds a zone under the current one

*/

zone * 
find_zone (zone* z, char* zid) 
{
    zone* q;
    for(q=z->next; q!=NULL ; q=q->opt) {
        if(strcmp(q->zone_name,zid)==0)
	    break;
    }
    return q;
    }

/*
    ADD A ZONE

    This routine adds a new zone named zid under the current zone z
*/
zone* 
add_zone(zone* current_zone, char* zid, letter* e, int endmarkerclosed)
{
  zone* q;
  instruction* inst; 
  instructions_list* inst_list; 
  for(q=current_zone->next; q!=NULL; q=q->opt) {
    if(strcmp(q->zone_name,zid)==0) {
      error(ERROR_SERIOUS, "Zone %s already exists in this scope",zid);
      return NULL;
    }
  }

  q=new_zone(zid,current_zone->top_level);
  q->opt=current_zone->next;
  current_zone->next=q;
  q->up=current_zone;

  inst = add_instruction_popzone(current_zone, endmarkerclosed);
  inst_list=add_instructions_list();
  *(inst_list->tail)=inst;
  inst_list->tail=&(inst->next);
  add_char(q,q->zone_main_pass,e,inst_list,NULL);
  return q;
}


/*
  A trivial hash function

  TODO: make this static, and provide a public interface for retrieval, instead.
*/
unsigned int hash_cstring (char* p) {
  unsigned int value=0;
  while(*p) {
    value+=*p;
    p++;
  }
  return value % GROUP_HASH_TABLE_SIZE;
}

unsigned int hash_cstring_n(char* p,size_t len)
{
  unsigned int value=0;
  unsigned int i=0;
  while(*p && (i++ < len)) {
    value+=*p;
    p++;
  }
  return value % GROUP_HASH_TABLE_SIZE;	/* XXX: why GROUP_HASH_TABLE_SIZE? */
}
