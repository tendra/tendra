/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "graph_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "access.h"
#include "chktype.h"
#include "class.h"
#include "derive.h"
#include "function.h"
#include "instance.h"
#include "namespace.h"
#include "predict.h"
#include "redeclare.h"
#include "token.h"


/*
    The flag do_access_checks may be set to false to suppress access
    checking.
*/

int do_access_checks = 1;


/*
    The variable crt_access is used to hold the current access specifier
    during a class definition.  prev_access is used to check for dubious
    base class access specifiers.
*/

DECL_SPEC crt_access = dspec_public;
DECL_SPEC prev_access = dspec_public;


/*
    This routine finds the composite of the access specifiers a and b,
    i.e. if Y is a base class of X of access a, and Z is a base class of
    Y of access b, then the result is the access of Z as a sub-class of X.
    Due to the fact that:

	    dspec_public < dspec_protected < dspec_private

    the composite is just the maximum of the access components of a and b.
*/

DECL_SPEC
join_access(DECL_SPEC a, DECL_SPEC b)
{
	DECL_SPEC p = (a & dspec_access);
	DECL_SPEC q = (b & dspec_access);
	if (p >= q) {
		return p;
	}
	return q;
}


/*
    This routine adjusts the access to the identifier id to the access
    level acc.  expl is true for explicit using and access declarations
    and false for simple redeclarations.
*/

void
adjust_access(IDENTIFIER id, DECL_SPEC acc, int expl)
{
    DECL_SPEC ds = DEREF_dspec(id_storage(id));
    DECL_SPEC pacc = (ds & dspec_access);
    if (pacc && acc != pacc) {
	if (!expl) {
	    /* Access changed by redeclaration */
	    PTR(LOCATION)loc = id_loc(id);
	    report(crt_loc, ERR_class_access_spec_change(id, loc));
	}
	if (acc > pacc) {
	    if (expl) {
		/* Access reduced by using declaration */
		PTR(LOCATION)loc = id_loc(id);
		report(crt_loc, ERR_dcl_nspace_udecl_acc(id, loc));
	    }
	    acc = pacc;
	}
	ds = ((ds & ~dspec_access) | acc);
	COPY_dspec(id_storage(id), ds);
    }
    if (IS_id_function_etc(id) && expl) {
	/* Deal with overloaded functions */
	id = DEREF_id(id_function_etc_over(id));
	if (!IS_NULL_id(id))adjust_access(id, acc, expl);
    }
    return;
}


/*
    This flag is set to true by access_decl.
*/

int have_access_decl = 0;


/*
    This routine adjusts the access of the member id of the current class.
    This is equivalent to a using declaration for id.
*/

IDENTIFIER
access_decl(IDENTIFIER id)
{
	report(crt_loc, ERR_class_access_dcl_using(id));
	have_access_decl = 1;
	id = using_identifier(id);
	return id;
}


/*
    This routine makes the function id into a friend of the class cs.
    The effect of this is to add cs to id's chums list and id to cs's
    pals list.
*/

void
friend_function(CLASS_TYPE cs, IDENTIFIER id, int expl)
{
    if (!IS_NULL_ctype(cs)) {
	IDENTIFIER cid;
	LIST(IDENTIFIER)pl;
	LIST(CLASS_TYPE)fr, fs;

	/* Make cs a pal of id */
	fr = DEREF_list(id_function_etc_chums(id));
	fs = fr;
	while (!IS_NULL_list(fs)) {
	    CLASS_TYPE ct = DEREF_ctype(HEAD_list(fs));
	    if (eq_ctype(ct, cs)) {
		/* id is already a friend of ns */
		if (expl) {
		    ERROR err = ERR_class_friend_dup_func(id, cs);
		    report(crt_loc, err);
		}
		return;
	    }
	    fs = TAIL_list(fs);
	}
	CONS_ctype(cs, fr, fr);
	COPY_list(id_function_etc_chums(id), fr);

	/* Make id a pal of cs */
	pl = DEREF_list(ctype_pals(cs));
	CONS_id(id, pl, pl);
	COPY_list(ctype_pals(cs), pl);

	/* Apply access checks immediately */
	cid = DEREF_id(ctype_name(cs));
	immediate_access(cid, id);
    }
    return;
}


/*
    This routine makes the class cid into a friend of the class cs.  The
    effect of this is to add cs to cid's chums list and cid to cs's pals
    list.
*/

void
friend_class(CLASS_TYPE cs, IDENTIFIER cid, int expl)
{
    if (!IS_NULL_ctype(cs)) {
	ERROR err;
	TYPE t = DEREF_type(id_class_name_etc_defn(cid));
	while (IS_type_templ(t)) {
	    t = DEREF_type(type_templ_defn(t));
	}
	if (IS_type_compound(t)) {
	    CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	    if (eq_ctype(cs, ct)) {
		/* Any class is a friend of itself */
		if (expl) {
		    err = ERR_class_friend_dup_class(ct, cs);
		    report(crt_loc, err);
		}
	    } else {
		IDENTIFIER sid;
		LIST(IDENTIFIER)pl;

		/* Make cs a chum of ct */
		LIST(CLASS_TYPE)fr = DEREF_list(ctype_chums(ct));
		LIST(CLASS_TYPE)fs = fr;
		while (!IS_NULL_list(fs)) {
		    CLASS_TYPE cr = DEREF_ctype(HEAD_list(fs));
		    if (eq_ctype(cr, cs)) {
			/* ct is already a friend of cs */
			if (expl) {
			    err = ERR_class_friend_dup_class(ct, cs);
			    report(crt_loc, err);
			}
			return;
		    }
		    fs = TAIL_list(fs);
		}
		CONS_ctype(cs, fr, fr);
		COPY_list(ctype_chums(ct), fr);

		/* Make ct a pal of cs */
		pl = DEREF_list(ctype_pals(cs));
		CONS_id(cid, pl, pl);
		COPY_list(ctype_pals(cs), pl);

		/* Apply access checks immediately */
		sid = DEREF_id(ctype_name(cs));
		immediate_access(sid, cid);
	    }
	}
    }
    return;
}


/*
    Access control checking cannot be performed immediately because, for
    example, it is not known until the end of a declaration whether that
    declaration represents a friend function.  The list crt_access_list
    is used to store any pending access checks.
*/

ACCESS_LIST crt_access_list = {
	NULL_list(IDENTIFIER), NULL_list(GRAPH),
	NULL_list(int), 0, 0
};


/*
    This routine finds the access level for the members of the class
    namespace ns by the identifier pid (or a base class conversion from
    ns if base is true).  It returns the highest access level greater
    than acc which can be accessed.  It also returns a secondary access
    giving the access to base class members, plus markers for whether
    the access is via the actual class, a derived class or a friend.
*/

static DECL_SPEC
find_access(IDENTIFIER *pid, NAMESPACE ns, DECL_SPEC acc, int base)
{
    NAMESPACE cns;
    CLASS_TYPE ct;
    TYPE t = NULL_type;
    IDENTIFIER id = *pid;

    /* Find the namespace corresponding to id */
    DECL_SPEC ok = (dspec_public | dspec_public2);
    if (IS_NULL_id(id)) {
	    return ok;
    }
    if (IS_id_class_name(id)) {
	cns = find_namespace(id);
    } else {
	cns = DEREF_nspace(id_parent(id));
    }
    if (IS_NULL_nspace(cns)) {
	    return ok;
    }

    /* Map block identifiers to the corresponding function */
    if (IS_nspace_block(cns)) {
	id = DEREF_id(nspace_name(cns));
	cns = DEREF_nspace(id_parent(id));
	*pid = id;
    }

    /* Allow for equal namespaces */
    if (base) {
	ok = (dspec_private | dspec_public2);
    } else {
	ok = (dspec_private | dspec_protected2);
    }
    if (EQ_nspace(cns, ns)) {
	ok |= dspec_defn;
	return ok;
    }
    ct = namespace_class(ns);
    ct = expand_ctype(ct, 2, &t);
    complete_class(ct, 1);

    /* Check access for classes */
    if (IS_nspace_ctype(cns)) {
	LIST(CLASS_TYPE)fr;
	CLASS_TYPE cs = namespace_class(cns);
	if (eq_ctype(cs, ct)) {
	    /* Same class */
	    ok |= dspec_defn;
	    return ok;
	}
	fr = DEREF_list(ctype_chums(cs));
	while (!IS_NULL_list(fr)) {
	    CLASS_TYPE cr = DEREF_ctype(HEAD_list(fr));
	    if (eq_ctype(cr, ct)) {
		/* Friend class */
		ok |= (dspec_defn | dspec_friend);
		return ok;
	    }
	    fr = TAIL_list(fr);
	}
    }

    /* Check for friend functions */
    if (IS_id_function_etc(id)) {
	LIST(CLASS_TYPE)fr;
	fr = DEREF_list(id_function_etc_chums(id));
	while (!IS_NULL_list(fr)) {
	    CLASS_TYPE cr = DEREF_ctype(HEAD_list(fr));
	    if (eq_ctype(cr, ct)) {
		/* Friend function */
		ok |= (dspec_defn | dspec_friend);
		return ok;
	    }
	    fr = TAIL_list(fr);
	}
    }

    /* End here for private members */
    if (acc == dspec_private || base) {
	ok = (dspec_public | dspec_public2);
	return ok;
    }

    /* Check access for derived classes */
    ok = (dspec_protected | dspec_protected2);
    if (IS_nspace_ctype(cns)) {
	LIST(CLASS_TYPE)fr;
	CLASS_TYPE cs = namespace_class(cns);
	GRAPH gr = find_base_class(cs, ct, 0);
	if (!IS_NULL_graph(gr)) {
	    /* Derived class */
	    ok |= dspec_inherit;
	    return ok;
	}
	fr = DEREF_list(ctype_chums(cs));
	while (!IS_NULL_list(fr)) {
	    CLASS_TYPE cr = DEREF_ctype(HEAD_list(fr));
	    gr = find_base_class(cr, ct, 0);
	    if (!IS_NULL_graph(gr)) {
		/* Friend class of derived class */
		ok |= (dspec_inherit | dspec_friend);
		return ok;
	    }
	    fr = TAIL_list(fr);
	}
    }

    /* Check for derived friend functions */
    if (IS_id_function_etc(id)) {
	LIST(CLASS_TYPE)fr;
	fr = DEREF_list(id_function_etc_chums(id));
	while (!IS_NULL_list(fr)) {
	    CLASS_TYPE cr = DEREF_ctype(HEAD_list(fr));
	    GRAPH gr = find_base_class(cr, ct, 0);
	    if (!IS_NULL_graph(gr)) {
		/* Friend function of derived class */
		ok |= (dspec_inherit | dspec_friend);
		return ok;
	    }
	    fr = TAIL_list(fr);
	}
    }

    /* Default access */
    ok = (dspec_public | dspec_public2);
    return ok;
}


/*
    This routine checks whether the access level ok returned by find_access
    is sufficient to access a member of type tag with declaration specifiers
    ds.  It returns true if the access is an error.
*/

static int
compare_access(DECL_SPEC ok, DECL_SPEC ds, unsigned tag, int mem)
{
	int ret = 0;
	DECL_SPEC acc = (ds & dspec_access);
	DECL_SPEC level = (ok & dspec_access);
	if (level < acc) {
		/* Straightforward case */
		ret = 1;
	} else {
		/* Deal with inheritance */
		if (ds & dspec_inherit) {
			DECL_SPEC acc2 = (ds & dspec_access2);
			level = (ok & dspec_access2);
			if (level < acc2) {
				ret = 1;
			}
		}
	}
	if (!ret && !mem) {
		if (tag == id_member_tag || tag == id_mem_func_tag) {
			/* Check for access through derived class */
			if (ok & dspec_inherit) {
				ret = 1;
			}
		}
	}
	return ret;
}


/*
    This routine checks whether the inherited class member pid can be
    accessed by the identifier id.  If so it returns true.  The direct
    cases, such as a member of a derived class accessing a member of a
    base class are handled by the main part of do_member_access, this
    routine deals with the indirect cases such as friends of classes
    intermediate between the base class and the derived class.
*/

static int
inherit_access(IDENTIFIER id, IDENTIFIER pid, int mem)
{
	/* Find inheritance base class */
	unsigned tag = TAG_id(pid);
	IDENTIFIER bid = DEREF_id(id_alias(pid));
	DECL_SPEC acc = DEREF_dspec(id_storage(bid));
	NAMESPACE pns = DEREF_nspace(id_parent(pid));
	NAMESPACE bns = DEREF_nspace(id_parent(bid));
	CLASS_TYPE ct = namespace_class(pns);
	CLASS_TYPE cs = namespace_class(bns);
	GRAPH gr = find_base_class(ct, cs, 0);

	/* Scan through all base classes of ct containing bid */
	while (!IS_NULL_graph(gr)) {
		GRAPH gs = gr;
		while (!IS_NULL_graph(gs)) {
			cs = DEREF_ctype(graph_head(gs));
			if (!eq_ctype(cs, ct)) {
				DECL_SPEC ds, ok;
				ds = DEREF_dspec(graph_access(gr));
				ds = join_access(acc, ds);
				bns = DEREF_nspace(ctype_member(cs));
				ok = find_access(&id, bns, ds, 2);
				if (ok & dspec_defn) {
					/* id is a member or friend of cs */
					if (!compare_access(ok, ds, tag, mem)) {
						/* Can access bid */
						return 1;
					}
				}
			}
			gs = DEREF_graph(graph_up(gs));
		}
		gr = DEREF_graph(graph_equal(gr));
	}
	return 0;
}


/*
    This routine checks the access of the class member pid by the
    identifier id.  It prints an error and returns true if the access
    is illegal.
*/

static int
do_member_access(IDENTIFIER id, IDENTIFIER pid, int mem)
{
	int ret = 0;
	NAMESPACE pns = DEREF_nspace(id_parent(pid));
	DECL_SPEC ds = DEREF_dspec(id_storage(pid));
	DECL_SPEC acc = (ds & dspec_access);
	DECL_SPEC ok = find_access(&id, pns, acc, 0);
	if (compare_access(ok, ds, TAG_id(pid), mem)) {
		if ((ds & dspec_inherit) && inherit_access(id, pid, mem)) {
			/* Can access through inheritance */
			/* EMPTY */
		} else {
			/* Report access error */
			ERROR err;
			if (IS_NULL_id(id)) {
				err = ERR_class_access_spec_none(pid, acc);
			} else {
				err = ERR_class_access_spec_id(pid, acc, id);
			}
			report(crt_loc, err);
			ret = 1;
		}
	}
	return ret;
}


/*
    This routine checks the access of the base class gr by the
    identifier id.  It prints an error and returns true if the access
    is illegal.
*/

static int
do_base_access(IDENTIFIER id, GRAPH gr)
{
	int ret = 0;
	GRAPH gt = DEREF_graph(graph_top(gr));
	CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
	NAMESPACE pns = DEREF_nspace(ctype_member(ct));
	DECL_SPEC ds = DEREF_dspec(graph_access(gr));
	DECL_SPEC acc = (ds & dspec_access);
	DECL_SPEC ok = find_access(&id, pns, acc, 1);
	if (compare_access(ok, ds, null_tag, 0)) {
		/* Report access error */
		ERROR err;
		CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
		if (IS_NULL_id(id)) {
			err = ERR_class_access_base_none(cs, ct, acc);
		} else {
			err = ERR_class_access_base_id(cs, ct, acc, id);
		}
		err = concat_error(err, ERR_conv_ptr_access());
		report(crt_loc, err);
		ret = 1;
	}
	return ret;
}


/*
    This routine clears the list of pending access checks given by p in
    the context given by the identifier id.  It returns true if any
    results in an error.
*/

static int
clear_id_access(IDENTIFIER id, LIST(IDENTIFIER)p, LIST(int)r)
{
	int ret = 0;
	if (!IS_NULL_list(p)) {
		int mem = DEREF_int(HEAD_list(r));
		IDENTIFIER pid = DEREF_id(HEAD_list(p));
		ret = clear_id_access(id, TAIL_list(p), TAIL_list(r));
		if (!IS_NULL_id(pid) && do_member_access(id, pid, mem)) {
			COPY_id(HEAD_list(p), NULL_id);
			ret = 1;
		}
	}
	return ret;
}


/*
    This routine clears the list of pending base class access checks given
    by p in the context given by the identifier id.  It returns true if
    any results in an error.
*/

static int
clear_base_access(IDENTIFIER id, LIST(GRAPH)p)
{
	int ret = 0;
	if (!IS_NULL_list(p)) {
		GRAPH gr = DEREF_graph(HEAD_list(p));
		ret = clear_base_access(id, TAIL_list(p));
		if (!IS_NULL_graph(gr) && do_base_access(id, gr)) {
			COPY_graph(HEAD_list(p), NULL_graph);
			ret = 1;
		}
	}
	return ret;
}


/*
    This routine clears the list of pending access checks given by acc in
    the context given by the identifier id.  It returns true if any
    results in an error.
*/

int
clear_access(IDENTIFIER id, ACCESS_LIST *acc)
{
	int ret = 0;
	if (acc->pending) {
		LIST(IDENTIFIER)p = acc->ids;
		LIST(GRAPH)q = acc->bases;
		LIST(int)r = acc->info;
		if (!IS_NULL_list(p) && clear_id_access(id, p, r)) {
			ret = 1;
		}
		if (!IS_NULL_list(q) && clear_base_access(id, q)) {
			ret = 1;
		}
	}
	return ret;
}


/*
    This routine clears all outstanding accesses in the scope given by id.
    It returns true if any results in an error.
*/

int
report_access(IDENTIFIER id)
{
	ACCESS_LIST *acc = &crt_access_list;
	int ret = clear_access(id, acc);
	free_access(acc);
	return ret;
}


/*
    This routine frees the list of accesses given by acc.
*/

void
free_access(ACCESS_LIST *acc)
{
	LIST(IDENTIFIER)p = acc->ids;
	LIST(GRAPH)q = acc->bases;
	LIST(int)r = acc->info;
	if (!IS_NULL_list(p)) {
		DESTROY_list(p, SIZE_id);
		acc->ids = NULL_list(IDENTIFIER);
	}
	if (!IS_NULL_list(q)) {
		DESTROY_list(q, SIZE_graph);
		acc->bases = NULL_list(GRAPH);
	}
	if (!IS_NULL_list(r)) {
		DESTROY_list(r, SIZE_int);
		acc->info = NULL_list(int);
	}
	acc->pending = 0;
	acc->inherit = 0;
	return;
}


/*
    This routine saves the current access list into acc and clears the
    list.
*/

void
save_access(ACCESS_LIST *acc)
{
	ACCESS_LIST *crt = &crt_access_list;
	acc->ids = crt->ids;
	acc->bases = crt->bases;
	acc->info = crt->info;
	acc->pending = crt->pending;
	acc->inherit = crt->inherit;
	crt->ids = NULL_list(IDENTIFIER);
	crt->bases = NULL_list(GRAPH);
	crt->info = NULL_list(int);
	crt->pending = 0;
	crt->inherit = 0;
	return;
}


/*
    This routine clears the current access list in the scope given by
    id and resets the current access list the values stored in acc.
*/

int
restore_access(IDENTIFIER id, ACCESS_LIST *acc)
{
	int ret = report_access(id);
	ACCESS_LIST *crt = &crt_access_list;
	crt->ids = acc->ids;
	crt->bases = acc->bases;
	crt->info = acc->info;
	crt->pending = acc->pending;
	crt->inherit = acc->inherit;
	return ret;
}


/*
    This routine adds the identifier id with access acc to the list of
    pending access checks.  acc will always be dspec_public, dspec_protected
    or dspec_private.
*/

void
check_access(IDENTIFIER id, DECL_SPEC acc)
{
	if (acc == dspec_public) {
		return;
	}
	if (do_access_checks) {
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		if (IS_nspace_ctype(ns)) {
			ACCESS_LIST *crt = &crt_access_list;
			if (in_function_defn && !in_declaration) {
				/* Calculate access immediately */
				IGNORE do_member_access(crt_func_id, id,
							crt->inherit);
			} else {
				/* Add to pending list */
				CONS_id(id, crt->ids, crt->ids);
				CONS_int(crt->inherit, crt->info, crt->info);
				crt->pending = 1;
			}
		} else {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_auto) {
				/* Used to mark for-init variables */
				report(crt_loc, ERR_stmt_for_init(id));
				ds &= ~dspec_access;
				COPY_dspec(id_storage(id), ds);
			}
		}
	}
	return;
}


/*
    This routine adds the base class graph gr to the list of pending
    base access checks.
*/

void
check_base_access(GRAPH gr)
{
	DECL_SPEC ds = DEREF_dspec(graph_access(gr));
	DECL_SPEC acc = (ds & dspec_access);
	DECL_SPEC acc2 = (ds & dspec_access2);
	if (acc == dspec_public) {
		return;
	}

	if (do_access_checks) {
		/* Find best access to a virtual base */
		GRAPH gs = DEREF_graph(graph_equal(gr));
		while (!IS_NULL_graph(gs)) {
			DECL_SPEC pds = DEREF_dspec(graph_access(gs));
			DECL_SPEC pacc = (pds & dspec_access);
			DECL_SPEC pacc2 = (pds & dspec_access2);
			if (pacc == dspec_public) {
				return;
			}
			if (pacc < acc || (pacc == acc && pacc2 < acc2)) {
				acc = pacc;
				acc2 = pacc2;
				gr = gs;
			}
			gs = DEREF_graph(graph_equal(gs));
		}

		/* Check access control */
		if (in_function_defn && !in_declaration) {
			/* Calculate access immediately */
			IGNORE do_base_access(crt_func_id, gr);
		} else {
			/* Add to pending list */
			ACCESS_LIST *crt = &crt_access_list;
			CONS_graph(gr, crt->bases, crt->bases);
			crt->pending = 1;
		}
	}
	return;
}


/*
    This routine applies an immediate access check to the identifier id
    by cid.
*/

void
immediate_access(IDENTIFIER cid, IDENTIFIER id)
{
	DECL_SPEC acc = DEREF_dspec(id_storage(id));
	acc &= dspec_access;
	if (acc == dspec_none || acc == dspec_public) {
		return;
	}
	if (do_access_checks) {
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		if (IS_nspace_ctype(ns)) {
			int mem = crt_access_list.inherit;
			IGNORE do_member_access(cid, id, mem);
		}
	}
	return;
}
