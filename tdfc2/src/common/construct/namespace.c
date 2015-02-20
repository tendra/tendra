/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/print.h>
#include <utility/ustring.h>

#include "ctype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include "access.h"
#include "class.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "hash.h"
#include "identifier.h"
#include "instance.h"
#include "label.h"
#include "namespace.h"
#include "parse.h"
#include "predict.h"
#include "redeclare.h"
#include "syntax.h"
#include "tokdef.h"
#include "variable.h"


/*
    These variables give the current namespace (the one which is currently
    being defined) and the stack of all enclosing namespaces.  Another stack
    of namespaces, which will be a superset of the first, gives the list
    of locations to be searched during name look-up.
*/

NAMESPACE crt_namespace = NULL_nspace;
NAMESPACE last_namespace = NULL_nspace;
NAMESPACE qual_namespace = NULL_nspace;
STACK(NAMESPACE) namespace_stack = NULL_stack(NAMESPACE);
STACK(NAMESPACE) crt_nspace_stack = NULL_stack(NAMESPACE);
STACK(NAMESPACE) local_nspace_stack = NULL_stack(NAMESPACE);


/*
    These variables give the various standard namespaces, including the
    global namespace and the external token namespace.  In addition a
    dynamic record of the smallest named namespace enclosing the current
    namespace and the smallest named or block namespace (or, if the
    proto_scope option is true, function prototype namespace) enclosing
    the current namespace are maintained in nonblock_namespace and
    nonclass_namespace respectively.
*/

NAMESPACE global_namespace = NULL_nspace;
NAMESPACE token_namespace = NULL_nspace;
NAMESPACE c_namespace = NULL_nspace;
NAMESPACE nonblock_namespace = NULL_nspace;
NAMESPACE nonclass_namespace = NULL_nspace;
static NAMESPACE scope_namespace = NULL_nspace;


/*
    The identifier local_namespace_id is used as the name for all unnamed
    namespaces defined within the current translation unit.
*/

static IDENTIFIER local_namespace_id = NULL_id;


/*
    This flag is set to indicate that name look-up should be cached
    whenever possible.  It is switched off temporarily in field selectors
    as an optimisation.
*/

int cache_lookup = 1;
int old_cache_lookup = 1;


/*
    This routine creates a global namespace of size sz with a dummy name
    given by s.
*/

NAMESPACE
make_global_nspace(const char *s, int sz)
{
	IDENTIFIER id;
	string u = ustrlit(s);
	NAMESPACE ns = NULL_nspace;
	DECL_SPEC ds = (dspec_defn | dspec_extern);
	HASHID nm = lookup_name(u, hash(u), 1, lex_identifier);
	MAKE_id_nspace_name(nm, ds, NULL_nspace, crt_loc, ns, id);
	ns = make_namespace(id, nspace_global_tag, sz);
	COPY_nspace(id_nspace_name_defn(id), ns);
	return ns;
}


/*
    This routine initialises the standard namespaces above.
*/

void
init_namespace(void)
{
	string s = ustrlit("<local>");
	HASHID nm = lookup_name(s, hash(s), 1, lex_identifier);
	local_namespace_id = DEREF_id(hashid_id(nm));
	global_namespace = make_global_nspace("<global>", 50);
#if LANGUAGE_CPP
	c_namespace = make_global_nspace("<c>", 50);
#endif
	token_namespace = make_global_nspace("<token>", 50);
	scope_namespace = make_global_nspace("<scope>", 50);
	last_namespace = global_namespace;
	old_cache_lookup = cache_lookup;
	return;
}


/*
    This routine checks whether the namespace ns contains the definition
    of the namespace pns.
*/

int
is_subnspace(NAMESPACE ns, NAMESPACE pns)
{
	if (EQ_nspace(ns, pns)) {
		return 1;
	}
	while (!IS_NULL_nspace(pns)) {
		pns = DEREF_nspace(nspace_parent(pns));
		if (EQ_nspace(ns, pns)) {
			return 1;
		}
	}
	return 0;
}


/*
    This routine finds the join of the namespaces ns and nt, that is to
    say the smallest namespace which contains both ns and nt.  A using
    directive for nt in ns causes the members of nt to be treated as
    members of the join namespace for the purposes of unqualified name
    look-up.
*/

static NAMESPACE
join_namespace(NAMESPACE ns, NAMESPACE nt)
{
	while (!EQ_nspace(ns, nt)) {
		if (IS_NULL_nspace(ns)) {
			return NULL_nspace;
		}
		if (IS_NULL_nspace(nt)) {
			return NULL_nspace;
		}
		if (is_subnspace(ns, nt)) {
			return ns;
		}
		if (is_subnspace(nt, ns)) {
			return nt;
		}
		ns = DEREF_nspace(nspace_parent(ns));
		nt = DEREF_nspace(nspace_parent(nt));
	}
	return ns;
}


/*
    This routine clears the cached name look-ups for all the names
    accessible from the namespace ns.
*/

void
uncache_namespace(NAMESPACE ns, int add)
{
	if (!IS_NULL_nspace(ns) && cache_lookup) {
		MEMBER mem;
		LIST(NAMESPACE) uns;

		/* Clear cache fields for all members */
		if (IS_nspace_named_etc(ns)) {
			mem = DEREF_member(nspace_named_etc_first(ns));
		} else {
			mem = DEREF_member(nspace_last(ns));
		}
		while (!IS_NULL_member(mem)) {
			IDENTIFIER id = DEREF_id(member_id(mem));
			if (!IS_NULL_id(id)) {
				HASHID nm = DEREF_hashid(id_name(id));
				if (!add) {
					id = NULL_id;
				}
				COPY_id(hashid_cache(nm), id);
			}
			mem = DEREF_member(member_next(mem));
		}

		/* Recursively clear all used namespaces */
		uns = DEREF_list(nspace_use(ns));
		if (!IS_NULL_list(uns)) {
			LIST(NAMESPACE) lns = uns;
			COPY_list(nspace_use(ns), NULL_list(NAMESPACE));
			while (!IS_NULL_list(lns)) {
				NAMESPACE pns = DEREF_nspace(HEAD_list(lns));
				uncache_namespace(pns, 0);
				lns = TAIL_list(lns);
			}
			COPY_list(nspace_use(ns), uns);
		}
	}
	return;
}


/*
    This routine adds the namespace ns to the look-up namespace list.  Note
    that this is automatically called by push_namespace.
*/

void
add_namespace(NAMESPACE ns)
{
	PUSH_nspace(ns, namespace_stack);
	uncache_namespace(ns, 1);
	return;
}


/*
    This routine removes the top namespace from the look-up namespace list.
    Note that this is automatically called by pop_namespace.
*/

void
remove_namespace(void)
{
	NAMESPACE ns;
	POP_nspace(ns, namespace_stack);
	uncache_namespace(ns, 0);
	return;
}


/*
    This routine pushes the namespace ns onto the namespace stack.
*/

void
store_namespace(NAMESPACE ns)
{
	NAMESPACE cns = crt_namespace;
	switch (TAG_nspace(ns)) {
	case nspace_named_tag:
	case nspace_unnamed_tag:
	case nspace_global_tag:
		/* Record named namespaces */
		nonblock_namespace = ns;
		nonclass_namespace = ns;
		break;
	case nspace_param_tag:
		/* Deal with function prototype scopes */
		if (option(OPT_proto_scope)) {
			nonclass_namespace = ns;
		}
		break;
	case nspace_block_tag:
		/* A block is a non-class namespace */
		nonclass_namespace = ns;
		break;
	}
	COPY_nspace(nspace_parent(ns), cns);
	PUSH_nspace(cns, crt_nspace_stack);
	crt_namespace = ns;
	return;
}


/*
    This routine removes a namespace from the namespace stack.
*/

NAMESPACE
restore_namespace(void)
{
	NAMESPACE ns = crt_namespace;
	int fb = EQ_nspace(ns, nonblock_namespace);
	int fc = EQ_nspace(ns, nonclass_namespace);
	int fa = (fb || fc);
	if (fa) {
		/* Check for enclosing namespaces */
		LIST(NAMESPACE) lns = LIST_stack(crt_nspace_stack);
		while (fa && !IS_NULL_list(lns)) {
			NAMESPACE pns = DEREF_nspace(HEAD_list(lns));
			switch (TAG_nspace(pns)) {
			case nspace_named_tag:
			case nspace_unnamed_tag:
			case nspace_global_tag:
				if (fb) {
					/* Non-block namespace found */
					nonblock_namespace = pns;
					fa = fc;
					fb = 0;
				}
				goto nonclass_namespace_lab;
			case nspace_param_tag:
				/* Deal with function prototype scopes */
				if (!option(OPT_proto_scope)) {
					break;
				}
				goto nonclass_namespace_lab;
			case nspace_block_tag:
nonclass_namespace_lab:
				if (fc) {
					/* Non-class namespace found */
					nonclass_namespace = pns;
					fa = fb;
					fc = 0;
				}
				break;
			}
			lns = TAIL_list(lns);
		}
	}
	POP_nspace(crt_namespace, crt_nspace_stack);
	return ns;
}


/*
    This routine makes the namespace ns into the current namespace, pushing
    the previous namespace onto the stack.
*/

void
push_namespace(NAMESPACE ns)
{
	store_namespace(ns);
	add_namespace(ns);
	return;
}


/*
    This routine restores the current namespace to its previous value by
    popping it from the stack.  It returns the removed namespace.
*/

NAMESPACE
pop_namespace(void)
{
	NAMESPACE ns = restore_namespace();
	remove_namespace();
	return ns;
}


/*
    This routine forces the recalculation of nonblock_namespace and
    nonclass_namespace by pushing and immediately popping the global
    namespace.
*/

void
update_namespace(void)
{
	NAMESPACE ns = global_namespace;
	if (!IS_NULL_nspace(ns)) {
		store_namespace(ns);
		IGNORE restore_namespace();
	}
	return;
}


/*
    This routine creates a namespace named id of type tag.  If tag is
    indicates a small namespace then sz will be zero.  Otherwise sz gives
    the size of hash table to be created.
*/

NAMESPACE
make_namespace(IDENTIFIER id, unsigned tag, int sz)
{
	NAMESPACE ns;
	NAMESPACE pns;
	if (!IS_NULL_id(id)) {
		pns = DEREF_nspace(id_parent(id));
	} else {
		pns = crt_namespace;
	}
	if (sz == 0) {
		/* Small namespace */
		MAKE_nspace_block_etc(tag, id, pns, ns);
	} else {
		/* Large namespace */
		PTR(MEMBER) ptr;
		SIZE(MEMBER) psz;
		unsigned long i, n = (unsigned long)sz;

		/* Allocate namespace hash table */
		psz = SCALE(SIZE_member, n);
		ptr = MAKE_ptr(psz);
		MAKE_nspace_named_etc(tag, id, pns, n, ptr, ns);

		/* Initialise hash table entries */
		for (i = 0; i < n; i++) {
			COPY_member(ptr, NULL_member);
			ptr = STEP_ptr(ptr, SIZE_member);
		}
	}
	return ns;
}


/*
    This routine creates a using directive for the namespace ns in
    the namespace cns.  nt gives the join of cns and ns.  The routine
    returns zero to indicate that ns has already been used from cns.
*/

int
use_namespace(NAMESPACE ns, NAMESPACE cns, NAMESPACE nt)
{
	if (!EQ_nspace(cns, ns)) {
		LIST(NAMESPACE) p = DEREF_list(nspace_use(cns));
		LIST(NAMESPACE) r = DEREF_list(nspace_join(cns));
		LIST(NAMESPACE) q = p;
		while (!IS_NULL_list(q)) {
			NAMESPACE qns = DEREF_nspace(HEAD_list(q));
			if (EQ_nspace(qns, ns)) {
				return 0;
			}
			q = TAIL_list(q);
		}
		CONS_nspace(nt, r, r);
		COPY_list(nspace_join(cns), r);
		CONS_nspace(ns, p, p);
		COPY_list(nspace_use(cns), p);
		return 1;
	}
	return 0;
}


/*
    During unqualified name look-up any using-directives are treated as
    injecting the names from the used namespace into the join on the
    used and the using namespaces.  This is implemented by injecting a
    dummy using-directive into the join namespace.  This list is used
    to keep track of all the join namespaces which have using-directives
    injected in this way.
*/

static LIST(NAMESPACE) join_nspaces = NULL_list(NAMESPACE);


/*
    This routine removes any dummy using-directives from the list of join
    namespaces above.
*/

static void
clear_join_nspaces(void)
{
	LIST(NAMESPACE) lns = join_nspaces;
	while (!IS_NULL_list(lns)) {
		NAMESPACE ns;
		NAMESPACE dns;
		LIST(NAMESPACE) p;
		DESTROY_CONS_nspace(destroy, ns, lns, lns);
		p = DEREF_list(nspace_use(ns));
		if (!IS_NULL_list(p)) {
			DESTROY_CONS_nspace(destroy, dns, p, p);
			UNUSED(dns);
			COPY_list(nspace_use(ns), p);
		}
		p = DEREF_list(nspace_join(ns));
		if (!IS_NULL_list(p)) {
			DESTROY_CONS_nspace(destroy, dns, p, p);
			UNUSED(dns);
			COPY_list(nspace_join(ns), p);
		}
	}
	join_nspaces = NULL_list(NAMESPACE);
	return;
}


/*
    This routine begins the definition of a namespace named id (or an
    anonymous namespace if anon is true).  Note that there may be multiple
    definitions of a namespace, the effect of the later definitions being
    to add elements to the existing namespace.  Only original namespace
    names, and not namespace aliases, can be used in these namespace
    extensions.
*/

void
begin_namespace(IDENTIFIER id, int anon)
{
	HASHID nm;
	MEMBER mem;
	IDENTIFIER old_id;
	NAMESPACE ns = NULL_nspace;
	NAMESPACE cns = crt_namespace;
	unsigned tag = nspace_named_tag;

	/* Find name for anonymous namespaces */
	if (anon) {
		id = local_namespace_id;
		tag = nspace_unnamed_tag;
	}
	nm = DEREF_hashid(id_name(id));

	/* Can only occur in namespace scope */
	if (in_function_defn || in_class_defn) {
		report(crt_loc, ERR_dcl_nspace_scope());
	}

	/* Look up namespace name */
	mem = search_member(cns, nm, 1);
	old_id = DEREF_id(member_id(mem));
	if (!IS_NULL_id(old_id)) {
		/* Check for redeclarations */
		old_id = redecl_inherit(old_id, qual_none, in_class_defn, 2);
		switch (TAG_id(old_id)) {
		case id_nspace_name_tag:
			/* Previously defined namespace */
			ns = DEREF_nspace(id_nspace_name_defn(old_id));
			break;
		case id_nspace_alias_tag: {
			/* Previously defined namespace alias */
			IDENTIFIER ns_id;
			ns = DEREF_nspace(id_nspace_alias_defn(old_id));
			ns_id = DEREF_id(nspace_name(ns));
			if (!IS_id_nspace_name(ns_id)) {
				/* Alias for class namespace */
				ns = NULL_nspace;
				goto default_lab;
			}
			report(crt_loc, ERR_dcl_nspace_def_orig(ns_id, old_id));
			break;
		}
		default:
default_lab: {
		     /* Other previously defined identifier */
		     PTR(LOCATION) loc = id_loc(old_id);
		     report(crt_loc, ERR_basic_odr_decl(old_id, loc));
		     break;
	     }
		}
	}

	/* Construct the namespace if necessary */
	if (IS_NULL_nspace(ns)) {
		DECL_SPEC ds = (dspec_defn | dspec_extern);
		MAKE_id_nspace_name(nm, ds, cns, decl_loc, ns, id);
		ns = make_namespace(id, tag, 50);
		COPY_nspace(id_nspace_name_defn(id), ns);
		set_member(mem, id);
		if (anon) {
			/* Anonymous namespaces are implicitly used */
			IGNORE use_namespace(ns, cns, cns);
			if (do_dump) {
				dump_using(ns, cns, &decl_loc);
			}
		}
	}

	/* Adjust the current namespace */
	if (do_dump) {
		dump_declare(id, &decl_loc, 1);
	}
	push_namespace(ns);
	cns = DEREF_nspace(id_parent(id));
	COPY_nspace(nspace_parent(ns), cns);
	return;
}


/*
    This routine ends the definition of the current namespace.
*/

void
end_namespace(int anon)
{
	NAMESPACE ns;
	clear_decl_blocks();
	ns = pop_namespace();
	if (do_dump) {
		IDENTIFIER id = DEREF_id(nspace_name(ns));
		dump_undefine(id, &crt_loc, 0);
	}
	UNUSED(anon);
	return;
}


/*
    This routine is called in the processing of target dependent
    preprocessing directives within declaration sequences.  The directive
    involved is given by dir, while c gives the associated condition for
    '#if' and '#elif'.
*/

void
target_decl(int dir, EXP c)
{
	if (!IS_NULL_exp(c)) {
		report(crt_loc, ERR_cpp_cond_if_ti_decl(dir));
	}
	return;
}


/*
    A declaration block is a technique for partitioning the external
    declarations into subsets.  These subsets have no significance within
    the language, but are useful for indicating, for example, those
    identifiers which form part of a certain API.  This routine starts
    a declaration block named id.
*/

void
begin_decl_block(IDENTIFIER id)
{
	NAMESPACE cns = nonblock_namespace;
	NAMESPACE sns = scope_namespace;
	HASHID nm = DEREF_hashid(id_name(id));
	MEMBER mem = search_member(sns, nm, 1);
	id = DEREF_id(member_id(mem));
	if (IS_NULL_id(id)) {
		/* Create dummy namespace identifier */
		NAMESPACE bns = NULL_nspace;
		DECL_SPEC ds = (dspec_defn | dspec_extern);
		MAKE_id_nspace_name(nm, ds, cns, crt_loc, bns, id);
		bns = make_namespace(id, nspace_block_tag, 0);
		COPY_nspace(id_nspace_name_defn(id), bns);
		COPY_id(member_id(mem), id);
	}
	if (do_dump) {
		/* Output scope to dump file */
		NAMESPACE bns = DEREF_nspace(id_nspace_name_defn(id));
		dump_begin_scope(id, bns, cns, &crt_loc);
	}
	if (!IS_NULL_nspace(cns)) {
		/* Add to current namespace */
		STACK(IDENTIFIER)pids = DEREF_stack(nspace_set(cns));
		PUSH_id(id, pids);
		COPY_stack(nspace_set(cns), pids);
	}
	return;
}


/*
    This routine ends a declaration block named id or the current
    declaration block if id is the null identifier.  If there is no
    current declaration block and force is true then an error is
    raised.  The routine returns true if a declaration block is ended.
*/

int
end_decl_block(IDENTIFIER id, int force)
{
	int res = 0;
	NAMESPACE cns = nonblock_namespace;
	if (!IS_NULL_nspace(cns)) {
		/* Add to current namespace */
		STACK(IDENTIFIER) pids = DEREF_stack(nspace_set(cns));
		if (IS_NULL_stack(pids)) {
			if (force) {
				/* Stack shouldn't be empty */
				report(crt_loc, ERR_pragma_dblock_end());
			}
		} else {
			IDENTIFIER pid;
			POP_id(pid, pids);
			COPY_stack(nspace_set(cns), pids);
			if (!IS_NULL_id(id)) {
				/* Check block name if given */
				HASHID nm = DEREF_hashid(id_name(id));
				HASHID pnm = DEREF_hashid(id_name(pid));
				if (!EQ_hashid(nm, pnm)) {
					report(crt_loc,
					       ERR_pragma_dblock_name(pnm));
				}
			}
			if (do_dump) {
				/* Output scope to dump file */
				NAMESPACE bns =
				    DEREF_nspace(id_nspace_name_defn(pid));
				dump_end_scope(pid, bns, &crt_loc);
			}
			res = 1;
		}
	}
	return res;
}


/*
    This routine ends all the declaration blocks associated with the
    current namespace.  This is called at the end of a namespace definition
    and at the end of the input file.
*/

void
clear_decl_blocks(void)
{
	while (end_decl_block(NULL_id, 0));
	return;
}


/*
    This routine finds the namespace corresponding to the identifier id,
    returning the null namespace if id does not represent a class or a
    namespace.
*/

NAMESPACE
find_namespace(IDENTIFIER id)
{
	NAMESPACE ns = NULL_nspace;
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_nspace_name_tag:
		case id_nspace_alias_tag:
			/* Explicitly named namespaces */
			ns = DEREF_nspace(id_nspace_name_etc_defn(id));
			break;
		case id_class_name_tag:
		case id_class_alias_tag: {
			/* Class namespaces */
			TYPE t = DEREF_type(id_class_name_etc_defn(id));
			if (IS_type_compound(t)) {
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				complete_class(ct, 1);
				ns = DEREF_nspace(ctype_member(ct));
			} else {
				CLASS_TYPE ct = find_class(id);
				if (!IS_NULL_ctype(ct)) {
					complete_class(ct, 1);
					ns = DEREF_nspace(ctype_member(ct));
				}
			}
			break;
		}
		}
	}
	return ns;
}


/*
    This routine looks up the identifier id as a namespace name in a
    namespace alias or namespace directive.
*/

NAMESPACE
find_nspace_id(IDENTIFIER id)
{
	NAMESPACE ns;
	if (IS_id_nspace_name_etc(id)) {
		ns = DEREF_nspace(id_nspace_name_etc_defn(id));
	} else {
		if (crt_templ_qualifier == 0) {
			HASHID nm = DEREF_hashid(id_name(id));
			if (crt_id_qualifier == qual_none) {
				IDENTIFIER nid = find_type_id(nm, 2);
				if (!IS_NULL_id(nid)) {
					id = nid;
				}
			} else {
				NAMESPACE pns = DEREF_nspace(id_parent(id));
				IDENTIFIER nid = find_qual_id(pns, nm, 0, 2);
				if (!IS_NULL_id(nid)) {
					id = nid;
				}
			}
		}
		ns = find_namespace(id);
		if (IS_NULL_nspace(ns)) {
			/* Invalid namespace identifier */
			report(crt_loc, ERR_dcl_nspace_undef(id));
			return NULL_nspace;
		}
	}
	use_id(id, 0);
	return ns;
}


/*
    This routine sets up id as an alias for the namespace ns.  A namespace
    alias may be consistently redefined any number of times.
*/

void
alias_namespace(IDENTIFIER id, NAMESPACE ns)
{
	MEMBER mem;
	IDENTIFIER old_id;
	NAMESPACE cns = crt_namespace;
	HASHID nm = DEREF_hashid(id_name(id));
	DECL_SPEC ds = (dspec_defn | dspec_extern);
	if (IS_NULL_nspace(ns)) {
		/* Invalid namespace identifier */
		begin_namespace(id, 0);
		end_namespace(0);
		return;
	}
	if (IS_nspace_ctype(ns)) {
		/* Can't have a class namespace */
		report(crt_loc, ERR_dcl_nspace_alias_class(ns));
	}

	/* Look up namespace alias name */
	mem = search_member(cns, nm, 1);
	old_id = DEREF_id(member_id(mem));

	/* Check for redeclarations */
	if (!IS_NULL_id(old_id)) {
		old_id = redecl_inherit(old_id, qual_none, in_class_defn, 2);
		switch (TAG_id(old_id)) {
		case id_nspace_name_tag: {
			/* Previously defined namespace name */
			ERROR err;
			NAMESPACE old_ns;
			PTR(LOCATION) loc = id_loc(old_id);
			old_ns = DEREF_nspace(id_nspace_name_defn(old_id));
			report(crt_loc, ERR_dcl_nspace_alias_bad(old_id, loc));
			if (EQ_nspace(ns, old_ns)) {
				/* No further action if consistent */
				return;
			}
			/* Hide namespace name with namespace alias */
			err = ERR_dcl_nspace_alias_redef(old_id, loc);
			report(crt_loc, err);
			break;
		}
		case id_nspace_alias_tag: {
			/* Previously defined namespace alias */
			NAMESPACE old_ns;
			old_ns = DEREF_nspace(id_nspace_alias_defn(old_id));
			if (!EQ_nspace(ns, old_ns)) {
				/* Inconsistent alias redefinition */
				ERROR err;
				PTR(LOCATION) loc = id_loc(old_id);
				err = ERR_dcl_nspace_alias_redef(old_id, loc);
				report(crt_loc, err);
				COPY_nspace(id_nspace_alias_defn(old_id), ns);
			}
			return;
		}
		default: {
			/* Other previously defined identifier */
			PTR(LOCATION) loc = id_loc(old_id);
			report(crt_loc, ERR_basic_odr_decl(old_id, loc));
			break;
		}
		}
	}

	/* Set up the namespace alias */
	MAKE_id_nspace_alias(nm, ds, cns, decl_loc, ns, id);
	set_member(mem, id);
	return;
}


/*
    This routine processes a using namespace directive for the namespace ns.
*/

void
using_namespace(NAMESPACE ns)
{
	if (!IS_NULL_nspace(ns)) {
		if (IS_nspace_ctype(ns)) {
			/* Namespace designates a class */
			report(crt_loc, ERR_dcl_nspace_udir_class(ns));
		} else {
			NAMESPACE cns = crt_namespace;
			NAMESPACE jns = join_namespace(ns, cns);
			if (IS_NULL_nspace(jns)) {
				jns = global_namespace;
			}
			if (!use_namespace(ns, cns, jns)) {
				/* Namespace already used */
				report(crt_loc, ERR_dcl_nspace_udir_dup(ns));
			}
			uncache_namespace(ns, 0);
			if (do_dump) {
				dump_using(ns, cns, &crt_loc);
			}
		}
	}
	return;
}


/*
    This routine adds the namespace ns to the look-up stack.  If ns is
    a nested namespace then the enclosing namespaces are also added.
    It returns true if the stack is changed.
*/

int
add_nested_nspace(NAMESPACE ns)
{
	int res = 0;
	if (!IS_NULL_nspace(ns) && !EQ_nspace(ns, crt_namespace)) {
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
		case nspace_unnamed_tag:
		case nspace_ctype_tag: {
			IDENTIFIER id = DEREF_id(nspace_name(ns));
			if (!IS_NULL_id(id)) {
				NAMESPACE pns = DEREF_nspace(id_parent(id));
				IGNORE add_nested_nspace(pns);
			}
			add_namespace(ns);
			res = 1;
			break;
		}
		}
	}
	return res;
}


/*
    This routine removes the namespace ns from the look-up stack.  If
    ns is a namespace class then the enclosing namespaces are also
    removed.  It returns true if the stack is changed.
*/

int
remove_nested_nspace(NAMESPACE ns)
{
	int res = 0;
	if (!IS_NULL_nspace(ns) && !EQ_nspace(ns, crt_namespace)) {
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
		case nspace_unnamed_tag:
		case nspace_ctype_tag: {
			IDENTIFIER id;
			remove_namespace();
			id = DEREF_id(nspace_name(ns));
			if (!IS_NULL_id(id)) {
				NAMESPACE pns = DEREF_nspace(id_parent(id));
				IGNORE remove_nested_nspace(pns);
			}
			res = 1;
			break;
		}
		}
	}
	return res;
}


/*
    This routine is called immediately after the declarator id given with
    identifier qualifiers idtype and qns to set the name look-up
    appropriately.  Thus for example, in 'int C::a = b ;', b is looked up
    in the scope of C.
*/

void
begin_declarator(IDENTIFIER id, QUALIFIER idtype, NAMESPACE qns, int scan)
{
	NAMESPACE ns = NULL_nspace;
	if (idtype != qual_none) {
		ns = DEREF_nspace(id_parent(id));
		if (!IS_NULL_nspace(ns) && !IS_nspace_ctype(ns)) {
			if (!IS_NULL_nspace(qns) && !EQ_nspace(qns, ns)) {
				/* Should have an immediate member */
				report(crt_loc, ERR_lookup_qual_decl(id, qns));
				ns = qns;
			}
		}
		if (add_nested_nspace(ns) && scan) {
			/* Rescan identifier if stack has changed */
			RESCAN_LEXER;
		}
	}
	PUSH_nspace(ns, local_nspace_stack);
	if (crt_state_depth == 0) {
		id = underlying_id(id);
		DEREF_loc(id_loc(id), decl_loc);
	} else {
		decl_loc = crt_loc;
	}
	return;
}


/*
    This routine is called at the end of the initialiser or definition
    of the declarator id to reset the name look-up.
*/

void
end_declarator(IDENTIFIER id, int scan)
{
	NAMESPACE ns;
	POP_nspace(ns, local_nspace_stack);
	if (IS_NULL_nspace(ns)) {
		if (!IS_NULL_id(id)) {
			HASHID nm = DEREF_hashid(id_name(id));
			IDENTIFIER cid = DEREF_id(hashid_cache(nm));
			if (!EQ_id(id, cid)) {
				/* Look-up may have changed */
				COPY_id(hashid_cache(nm), NULL_id);
				if (scan) {
					/* Rescan identifier if look-up has
					 * changed */
					RESCAN_LEXER;
				}
			}
		}
	} else {
		if (remove_nested_nspace(ns) && scan) {
			/* Rescan identifier if stack has changed */
			RESCAN_LEXER;
		}
	}
	return;
}


/*
    This routine sets the identifier id to be a namespace member as
    indicated by mem.  It also sets the look-up cache to id if appropriate.
*/

void
set_member(MEMBER mem, IDENTIFIER id)
{
	if (!IS_NULL_member(mem)) {
		HASHID nm;
		IDENTIFIER cid;
		LIST(NAMESPACE) lns;

		/* Check any previous definition */
		IDENTIFIER pid = DEREF_id(member_id(mem));
		if (!IS_NULL_id(pid)) {
			if (IS_id_token(pid)) {
				IGNORE unify_id(pid, id, 1);
			} else if (IS_id_token(id)) {
				if (unify_id(id, pid, 0)) {
					return;
				}
			}
		}

		/* Check look-up cache */
		cid = NULL_id;
		nm = DEREF_hashid(id_name(id));
		lns = LIST_stack(namespace_stack);
		if (!IS_NULL_list(lns)) {
			/* Check for current namespace */
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			NAMESPACE pns = DEREF_nspace(HEAD_list(lns));
			if (EQ_nspace(ns, pns)) {
				/* Check for unambiguous look-up */
				lns = DEREF_list(nspace_use(ns));
				if (IS_NULL_list(lns)) {
					cid = id;
				}
			}
		}
		COPY_id(hashid_cache(nm), cid);

		/* Set member identifier */
		COPY_id(member_id(mem), id);
	}
	return;
}


/*
    This routine sets the type identifier id to be a namespace member
    as indicated by mem.  Note that in C this just sets the alt field
    of mem, whereas in C++ it may also set the id field.
*/

void
set_type_member(MEMBER mem, IDENTIFIER id)
{
	if (!IS_NULL_member(mem)) {
#if LANGUAGE_CPP
		IDENTIFIER mid = DEREF_id(member_id(mem));
		if (IS_NULL_id(mid)) {
			/* No object of the same name */
			set_member(mem, id);
		} else {
			/* Hidden by object of the same name */
			HASHID nm = DEREF_hashid(id_name(id));
			DECL_SPEC ds = DEREF_dspec(id_storage(mid));
			if ((ds & dspec_inherit) && !(ds & dspec_alias)) {
				ds = DEREF_dspec(id_storage(id));
				if (!(ds & dspec_inherit)) {
					/* An uninherited type overrrides an
					 * inherited object */
					COPY_id(member_id(mem), id);
				}
			}
			COPY_id(hashid_cache(nm), NULL_id);
		}
#endif
		COPY_id(member_alt(mem), id);
	}
	return;
}


/*
    This routine clears all meanings of the member nm of the namespace ns.
*/

void
clear_member(NAMESPACE ns, HASHID nm)
{
	MEMBER mem = search_member(ns, nm, 0);
	if (!IS_NULL_member(mem)) {
		COPY_id(member_id(mem), NULL_id);
		COPY_id(member_alt(mem), NULL_id);
	}
	COPY_id(hashid_cache(nm), NULL_id);
	return;
}


/*
    This routine searches the namespace ns for a member named nm.  This
    is returned if found.  Otherwise if create is true then an empty
    member is created and returned.  Otherwise the null member is returned.
*/

MEMBER
search_member(NAMESPACE ns, HASHID nm, int create)
{
	MEMBER mem;

	if (IS_NULL_nspace(ns)) {
		/* Null namespace */
		if (create) {
			MAKE_member_small(NULL_member, mem);
		} else {
			mem = NULL_member;
		}

	} else if (IS_nspace_block_etc(ns)) {
		/* Small namespaces */
		MEMBER last = DEREF_member(nspace_last(ns));

		/* Search through members */
		mem = last;
		while (!IS_NULL_member(mem)) {
			IDENTIFIER mid = DEREF_id(member_id(mem));
			if (!IS_NULL_id(mid)) {
				HASHID mnm = DEREF_hashid(id_name(mid));
				if (EQ_hashid(nm, mnm)) {
					return mem;
				}
#if LANGUAGE_C
			} else {
			/* ... continues */
				/* Need to also check tag namespace in C */
				mid = DEREF_id(member_alt(mem));
				if (!IS_NULL_id(mid)) {
					HASHID mnm = DEREF_hashid(id_name(mid));
					if (EQ_hashid(nm, mnm)) {
						return mem;
					}
				}
#endif
			}
			mem = DEREF_member(member_next(mem));
		}

		/* Create new member if necessary */
		if (create) {
			MAKE_member_small(last, mem);
			COPY_member(nspace_last(ns), mem);
		}
	} else {
		/* Large namespaces */
		PTR(MEMBER) ptr = DEREF_ptr(nspace_named_etc_table(ns));
		unsigned long sz = DEREF_ulong(nspace_named_etc_size(ns));
		unsigned long h = DEREF_ulong(hashid_hash(nm));
		SIZE(MEMBER) psz = SCALE(SIZE_member,(h % sz));

		/* Search through members */
		ptr = STEP_ptr(ptr, psz);
		mem = DEREF_member(ptr);
		while (!IS_NULL_member(mem)) {
			IDENTIFIER mid = DEREF_id(member_id(mem));
			if (!IS_NULL_id(mid)) {
				HASHID mnm = DEREF_hashid(id_name(mid));
				if (EQ_hashid(nm, mnm)) {
					return mem;
				}
#if LANGUAGE_C
			} else {
			/* ... continues */
				/* Need to also check tag namespace in C */
				mid = DEREF_id(member_alt(mem));
				if (!IS_NULL_id(mid)) {
					HASHID mnm = DEREF_hashid(id_name(mid));
					if (EQ_hashid(nm, mnm)) {
						return mem;
					}
				}
#endif
			}
			mem = DEREF_member(member_large_tnext(mem));
		}

		/* Create new member if necessary */
		if (create) {
			MEMBER last;
			mem = DEREF_member(ptr);
			MAKE_member_large(NULL_member, mem, mem);
			COPY_member(ptr, mem);
			last = DEREF_member(nspace_last(ns));
			if (IS_NULL_member(last)) {
				COPY_member(nspace_named_etc_first(ns), mem);
			} else {
				COPY_member(member_next(last), mem);
			}
			COPY_member(nspace_last(ns), mem);
		}
	}
	return mem;
}


/*
    This routine copies the member mem of the namespace ns to the end of
    the list of all members.  In block namespaces this is to force the
    member to be re-examined in make_decl_stmt.  In class namespaces this
    is to preserve the order of the data members.
*/

MEMBER
update_member(NAMESPACE ns, MEMBER mem)
{
	IDENTIFIER id = DEREF_id(member_id(mem));
	IDENTIFIER alt = DEREF_id(member_alt(mem));
	COPY_id(member_id(mem), NULL_id);
	COPY_id(member_alt(mem), NULL_id);
	if (IS_member_small(mem)) {
		/* Create new small member */
		MEMBER last = DEREF_member(nspace_last(ns));
		MAKE_member_small(last, mem);
		COPY_member(nspace_last(ns), mem);
	} else {
		/* Create new large member */
		if (!IS_NULL_id(id)) {
			HASHID nm = DEREF_hashid(id_name(id));
			mem = search_member(ns, nm, 1);
		} else if (!IS_NULL_id(alt)) {
			HASHID nm = DEREF_hashid(id_name(alt));
			mem = search_member(ns, nm, 1);
		}
	}
	COPY_id(member_id(mem), id);
	COPY_id(member_alt(mem), alt);
	return mem;
}


/*
    This routine checks whether the identifier id is a type name (if bit 0
    of type is true) or a namespace name (if bit 1 of type is true).  In
    C only struct, union and enum tags are allowed.
*/

static IDENTIFIER
select_type_id(IDENTIFIER id, int type)
{
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_class_name_tag:
		case id_enum_name_tag:
			if (type & 1) {
				return id;
			}
			break;
#if LANGUAGE_CPP
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag:
			if (type & 1) {
				return id;
			}
			break;
		case id_nspace_name_tag:
		case id_nspace_alias_tag:
			if (type & 2) {
				return id;
			}
			break;
#endif
		}
	}
	return NULL_id;
}


/*
    This routine returns the type or namespace name associated with the
    member mem, or the null identifier if this does not exist.  The
    type argument is as above.  In C++ it is necessary to check both
    the id and the alt fields of mem, whereas in C only the alt field
    needs to be examined.
*/

IDENTIFIER
type_member(MEMBER mem, int type)
{
	IDENTIFIER id = NULL_id;
	if (!IS_NULL_member(mem)) {
#if LANGUAGE_CPP
		id = DEREF_id(member_id(mem));
		id = select_type_id(id, type);
		if (IS_NULL_id(id)) {
			id = DEREF_id(member_alt(mem));
			id = select_type_id(id, type);
		}
#else
		id = DEREF_id(member_alt(mem));
		id = select_type_id(id, type);
#endif
	}
	return id;
}


/*
    This routine checks whether the identifier id is in the list of
    ambiguous meanings given by pid and pids.  Functions are excluded
    because of the complications introduced by using-declarations and
    overloading.  Overload resolution will eliminate duplicate entries
    in this case.
*/

static int
already_found_id(IDENTIFIER id, IDENTIFIER pid, LIST(IDENTIFIER) pids)
{
	if (IS_id_function_etc(id)) {
		/* Exclude functions */
		return 0;
	}
	if (!IS_NULL_id(pid)) {
		if (IS_id_ambig(pid)) {
			/* Check ambiguous identifiers */
			LIST(IDENTIFIER) qids = DEREF_list(id_ambig_ids(pid));
			if (already_found_id(id, NULL_id, qids)) {
				return 1;
			}
		} else {
			/* Check simple identifiers */
			if (!IS_id_function_etc(pid)) {
				id = DEREF_id(id_alias(id));
				pid = DEREF_id(id_alias(pid));
				if (EQ_id(id, pid)) {
					return 1;
				}
			}
		}
	}
	if (!IS_NULL_list(pids)) {
		/* Check identifier lists */
		IDENTIFIER qid = DEREF_id(HEAD_list(pids));
		pids = TAIL_list(pids);
		return already_found_id(id, qid, pids);
	}
	return 0;
}


/*
    This routine looks up the identifier nm in the namespace ns.
*/

IDENTIFIER
search_id(NAMESPACE ns, HASHID nm, int create, int type)
{
	IDENTIFIER id;
	MEMBER mem = search_member(ns, nm, create);
	if (!IS_NULL_member(mem)) {
		if (type) {
			id = type_member(mem, type);
		} else {
			id = DEREF_id(member_id(mem));
		}
	} else {
		id = NULL_id;
	}
	return id;
}


/*
    This routine searches the namespace ns and used namespaces for an
    identifier named nm, which is returned if found.  Otherwise if create
    is true then a dummy identifier is created and returned.  Otherwise
    the null identifier is returned.  qual is true for qualified look-ups.
    If type is nonzero then only type and namespace names are considered.
    rns gives the original value of ns for use when recursively searching
    used namespaces.
*/

static IDENTIFIER
search_nspace(NAMESPACE ns, HASHID nm, NAMESPACE rns, int qual, int create,
	      int type)
{
	IDENTIFIER id;
	LIST(NAMESPACE) uns;

	/* Allow for class namespaces */
	if (IS_nspace_ctype(ns)) {
		id = search_field(ns, nm, create, type);
		return id;
	}

	/* Search main namespace */
	id = search_id(ns, nm, create, type);
	if (!IS_NULL_id(id) && qual) {
		/* Return found identifier */
		return id;
	}

	/* Search used namespaces */
	uns = DEREF_list(nspace_use(ns));
	if (!IS_NULL_list(uns)) {
		LIST(NAMESPACE) vns = DEREF_list(nspace_join(ns));
		LIST(NAMESPACE) uns_orig = uns;
		LIST(NAMESPACE) vns_orig = vns;
		LIST(IDENTIFIER) ambig = NULL_list(IDENTIFIER);
		COPY_list(nspace_use(ns), NULL_list(NAMESPACE));
		COPY_list(nspace_join(ns), NULL_list(NAMESPACE));
		while (!IS_NULL_list(uns)) {
			NAMESPACE pns = DEREF_nspace(HEAD_list(uns));
			NAMESPACE jns = DEREF_nspace(HEAD_list(vns));
			if (qual || is_subnspace(rns, jns)) {
				/* Look-up identifier in used namespace */
				IDENTIFIER pid;
				pid = search_nspace(pns, nm, rns, qual, 0,
						    type);
				if (!IS_NULL_id(pid)) {
					/* Add found identifier to list */
					if (IS_NULL_id(id)) {
						id = pid;
					} else if (!already_found_id(pid, id,
								     ambig)) {
						CONS_id(pid, ambig, ambig);
					}
				}
			} else {
				/* Postpone look-up until join namespace */
				if (use_namespace(pns, jns, jns)) {
					CONS_nspace(jns, join_nspaces,
						    join_nspaces);
				}
			}
			vns = TAIL_list(vns);
			uns = TAIL_list(uns);
		}
		if (!IS_NULL_list(ambig)) {
			/* Ambiguous resolution */
			DECL_SPEC ds;
			CONS_id(id, ambig, ambig);
			ds = find_ambig_dspec(ambig);
			MAKE_id_ambig(nm, ds, rns, crt_loc, ambig, 1, id);
		}
		COPY_list(nspace_use(ns), uns_orig);
		COPY_list(nspace_join(ns), vns_orig);
	}

	/* Create dummy identifier if necessary */
	if (IS_NULL_id(id) && create) {
		MAKE_id_undef(nm, dspec_none, ns, crt_loc, id);
	}
	return id;
}


/*
    This routine searches all the namespaces in the current namespace stack
    which are contained within pns for the identifier pns.  If type is
    nonzero then only type and namespace names are considered.
*/

IDENTIFIER
find_extern_id(HASHID nm, NAMESPACE pns, int type)
{
	IDENTIFIER id = NULL_id;
	LIST(NAMESPACE) lns = LIST_stack(namespace_stack);
	while (!IS_NULL_list(lns)) {
		NAMESPACE ns = DEREF_nspace(HEAD_list(lns));
		if (!IS_NULL_nspace(ns)) {
			id = search_nspace(ns, nm, ns, 0, 0, type);
			if (!IS_NULL_id(id)) {
				break;
			}
			if (EQ_nspace(ns, pns)) {
				break;
			}
		}
		lns = TAIL_list(lns);
	}
	if (!IS_NULL_list(join_nspaces)) {
		clear_join_nspaces();
	}
	return id;
}


/*
    This routine (aka who the feck is fred?) looks up the name nm in the
    current scope, returning the corresponding identifier.  Note that
    there is always a meaning for nm even if it is the underlying dummy
    identifier.
*/

IDENTIFIER
find_id(HASHID nm)
{
	IDENTIFIER id;
	if (cache_lookup) {
		id = DEREF_id(hashid_cache(nm));
		if (IS_NULL_id(id)) {
			id = find_extern_id(nm, NULL_nspace, 0);
			if (IS_NULL_id(id)) {
				/* Use underlying meaning if not found */
				id = DEREF_id(hashid_id(nm));
			}
			COPY_id(hashid_cache(nm), id);
		}
	} else {
		id = find_extern_id(nm, NULL_nspace, 0);
		if (IS_NULL_id(id)) {
			/* Use underlying meaning if not found */
			id = DEREF_id(hashid_id(nm));
		}
	}
	return id;
}


/*
    This routine (aka who the feck is fred::bloggs?) looks up the name nm
    in the namespace ns.  Only type names are considered when type is
    nonzero.  When ns is the null namespace this reduces to an unqualified
    name look-up.
*/

IDENTIFIER
find_qual_id(NAMESPACE ns, HASHID nm, int create, int type)
{
	IDENTIFIER id;
	if (IS_NULL_nspace(ns)) {
		/* Unqualified name look-up */
		if (type == 0) {
			id = find_id(nm);
		} else {
			id = find_type_id(nm, type);
		}
	} else {
		/* Qualified name look-up */
		id = search_nspace(ns, nm, ns, 1, create, type);
	}
	return id;
}


/*
    This routine looks up the name nm as a type in the current scope,
    returning the corresponding identifier.  If there is no type named
    nm then the null identifier is returned.
*/

IDENTIFIER
find_type_id(HASHID nm, int type)
{
	IDENTIFIER id;
	if (cache_lookup) {
		/* Check whether cached value is a type */
		id = DEREF_id(hashid_cache(nm));
		id = select_type_id(id, type);
		if (!IS_NULL_id(id)) {
			return id;
		}
	}
	id = find_extern_id(nm, NULL_nspace, type);
	return id;
}


/*
    This routine is identical to find_id except that it ignores all class
    namespaces.  This is used when looking up operator functions in C++
    and is the default look-up rule in C.
*/

IDENTIFIER
find_op_id(HASHID nm)
{
	IDENTIFIER id;
	LIST(NAMESPACE) lns;
	int cache = cache_lookup;
	if (cache) {
		/* Check cached look-up */
		id = DEREF_id(hashid_cache(nm));
		if (!IS_NULL_id(id)) {
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			if (IS_NULL_nspace(ns) || !IS_nspace_ctype(ns)) {
				return id;
			}
			cache = 0;
		}
	}

	/* Scan through namespace stack */
	lns = LIST_stack(namespace_stack);
	while (!IS_NULL_list(lns)) {
		NAMESPACE ns = DEREF_nspace(HEAD_list(lns));
		if (!IS_NULL_nspace(ns) && !IS_nspace_ctype(ns)) {
			id = search_nspace(ns, nm, ns, 0, 0, 0);
			if (!IS_NULL_id(id)) {
				if (!IS_NULL_list(join_nspaces)) {
					clear_join_nspaces();
				}
				if (cache) {
					COPY_id(hashid_cache(nm), id);
				}
				return id;
			}
		} else {
			cache = 0;
		}
		lns = TAIL_list(lns);
	}
	if (!IS_NULL_list(join_nspaces)) {
		clear_join_nspaces();
	}
	id = DEREF_id(hashid_id(nm));
	if (cache) {
		COPY_id(hashid_cache(nm), id);
	}
	return id;
}


/*
    This routine gives a final check in the name look-up.  In most cases
    id will already be a valid identifier for the namespace ns - the couple
    of exceptions - undeclared members and non-simple identifier names
    are handled by this routine.
*/

IDENTIFIER
check_id(NAMESPACE ns, IDENTIFIER id, int templ)
{
	if (!IS_NULL_id(id)) {
		unsigned tag = TAG_id(id);
		if (tag == id_dummy_tag) {
			/* Re-scan dummy identifiers */
			HASHID nm = DEREF_hashid(id_name(id));
			id = find_qual_id(ns, nm, 1, 0);
			tag = TAG_id(id);
		}
		if (tag == id_token_tag && crt_id_qualifier != qual_none) {
			/* Can't qualify token names */
			report(crt_loc, ERR_token_qual(id));
		}
		UNUSED(templ);
	}
	return id;
}


/*
    This routine removes the function id from the set of overloaded
    functions fid.
*/

static IDENTIFIER
remove_func(IDENTIFIER fid, IDENTIFIER id)
{
	if (!IS_NULL_id(fid)) {
		IDENTIFIER pid = DEREF_id(id_function_etc_over(fid));
		if (EQ_id(fid, id)) {
			fid = pid;
			COPY_id(id_function_etc_over(id), NULL_id);
		} else {
			pid = remove_func(pid, id);
			COPY_id(id_function_etc_over(fid), pid);
		}
	}
	return fid;
}


/*
    This routine removes the identifier id its parent namespace.
*/

void
remove_id(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	MEMBER mem = search_member(ns, nm, 0);
	if (!IS_NULL_member(mem)) {
		IDENTIFIER mid = DEREF_id(member_id(mem));
		IDENTIFIER tid = DEREF_id(member_alt(mem));
		if (IS_id_function_etc(id)) {
			mid = remove_func(mid, id);
		} else {
			if (EQ_id(id, mid)) {
				mid = NULL_id;
			}
			if (EQ_id(id, tid)) {
				tid = NULL_id;
			}
		}
		if (IS_NULL_id(mid)) {
			mid = tid;
		}
		COPY_id(member_id(mem), mid);
		COPY_id(member_alt(mem), tid);
		COPY_id(hashid_cache(nm), NULL_id);
		IGNORE check_identifier(id, ns, NULL_exp, ANON_NONE, 1);
	}
	return;
}


/*
    This routine checks whether the identifier id has an external linkage
    name.  It cannot be a member of a block, an unnamed class or an
    anonymous namespace.
*/

int
has_linkage(IDENTIFIER id)
{
	while (!IS_NULL_id(id)) {
		HASHID nm = DEREF_hashid(id_name(id));
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (IS_hashid_anon(nm)) {
			return 0;
		}
		if (!(ds & dspec_extern)) {
			return 0;
		}
		if ((ds & dspec_c) && !anon_c_linkage) {
			return 1;
		}
		if (IS_NULL_nspace(ns)) {
			return 0;
		}
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
			break;
		case nspace_ctype_tag:
			break;
		case nspace_global_tag:
			return 1;
		default:
			return 0;
		}
		id = DEREF_id(nspace_name(ns));
	}
	return 0;
}


/*
    This routine is used to report on variables, parameters and functions
    hidden by id.  Note that only the first instance is reported, and that
    the hiding of one declaration by a subsequent incompatible redeclaration
    is excluded.
*/

void
check_hiding(IDENTIFIER id)
{
    if (crt_id_qualifier == qual_none) {
	/* Check through all look-up namespaces */
	HASHID nm = DEREF_hashid(id_name(id));
	LIST(NAMESPACE) lns = LIST_stack(namespace_stack);
	while (!IS_NULL_list(lns)) {
	    NAMESPACE ns = DEREF_nspace(HEAD_list(lns));
	    if (!IS_NULL_nspace(ns)) {
		IDENTIFIER mid = search_nspace(ns, nm, ns, 0, 0, 0);
		if (!IS_NULL_id(mid) && !EQ_id(mid, id)) {
		    ERROR err = NULL_err;
		    switch (TAG_id(mid)) {
			case id_variable_tag:
			case id_parameter_tag:
			case id_function_tag: {
			    /* Report hiding of these objects */
			    PTR(LOCATION) mloc = id_loc(mid);
			    err = ERR_basic_scope_hide(nm, mloc);
			    break;
			}
			case id_stat_member_tag:
			case id_mem_func_tag:
			case id_stat_mem_func_tag:
			case id_member_tag:
			    /* Report hiding of members */
			    err = ERR_basic_scope_hide_mem(nm, mid);
			    break;
		    }
		    if (!IS_NULL_err(err)) {
			/* Print error */
			LOCATION loc;
			DEREF_loc(id_loc(id), loc);
			report(crt_loc, err);
		    }
		    break;
		}
	    }
	    lns = TAIL_list(lns);
	}
	if (!IS_NULL_list(join_nspaces)) {
		clear_join_nspaces();
	}
    }
    return;
}
