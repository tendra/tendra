/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>

#include "ctype_ops.h"
#include "graph_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include "access.h"
#include "chktype.h"
#include "class.h"
#include "declare.h"
#include "initialise.h"
#include "merge.h"
#include "namespace.h"
#include "redeclare.h"
#include "token.h"


/*
    This flag is set to true to indicate that name merging is taking
    place.
*/

int force_merge = 0;


/*
    This routine checks whether the classes ct and cs are layout compatible,
    i.e. they have the same member types and accesses.
*/

int
compatible_class(CLASS_TYPE ct, CLASS_TYPE cs)
{
	GRAPH gt, gs;
	MEMBER mt, ms;
	BASE_TYPE kt, ks;
	NAMESPACE nt, ns;
	LIST(GRAPH) bt, bs;

	/* Check for obvious equality */
	if (eq_ctype(ct, cs)) {
		return 1;
	}

	/* Check class keys */
	kt = find_class_key(ct);
	ks = find_class_key(cs);
	if (!equal_key(kt, ks)) {
		return 0;
	}

	/* Check base classes */
	gt = DEREF_graph(ctype_base(ct));
	gs = DEREF_graph(ctype_base(cs));
	bt = DEREF_list(graph_tails(gt));
	bs = DEREF_list(graph_tails(gs));
	while (!IS_NULL_list(bt) && !IS_NULL_list(bs)) {
		GRAPH ht = DEREF_graph(HEAD_list(bt));
		GRAPH hs = DEREF_graph(HEAD_list(bs));
		CLASS_TYPE pt = DEREF_ctype(graph_head(ht));
		CLASS_TYPE ps = DEREF_ctype(graph_head(hs));
		DECL_SPEC at = DEREF_dspec(graph_access(ht));
		DECL_SPEC as = DEREF_dspec(graph_access(hs));
		at &= (dspec_access | dspec_virtual);
		as &= (dspec_access | dspec_virtual);
		if (at != as) {
			return 0;
		}
		if (!compatible_class(pt, ps)) {
			return 0;
		}
		bs = TAIL_list(bs);
		bt = TAIL_list(bt);
	}
	if (!EQ_list(bt, bs)) {
		return 0;
	}

	/* Check class members */
	nt = DEREF_nspace(ctype_member(ct));
	mt = DEREF_member(nspace_ctype_first(nt));
	mt = next_data_member(mt, 1);
	ns = DEREF_nspace(ctype_member(cs));
	ms = DEREF_member(nspace_ctype_first(ns));
	ms = next_data_member(ms, 1);
	while (!IS_NULL_member(mt) && !IS_NULL_member(ms)) {
		IDENTIFIER it = DEREF_id(member_id(mt));
		IDENTIFIER is = DEREF_id(member_id(ms));
		TYPE t = DEREF_type(id_member_type(it));
		TYPE s = DEREF_type(id_member_type(is));
		DECL_SPEC at = DEREF_dspec(id_storage(it));
		DECL_SPEC as = DEREF_dspec(id_storage(is));
		at &= dspec_access;
		as &= dspec_access;
		if (at != as) {
			return 0;
		}
		if (!eq_type(t, s)) {
			return 0;
		}
		ms = DEREF_member(member_next(ms));
		ms = next_data_member(ms, 1);
		mt = DEREF_member(member_next(mt));
		mt = next_data_member(mt, 1);
	}
	if (!EQ_member(mt, ms)) {
		return 0;
	}
	return 1;
}


/*
    This routine checks whether the identifiers tid and sid are to be made
    equal by merge_id.  This essentially means that they should be the
    same.
*/

int
merge_type(IDENTIFIER tid, IDENTIFIER sid)
{
	while (!EQ_id(tid, sid)) {
		unsigned tt, ts;
		HASHID tnm, snm;
		NAMESPACE nt, ns;

		/* Check identifiers */
		if (IS_NULL_id(tid)) {
			return 0;
		}
		if (IS_NULL_id(sid)) {
			return 0;
		}
		tt = TAG_id(tid);
		ts = TAG_id(sid);
		if (tt != ts) {
			return 0;
		}

		/* Check identifier names */
		tnm = DEREF_hashid(id_name(tid));
		snm = DEREF_hashid(id_name(sid));
		if (!EQ_hashid(tnm, snm)) {
			return 0;
		}

		/* Check identifier namespaces */
		nt = DEREF_nspace(id_parent(tid));
		ns = DEREF_nspace(id_parent(sid));
		if (EQ_nspace(nt, ns)) {
			return 1;
		}
		if (IS_NULL_nspace(nt)) {
			return 0;
		}
		if (IS_NULL_nspace(ns)) {
			return 0;
		}
		tt = TAG_nspace(nt);
		ts = TAG_nspace(ns);
		if (tt != ts) {
			return 0;
		}
		switch (tt) {
		case nspace_global_tag:
			return 1;
		case nspace_ctype_tag:
		case nspace_named_tag:
		case nspace_unnamed_tag:
			break;
		default:
			return 0;
		}
		tid = DEREF_id(nspace_name(nt));
		sid = DEREF_id(nspace_name(ns));
	}
	return 1;
}


/*
    This routine checks whether the definitions of the objects pid and
    qid and consistent.
*/

static int
consistent_redef(IDENTIFIER pid, IDENTIFIER qid)
{
	int ok = 1;
	switch (TAG_id(pid)) {
	case id_nspace_name_tag: {
		/* Merge namespace definitions */
		NAMESPACE pns = DEREF_nspace(id_nspace_name_defn(pid));
		NAMESPACE qns = DEREF_nspace(id_nspace_name_defn(qid));
		if (IS_nspace_named(pns)) {
			COPY_nspace(id_nspace_name_defn(pid), qns);
			merge_namespaces(qns, pns);
		} else {
			merge_namespaces(NULL_nspace, pns);
		}
		break;
	}
	case id_class_name_tag: {
		BASE_TYPE bt, bs;
		CLASS_TYPE ct, cs;
		NAMESPACE pns, qns;
		TYPE t = DEREF_type(id_class_name_defn(pid));
		TYPE s = DEREF_type(id_class_name_defn(qid));
		while (IS_type_templ(t)) {
			t = DEREF_type(type_templ_defn(t));
		}
		ct = DEREF_ctype(type_compound_defn(t));
		bt = find_class_key(ct);
		pns = DEREF_nspace(ctype_member(ct));
		while (IS_type_templ(s)) {
			s = DEREF_type(type_templ_defn(s));
		}
		cs = DEREF_ctype(type_compound_defn(s));
		bs = find_class_key(cs);
		qns = DEREF_nspace(ctype_member(cs));
		COPY_nspace(ctype_member(ct), qns);
		if (!equal_key(bt, bs)) {
			/* Inconsistent key */
			PTR(LOCATION) loc = id_loc(qid);
			ERROR err = ERR_dcl_type_elab_bad(bt, bs, qid, loc);
			report(crt_loc, err);
		}
		merge_namespaces(qns, pns);
		break;
	}
	case id_variable_tag:
	case id_stat_member_tag:
		ok = 0;
		break;
	}
	return ok;
}


/*
    This routine expands the identifier id read from a spec input file.
    This is necessary because id may still contain pending identifiers.
*/

static void
expand_id(IDENTIFIER id)
{
	DEREF_loc(id_loc(id), crt_loc);
	decl_loc = crt_loc;
	return;
}


/*
    The macro dspec_mask is a mask which gives those declaration specifiers
    which should be the same for all declarations.
*/

#define dspec_mem_func\
   (dspec_virtual | dspec_pure | dspec_explicit | dspec_implicit)

#define dspec_mask\
   (dspec_storage | dspec_access | dspec_language | dspec_mem_func)


/*
    This routine merges the identifier id read from a spec input file
    into the namespace ns.
*/

static void
merge_id(NAMESPACE ns, IDENTIFIER id)
{
	int type;
	HASHID nm;
	MEMBER mem;
	IDENTIFIER pid;

	/* Allow for overloaded functions */
	if (IS_id_function_etc(id)) {
		IDENTIFIER over = DEREF_id(id_function_etc_over(id));
		if (!IS_NULL_id(over)) {
			merge_id(ns, over);
		}
	}

	/* Find previous declaration */
	expand_id(id);
	if (IS_NULL_nspace(ns)) {
		return;
	}
	nm = DEREF_hashid(id_name(id));
	mem = search_member(ns, nm, 1);
	if (is_tagged_type(id)) {
		pid = type_member(mem, 3);
		type = 1;
	} else {
		pid = DEREF_id(member_id(mem));
		type = 0;
	}

	/* Check previous declaration */
	if (!IS_NULL_id(pid)) {
		unsigned tag = TAG_id(id);
		unsigned ptag = TAG_id(pid);
		if (tag == id_stat_mem_func_tag) {
			tag = id_mem_func_tag;
		}
		if (ptag == id_stat_mem_func_tag) {
			ptag = id_mem_func_tag;
		}
		if (tag == ptag) {
			int ok = 1;
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			DECL_SPEC pds = DEREF_dspec(id_storage(pid));
			PTR(TYPE) pt = NULL_ptr(TYPE);
			PTR(TYPE) ps = NULL_ptr(TYPE);
			switch (tag) {
			case id_class_name_tag:
			case id_enum_name_tag:
			case id_class_alias_tag:
			case id_enum_alias_tag:
			case id_type_alias_tag:
				pt = id_class_name_etc_defn(id);
				ps = id_class_name_etc_defn(pid);
				break;
			case id_variable_tag:
			case id_parameter_tag:
			case id_stat_member_tag:
				pt = id_variable_etc_type(id);
				ps = id_variable_etc_type(pid);
				break;
#if 0
			case id_function_tag:
			case id_mem_func_tag:
			case id_stat_mem_func_tag: {
				/* NOT YET IMPLEMENTED - function overloading */
				pt = id_function_etc_type(id);
				ps = id_function_etc_type(pid);
				break;
			}
#endif
			case id_member_tag:
				pt = id_member_type(id);
				ps = id_member_type(pid);
				break;
			case id_enumerator_tag:
				pt = id_enumerator_etype(id);
				ps = id_enumerator_etype(pid);
				break;
			}

			/* Check type compatibility */
			if (!IS_NULL_ptr(pt) && !IS_NULL_ptr(ps)) {
				ERROR err = NULL_err;
				TYPE t = DEREF_type(pt);
				TYPE s = DEREF_type(ps);
				t = expand_type(t, 1);
				s = expand_type(s, 1);
				s = check_compatible(s, t, 0, &err, 1);
				if (!IS_NULL_err(err)) {
					/* Incompatible declaration */
					PTR(LOCATION) ploc = id_loc(pid);
					ERROR err2 =
					    ERR_basic_link_decl_type(pid, ploc);
					err = concat_error(err, err2);
					report(crt_loc, err);
					ok = 0;
				} else {
					COPY_type(pt, t);
					COPY_type(ps, s);
				}
			}

			/* Check declaration specifiers */
			if (ok && (ds & dspec_mask)!= (pds & dspec_mask)) {
				PTR(LOCATION) ploc = id_loc(pid);
				DECL_SPEC st = (ds & dspec_storage);
				DECL_SPEC pst = (pds & dspec_storage);
				if (st != pst) {
					/* Inconsistent linkage */
					ERROR err;
					if (pst & dspec_static) {
						err = ERR_dcl_stc_internal(pid, ploc);
					} else {
						err = ERR_dcl_stc_external(pid, ploc);
					}
					report(crt_loc, err);
				}
				st = (ds & dspec_access);
				pst = (pds & dspec_access);
				if (st != pst) {
					/* Adjust access */
					adjust_access(pid, st, 0);
				}
				st = (ds & dspec_language);
				pst = (pds & dspec_language);
				if (st != pst) {
					/* Inconsistent language */
					string lang =
					    linkage_string(pst, cv_none);
					ERROR err =
					    ERR_dcl_link_lang(pid, lang, ploc);
					report(crt_loc, err);
				}
				st = (ds & dspec_mem_func);
				pst = (pds & dspec_mem_func);
				if (st != pst) {
					/* NOT YET IMPLEMENTED */
					/* EMPTY */
				}
			}

			/* Check for multiple definitions */
			if (pds & dspec_defn) {
				if (ds & dspec_defn) {
					if (!consistent_redef(id, pid) && ok) {
						PTR(LOCATION) ploc =
						    id_loc(pid);
						report(crt_loc, ERR_basic_odr_def(pid, ploc));
					}
				} else {
					id = pid;
				}
			}

		} else {
			/* Redeclared as different type of object */
			PTR(LOCATION) ploc = id_loc(pid);
			report(crt_loc, ERR_basic_odr_diff(pid, ploc));
		}
	}

	/* Set member */
	COPY_nspace(id_parent(id), ns);
	if (type) {
		set_type_member(mem, id);
	} else {
		set_member(mem, id);
	}
	return;
}


/*
    This routine merges the namespace ns with the additional members
    read from a spec input file given by pns.
*/

void
merge_namespaces(NAMESPACE ns, NAMESPACE pns)
{
	MEMBER mem = DEREF_member(nspace_named_etc_first(pns));
	LIST(IDENTIFIER) ids = DEREF_list(nspace_named_etc_extra(pns));
	force_merge++;
	while (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		IDENTIFIER alt = DEREF_id(member_alt(mem));
		if (!IS_NULL_id(id)) {
			merge_id(ns, id);
		}
		if (!IS_NULL_id(alt) && !EQ_id(id, alt)) {
			merge_id(ns, alt);
		}
		mem = DEREF_member(member_next(mem));
	}
	while (!IS_NULL_list(ids)) {
		IDENTIFIER id = DEREF_id(HEAD_list(ids));
		expand_id(id);
		ids = TAIL_list(ids);
	}
	force_merge--;
	return;
}
