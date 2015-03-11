/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <tdf/capsule.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>

#include <syntax/syntax.h>

#include <output/capsule.h>
#include <output/dump.h>

#include <construct/access.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/derive.h>
#include <construct/exception.h>
#include <construct/function.h>
#include <construct/namespace.h>
#include <construct/overload.h>
#include <construct/template.h>
#include <construct/virtual.h>

#include "ctype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "type_ops.h"
#include "virt_ops.h"


/*
    This routine is called when the same virtual function is inherited
    via both vp and vq.  It combine the two virtual function table entries
    and returns the result.  Note that one or other may be selected using
    the dominance rule in certain cases.
*/

static VIRTUAL
inherit_duplicate(VIRTUAL vp, VIRTUAL vq)
{
	GRAPH gr;
	IDENTIFIER fn;
	IDENTIFIER gn;
	unsigned long n;
	if (IS_virt_inherit(vq)) {
		DESTROY_virt_inherit(destroy, fn, n, gr, vq, vq);
		UNUSED(fn);
		UNUSED(n);
		UNUSED(gr);
		UNUSED(vq);
		return vp;
	}
	if (IS_virt_inherit(vp)) {
		DESTROY_virt_inherit(destroy, fn, n, gr, vp, vp);
		UNUSED(fn);
		UNUSED(n);
		UNUSED(gr);
		UNUSED(vp);
		return vq;
	}
	fn = DEREF_id(virt_func(vp));
	gn = DEREF_id(virt_func(vq));
	if (EQ_id(fn, gn)) {
		return vp;
	}
	COPY_virt(virt_next(vq), vp);
	return vq;
}


/*
    This routine inherits the virtual function vq from the direct base
    class gs.  p gives the list of functions already inherited.
*/

static VIRTUAL
inherit_virtual(VIRTUAL vq, GRAPH gs, LIST(VIRTUAL) p)
{
	VIRTUAL vp = NULL_virt;
	CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
	CLASS_INFO ci = DEREF_cinfo(ctype_info(cs));
	GRAPH gt = DEREF_graph(ctype_base(cs));
	IDENTIFIER fn = DEREF_id(virt_func(vq));
	switch (TAG_virt(vq)) {
	case virt_simple_tag:
		/* Simple inheritance */
		MAKE_virt_inherit(fn, 0, gs, vp);
		return vp;
	case virt_override_tag: {
		/* Override inheritance */
		IDENTIFIER bn = DEREF_id(virt_override_orig(vq));
		GRAPH rq = DEREF_graph(virt_override_ret(vq));
		GRAPH sq = DEREF_graph(virt_override_src(vq));
		GRAPH sp = find_subgraph(gs, gt, sq);
		MAKE_virt_complex(fn, 0, gs, rq, bn, sp, vp);
		fn = bn;
		gs = sp;
		break;
	}
	case virt_inherit_tag: {
		/* Nested inheritance */
		GRAPH gq = DEREF_graph(virt_base(vq));
		GRAPH gp = find_subgraph(gs, gt, gq);
		MAKE_virt_inherit(fn, 0, gp, vp);
		gs = gp;
		break;
	}
	case virt_complex_tag: {
		/* Complex inheritance */
		IDENTIFIER bn = DEREF_id(virt_complex_orig(vq));
		GRAPH rq = DEREF_graph(virt_complex_ret(vq));
		GRAPH sq = DEREF_graph(virt_complex_src(vq));
		GRAPH sp = find_subgraph(gs, gt, sq);
		GRAPH gq = DEREF_graph(virt_base(vq));
		GRAPH gp = find_subgraph(gs, gt, gq);
		MAKE_virt_complex(fn, 0, gp, rq, bn, sp, vp);
		fn = bn;
		gs = sp;
		break;
	}
	case virt_link_tag: {
		/* Symbolic link */
		PTR(VIRTUAL)pv = DEREF_ptr(virt_link_to(vq));
		vq = DEREF_virt(pv);
		vp = inherit_virtual(vq, gs, p);
		return vp;
	}
	default:
		/* Shouldn't occur */
		return vp;
	}

	/* Check previous cases */
	if (ci & cinfo_virtual_base) {
		while (!IS_NULL_list(p)) {
			VIRTUAL vr = DEREF_virt(HEAD_list(p));
			switch (TAG_virt(vr)) {
			case virt_inherit_tag: {
				/* Previous simple inheritance */
				IDENTIFIER bn = DEREF_id(virt_func(vr));
				GRAPH gr = DEREF_graph(virt_base(vr));
				if (EQ_id(bn, fn) && eq_graph(gr, gs)) {
					unsigned long n =
					    DEREF_ulong(virt_no(vr));
					vp = inherit_duplicate(vr, vp);
					COPY_ulong(virt_no(vr), n);
					COPY_virt(HEAD_list(p), vp);
					MAKE_virt_link(bn, n, gr, HEAD_list(p),
						       vp);
					return vp;
				}
				break;
			}
			case virt_complex_tag: {
				/* Previous complex inheritance */
				IDENTIFIER bn = DEREF_id(virt_complex_orig(vr));
				GRAPH gr = DEREF_graph(virt_complex_src(vr));
				if (EQ_id(bn, fn) && eq_graph(gr, gs)) {
					unsigned long n =
					    DEREF_ulong(virt_no(vr));
					vp = inherit_duplicate(vr, vp);
					COPY_ulong(virt_no(vr), n);
					COPY_virt(HEAD_list(p), vp);
					MAKE_virt_link(bn, n, gr, HEAD_list(p),
						       vp);
					return vp;
				}
				break;
			}
			}
			p = TAIL_list(p);
		}
	}
	return vp;
}


/*
    This routine inherits the virtual function table vs to the class
    corresponding to the graph gt.  vt gives any previous virtual function
    tables.
*/

static VIRTUAL
inherit_table(VIRTUAL vs, VIRTUAL vt, GRAPH gt)
{
	if (!IS_NULL_virt(vs)) {
		OFFSET off;
		VIRTUAL vp;
		IDENTIFIER id = DEREF_id(virt_func(vs));
		GRAPH gr = DEREF_graph(virt_base(vs));
		GRAPH gs = DEREF_graph(graph_top(gr));
		VIRTUAL vr = DEREF_virt(virt_next(vs));
		vr = inherit_table(vr, vt, gt);
		gr = find_subgraph(gt, gs, gr);
		off = DEREF_off(graph_off(gr));
		vp = vr;
		while (!IS_NULL_virt(vp)) {
			/* Check for previous use of this base */
			GRAPH gp = DEREF_graph(virt_base(vp));
			if (eq_graph(gp, gr)) {
				COPY_off(virt_table_off(vp), off);
				COPY_graph(virt_base(vp), gr);
				return vt;
			}
			vp = DEREF_virt(virt_next(vp));
		}
		MAKE_virt_table(id, 0, gr, off, vt);
		COPY_virt(virt_next(vt), vr);
	}
	return vt;
}


/*
    This routine inherits the virtual function tables from the list of
    base classes br.
*/

static VIRTUAL
inherit_base_tables(LIST(GRAPH) br)
{
	if (!IS_NULL_list(br)) {
		VIRTUAL vt = inherit_base_tables(TAIL_list(br));
		GRAPH gs = DEREF_graph(HEAD_list(br));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
		VIRTUAL vs = DEREF_virt(ctype_virt(cs));
		vt = inherit_table(vs, vt, gs);
		return vt;
	}
	return NULL_virt;
}


/*
    This routine creates the virtual function tables for the class ct.
    If code generation is not enabled then this is just a simple table
    corresponding to ct.  Otherwise it may be necessary to create a
    number of tables, corresponding to the base classes of ct.  If the
    first base class is not virtual then its inherited table is used
    for ct, otherwise a new table needs to be created.  If bases is
    false then a single table is created.
*/

static VIRTUAL
make_virt_table(CLASS_TYPE ct, CLASS_INFO cj, int bases)
{
	VIRTUAL vt = NULL_virt;
	VIRTUAL vs = NULL_virt;
	GRAPH gr = DEREF_graph(ctype_base(ct));
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));

	/* Inherit tables from base classes */
	if (bases) {
		LIST(GRAPH) br = DEREF_list(graph_tails(gr));
		vs = inherit_base_tables(br);
		if (!IS_NULL_virt(vs)) {
			OFFSET off = DEREF_off(virt_table_off(vs));
			if (is_zero_offset(off)) {
				/* Use inherited virtual function table */
				vt = vs;
			}
		}
	}

	/* Create new virtual function table */
	if (IS_NULL_virt(vt)) {
		IDENTIFIER id = DEREF_id(ctype_name(ct));
		MAKE_virt_table(id, 0, gr, NULL_off, vt);
		COPY_virt(virt_next(vt), vs);
	}
	COPY_virt(ctype_virt(ct), vt);
	COPY_cinfo(ctype_info(ct), (ci | cj));
	return vt;
}


/*
    This routine initialises the virtual function table for the class
    type ct.
*/

void
begin_virtual(CLASS_TYPE ct)
{
	unsigned long n = 0;
	LIST(VIRTUAL) p = NULL_list(VIRTUAL);
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH) br = DEREF_list(graph_tails(gr));

	/* Scan through direct base classes */
	while (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
		VIRTUAL vs = DEREF_virt(ctype_virt(cs));
		if (!IS_NULL_virt(vs)) {
			LIST(VIRTUAL)q = DEREF_list(virt_table_entries(vs));
			while (!IS_NULL_list(q)) {
				VIRTUAL vq = DEREF_virt(HEAD_list(q));
				VIRTUAL vp = inherit_virtual(vq, gs, p);
				if (!IS_NULL_virt(vp)) {
					/* Add inherited function to list */
					CONS_virt(vp, p, p);
					COPY_ulong(virt_no(vp), n);
					n++;
				}
				q = TAIL_list(q);
			}
		}
		br = TAIL_list(br);
	}

	/* Construct the virtual function table */
	if (!IS_NULL_list(p)) {
		CLASS_INFO ci = (cinfo_polymorphic | cinfo_poly_base);
		VIRTUAL vt = make_virt_table(ct, ci, output_capsule);
		p = REVERSE_list(p);
		COPY_list(virt_table_entries(vt), p);
		COPY_ulong(virt_no(vt), n);
	}
	return;
}


/*
    This routine is called at the end of a class definition to complete
    the construction of the virtual function table.  It checks for
    inherited pure virtual functions and for final overriding functions.
    Also if any overriding virtual function involves a non-trivial base
    class conversion then an inherited virtual function table cannot be
    used as the main virtual function table for ct.
*/

void
end_virtual(CLASS_TYPE ct)
{
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	if (!IS_NULL_virt(vt)) {
		int destr = 0;
		int trivial = 1;
		OFFSET off = DEREF_off(virt_table_off(vt));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		LIST(VIRTUAL) p = DEREF_list(virt_table_entries(vt));
		LIST(VIRTUAL) q = p;
		unsigned long n = DEREF_ulong(virt_no(vt));
		IGNORE check_value(OPT_VAL_virtual_funcs, n);
		while (!IS_NULL_list(q)) {
			VIRTUAL vf = DEREF_virt(HEAD_list(q));
			IDENTIFIER id = DEREF_id(virt_func(vf));
			HASHID nm = DEREF_hashid(id_name(id));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_pure) {
				ci |= cinfo_abstract;
			}
			if (IS_hashid_destr(nm)) {
				destr = 1;
			}
			if (IS_virt_override(vf)) {
				/* Check for non-trivial return conversions */
				GRAPH gr = DEREF_graph(virt_override_ret(vf));
				if (!IS_NULL_graph(gr)) {
					DECL_SPEC acc =
					    DEREF_dspec(graph_access(gr));
					if (!(acc & dspec_ignore)) {
						trivial = 0;
					}
				}
			} else if (IS_virt_complex(vf)) {
				/* Check for final overrider */
				GRAPH gr = DEREF_graph(virt_complex_ret(vf));
				VIRTUAL vn = DEREF_virt(virt_next(vf));
				if (!IS_NULL_virt(vn)) {
					id = DEREF_id(virt_complex_orig(vf));
					report(crt_loc,
					       ERR_class_virtual_final(id, ct));
				}
				if (!IS_NULL_graph(gr)) {
					DECL_SPEC acc =
					    DEREF_dspec(graph_access(gr));
					if (!(acc & dspec_ignore)) {
						trivial = 0;
					}
				}
			}
			q = TAIL_list(q);
		}
		if (!IS_NULL_off(off) && !trivial && output_capsule) {
			/* Can't use inherited virtual function table */
			VIRTUAL vs = make_virt_table(ct, cinfo_none, 0);
			COPY_virt(virt_next(vs), vt);
			COPY_ulong(virt_no(vs), n);
			COPY_list(virt_table_entries(vs), p);
		}
		if (!destr) {
			/* Warn about non-virtual destructors */
			report(crt_loc, ERR_class_virtual_destr(ct));
		}
		ci |= cinfo_polymorphic;
		COPY_cinfo(ctype_info(ct), ci);
	}
	return;
}


/*
    This routine checks whether the return type of the function type s is
    valid for a virtual function which overrides a function of type t.
    If the return types differ by a base class conversion then the
    corresponding base class graph is returned via pgr.
*/

static int
virtual_return(TYPE s, TYPE t, GRAPH *pgr)
{
    if (IS_type_func(s) && IS_type_func(t)) {
	TYPE p = DEREF_type(type_func_ret(s));
	TYPE q = DEREF_type(type_func_ret(t));
	unsigned np = TAG_type(p);
	unsigned nq = TAG_type(q);
	if (np == nq) {
	    if (eq_type(p, q)) {
		    return 1;
	    }
	    if (np == type_ptr_tag || nq == type_ref_tag) {
		p = DEREF_type(type_ptr_etc_sub(p));
		np = TAG_type(p);
		if (np == type_compound_tag) {
		    q = DEREF_type(type_ptr_etc_sub(q));
		    nq = TAG_type(q);
		    if (nq == type_compound_tag) {
			/* Both pointer or reference to class */
			GRAPH gr;
			CLASS_TYPE cp, cq;
			cp = DEREF_ctype(type_compound_defn(p));
			cq = DEREF_ctype(type_compound_defn(q));
			gr = find_base_class(cp, cq, 1);
			if (!IS_NULL_graph(gr)) {
			    /* Base class conversion */
			    CV_SPEC cv = cv_compare(q, p);
			    if (cv == cv_none) {
				/* Qualification conversion */
				*pgr = gr;
				return 1;
			    }
			}
		    }
		}
	    }
	}

	/* Allow for template types */
	if (np == type_token_tag && is_templ_type(p)) {
		return 1;
	}
	if (nq == type_token_tag && is_templ_type(q)) {
		return 1;
	}
	if (np == type_error_tag || nq == type_error_tag) {
		return 1;
	}
    }
    return 0;
}


/*
    This routine checks whether a member function nm of type t overrides
    a virtual function in some base class of ct.  It returns a list of
    all such functions.  The function return types are not checked at
    this stage.  If the function is not an overriding virtual function
    but has the same name as a virtual function then this is returned
    via pid.
*/

LIST(VIRTUAL)
overrides_virtual(CLASS_TYPE ct, HASHID nm, TYPE t, IDENTIFIER *pid)
{
	LIST(VIRTUAL) res = NULL_list(VIRTUAL);
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	if (!IS_NULL_virt(vt)) {
		unsigned nt = TAG_hashid(nm);
		LIST(VIRTUAL) p = DEREF_list(virt_table_entries(vt));
		while (!IS_NULL_list(p)) {
			VIRTUAL vf = DEREF_virt(HEAD_list(p));
			switch (TAG_virt(vf)) {
			case virt_inherit_tag:
			case virt_complex_tag: {
				/* Only check inherited functions */
				IDENTIFIER fid = DEREF_id(virt_func(vf));
				HASHID fnm = DEREF_hashid(id_name(fid));
				if (EQ_hashid(fnm, nm)) {
					/* Names match */
					TYPE s;
					s = DEREF_type(id_function_etc_type(fid));
					if (eq_func_type(t, s, 1, 0)) {
						/* Types basically match */
						CONS_virt(vf, res, res);
					} else {
						*pid = fid;
					}
				} else if (nt == hashid_destr_tag) {
					/* Check for virtual destructors */
					if (IS_hashid_destr(fnm)) {
						CONS_virt(vf, res, res);
					}
				}
				break;
			}
			}
			p = TAIL_list(p);
		}
		res = REVERSE_list(res);
	}
	return res;
}


/*
    This routine finds an overriding virtual function for the virtual
    function id inherited from the base class gr of ct.  If the return
    types do not match then the base class conversion is assigned to pgr.
*/

VIRTUAL
find_overrider(CLASS_TYPE ct, IDENTIFIER id, GRAPH gr, GRAPH *pgr)
{
	HASHID nm = DEREF_hashid(id_name(id));
	unsigned nt = TAG_hashid(nm);
	TYPE t = DEREF_type(id_function_etc_type(id));

	/* Scan through virtual functions */
	VIRTUAL vs = DEREF_virt(ctype_virt(ct));
	if (!IS_NULL_virt(vs)) {
		LIST(VIRTUAL) p = DEREF_list(virt_table_entries(vs));
		while (!IS_NULL_list(p)) {
			VIRTUAL vf = DEREF_virt(HEAD_list(p));
			if (!IS_virt_link(vf)) {
				GRAPH gs = DEREF_graph(virt_base(vf));
				if (is_subgraph(gs, gr)) {
					HASHID fnm;
					IDENTIFIER fid =
					    DEREF_id(virt_func(vf));
					if (EQ_id(fid, id)) {
						/* Identical functions */
						return vf;
					}
					fnm = DEREF_hashid(id_name(fid));
					if (EQ_hashid(fnm, nm)) {
						/* Names match */
						TYPE s;
						s = DEREF_type(id_function_etc_type(fid));
						if (eq_func_type(s, t, 1, 0)) {
							/* Types basically
							 * match */
							IGNORE virtual_return(s, t, pgr);
							return vf;
						}
					} else if (nt == hashid_destr_tag) {
						/* Check for virtual
						 * destructors */
						if (IS_hashid_destr(fnm)) {
							return vf;
						}
					}
				}
			}
			p = TAIL_list(p);
		}
	}
	return NULL_virt;
}


/*
    This routine finds the offset within the main virtual function table
    for a class of those functions inherited from the base class gr.
*/

unsigned long
virtual_start(GRAPH gr)
{
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if (!(acc & dspec_ignore)) {
		GRAPH gu = DEREF_graph(graph_up(gr));
		if (!IS_NULL_graph(gu)) {
			unsigned long n = virtual_start(gu);
			LIST(GRAPH) br = DEREF_list(graph_tails(gu));
			while (!IS_NULL_list(br)) {
				VIRTUAL vs;
				CLASS_TYPE cs;
				GRAPH gs = DEREF_graph(HEAD_list(br));
				if (eq_graph(gs, gr)) {
					return n;
				}
				cs = DEREF_ctype(graph_head(gs));
				vs = DEREF_virt(ctype_virt(cs));
				if (!IS_NULL_virt(vs)) {
					/* Add virtual functions from cs */
					unsigned long m =
					    DEREF_ulong(virt_no(vs));
					n += m;
				}
				br = TAIL_list(br);
			}
			return n;
		}
	}
	return 0;
}


/*
    This routine creates an overriding virtual function id for vq.  gs gives
    the base class graph of the underlying type.
*/

static VIRTUAL
override_virtual(IDENTIFIER id, VIRTUAL vq, GRAPH gs)
{
	GRAPH gt;
	VIRTUAL vp;
	GRAPH gr = NULL_graph;
	IDENTIFIER fn = DEREF_id(virt_func(vq));
	unsigned long n = DEREF_ulong(virt_no(vq));

	/* Check function return types */
	TYPE t = DEREF_type(id_function_etc_type(id));
	TYPE s = DEREF_type(id_function_etc_type(fn));
	if (virtual_return(t, s, &gr)) {
		if (!IS_NULL_graph(gr)) {
			ERROR err = check_ambig_base(gr);
			if (!IS_NULL_err(err)) {
				/* Can't be ambiguous */
				ERROR err2 = ERR_class_virtual_ambig(id, fn);
				err = concat_error(err, err2);
				report(crt_loc, err);
			}
			check_base_access(gr);
		}
		if (!eq_except(t, s)) {
			/* Check exception specifiers */
			PTR(LOCATION)loc = id_loc(fn);
			report(crt_loc, ERR_except_spec_virtual(id, fn, loc));
		}
	} else {
		PTR(LOCATION)loc = id_loc(fn);
		report(crt_loc, ERR_class_virtual_ret(id, fn, loc));
	}

	/* Find the result components */
	switch (TAG_virt(vq)) {
	case virt_override_tag:
		fn = DEREF_id(virt_override_orig(vq));
		gs = DEREF_graph(virt_override_src(vq));
		break;
	case virt_inherit_tag:
		gs = DEREF_graph(virt_base(vq));
		break;
	case virt_complex_tag:
		fn = DEREF_id(virt_complex_orig(vq));
		gs = DEREF_graph(virt_complex_src(vq));
		break;
	}
	gt = DEREF_graph(graph_top(gs));
	MAKE_virt_override(id, n, gt, gr, fn, gs, vp);
	if (do_dump) {
		dump_override(id, fn);
	}
	return vp;
}


/*
    This routine adds the virtual function id to the virtual function
    table for the class ct.  r is the result of a call to overrides_virtual
    on id.
*/

void
add_virtual(CLASS_TYPE ct, IDENTIFIER id, LIST(VIRTUAL) r)
{
	VIRTUAL vf;
	unsigned long n;
	LIST(VIRTUAL)p, q;
	GRAPH gr = DEREF_graph(ctype_base(ct));

	/* Create the virtual function table if necessary */
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	if (IS_NULL_virt(vt)) {
		vt = make_virt_table(ct, cinfo_polymorphic, output_capsule);
		p = NULL_list(VIRTUAL);
		n = 0;
	} else {
		p = DEREF_list(virt_table_entries(vt));
		n = DEREF_ulong(virt_no(vt));
	}

	/* Create the table entry */
	if (IS_NULL_list(r)) {
		/* New virtual function */
		MAKE_virt_simple(id, n, gr, vf);
		CONS_virt(vf, NULL_list(VIRTUAL), q);
		p = APPEND_list(p, q);
		COPY_list(virt_table_entries(vt), p);
		COPY_ulong(virt_no(vt), n + 1);
	} else {
		/* Overriding virtual function */
		q = r;
		while (!IS_NULL_list(q)) {
			VIRTUAL vq = DEREF_virt(HEAD_list(q));
			for (;;) {
				VIRTUAL vp = DEREF_virt(HEAD_list(p));
				if (EQ_virt(vp, vq)) {
					break;
				}
				p = TAIL_list(p);
			}
			vf = override_virtual(id, vq, gr);
			COPY_virt(HEAD_list(p), vf);
			p = TAIL_list(p);
			q = TAIL_list(q);
		}
		DESTROY_list(r, SIZE_virt);
	}
	return;
}


/*
    This routine returns a pure virtual function of the class ct if such
    exists.  Otherwise the null identifier is returned.
*/

IDENTIFIER
find_pure_function(CLASS_TYPE ct)
{
	VIRTUAL vt = DEREF_virt(ctype_virt(ct));
	if (!IS_NULL_virt(vt)) {
		LIST(VIRTUAL) p = DEREF_list(virt_table_entries(vt));
		while (!IS_NULL_list(p)) {
			VIRTUAL vf = DEREF_virt(HEAD_list(p));
			IDENTIFIER id = DEREF_id(virt_func(vf));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_pure) {
				return id;
			}
			p = TAIL_list(p);
		}
	}
	return NULL_id;
}
