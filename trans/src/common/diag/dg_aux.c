/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/check.h>
#include <shared/xalloc.h>

#include <reader/exp.h>

#include <reader/code.h>
#include <reader/basicread.h>
#include <reader/sort.h>
#include <reader/externs.h>
#include <reader/table_fns.h>

#include <construct/tags.h>
#include <construct/exp.h>
#include <construct/me_fns.h>

#include <main/flags.h>

#include <refactor/const.h>
#include <refactor/refactor.h>

#include "dg_aux.h"
#include "dg_globs.h"


#define isdiaginfo(e)	0
#define setisdiaginfo(e)
#define isdiscarded(e)	0
#define setisdiscarded(e)


int doing_inlining = 0;

dg_info current_dg_info = NULL;	/* needed when coding extra_diags */
exp current_dg_exp = NULL;		/* needed when coding extra_diags */

short_sourcepos no_short_sourcepos;



#define DG_CLUMP_SIZE 50	/* Generate a clump of dg_name etc together */
#define FILE_CLUMP_SIZE 5


typedef union {			/* These have similar size */
	struct dg_name_t	nam;
	struct dg_type_t	typ;
	struct dg_info_t	inf;
	struct dg_more_t	mor;
} dg_union;

static int dg_clump_left = 0;
static dg_union *next_dg;

static void
make_dg_clump(void)
{
	next_dg = (dg_union *)xcalloc(DG_CLUMP_SIZE, sizeof(dg_union));
	dg_clump_left = DG_CLUMP_SIZE;
	return;
}


dg_name
new_dg_name(dg_name_key k)
{
	dg_name ans;
	if (!dg_clump_left) {
		make_dg_clump();
	}
	dg_clump_left--;
	ans = &((next_dg++)->nam);
	ans->key = k;
	ans->mor = (dg_more_name)0;
	ans->next = NULL;
	return ans;
}


dg_type
new_dg_type(dg_type_key k)
{
	dg_type ans;
	if (!dg_clump_left) {
		make_dg_clump();
	}
	dg_clump_left--;
	ans = &((next_dg++)->typ);
	ans->key = k;
	ans->outref.k = NO_LAB;
	ans->mor = (dg_more_name)0;
	return ans;
}


dg_info
new_dg_info(dg_info_key k)
{
	dg_info ans;
	if (!dg_clump_left) {
		make_dg_clump();
	}
	dg_clump_left--;
	ans = &((next_dg++)->inf);
	ans->key = k;
	ans->this_tag = NULL;
	ans->more = NULL;
	return ans;
}


void
extend_dg_name(dg_name nm)
{
	dg_more_name mor;
	if (!dg_clump_left) {
		make_dg_clump();
	}
	dg_clump_left--;
	nm->mor = mor = &((next_dg++)->mor);
	mor->this_tag = NULL;
	mor->inline_ref = NULL;
	mor->refspec = NULL;
	mor->elabn = NULL;
	mor->exptns = no_dg_type_list_option;
	mor->end_pos = no_short_sourcepos;
	mor->en_family = NULL;
	mor->vslot = NULL;
	mor->repn = NULL;
	mor->acc = DG_ACC_NONE;
	mor->virt = DG_VIRT_NONE;
	mor->isinline = 0;
	mor->prognm = 0;
	mor->isconst = 0;
	mor->isspec = 0;
	mor->issep = 0;
	mor->isnew = 0;
	mor->aderiv = 0;
	return;
}


void
extend_dg_type(dg_type tp)
{
	dg_more_name mor;
	if (!dg_clump_left) {
		make_dg_clump();
	}
	dg_clump_left--;
	tp->mor = mor = &((next_dg++)->mor);
	mor->this_tag = NULL;
	mor->inline_ref = NULL;
	mor->refspec = NULL;
	mor->elabn = NULL;
	mor->acc = DG_ACC_NONE;
	mor->virt = DG_VIRT_NONE;
	mor->isinline = 0;
	mor->prognm = 0;
	mor->isconst = 0;
	mor->isspec = 0;
	mor->isnew = 0;
	mor->aderiv = 0;
	return;
}


void
init_dgtag(dg_tag tg)
{
	tg->key = DGK_NONE;
	tg->done = 0;
	tg->needed = 0;
	tg->any_inl = 0;
	tg->outref.k = NO_LAB;
	tg->abstract_lab = 0;
	tg->copy = NULL;
	return;
}


dg_tag
gen_tg_tag(void)
{
	dg_tag tg = (dgtag_struct *)xcalloc(1, sizeof(dgtag_struct));
	init_dgtag(tg);
	return tg;
}


/* The following avoids repetitions of pointers and other qualified types */

dg_type
get_qual_dg_type(dg_qual_type_key qual, dg_type typ)
{
	static dg_type qual_type_list[N_DG_QUAL_TYPES] = {NULL };
	dg_type ans = qual_type_list[qual];
	while (ans) {
		if (ans->data.t_qual.typ == typ) {
			return ans;
		}
		ans = ans->data.t_qual.another;
	}
	ans = new_dg_type(DGT_QUAL);
	ans->data.t_qual.q_key = qual;
	ans->data.t_qual.typ = typ;
	ans->data.t_qual.another = qual_type_list[qual];
	qual_type_list[qual] = ans;
	return ans;
}


/* The following avoids repetitions of bitfield types */

dg_type
get_dg_bitfield_type(dg_type typ, shape sha, bitfield_variety bv)
{
	static dg_type bf_list = NULL;
	dg_type ans = bf_list;
	while (ans) {
		if (ans->data.t_bitf.expanded == typ &&
		    ans->data.t_bitf.bv.bits == bv.bits &&
		    ans->data.t_bitf.bv.has_sign == bv.has_sign) {
			return ans;
		}
		ans = ans->data.t_bitf.another;
	}
	ans = new_dg_type(DGT_BITF);
	ans->data.t_bitf.expanded = typ;
	ans->data.t_bitf.sha = sha;
	ans->data.t_bitf.bv = bv;
	ans->data.t_bitf.another = bf_list;
	bf_list = ans;
	return ans;
}

/* All other types are either unlikely to be repeated, or are rare */


/* dg_idname is overkill for many purposes - we just want a string */

char *
idname_chars(dg_idname nam)
{
	static char *empty = "";
	switch (nam.id_key) {
	case DG_ID_INST:
		failer("inappropriate dg_instance_idname");
		return empty;
	case DG_ID_NONE:
		return empty;
	default:
		return nam.idd.nam;
	}
}


/* Avoid repetition of files */

dg_filename
get_filename(long dat, char *host, char *path, char *nam)
{
	static dg_filename next_file = NULL;
	static int filespace_left = 0;

	dg_filename ans = all_files;
	while (ans) {
		if (ans->file_dat == dat &&
		    !strcmp(ans->file_host, host) &&
		    !strcmp(ans->file_path, path) &&
		    !strcmp(ans->file_name, nam)) {
			return ans;
		}
		ans = ans->another;
	}

	if (!filespace_left) {
		next_file = (dg_filename)xcalloc(FILE_CLUMP_SIZE,
						 sizeof(struct file_t));
		filespace_left = FILE_CLUMP_SIZE;
	}
	filespace_left--;
	ans = (next_file++);
	ans->file_dat = dat;
	ans->file_host = host;
	ans->file_path = path;
	ans->file_name = nam;
	ans->another = all_files;
	all_files = ans;
	return ans;
}


short_sourcepos
shorten_sourcepos(dg_sourcepos pos)
{
	short_sourcepos ans;
	switch (pos.sp_key) {
	case SP_SHORT:
	case SP_SPAN:
		ans.file = pos.file;
		ans.line = pos.from_line;
		ans.column = pos.from_column;
		break;
	case SP_FILE:
		ans.file = pos.file;
		ans.line = 0;
		ans.column = 0;
		break;
	default:
		ans.file = NULL;
		ans.line = 0;
		ans.column = 0;
	}
	return ans;
}


short_sourcepos
end_sourcepos(dg_sourcepos pos)
{
	short_sourcepos ans;
	if (pos.sp_key == SP_SPAN) {
		ans.file = pos.to_file;
		ans.line = pos.to_line;
		ans.column = pos.to_column;
	}
	else {
		ans.file = NULL;
		ans.line = 0;
		ans.column = 0;
	}
	return ans;
}


dg_type
find_proc_type(dg_type t)
{
	if (t && t->key == DGT_PROC) {
		return t;
	}
	if (t && t->key == DGT_TAGGED) {
		dg_tag tg = t->data.t_tag;
		if (tg->key == DGK_TYPE) {
			return find_proc_type(tg->p.typ);
		}
		if (tg->key == DGK_NAME) {
			dg_name ref_n = tg->p.nam;
			if (ref_n->key == DGN_TYPE) {
				return find_proc_type(ref_n->data.n_typ.raw);
			}
		}
	}
	failer("proc type details unavailable");
	return f_dg_proc_type(new_dg_param_list(0), f_dg_void_type,
			      no_bool_option, no_nat_option, no_nat_option,
			      no_procprops_option);
}


static void
scan_diag_names(exp e, exp whole)
{
	if (name(e) == name_tag) {
		exp id = son(e);
		if (!isdiaginfo(e) && !internal_to(whole, id)) {
			setisdiaginfo(e);
			--no(id);
		}
		return;
	}
	if (son(e) != NULL && name(e) != env_offset_tag) {
		exp t = son(e);
		for (;;) {
			scan_diag_names(t, whole);
			if (last(t)) {
				return;
			}
			t = bro(t);
		}
	}
	return;
}


exp
diaginfo_exp(exp e)
{
	/* mark external names to avoid influencing optimisations */
	exp ans;
	if (!e) {
		return e;
	}
	scan_diag_names(e, e);
	ans = hold(e);
	setpt(ans, NULL);
	setbro (ans, NULL);	/* these fields are used in dwarf generation */
	no(ans) = 0;
	props(ans) = 0;
	clearlast(ans);
	IGNORE refactor(e, e);
	return ans;
}


exp
relative_exp(shape s, token t)
{
	exp id = me_startid(s, f_make_value(s), 0);
	tokval tv;
	tv.tk_exp = me_obtain(id);
	tv = apply_tok(t, keep_place(), EXP_S, &tv);
	IGNORE me_complete_id(id, hold_refactor(tv.tk_exp));
	return hold(id);
}
