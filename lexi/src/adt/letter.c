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
#include "tree.h"	/* XXX */


/*
    FIND AN ESCAPE SEQUENCE

    This routine finds the character corresponding to the escape sequence c.
*/

letter
find_escape(int c, letter eof_letter_code)
{
    letter a;
    switch (c) {
	case 'n': a = '\n'; break;
	case 't': a = '\t'; break;
	case 'v': a = '\v'; break;
	case 'f': a = '\f'; break;
	case 'r': a = '\r'; break;
	case '?': a = '?'; break;
	case '"': a = '"'; break;
	case '[': a = '['; break;
	case '\\': a = '\\'; break;
	case '\'': a = '\''; break;
	case 'e': a = eof_letter_code; break;
	default : {
	    error(ERROR_SERIOUS, "Unknown escape sequence, '\\%c'",
		   (unsigned char)c);
	    a = (letter)(c & 0xff);
	    break;
	}
    }
    return a;
}


/*
    TRANSLATE A STRING INTO A CHARACTER STRING

    This routine translates the string s into an array of letters.
*/

letter *
make_string(char *s, zone* scope)
{
    int i = 0, n = (int)strlen(s);
    letter *p = xmalloc_nof(letter, n + 1);
    unsigned int hash_key;
    int reverse_match=0;
    char_group* grp;
    zone* inner_scope;
    while (*s) {
	letter a;
	char c = *(s++);
	if (c == '\\') {
	    c = *(s++);
	    a = find_escape(c,tree_get_eoflettercode(scope->top_level));
	} else if (c == '[') {
	    size_t glen;
	    char *gnm = s;
	    if(*s=='^') {
	        gnm++;
		s++;
		reverse_match=1;
	    }
	    else
	      reverse_match=0;
	    while (*s && *s != ']')s++;
	    glen = (size_t)(s - gnm);
	    if (*s) {
		s++;
	    } else {
		error(ERROR_SERIOUS,
			"Unterminated character group name, '%s'", gnm);
	    }
	    
	    hash_key=hash_cstring_n(gnm,glen);
	    for(inner_scope=scope; inner_scope!=NULL;inner_scope=inner_scope->up) {
	       for (grp = inner_scope->groups_hash_table[hash_key].head; grp!=NULL; grp=grp->next) {
		   if (strncmp(gnm, grp->name, glen) == 0) 
		       break;
		}
	        if(grp!=NULL)
		    break;
	    }
	    if(inner_scope==NULL) {
	        error(ERROR_SERIOUS, "Unknown character group, '%.*s'",
		      (int)glen, gnm);
		a = '?';
	    } else 
	        a = (reverse_match ? grp->notin_letter_code : grp->letter_code) ;
	} else {
	  a= (letter) (c & 0xff);
	}
	p [i] = a;
	i++;
    }
    p [i] = tree_get_lastlettercode(scope->top_level);
    return p;
}

/* 
   NEW LETTER TRANSLATION 
*/
letter_translation* new_letter_translation(letter_translation_type ltt)
{
  letter_translation *p;
  p = xmalloc(sizeof *p);
  p->type=ltt;
  p->next=NULL;
  return p;
}

/* 
   ADD LETTER TRANSLATION 
*/
letter_translation* add_group_letter_translation(char_group* grp, int reverse_match)
{
  letter_translation_type type= reverse_match ? notin_group_letter: group_letter;
  letter_translation*p= new_letter_translation(type);
  p->letter_code=tree_add_generated_key(grp->z->top_level);
  p->u.grp=grp;
  return p;
}

