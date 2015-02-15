/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "inst_ops.h"
#include "nat_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "basetype.h"
#include "cast.h"
#include "chktype.h"
#include "construct.h"
#include "constant.h"
#include "convert.h"
#include "copy.h"
#include "class.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "namespace.h"
#include "operator.h"
#include "parse.h"
#include "predict.h"
#include "redeclare.h"
#include "rewrite.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "virtual.h"


/*
    This routine adjusts the class information ci to be that representing
    the given class key.
*/

static CLASS_INFO
set_class_key(CLASS_INFO ci, BASE_TYPE key)
{
	ci &= ~cinfo_key;
	if (key == btype_union) {
		ci |= cinfo_union;
	} else if (key == btype_struct) {
		ci |= cinfo_struct;
	}
	return ci;
}


/*
    This routine checks whether the namespace ns is enclosed within a
    block namespace.
*/

int
is_local_nspace(NAMESPACE ns)
{
	while (!IS_NULL_nspace(ns)) {
		IDENTIFIER id;
		switch (TAG_nspace(ns)) {
		case nspace_block_tag:
		case nspace_dummy_tag: {
			return 1;
		}
		case nspace_param_tag:
		case nspace_templ_tag: {
			return 2;
		}
		}
		id = DEREF_id(nspace_name(ns));
		if (IS_NULL_id(id)) {
			break;
		}
		ns = DEREF_nspace(id_parent(id));
	}
	return 0;
}


/*
    This routine creates a class or enumeration type (indicated by key)
    with type name nm and template qualifiers q in the namespace ns.
*/

IDENTIFIER
make_class(NAMESPACE ns, HASHID nm, BASE_TYPE key, DECL_SPEC bds, TYPE q,
	   TYPE prev)
{
	TYPE t;
	IDENTIFIER id;
	ENUM_TYPE et = NULL_etype;
	CLASS_TYPE ct = NULL_ctype;
	CLASS_INFO ci = cinfo_default;
	DECL_SPEC ds = (bds | dspec_lang);
	if (option(OPT_complete_struct) && crt_file_type == 0) {
		/* Allow incomplete types in start-up files */
		ci |= cinfo_incomplete;
	}

	/* Check on class linkage and access */
	if (!IS_NULL_nspace(ns)) {
		if (IS_nspace_ctype(ns)) {
			/* Only nested classes (not friend classes) have
			 * access */
			if (!(ds & dspec_access)) {
				ds |= crt_access;
			}
		}
		if (!really_in_function_defn || !is_local_nspace(ns)) {
			ds |= dspec_extern;
		}
	}

	if (key == btype_enum) {
		/* Create the enumeration type */
		MAKE_id_enum_name(nm, ds, ns, decl_loc, NULL_type, id);
		COPY_btype(id_enum_name_rep(id), key);
		MAKE_etype_basic(id, ci, type_sint, et);
		MAKE_type_enumerate(cv_none, et, t);
		if (!IS_NULL_type(q)) {
			report(decl_loc, ERR_temp_decl_bad());
		}
		COPY_type(id_enum_name_defn(id), t);
	} else {
		TYPE s;
		GRAPH gr;
		MEMBER mem;
		NAMESPACE mns;
		DECL_SPEC acc;
		IDENTIFIER cid;

		/* Allow for template classes */
		if (!IS_NULL_type(q)) {
			ds |= dspec_template;
			ci |= cinfo_template;
		}

		/* Create the class member namespace */
		MAKE_id_class_name(nm, ds, ns, decl_loc, NULL_type, id);
		COPY_btype(id_class_name_rep(id), key);
		mns = make_namespace(id, nspace_ctype_tag, 20);

		/* Construct the base class graph */
		acc = (dspec_public | dspec_defn | dspec_done);
		MAKE_graph_basic(NULL_ctype, acc, gr);
		COPY_graph(graph_top(gr), gr);

		/* Construct the class */
		ci = set_class_key(ci, key);
		MAKE_ctype_basic(id, ci, cusage_none, mns, gr, 1, prev, ct);
		COPY_ctype(graph_head(gr), ct);

		/* Construct the class type */
		MAKE_type_compound(cv_none, ct, t);
		COPY_type(id_class_name_defn(id), t);
		s = t;
		if (!IS_NULL_type(q)) {
			/* Allow for template qualifiers */
			t = inject_pre_type(q, t, 0);
			COPY_type(id_class_name_defn(id), t);
			IGNORE check_templ_params(t, id);
		}

		/* Construct the constructor and destructor names */
		IGNORE lookup_constr(s, id);
		IGNORE lookup_destr(s, id);

		/* Inject the class name into the class */
		ds &= ~dspec_access;
		ds |= (dspec_alias | dspec_implicit | dspec_public);
		if (bds & dspec_instance) {
			ds |= dspec_template;
		}
		mem = search_member(mns, nm, 1);
		MAKE_id_class_name(nm, ds, mns, decl_loc, t, cid);
		COPY_btype(id_class_name_rep(cid), key);
		COPY_id(id_alias(cid), id);
		COPY_id(member_alt(mem), cid);
#if LANGUAGE_CPP
		COPY_id(member_id(mem), cid);
#endif
	}

	/* Deal with nested classes */
	if (IS_nspace_ctype(ns)) {
		CLASS_TYPE cr;
		CLASS_INFO cj;
		LIST(IDENTIFIER)fr;
		IDENTIFIER rid = DEREF_id(nspace_name(ns));
		TYPE r = DEREF_type(id_class_name_defn(rid));
		while (IS_type_templ(r)) {
			r = DEREF_type(type_templ_defn(r));
		}
		cr = DEREF_ctype(type_compound_defn(r));
		cj = DEREF_cinfo(ctype_info(cr));
		if (cj & cinfo_template) {
			/* Mark nested template classes */
			ci |= (cinfo_template | cinfo_rescan);
		}
		ci |= cinfo_nested;
		if (!IS_NULL_ctype(ct)) {
			COPY_cinfo(ctype_info(ct), ci);
		}
		if (!IS_NULL_etype(et)) {
			COPY_cinfo(etype_info(et), ci);
		}
		fr = DEREF_list(ctype_nest(cr));
		CONS_id(id, fr, fr);
		COPY_list(ctype_nest(cr), fr);
	}
	return id;
}


/*
    This routine is called for a declarator id which represents a type
    name in the namespace ns.  It checks whether id is actually a
    constructor name, and if so returns the correct identifier.
*/

IDENTIFIER
constr_name(NAMESPACE ns, IDENTIFIER id)
{
	unsigned tag = TAG_id(id);
	if (tag == id_class_name_tag || tag == id_class_alias_tag) {
		CLASS_TYPE ct;
		NAMESPACE cns;
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		while (IS_type_templ(t)) {
			t = DEREF_type(type_templ_defn(t));
		}
		ct = DEREF_ctype(type_compound_defn(t));
		cns = DEREF_nspace(ctype_member(ct));
		if (IS_NULL_nspace(ns)) {
			ns = crt_namespace;
		}
		if (EQ_nspace(ns, cns)) {
			/* This is a constructor */
			IDENTIFIER cid = DEREF_id(ctype_constr(ct));
			if (tag == id_class_alias_tag && is_constructor_next) {
				/* Can't use type alias */
				HASHID cnm = DEREF_hashid(id_name(cid));
				IDENTIFIER tid =
				    DEREF_id(hashid_constr_tid(cnm));
				if (!EQ_id(tid, id)) {
					report(crt_loc, ERR_dcl_typedef_constr(id, cnm));
				}
			}
			set_hashid_loc(cid, id);
			id = cid;
		}
	}
	is_constructor_next = 0;
	return id;
}


/*
    This routine checks whether the type associated with the identifier id
    has been defined or just declared.  A value of 2 is returned for
    tokenised types.  The value associated with a defined type is returned
    via pt.  If force is true then any template classes are completed.
*/

int
is_defined(IDENTIFIER id, TYPE *pt, int force)
{
	if (IS_id_class_name_etc(id)) {
		CLASS_INFO ci;
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		unsigned tag = TAG_type(t);
		*pt = t;
		while (tag == type_templ_tag) {
			t = DEREF_type(type_templ_defn(t));
			tag = TAG_type(t);
		}
		if (tag == type_compound_tag) {
			/* Class type */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			if (force) {
				complete_class(ct, 0);
			}
			ci = DEREF_cinfo(ctype_info(ct));
		} else if (tag == type_enumerate_tag) {
			/* Enumeration type */
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			ci = DEREF_cinfo(etype_info(et));
		} else {
			return 1;
		}
		if (ci & cinfo_token) {
			/* Tokenised types */
			IDENTIFIER tid = find_token(id);
			DECL_SPEC ds = DEREF_dspec(id_storage(tid));
			if (ds & dspec_pure) {
				return 1;
			}
			return 2;
		}
		if (ci & (cinfo_complete | cinfo_defined)) {
			/* Defined types */
			return 1;
		}
	}
	return 0;
}


/*
    This routine returns the class key associated with the class type ct.
*/

BASE_TYPE
find_class_key(CLASS_TYPE ct)
{
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	if (ci & cinfo_union) {
		return btype_union;
	}
	if (ci & cinfo_struct) {
		return btype_struct;
	}
	return btype_class;
}


/*
    This routine returns the class key associated with the identifier id.
    Note that typedef names are only expanded to their definitions if
    expand is true.  If id is a template type parameter which has not
    previously been qualified then its key is set to new_key.
*/

static BASE_TYPE
find_key(IDENTIFIER id, int expand, BASE_TYPE new_key)
{
	switch (TAG_id(id)) {
	case id_class_name_tag:
class_name_lab: {
			/* Class names */
			CLASS_TYPE ct;
			BASE_TYPE key;
			TYPE t = DEREF_type(id_class_name_etc_defn(id));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			key = find_class_key(ct);
			return key;
		}
	case id_enum_name_tag: {
		/* Enumeration names */
		return btype_enum;
	}
	case id_class_alias_tag: {
		/* Class aliases */
		if (expand) {
			goto class_name_lab;
		}
		return btype_alias;
	}
	case id_enum_alias_tag: {
		/* Enumeration aliases */
		if (expand) {
			return btype_enum;
		}
		return btype_alias;
	}
	case id_type_alias_tag: {
		/* Type aliases */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_token) {
			/* Check tokenised types */
			TYPE t = DEREF_type(id_type_alias_defn(id));
			if (IS_type_token(t)) {
				id = DEREF_id(type_token_tok(t));
				return find_key(id, expand, new_key);
			}
		}
		return btype_alias;
	}
	case id_token_tag: {
		/* Tokenised types */
		TOKEN tok = DEREF_tok(id_token_sort(id));
		if (IS_tok_type(tok)) {
			BASE_TYPE bt = DEREF_btype(tok_type_kind(tok));
			if (bt & btype_template) {
				/* Template parameter */
				BASE_TYPE key = (bt & btype_named);
				if (key == btype_none) {
					key = new_key;
					bt |= key;
					COPY_btype(tok_type_kind(tok), bt);
				}
				return key;
			}
			return btype_alias;
		}
		break;
	}
	}
	return btype_none;
}


/*
    This routine checks whether the class keys key1 and key2 are consistent.
    Basically they are consistent if they are equal, but also 'class' is
    consistent with 'struct'.
*/

int
equal_key(BASE_TYPE key1, BASE_TYPE key2)
{
	if (key1 == key2) {
		return 1;
	}
	if (key1 == btype_class && key2 == btype_struct) {
		return 1;
	}
	if (key1 == btype_struct && key2 == btype_class) {
		return 1;
	}
	if (key1 == btype_any || key2 == btype_any) {
		return 1;
	}
	return 0;
}


/*
    This routine checks the given class key for the type id.  It returns
    true if either the new or the existing class key is 'enum'.
*/

static int
check_key(IDENTIFIER id, BASE_TYPE key)
{
	int is_enum = 0;
	BASE_TYPE prev = find_key(id, 1, key);
	if (!equal_key(prev, key)) {
		PTR(LOCATION)loc = id_loc(id);
		ERROR err = ERR_dcl_type_elab_bad(key, prev, id, loc);
		report(crt_loc, err);
		if (prev == btype_enum) {
			is_enum = 1;
		}
		if (key == btype_enum) {
			is_enum = 1;
		}
	}
	return is_enum;
}


/*
    This routine creates a dummy class or union type (as indicated by key)
    representing the type 'id < args >' where id depends on a template
    parameter.
*/

TYPE
make_dummy_class(IDENTIFIER id, LIST(TOKEN)args, BASE_TYPE key)
{
	TYPE t, s;
	CLASS_TYPE ct;
	CLASS_INFO ci;
	IDENTIFIER tid;
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	decl_loc = crt_loc;
	tid = make_class(ns, nm, key, dspec_public, NULL_type, NULL_type);
	t = DEREF_type(id_class_name_defn(tid));
	ct = DEREF_ctype(type_compound_defn(t));
	ci = DEREF_cinfo(ctype_info(ct));
	ci |= (cinfo_defined | cinfo_complete);
	COPY_cinfo(ctype_info(ct), ci);
	MAKE_type_token(cv_none, id, args, s);
	COPY_type(ctype_form(ct), s);
	return t;
}


/*
    This routine returns the class type associated with the identifier id.
    The null class type is returned if id is not a class name.
*/

CLASS_TYPE
find_class(IDENTIFIER id)
{
	unsigned tag = TAG_id(id);
	if (tag == id_class_name_tag || tag == id_class_alias_tag) {
		/* Simple class names */
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		if (IS_type_compound(t)) {
			/* Simple classes */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			return ct;
		} else {
			/* Template classes */
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			if (IS_type_compound(t)) {
				CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
				if (defining_class(ct)) {
					/* Only allow unqualified in definition */
					return ct;
				}
			}
		}

	} else if (tag == id_type_alias_tag) {
		/* Check tokenised types */
		TYPE t = DEREF_type(id_type_alias_defn(id));
		while (IS_type_templ(t)) {
			t = DEREF_type(type_templ_defn(t));
		}
		if (IS_type_token(t)) {
			id = DEREF_id(type_token_tok(t));
			return find_class(id);
		}

	} else if (tag == id_token_tag && is_templ_param(id)) {
		/* Check for template parameters */
		int simple = 0;
		BASE_TYPE key = btype_lang;
		TOKEN sort = DEREF_tok(id_token_sort(id));
		if (IS_tok_type(sort)) {
			key = DEREF_btype(tok_type_kind(sort));
			key &= btype_named;
			simple = 1;
		}
		if (key != btype_enum) {
			TYPE t;
			if (simple) {
				t = DEREF_type(tok_type_alt(sort));
			} else {
				t = DEREF_type(tok_class_alt(sort));
			}
			if (IS_NULL_type(t)) {
				/* Create dummy class type */
				if (key == btype_none) {
					key = btype_lang;
				}
				t = make_dummy_class(id, NULL_list(TOKEN), key);
				if (simple) {
					COPY_type(tok_type_alt(sort), t);
				} else {
					COPY_type(tok_class_alt(sort), t);
				}
			}
			if (IS_type_compound(t)) {
				/* Return previous dummy class type */
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				return ct;
			}
		}
	}
	return NULL_ctype;
}


/*
    This routine returns the compound type associated with the class ct.
*/

TYPE
make_class_type(CLASS_TYPE ct)
{
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	TYPE t = DEREF_type(id_class_name_etc_defn(cid));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	return t;
}


/*
    This routine redeclares the template class t using the template type
    qualifiers q.
*/

static TYPE
redecl_templ_class(TYPE q, TYPE t, IDENTIFIER *pid)
{
	TYPE s = t;
	IDENTIFIER id;
	while (IS_type_templ(s)) {
		s = DEREF_type(type_templ_defn(s));
	}
	s = inject_pre_type(q, s, 0);
	s = bind_specialise(pid, s, dspec_none, 1, 0, 0);
	id = *pid;
	if (eq_type(s, t) == 1) {
		/* Consistent redeclaration */
		TYPE ps = s;
		TYPE pt = t;
		redecl_template(&pt, &ps, id);
	} else {
		/* Inconsistent redeclaration */
		ERROR err = ERR_basic_link_incompat(s, t);
		ERROR err2 = ERR_basic_link_decl_type(id, id_loc(id));
		err = concat_error(err, err2);
		report(crt_loc, err);
	}
	return s;
}


/*
    This routine does the opposite of inject_pre_type by extracting the
    template qualifiers from the type t.
*/

static TYPE
extract_templ_qual(TYPE t)
{
	if (!IS_NULL_type(t) && IS_type_templ(t)) {
		TYPE s = DEREF_type(type_templ_defn(t));
		s = extract_templ_qual(s);
		COPY_type(type_templ_defn(t), s);
		return t;
	}
	return NULL_type;
}


/*
    This routine declares a class or enumeration type with name nm,
    class key key (which can be btype_class, btype_struct, btype_union
    or btype_enum) and template specifiers q.  The argument def is 1 if
    the type is about to be defined or 2 if it is about to be defined
    as a token.  Note that it is possible for a class or enumeration
    to have the same name as an object in the same scope.  In this case
    the type name is hidden by the object name.
*/

static IDENTIFIER
declare_type(NAMESPACE ns, HASHID nm, BASE_TYPE key, TYPE q, int def,
	     int force)
{
	TYPE t = NULL_type;
	MEMBER mem = search_member(ns, nm, 1);
	IDENTIFIER pid = DEREF_id(member_id(mem));
	IDENTIFIER id = type_member(mem, 3);
	if (!IS_NULL_id(id)) {
		/* Check for reserved identifiers */
		IDENTIFIER qid = id;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_reserve) {
			PTR(LOCATION)loc = id_loc(id);
			report(crt_loc, ERR_basic_odr_def_type(id, loc));
			id = NULL_id;
		} else {
			id = redecl_inherit(id, crt_id_qualifier,
					    in_class_defn, 0);
		}

		/* Check previous type declaration */
		if (!IS_NULL_id(id)) {
			switch (TAG_id(id)) {

			case id_class_name_tag:
			case id_enum_name_tag: {
				/* Previously declared as class name */
				int hide_prev = check_key(id, key);
				int prev_def = is_defined(id, &t, 1);
				if (!IS_NULL_type(q) || IS_type_templ(t)) {
					/* Redeclaration of template type */
					q = redecl_templ_class(q, t, &id);
				}
				if (def && prev_def) {
					/* Multiple definitions */
					if (def == 2) {
						/* This is a token */
						/* EMPTY */
					} else if (prev_def == 2) {
						/* Previous was a token */
						/* EMPTY */
					} else {
						/* Neither is a token */
						PTR(LOCATION)loc = id_loc(id);
						ERROR err = ERR_basic_odr_def_type(id, loc);
						report(crt_loc, err);
						q = extract_templ_qual(q);
						t = NULL_type;
					}
					break;
				}
				if (hide_prev) {
					/* Hide previous if only one is an
					 * enumeration */
					break;
				}
				/* This is a genuine type redeclaration */
				found_elaborate_type = 1;
				if (in_class_defn) {
					/* Adjust access specifiers */
					adjust_access(id, crt_access, 0);
				}
				if (def) {
					/* Record location of definition */
					if (!IS_NULL_type(q)) {
						/* Update template class */
						COPY_type(id_class_name_etc_defn(id), q);
						reset_primary_templ(t, q);
					}
					COPY_loc(id_loc(id), decl_loc);
				}
				return id;
			}
			case id_class_alias_tag:
			case id_enum_alias_tag:
			case id_type_alias_tag: {
				/* Previously declared as typedef name */
				PTR(LOCATION)loc = id_loc(id);
				report(crt_loc,
				       ERR_basic_odr_def_type(id, loc));
				break;
			}
			case id_nspace_name_tag:
			case id_nspace_alias_tag: {
				/* Previously declared as namespace name */
				PTR(LOCATION)loc = id_loc(id);
				report(crt_loc, ERR_basic_odr_decl(id, loc));
				break;
			}
			}
			/* Clobber previous definition */
			if (EQ_id(pid, qid)) {
				COPY_id(member_id(mem), NULL_id);
				pid = NULL_id;
			}
			COPY_id(member_alt(mem), NULL_id);
		}
	}

	/* Check for template declarations */
	if (!IS_NULL_type(q)) {
		if (!IS_NULL_id(pid)) {
			/* Already declared as object */
			PTR(LOCATION)loc = id_loc(pid);
			report(crt_loc, ERR_basic_odr_diff(pid, loc));
		}
		if (crt_linkage == dspec_c) {
			report(crt_loc, ERR_temp_decl_linkage());
		}
	}

	/* Construct the type declaration */
	if (force) {
		id = make_class(ns, nm, key, dspec_none, q, t);
		set_type_member(mem, id);
		if (IS_nspace_param(ns)) {
			/* Warn about function parameter scope */
			report(crt_loc, ERR_basic_scope_pdecl_param(id));
		}
	}
	found_elaborate_type = 0;
	return id;
}


/*
    This routine returns the class type corresponding to the member
    identifier id.  The null type is returned for non-members.
*/

CLASS_TYPE
parent_class(IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		NAMESPACE ns = DEREF_nspace(id_parent(id));
		if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
			IDENTIFIER cid = DEREF_id(nspace_name(ns));
			TYPE t = DEREF_type(id_class_name_etc_defn(cid));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			if (IS_type_compound(t)) {
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				return ct;
			}
		}
	}
	return NULL_ctype;
}


/*
    This routine returns the class type corresponding to the namespace
    ns.  The null type is returned if ns is not a class member namespace.
*/

CLASS_TYPE
namespace_class(NAMESPACE ns)
{
	if (IS_nspace_ctype(ns)) {
		CLASS_TYPE ct;
		IDENTIFIER cid = DEREF_id(nspace_name(ns));
		TYPE t = DEREF_type(id_class_name_etc_defn(cid));
		while (IS_type_templ(t)) {
			t = DEREF_type(type_templ_defn(t));
		}
		ct = DEREF_ctype(type_compound_defn(t));
		return ct;
	}
	return NULL_ctype;
}


/*
    The variable crt_class holds the class currently being defined.  The
    stack class_stack allows for nested class definitions.
*/

CLASS_TYPE crt_class = NULL_ctype;
static STACK(CLASS_TYPE) class_stack = NULL_stack(CLASS_TYPE);


/*
    This routine sets the current class to ct pushing the previous class
    to the class stack.
*/

void
push_class(CLASS_TYPE ct)
{
	PUSH_ctype(crt_class, class_stack);
	crt_class = ct;
	return;
}


/*
    This routine sets the current class from the top of the class stack.
*/

void
pop_class(void)
{
	POP_ctype(crt_class, class_stack);
	return;
}


/*
    This routine checks whether the class ct is in the process of being
    defined by checking it against the current class and the various
    elements of the class stack.
*/

int
defining_class(CLASS_TYPE ct)
{
	NAMESPACE nt;
	LIST(NAMESPACE)q;
	LIST(CLASS_TYPE)p;
	if (EQ_ctype(ct, crt_class)) {
		return 1;
	}
	p = LIST_stack(class_stack);
	while (!IS_NULL_list(p)) {
		CLASS_TYPE cs = DEREF_ctype(HEAD_list(p));
		if (EQ_ctype(cs, ct)) {
			return 1;
		}
		p = TAIL_list(p);
	}
	nt = DEREF_nspace(ctype_member(ct));
	q = LIST_stack(namespace_stack);
	while (!IS_NULL_list(q)) {
		NAMESPACE ns = DEREF_nspace(HEAD_list(q));
		if (EQ_nspace(ns, nt)) {
			return 1;
		}
		q = TAIL_list(q);
	}
	return 0;
}


/*
    This routine begins the definition of a class type (this includes
    structures and unions).  The class name is given by id and key is one
    of the values btype_class, btype_struct or btype_union indicating the
    class key.  ci gives any initial class information and q gives any
    template class qualifiers.
*/

IDENTIFIER
begin_class_defn(IDENTIFIER id, BASE_TYPE key, CLASS_INFO ci, TYPE q)
{
	TYPE t;
	DECL_SPEC ds;
	CLASS_TYPE ct;
	CLASS_INFO cj;
	int nested = 0;
	IDENTIFIER cid = NULL_id;
	QUALIFIER cq = crt_id_qualifier;
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = crt_namespace;
	begin_declarator(id, cq, qual_namespace, 1);
	IGNORE incr_value(OPT_VAL_nested_class);

	/* Check for template specialisations */
	if (is_templ_decl(id, NULL_type) || is_templ_spec(q)) {
		q = bind_specialise(&id, q, dspec_none, 1, 1, 1);
		if (IS_NULL_id(id) || check_key(id, key)) {
			nm = lookup_anon();
			id = DEREF_id(hashid_id(nm));
			cq = qual_none;
		} else {
			cid = id;
			ns = DEREF_nspace(id_parent(cid));
			check_decl_nspace(cid, ns, 1, crt_namespace);
			if (is_defined(cid, &t, 0)) {
				/* Redefinition of template class */
				PTR(LOCATION)loc = id_loc(cid);
				ERROR err = ERR_basic_odr_def_type(cid, loc);
				report(crt_loc, err);
			}
		}
	}

	/* Check for qualified identifiers */
	if (IS_NULL_id(cid)) {
		/* Check on class name */
		int def = 1;
		ERROR err = check_id_name(id, CONTEXT_CLASS);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
		if (IS_nspace_ctype(ns)) {
			nested = 1;
		}
		if (cq == qual_none) {
			/* Simple class name */
			if (option(OPT_class_scope)) {
				ns = crt_namespace;
				if (IS_nspace_param(ns)) {
					ns = nonclass_namespace;
					if (nested) {
						nested = 2;
					}
				}
			} else {
				ns = nonclass_namespace;
				if (nested) {
					nested = 2;
				}
			}
		} else {
			/* Definition of nested class */
			ns = DEREF_nspace(id_parent(id));
			check_decl_nspace(id, ns, 1, crt_namespace);
			if (IS_id_undef(id)) {
				nm = lookup_anon();
			}
			if (nested) {
				nested = 2;
			}
		}

		/* Declare the type */
		if (ci & cinfo_token) {
			def = 2;
		}
		cid = declare_type(ns, nm, key, q, def, 1);
	}

	/* Find the class type */
	t = DEREF_type(id_class_name_defn(cid));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ct = DEREF_ctype(type_compound_defn(t));
	ns = DEREF_nspace(ctype_member(ct));

	/* Mark start of definition */
	cj = DEREF_cinfo(ctype_info(ct));
	cj = set_class_key(cj, key);
	cj |= (ci | cinfo_defined);
	if (nested == 1) {
		cj |= cinfo_nested;
	}
	cj &= ~cinfo_complete;
	COPY_cinfo(ctype_info(ct), cj);

	/* Mark tokenised types */
	ds = DEREF_dspec(id_storage(cid));
	if (cj & cinfo_token) {
		ds |= dspec_token;
	}
	COPY_dspec(id_storage(cid), (ds | dspec_defn));

#if LANGUAGE_CPP
	/* Make sure that nested classes are nested */
	if (nested == 2) {
		NAMESPACE pns = crt_namespace;
		HASHID pnm = lookup_anon();
		IDENTIFIER pid = declare_type(pns, pnm, key, q, 1, 1);
		ds = DEREF_dspec(id_storage(pid));
		COPY_dspec(id_storage(pid), (ds | dspec_defn));
		t = DEREF_type(id_class_name_defn(cid));
		COPY_type(id_class_name_defn(pid), t);
	}
#endif

	/* Force definition information */
	COPY_loc(id_loc(cid), decl_loc);
	if (do_dump) {
		dump_declare(cid, &decl_loc, 1);
	}

	/* Push current class and namespace */
	push_namespace(ns);
	push_class(ct);

	/* Set up default access specifier */
	ds = (key == btype_class ? dspec_private : dspec_public);
	crt_access = ds;
	prev_access = ds;
	return cid;
}


/*
    This routine completes the definition of the class type id.
*/

IDENTIFIER
end_class_defn(IDENTIFIER id)
{
	TYPE p;
	CLASS_TYPE ct;
	CLASS_INFO ci;
	LIST(IDENTIFIER)ft;
	HASHID nm = DEREF_hashid(id_name(id));
	TYPE t = DEREF_type(id_class_name_defn(id));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ct = DEREF_ctype(type_compound_defn(t));

	/* Deal with implicitly declared constructors */
	ci = DEREF_cinfo(ctype_info(ct));
	if (ci & cinfo_empty) {
		report(crt_loc, ERR_class_none());
	}
#if LANGUAGE_CPP
	ci = implicit_decl(ct, ci, dspec_none);
#endif
	if (ci & cinfo_non_aggregate) {
		/* POD classes must be aggregate classes */
		ci &= ~cinfo_pod;
	}
	ci |= cinfo_complete;
	COPY_cinfo(ctype_info(ct), ci);

	/* Deal with any inheritance issues */
	inherit_class();

	/* Check for previous definitions */
	p = DEREF_type(ctype_prev(ct));
	if (!IS_NULL_type(p)) {
		if (ci & cinfo_token) {
			/* Make p the tokenised type */
			TYPE q = p;
			p = t;
			t = q;
		}
		force_tokdef++;
		IGNORE unify_type(p, t, cv_none, 0);
		force_tokdef--;
	}

	/* Compile any inline functions */
	if (is_exported(id)) {
		export_template(id, 1);
	}
	ft = DEREF_list(ctype_pals(ct));
	if (!IS_NULL_list(ft)) {
		unsigned nf;
		ft = REVERSE_list(ft);
		COPY_list(ctype_pals(ct), ft);
		nf = LENGTH_list(ft);
		IGNORE check_value(OPT_VAL_friends,(ulong)nf);
	}
	ft = DEREF_list(ctype_nest(ct));
	if (!IS_NULL_list(ft)) {
		ft = REVERSE_list(ft);
		COPY_list(ctype_nest(ct), ft);
		if (!(ci & cinfo_nested) || in_class_defn == 1) {
			rescan_functions();
		}
	}

	/* Pop current class and namespace */
	if (do_dump) {
		dump_undefine(id, &crt_loc, 0);
	}
	IGNORE pop_namespace();
	pop_class();
	decr_value(OPT_VAL_nested_class);
	end_declarator(id, 1);

	/* Set type declaration flag */
	if (IS_hashid_anon(nm)) {
		have_type_declaration = TYPE_DECL_ANON;
	} else {
		have_type_declaration = TYPE_DECL_NORMAL;
	}
	return id;
}


/*
    This routine checks the effect of a non-static data member or base
    class (as indicated by base) with class information cj on a class
    with class information ci.  In a class definition trivial_constr,
    for example, is true if all the base classes and members have
    trivial constructors.  At the end of the definition, when the
    implicit constructors are declared, it is used to indicate that the
    class itself has a trivial constructor.
*/

CLASS_INFO
check_class_info(CLASS_INFO ci, CLASS_INFO cj, int base, DECL_SPEC acc)
{
	if (!(cj & cinfo_pod)) {
		ci &= ~cinfo_pod;
	}
	if (!(cj & cinfo_trivial_constr)) {
		ci &= ~cinfo_trivial_constr;
	}
	if (!(cj & cinfo_trivial_copy)) {
		ci &= ~cinfo_trivial_copy;
	}
	if (!(cj & cinfo_trivial_assign)) {
		ci &= ~cinfo_trivial_assign;
	}
	if (!(cj & cinfo_trivial_destr)) {
		ci &= ~cinfo_trivial_destr;
	}
	if (!(cj & cinfo_const_copy)) {
		ci &= ~cinfo_const_copy;
	}
	if (!(cj & cinfo_const_assign)) {
		ci &= ~cinfo_const_assign;
	}
	if (cj & cinfo_recursive) {
		ci |= cinfo_recursive;
	}
	if (cj & cinfo_params) {
		ci |= cinfo_params;
	}
	if (cj & cinfo_const) {
		ci |= cinfo_const;
	}
	if (base) {
		/* Base class checks */
		if (cj & cinfo_multiple_base) {
			ci |= cinfo_multiple_base;
		}
		if (cj & cinfo_templ_base) {
			ci |= cinfo_templ_base;
		}
		if (cj & cinfo_function) {
			ci |= cinfo_function;
		}
		if (cj & cinfo_static) {
			ci |= cinfo_static;
		}
		ci &= ~cinfo_empty;
		ci |= cinfo_base;
		UNUSED(acc);
	}
	return ci;
}


/*
    This routine checks whether the class ct has trivial default
    constructors, destructors, copy constructors and copy assignment
    operators.
*/

ERROR
check_trivial_class(CLASS_TYPE ct)
{
	ERROR err = NULL_err;
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	CLASS_INFO cj = (ci & cinfo_trivial);
	if (cj != cinfo_trivial) {
		if (!(cj & cinfo_trivial_constr)) {
			err = ERR_class_ctor_nontriv(ct);
		} else if (!(cj & cinfo_trivial_destr)) {
			err = ERR_class_dtor_nontriv(ct);
		} else if (!(cj & cinfo_trivial_copy)) {
			err = ERR_class_copy_nontriv_constr(ct);
		} else if (!(cj & cinfo_trivial_assign)) {
			err = ERR_class_copy_nontriv_assign(ct);
		}
	}
	return err;
}


/*
    This routine checks the type t of a non-static data member of the
    class ct.  This is recorded in the effect on the class information ci.
    The criterion for spotting recursively defined classes is that it
    contains a pointer to an incomplete type (or a base class or member
    of such a type).  This certainly contains all recursive types, and
    is about the best that can be done without any deep analysis.
*/

CLASS_INFO
check_member_type(CLASS_TYPE ct, CLASS_INFO ci, TYPE t, int ptr)
{
	if (!ptr) {
		/* Check for const members */
		CV_SPEC cv = DEREF_cv(type_qual(t));
		if (cv & cv_const) {
			ci |= cinfo_const;
		}
	}
	switch (TAG_type(t)) {
	case type_compound_tag: {
		/* Compound types */
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO cj = DEREF_cinfo(ctype_info(cs));
		if (!(cj & cinfo_complete)) {
			/* Could be a recursive type ... */
			ci |= cinfo_recursive;
		}
		if (!ptr) {
			if (ci & cinfo_union) {
				/* Union component must be trivial */
				ERROR err = check_trivial_class(cs);
				if (!IS_NULL_err(err)) {
					ERROR err2 = ERR_class_union_mem(ct, t);
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
			}
			ci = check_class_info(ci, cj, 0, dspec_none);
		}
		break;
	}
	case type_ptr_tag: {
		/* Pointer types */
		if (!ptr) {
			TYPE s = DEREF_type(type_ptr_sub(t));
			ci = check_member_type(ct, ci, s, 1);
		}
		break;
	}
	case type_ref_tag: {
		/* Reference types */
		if (!ptr) {
			TYPE s = DEREF_type(type_ref_sub(t));
			if (ci & cinfo_union) {
				/* Unions can't have reference members */
				report(crt_loc, ERR_class_union_ref(ct, t));
			}
			ci = check_member_type(ct, ci, s, 1);
			ci &= ~cinfo_pod;
		}
		break;
	}
	case type_ptr_mem_tag: {
		/* Pointer to member types */
		if (!ptr) {
			ci &= ~cinfo_pod;
		}
		break;
	}
	case type_array_tag: {
		/* Array types */
		TYPE s = DEREF_type(type_array_sub(t));
		ci = check_member_type(ct, ci, s, ptr);
		break;
	}
	}
	if (is_templ_depend(t)) {
		ci |= cinfo_params;
	}
	return ci;
}


/*
    This routine reports the information about the class ct indicated by
    the class information mask cm.  It returns an error message summarising
    those properties which hold for ct.  At most n properties are reported.
*/

ERROR
class_info(CLASS_TYPE ct, CLASS_INFO cm, int n)
{
	/* Find class information */
	ERROR err = NULL_err;
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	ci &= cm;
	if (ci == cinfo_none) {
		return err;
	}

	/* Check for tokenised types */
	if (ci & cinfo_token) {
		IDENTIFIER id = DEREF_id(ctype_name(ct));
		err = concat_error(err, ERR_token_info(id));
		if (--n == 0) {
			return err;
		}
	}

	/* Check for user-defined constructors */
	if (ci & cinfo_usr_constr) {
		err = concat_error(err, ERR_class_ctor_user(ct));
		if (--n == 0) {
			return err;
		}
	}

	/* Check for ambiguous base classes */
	if (ci & cinfo_ambiguous) {
		GRAPH gr = DEREF_graph(ctype_base(ct));
		gr = find_ambig_base(gr);
		if (!IS_NULL_graph(gr)) {
			/* Ambiguous base class found */
			CLASS_TYPE cs = DEREF_ctype(graph_head(gr));
			ERROR err2 = ERR_class_member_lookup_ambig(cs, ct);
			err = concat_error(err, err2);
			if (--n == 0) {
				return err;
			}
		}
	}

	/* Check for base classes */
	if (ci & cinfo_base) {
		CLASS_TYPE cs;
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH)tails = DEREF_list(graph_tails(gr));
		gr = DEREF_graph(HEAD_list(tails));
		cs = DEREF_ctype(graph_head(gr));
		err = concat_error(err, ERR_class_derived_base(ct, cs));
		if (--n == 0) {
			return err;
		}
	}

	/* Check for private or protected members */
	if (ci & cinfo_private) {
		err = concat_error(err, ERR_class_access_spec_priv(ct));
		if (--n == 0) {
			return err;
		}
	}

	/* Check for abstract classes */
	if (ci & cinfo_abstract) {
		IDENTIFIER id = find_pure_function(ct);
		err = concat_error(err, ERR_class_abstract_pure(id));
		err = concat_error(err, ERR_class_abstract_class(ct));
		if (--n == 0) {
			return err;
		}
	}

	/* Check for polymorphic classes */
	if (ci & cinfo_polymorphic) {
		err = concat_error(err, ERR_class_virtual_poly(ct));
		if (--n == 0) {
			return err;
		}
	}

	/* Return the resultant error */
	UNUSED(n);
	return err;
}


/*
    This routine checks whether the class type ct has a non-trivial member,
    that is to say not all its base classes and members are empty classes.
*/

static int
is_empty_ctype(CLASS_TYPE ct)
{
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH)br = DEREF_list(graph_tails(gr));
	NAMESPACE ns = DEREF_nspace(ctype_member(ct));
	MEMBER mem = DEREF_member(nspace_ctype_first(ns));
	mem = next_data_member(mem, 2);
	if (!IS_NULL_member(mem)) {
		return 0;
	}
	while (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
		if (!is_empty_ctype(cs)) {
			return 0;
		}
		br = TAIL_list(br);
	}
	return 1;
}


/*
    This routine checks whether the type t is an empty class type or an
    array of such.
*/

int
is_empty_class(TYPE t)
{
	while (!IS_NULL_type(t)) {
		switch (TAG_type(t)) {
		case type_compound_tag: {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			return is_empty_ctype(ct);
		}
		case type_array_tag: {
			t = DEREF_type(type_array_sub(t));
			break;
		}
		case type_templ_tag: {
			t = DEREF_type(type_templ_defn(t));
			break;
		}
		default:
			return 0;
		}
	}
	return 0;
}


/*
    This routine begins the definition on an enumeration type.  The
    enumeration name is given by id and q gives any template type qualifiers.
    Note that an enumeration definition does not define a scope.
*/

IDENTIFIER
begin_enum_defn(IDENTIFIER id, TYPE q)
{
	TYPE t;
	ERROR err;
	DECL_SPEC ds;
	NAMESPACE ns;
	ENUM_TYPE et;
	CLASS_INFO ei;
	IDENTIFIER eid = id;
	QUALIFIER cq = crt_id_qualifier;
	HASHID nm = DEREF_hashid(id_name(eid));
	begin_declarator(id, cq, qual_namespace, 1);

	/* Check on enumeration name */
	if (is_templ_decl(id, NULL_type) || is_templ_spec(q)) {
		/* Shouldn't have a template application */
		q = bind_specialise(&eid, q, dspec_none, 1, 1, 1);
		if (IS_NULL_id(eid) || check_key(eid, btype_enum)) {
			nm = lookup_anon();
			eid = DEREF_id(hashid_id(nm));
			cq = qual_none;
		}
	}
	err = check_id_name(eid, CONTEXT_ENUM);
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}

	/* Check for qualified identifiers */
	if (cq == qual_none) {
		/* Simple enumeration name */
		if (option(OPT_class_scope)) {
			ns = crt_namespace;
			if (IS_nspace_param(ns)) {
				ns = nonclass_namespace;
			}
		} else {
			ns = nonclass_namespace;
		}
	} else {
		/* Definition of nested enumeration */
		ns = DEREF_nspace(id_parent(eid));
		check_decl_nspace(eid, ns, 1, crt_namespace);
		if (IS_id_undef(eid)) {
			nm = lookup_anon();
		}
	}

	/* Declare the enumeration */
	eid = declare_type(ns, nm, btype_enum, q, 1, 1);
	ds = DEREF_dspec(id_storage(eid));
	COPY_dspec(id_storage(eid), (ds | dspec_defn));
	t = DEREF_type(id_enum_name_defn(eid));
	et = DEREF_etype(type_enumerate_defn(t));

	/* Mark start of definition */
	ei = DEREF_cinfo(etype_info(et));
	ei |= cinfo_defined;
	ei &= ~cinfo_complete;
	COPY_cinfo(etype_info(et), ei);
	if (do_dump) {
		dump_declare(eid, &decl_loc, 1);
	}

	/* Force definition information */
	COPY_loc(id_loc(eid), decl_loc);
	return eid;
}


/*
    This routine completes the definition of the enumeration type id.
    Note that only at this stage do the enumerators acquire the type
    of the enumeration in C++.
*/

IDENTIFIER
end_enum_defn(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	TYPE t = DEREF_type(id_enum_name_defn(id));
	ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
	CLASS_INFO ei = DEREF_cinfo(etype_info(et));

	/* Sort enumerators */
	LIST(IDENTIFIER)ens = DEREF_list(etype_values(et));
	unsigned nenums = LENGTH_list(ens);
	if (nenums == 0) {
		report(crt_loc, ERR_dcl_enum_none());
	}
	IGNORE check_value(OPT_VAL_enum_consts,(ulong)nenums);
	ens = REVERSE_list(ens);
	COPY_list(etype_values(et), ens);

#if LANGUAGE_CPP
	/* Convert enumerators to enumeration type */
	while (!IS_NULL_list(ens)) {
		IDENTIFIER eid = DEREF_id(HEAD_list(ens));
		EXP e = DEREF_exp(id_enumerator_value(eid));
		e = eval_exp(e, 0);
		e = cast_exp(t, e, KILL_err, CAST_STATIC);
		if (IS_exp_int_lit(e)) {
			COPY_unsigned(exp_int_lit_etag(e), exp_identifier_tag);
			if (is_zero_exp(e)) {
				ei |= cinfo_usr_constr;
			}
			COPY_exp(id_enumerator_value(eid), e);
		}
		ens = TAIL_list(ens);
	}
#endif

	/* Mark end of definition */
	ei |= cinfo_complete;
	COPY_cinfo(etype_info(et), ei);
	COPY_exp(etype_value(et), NULL_exp);
	COPY_ulong(etype_plus(et), 0);
	if (do_dump) {
		dump_undefine(id, &crt_loc, 0);
	}
	end_declarator(id, 1);

	/* Set type declaration flag */
	if (IS_hashid_anon(nm) && nenums == 0) {
		have_type_declaration = TYPE_DECL_ANON;
	} else {
		have_type_declaration = TYPE_DECL_NORMAL;
	}
	return id;
}


/*
    The underlying type of an enumeration can be int, unsigned int, long
    or unsigned long, depending on the values of the enumerators.  This
    macro gives the maximum value which is guaranteed to fit into all of
    these types.  Because unsigned types are involved, the minimum value
    is 0.
*/

#define ENUM_MAX		((unsigned long)0x7fff)


/*
    This routine declares an enumerator named id belonging to the enumeration
    type indicated by eid.  The value of the enumerator is given by the
    integer constant expression val, if this is present, or one more than
    the previous enumerator otherwise.  In C the value is converted to
    'int'.  In C++ the value is converted to the enumeration type, but
    this is only done at the end of the enumeration definition.
*/

IDENTIFIER
make_enumerator(IDENTIFIER eid, IDENTIFIER id, EXP val)
{
	NAT n;
	EXP e;
	ERROR err;
	int record = 0;
	unsigned long v;
	DECL_SPEC ds = (crt_access | dspec_defn | dspec_lang);

	/* Find the current enumeration type */
	TYPE t = DEREF_type(id_enum_name_defn(eid));
	ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
	CLASS_INFO ei = DEREF_cinfo(etype_info(et));
	LIST(IDENTIFIER)ens = DEREF_list(etype_values(et));
	NAMESPACE ns = DEREF_nspace(id_parent(eid));

	/* Look up the enumerator name */
	IDENTIFIER nid = id;
	HASHID nm = DEREF_hashid(id_name(nid));
	MEMBER mem = search_member(ns, nm, 1);

	/* Check on enumeration name */
	err = check_id_name(nid, CONTEXT_ENUMERATOR);
	if (!IS_NULL_err(err)) {
		report(decl_loc, err);
		err = NULL_err;
	}

	/* Check for redeclarations */
	nid = DEREF_id(member_id(mem));
	if (!IS_NULL_id(nid)) {
		nid = redecl_inherit(nid, crt_id_qualifier, in_class_defn, 0);
		if (!IS_NULL_id(nid)) {
			IGNORE redecl_id(dspec_reserve, t, nid, 0, 0);
		}
	}

	/* Declare the enumerator */
	MAKE_id_enumerator(nm, ds, ns, decl_loc, t, val, nid);
	if (do_dump) {
		dump_declare(nid, &decl_loc, 1);
	}

	/* Find the enumerator value */
	t = DEREF_type(etype_rep(et));
	if (!IS_NULL_exp(val)) {
		/* Check that any given val is a constant */
		TYPE s = DEREF_type(exp_type(val));
#if LANGUAGE_CPP
		s = promote_type(s);
		val = convert_promote(s, val);
#else
		switch (TAG_type(s)) {
		case type_integer_tag:
		case type_bitfield_tag:
		case type_enumerate_tag: {
			/* Convert integral values to 'int' */
			s = t;
			val = cast_int_int(s, val, &err, CAST_IMPLICIT, -1);
			if (!IS_NULL_err(err)) {
				report(crt_loc, err);
				err = NULL_err;
			}
			break;
		}
		}
#endif
		n = make_nat_exp(val, &err);
		if (!IS_NULL_err(err)) {
			/* Value is not an integral constant */
			err = concat_error(err, ERR_dcl_enum_const(nid));
			report(crt_loc, err);
			s = t;
		}
		v = get_nat_value(n);
		if (v <= ENUM_MAX) {
			/* Small values */
			if (!EQ_type(t, s)) {
				/* Mark if enumerator has different type */
				ei |= cinfo_polymorphic;
				t = s;
			}
			if (v == 0) {
				ei |= cinfo_usr_constr;
			}
			COPY_exp(etype_value(et), NULL_exp);
		} else {
			/* Large values */
			EXP cond = crt_hash_cond;
			if (!EQ_type(t, s)) {
				/* Extend type range if necessary */
				t = arith_type(t, s, NULL_exp, NULL_exp);
				COPY_type(etype_rep(et), t);
				ei |= cinfo_polymorphic;
				t = s;
			}
			if (!IS_NULL_exp(cond) && is_calc_nat(n)) {
				/* Propagate target dependent conditionals */
				EXP alt = make_null_exp(t);
				MAKE_exp_hash_if (t, cond, val, alt, val);
				MAKE_nat_calc(val, n);
			}
			record = 1;
			v = 0;
		}
	} else {
		/* Other enumerators are one more than the previous one */
		v = DEREF_ulong(etype_plus(et));
		n = make_nat_value(v);
		e = DEREF_exp(etype_value(et));
		if (IS_NULL_exp(e)) {
			if (ei & cinfo_polymorphic) {
				/* Use type of last enumerator, if different */
				IDENTIFIER pid = DEREF_id(HEAD_list(ens));
				e = DEREF_exp(id_enumerator_value(pid));
				t = DEREF_type(exp_type(e));
			}
			if (v == 0) {
				ei |= cinfo_usr_constr;
			}
		} else {
			EXP c;
			t = DEREF_type(exp_type(e));
			MAKE_exp_int_lit(t, n, exp_int_lit_tag, c);
			MAKE_exp_plus(t, e, c, e);
			MAKE_nat_calc(e, n);
		}
	}
	MAKE_exp_int_lit(t, n, exp_identifier_tag, e);
	COPY_exp(id_enumerator_value(nid), e);

	/* Increment enumerator counter */
	if (v >= ENUM_MAX) {
		record = 1;
		v = 0;
	}
	if (record) {
		COPY_exp(etype_value(et), e);
	}
	COPY_ulong(etype_plus(et), v + 1);

	/* Add enumerator to the enumerator list */
	set_member(mem, nid);
	CONS_id(nid, ens, ens);
	COPY_list(etype_values(et), ens);
	COPY_cinfo(etype_info(et), ei);
	return nid;
}


/*
    This routine checks whether the integer constant n is a valid enumerator
    for the enumeration et.  If so it returns the enumerator identifier.
*/

IDENTIFIER
find_enumerator(ENUM_TYPE et, NAT n)
{
	LIST(IDENTIFIER)p = DEREF_list(etype_values(et));
	while (!IS_NULL_list(p)) {
		IDENTIFIER eid = DEREF_id(HEAD_list(p));
		EXP e = DEREF_exp(id_enumerator_value(eid));
		NAT m = DEREF_nat(exp_int_lit_nat(e));
		if (EQ_nat(n, m) || eq_nat(n, m)) {
			return eid;
		}
		p = TAIL_list(p);
	}
	return NULL_id;
}


/*
    This flag is set by find_elaborate_type and declare_type to indicate
    that the given type specifier referred to a pre-existing type.
*/

int found_elaborate_type = 0;


/*
    This routine finds the type identifier corresponding to the elaborated
    type specifier with identifier id, class key key (which can be
    btype_class, btype_struct, btype_union or btype_enum) and template
    type qualifiers q.  The argument mode gives information on the
    context for the type specifier:

	dspec_defn	for explicit declarations,
	dspec_friend	for friend declarations,
	dspec_alias	for qualified identifiers,
	dspec_auto	if type is to be declared in current namespace,
	dspec_used	if type is to be searched for.
*/

IDENTIFIER
find_elaborate_type(IDENTIFIER id, BASE_TYPE key, TYPE q, DECL_SPEC mode)
{
	ERROR err;
	LOCATION loc;
	NAMESPACE ns;
	IDENTIFIER tid;
	int templ = is_templ_spec(q);
	HASHID nm = DEREF_hashid(id_name(id));

	/* Check for template applications */
	if (templ || is_templ_decl(id, NULL_type)) {
		tid = id;
		if (mode & dspec_defn) {
			/* Bind template specialisations */
			DECL_SPEC ds = (mode & dspec_friend);
			q = bind_specialise(&tid, q, ds, 1, 1, 0);
		}
		if (!IS_NULL_id(tid) && IS_id_class_name_etc(tid)) {
			IGNORE check_key(tid, key);
			if (templ) {
				/* Check namespace for explicit declaration */
				ns = DEREF_nspace(id_parent(tid));
				check_decl_nspace(tid, ns, 0, crt_namespace);
			}
			found_elaborate_type = 1;
			return tid;
		}
	} else {
		if (mode & dspec_alias) {
			/* Qualified identifier */
			NAMESPACE tns = DEREF_nspace(id_parent(id));
			tid = find_qual_id(tns, nm, 0, 1);
			if (IS_NULL_id(tid) || !IS_id_class_name_etc(tid)) {
				if (!IS_NULL_id(tid) && IS_id_ambig(tid)) {
					tid = report_ambiguous(tid, 1, 1, 1);
				} else {
					report(crt_loc,
					       ERR_dcl_type_simple_undef(id));
					tid = NULL_id;
					q = NULL_type;
				}
			}
		} else if (mode & dspec_register) {
			/* Search enclosing namespace */
			tid = find_extern_id(nm, nonclass_namespace, 1);
		} else if (mode & dspec_used) {
			/* Search for enclosing declaration */
			tid = find_type_id(nm, 1);
		} else {
			/* Force a new declaration */
			tid = NULL_id;
		}
	}

	/* Check previous declaration */
	while (!IS_NULL_id(tid)) {
		if (IS_id_class_name_etc(tid)) {
			/* Previous declaration was a type name */
			BASE_TYPE prev = find_key(tid, 0, key);
			if (prev == btype_alias) {
				/* This was a typedef name */
				err = ERR_lookup_elab_alias(key, tid);
				report(crt_loc, err);
			} else if (!equal_key(prev, key)) {
				/* The class keys don't match */
				PTR(LOCATION)ploc = id_loc(tid);
				err = ERR_dcl_type_elab_bad(key, prev, tid,
							    ploc);
				report(crt_loc, err);
			}
			found_elaborate_type = 1;
			return tid;
		}
		if (IS_id_ambig(tid)) {
			tid = report_ambiguous(tid, 1, 1, 1);
		} else {
			report(crt_loc, ERR_lookup_elab_invalid(key, tid));
			tid = NULL_id;
		}
	}

	/* Find namespace for declared type */
	if (mode & dspec_alias) {
		/* Declare in parent namespace */
		ns = DEREF_nspace(id_parent(id));
	} else if ((mode & dspec_auto) && option(OPT_class_scope)) {
		/* Declare in the current namespace */
		ns = crt_namespace;
	} else if (mode & dspec_template) {
		/* Declare in template namespace */
		ns = templ_namespace;
	} else {
		/* Declare in enclosing namespace */
		ns = nonclass_namespace;
	}

	/* Declare new type */
	loc = decl_loc;
	err = check_id_name(id, CONTEXT_CLASS);
	id = underlying_id(id);
	DEREF_loc(id_loc(id), decl_loc);
	if (!IS_NULL_err(err)) {
		report(decl_loc, err);
	}
	tid = declare_type(ns, nm, key, q, 0, 1);
	if (do_dump) {
		dump_declare(tid, &decl_loc, 0);
	}
	if (key == btype_enum) {
		/* Can't declare enumerations (but have done) */
		report(decl_loc, ERR_lookup_elab_enum(tid));
	}
	if (mode & dspec_friend) {
		/* Warn about potential friend problems */
		report(decl_loc, ERR_class_friend_pre(tid));
	}
	decl_loc = loc;
	return tid;
}


/*
    This routine creates a typedef with name nm and definition t
    in the namespace ns (but doesn't bring it into scope).  Note that
    typedefs are split into class aliases, enumeration aliases and other
    type aliases.  In the former two cases the class identifier is
    associated with t as the type name, and the member namespace name for
    classes, if this has not yet been defined.
*/

IDENTIFIER
make_typedef(NAMESPACE ns, HASHID nm, TYPE t, DECL_SPEC ds)
{
	TYPE s;
	unsigned tag;
	IDENTIFIER id;

	/* Force copy of type */
	CV_SPEC cv = DEREF_cv(type_qual(t));
	t = qualify_type(t, cv, 1);
	s = t;
	tag = TAG_type(s);

	/* Check for template types */
	if (ds == dspec_none) {
		ds = (crt_access | dspec_defn);
	}
	while (tag == type_templ_tag) {
		s = DEREF_type(type_templ_defn(s));
		tag = TAG_type(s);
		ds |= dspec_template;
	}

	/* Check for class aliases */
	if (tag == type_compound_tag) {
		CV_SPEC qual = DEREF_cv(type_qual(s));
		if (qual == cv_none) {
			/* Find the class name */
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(s));
			IDENTIFIER cid = DEREF_id(ctype_name(ct));
			HASHID cnm = DEREF_hashid(id_name(cid));

			/* Set up the class alias */
			MAKE_id_class_alias(nm, ds, ns, decl_loc, t, id);

			if (IS_hashid_anon(cnm)) {
				/* Set the class name if necessary */
				NAMESPACE mns;
				if (do_dump) {
					dump_declare(id, &decl_loc, 1);
					dump_anon_class = 1;
				}
				COPY_dspec(id_storage(id), (ds | dspec_lang));
				mns = DEREF_nspace(ctype_member(ct));
				COPY_id(nspace_name(mns), id);
				COPY_id(ctype_name(ct), id);

				/* Also set constructor and destructor names */
				cid = DEREF_id(ctype_constr(ct));
				cnm = DEREF_hashid(id_name(cid));
				COPY_id(hashid_constr_tid(cnm), id);
				cid = DEREF_id(ctype_destr(ct));
				cnm = DEREF_hashid(id_name(cid));
				COPY_id(hashid_destr_tid(cnm), id);
			}
			return id;
		}
	}

	/* Check for enumeration aliases */
	if (tag == type_enumerate_tag) {
		CV_SPEC qual = DEREF_cv(type_qual(s));
		if (qual == cv_none) {
			/* Find the enumeration name */
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(s));
			IDENTIFIER eid = DEREF_id(etype_name(et));
			HASHID enm = DEREF_hashid(id_name(eid));

			/* Set up the enumeration alias */
			MAKE_id_enum_alias(nm, ds, ns, decl_loc, t, id);

			/* Set the enumeration name if necessary */
			if (IS_hashid_anon(enm)) {
				if (do_dump) {
					dump_declare(id, &decl_loc, 1);
					dump_anon_class = 1;
				}
				COPY_dspec(id_storage(id), (ds | dspec_lang));
				COPY_id(etype_name(et), id);
			}
			return id;
		}
	}

	/* Other type aliases */
	MAKE_id_type_alias(nm, ds, ns, decl_loc, t, id);
	return id;
}


/*
    This routine finds the member of the class cid corresponding to the
    class member id.  cid will be a copy of the class containing id.
    Note that if res is false a set of overloaded functions is mapped to
    a set of overloaded functions, further resolutions based on type may be
    performed later.  If res is true overload resolution is performed
    based on whether the result is an instantiation of id.
*/

IDENTIFIER
find_copied(IDENTIFIER cid, IDENTIFIER id, int res)
{
	HASHID nm;
	MEMBER mem;
	NAMESPACE ns;
	CLASS_TYPE ct;
	IDENTIFIER mid;

	/* Find class namespace */
	TYPE t = DEREF_type(id_class_name_etc_defn(cid));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ct = DEREF_ctype(type_compound_defn(t));
	complete_class(ct, 1);
	ns = DEREF_nspace(ctype_member(ct));

	/* Look up name in namespace */
	nm = DEREF_hashid(id_name(id));
	nm = expand_name(nm, ct);
	do {
		mem = search_member(ns, nm, 0);
		if (!IS_NULL_member(mem)) {
			break;
		}
		nm = next_expand_name(nm);
	} while (!IS_NULL_hashid(nm));

	/* Check for corresponding identifier */
	if (!IS_NULL_member(mem)) {
		mid = DEREF_id(member_id(mem));
		if (!IS_NULL_id(mid)) {
			/* Identifier matches member */
			if (IS_id_function_etc(mid) && IS_id_function_etc(id)) {
				/* Matching functions */
				if (res) {
					IDENTIFIER fid = NULL_id;
					TYPE f = DEREF_type(id_function_etc_form(id));
					if (!IS_NULL_type(f) && IS_type_instance(f)) {
						fid = DEREF_id(type_instance_id(f));
					}
					while (!IS_NULL_id(mid)) {
						/* Perform overload resolution */
						if (EQ_id(mid, id)) {
							return mid;
						}
						if (EQ_id(mid, fid)) {
							return mid;
						}
						f = DEREF_type(id_function_etc_form(mid));
						if (!IS_NULL_type(f) && IS_type_instance(f)) {
							IDENTIFIER nid;
							nid = DEREF_id(type_instance_id(f));
							if (EQ_id(nid, id)) {
								return mid;
							}
							if (EQ_id(nid, fid)) {
								return mid;
							}
						}
						mid = DEREF_id(id_function_etc_over(mid));
					}
					mid = id;
				}
				return mid;
			}
			if (TAG_id(mid) == TAG_id(id)) {
				return mid;
			}
		}
		mid = DEREF_id(member_alt(mem));
		if (!IS_NULL_id(mid) && TAG_id(mid) == TAG_id(id)) {
			/* Identifier matches type member */
			return mid;
		}
	}
	return id;
}


/*
    This routine creates a new class which is a copy of t.  This is used
    in the instantiation of template classes.  Note that the members of
    the class are copied later by copy_members.
*/

TYPE
copy_class(TYPE t, DECL_SPEC ds)
{
	LOCATION loc;
	IDENTIFIER tid;
	int r = really_in_class_defn;
	int f = really_in_function_defn;
	CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	BASE_TYPE key = find_class_key(ct);
	IDENTIFIER id = DEREF_id(ctype_name(ct));
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	DECL_SPEC acc = DEREF_dspec(id_storage(id));
	ds |= (acc & dspec_access);
	loc = crt_loc;
	bad_crt_loc++;
	really_in_class_defn = 0;
	really_in_function_defn = 0;
	DEREF_loc(id_loc(id), crt_loc);
	decl_loc = crt_loc;
	tid = make_class(ns, nm, key, ds, NULL_type, NULL_type);
	t = DEREF_type(id_class_name_defn(tid));
	really_in_function_defn = f;
	really_in_class_defn = r;
	bad_crt_loc--;
	decl_loc = loc;
	crt_loc = loc;
	return t;
}


/*
    This routine copies any partial or explicit specialisations of the
    template member tid of a template class to the corresponding member
    sid of an instance of that template class.
*/

static void
copy_specs(IDENTIFIER sid, IDENTIFIER tid, int type)
{
	TYPE s, t;
	if (type) {
		/* Template classes */
		s = DEREF_type(id_class_name_etc_defn(sid));
		t = DEREF_type(id_class_name_etc_defn(tid));
	} else {
		/* Template functions */
		s = DEREF_type(id_function_etc_type(sid));
		t = DEREF_type(id_function_etc_type(tid));
	}
	if (IS_type_templ(s) && IS_type_templ(t)) {
		TOKEN ps = DEREF_tok(type_templ_sort(s));
		TOKEN pt = DEREF_tok(type_templ_sort(t));
		INSTANCE as = DEREF_inst(tok_templ_apps(ps));
		INSTANCE at = DEREF_inst(tok_templ_apps(pt));
		while (!IS_NULL_inst(at)) {
			DECL_SPEC acc = DEREF_dspec(inst_templ_access(at));
			if (!(acc & (dspec_alias | dspec_main))) {
				/* NOT YET IMPLEMENTED */
			}
			at = DEREF_inst(inst_next(at));
		}
		COPY_inst(tok_templ_apps(ps), as);
	}
	return;
}


/*
    This routine copies the nested class or enumeration type tid of a
    template class.
*/

static IDENTIFIER
copy_nested(IDENTIFIER tid, TYPE t, TYPE q, LOCATION *ploc)
{
	IDENTIFIER id = tid;
	switch (TAG_type(t)) {
	case type_compound_tag: {
		/* Non-template classes */
		TYPE s;
		TYPE form;
		int def = 0;
		DECL_SPEC ds;
		CLASS_TYPE cs;
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		BASE_TYPE key = find_class_key(ct);
		IDENTIFIER cid = DEREF_id(ctype_name(ct));
		HASHID nm = DEREF_hashid(id_name(cid));
		NAMESPACE ns = crt_namespace;

		/* Declare class */
		if (!IS_id_class_name(tid)) {
			break;
		}
		if (ci & cinfo_complete) {
			def = 1;
		}
		id = declare_type(ns, nm, key, q, def, 1);
		s = DEREF_type(id_class_name_defn(id));
		while (IS_type_templ(s)) {
			s = DEREF_type(type_templ_defn(s));
		}
		cs = DEREF_ctype(type_compound_defn(s));
		ds = DEREF_dspec(id_storage(id));
		ds |= dspec_instance;
		COPY_dspec(id_storage(id), ds);

		/* Set up instance type */
		MAKE_type_instance(cv_none, tid, dspec_none, form);
		COPY_id(type_name(form), id);
		COPY_type(ctype_form(cs), form);
		if (do_dump) {
			dump_declare(id, ploc, 0);
		}
		/* complete_class ( cs, 1 ) ; */
		break;
	}
	case type_enumerate_tag: {
		/* Enumeration type */
		TYPE form;
		DECL_SPEC ds;
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		CLASS_INFO ei = DEREF_cinfo(etype_info(et));
		TYPE s = DEREF_type(etype_rep(et));
		IDENTIFIER eid = DEREF_id(etype_name(et));
		HASHID nm = DEREF_hashid(id_name(eid));
		NAMESPACE ns = crt_namespace;

		/* Declare enumeration */
		if (!IS_id_enum_name(tid)) {
			break;
		}
		id = declare_type(ns, nm, btype_enum, NULL_type, 1, 1);
		ds = DEREF_dspec(id_storage(id));
		ds |= dspec_instance;
		COPY_dspec(id_storage(id), ds);
		t = DEREF_type(id_enum_name_defn(id));
		et = DEREF_etype(type_enumerate_defn(t));
		COPY_cinfo(etype_info(et), ei);
		s = expand_type(s, 1);
		COPY_type(etype_rep(et), s);

		/* Set up instance type */
		MAKE_type_instance(cv_none, tid, dspec_none, form);
		COPY_id(type_name(form), id);
		COPY_type(etype_form(et), form);
		if (do_dump) {
			dump_declare(id, ploc, 0);
		}
		break;
	}
	case type_templ_tag: {
		/* Template classes */
		TYPE s;
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		sort = expand_templ_sort(sort, 1);
		MAKE_type_templ(cv_none, sort, NULL_type, 0, s);
		q = inject_pre_type(q, s, 0);
		t = DEREF_type(type_templ_defn(t));
		id = copy_nested(tid, t, q, ploc);
		reset_templ_sort(sort);
		copy_specs(id, tid, 1);
		break;
	}
	}
	return id;
}


/*
    This routine copies the class member id to the namespace ns, renaming
    it to nm.
*/

static IDENTIFIER
copy_member(IDENTIFIER id, HASHID nm, NAMESPACE ns, CLASS_TYPE ct,
	    LOCATION *ploc)
{
	TYPE form;
	IDENTIFIER tid = NULL_id;
	unsigned tag = TAG_id(id);

	/* Check for implicit and inherited members */
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (ds & (dspec_inherit | dspec_implicit)) {
		/* Ignore implicit or inherited members */
		if ((ds & dspec_alias) && (ds & dspec_inherit)) {
			GRAPH gr;
			tid = DEREF_id(id_alias(id));
			tid = rescan_member(tid);
			gr = is_subfield(ns, tid);
			if (!IS_NULL_graph(gr)) {
				DECL_SPEC acc = crt_access;
				crt_access = (ds & dspec_access);
				tid = search_subfield(ns, gr, tid);
				tid = alias_id(tid, ns, NULL_id, 0);
				if (TAG_id(tid) != tag) {
					tid = NULL_id;
				}
				crt_access = acc;
			} else {
				report(crt_loc,
				       ERR_dcl_nspace_udecl_base(tid, ct));
				tid = NULL_id;
			}
		}
		if (tag == id_mem_func_tag || tag == id_stat_mem_func_tag) {
			IDENTIFIER fid = DEREF_id(id_function_etc_over(id));
			if (!IS_NULL_id(fid)) {
				/* Deal with overloaded functions */
				DEREF_loc(id_loc(fid), crt_loc);
				fid = copy_member(fid, nm, ns, ct, ploc);
				if (!IS_NULL_id(tid)) {
					COPY_id(id_function_etc_over(tid), fid);
					if (!IS_NULL_id(fid)) {
						tid = hide_functions(tid, fid,
								     1);
					}
				} else {
					tid = fid;
				}
			}
		}
		return tid;
	}

	/* Nested classes and enumerations already copied */
	if (tag == id_class_name_tag || tag == id_enum_name_tag) {
		return NULL_id;
	}

	/* Copy member */
	tid = copy_id(id, 2);
	if (!EQ_id(tid, id)) {
		int def = 0;
		int virt = 0;
		int templ = 0;
		IDENTIFIER fid = NULL_id;
		CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
		ds = DEREF_dspec(id_storage(tid));
		COPY_nspace(id_parent(tid), ns);
		COPY_hashid(id_name(tid), nm);
		switch (tag) {
		case id_member_tag: {
			/* Non-static data members */
			OFFSET off;
			DECL_SPEC acc = (ds & dspec_access);
			TYPE t = DEREF_type(id_member_type(tid));
			MAKE_off_member(tid, off);
			COPY_off(id_member_off(tid), off);
			check_mem_decl(ds, t, tid);
			ci = check_member_type(ct, ci, t, 0);
			if (acc != dspec_public) {
				ci |= cinfo_private;
			}
			def = 1;
			break;
		}
		case id_stat_member_tag: {
			/* Static data members */
			EXP dummy;
			TYPE t = DEREF_type(id_stat_member_type(tid));
			check_mem_decl(ds, t, tid);
			MAKE_type_instance(cv_none, id, dspec_none, form);
			COPY_id(type_name(form), tid);
			MAKE_exp_paren(form, NULL_exp, dummy);
			COPY_exp(id_stat_member_init(tid), NULL_exp);
			COPY_exp(id_stat_member_term(tid), dummy);
			ci |= cinfo_static;
			ds &= ~dspec_defn;
			break;
		}
#if LANGUAGE_CPP
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Member functions */
			LIST(VIRTUAL)vt;
			IDENTIFIER hide_id = NULL_id;
			unsigned ntag = TAG_hashid(nm);
			TYPE t = DEREF_type(id_function_etc_type(tid));
			fid = DEREF_id(id_function_etc_over(id));
			if (!IS_NULL_id(fid)) {
				/* Deal with overloaded functions */
				DEREF_loc(id_loc(fid), crt_loc);
				fid = copy_member(fid, nm, ns, ct, ploc);
				COPY_id(id_function_etc_over(tid), fid);
				DEREF_loc(id_loc(tid), crt_loc);
			}
			if (ntag == hashid_op_tag) {
				/* Check operator type */
				int alloc = 0;
				t = check_operator(t, tid, 1, &alloc);
				if (alloc) {
					recheck_allocator(tid, alloc);
				}
			}
			decl_func_type(tid, t, 0);
			special_func_mem(ct, tid, ntag, NULL_id);
			vt = overrides_virtual(ct, nm, t, &hide_id);
			if (!IS_NULL_list(vt)) {
				/* Check for overriding virtual functions */
				if (!(ds & dspec_virtual)) {
					ERROR err =
					    ERR_class_virtual_override(nm);
					if (!IS_NULL_err(err)) {
						report(crt_loc, err);
					}
				}
				ds |= dspec_virtual;
			}
			if (ds & dspec_virtual) {
				/* Deal with virtual functions */
				add_virtual(ct, tid, vt);
				ci |= cinfo_polymorphic;
				if (!(ds & dspec_pure)) {
					virt = 1;
				}
			}
			MAKE_type_instance(cv_none, id, dspec_none, form);
			COPY_id(type_name(form), tid);
			COPY_type(id_function_etc_form(tid), form);
			COPY_exp(id_function_etc_defn(tid), NULL_exp);
			if (IS_type_templ(t)) {
				templ = 1;
			}
			ci |= cinfo_function;
			ds &= ~dspec_defn;
			break;
		}
#endif
		case id_enumerator_tag: {
			/* Enumerators */
			TYPE t = DEREF_type(id_enumerator_etype(tid));
			if (IS_type_enumerate(t)) {
				/* Maintain list of enumerators */
				LIST(IDENTIFIER)p, q;
				ENUM_TYPE et =
				    DEREF_etype(type_enumerate_defn(t));
				p = DEREF_list(etype_values(et));
				CONS_id(tid, NULL_list(IDENTIFIER), q);
				p = APPEND_list(p, q);
				COPY_list(etype_values(et), p);
			}
			break;
		}
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag: {
			/* Typedefs */
			LIST(IDENTIFIER)ft = DEREF_list(ctype_nest(ct));
			CONS_id(tid, ft, ft);
			COPY_list(ctype_nest(ct), ft);
			break;
		}
		}
		ds &= ~(dspec_used | dspec_called | dspec_done);
		ds |= dspec_instance;
		COPY_dspec(id_storage(tid), ds);
		COPY_cinfo(ctype_info(ct), ci);
		if (do_dump) {
			dump_declare(tid, ploc, def);
		}
		if (templ) {
			copy_specs(tid, id, 0);
		}
		if (virt) {
			define_template(tid, 0);
		}
		if (!IS_NULL_id(fid)) {
			/* Check overloaded functions */
			tid = hide_functions(tid, fid, 1);
		}
	}
	return tid;
}


/*
    This routine copies the friend class id of a template class.  This may
    involve name injection.
*/

static IDENTIFIER
copy_friend_class(IDENTIFIER id)
{
	TYPE t = DEREF_type(id_class_name_etc_defn(id));
	TYPE s = expand_type(t, 1);
	t = s;
	while (IS_type_templ(s)) {
		s = DEREF_type(type_templ_defn(s));
	}
	if (IS_type_compound(s)) {
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
		TYPE form = DEREF_type(ctype_form(cs));
		id = DEREF_id(ctype_name(cs));
		if (IS_NULL_type(form)) {
			/* Allow for name injection */
			HASHID nm = DEREF_hashid(id_name(id));
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			MEMBER mem = search_member(ns, nm, 1);
			TYPE q = extract_templ_qual(t);
			BASE_TYPE key = find_key(id, 1, btype_none);
			IDENTIFIER tid = declare_type(ns, nm, key, q, 0, 0);
			IGNORE inject_pre_type(q, t, 0);
			if (!IS_NULL_id(tid) && IS_id_class_name(tid)) {
				/* Allow for redeclarations */
				if (!EQ_id(tid, id)) {
					IDENTIFIER pid =
					    DEREF_id(id_alias(tid));
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(id));
					ds |= dspec_alias;
					COPY_dspec(id_storage(id), ds);
					COPY_id(id_alias(id), pid);
					t = DEREF_type(id_class_name_defn(tid));
					COPY_type(ctype_form(cs), t);
					id = tid;
				}
			}
			if (!in_template_decl) {
				set_type_member(mem, id);
			}
		}
	}
	return id;
}


/*
    This routine copies the friend function id of a template class.  This
    may involve name injection.
*/

static IDENTIFIER
copy_friend_func(IDENTIFIER id)
{
	TYPE form;
	MEMBER mem;
	DECL_SPEC ds;
	IDENTIFIER fid;
	int changed = 0;
	IDENTIFIER over = NULL_id;
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	HASHID nm1 = expand_name(nm, NULL_ctype);
	NAMESPACE ns1 = rescan_nspace(ns);
	TYPE t = DEREF_type(id_function_etc_type(id));
	if (!IS_type_templ(t)) {
		TYPE t1 = expand_type(t, 1);
		if (!EQ_type(t1, t)) {
			changed = 1;
			t = t1;
		}
	}
	if (!EQ_hashid(nm1, nm)) {
		changed = 1;
		nm = nm1;
	}
	if (!EQ_nspace(ns1, ns)) {
		changed = 1;
		ns = ns1;
	}
	if (changed) {
		/* Copy identifier if necessary */
		id = copy_id(id, 2);
		COPY_nspace(id_parent(id), ns);
		COPY_hashid(id_name(id), nm);
	}

	/* Check for template functions */
	form = DEREF_type(id_function_etc_form(id));
	if (!IS_NULL_type(form) && IS_type_token(form)) {
		IDENTIFIER tid = DEREF_id(type_token_tok(form));
		if (IS_id_function_etc(tid)) {
			/* Template function instance */
			TYPE t1 = DEREF_type(id_function_etc_type(tid));
			t = injected_type(t, 1);
			if (eq_type(t1, t) == 1) {
				/* Allow for redeclarations */
				id = tid;
			} else {
				LIST(TOKEN)args;
				args = DEREF_list(type_token_args(form));
				tid = copy_friend_func(tid);
				if (do_dump) {
					dump_declare(tid, &crt_loc, 0);
				}
				args = expand_args(args, 1, 1);
				id = instance_func(tid, args, 0, 0);
				return id;
			}
		}
	}

	/* Look up matching declaration */
	ds = DEREF_dspec(id_storage(id));
	mem = search_member(ns, nm, 1);
	fid = DEREF_id(member_id(mem));
	if (!IS_NULL_id(fid)) {
		unsigned tag = TAG_id(id);
		DECL_SPEC cl = crt_linkage;
		QUALIFIER cq = crt_id_qualifier;
		crt_id_qualifier = qual_nested;
		crt_linkage = (ds & dspec_language);
		ds &= ~dspec_alias;
		fid = redecl_func(ds, t, fid, tag, &over, -2);
		crt_id_qualifier = cq;
		crt_linkage = cl;
	}
	if (IS_NULL_id(fid)) {
		/* Allow for name injection */
		if (IS_nspace_ctype(ns)) {
			report(crt_loc, ERR_basic_link_unmatch(t, id));
		} else {
			COPY_id(id_function_etc_over(id), over);
			COPY_exp(id_function_etc_defn(id), NULL_exp);
			if (!in_template_decl) {
				set_member(mem, id);
			}
		}
	} else {
		/* Set up function alias */
		if (!EQ_id(fid, id)) {
			IDENTIFIER pid = DEREF_id(id_alias(fid));
			ds |= dspec_alias;
			COPY_dspec(id_storage(id), ds);
			COPY_id(id_alias(id), pid);
			id = fid;
		}
	}
	return id;
}


/*
    This routine copies the members of the class cs to the class ct.
    Note that this is done only if cs has been completely defined,
    partially defined classes are not copied.
*/

void
copy_members(CLASS_TYPE ct, CLASS_TYPE cs, CLASS_INFO ci, int def)
{
	CLASS_INFO ck = DEREF_cinfo(ctype_info(cs));
	CLASS_INFO cj = DEREF_cinfo(ctype_info(ct));
	if (!(ck & cinfo_complete)) {
		def = 0;
	}
	if (ck & cinfo_recursive) {
		cj |= cinfo_recursive;
	}
	cj |= ci;
	COPY_cinfo(ctype_info(ct), cj);
	if (def && !(cj & cinfo_defined)) {
		int ic;
		GRAPH gr;
		MEMBER mem;
		DECL_SPEC ds;
		LOCATION loc;
		IDENTIFIER cid;
		DECL_SPEC pacc;
		ACCESS_LIST accs;
		LIST(GRAPH)br;
		LIST(IDENTIFIER)fr;
		LIST(CLASS_TYPE)fc;
		int lex = crt_lex_token;
		int fn = in_function_defn;
		int rfn = really_in_function_defn;
		NAMESPACE nt = DEREF_nspace(ctype_member(ct));
		NAMESPACE ns = DEREF_nspace(ctype_member(cs));

		/* Save class information */
		loc = crt_loc;
		bad_crt_loc++;
		ic = in_class_defn;
		push_class(ct);
		push_namespace(nt);
		in_class_defn = 1;
		in_function_defn = 0;
		really_in_class_defn++;
		really_in_function_defn = 0;
		crt_lex_token = lex_ignore_token;
		save_access(&accs);
		cid = DEREF_id(ctype_name(ct));
		DEREF_loc(id_loc(cid), crt_loc);
		ds = DEREF_dspec(id_storage(cid));
		ds |= dspec_defn;
		COPY_dspec(id_storage(cid), ds);
		cj |= (cinfo_complete | cinfo_defined);
		COPY_cinfo(ctype_info(ct), cj);
		if (do_dump) {
			dump_declare(cid, &loc, 1);
		}

		/* Copy base classes */
		pacc = prev_access;
		gr = DEREF_graph(ctype_base(cs));
		br = DEREF_list(graph_tails(gr));
		while (!IS_NULL_list(br)) {
			int virt = 0;
			GRAPH gu = DEREF_graph(HEAD_list(br));
			CLASS_TYPE cu = DEREF_ctype(graph_head(gu));
			DECL_SPEC acc = DEREF_dspec(graph_access(gu));
			cid = DEREF_id(ctype_name(cu));
			if (acc & dspec_virtual) {
				virt = 1;
			}
			acc &= dspec_access;
			add_base_class(cid, acc, virt);
			br = TAIL_list(br);
		}
		end_base_class(ct, 1);
		prev_access = pacc;

		/* Copy nested classes */
		fr = DEREF_list(ctype_nest(cs));
		while (!IS_NULL_list(fr)) {
			IDENTIFIER fid = DEREF_id(HEAD_list(fr));
			if (IS_id_class_name_etc(fid)) {
				DECL_SPEC fds = DEREF_dspec(id_storage(fid));
				if (!(fds & dspec_instance)) {
					TYPE f;
					DEREF_loc(id_loc(fid), crt_loc);
					pacc = crt_access;
					crt_access = (fds & dspec_access);
					f = DEREF_type(id_class_name_etc_defn(fid));
					IGNORE copy_nested(fid, f, NULL_type, &loc);
					crt_access = pacc;
				}
			}
			fr = TAIL_list(fr);
		}

		/* Copy class members */
		mem = DEREF_member(nspace_ctype_first(ns));
		while (!IS_NULL_member(mem)) {
			HASHID tnm = NULL_hashid;
			MEMBER tmem = NULL_member;
			IDENTIFIER id = DEREF_id(member_id(mem));
			IDENTIFIER alt = DEREF_id(member_alt(mem));
			if (!IS_NULL_id(id)) {
				IDENTIFIER tid;
				HASHID nm = DEREF_hashid(id_name(id));
				DEREF_loc(id_loc(id), crt_loc);
				tnm = expand_name(nm, ct);
				tmem = search_member(nt, tnm, 1);
				tid = copy_member(id, tnm, nt, ct, &loc);
				if (!IS_NULL_id(tid)) {
					set_member(tmem, tid);
				}
			}
			if (!IS_NULL_id(alt) && !EQ_id(id, alt)) {
				IDENTIFIER talt;
				DEREF_loc(id_loc(alt), crt_loc);
				if (IS_NULL_member(tmem)) {
					HASHID nm = DEREF_hashid(id_name(alt));
					tnm = expand_name(nm, ct);
					tmem = search_member(nt, tnm, 1);
				}
				talt = copy_member(alt, tnm, nt, ct, &loc);
				if (!IS_NULL_id(talt)) {
					set_type_member(tmem, talt);
				}
			}
			mem = DEREF_member(member_next(mem));
		}

		/* Copy chums */
		fc = DEREF_list(ctype_chums(cs));
		while (!IS_NULL_list(fc)) {
			TYPE r = NULL_type;
			CLASS_TYPE cr = DEREF_ctype(HEAD_list(fc));
			cr = expand_ctype(cr, 2, &r);
			friend_class(cr, cid, 0);
			fc = TAIL_list(fc);
		}

		/* Copy pals */
		fr = DEREF_list(ctype_pals(cs));
		if (!IS_NULL_list(fr)) {
			while (!IS_NULL_list(fr)) {
				IDENTIFIER fid = DEREF_id(HEAD_list(fr));
				DEREF_loc(id_loc(fid), decl_loc);
				DEREF_loc(id_loc(fid), crt_loc);
				if (IS_id_class_name(fid)) {
					fid = copy_friend_class(fid);
					friend_class(ct, fid, 0);
				} else {
					EXP e = DEREF_exp(id_function_etc_defn(fid));
					fid = copy_friend_func(fid);
					friend_function(ct, fid, 0);
					if (!IS_NULL_exp(e) &&
					    !IS_exp_value(e)) {
						copy_object(fid, e);
					}
				}
				if (do_dump) {
					dump_declare(fid, &crt_loc, 0);
				}
				fr = TAIL_list(fr);
			}
			fr = DEREF_list(ctype_pals(ct));
			fr = REVERSE_list(fr);
			COPY_list(ctype_pals(ct), fr);
		}

		/* Update class information */
		cj = DEREF_cinfo(ctype_info(ct));
#if LANGUAGE_CPP
		cj = implicit_decl(ct, cj, dspec_instance);
#endif
		if (cj & cinfo_non_aggregate) {
			/* POD classes must be aggregate classes */
			cj &= ~cinfo_pod;
		}
		cj |= cinfo_complete;
		COPY_cinfo(ctype_info(ct), cj);
		inherit_class();
		IGNORE restore_access(cid, &accs);
		in_class_defn = ic;
		really_in_class_defn--;
		really_in_function_defn = rfn;
		in_function_defn = fn;
		crt_lex_token = lex;
		IGNORE pop_namespace();
		pop_class();
		decl_loc = loc;
		crt_loc = loc;
		bad_crt_loc--;
	}
	return;
}
