/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include <limits.h>
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "derive.h"
#include "dump.h"
#include "identifier.h"
#include "instance.h"
#include "namespace.h"
#include "redeclare.h"
#include "syntax.h"
#include "template.h"
#include "token.h"
#include "virtual.h"


/*
    ARE TWO GRAPHS EQUAL?

    This routine checks whether the graphs gr and gs are equal.  Allowance
    is made for the equivalence of virtual bases.
*/

int
eq_graph(GRAPH gr, GRAPH gs)
{
	GRAPH hr = gr;
	GRAPH hs = gs;
	while (!IS_NULL_graph(gr)) {
		/* Calculate canonical form for virtual bases */
		hr = gr;
		gr = DEREF_graph(graph_equal(gr));
	}
	while (!IS_NULL_graph(gs)) {
		/* Calculate canonical form for virtual bases */
		hs = gs;
		gs = DEREF_graph(graph_equal(gs));
	}
	return EQ_graph(hr, hs);
}


/*
    SEARCH A GRAPH FOR A BASE

    This routine searches the graph gr for the base class ct.  It returns
    the first node encountered which matches ct, or the null graph if no
    such match is found.  Note that the search algorithm is based on a
    depth-first left-to-right traversal of the graph.
*/

static GRAPH
search_graph(GRAPH gr, CLASS_TYPE ct)
{
	DECL_SPEC acc;

	/* Check the head of gr */
	CLASS_TYPE cr = DEREF_ctype(graph_head(gr));
	if (eq_ctype(cr, ct)) {
		return gr;
	}

	/* Only search first instance */
	acc = DEREF_dspec(graph_access(gr));
	if (acc & dspec_defn) {
		/* Search the branches of gr */
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			GRAPH gs = DEREF_graph(HEAD_list(br));
			gs = search_graph(gs, ct);
			if (!IS_NULL_graph(gs)) {
				return gs;
			}
			br = TAIL_list(br);
		}
	}
	return NULL_graph;
}


/*
    IS ONE GRAPH A SUBGRAPH OF ANOTHER?

    This routine checks whether the graph gs is a subgraph of gr (allowing
    for the identification of virtual bases).
*/

int
is_subgraph(GRAPH gr, GRAPH gs)
{
	unsigned nt, ns;
	CLASS_TYPE ct, cs;
	if (EQ_graph(gr, gs)) {
		return 1;
	}
	ct = DEREF_ctype(graph_head(gr));
	cs = DEREF_ctype(graph_head(gs));
	nt = DEREF_unsigned(ctype_no_bases(ct));
	ns = DEREF_unsigned(ctype_no_bases(cs));
	if (nt == ns) {
		/* Graphs are the same size */
		return eq_graph(gr, gs);
	}
	if (nt > ns) {
		/* gr is bigger than gs */
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			GRAPH gt = DEREF_graph(HEAD_list(br));
			if (is_subgraph(gt, gs)) {
				return 1;
			}
			br = TAIL_list(br);
		}
	}
	return 0;
}


/*
    COPY A GRAPH

    This routine recursively copies the graph gr into the base class graph
    of the current class, with access specifiers adjusted by acc and virtual
    specifier virt.  indir is true if the graph is a subgraph of a virtual
    base and templ is true if the graph represents a template parameter.
*/

static GRAPH
copy_graph(GRAPH gr, OFFSET off, DECL_SPEC acc, int virt, int indir, int templ)
{
	OFFSET offa;
	DECL_SPEC as;
	GRAPH gc, gp, gs;
	LIST(GRAPH)bs;

	/* Decompose head of graph */
	CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
	LIST(GRAPH)bt = DEREF_list(graph_tails(gr));

	/* Adjust access specifiers */
	DECL_SPEC at = DEREF_dspec(graph_access(gr));
	as = join_access(at, acc);
	as |= shadow_access(at);
	if (at & dspec_virtual) {
		virt = 1;
	}
	if (virt) {
		/* Mark virtual bases */
		as |= dspec_virtual;
		indir = 1;
	}
	if (indir) {
		/* Mark indirect bases */
		as |= dspec_mutable;
	}
	if (templ) {
		/* Mark template parameter bases */
		as |= dspec_template;
	}
	as |= dspec_inherit;
	as &= ~dspec_done;

	/* Search existing graph for ct */
	gc = DEREF_graph(ctype_base(crt_class));
	gp = search_graph(gc, ct);
	if (IS_NULL_graph(gp)) {
		as |= dspec_defn;
	}

	/* Copy components */
	bs = NULL_list(GRAPH);
	while (!IS_NULL_list(bt)) {
		GRAPH gt = DEREF_graph(HEAD_list(bt));
		gt = copy_graph(gt, off, as, 0, indir, templ);
		CONS_graph(gt, bs, bs);
		bt = TAIL_list(bt);
	}
	bs = REVERSE_list(bs);

	/* Create new graph */
	MAKE_graph_basic(ct, as, gs);
	COPY_list(graph_tails(gs), bs);
	COPY_graph(graph_top(gs), gc);

	/* Set base offset */
	offa = DEREF_off(graph_off(gr));
	if (!IS_NULL_off(offa)) {
		MAKE_off_deriv(gs, off, offa, off);
	}
	COPY_off(graph_off(gs), off);

	/* Set up-field of bases */
	while (!IS_NULL_list(bs)) {
		GRAPH gt = DEREF_graph(HEAD_list(bs));
		COPY_graph(graph_up(gt), gs);
		bs = TAIL_list(bs);
	}
	return gs;
}


/*
    FIND A COPY OF A SUBGRAPH

    Given a graph gs, a subgraph hs of gs, and a copy gr of gs (produced
    by copy_graph above), this routine returns the subgraph of gr which is
    the image of hs under this copy operation, i.e. it is the subgraph
    hr which makes the following diagram commutative:

				copy
			    gr ------ gs
			     |        |
			incl |        | incl
			     |        |
			    hr ------ hs
				copy
*/

GRAPH
find_subgraph(GRAPH gr, GRAPH gs, GRAPH hs)
{
	if (EQ_graph(gs, hs)) {
		return gr;
	}
	if (!IS_NULL_graph(gr)) {
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		LIST(GRAPH)bs = DEREF_list(graph_tails(gs));
		while (!IS_NULL_list(br)) {
			GRAPH ar = DEREF_graph(HEAD_list(br));
			GRAPH as = DEREF_graph(HEAD_list(bs));
			GRAPH hr = find_subgraph(ar, as, hs);
			if (!IS_NULL_graph(hr)) {
				return hr;
			}
			br = TAIL_list(br);
			bs = TAIL_list(bs);
		}
	}
	return NULL_graph;
}


/*
    IDENTIFY TWO GRAPHS

    This routine identifies the graph gs with the graph gr by linking
    them by means of their equal fields.
*/

static void
identify_graph(GRAPH gr, GRAPH gs)
{
	DECL_SPEC acc;
	LIST(GRAPH)br, bs;
	GRAPH gu = DEREF_graph(graph_equal(gs));
	while (!IS_NULL_graph(gu)) {
		gs = gu;
		gu = DEREF_graph(graph_equal(gs));
	}
	br = DEREF_list(graph_tails(gr));
	bs = DEREF_list(graph_tails(gs));
	while (!IS_NULL_list(br)) {
		GRAPH hr = DEREF_graph(HEAD_list(br));
		GRAPH hs = DEREF_graph(HEAD_list(bs));
		identify_graph(hr, hs);
		br = TAIL_list(br);
		bs = TAIL_list(bs);
	}
	COPY_graph(graph_equal(gs), gr);
	acc = DEREF_dspec(graph_access(gr));
	acc |= dspec_done;
	COPY_dspec(graph_access(gr), acc);
	return;
}


/*
    BASE CLASS INFORMATION

    The variable base_info holds information about the graph being analysed
    by fold_graph, for example, does it have a virtual or an ambiguous base
    class?
*/

static CLASS_INFO base_info = cinfo_none;
static LIST(GRAPH) virtual_bases = NULL_list(GRAPH);


/*
    FOLD A GRAPH

    This routine folds the graph gr by identifying all of its equal virtual
    bases.  It also defines values representing the offset of each base
    from the start of its class.  It returns a list of all the base classes
    in gr (allowing for virtual bases).  All bases added to the list are
    marked as explicit bases.
*/

static LIST(GRAPH)
fold_graph(GRAPH gr, LIST(GRAPH)br)
{
	CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));

	/* Scan for previous uses of this base */
	LIST(GRAPH)bs = br;
	while (!IS_NULL_list(bs)) {
		GRAPH gs = DEREF_graph(HEAD_list(bs));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
		if (eq_ctype(cs, ct)) {
			/* Duplicate base found */
			DECL_SPEC acs = DEREF_dspec(graph_access(gs));
			if ((acs & dspec_virtual) && (acc & dspec_virtual)) {
				/* Both bases are virtual */
				if (!eq_graph(gr, gs)) {
					/* Identify graphs if not already
					 * done */
					identify_graph(gr, gs);
				}
				/* Propagate ambiguous bases */
				if (acs & dspec_alias) {
					acc |= dspec_alias;
				} else if (acc & dspec_alias) {
					while (!IS_NULL_graph(gs)) {
						acs = DEREF_dspec(graph_access(gs));
						acs |= dspec_alias;
						COPY_dspec(graph_access(gs),
							   acs);
						gs = DEREF_graph(graph_equal(gs));
					}
				}
				acc |= dspec_done;
				COPY_dspec(graph_access(gr), acc);
				return br;
			}
			/* Ambiguous base */
			base_info |= cinfo_ambiguous;
			acc |= dspec_alias;
			acs |= dspec_alias;
			COPY_dspec(graph_access(gs), acs);
		}
		bs = TAIL_list(bs);
	}

	/* Add base class to list */
	acc |= (dspec_main | dspec_done);
	COPY_dspec(graph_access(gr), acc);
	CONS_graph(gr, br, br);

	/* Fold subgraphs */
	bs = DEREF_list(graph_tails(gr));
	while (!IS_NULL_list(bs)) {
		GRAPH gs = DEREF_graph(HEAD_list(bs));
		br = fold_graph(gs, br);
		bs = TAIL_list(bs);
	}

	/* Build list of virtual classes */
	if (acc & dspec_virtual) {
		base_info |= cinfo_virtual_base;
		CONS_graph(gr, virtual_bases, virtual_bases);
	}
	return br;
}


/*
    FIND A SINGLE INHERITANCE BASE CLASS

    This routine returns the single inheritance base class of gr or the
    null graph if there is no such base.  The single inheritance base
    is the first direct base, provided this is not virtual.  Derived
    classes are laid out so that their single inheritance base classes
    are at zero offset from the start of the class, thereby minimising
    the cost of a base class conversion.
*/

static GRAPH
find_first_base(GRAPH gr)
{
	LIST(GRAPH)br = DEREF_list(graph_tails(gr));
	if (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		DECL_SPEC acc = DEREF_dspec(graph_access(gs));
		if (!(acc & dspec_virtual)) {
			return gs;
		}
	}
	return NULL_graph;
}


/*
    END BASE CLASS DEFINITIONS

    This routine is called after all the base classes of a class have been
    processed.  ok is false for an empty base class list.  The routine
    folds the base class graph of the current class and records the total
    number of bases.  It also initialises the virtual function table.
*/

void
end_base_class(CLASS_TYPE ct, int ok)
{
	if (!IS_NULL_ctype(ct)) {
		/* Scan for virtual bases */
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH)bs = DEREF_list(graph_tails(gr));
		unsigned nd = LENGTH_list(bs);
		LIST(GRAPH)br = fold_graph(gr, NULL_list(GRAPH));
		unsigned nb = LENGTH_list(br);
		IGNORE check_value(OPT_VAL_base_classes,(ulong)(nb - 1));
		IGNORE check_value(OPT_VAL_direct_bases,(ulong)nd);
		COPY_unsigned(ctype_no_bases(ct), nb);
		while (!IS_NULL_list(br)) {
			GRAPH gs;
			nb--;
			DESTROY_CONS_graph(destroy, gs, br, br);
			do {
				COPY_unsigned(graph_no(gs), nb);
				gs = DEREF_graph(graph_equal(gs));
			} while (!IS_NULL_graph(gs));
		}
		br = REVERSE_list(virtual_bases);
		COPY_list(ctype_vbase(ct), br);
		nd = LENGTH_list(br);
		IGNORE check_value(OPT_VAL_virtual_bases,(ulong)nd);
		virtual_bases = NULL_list(GRAPH);

		/* Mark single inheritance bases */
		do {
			DECL_SPEC acc = DEREF_dspec(graph_access(gr));
			acc |= dspec_ignore;
			COPY_dspec(graph_access(gr), acc);
			gr = find_first_base(gr);
		} while (!IS_NULL_graph(gr));

		/* Set up base class namespaces */
		while (!IS_NULL_list(bs)) {
			GRAPH gs = DEREF_graph(HEAD_list(bs));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			NAMESPACE ns = DEREF_nspace(ctype_member(cs));
			NAMESPACE nt = DEREF_nspace(ctype_member(ct));
			IGNORE use_namespace(ns, nt, nt);
			uncache_namespace(ns, 0);
			bs = TAIL_list(bs);
		}

		/* Record class information */
		if (!ok) {
			report(crt_loc, ERR_class_derived_empty(ct));
		}
		ci |= base_info;
		COPY_cinfo(ctype_info(ct), ci);
		base_info = cinfo_none;
		if (do_dump) {
			dump_base(ct);
		}

		/* Set up virtual function table */
		begin_virtual(ct);
	}
	return;
}


/*
    ADD A BASE CLASS TO A CLASS DEFINITION

    This routine adds a base class bid with access specifier acc to the
    current class.  virt is true to indicate a virtual base class.
*/

void
add_base_class(IDENTIFIER bid, DECL_SPEC acc, int virt)
{
	GRAPH gt;
	int ok = 1;
	CLASS_INFO cj;
	int templ = 0;
	LIST(GRAPH)bt;
	TYPE s = NULL_type;
	CLASS_TYPE cs = NULL_ctype;

	/* Examine the derived class */
	CLASS_TYPE ct = crt_class;
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	if (ci & cinfo_union) {
		/* Derived class can't be a union */
		report(crt_loc, ERR_class_union_deriv(ct));
		ok = 0;
	}

	/* Examine the base class */
	if (IS_id_class_name_etc(bid)) {
		s = DEREF_type(id_class_name_etc_defn(bid));
	} else {
		IDENTIFIER tid;
		HASHID bnm = DEREF_hashid(id_name(bid));
		if (crt_id_qualifier == qual_none) {
			tid = find_type_id(bnm, 1);
		} else {
			NAMESPACE bns = DEREF_nspace(id_parent(bid));
			tid = find_qual_id(bns, bnm, 0, 1);
			if (IS_NULL_id(tid)) {
				/* Allow for implicit typename */
				s = check_typename(bns, bid, btype_class);
			}
		}
		if (!IS_NULL_id(tid)) {
			if (IS_id_ambig(tid)) {
				tid = report_ambiguous(tid, 0, 1, 1);
			}
			if (IS_id_class_name_etc(tid)) {
				s = DEREF_type(id_class_name_etc_defn(tid));
				bid = tid;
			}
		}
	}
	if (!IS_NULL_type(s)) {
		/* Declared base type */
		s = expand_type(s, 2);
		if (IS_type_compound(s)) {
			cs = DEREF_ctype(type_compound_defn(s));
		} else if (IS_type_token(s)) {
			/* Allow for template parameters */
			IDENTIFIER pid = DEREF_id(type_token_tok(s));
			cs = find_class(pid);
			templ = 1;
		}
		if (IS_NULL_ctype(cs)) {
			/* Inappropriate base class type */
			if (!IS_type_error(s)) {
				report(crt_loc, ERR_class_derived_class(s));
			}
			ok = 0;
		} else {
			/* Examine base class type */
			bid = DEREF_id(ctype_name(cs));
			cj = DEREF_cinfo(ctype_info(cs));
			if (cj & cinfo_union) {
				/* Base class can't be a union */
				report(crt_loc, ERR_class_union_base(cs));
				ok = 0;
			} else {
				/* Base class must be complete */
				ERROR err = check_incomplete(s);
				if (!IS_NULL_err(err)) {
					ERROR err2 =
					    ERR_class_derived_incompl();
					err = concat_error(err, err2);
					report(crt_loc, err);
					ok = 0;
				}
			}
		}
	} else {
		/* Undeclared base type */
		report(crt_loc, ERR_dcl_type_simple_undef(bid));
		ok = 0;
	}

	/* Check the access specifier */
	if (acc == dspec_none) {
		/* No access specifier given */
		acc = crt_access;
		if (acc != prev_access) {
			/* Warn about 'class C : public A, B' */
			report(crt_loc, ERR_class_access_base_acc(bid, acc));
		}
	}
	prev_access = acc;
	if (virt) {
		prev_access |= dspec_virtual;
	}

	/* Check for duplicate base classes */
	gt = DEREF_graph(ctype_base(ct));
	if (ok) {
		bt = DEREF_list(graph_tails(gt));
		while (!IS_NULL_list(bt)) {
			GRAPH gu = DEREF_graph(HEAD_list(bt));
			CLASS_TYPE cu = DEREF_ctype(graph_head(gu));
			if (eq_ctype(cs, cu)) {
				report(crt_loc, ERR_class_mi_dup(ct, cs));
				ok = 0;
				break;
			}
			bt = TAIL_list(bt);
		}
	}

	/* Add base class to graph */
	if (ok) {
		OFFSET off;
		LIST(GRAPH)bs = NULL_list(GRAPH);
		GRAPH gs = DEREF_graph(ctype_base(cs));
		MAKE_off_base(gs, off);
		gs = copy_graph(gs, off, acc, virt, virt, templ);
		COPY_graph(off_base_graph(off), gs);
		COPY_graph(graph_up(gs), gt);
		CONS_graph(gs, bs, bs);
		bt = DEREF_list(graph_tails(gt));
		if (!IS_NULL_list(bt)) {
			/* Mark multiple inheritance */
			ci |= cinfo_multiple_base;
		}
		bt = APPEND_list(bt, bs);
		COPY_list(graph_tails(gt), bt);

		/* Adjust class information */
		cj = DEREF_cinfo(ctype_info(cs));
		ci = check_class_info(ci, cj, 1, acc);
		COPY_cinfo(ctype_info(ct), ci);

		/* Use class name */
		use_id(bid, 0);
	}
	return;
}


/*
    FIND A BASE CLASS

    This routine finds whether cs is a base class of ct, returning the
    corresponding node of the base class graph, or the null graph.  The
    first guess is based on the fact that if cs is a base class of ct
    then ct has at least as many base classes as cs.   The way to remember
    which way round the arguments go is that 'find_base_class ( ct, cs )'
    checks for 'class ct : public cs {}'.  If ct is a template class
    then def indicates whether this operation implies that ct should
    be defined (not properly implemented yet).
*/

GRAPH
find_base_class(CLASS_TYPE ct, CLASS_TYPE cs, int def)
{
	unsigned nt, ns;
	complete_class(ct, 1);
	nt = DEREF_unsigned(ctype_no_bases(ct));
	ns = DEREF_unsigned(ctype_no_bases(cs));
	if (nt >= ns) {
		/* ct is bigger than cs */
		GRAPH gr = DEREF_graph(ctype_base(ct));
		return search_graph(gr, cs);
	}
	UNUSED(def);
	return NULL_graph;
}


/*
    COMPARE TWO CLASSES

    This routine finds whether cs is a base class of ct, or ct is a base
    class of cs.  It returns whichever class is the base class, or the null
    class if the two classes are not so related.  The first guess is based
    on the relative numbers of base classes of each type.  def is as in
    find_base_class.
*/

CLASS_TYPE
compare_base_class(CLASS_TYPE ct, CLASS_TYPE cs, int def)
{
	unsigned nt, ns;
	complete_class(ct, 1);
	complete_class(cs, 1);
	nt = DEREF_unsigned(ctype_no_bases(ct));
	ns = DEREF_unsigned(ctype_no_bases(cs));
	if (nt >= ns) {
		/* ct is bigger than cs */
		GRAPH gr = DEREF_graph(ctype_base(ct));
		gr = search_graph(gr, cs);
		if (!IS_NULL_graph(gr)) {
			return cs;
		}
	} else {
		/* ct is smaller than cs */
		GRAPH gr = DEREF_graph(ctype_base(cs));
		gr = search_graph(gr, ct);
		if (!IS_NULL_graph(gr)) {
			return ct;
		}
	}
	UNUSED(def);
	return NULL_ctype;
}


/*
    CHECK AN AMBIGUOUS BASE CLASS

    This routine checks whether the base class corresponding to the node
    gr is ambiguous.  It returns a suitable error message.
*/

ERROR
check_ambig_base(GRAPH gr)
{
    if (!IS_NULL_graph(gr)) {
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if (acc & dspec_alias) {
	    /* Ambiguous base class */
	    GRAPH gt = DEREF_graph(graph_top(gr));
	    CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
	    CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
	    ERROR err = ERR_class_member_lookup_ambig(cs, ct);
	    return err;
	}
    }
    return NULL_err;
}


/*
    CHECK A VIRTUAL BASE CLASS

    This routine checks whether the base class corresponding to the node
    gr is a virtual base of a base class of a virtual base.  It returns a
    suitable error message.
*/

ERROR
check_virt_base(GRAPH gr)
{
	if (!IS_NULL_graph(gr)) {
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		if (acc & dspec_mutable) {
			/* Virtual base class */
			GRAPH gt = DEREF_graph(graph_top(gr));
			CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
			ERROR err = ERR_class_derived_virt(cs, ct);
			return err;
		}
	}
	return NULL_err;
}


/*
    FIND A UNIQUE BASE CLASS

    This routine returns the graph representing the unique direct base
    class of ct if this exists.  Otherwise it adds an error to err and
    returns the null graph.
*/

GRAPH
uniq_base_class(CLASS_TYPE ct, ERROR *err)
{
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH)br = DEREF_list(graph_tails(gr));
	if (LENGTH_list(br) == 1) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		return gs;
	}
	add_error(err, ERR_class_base_init_uniq(ct));
	return NULL_graph;
}


/*
    FIND THE SHORTEST ROUTE TO A BASE CLASS

    There may be several path for accessing a virtual base class.  This
    routine finds the shortest such path in terms of virtual base
    indirections for reaching the base gr.
*/

GRAPH
min_base_class(GRAPH gr)
{
	GRAPH gs = gr;
	unsigned n = (unsigned)UINT_MAX;
	while (!IS_NULL_graph(gs)) {
		GRAPH gt = gs;
		unsigned m = 0;
		while (!IS_NULL_graph(gt)) {
			/* Find base class depth */
			DECL_SPEC acc = DEREF_dspec(graph_access(gt));
			if (acc & dspec_virtual) {
				m++;
			}
			gt = DEREF_graph(graph_up(gt));
		}
		if (m < n) {
			/* Shortest path so far */
			gr = gs;
			n = m;
		}
		gs = DEREF_graph(graph_equal(gs));
	}
	return gr;
}


/*
    FIND A DIRECT OR VIRTUAL BASE CLASS

    This routine checks whether the class cs denotes a direct or a virtual
    base class of ct.  If so it returns the corresponding graph.  If it is
    both then an error is added to err and the direct base is returned.
    Otherwise an error is added to err and the null graph is returned.
*/

GRAPH
direct_base_class(CLASS_TYPE ct, CLASS_TYPE cs, ERROR *err)
{
	GRAPH gt = NULL_graph;
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH)bd = DEREF_list(graph_tails(gr));
	LIST(GRAPH)bv = DEREF_list(ctype_vbase(ct));

	/* Scan through direct base classes */
	while (!IS_NULL_list(bd)) {
		GRAPH gs = DEREF_graph(HEAD_list(bd));
		CLASS_TYPE cr = DEREF_ctype(graph_head(gs));
		if (eq_ctype(cr, cs)) {
			gt = gs;
			break;
		}
		bd = TAIL_list(bd);
	}

	/* Scan through virtual base classes */
	while (!IS_NULL_list(bv)) {
		GRAPH gs = DEREF_graph(HEAD_list(bv));
		CLASS_TYPE cr = DEREF_ctype(graph_head(gs));
		if (eq_ctype(cr, cs)) {
			if (IS_NULL_graph(gt)) {
				gt = gs;
			} else if (!eq_graph(gt, gs)) {
				/* Both a direct and a virtual base */
				add_error(err, ERR_class_base_init_ambig(cs));
			}
			break;
		}
		bv = TAIL_list(bv);
	}

	/* Return result */
	if (IS_NULL_graph(gt)) {
		/* Neither a direct nor a virtual base */
		add_error(err, ERR_class_base_init_base(cs));
	}
	return gt;
}


/*
    FIND AN AMBIGUOUS BASE CLASS

    This routine searches the graph gr for any ambiguous base class,
    returning the corresponding node if it is found, or the null graph
    otherwise.
*/

GRAPH
find_ambig_base(GRAPH gr)
{
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if (acc & dspec_alias) {
		/* Ambiguous classes are marked */
		return gr;
	}
	if (acc & dspec_defn) {
		/* Only search the first occurrence of each class */
		LIST(GRAPH)br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			GRAPH gs = DEREF_graph(HEAD_list(br));
			gs = find_ambig_base(gs);
			if (!IS_NULL_graph(gs)) {
				return gs;
			}
			br = TAIL_list(br);
		}
	}
	return NULL_graph;
}


/*
    EXPAND A BASE CLASS GRAPH

    This routine expands any token definitions in the base class graph
    gr.  The null graph is returned if the result is not a valid base
    class.
*/

GRAPH
expand_graph(GRAPH gr, int rec)
{
	if (!IS_NULL_graph(gr)) {
		TYPE t = NULL_type;
		GRAPH gt = DEREF_graph(graph_top(gr));
		CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
		ct = expand_ctype(ct, rec, &t);
		if (IS_NULL_ctype(ct)) {
			return NULL_graph;
		}
		cs = expand_ctype(cs, rec, &t);
		if (IS_NULL_ctype(cs)) {
			return NULL_graph;
		}
		gr = find_base_class(ct, cs, 1);
	}
	return gr;
}


/*
    CONSTRUCT AN INHERITED IDENTIFIER

    This routine constructs an identifier representing the inherited value
    of id in the namespace ns.  gr and off give the corresponding base class
    if appropriate.
*/

static IDENTIFIER
inherit_id(NAMESPACE ns, GRAPH gr, OFFSET off, IDENTIFIER id, int prev)
{
	HASHID nm;
	DECL_SPEC ds;
	unsigned tag;
	NAMESPACE pns;
	IDENTIFIER cid;
	LIST(IDENTIFIER)p = NULL_list(IDENTIFIER);

	/* Check for trivial inheritance */
	if (IS_NULL_id(id)) {
		return NULL_id;
	}
	pns = DEREF_nspace(id_parent(id));
	if (EQ_nspace(pns, ns)) {
		return id;
	}

	/* Check for previous declarations */
	tag = TAG_id(id);
	nm = DEREF_hashid(id_name(id));
	if (!IS_NULL_graph(gr) && !prev) {
		LIST(IDENTIFIER)q;
		p = DEREF_list(graph_member(gr));
		q = p;
		while (!IS_NULL_list(q)) {
			IDENTIFIER qid = DEREF_id(HEAD_list(q));
			HASHID qnm = DEREF_hashid(id_name(qid));
			if (EQ_hashid(qnm, nm) && tag == TAG_id(qid)) {
				/* Already have inherited member */
				return qid;
			}
			q = TAIL_list(q);
		}
	}

	/* Calculate inherited access */
	ds = DEREF_dspec(id_storage(id));
	if (!IS_NULL_graph(gr)) {
		int adjust = 1;
		if (tag == id_class_name_tag) {
			CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
			TYPE t = DEREF_type(id_class_name_defn(id));
			if (IS_type_compound(t)) {
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				if (eq_ctype(cs, ct)) {
					/* This is an injected base class
					 * name */
					adjust = 0;
				}
			}
		}
		if (adjust) {
			DECL_SPEC acc = DEREF_dspec(graph_access(gr));
			DECL_SPEC acc2 = unshadow_access(acc);
			acc = join_access(ds, acc);
			acc2 = join_access(ds, acc2);
			ds &= ~(dspec_access | dspec_access2);
			ds |= acc;
			ds |= shadow_access(acc2);
		}
	}
	ds |= dspec_inherit;
	ds &= ~dspec_alias;

	/* Copy the identifier */
	cid = copy_id(id, 0);
	if (!EQ_id(cid, id)) {
		switch (tag) {
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Functions */
			IDENTIFIER over;
			over = DEREF_id(id_function_etc_over(cid));
			if (!IS_NULL_id(over)) {
				/* Overloaded functions */
				over = inherit_id(ns, gr, off, over, 1);
				COPY_id(id_function_etc_over(cid), over);
			}
			break;
		}
		case id_member_tag: {
			/* Members */
			if (!IS_NULL_graph(gr)) {
				/* Add base class offset */
				OFFSET off1 = DEREF_off(id_member_off(cid));
				MAKE_off_plus(off, off1, off1);
				COPY_off(id_member_off(cid), off1);
				COPY_graph(id_member_base(cid), gr);
			}
			break;
		}
		}
		COPY_nspace(id_parent(cid), ns);
		COPY_dspec(id_storage(cid), ds);
	}

	/* Add to list of inherited members */
	if (!IS_NULL_graph(gr) && !prev) {
		CONS_id(cid, p, p);
		COPY_list(graph_member(gr), p);
	}
	return cid;
}


/*
    TYPE REPRESENTING A SET OF MEMBER LOOK-UPS

    This structure is used to represent a list of class member look-ups.
    Each look-up consists of a member identifier plus a base class graph
    indicating from which base class it is inherited.
*/

typedef struct {
	LIST(IDENTIFIER) ids;
	LIST(GRAPH) bases;
} MEMBER_LOOKUP;


/*
    RESOLVE AMBIGUOUS MEMBER LOOK-UP

    This routine resolves the potentially ambiguous member look-up for the
    member named nm in the namespace ns given by mems.  If form is not
    the null type then it gives a list of template arguments to be
    applied to nm.  The routine also destroys mems.
*/

static IDENTIFIER
resolve_member(NAMESPACE ns, HASHID nm, MEMBER_LOOKUP *mems, TYPE form,
	       int dominate)
{
	IDENTIFIER id = NULL_id;
	LIST(IDENTIFIER)ambig = NULL_list(IDENTIFIER);
	LIST(IDENTIFIER)pids = mems->ids;
	LIST(GRAPH)grs = mems->bases;

	/* Check for empty lists */
	if (IS_NULL_list(pids)) {
		return NULL_id;
	}

	/* Scan through various look-ups */
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		GRAPH gp = DEREF_graph(HEAD_list(grs));
		if (!IS_NULL_id(pid)) {
			int ok = 1;
			int dep = IS_id_member(pid);
			IDENTIFIER pal = DEREF_id(id_alias(pid));
			DECL_SPEC pds = DEREF_dspec(id_storage(pid));
			DECL_SPEC gds = DEREF_dspec(graph_access(gp));
			DECL_SPEC acc = join_access(pds, gds);
			OFFSET off = DEREF_off(graph_off(gp));

			/* Mark equivalent look-ups */
			LIST(IDENTIFIER)qids = TAIL_list(pids);
			LIST(GRAPH)hrs = TAIL_list(grs);
			while (!IS_NULL_list(qids)) {
				IDENTIFIER qid = DEREF_id(HEAD_list(qids));
				IDENTIFIER qal = DEREF_id(id_alias(qid));
				GRAPH hp = DEREF_graph(HEAD_list(hrs));
				if (EQ_id(pal, qal)) {
					if (!dep || eq_graph(gp, hp)) {
						/* This represents the same
						 * member */
						DECL_SPEC acc2;
						COPY_id(HEAD_list(qids),
							NULL_id);
						pds = DEREF_dspec(id_storage(qid));
						gds = DEREF_dspec(graph_access(hp));
						acc2 = join_access(pds, gds);
						if (acc2 < acc) {
							/* More accessible by
							 * this route */
							gp = hp;
							acc = acc2;
						}
					}
				} else {
					/* Check for dominating bases */
					if (is_subgraph(gp, hp)) {
						if (dominate) {
							COPY_id(HEAD_list(qids),
								NULL_id);
						}
					} else if (is_subgraph(hp, gp)) {
						ok = 0;
						break;
					}
				}
				qids = TAIL_list(qids);
				hrs = TAIL_list(hrs);
			}

			/* Record look-up */
			if (ok) {
				int prev = 0;
				if (!IS_NULL_type(form) &&
				    IS_type_token(form)) {
					/* Allow for templates */
					LIST(TOKEN)args;
					args =
					    DEREF_list(type_token_args(form));
					pid = apply_template(pid, args, 0, 0);
					prev = 1;
				}
				pid = inherit_id(ns, gp, off, pid, prev);
				if (IS_NULL_id(id)) {
					id = pid;
				} else {
					CONS_id(pid, ambig, ambig);
				}
			}
		}
		pids = TAIL_list(pids);
		grs = TAIL_list(grs);
	}

	/* Construct the result */
	if (!IS_NULL_list(ambig)) {
		DECL_SPEC ds;
		CONS_id(id, ambig, ambig);
		ds = find_ambig_dspec(ambig);
		ds |= dspec_inherit;
		MAKE_id_ambig(nm, ds, ns, crt_loc, ambig, 1, id);
	}

	/* Destroy lists */
	DESTROY_list(mems->ids, SIZE_id);
	DESTROY_list(mems->bases, SIZE_graph);
	return id;
}


/*
    SEARCH A BASE CLASS GRAPH FOR AN IDENTIFIER

    This routine searches the graph gr for all visible members named nm,
    storing the result in mems.  If cs is not the null class then only
    base classes lying below such a class are searched.  If type is nonzero
    then only type members are found.  depth gives a depth count and is
    used because the top level is searched elsewhere.
*/

static void
search_base(GRAPH gr, HASHID nm, MEMBER_LOOKUP *mems, CLASS_TYPE cs, int type,
	    int depth)
{
	LIST(GRAPH)br;
	LIST(GRAPH)gres = NULL_list(GRAPH);
	LIST(IDENTIFIER)res = NULL_list(IDENTIFIER);
	DECL_SPEC acc = DEREF_dspec(graph_access(gr));
	if (!(acc & dspec_done)) {
		/* Not yet in scope */
		mems->ids = res;
		mems->bases = gres;
		return;
	}

	/* Search derived class */
	if (depth) {
		CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
		if (IS_NULL_ctype(cs) || eq_ctype(ct, cs)) {
			NAMESPACE ns = DEREF_nspace(ctype_member(ct));
			IDENTIFIER id = search_id(ns, nm, 0, type);
			if (!IS_NULL_id(id)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if ((ds & dspec_inherit) &&
				    !(ds & dspec_alias)) {
					/* Ignore inherited members */
					/* EMPTY */
				} else {
					CONS_id(id, res, res);
					CONS_graph(gr, gres, gres);
					mems->ids = res;
					mems->bases = gres;
					return;
				}
			}
			cs = NULL_ctype;
		}
	}

	/* Search base classes */
	br = DEREF_list(graph_tails(gr));
	while (!IS_NULL_list(br)) {
		MEMBER_LOOKUP bmems;
		GRAPH gs = DEREF_graph(HEAD_list(br));
		search_base(gs, nm, &bmems, cs, type, depth + 1);
		if (!IS_NULL_list(bmems.ids)) {
			res = APPEND_list(res, bmems.ids);
			gres = APPEND_list(gres, bmems.bases);
		}
		br = TAIL_list(br);
	}
	mems->ids = res;
	mems->bases = gres;
	return;
}


/*
    SEARCH BASE CLASSES FOR A CLASS MEMBER

    This routine searches the base classes of the class namespace ns
    for a member named nm.
*/

IDENTIFIER
search_base_field(NAMESPACE ns, HASHID nm, int type, int dominate)
{
	GRAPH gr;
	IDENTIFIER id;
	CLASS_TYPE ct;
	MEMBER_LOOKUP mems;
	IDENTIFIER cid = DEREF_id(nspace_name(ns));
	TYPE t = DEREF_type(id_class_name_etc_defn(cid));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ct = DEREF_ctype(type_compound_defn(t));
	gr = DEREF_graph(ctype_base(ct));
	search_base(gr, nm, &mems, NULL_ctype, type, 0);
	id = resolve_member(ns, nm, &mems, NULL_type, dominate);
	return id;
}


/*
    SEARCH FOR A CLASS MEMBER

    This routine searches the class namespace ns and its base classes
    for a member named nm, which is returned if found.  Otherwise if
    create is true then a dummy identifier is created and returned.
    Otherwise the null identifier is returned.  If type is true then only
    type and namespace names are considered.
*/

IDENTIFIER
search_field(NAMESPACE ns, HASHID nm, int create, int type)
{
	/* Search main class */
	IDENTIFIER id;
	MEMBER mem = search_member(ns, nm, 1);
	if (type) {
		id = type_member(mem, type);
	} else {
		id = DEREF_id(member_id(mem));
	}

	/* Search base classes */
	if (IS_NULL_id(id)) {
		id = search_base_field(ns, nm, type, 1);
		if (!IS_NULL_id(id)) {
			if (type) {
				set_type_member(mem, id);
			} else {
				set_member(mem, id);
			}
			if (IS_hashid_destr(nm)) {
				/* Check destructor names */
				report(crt_loc, ERR_class_dtor_inherit(nm, ns));
			}
		} else {
			if (create) {
				/* Create dummy identifier if necessary */
				MAKE_id_undef(nm, dspec_none, ns, crt_loc, id);
			}
			if (IS_hashid_destr(nm)) {
				/* Check destructor names */
				TYPE s = DEREF_type(hashid_destr_type(nm));
				IDENTIFIER tid = DEREF_id(nspace_name(ns));
				TYPE t =
				    DEREF_type(id_class_name_etc_defn(tid));
				if (!eq_type(s, t)) {
					report(crt_loc,
					       ERR_expr_pseudo_type(t, s));
				}
			}
		}
	}
	return id;
}


/*
    IS AN IDENTIFIER A MEMBER OF A CLASS?

    This routine checks whether the identifier id is a member of the class
    namespace ns or any base class of ns.  It returns the corresponding
    base class graph, or the null graph if id is not such a member.
*/

GRAPH
is_subfield(NAMESPACE ns, IDENTIFIER id)
{
	CLASS_TYPE ct = namespace_class(ns);
	if (!IS_NULL_ctype(ct)) {
		NAMESPACE cns = DEREF_nspace(id_parent(id));
		if (!IS_NULL_nspace(cns) && IS_nspace_ctype(cns)) {
			CLASS_TYPE cs = namespace_class(cns);
			GRAPH gr = find_base_class(ct, cs, 0);
			return gr;
		}
	}
	return NULL_graph;
}


/*
    SEARCH FOR A SUBFIELD

    This routine finds the member of a class corresponding to the member
    id of the base class of ns indicated by gr.
*/

IDENTIFIER
search_subfield(NAMESPACE ns, GRAPH gr, IDENTIFIER id)
{
	GRAPH gt = DEREF_graph(graph_top(gr));
	if (!EQ_graph(gr, gt)) {
		int def = 0;
		IDENTIFIER pid;
		MEMBER_LOOKUP mems;
		TYPE form = find_form(id, &def);
		HASHID nm = DEREF_hashid(id_name(id));
		DECL_SPEC acc = DEREF_dspec(graph_access(gr));
		if (acc & dspec_alias) {
			/* Ambiguous base class */
			CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
			search_base(gt, nm, &mems, cs, 0, 1);
		} else {
			/* Unambiguous base class */
			search_base(gr, nm, &mems, NULL_ctype, 0, 1);
		}
		pid = resolve_member(ns, nm, &mems, form, 1);
		if (!IS_NULL_id(pid)) {
			id = pid;
		}
	}
	return id;
}


/*
    PROCESS INHERITANCE FOR A CLASS

    This routine is called at the end of a class definition to handle
    any inheritance issues.  At present an inherited member is only
    recorded as it is looked up.  However the lists of all virtual
    functions and conversion functions on the class need to take account
    of inheritance immediately.
*/

void
inherit_class(void)
{
	CLASS_TYPE ct = crt_class;
	NAMESPACE ns = crt_namespace;
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH)bases = DEREF_list(graph_tails(gr));
	LIST(IDENTIFIER)pc = DEREF_list(ctype_conv(ct));

	/* Scan through base classes */
	while (!IS_NULL_list(bases)) {
		GRAPH gs = DEREF_graph(HEAD_list(bases));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));

		/* Deal with conversion functions */
		LIST(IDENTIFIER)qc = DEREF_list(ctype_conv(cs));
		while (!IS_NULL_list(qc)) {
			/* Deal with each inherited conversion */
			IDENTIFIER qid = DEREF_id(HEAD_list(qc));
			HASHID qnm = DEREF_hashid(id_name(qid));
			LIST(IDENTIFIER)r = pc;
			while (!IS_NULL_list(r)) {
				/* Check whether already declared */
				IDENTIFIER rid = DEREF_id(HEAD_list(r));
				HASHID rnm = DEREF_hashid(id_name(rid));
				if (EQ_hashid(rnm, qnm)) {
					break;
				}
				r = TAIL_list(r);
			}
			if (IS_NULL_list(r)) {
				/* Construct inherited member */
				qid = search_field(ns, qnm, 0, 0);
				if (!IS_NULL_id(qid)) {
					if (IS_id_ambig(qid)) {
						LIST(IDENTIFIER)qids;
						qids = DEREF_list(id_ambig_ids(qid));
						while (!IS_NULL_list(qids)) {
							qid = DEREF_id(HEAD_list(qids));
							CONS_id(qid, pc, pc);
							qids = TAIL_list(qids);
						}
					} else {
						CONS_id(qid, pc, pc);
					}
				}
			}
			qc = TAIL_list(qc);
		}

		/* Process next base class */
		bases = TAIL_list(bases);
	}

	/* Record modified information */
	COPY_list(ctype_conv(ct), pc);

	/* Deal with virtual functions */
	end_virtual(ct);
	return;
}
