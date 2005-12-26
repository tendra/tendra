/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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
 *    		 Crown Copyright (c) 1996
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


#include "config.h"
#include "common_types.h"
#include "assembler.h"
#include "exp.h"
#include "shapemacs.h"
#include "tags.h"
#include "tests.h"
#include "is_worth.h"
#ifndef tdf3
#include "68k_globals.h"
#endif


/*
 *    CC CONVENTIONS
 *
 *    HP cc has different conventions to gcc on certain points, most
 *    notably on the alignment of bitfields.  Both conventions are
 *    supported, but the cc conventions are default on the HP.  NeXT
 *    cc is gcc.
 */

#ifdef hp_cc_conventions
int cc_conventions = 1;
#else
int cc_conventions = 0;
#endif

bool
reused_parameter(exp e)
{
	bool reused = 0;
	exp def, ident_exp;
	def = son (e);
	if (name (def) == name_tag) {
		ident_exp = son (def);
		if (! isvar (ident_exp)) {
			/* This an obtain_tag of a parameter */
			if (name(son(ident_exp)) == formal_callee_tag) {
				reused = cur_proc_use_same_callees;
			}
			else {
				/* caller parameter */
				reused = cur_proc_has_tail_call;
			}
		}
	}
	return reused;
}

/*
 *    CAN THE VALUE OF AN EXPRESSION BE PUT INTO A REGISTER?
 *
 *    This routine returns 1 if the expression e can be put into a register.
 *    It has to have its visible flag false, and to be of a suitable shape.
 */

bool
regable(exp e)
{
    shape sha;
    char n;
    long sz;
	
    if (isvis (e)) return (0);
	
    sha = sh (son (e));
    n = name (sha);
    if (n == realhd || n == doublehd) return (1);
	
    sz = shape_size (sha);
	
    return (n != cpdhd && n != nofhd && sz <= 32);
}


/*
 *    DOES AN EXP HAVE NO SIDE EFFECTS?
 *
 *    This routine returns 1 if e has no side effects.
 */

bool
no_side(exp e)
{
    int n = name (e);
    if (n == ident_tag) {
		return (no_side (son (e)) && (no_side (bro (son (e)))));
    }
    return (is_a (n) || n == test_tag ||
			n == ass_tag || n == testbit_tag);
}

char n;

/*
 *    IS AN EXP A PUSHABLE PROCEDURE ARGUMENT?
 *
 *    Can the expression e be pushed directly onto the stack when it is
 *    the parameter of a procedure?
 */

bool
push_arg(exp e)
{
    unsigned char n = name (e);
	
    if (is_a (n)) return (1);
    if (n == apply_tag || n == apply_general_tag) return (reg_result (sh (e)));
    if (n == ident_tag) {
		return (push_arg (son (e)) && push_arg (bro (son (e))));
    }
    return (0);
}


#if 0

/*
 *    IS A UNION ACTUALLY POINTER VOID?
 *
 *    No longer used.
 */


#ifndef PTR_VOID_MIN
#define PTR_VOID_MIN	10
#endif

bool
is_ptr_void(shape sha)
{
    bool go;
    int ptrs = 0;
    exp t = son (sha);
    if (t == nilexp) return (0);
    do {
		go = (last (t) ? 0 : 1);
		if (name (sh (t)) != ptrhd) return (0);
		ptrs++;
		t = bro (t);
    } while (go);
    if (ptrs < PTR_VOID_MIN) return (0);
#ifdef PTR_VOID_MAX
    if (ptrs > PTR_VOID_MAX) return (0);
#endif
    return (1);
}

#endif


/*
 *    IS A SHAPE COMPOUND?
 *
 *    This routine is designed to test whether a given shape is compound,
 *    and thus likely to cause problems when it is the parameter of a
 *    procedure.
 */

bool
cpd_param(shape sha)
{
    char n = name (sha);
    if (!cc_conventions || n == bitfhd) {
		long sz = shape_size (sha);
		if (sz <= 32) return (0);
    }
    return (n == cpdhd || n == nofhd || n == bitfhd
			
            || n == s64hd || n == u64hd
			
		);
}


/*
 *    DOES A PROCEDURE RETURN A RESULT OF A GIVEN SHAPE IN A REGISTER?
 *
 *    cc has two ways of getting results from procedures.  Firstly in the
 *    register D0 (or D0 and D1 in certain cases) and secondly in a section
 *    of memory the address of which is passed in at the start of the
 *    procedure in the A1 register and returned at the end in the D0
 *    register.  This routine works out whether or not a procedure
 *    delivering a result of shape sha will use the first method.
 */


int
reg_result(shape sha)
{
    char n = name (sha);
    if (cc_conventions) {
		/* HP cc doesn't return any tuples, unions etc in a register */
		return (n != cpdhd && n != nofhd);
    } else {
		/* Return anything of size <= 32 or 64 in a register */
		long sz = shape_size (sha);
		return (sz <= 32 || sz == 64);
    }
}


/*
 *    IS A SHAPE OF VARIABLE SIZE?
 *
 *    This routine returns 1 if sha involves an array.
 */

bool
varsize(shape sha)
{
    return (name (sha) == nofhd ? 1 : 0);
}

#if 0
Use is_signed macro instead

/*
 *    IS A SHAPE SIGNED?
 *
 *    This routine returns 1 if the integer variety shape sha is signed
 *    and 0 otherwise.
 */

bool
issigned(shape sha)
{
    char n = name (sha);
    if (n == ucharhd || n == uwordhd || n == ulonghd) return (0);
    return (1);
}
#endif

/*
 *    CHECK ON DECLARATION FOR PARAMETER SUBSTITUTION
 *
 *    This routine checks if the declaration e should be substituted
 *    for all its uses or not.
 */

int do_sub_params = 1;

int
check_anyway(exp e)
{
#ifndef tdf3
	return 0;
#else
    if (do_sub_params) {
		setmarked (e);
		if (no (e) > 2) return (1);
    }
    return (0);
#endif
}


/*
 *    IS IT WORTH EXTRACTING A CONSTANT?
 */

int
is_worth(exp c)
{
	unsigned char cnam = name (c);
	return ((!is_o (cnam) && cnam != clear_tag) ||
			/* ignore simple things unless ... */
			(cnam == cont_tag && name (son (c)) == cont_tag &&
			 name (son (son (c)))  == name_tag) ||
			(cnam == name_tag && isparam (son (c)) && !isvar (son (c)) &&
			 shape_size (sh (c)) <= 32 && name (sh (c)) != shrealhd));
}
