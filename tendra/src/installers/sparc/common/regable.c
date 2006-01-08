/*
 * Copyright (c) 2002-2004, The Tendra Project <http://www.tendra.org/>
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


#define SPARCTRANS_CODE
#include "config.h"
#include "common_types.h"
#include "shapemacs.h"
#include "tags.h"
#include "regable.h"

/*
 *  DOES A VALUE OF SHAPE s FIT INTO A FIXED REGISTER?
 */

bool
valregable(shape s)
{
	if (is_floating (name (s))) {
		/* Floating point values don't go in fixed registers */
		return (0);
	}
	else {
		ash a;
		a = ashof (s);
		if (a.ashsize > 32) {
			/* Reject anything too big */
			return (0);
		}
		else if (name (s) == SH_COMPOUND || name (s) == SH_NOF) {
			/* Compound shapes are not put in registers */
			return (0);
		}
		else if (/*a.ashsize == a.ashalign && a.ashalign !=*/ 1) {
			/* Bitfields are put in registers */
			return (1);
		}
	}
	return (0);
}


/*
 *  DOES THE EXPRESSION e FIT INTO A FIXED REGISTER?
 */

bool
fixregable(exp e)
{
	if (!isvis (e) && !isoutpar (e) && !isglob (e) && !isenvoff(e) &&
		name(son(e)) != caller_name_tag) {
		shape s = sh (son (e));
		return (valregable (s));
	}
	return (0);
}


/*
 *  DOES THE EXPRESSION e FIT INTO A FLOATING POINT REGISTER?
 */

bool
floatregable(exp e)
{
	if (!isvis (e) && !isoutpar (e) && !isglob (e) && !isenvoff(e) &&
		name(son(e)) != caller_name_tag) {
		shape s = sh (son (e));
		if (is_floating (name (s))) {
#if use_long_double
			if (shape_size (s) > 64) return (0);
#endif
			return (1);
		}
		else {
			return (0);
		}
	}
	return (0);
}
