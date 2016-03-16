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
#include "diagglob.h"

static int clean_copy = 0; /* set by copy_dg_separate */

int doing_inlining = 0;

dg_info current_dg_info = NULL; /* needed when coding extra_diags */
exp current_dg_exp      = NULL; /* needed when coding extra_diags */

short_sourcepos no_short_sourcepos;

#define DG_CLUMP_SIZE 50	/* Generate a clump of dg_name etc together */
#define FILE_CLUMP_SIZE 5


/* These have similar size */
typedef union {
	struct dg_name_t name;
	struct dg_type_t type;
	struct dg_info_t inf;
	struct dg_more_t more;
} dg_union;

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
	ans = &(next_dg++)->name;
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

	ans = &(next_dg++)->type;
	ans->key      = k;
	ans->outref.k = NO_LAB;
	ans->more     = (dg_more_name)0;

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

	ans = &(next_dg++)->inf;
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

	name->more       = more = &(next_dg++)->more;
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
extend_dg_type(dg_type tp)
{
	dg_more_name more;

	if (!dg_clump_left) {
		make_dg_clump();
	}

	dg_clump_left--;

	tp->more         = more = &(next_dg++)->more;
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

dg_tag
gen_dg_tag(void)
{
	dg_tag tag = xcalloc(1, sizeof(dgtag_struct));
	init_dgtag(tag);
	return tag;
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
	ans->data.t_qual.q_key   = qual;
	ans->data.t_qual.type    = type;
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
	ans->data.t_bitf.sha      = sha;
	ans->data.t_bitf.bv       = bv;
	ans->data.t_bitf.another  = bf_list;

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
	ans = next_file++;
	ans->file_dat = dat;
	ans->file_host = host;
	ans->file_path = path;
	ans->file_name = name;
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

			t = bro(t);
		}
	}
}

exp
diaginfo_exp(exp e)
{
	exp ans;

	/* mark external names to avoid influencing optimisations */

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

void
diag_kill_id(exp id)
{
	exp t;

	for (t = pt(id); t; t = pt(t)) {
		if (!isdiaginfo(t)) {
			error(ERR_INTERNAL, "bad kill ident");
		}
		setdiscarded(t);
	}

	son(id) = NULL;
}

/* nm is defining reference for its obtain value */
void
set_obj_ref(dg_name nm)
{
	exp e = nm->data.n_obj.obtain_val;
	while (e && (e->tag == hold_tag || e->tag == cont_tag ||
	             e->tag == reff_tag)) {
		e = son(e);
	}

	if (e && e->tag == name_tag && isglob(son(e)) &&
	    !(brog(son(e))->dg_name)) {
		brog(son(e))->dg_name = nm;
	}
}

/* e is name_tag for required object */
static int
matched_obj(exp e, dg_name nm, dg_tag *refans)
{
	exp x;

	if (nm->key != DGN_OBJECT) {
		return 0;
	}

	x = nm->data.n_obj.obtain_val;
	while (x && (x->tag == hold_tag || x->tag == cont_tag ||
	             x->tag == reff_tag)) {
		x = son(x);
	}

	if ((x) && x->tag == name_tag && son(x) == son(e)) {
		if ((no(x) <= no(e)) &&
		    (no(x) + shape_size(sh(x)) >= no(e) + shape_size(sh(e)))) {
			if (!nm->more || !nm->more->this_tag) {
				IGNORE f_dg_tag_name(gen_dg_tag(), nm);
			}

			*refans = nm->more->this_tag;
			return 1;
		}
	}

	return 0;
}

static int
end_ref_search(exp e, dg_info d, dg_tag *refans)
{
	dg_name pm;

	while (d && d->key != DGA_NAME && d->key != DGA_INL_CALL &&
	       d->key != DGA_PARAMS) {
		d = d->more;
	}

	if (!d) {
		return 0;
	}

	if (d->more && end_ref_search(e, d->more, refans)) {
		return 1;
	}

	if (d->key == DGA_NAME) {
		return matched_obj(e, d->data.i_name.dname, refans);
	}

	/* otherwise inlined call or outermost proc */
	if (d->key == DGA_PARAMS) {
		pm = d->data.i_param.args;
	} else {
		pm = d->data.i_inl.args;
	}

	while (pm && !matched_obj(e, pm, refans)) {
		pm = pm->next;
	}

	return 1; /* we don't search the caller environment */
}

/* e is name_tag for required object */
static dg_tag
find_obj_ref(exp contex, exp e)
{
	dg_tag ans = NULL;

	while ((contex->tag != ident_tag || !isglob(contex)) &&
	       (!dgf(contex) || !end_ref_search(e, dgf(contex), &ans))) {
		contex = father(contex);
	}

	if (!ans) {
		dg_compilation cl;
		dg_name dl;

		for (cl = all_comp_units; cl; cl = cl->another) {
			for (dl = cl->dn_list; dl; dl = dl->next) {
				if (matched_obj(e, dl, &ans)) {
					return ans;
				}
			}
		}
	}

	return ans;
}

static void
check_const_exp(exp e)
{
	if (!e) {
		return;
	}

	if (e->tag != hold_tag || son(e)->tag != val_tag) {
		error(ERR_INTERNAL, "diag_type may need copying");
	}

	/* copy within type, unless all name_tags are uncopied */
}

static void
check_const_type(dg_type t)
{
	int i;

	switch (t->key) {
	case DGT_QUAL:
		check_const_type(t->data.t_qual.type);
		break;

	case DGT_CONS:
		check_const_type(t->data.t_cons.type);
		break;

	case DGT_ARRAY:
		check_const_type(t->data.t_arr.elem_type);
		check_const_exp(t->data.t_arr.stride);

		for (i = 0; i < t->data.t_arr.dims.len; i++) {
			dg_dim *dim = &(t->data.t_arr.dims.array[i]);
			if (dim->d_key != DG_DIM_TYPE) {
				if (!dim->low_ref) {
					check_const_exp(dim->lower.exp);
				}
				if (!dim->hi_ref) {
					check_const_exp(dim->upper.exp);
				}
			}
		}
		break;

	case DGT_SUBR:
		check_const_type(t->data.t_subr.d_type);
		if (!t->data.t_subr.low_ref) {
			check_const_exp(t->data.t_subr.lower.exp);
		}
		if (!t->data.t_subr.hi_ref) {
			check_const_exp(t->data.t_subr.upper.exp);
		}
		break;

	case DGT_STRUCT:
		for (i = 0; i < t->data.t_struct.u.fields.len; i++) {
			dg_classmem *f = &(t->data.t_struct.u.fields.array[i]);
			check_const_type(f->d.cm_f.f_type);
			check_const_exp(f->d.cm_f.f_offset);
		}
		break;

	case DGT_PROC:
		if (t->data.t_proc.res_type) {
			check_const_type(t->data.t_proc.res_type);
		}

		for (i = 0; i < t->data.t_proc.params.len; i++) {
			dg_param *p = &(t->data.t_proc.params.array[i]);
			check_const_type(p->p_type);
		}
		break;

	case DGT_STRING:
		check_const_exp(t->data.t_string.lb);
		check_const_exp(t->data.t_string.length);
		break;

	case DGT_CLASS:
	case DGT_PMEM:
		error(ERR_INTERNAL, "uncopyable type");
		break;

	default:
		break;
	}
}

static int inner_copy = 0;

static dg_name
new_copy_name(dg_name d)
{
	dg_name new = new_dg_name(d->key);
	if (d->more && d->more->this_tag) {
		IGNORE f_dg_tag_name(gen_dg_tag(), new);

		if (d->more->this_tag->copy) {
			error(ERR_INTERNAL, "bad copy_diagname");
		}

		if (inner_copy) {
			d->more->this_tag->copy = new->more->this_tag;
		}
	}

	if (doing_inlining) {
		if (!d->more || (!d->more->this_tag && !d->more->inline_ref)) {
			IGNORE f_dg_tag_name(gen_dg_tag(), d);
		}

		if (!d->more->inline_ref) {
			d->more->inline_ref = d->more->this_tag;
		}
	}

	new->idname = d->idname;
	new->whence = d->whence;

	if (d->more && (d->more->inline_ref || d->more->refspec || d->more->acc ||
	                d->more->isconst)) {
		extend_dg_name(new);
		new->more->inline_ref = d->more->inline_ref;
		new->more->refspec    = d->more->refspec;
		new->more->acc        = d->more->acc;
		new->more->isconst    = d->more->isconst;
	}

	return new;
}

static int
is_copied(exp e)
{
	if (!e) {
		return 0;
	}

	switch (e->tag) {
	case name_tag:
		return copying(son(e));

	case hold_tag:
	case cont_tag:
	case contvol_tag:
	case reff_tag:
	case chvar_tag:
	case chfl_tag:
		return is_copied(son(e));

	case val_tag:
	case null_tag:
	case real_tag:
	case string_tag:
		return 0;

	default:
		error(ERR_INTERNAL, "unexpected copy_diagname obtain_val");
	}

	return 0;
}

/* need (new dg_name) if copying a name_list, or if inlining */
static dg_name
copy_diagname(dg_name d, exp var, exp lab, int need)
{
	dg_name new = d;

	switch (d->key) {
	case DGN_OBJECT: {
		int moved = is_copied(d->data.n_obj.obtain_val);
		check_const_type(d->data.n_obj.type);
		if (need || moved) {
			new = new_copy_name(d);
			new->data.n_obj = d->data.n_obj;
#if 0
			if (moved)
#endif
				new->data.n_obj.obtain_val =
				    copy_res(d->data.n_obj.obtain_val, var,
				             lab);
		}
		break;
	}

	case DGN_TYPE:
		check_const_type(d->data.n_type.raw);
		break;

	case DGN_IMPORT:
		if (d->data.n_imp.i_type) {
			check_const_type(d->data.n_imp.i_type);
		}
		break;

	default:
		error(ERR_INTERNAL, "unexpected copy_diagname");
	}

	return new;
}

static void update_detch_copy(detch_info *dl, int update);

static void
update_diag_copy(exp e, dg_info d, int update)
{
	if (!e) {
		return;
	}

	if (!d && e) {
		switch (e->tag) {
		case name_tag:
		case env_offset_tag:
		case general_env_offset_tag:
			break;

		default: {
			exp s;

			for (s = son(e); s; s = bro(s)) {
				update_diag_copy(s, dgf(s), update);
				if (s->last) {
					break;
				}
			}
		}
		}

		return;
	}

	if (update) {
		/* use all dg_tag copies */
		switch (d->key) {
		case DGA_INL_RES: {
			dg_tag ic = d->data.i_res.call;
			if (ic->copy) {
				d->data.i_res.call = ic->copy;
			}
			break;
		}

		case DGA_BEG: {
			dg_tag tag = d->data.i_tag;
			if (tag->copy) {
				d->data.i_tag = tag->copy;
			}
			break;
		}

		case DGA_RVS: {
			dg_tag tag = d->data.i_rvs.u.tag;
			if (tag && tag->copy) {
				d->data.i_rvs.u.tag = tag->copy;
			}
			break;
		}

		case DGA_DETCH:
			update_detch_copy(d->data.i_detch.dl, 1);
			break;

		case DGA_MOVD:
		case DGA_HOIST: {
			dg_tag tag = d->data.i_movd.tag;

			if (tag && tag->copy) {
				d->data.i_movd.tag = tag->copy;
			}

#if 1
			if (d->key == DGA_MOVD && !d->more) {
				error(ERR_INTERNAL, "lost movd?");
			}
#endif
			break;
		}

		default:
			break;
		}
	} else {
		/* remove all dg_tag copies */
		if (d->this_tag && (doing_inlining || clean_copy)) {
			d->this_tag->copy = NULL;
		}

		/* otherwise keep record for code movement */
		switch (d->key) {
		case DGA_NAME: {
			dg_name a = d->data.i_name.dname;
			if (a->more && a->more->this_tag) {
				a->more->this_tag->copy = NULL;
			}
			break;
		}

		case DGA_INL_CALL: {
			dg_name a;

			for (a = d->data.i_inl.args; a; a = a->next) {
				if (a->more && a->more->this_tag) {
					a->more->this_tag->copy = NULL;
				}
			}
			break;
		}

		case DGA_X_CATCH: {
			dg_name a = d->data.i_catch.ex;
			if (a->more && a->more->this_tag) {
				a->more->this_tag->copy = NULL;
			}
			break;
		}

		case DGA_DETCH:
			if (doing_inlining || clean_copy) {
				update_detch_copy(d->data.i_detch.dl, 0);
			}
			break;

#if 1
		case DGA_MOVD:
			if (!d->more) {
				error(ERR_INTERNAL, "lost movd?");
			}
			break;
#endif

		default:
			break;
		}
	}

	update_diag_copy(e, d->more, update);
}

static void
update_detch_copy(detch_info *dl, int update)
{
	while (dl) {
		if (dl->info) {
			update_diag_copy(NULL, dl->info, update);
		}

		if (update && dl->tag && dl->tag->copy) {
			dl->tag = dl->tag->copy;
		}

		if (dl->sub) {
			update_detch_copy(dl->sub, update);
		}

		dl = dl->next;
	}
}

static detch_info *copy_detch_tree(detch_info *dl);

static dg_info
copy_dg_info(dg_info d, exp var, exp lab, int doing_exp_copy)
{
	dg_info new = new_dg_info(d->key);

	if (d->this_tag) {
		IGNORE f_make_tag_dg(gen_dg_tag(), new);
		if (d->this_tag->copy) {
			error(ERR_INTERNAL, "bad copy_dg_info");
		}

		if (inner_copy) {
			d->this_tag->copy = new->this_tag;
		}
	}

	switch (new->key) {
	case DGA_PARAMS:
		new->data.i_param = d->data.i_param;
		break;

	case DGA_COMP:
		new->data.i_comp = d->data.i_comp;
		break;

	case DGA_SRC:
		new->data.i_src = d->data.i_src;
		break;

	case DGA_LAB:
	case DGA_EXTRA:
	case DGA_SCOPE:
		new->data.i_scope = d->data.i_scope;
		break;

	case DGA_NAME:
		new->data.i_name = d->data.i_name;
		if (doing_exp_copy) {
			/* a named item might be copied */
			new->data.i_name.dname =
			    copy_diagname(d->data.i_name.dname, var, lab,
			                  doing_inlining);
		}
		break;

	case DGA_WITH:
		new->data.i_with = d->data.i_with;
		check_const_type(d->data.i_with.w_type);
		if (doing_exp_copy) {
			new->data.i_with.w_exp = copy_res(d->data.i_with.w_exp,
			                                  var, lab);
		}
		break;

	case DGA_CALL:
		new->data.i_call = d->data.i_call;
		break;

	case DGA_INL_CALL: {
		dg_name a = d->data.i_inl.args;
		dg_name *b = &(new->data.i_inl.args);
		new->data.i_inl = d->data.i_inl;

		if (doing_exp_copy) {
			while (a) {
				*b = copy_diagname(a, var, lab, 1);
				a = a->next;
				b = &((*b)->next);
			}
		}

		d->data.i_inl.proc->any_inl = 1;
		break;
	}

	case DGA_INL_RES:
		new->data.i_res = d->data.i_res;
		new->data.i_res.call = d->data.i_res.call;
		break;

	case DGA_X_TRY:
		new->data.i_try = d->data.i_try;
		break;

	case DGA_X_CATCH:
		new->data.i_catch = d->data.i_catch;

		if (doing_exp_copy) {
			new->data.i_catch.ex =
			    copy_diagname(d->data.i_catch.ex, var, lab,
			                  doing_inlining);
		}
		break;

	case DGA_X_RAISE:
		new->data.i_raise = d->data.i_raise;

		if (d->data.i_raise.x_type) {
			check_const_type(d->data.i_raise.x_type);
		}

		if (d->data.i_raise.x_val && doing_exp_copy) {
			new->data.i_raise.x_val =
			    copy_res(d->data.i_raise.x_val, var, lab);
		}
		break;

	case DGA_BRANCH:
		new->data.i_brn = d->data.i_brn;
		break;

	case DGA_TEST:
	case DGA_JUMP:
		new->data.i_tst = d->data.i_tst;
		break;

	case DGA_LJ:
		new->data.i_lj = d->data.i_lj;
		break;

	case DGA_BEG:
		new->data.i_tag = d->data.i_tag;
		break;

	case DGA_DEST:
		new->data.i_dest = d->data.i_dest;
		break;

	case DGA_RVS:
		new->data.i_rvs = d->data.i_rvs;
		break;

	case DGA_BAR:
		new->data.i_bar = d->data.i_bar;
		break;

	case DGA_DETCH:
		new->data.i_detch = d->data.i_detch;

		if (doing_exp_copy) {
			new->data.i_detch.dl =
			    copy_detch_tree(new->data.i_detch.dl);
		}
		break;

	case DGA_MOVD:
	case DGA_HOIST:
		new->data.i_movd = d->data.i_movd;

#if 1
		if (d->key == DGA_MOVD && !d->more) {
			error(ERR_INTERNAL, "lost movd?");
		}
#endif
		break;

	case DGA_OPTIM:
		new->data.i_optim = d->data.i_optim;
		break;

	case DGA_REMVAL:
		new->data.i_remval = d->data.i_remval;
		if (copying(son(son(d->data.i_remval.var)))) {
			new->data.i_remval.var = copy(d->data.i_remval.var);
		}
		break;

	default:
		error(ERR_INTERNAL, "copy_diaginfo incomplete");
	}

	return new;
}

static detch_info *
copy_detch_tree(detch_info *dl)
{
	detch_info *ans = xcalloc(1, sizeof(detch_info));

	*ans = *dl;

	if (dl->info) {
		ans->info = copy_dg_info(dl->info, NULL, NULL, 1);
	}

	if (dl->sub) {
		ans->sub = copy_detch_tree(dl->sub);
	}

	if (dl->next) {
		ans->next = copy_detch_tree(dl->next);
	}

	return ans;
}

exp
copy_res_diag(exp e, dg_info d, exp var, exp lab)
{
	int ic = inner_copy;
	dg_info new;
	exp ans;

	if (!d /* ||
		  (e->tag == name_tag && isdiaginfo(e) && !doing_inlining && !clean-copy) */
	    /* only one defining name tag */
	   ) {
		dg_info all = dgf(e);
		dgf(e) = NULL;
		ans = copy_res(e, var, lab);
		dgf(e) = all;
		dgf(ans) = combine_diaginfo(dgf(ans), d);
		return ans;
	}

	if (d->key == DGA_PARAMS) {
		return copy_res_diag(e, d->more, var, lab);
	}

	inner_copy = 1;
	new = copy_dg_info(d, var, lab, 1);
	ans = copy_res_diag(e, d->more, var, lab);

	new->more = dgf(ans);
	dgf(ans) = new;
	if (!ic) {
		inner_copy = 0;
		update_diag_copy(ans, dgf(ans), 1);
		update_diag_copy(e, dgf(e), 0);
	}

	return ans;
}

/* called by copy_res when inlining */
exp
diag_hold_refactor(exp e)
{
	int was_inlining = doing_inlining;
	exp hc;

	doing_inlining = 0;
	hc = hold_refactor(e);
	doing_inlining = was_inlining;

	return hc;
}

static dg_tag current_inliner = NULL;

static int
ref_param(exp e)
{
	switch (e->tag) {
	case name_tag:
	case cont_tag:
	case chvar_tag:
	case chfl_tag:
		return ref_param(son(e));

	case ident_tag:
		if (isparam(e)) {
			return 1;
		}

		if (dgf(e) || isglob(e)) {
			return 0;
		}
		return ref_param(son(e));

	default:
		return 0;
	}
}

void
start_diag_inlining(exp e, dg_name dn)
{
	exp body = son(e);
	dg_info di;
	int any_inl;
	dg_name_list args = NULL;

	if (!dn || dn->key != DGN_PROC) {
		return;
	}

	while (body->tag == ident_tag &&
	       (isparam(body) || (!dgf(body) && ref_param(son(body))))) {
		body = bro(son(body));
	}

	di = dgf(body);
	if (di && di->key == DGA_PARAMS) {
		dn->data.n_proc.params = di;
		args = di->data.i_param.args;
	}

	if (!dn->more || !dn->more->this_tag) {
		IGNORE f_dg_tag_name(gen_dg_tag(), dn);
	}

	any_inl = dn->more->this_tag->any_inl;
	/* for copying only */
	di = f_inline_call_dg(dn->more->this_tag, args, no_nat_option);
	dn->more->this_tag->any_inl = any_inl;
	current_inliner = gen_dg_tag();
	di = f_make_tag_dg(current_inliner, di);
	di->more = dgf(body);
	dgf(body) = di;
}

void
end_diag_inlining(exp e, dg_name dn)
{
	exp body;

	if (!dn || dn->key != DGN_PROC) {
		return;
	}

	body = son(e);
	while (body->tag == ident_tag &&
	       (isparam(body) || (!dgf(body) && ref_param(son(body))))) {
		body = bro(son(body));
	}

	dgf(body) = dgf(body)->more;
	current_inliner = 0;
}

dg_info
combine_diaginfo(dg_info d1, dg_info d2)
{
	dg_info d;

	if (!d1) {
		return d2;
	}

	if (!d2) {
		return d1;
	}

	d = copy_dg_info(d1, NULL, NULL, 0);
	d->more = combine_diaginfo(d1->more, d2);

	return d;
}

void
diag_inline_result(exp e)
{
	if (current_inliner) {
		dgf(e) = f_inline_result_dg(current_inliner);
	}
}

/*
 * for use before replace (whole, comp, x) when
 * whole is replaced by its only remaining component
 */
void
dg_whole_comp(exp whole, exp comp)
{
	if (dgf(whole)) {
		dg_info *next = &(dgf(whole)->more);

		while (*next) {
			next = &((*next)->more);
		}

		*next = dgf(comp);
		dgf(comp) = dgf(whole);
	}
}

/* as dg_whole_comp, but remove DGA_CALL */
void
dg_complete_inline(exp whole, exp comp)
{
	if (dgf(whole)) {
		int rem = 0;
		dg_info *next = &(dgf(whole)->more);

		while (*next) {
			if ((*next)->key == DGA_CALL) {
				*next = (*next)->more;
				rem = 1;
			} else {
				next = &((*next)->more);
			}
		}

		if (rem) {
			/* we must find DGA_INL_CALL to replace the DGA_CALL */
			while (!dgf(comp)) {
				if (comp->tag == ident_tag) {
					comp = bro(son(comp));
				} else if (comp->tag == cond_tag) {
					comp = son(comp);
				} else {
					break;
				}
			}

			if (!dgf(comp) || dgf(comp)->key != DGA_INL_CALL) {
				error(ERR_INTERNAL, "lost inline call movement");
			}
		}

		*next = dgf(comp);
		dgf(comp) = dgf(whole);
	}
}

/*
 * e is exp under consideration.
 * dx is (ref) dg_info under consideration
 * part of dgf(e); this info being removed.
 * reason is enumerated reason for debugger.
 * descend is nonzero if son(e) to be processed.
 * reuse is nonzero if simple movement (e remains in use).
 * opt_ref for reference to complex optimisation info.
 */
static detch_info *
gather_detch(exp e, dg_info *dx, int reason, int descend, int reuse,
             dg_tag opt_ref)
{
	dg_info d = *dx;
	detch_info *ans;
	exp s;

	if (d) {
		if (d->key == DGA_DETCH) {
			/* previous detachment */
			detch_info *more = gather_detch(e, &(d->more), reason,
			                                descend, reuse,
			                                opt_ref);
			detch_info **ptr;
			if (d->data.i_detch.posn < 0) {
				ans = d->data.i_detch.dl;
			} else {
				ans = more;
				more = d->data.i_detch.dl;
			}

			for (ptr = &ans; *ptr; ptr = &((*ptr)->next))
				;

			*ptr = more;
			return ans;
		}

		if (d->key == DGA_MOVD) {
			/* previous simple movement */
			if (!d->more) {
				error(ERR_INTERNAL, "lost movd?");
			}

			if (reason < d->data.i_movd.reason) {
				d->data.i_movd.reason = reason;
				d->data.i_movd.tag = opt_ref;
			}

			if (reuse) {
				return NULL;
			}

			d->data.i_movd.lost = 1;
			if (d->more->key == DGA_INL_CALL) {
				/* ignore internals */
				*dx = NULL;
				return NULL;
			}

			*dx = d->more->more;
			return gather_detch(e, dx, reason, descend, reuse, opt_ref);
		}

		ans = xcalloc(1, sizeof(detch_info));
		ans->next = NULL;
		if (d->key == DGA_INL_CALL) {
			ans->sub = NULL;
		} else {
			ans->sub = gather_detch(e, &(d->more), reason, descend, reuse, opt_ref);
		}

		ans->why = reason;
		if (reuse) {
			d = new_dg_info(DGA_MOVD);
			d->data.i_movd.reason = reason;
			d->data.i_movd.lost   = 0;
			d->data.i_movd.tag    = opt_ref;
			d->data.i_movd.lo_pc  = 0;
			d->more = *dx;
			*dx = d;

			if (!d->more) {
				error(ERR_INTERNAL, "lost movd?");
			}

			IGNORE f_make_tag_dg(gen_dg_tag(), d);
			ans->info = NULL;
			ans->tag = d->this_tag;
		} else {
			/* original about to be discarded */
			ans->info = d;
			d->more = NULL;
			ans->tag = opt_ref;
		}

		return ans;
	}

	if (extra_diags && reuse &&
	    (e->tag == apply_tag || e->tag == apply_general_tag)) {
		/* need info to modify in case of subsequent inlining */
		dg_info x = dgf(e);

		while (x && x->key != DGA_CALL) {
			x = x->more;
		}

		if (!x) {
			*dx = d = new_dg_info(DGA_CALL);
			d->data.i_call.clname = NULL;
			d->data.i_call.pos = no_short_sourcepos;
			d->data.i_call.ck = 0;
			return gather_detch(e, dx, reason, descend, reuse, opt_ref);
		}
	}

	if (!descend) {
		return NULL;
	}

	s = son(e);
	if (e->tag == name_tag || e->tag == env_size_tag ||
	    e->tag == env_offset_tag || !s) {
		return NULL;
	}

	ans = gather_detch(s, &(dgf(s)), reason, descend, reuse, opt_ref);
	if (e->tag != case_tag) {
		detch_info **ptr;

		while (!s->last) {
			s = bro(s);

			for (ptr = &ans; *ptr; ptr = &((*ptr)->next))
				;

			*ptr = gather_detch(s, &(dgf(s)), reason, descend, reuse, opt_ref);
		}
	}

	return ans;
}

static void
dg_detach(exp old, exp keep, int position, int reason, int descend, int reuse,
          dg_tag opt_ref)
{
	detch_info *info = gather_detch(old, &(dgf(old)), reason, descend, reuse, opt_ref);

	if (info) {
		dg_info newd = new_dg_info(DGA_DETCH);
		newd->data.i_detch.posn = position;
		newd->data.i_detch.dl   = info;
		newd->more = dgf(keep);
		dgf(keep) = newd;
	}
}

/* mark removal of dead code following prev */
void
dg_dead_code(exp dead, exp prev)
{
	dg_detach(dead, prev, +1, DGD_DEAD, 1, 0, NULL);
}

/* mark removal of redundant code before next */
void
dg_rdnd_code(exp rdnd, exp next)
{
	dg_detach(rdnd, next, -1, DGD_RDND, 1, 0, NULL);
}

/* incorporated part in whole evaluated constant*/
void
dg_detach_const(exp part, exp whole)
{
	dg_detach(part, whole, 0, DGD_CNST, 0, 0, NULL);
}

/* mark movement of inner into outer */
void
dg_restruct_code(exp outer, exp inner, int posn)
{
	dg_detach(inner, outer, posn, DGD_MOVD, 1, 1, NULL);
}

/* mark removal of propagated assignment */
void
dg_rem_ass(exp ass)
{
	exp val = bro(son(ass));

	if (son(ass)->tag == name_tag &&
	    (val->tag == val_tag || val->tag == real_tag ||
	     val->tag == null_tag)) {
		dg_info h = dgf(val);
		dg_info *dx = &(dgf(ass));
		dg_info rem = new_dg_info(DGA_REMVAL);
		rem->data.i_remval.var = hold(me_obtain(son(son(ass))));
		setisdiaginfo(son(rem->data.i_remval.var));
		--no(son(son(rem->data.i_remval.var)));
		dgf(val) = NULL;
		rem->data.i_remval.val = copy(val);
		dgf(val) = h;
		rem->data.i_remval.lo_pc = 0;
		rem->more = NULL;

		while (*dx) {
			dx = &((*dx)->more);
		}

		*dx = rem;
	}

	dg_detach(ass, bro(son(ass)), -1, DGD_REM, 0, 0, NULL);
}

void
strip_dg_context(exp e)
{
	dg_info d = dgf(e);

	while (d && (d->key == DGA_DETCH || d->key == DGA_NAME)) {
		d = d->more;
	}

	dgf(e) = d;
}

static dg_info *
after_dg_context(exp e)
{
	dg_info *dx = &(dgf(e));

	while (*dx && ((*dx)->key == DGA_DETCH || (*dx)->key == DGA_NAME)) {
		dx = &((*dx)->more);
	}

	return dx;
}

/* old replaced by nm */
void
dg_extracted(exp nm, exp old)
{
	dg_info con_start = dgf(old);
	dg_info con_end = (strip_dg_context(old), dgf(old));
	dg_info *dx;

	if (nm->tag != name_tag ||
	    (dx = after_dg_context(son(nm)), !(*dx)->this_tag)) {
		error(ERR_INTERNAL, "make_optim error");
		return;
	}

	dg_detach(old, nm, -1, DGD_EXTRACT, 1, 0, (*dx)->this_tag);
	if (con_start != con_end) {
		dg_info d;

		for (d = con_start; d->more != con_end; d = d->more)
			;

		d->more = dgf(nm);
		dgf(nm) = con_start;
	}
}

/*
 * gather into obs, all objects accessed within e that are
 * external to whole, distinguishing those that may be altered
 */
static void
gather_objects(exp e, exp whole, objset **obs, int ass)
{
	exp t;

	switch (e->tag) {
	case name_tag:
		if (!intnl_to(whole, son(e))) {
			dg_tag tag = find_obj_ref(whole, e);
			if (tag) {
				objset *x;

				for (x = *obs; x && x->tag != tag; x = x->next)
					;

				if (!x) {
					x = xcalloc(1, sizeof(objset));
					x->tag  = tag;
					x->ass  = ass;
					x->next = *obs;
					*obs = x;
				} else if (ass) {
					x->ass = 1;
				}
			}
		}
		return;

	case ident_tag:
		/* definition part no_ass */
		gather_objects(bro(son(e)), whole, obs, ass);
		break;

	case seq_tag:
		/* statements no_ass */
		gather_objects(bro(son(e)), whole, obs, ass);
		e = son(e);
		break;

	case cond_tag:
		gather_objects(son(e), whole, obs, ass);
		gather_objects(bro(son(e)), whole, obs, ass);
		return;

	case labst_tag:
		gather_objects(bro(son(e)), whole, obs, ass);
		return;

	case rep_tag:
		gather_objects(son(e), whole, obs, 0);
		gather_objects(bro(son(e)), whole, obs, ass);
		return;

	case solve_tag:
		for (t = son(e); ; t = bro(t)) {
			gather_objects(t, whole, obs, ass);
			if (t->last) {
				return;
			}
		}

	case ass_tag:
	case assvol_tag:
		gather_objects(son(e), whole, obs, 1);
		gather_objects(bro(son(e)), whole, obs, 0);
		return;

	case addptr_tag:
		gather_objects(son(e), whole, obs, ass);
		gather_objects(bro(son(e)), whole, obs, 0);
		return;

	case env_offset_tag:
		return;

	default:
		break;
	}

	/* remaining cases all no_ass */
	for (t = son(e); t; t = bro(t)) {
		gather_objects(t, whole, obs, 0);
		if (t->last) {
			return;
		}
	}
}

void
make_optim_dg(int reason, exp e)
{
	dg_info sub = new_dg_info(DGA_HOIST);
	exp konst = son(e);
	exp body = bro(konst);
	dg_info *dx;
	dgf(e) = dgf(body);
	dgf(body) = NULL;
	dx = after_dg_context(e);

	if (!*dx || (*dx)->key != DGA_OPTIM ||
	    (*dx)->data.i_optim.reason != reason) {
		dg_info ans = new_dg_info(DGA_OPTIM);
		ans->data.i_optim.reason = reason;
		ans->data.i_optim.objs = NULL;
		ans->data.i_optim.lo_pc = ans->data.i_optim.hi_pc = 0;
		IGNORE f_make_tag_dg(gen_dg_tag(), ans);
		ans->more = *dx;
		*dx = ans;
	}

	sub->data.i_movd.reason = reason;
	sub->data.i_movd.lost   = 0;
	sub->data.i_movd.tag    = (*dx)->this_tag;
	sub->data.i_movd.lo_pc  = sub->data.i_movd.hi_pc = 0;
	sub->more = dgf(konst);

	dgf(konst) = sub;
	gather_objects(konst, konst, &((*dx)->data.i_optim.objs), 0);
}

/*
 * Used instead of copy if the original may still be in use.
 * This resets tracing of dg_tag copies
 */
exp
copy_dg_separate(exp e)
{
	exp ans;

	clean_copy = 1;
	ans = copy(e);
	clean_copy = 0;

	return ans;
}

exp
relative_exp(shape s, token t)
{
	exp id = me_startid(s, f_make_value(s), 0);
	tokval tv;

	tv.tk_exp = me_obtain(id);
	tv = apply_tok(t, keep_place(), SORT_EXP, &tv);

	IGNORE me_complete_id(id, hold_refactor(tv.tk_exp));

	return hold(id);
}

