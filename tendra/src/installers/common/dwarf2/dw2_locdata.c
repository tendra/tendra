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
 *    		 Crown Copyright (c) 1998
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


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$
 *$Log$
 *Revision 1.2  2002/11/21 22:31:06  nonce
 *Remove ossg prototypes.  This commit is largely whitespace changes,
 *but is nonetheless important.  Here's why.
 *
 *I.  Background
 *=========================
 *
 *    The current TenDRA-4.1.2 source tree uses "ossg" prototype
 *conventions, based on the Open Systems Software Group publication "C
 *Coding Standards", DRA/CIS(SE2)/WI/94/57/2.0 (OSSG internal document).
 *The goal behind ossg prototypes remains admirable: TenDRA should
 *support platforms that lack ANSI compliant compilers.  The explicit
 *nature of ossg's prototypes makes macro substition easy.
 *
 *    Here's an example of one function:
 *
 *    static void uop
 *	PROTO_N ( ( op, sha, a, dest, stack ) )
 *	PROTO_T ( void ( *op ) PROTO_S ( ( shape, where, where ) ) X
 *		  shape sha X exp a X where dest X ash stack )
 *    {
 *
 *tendra/src/installers/680x0/common/codec.c
 *
 *  The reasons for removing ossg are several, including:
 *
 *  0) Variables called 'X' present a problem (besides being a poor
 *variable name).
 *
 *  1) Few platforms lack ANSI-compliant compilers.  ISO-compliant
 *prototypes are easily handled by most every compiler these days.
 *
 *  2) Although TenDRA emphasizes portability, standards compliance is
 *the primary goal of the current project.  We should expect no less
 *from the compiler source code.
 *
 *  3) The benefits of complex prototypes are few, given parameter
 *promotion rules.  (Additionally, packing more types into int-sized
 *spaces tends to diminish type safety, and greatly complicates
 *debugging and testing.)
 *
 *  4) It would prove impractical to use an OSSG internal style document
 *in an open source project.
 *
 *  5) Quite frankly, ossg prototypes are difficult to read, but that's
 *certainly a matter of taste and conditioning.
 *
 *II.  Changes
 *=========================
 *
 *   This commit touches most every .h and .c file in the tendra source
 *tree.  An emacs lisp script (http://www.tendra.org/~nonce/tendra/rmossg.el)
 *was used to automate the following changes:
 *
 *   A.  Prototype Conversions.
 *   --------------------------------------------------
 *
 *   The PROTO_S, PROTO_Z, PROTO_N, PROTO_T, and PROTO_V macros were
 *rewritten to ISO-compliant form.  Not every file was touched.  The
 *files named ossg.h, ossg_api.h, code.c, coder.c and ossg_std.h were
 *left for hand editing.  These files provide header generation, or have
 *non-ossg compliant headers to start with.  Scripting around these
 *would take too much time; a separate hand edit will fix them.
 *
 *   B.  Statement Spacing
 *   --------------------------------------------------
 *
 *   Most of the code in the TenDRA-4.1.2 used extra spaces to separate
 *parenthetical lexemes.  (See the quoted example above.)  A simple
 *text substitution was made for:
 *
 *     Before            After
 *===================================
 *
 *   if ( x )            if (x)
 *   if(x)               if (x)
 *   x = 5 ;             x = 5;
 *   ... x) )            ... x))
 *
 *All of these changes are suggested by style(9).  Additional, statement
 *spacing considerations were made for all of the style(9) keywords:
 *"if" "while" "for" "return" "switch".
 *
 *A few files seem to have too few spaces around operators, e.g.:
 *
 *      arg1*arg2
 *
 *instead of
 *
 *      arg1 * arg2
 *
 *These were left for hand edits and later commits, since few files
 *needed these changes.  (At present, the rmossg.el script takes 1 hour
 *to run on a 2GHz P4, using a ramdisk.  Screening for the 1% that
 *needed change would take too much time.)
 *
 *   C.  License Information
 *   --------------------------------------------------
 *
 *After useful discussion on IRC, the following license changes were
 *made:
 *
 *   1) Absent support for $License::BSD$ in the repository, license
 *and copyright information was added to each file.
 *
 *   2) Each file begins with:
 *
 *   Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 *   All rights reserved.
 *
 *   Usually, copyright stays with the author of the code; however, I
 *feel very strongly that this is a group effort, and so the tendra
 *project should claim any new (c) interest.
 *
 *   3) The comment field then shows the bsd license and warranty
 *
 *   4) The comment field then shows the Crown Copyright, since our
 *changes are not yet extensive enough to claim any different.
 *
 *   5) The comment field then closes with the $TenDRA$ tag.
 *
 *   D.  Comment Formatting
 *   --------------------------------------------------
 *
 *The TenDRA-4.1.2 code base tended to use comment in this form:
 *
 *    /*
 *       Statement statement
 *       statement
 *     */
 *
 *while style(9) suggests:
 *
 *    /*
 *     * Statement statement
 *     * statement
 *     */
 *
 *Not every comment in -4.1.2 needed changing.  A parser was written to
 *identify non-compliant comments.  Note that a few comments do not
 *follow either the TenDRA-4.1.2 style or style(9), or any style I can
 *recognize.  These need hand fixing.
 *
 *   E.  Indentation
 *   --------------------------------------------------
 *
 *   A elisp tendra-c-mode was created to define how code should be
 *indented.  The structure follows style(9) in the following regards:
 *
 *  (c-set-offset 'substatement-open 0)
 *  (setq c-indent-tabs-mode t
 *	c-indent-level 4
 *	c-argdecl-indent t
 *	c-tab-always-indent t
 *	backward-delete-function nil
 *	c-basic-offset 4
 *	tab-width 4))
 *
 *This means that substatement opening are not indented.  E.g.:
 *
 *   if (condition)
 *   {
 *
 *instead of
 *
 *   if (condition)
 *     {
 *
 *or even
 *
 *   if (condition) {
 *
 *Each statement is indented by a tab instead of a spaces.  Set your tab
 *stop to comply with style(9); see the vim resources in the tendra
 *tree.  I'll add the emacs mode support shortly.
 *
 *No doubt, a function or two escaped change because of unusual
 *circumstances.  These must be hand fixed as well.
 *
 *III.  Things Not Changed
 *=========================
 *
 *    A large number of style(9) deficiencies remain.  These will
 *require a separate effort.  I decided to stop with the changes noted
 *above because:
 *
 *   0)  The script currently takes hours to run to completion even on
 *high-end consumer machines.
 *
 *   1)  We need to move on and fix other substantive problems.
 *
 *   2) The goal of this commit was *just* ossg removal; I took the
 *opportunity to get other major white-space issues out of the way.
 *
 *    I'll also note that despite this commit, a few ossg issues remain.
 *These include:
 *
 *   0) The ossg headers remain.  They contain useful flags needed by
 *other operations.  Additionally, the BUILD_ERRORS perl script still
 *generates ossg-compliant headers.  (This is being removed as we change
 *the build process.)
 *
 *   1) A few patches of code check for ossg flags: "if (ossg) etc."
 *These can be hand removed as well.
 *
 *   2) No doubt, a few ossg headers escaped the elisp script.  We can
 *address these seriatim.
 *
 *IV.  Testing
 *=========================
 *
 *    Without a complete build or test suite, it's difficult to
 *determine if these changes have introduced any bugs.  I've identified
 *several situations where removal of ossg caused bugs in sid and
 *calculus operations.  The elisp script avoids these situations; we
 *will hand edit a few files.
 *
 *    As is, the changes should behave properly; the source base builds
 *the same before and after the rmossg.el script is run.  Nonetheless,
 *please note that this commit changes over 23,000 PROTO declarations,
 *and countless line changes.  I'll work closely with any developers
 *affected by this change.
 *
 * Revision 1.2  1998/03/15  16:00:36  pwe
 * regtrack dwarf dagnostics added
 *
 * Revision 1.1  1998/03/11  11:03:46  pwe
 * DWARF optimisation info
 *
 **********************************************************************/

#include "config.h"
#include "common_types.h"
#include "dg_types.h"
#include "dw2_config.h"
#include "dw2_basic.h"
#include "dw2_codes.h"
#include "dw2_iface.h"
#include "dw2_info.h"
#include "expmacs.h"
#include "tags.h"
#include "basicread.h"
#include "xalloc.h"
#include "externs.h"
#include "dg_aux.h"
#include "dw2_locdata.h"


/*	Location list information is collected for each object, held via
 *	fields of the 'obtain_value' exp (which is a hold_tag). last is set
 *	if the object is master of a new location. bro is used to hold 
 *	references to other objects that share this location (as a bro list).
 *	no is label for shared location set.
 *		pt holds other more temporary uses (via ll_item).
 */



#define	LOp_Non_Current 1
#define	LOp_Locked	2
#define	LOp_Const	3
#define	LOp_Shared	4
#define	LOp_Portion	5


typedef enum
{
	LL_OPTLOCK = 1,
	LL_CONST,
	LL_RET,
	LL_REGSHARE,
	LL_MASTERSHARE
} loclist_key;

typedef struct rs_s
{
	long			start;
	long			end;
	long			share;
	dg_name		nm;
	int			reg;
	struct rs_s *		next_share;
	struct rs_s *		next_loc;
} * regshare_item;

typedef struct rsl_s
{
	dg_name		alloc;
	int			reg;
	regshare_item		items;
	struct rsl_s *	next;
} * regshare_list;

typedef struct ll_s
{
	int			key	: 8;
	int			open	: 1;
	int			has_inner : 1;
	union
	{
		dg_info		d;
		retrec *		r;
		regshare_item	l;
	} u;
	struct ll_s *		next;
	struct ll_s *		inner;
} * ll_item;

static *
ll_root(dg_name nm)
{
	exp x = nm->data.n_obj.obtain_val;
	exp * ref = &(pt(x));
	return (ll_item *)((void *)ref);
}

static ll_item
new_ll_item(loclist_key k, int o)
{
	ll_item ans = (ll_item) xmalloc (sizeof (struct ll_s));
	ans->key = k;
	ans->open = ans->has_inner = o;
	ans->next = (ll_item)0;
	ans->inner = (ll_item)0;
	return ans;
}

static regshare_list all_regshares = (regshare_list)0;

void *
dw_new_regshare(dg_name nm, int reg)
{
	regshare_list ans = (regshare_list) xmalloc (sizeof (struct rsl_s));
	ans->alloc = nm;
	ans->reg = reg;
	ans->items = (regshare_item)0;
	ans->next = all_regshares;
	all_regshares = ans;
	return (void *)ans;		/* actual type local to this file */
}

void
dw_add_regshare(void * w, dg_name nm, long start,
				long end)
{
	regshare_list holder = (regshare_list)w;
	regshare_item item = (regshare_item) xmalloc (sizeof (struct rs_s));
	item->start = start;
	item->end = end;
	item->share = 0;
	item->nm = nm;
	item->next_share = holder->items;
	item->next_loc = (regshare_item)0;
	holder->items = item;
	return;
}


obj_list * local_objects = (obj_list *)0;

static void
check_taggable(dg_name nm)
{
	if (!nm->mor || !nm->mor->this_tag)
		IGNORE f_dg_tag_name (gen_tg_tag (), nm);
	return;
}


void
set_locdata(obj_list this_obl)
{
	dg_name this_nm = this_obl.obj;
	while (this_nm) {
		if (this_nm->key == DGN_OBJECT) {
			exp x = this_nm->data.n_obj.obtain_val;
			exp id;
			if (x && (id = dw_has_location (son(x)), id)) {
				if (isglob(id)) {
					dg_name master = brog(id)->dec_u.dec_val.diag_info;
					if (!master)
						master = brog(id)->dec_u.dec_val.diag_info = this_nm;
					if (master == this_nm) {
						setlast (x);
						no(x) = next_dwarf_label ();
					}
					else {
						exp y = master->data.n_obj.obtain_val;
						setbro (x, bro(y));
						setbro (y, (exp)((void *)this_nm));
						no(x) = no(y);
						check_taggable (master);
						check_taggable (this_nm);
					}
				}
				else {
					int found = 0;
					obj_list * obl = local_objects;
					while (obl && !found) {
						dg_name nm = obl->obj;
						while (nm) {
							if (nm->key == DGN_OBJECT) {
								exp y = nm->data.n_obj.obtain_val;
								if (y && last(y) && dw_has_location (son(y)) == id) {
									setbro (x, bro(y));
									setbro (y, (exp)((void *)this_nm));
									no(x) = no(y);
									check_taggable (nm);
									check_taggable (this_nm);
									found = 1;
									break;
								}
							}
							if (!obl->islist)
								break;
							nm = nm->next;
						}
						obl = obl->next;
					}
					if (!found) {
						setlast (x);
						no(x) = next_dwarf_label ();
						dw_allocated (this_nm, id);
					}
				}
			}
			else
				no(x) = 0;
		}
		if (!this_obl.islist)
			break;
		this_nm = this_nm->next;
	}
}


void
close_locdata(obj_list this_obl)
{
	dg_name this_nm = this_obl.obj;
	while (this_nm) {
		if (this_nm->key == DGN_OBJECT) {
			exp x = this_nm->data.n_obj.obtain_val;
			if (x && last(x))
				dw_deallocated (this_nm);
		}
		if (!this_obl.islist)
			break;
		this_nm = this_nm->next;
	}
}


dg_name
find_equiv_object(exp e, int isc)
{
	obj_list * obl = local_objects;
	while (obl) {
		dg_name nm = obl->obj;
		while (nm) {
			if (nm->key == DGN_OBJECT) {
				exp x = nm->data.n_obj.obtain_val;
				if (isc) {
					if (x && name(son(x)) == cont_tag && 
						dw_loc_equivalence (e, son(son(x))))
						return nm;
				}
				else {
					if (x && dw_loc_equivalence (e, son(x)))
						return nm;
				}
			}
			if (!obl->islist)
				break;
			nm = nm->next;
		}
		obl = obl->next;
	}
	return (dg_name)0;
}



static dg_name
find_simple_object(exp e)
{				/* e is name_tag for required object */
	obj_list * obl = local_objects;
	while (obl) {
		dg_name nm = obl->obj;
		while (nm) {
			if (nm->key == DGN_OBJECT) {
				exp x = nm->data.n_obj.obtain_val;
				while (x && (name(x) == hold_tag || name(x) == cont_tag || 
							 name(x) == reff_tag))
					x = son(x);
				if ((x) && name(x) == name_tag && son(x) == son(e) &&
					(no(x) <= no(e)) && 
					(no(x) + shape_size(sh(x))) >= (no(e) + shape_size(sh(e))))
					return nm;
			}
			if (!obl->islist)
				break;
			nm = nm->next;
		}
		obl = obl->next;
	}
	return (dg_name)0;
}


void
set_optim_objects(dg_info optim, int start)
{
	objset * obj = optim->data.i_optim.objs;
	while (obj) {
		dg_name nm = obj->tg->p.nam;
		if (start) {
			ll_item * l = ll_root (nm);
			while (*l) {
				if ((*l)->open)
					l = &((*l)->inner);
				else
					l = &((*l)->next);
			}
			*l = new_ll_item (LL_OPTLOCK, 1);
			(*l)->u.d = optim;
		}
		else {
			ll_item l = * ll_root (nm);
			while (l->key != LL_OPTLOCK || l->u.d != optim) {
				if ((l)->open)
					l = l->inner;
				else
					l = l->next;
			}
			l->open = 0;
		}
		obj = obj->next;
	}
	return;
}


void
set_remval_object(dg_info rmv)
{
	dg_name nm = find_simple_object (son (rmv->data.i_remval.var));
	if (nm) {
		ll_item * l = ll_root (nm);
		while (*l) {
			if ((*l)->open)
				l = &((*l)->inner);
			else
				l = &((*l)->next);
		}
		*l = new_ll_item (LL_CONST, 0);
		(*l)->u.d = rmv;
	}
	return;
}


void
set_obj_rets(retrec * rec)
{
	obj_list * obl = local_objects;
	while (obl) {
		dg_name nm = obl->obj;
		while (nm) {
			if (nm->key == DGN_OBJECT) {
				exp x = nm->data.n_obj.obtain_val;
				while (x && (name(x) == hold_tag || name(x) == cont_tag || 
							 name(x) == reff_tag))
					x = son(x);
				if ((x) && name(x) == name_tag && !isdiscarded(x) && 
					!isglob(son(x))) {
					ll_item * l = ll_root (nm);
					while (*l) {
						if ((*l)->open)
							l = &((*l)->inner);
						else
							l = &((*l)->next);
					}
					*l = new_ll_item (LL_RET, 0);
					(*l)->u.r = rec;
				}
			}
			if (!obl->islist)
				break;
			nm = nm->next;
		}
		obl = obl->next;
	}
	return;
}


static ll_item
find_ll_item(dg_name nm, loclist_key k, int force)
{
	ll_item * ll = ll_root (nm);
	ll_item l = *ll;
	while (l && l->key != k)
		l = l->next;
	if (!l && force) {
		l = new_ll_item (k, 0);
		l->u.l = (regshare_item)0;
		l->next = *ll;
		*ll = l;
	}
	return l;
}

static void
out_regshare_set(regshare_item it)
{
	regshare_item this = it;
	while (this) {
		dg_name nm = this->nm;
		if (nm) {
			regshare_item look = it;
			while (look->nm != nm)	/* avoid duplicates */
				look = look->next_share;
			if (look == this)
				dw_at_ext_address (nm->mor->this_tag);
		}
		this = this->next_share;  
	}
	return;
}



void
init_dw_locdata()
{
	all_regshares = (regshare_list)0;
	local_objects = (obj_list *)0;
	dw_all_deallocated ();
	return;
}

void
complete_dw_locdata()
{
	regshare_list top_l = all_regshares;
	while (top_l) {
		dg_name master = top_l->alloc;
		int reg = top_l->reg;
		regshare_item regitem = top_l->items;
		dg_name nm;
		if (master) {
			while (regitem) {
				nm = master;
				do {
					if (regitem->nm == nm) {
						regitem->nm = (dg_name)0;
						break;
					}
					nm = (dg_name)((void *)bro(nm->data.n_obj.obtain_val));
				} while (nm);
				if (!nm) {	/* regitem not in allocation shareset */
					ll_item l = find_ll_item (master, LL_MASTERSHARE, 1);
					if (!l->u.l)
						l->u.l = regitem;	/* start of extra share list for master */
					regitem->share = no(master->data.n_obj.obtain_val);
					regitem->reg = reg;
					l = find_ll_item (regitem->nm, LL_REGSHARE, 1);
					regitem->next_loc = l->u.l;
					l->u.l = regitem;
					check_taggable (regitem->nm);
					check_taggable (master);
				}
				regitem = regitem->next_share;
			}
		}
		else {
			long share = 0;
			master = nm = (dg_name)0;
			while (regitem) {
				if (!master)
					master = regitem->nm;
				if (!nm)
					nm = regitem->nm;
				if (nm != master) {
					share = next_dwarf_label ();
					break;
				}
				regitem = regitem->next_share;
			}
			regitem = top_l->items;
			while (regitem) {
				ll_item l = find_ll_item (regitem->nm, LL_REGSHARE, 1);
				regitem->share = share;
				if (share)
					check_taggable (regitem->nm);
				regitem->reg = reg;
				regitem->next_loc = l->u.l;
				l->u.l = regitem;
				regitem = regitem->next_share;
			}
			if (share) {
				enter_section ("debug_loc");
				out_dwf_label (share, 1);
				out_regshare_set (top_l->items);
				exit_section ();
			}
		}
		top_l = top_l->next;
	}
	return;
}



static int
obj_decide(ll_item l)
{
	int ans = 0, x;
	while (l && ans < 2) {
		switch (l->key) {
		case LL_OPTLOCK:
		case LL_CONST:
		case LL_MASTERSHARE:
			return 2;
		case LL_RET: {
			if (!ans)
				ans = 1;
			break;
		}
		case LL_REGSHARE: {
			regshare_item rs = l->u.l;
			while (rs && ans<2) {
				if (rs->share)
					ans = 2;
				else
					if (!ans)
						ans = 1;
				rs = rs->next_loc;
			}
			break;
		}
		}
		if (l->has_inner && (x = obj_decide (l->inner), x > ans))
			ans = x;
		l = l->next;
	}
	return ans;
}

int
decide_ll_type(exp x)
{			/* 1 if need location list, 2 if extension list */
	ll_item l = (ll_item)((void *)(pt(x)));
	if ((last(x) && bro(x)) || (!last(x) && no(x)))
		/* main location is shared */
		return 2;
	else
		return obj_decide (l);
}


static long startlab;
static int ll_ok;
static exp obval;

static void
loclist_portion(ll_item l)
{
	while (l) {
		switch (l->key) {
		case LL_CONST: {
			ll_ok = 0;
			break;
		}
		case LL_RET: {
			long endlab = l->u.r->lab;
			if (ll_ok && endlab != startlab) {
				out_loc_range (startlab, endlab, 0);
				dw2_locate_exp (obval, 0, 1);
			}
			startlab = l->u.r->over;
			break;
		}
		case LL_REGSHARE: {
			regshare_item rs = l->u.l;
			while (rs) {
				out_loc_range (rs->start, rs->end, 1);
				out16 (); 
				if (rs->reg < 32) {
					outn ((long)1); outnl();
					out8 (); outn ((long)(DW_OP_reg0 + rs->reg));
				}
				else {
					outn ((long)(1 + uleb128_length((unsigned long)rs->reg)));
					outnl(); out8 ();
					outn ((long)DW_OP_regx); outs (", ");
					uleb128((unsigned long)rs->reg);
				}
				outnl();
				rs = rs->next_loc;
			}
		}
		default:
			break;
		}
		if (l->has_inner)
			loclist_portion (l->inner);
		l = l->next;
	}
	return;
}

void
out_obj_loclist(long l1, long l2, exp x)
{
	ll_item l = (ll_item)((void *)(pt(x)));
	startlab = l1;
	ll_ok = 1;
	obval = son(x);
	loclist_portion (l);
	if (ll_ok && l2 != startlab) {
		out_loc_range (startlab, l2, 0);
		dw2_locate_exp (obval, 0, 1);
	}
	return;
}


static void
extlist_portion(ll_item l)
{
	while (l) {
		switch (l->key) {
		case LL_CONST: {
			long here = l->u.d->data.i_remval.lo_pc;
			if (ll_ok && here != startlab) {
				out_loc_range (startlab, here, 0);
				dw_at_data (1, LOp_Const);
				dw_out_const (obval);
			}
			startlab = here;
			ll_ok = 1;
			obval = l->u.d->data.i_remval.val;
			break;
		}
		case LL_OPTLOCK: {
			out_loc_range (l->u.d->data.i_optim.lo_pc,
						   l->u.d->data.i_optim.hi_pc, 0);
			dw_at_data (1, LOp_Locked);
			dw_at_data (1, l->u.d->data.i_optim.reason);
			break;
		}
		case LL_REGSHARE: {
			regshare_item rs = l->u.l;
			while (rs) {
				if (rs->share) {
					out_loc_range (rs->start, rs->end, 1);
					dw_at_data (1, LOp_Shared);
					dw_at_address (rs->share);
				}
				rs = rs->next_loc;
			}
		}
		default:
			break;
		}
		if (l->has_inner)
			loclist_portion (l->inner);
		l = l->next;
	}
	return;
}

void
out_obj_extloclist(long l1, long l2, exp x)
{
	ll_item l = (ll_item)((void *)(pt(x)));
	if ((last(x) && bro(x)) || (!last(x) && no(x))) {
		/* main location is shared */
		out_loc_range (l1, l2, 0);
		dw_at_data (1, LOp_Shared);
		dw_at_address (no(x));
	}
	startlab = l1;
	ll_ok = 0;
	if (l)
		extlist_portion (l);
	if (ll_ok && l2 != startlab) {
		out_loc_range (startlab, l2, 0);
		dw_at_data (1, LOp_Const);
		dw_out_const (obval);
	}
	return;
}

void
out_obj_shared_set(dg_name dn)
{
	exp x = dn->data.n_obj.obtain_val;
	ll_item l = find_ll_item (dn, LL_MASTERSHARE, 0);
	if (last(x) && (bro(x) || l)) {
		out_dwf_label (no(x), 1);
		dw_at_ext_address (dn->mor->this_tag);
		while (bro(x)) {
			dg_name nm = (dg_name)((void *)bro(x));
			dw_at_ext_address (nm->mor->this_tag);
			x = nm->data.n_obj.obtain_val;
		}
		if (l)
			out_regshare_set (l->u.l);
		out32(); outs("0"); outnl_comment ("share list end");
	}
	return;
}

