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
 *	(1) Its Recipients shall ensure that this Notice is
 *	reproduced upon any copies or amended versions of it;
 *    
 *	(2) Any amended version of it shall be clearly marked to
 *	show both the nature of and the organisation responsible
 *	for the relevant amendment or amendments;
 *    
 *	(3) Its onward transfer from a recipient to another
 *	party shall be deemed to be that party's acceptance of
 *	these conditions;
 *    
 *	(4) DERA gives no warranty or assurance as to its
 *	quality or suitability for any purpose and DERA accepts
 *	no liability whatsoever in relation to any use to which
 *	it may be put.
 *
 * $TenDRA$
 */


/**/


#define HPPATRANS_CODE
#include "config.h"
#include "common_types.h"
#include "tags.h"
#include "expmacs.h"
#include "exp.h"
#include "shapemacs.h"
#include "hppains.h"
#include "is_worth.h"

/*
 *    BOOLEAN VALUES
 */

#define true 1
#define false 0


/*
 *    IS THE EXPRESSION c WORTH EXTRACTING FROM A LOOP?
 *
 *    This is called from mc_list.
 */

int
is_worth(exp c)
{
    unsigned char cnam = name (c);
    bool isflt = (bool) is_floating (name (sh (c)));
	
    if (name (sh (c)) == ptrhd && al1 (sh (c)) == 1) {
		/* Pointers to bits aren't */
		return (false);
    }
	
#if 0
    if (cnam==name_tag && name(father(c))==addptr_tag && isglob(son(c)))
		return (true);
#endif
	
    if (cnam == real_tag) {
		/* Real constants are */
		return (true);
    }
	
    if (cnam == goto_tag) {
		/* Extracting gotos messes things up */
		return (false);
    }
	
    if (cnam == cont_tag) {
		exp s = son (c);
		if (isflt && (name (s) != name_tag || isglob (son (s)))) {
			return (true);
		}
		if (name (s) == reff_tag && no (s) == 0) s = son (s);
		if (name (s) == name_tag && isglob (son (s))) {
			return (true);
		}
		if (name (s) == cont_tag) {
			exp ss = son (s);
			if (name (ss) == reff_tag && no (ss) == 0) ss = son (ss);
			if (name (ss) == name_tag) return (true);
		}
		return (false);
    }
	
#if 0
    if (name (sh (c)) == ptrhd && isglob(son(c))) {
		return (true);
    }
#endif
	
    if (cnam == val_tag) {
		/* It is sometimes worth extracting large integer constants */
		exp dad;
		long n = no (c);
		if (n==0 )
			return (false);
		if (shape_size(sh(c))==64)
			return (false) ; /* Cannot put 64 bit integers in registers! */
		dad = father (c);
		if (dad==nilexp)
		{
			if (SIMM13(n)) return (false);
			return (true);
		}
		
		switch (name (dad)) {
			
	    case and_tag : {
			exp grandad = father (dad);
			if ((name (grandad) == test_tag && (n & (n - 1)) == 0
				 && (props (grandad) == 5 || props (grandad) == 6)
				 && (name (bro (son (grandad))) == val_tag
					 && no (bro (son (grandad))) == 0))
				|| (name (son (grandad)) == val_tag
					&& no (son (grandad)) == 0)) {
				/* a & 2^n == 0 is transformed into a shift */
				return (false);
			}
			/* FALL THROUGH */
			if (((n+1)&n) ==0)
				return false;
			
	    }
			
	    case or_tag :
	    case xor_tag :
	    case test_tag : {
			/* Large or negative constants are worth extracting */
			return ((bool) (n<0 || !SIMM5(n)));
	    }
			
	    case mult_tag :
	    case offset_mult_tag : {
#if 0
			/* Is this necessarily true? */
			if (SIMM13(n)) return (false);
			return ((bool) ((n & (n - 1)) != 0 &&
							(n & (n + 1)) != 0 &&
							((n - 1) & (n - 2)) != 0));
#endif
			return (false);
	    }
			
	    case div1_tag :
	    case div2_tag :
	    case rem2_tag : {
#if 0
			/* Is this necessarily true? */
			if (SIMM13(n)) return (false);
#endif
			return ((bool) ((n & (n - 1)) != 0)) ; /* LINT */
	    }
			
	    default : {
			/* Extract large constants */
			if (SIMM13(n)) return (false);
			return (true);
	    }
		}
    }
	
    if (is_o (cnam) || cnam == clear_tag) return (false);
    return (true);
}

