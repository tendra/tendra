/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <shared/bool.h>
#include <shared/check.h>
#include <shared/error.h>
#include <shared/string.h>
#include <shared/xalloc.h>

#include <tdf/nat.h>
#include <tdf/sort.h>
#include <tdf/tag.h>

#include <reader/exp.h>
#include <reader/basicread.h>
#include <reader/externs.h>
#include <reader/table_fns.h>

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

#define DG_CLUMP_SIZE 50	/* Generate a clump of dg_name etc together */
#define FILE_CLUMP_SIZE 5

typedef union {
	/* These have similar size */
	struct dg_name_t name;
	struct dg_type_t type;
	struct dg_info_t info;
	struct dg_more_t more;
} dg_union;

short_sourcepos no_short_sourcepos;

static int dg_clump_left = 0;
static dg_union *next_dg;

static void
make_dg_clump(void)
{
	next_dg = xcalloc(DG_CLUMP_SIZE, sizeof(dg_union));
	dg_clump_left = DG_CLUMP_SIZE;
}

dg_name
new_dg_name(dg_name_key k)
{
	dg_name ans;

	if (!dg_clump_left) {
		make_dg_clump();
	}

	dg_clump_left--;

	ans = &((next_dg++)->name);
	ans->key  = k;
	ans->more = (dg_more_name)0;
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

	ans = &((next_dg++)->type);
	ans->key = k;
	ans->outref.k = NO_LAB;
	ans->more = (dg_more_name)0;

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

	ans = &((next_dg++)->info);
	ans->key      = k;
	ans->this_tag = NULL;
	ans->more     = NULL;

	return ans;
}

void
extend_dg_name(dg_name name)
{
	dg_more_name more;

	if (!dg_clump_left) {
		make_dg_clump();
	}

	dg_clump_left--;

	name->more = more = &((next_dg++)->more);

	more->this_tag   = NULL;
	more->inline_ref = NULL;
	more->refspec    = NULL;
	more->elabn      = NULL;
	more->exptns     = no_dg_type_list_option;
	more->end_pos    = no_short_sourcepos;
	more->en_family  = NULL;
	more->vslot      = NULL;
	more->repn       = NULL;
	more->acc        = DG_ACC_NONE;
	more->virt       = DG_VIRT_NONE;
	more->isinline   = 0;
	more->prognm     = 0;
	more->isconst    = 0;
	more->isspec     = 0;
	more->issep      = 0;
	more->isnew      = 0;
	more->aderiv     = 0;
}

void
extend_dg_type(dg_type type)
{
	dg_more_name more;

	if (!dg_clump_left) {
		make_dg_clump();
	}

	dg_clump_left--;

	type->more = more = &((next_dg++)->more);

	more->this_tag   = NULL;
	more->inline_ref = NULL;
	more->refspec    = NULL;
	more->elabn      = NULL;
	more->acc        = DG_ACC_NONE;
	more->virt       = DG_VIRT_NONE;
	more->isinline   = 0;
	more->prognm     = 0;
	more->isconst    = 0;
	more->isspec     = 0;
	more->isnew      = 0;
	more->aderiv     = 0;
}

void
init_dgtag(dg_tag tag)
{
	tag->key          = DGK_NONE;
	tag->done         = 0;
	tag->needed       = 0;
	tag->any_inl      = 0;
	tag->outref.k     = NO_LAB;
	tag->abstract_lab = 0;
	tag->copy         = NULL;
}

/* The following avoids repetitions of pointers and other qualified types */
dg_type
get_qual_dg_type(dg_qual_type_key qual, dg_type type)
{
	static dg_type qual_type_list[N_DG_QUAL_TYPES] = { NULL };
	dg_type ans;

	for (ans = qual_type_list[qual]; ans; ans = ans->data.t_qual.another) {
		if (ans->data.t_qual.type == type) {
			return ans;
		}
	}

	ans = new_dg_type(DGT_QUAL);
	ans->data.t_qual.q_key = qual;
	ans->data.t_qual.type = type;
	ans->data.t_qual.another = qual_type_list[qual];
	qual_type_list[qual] = ans;

	return ans;
}

/* The following avoids repetitions of bitfield types */
dg_type
get_dg_bitfield_type(dg_type type, shape sha, bitfield_variety bv)
{
	static dg_type bf_list = NULL;
	dg_type ans;

	for (ans = bf_list; ans; ans = ans->data.t_bitf.another) {
		if (ans->data.t_bitf.expanded == type &&
		    ans->data.t_bitf.bv.bits == bv.bits &&
		    ans->data.t_bitf.bv.has_sign == bv.has_sign) {
			return ans;
		}
	}

	ans = new_dg_type(DGT_BITF);
	ans->data.t_bitf.expanded = type;
	ans->data.t_bitf.sha = sha;
	ans->data.t_bitf.bv = bv;
	ans->data.t_bitf.another = bf_list;

	bf_list = ans;

	return ans;
}

/* All other types are either unlikely to be repeated, or are rare */

/* dg_idname is overkill for many purposes - we just want a string */
char *
idname_chars(dg_idname name)
{
	static char *empty = "";

	switch (name.id_key) {
	case DG_ID_INST:
		error(ERR_INTERNAL, "inappropriate dg_instance_idname");
		return empty;

	case DG_ID_NONE:
		return empty;

	default:
		return name.idd.name;
	}
}

/* Avoid repetition of files */
dg_filename
get_filename(long dat, char *host, char *path, char *name)
{
	static dg_filename next_file = NULL;
	static int filespace_left = 0;
	dg_filename ans;

	for (ans = all_files; ans; ans = ans->another) {
		if (ans->file_dat == dat &&
		    streq(ans->file_host, host) &&
		    streq(ans->file_path, path) &&
		    streq(ans->file_name, name)) {
			return ans;
		}
	}

	if (!filespace_left) {
		next_file = xcalloc(FILE_CLUMP_SIZE, sizeof(struct file_t));
		filespace_left = FILE_CLUMP_SIZE;
	}
	filespace_left--;

	ans = (next_file++);
	ans->file_dat  = dat;
	ans->file_host = host;
	ans->file_path = path;
	ans->file_name = name;
	ans->another   = all_files;

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
	} else {
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
		dg_tag tag = t->data.t_tag;

		if (tag->key == DGK_TYPE) {
			return find_proc_type(tag->p.type);
		}

		if (tag->key == DGK_NAME) {
			dg_name ref_n = tag->p.name;

			if (ref_n->key == DGN_TYPE) {
				return find_proc_type(ref_n->data.n_type.raw);
			}
		}
	}

	error(ERR_INTERNAL, "proc type details unavailable");
	return f_dg_proc_type(new_dg_param_list(0), f_dg_void_type,
	                      no_bool_option, no_nat_option, no_nat_option,
	                      no_procprops_option);
}

static void
scan_diag_names(exp e, exp whole)
{
	if (e->tag == name_tag) {
		exp id = son(e);

		if (!isdiaginfo(e) && !internal_to(whole, id)) {
			setisdiaginfo(e);
			--no(id);
		}

		return;
	}

	if (son(e) != NULL && e->tag != env_offset_tag) {
		exp t;

		for (t = son(e); ; t = bro(t)) {
			scan_diag_names(t, whole);
			if (t->last) {
				return;
			}
		}
	}
}

/* mark external names to avoid influencing optimisations */
exp
diaginfo_exp(exp e)
{
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
	ans->last = false;
	IGNORE refactor(e, e);

	return ans;
}

exp
relative_exp(shape s, token t)
{
	exp id;
	tokval tv;

	id = me_startid(s, f_make_value(s), 0);
	tv.tk_exp = me_obtain(id);
	tv = apply_tok(t, keep_place(), SORT_EXP, &tv);
	IGNORE me_complete_id(id, hold_refactor(tv.tk_exp));

	return hold(id);
}

