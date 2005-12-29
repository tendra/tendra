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


#include "config.h"
#include "fmm.h"
#include "msgcat.h"

#include "common_types.h"
#include "installglob.h"
#include "externs.h"
#include "flags.h"
#include "global_opt.h"
#include "basicread.h"
#include "messages_c.h"
#include "szs_als.h"

#include "aldefs.h"

#define max(x,y) ((x)>(y)) ? (x) : (y)


/*
 * frame_als array provides storage for stack frame based alignments.
 * Specially crafted placement of respective alignments provides
 * simple mechanism for comparing them.
 */
static struct aldef_t frame_als[32];

alignment f_locals_alignment    = frame_als + 0;
alignment nv_callers_alignment  = frame_als + 1;
alignment var_callers_alignment = frame_als + 3;
alignment nv_callees_alignment  = frame_als + 7;
alignment var_callees_alignment = frame_als + 15;

/*
 * Common alignments
 */
static struct aldef_t const_aldefs[6];

alignment const_al1   = const_aldefs + 0;
alignment const_al8   = const_aldefs + 1;
alignment const_al16  = const_aldefs + 2;
alignment const_al32  = const_aldefs + 3;
alignment const_al64  = const_aldefs + 4;
alignment const_al512 = const_aldefs + 5;

alignment frame_alignment;

/*
 * Hardcoded and platform dependent alignments.
 */
alignment f_alloca_alignment;
alignment f_var_param_alignment;
alignment f_code_alignment;


static struct CAL {
	int			sh_hd;
	int			al;
	alignment	res;
	struct CAL	*next;
} *cache_pals;


static alignment
get_pal(alignment a, int sh_hd, int al)
{
	struct CAL *cp = cache_pals;
	alignment ap;

	for (cp = cache_pals; cp != NULL; cp = cp->next) {
		if (cp->sh_hd == sh_hd && cp->al == al)
			return cp->res;
	}
	ap = xmalloc(sizeof(*ap));
	*ap = *a;
	ap->sh_hd = sh_hd;
	cp = xmalloc(sizeof(*cp));
	cp->sh_hd = sh_hd;
	cp->al = al;
	cp->res = ap;
	cp->next = cache_pals;
	cache_pals = cp;
	return ap;
}

/*
 * Initialise alignments framework.  Called before d_capsule().
 */
void
init_alignment(void)
{
	int i;

	const_al1->al_n = ALDS_SOLVED;
	const_al1->al = 1;
	const_al1->al_frame = 0;
	const_al1->sh_hd = 0;
	const_al8->al_n = ALDS_SOLVED;
	const_al8->al = 8;
	const_al8->al_frame = 0;
	const_al8->sh_hd = 0;
	const_al16->al_n = ALDS_SOLVED;
	const_al16->al = 16;
	const_al16->al_frame = 0;
	const_al16->sh_hd = 0;
	const_al32->al_n = ALDS_SOLVED;
	const_al32->al = 32;
	const_al32->al_frame = 0;
	const_al32->sh_hd = 0;
	const_al64->al_n = ALDS_SOLVED;
	const_al64->al = 64;
	const_al64->al_frame = 0;
	const_al64->sh_hd = 0;
	const_al512->al_n = ALDS_SOLVED;
	const_al512->al = 512;
	const_al512->al_frame = 0;
	const_al512->sh_hd = 0;
	
	cache_pals = (struct CAL *)0;
	
	for (i = 0; i < 32; i++) {
		frame_als[i].sh_hd = 0;
		frame_als[i].al_n = ALDS_SOLVED;
		frame_als[i].al = 64;
		frame_als[i].al_frame = i + 1;
	}
	f_alloca_alignment = ALLOCA_ALIGN;
	f_var_param_alignment = VAR_PARAM_ALIGN;
	f_code_alignment = CODE_ALIGN;
	stack_align = max(param_align, double_align);
	return;
}


/*
 * Allocate and initialise table of alignment tags
 */
struct aldef_t*
aldef_newtable(long n)
{
	struct aldef_t *tbl, *ap;
	long i;

	tbl = xalloc(sizeof(*ap) * n);

	for (i = 0, ap = tbl; i < n; i++, ap++)
		ap->al_n = ALDS_INVALID;
	return tbl;
}

/*
 * Dispose table of alignmet tags
 */
void
aldef_freetable(struct aldef_t *tbl)
{
	xfree(tbl);
}

static struct aldef_t*
aldef_new(void)
{
	struct aldef_t *ap;

	ap = xalloc(sizeof(*ap));
	ap->al_n = ALDS_INVALID;
	ap->al_frame = 0;
	ap->al = 0;
	ap->sh_hd = 0;
	ap->next_aldef = top_aldef;
	top_aldef = ap;
	return ap;
}

/*
 * Return an alignment for something of which the
 * addresses must be divisible by n bits
 */
alignment
long_to_al(int n)
{
	switch (n) {
	case 0:
	case 1: return const_al1;
	case 8: return const_al8;
	case 16: return const_al16;
	case 32: return const_al32;
	case 64: return const_al64;
	case 512: return const_al512;
	}
	MSG_fatal_illegal_value_for_alignment(n);
	return NULL; /* NOTREACHED */
}


/*
 * Process alignment construct.
 * Return alignment of object of the given shape.
 */
alignment
f_alignment(shape sha)
{
	return align_of(sha);
}

/*
 * Process obtain_al_tag construct.
 */
alignment
f_obtain_al_tag(al_tag a1)
{
	alignment ap;

	if (a1->al_n == ALDS_SOLVED)
		return long_to_al(a1->al);
	/*
	 * The actual value of the aligment is not known at this time, so
	 * we have to put a reference and resolve it later.
	 */
	ap = aldef_new();
	ap->al_n = ALDS_A;
	ap->a = a1;
	return ap;
}

/*
 * Process parameter_alignment construct.
 * Return alignment of a parameter of a procedure of shape sha.
 */
alignment
f_parameter_alignment(shape sha)
{
	int n = name(sha);
	alignment t =
#if issparc
		MIN_PAR_ALIGNMENT;
#else
	f_unite_alignments(MIN_PAR_ALIGNMENT, f_alignment(sha));
#endif

#if ishppa
	if (shape_size(sha) > 64)
		n = nofhd + 1;
#endif
#if issparc
	if (sparccpd(sha))
		n = nofhd + 1;
#endif

	return get_pal(t, n, shape_align(sha));
}

/*
 * Process unite_alignments construct.
 * The resulting alignment should be correct for placing any of the
 * a1 or a2 objects.
 */
alignment
f_unite_alignments(alignment a1, alignment a2)
{
	alignment ap;

	if (a1->al_n == ALDS_SOLVED && a2->al_n == ALDS_SOLVED) {
		if (a1->al_frame == a2->al_frame) {
			if (a1->al > a2->al)
				return a1;
			return a2;
		} else if (a1->al_frame == 0) {
			return a2;
		} else if (a2->al_frame == 0) {
			return a1;
		}
		return (&frame_als[(a1->al_frame | a2->al_frame) - 1]);
	}

	ap = aldef_new();
	ap->al_n = ALDS_AB;
	ap->a = a1;
	ap->b = a2;
	return ap;
}


/* The alignment definitions form a set of simultaneous equations
 *   of the form
 *
 *     a1 = f1(a1,a2 .. an)
 *     a2 = f2(a1,a2 ... an)
 *     ...
 *
 *   The functions f1 f2 etc. are formed entirely from f_alignment,
 *   which takes a shape and delivers an alignment, and unite_sets.
 *   f_alignment provides constants. Since the representation of
 *   alignments must be a homomorphism of sets under unite_sets, and
 *   since any program contains a finite number of basic alignments,
 *   these equations can be solved by iterating unite_sets until
 *   no further change occurs. Unite_sets is represented here by max.
 */

void
process_aldefs(void)
{
	struct aldef_t *ap, *a1, *a2;
	int changed, complete;
	

	/* iterate until there will be no changes */	
	do {
		ap = top_aldef;
		changed = 0;
		complete = 1;
		while (ap != NULL) {
			switch (ap->al_n) {
			case ALDS_SOLVED:
				break;
			case ALDS_AB:
				a1 = ap->a;
				a2 = ap->b;
				if (a1->al_n == ALDS_SOLVED && a2->al_n == ALDS_SOLVED) {
					ap->al_n = ALDS_SOLVED;
					ap->al = max(a1->al, a2->al);
					changed = 1;
				} else
					complete = 0;
				break;
			case ALDS_A:
				a1 = ap->a;
				if (a1->al_n == ALDS_SOLVED) {
					ap->al_n = ALDS_SOLVED;
					ap->al = a1->al;
					changed = 1;
				} else
					complete = 0;
				break;
			default:
				MSG_fatal_illegal_alignment_state(ap->al_n);
			}
			ap = ap->next_aldef;
		}
	} while (changed);

	if (!complete)
		MSG_fatal_incomplete_alignment_eqs();
	return;
}
