/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include "config.h"
#include "c_types.h"

#include "ctype_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "loc_ext.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "basetype.h"
#include "capsule.h"
#include "chktype.h"
#include "class.h"
#include "compile.h"
#include "construct.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "exception.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "inttype.h"
#include "namespace.h"
#include "operator.h"
#include "overload.h"
#include "predict.h"
#include "preproc.h"
#include "redeclare.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "virtual.h"


/*
    This variable is used to record the location of the current declaration.
    This is primarily so that the location of a declaration can be set to
    the location of the declarator rather than the end of the corresponding
    initialiser.
*/

LOCATION decl_loc = NULL_loc;
int is_redeclared = 0;


/*
    These variables give the default linkages for inline functions and
    const objects and the default cv-qualifiers for external objects.
*/

DECL_SPEC inline_linkage = dspec_static;
DECL_SPEC const_linkage = dspec_static;
CV_SPEC cv_extern = cv_none;


/*
    The value dspec_empty is used during the processing of declarations
    to mark any declaration specifier which does not contain an explicit
    specifier.  The value dspec_nonempty gives those declaration
    specifiers which constitute an explicit specifier.
*/

#define dspec_empty		dspec_pure
#define dspec_nonempty		dspec_keyword


/*
    This routine completes the declaration specifier given by the
    specifiers ds, the type t and the cv-qualifier cv.  If these are
    all empty then the result is marked using dspec_empty.  The special
    case 'extern "LANG" typedef' is checked.
*/

DECL_SPEC
complete_dspec(DECL_SPEC ds, BASE_TYPE bt, TYPE t, CV_SPEC cv)
{
	DECL_SPEC key = (ds & dspec_nonempty);
	if (key || bt || !IS_NULL_type(t) || cv) {
		/* Have a declaration specifier */
		if (ds & dspec_c) {
			/* Have a linkage specification */
			if (ds & dspec_typedef) {
				ds &= ~dspec_extern;
			}
			ds &= ~dspec_c;
		}
	} else {
		ds |= dspec_empty;
	}
	return ds;
}


/*
    This routine checks the declaration specifiers ds and the type *p for
    inferred types and empty specifier lists.  It is used in object,
    parameter and class member declarations.
*/

static DECL_SPEC
check_inferred_type(DECL_SPEC ds, TYPE *p, int mem)
{
	int infer;
	TYPE t = *p;
	int empty = 0;
	ERROR err = NULL_err;

	/* Report if there are no declaration specifiers */
	if (ds & dspec_empty) {
		if (mem) {
			err = ERR_class_mem_ds_empty();
		} else {
			err = ERR_dcl_dcl_ds_empty();
		}
		ds &= ~dspec_empty;
		empty = 1;
	}

	/* Check on inferred types */
	infer = is_type_inferred(t);
	if (infer != INFERRED_NOT) {
		ERROR err2;
		t = clean_inferred_type(t);
		if (empty) {
			err2 = ERR_dcl_type_infer(t);
		} else {
			err2 = report_inferred_type(t, infer);
		}
		err = concat_error(err, err2);
		*p = t;
	}
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}
	return ds;
}


/*
    This routine checks the declaration specifiers ds and the function
    type t for inferred types and empty specifier lists.  It is used in
    function declarations and definitions (as indicated by def).
*/

static DECL_SPEC
check_func_type(DECL_SPEC ds, TYPE t, int def, int chk, int mem)
{
	int empty = 0;
	ERROR err = NULL_err;

	/* Report if there are no declaration specifiers */
	if (ds & dspec_empty) {
		if (mem) {
			err = ERR_class_mem_ds_empty();
		} else if (def) {
			err = ERR_dcl_dcl_ds_func();
		} else {
			err = ERR_dcl_dcl_ds_empty();
		}
		ds &= ~dspec_empty;
		empty = 1;
	}

	/* Check for template types */
	while (IS_type_templ(t)) {
		ds |= dspec_template;
		t = DEREF_type(type_templ_defn(t));
	}

	/* Check the return type */
	if (chk) {
		TYPE r = DEREF_type(type_func_ret(t));
		int infer = is_type_inferred(r);
		if (infer != INFERRED_NOT) {
			ERROR err2;
			r = clean_inferred_type(r);
			if (empty) {
				err2 = ERR_dcl_type_infer(r);
			} else {
				err2 = report_inferred_type(r, infer);
			}
			err = concat_error(err, err2);
			COPY_type(type_func_ret(t), r);
		}
	}
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}
	return ds;
}


/*
    This macro is used to shift a storage class specifier into a more
    sensible range.
*/

#define DSPEC_STORAGE(A)	((A) >> 6)


/*
    This routine extracts the storage class specifiers from the declaration
    specifiers ds in the context given by loc.  It returns a valid storage
    class specifier.
*/

static DECL_SPEC
check_storage(DECL_SPEC ds, int loc, IDENTIFIER id)
{
	DECL_SPEC st = (ds & dspec_storage);

	/* Check on storage class */
switch_label:
	switch (DSPEC_STORAGE(st)) {
	case DSPEC_STORAGE(dspec_none): {
		/* No storage class given */
		break;
	}
	case DSPEC_STORAGE(dspec_auto):
	case DSPEC_STORAGE(dspec_register): {
		/* Deal with auto and register */
		switch (loc) {
		case CONTEXT_OBJECT: {
			/* Objects declared in a block are alright */
			if (!in_function_defn) {
				goto bad_auto_lab;
			}
			break;
		}
		case CONTEXT_FUNCTION: {
			/* Functions can't be auto */
			if (!in_function_defn) {
				goto bad_auto_lab;
			}
			report(crt_loc, ERR_dcl_stc_auto_func(st));
			st = dspec_none;
			break;
		}
		case CONTEXT_PARAMETER:
		case CONTEXT_WEAK_PARAM: {
			/* Function parameters are alright */
			if (st == dspec_auto) {
				/* Can't have auto parameters in C */
				report(crt_loc, ERR_dcl_stc_auto_par());
			}
			break;
		}
		case CONTEXT_TEMPL_PARAM: {
			/* Template parameters can't have storage class */
			report(crt_loc, ERR_temp_param_dcl_stc(st));
			st = dspec_none;
			break;
		}
		default:
bad_auto_lab:
			/* Anything outside a block can't be auto */
			report(crt_loc, ERR_dcl_stc_auto_bad(st));
			st = dspec_none;
			break;
		}
		break;
	}
	case DSPEC_STORAGE(dspec_static): {
		/* Deal with static */
		switch (loc) {
		case CONTEXT_PARAMETER:
		case CONTEXT_WEAK_PARAM: {
			/* Function parameters can't be static */
			report(crt_loc, ERR_dcl_stc_param(st));
			st = dspec_none;
			break;
		}
		case CONTEXT_TEMPL_PARAM: {
			/* Template parameters can't have storage class */
			report(crt_loc, ERR_temp_param_dcl_stc(st));
			st = dspec_none;
			break;
		}
		}
		break;
	}
	case DSPEC_STORAGE(dspec_extern): {
		/* Deal with extern */
		switch (loc) {
		case CONTEXT_OBJECT:
		case CONTEXT_FUNCTION: {
			/* Objects and functions can be extern */
			if (!IS_NULL_id(id)) {
				switch (TAG_id(id)) {
				case id_member_tag:
				case id_mem_func_tag:
				case id_stat_member_tag:
				case id_stat_mem_func_tag: {
					/* But not class members */
					ERROR err = ERR_dcl_stc_ext_mem();
					report(crt_loc, err);
					break;
				}
				}
			}
			break;
		}
		case CONTEXT_PARAMETER:
		case CONTEXT_WEAK_PARAM: {
			/* Function parameters can't be extern */
			report(crt_loc, ERR_dcl_stc_param(st));
			st = dspec_none;
			break;
		}
		case CONTEXT_TEMPL_PARAM: {
			/* Template parameters can't have storage class */
			report(crt_loc, ERR_temp_param_dcl_stc(st));
			st = dspec_none;
			break;
		}
		default:
			/* Class members can't be extern */
			report(crt_loc, ERR_dcl_stc_ext_mem());
			st = dspec_none;
			break;
		}
		break;
	}
	case DSPEC_STORAGE(dspec_mutable): {
		/* Deal with mutable */
		if (loc != CONTEXT_MEMBER) {
			/* Only data members can be mutable */
			report(crt_loc, ERR_dcl_stc_mut_bad());
			st = dspec_none;
		}
		break;
	}
	default: {
		/* More than one storage class - select one */
		DECL_SPEC nst = dspec_static;
		while (!(st & nst)) {
			assert(nst != dspec_none);
			nst <<= 1;
		}
		report(crt_loc, ERR_dcl_stc_dup(st, nst));
		st = nst;
		goto switch_label;
	}
	}
	return st;
}


/*
    This routine extracts the function specifiers (plus friend specifiers)
    from the declaration specifiers ds in the context given by loc (as
    above).  It returns a valid combination of function and friend
    specifiers.
*/

static DECL_SPEC
check_func_spec(DECL_SPEC ds, int loc)
{
	DECL_SPEC fn = dspec_none;

	/* Only functions can be inline */
	if (ds & dspec_inline) {
		if (loc == CONTEXT_FUNCTION || loc == CONTEXT_FUNC_MEMBER) {
			fn |= dspec_inline;
		} else {
			report(crt_loc, ERR_dcl_fct_spec_inline_bad());
		}
	}

	/* Only function members can be virtual */
	if (ds & dspec_virtual) {
		if (loc == CONTEXT_FUNC_MEMBER) {
			fn |= dspec_virtual;
		} else {
			report(crt_loc, ERR_dcl_fct_spec_virtual());
		}
	}

	/* Only function members can be explicit */
	if (ds & dspec_explicit) {
		if (loc == CONTEXT_FUNC_MEMBER) {
			fn |= dspec_explicit;
		} else {
			report(crt_loc, ERR_dcl_fct_spec_explicit());
		}
	}

	/* Only functions declared in a class can be friends */
	if (ds & dspec_friend) {
		if (loc == CONTEXT_FUNCTION && in_class_defn) {
			/* Don't add to specifier list */
			/* EMPTY */
		} else if (in_class_defn) {
			report(crt_loc, ERR_class_friend_decl());
		} else {
			report(crt_loc, ERR_dcl_friend_class());
		}
	}

	/* Allow for function discarding */
	if (loc == CONTEXT_FUNCTION || loc == CONTEXT_FUNC_MEMBER) {
		fn |= dspec_ignore;
	}
	return fn;
}


/*
    This routine constructs the declaration of a type with declaration
    specifiers ds (which will include typedef), type t and name id in the
    namespace ns.  mem gives the member of ns corresponding to id or the
    null member for class member redeclarations.
*/

static IDENTIFIER
make_type_decl(NAMESPACE ns, DECL_SPEC ds, TYPE t, MEMBER mem, IDENTIFIER id)
{
	int reported = 0;
	IDENTIFIER old_id;
	unsigned tag = TAG_type(t);
	QUALIFIER cq = crt_id_qualifier;
	HASHID nm = DEREF_hashid(id_name(id));

	/* Can't have other declaration specifiers with typedef */
	DECL_SPEC st = (ds & dspec_keyword);
	if (st != dspec_typedef) {
		st &= ~dspec_typedef;
		report(crt_loc, ERR_dcl_typedef_dspec(st));
	}

	/* Check for function cv-qualifiers and exception specifiers */
	object_type(t, id_type_alias_tag);

	/* Check for previous declaration */
	if (IS_NULL_member(mem)) {
		mem = search_member(ns, nm, 1);
		old_id = DEREF_id(member_id(mem));
		old_id = redecl_inherit(old_id, cq, in_class_defn, 2);
		if (IS_NULL_id(old_id)) {
			report(crt_loc, ERR_lookup_qual_undef(nm, ns));
		}
	} else {
		old_id = DEREF_id(member_id(mem));
		old_id = redecl_inherit(old_id, cq, in_class_defn, 2);
	}

	/* Allow for type redeclarations */
#if LANGUAGE_CPP
	id = type_member(mem, 3);
	id = redecl_inherit(id, cq, in_class_defn, 2);
#else
	id = old_id;
#endif
	if (!IS_NULL_id(id) && IS_id_class_name_etc(id)) {
		/* Already declared as a type name */
		TYPE s;
		ERROR err = NULL_err;
		PTR(LOCATION)loc = id_loc(id);
		unsigned long tokdefs = no_token_defns;

		/* Check for reserved identifiers */
		DECL_SPEC ods = DEREF_dspec(id_storage(id));
		if ((ds | ods) & dspec_reserve) {
			report(crt_loc, ERR_basic_odr_decl(id, loc));
			return id;
		}

		/* Check type compatibility */
		s = DEREF_type(id_class_name_etc_defn(id));
		s = check_compatible(s, t, 0, &err, 1);
		/* QUERY: or is type equality required? */

		/* Compatible redefinition */
		if (IS_NULL_err(err)) {
			NAMESPACE cns = crt_namespace;
			if (cq != qual_none) {
				/* Check qualified definitions */
				check_decl_nspace(id, ns, 1, cns);
			}
			if (in_class_defn && EQ_nspace(ns, cns)) {
				if (!is_tagged_type(id)) {
					/* Still not allowed in a class
					 * definition */
					report(crt_loc,
					       ERR_class_mem_redecl(id, loc));
				}
			} else if (tokdefs == no_token_defns &&
				   !in_pragma_dir) {
				/* Can't redeclare types in C */
				report(crt_loc, ERR_basic_odr_typedef(id, loc));
			}
			if (tag == type_func_tag) {
				/* Check function types */
				s = redecl_func_type(id, s, t, 0, 1);
			}
			COPY_type(id_class_name_etc_defn(id), s);
			adjust_access(id, crt_access, 0);
			return id;
		}

		/* Incompatible redefinition */
		err = concat_error(err, ERR_basic_link_typedef(id, loc));
		report(crt_loc, err);
		reported = 1;
	}

	/* Declare the type */
	id = make_typedef(ns, nm, t, dspec_none);
	if (is_tagged_type(id)) {
		/* Class-like typedef-names */
		set_type_member(mem, id);
	} else {
		/* Object-like typedef-names */
		if (!IS_NULL_id(old_id) && !reported) {
			/* Already declared as an object */
			PTR(LOCATION)loc = id_loc(old_id);
			report(crt_loc, ERR_basic_odr_diff(old_id, loc));
		}
		set_member(mem, id);
	}
	if (tag == type_func_tag) {
		/* Check function type */
		decl_func_type(id, t, 0);
	} else if (tag == type_templ_tag) {
		IGNORE check_templ_params(t, id);
		report(crt_loc, ERR_temp_decl_bad());
	}
	return id;
}


/*
    This routine creates a typedef of the identifier id to the special
    type t.
*/

void
typedef_special(IDENTIFIER id, TYPE t)
{
	int pushed = 0;
	NAMESPACE ns = nonblock_namespace;
	if (!EQ_nspace(ns, crt_namespace)) {
		push_namespace(ns);
		pushed = 1;
	}
	decl_loc = preproc_loc;
	if (in_class_defn) {
		id = make_member_decl(dspec_typedef, t, id, 0);
	} else {
		id = make_object_decl(dspec_typedef, t, id, 0);
	}
	if (do_dump) {
		dump_declare(id, &decl_loc, 1);
	}
	if (pushed) {
		IGNORE pop_namespace();
	}
	return;
}


/*
    This routine finds the linkage of the identifier id (including the
    language specifier), returning the default value st if id does not
    represent an object or function.
*/

static DECL_SPEC
find_storage(IDENTIFIER id, DECL_SPEC st, TYPE t)
{
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_variable_tag:
		case id_parameter_tag:
		case id_stat_member_tag:
		case id_weak_param_tag: {
			/* Objects */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			st = (ds & (dspec_storage | dspec_language));
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Functions */
			DECL_SPEC ds;
#if LANGUAGE_CPP
			LIST(IDENTIFIER)pids = NULL_list(IDENTIFIER);
			if (!IS_NULL_type(t)) {
				int eq = 0;
				id = resolve_func(id, t, 0, 0, pids, &eq);
				if (IS_NULL_id(id) ||
				    !IS_id_function_etc(id)) {
					return st;
				}
			}
#else
			UNUSED(t);
#endif
			ds = DEREF_dspec(id_storage(id));
			st = (ds & (dspec_storage | dspec_language));
			break;
		}
		}
	}
	return st;
}


/*
    This routine checks whether the namespace cns is a suitable location
    for redeclaring the object id, which is a member of the namespace ns.
    def is true for a definition.
*/

void
check_decl_nspace(IDENTIFIER id, NAMESPACE ns, int def, NAMESPACE cns)
{
	int func = 0;
	int local_def = really_in_function_defn;
	switch (TAG_id(id)) {
	case id_class_name_tag:
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Can define local types */
		local_def = 0;
		break;
	}
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Member function */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_implicit) {
			/* Ignore implicit constructors etc */
			return;
		}
		if (!def && !is_templ_nspace(ns)) {
			/* Can't even redeclare in this case */
			report(crt_loc, ERR_class_mfct_redecl(id));
			return;
		}
		func = 1;
		break;
	}
	case id_undef_tag: {
		/* Report undeclared members */
		HASHID nm = DEREF_hashid(id_name(id));
		report(crt_loc, ERR_lookup_qual_undef(nm, ns));
		return;
	}
	}

	if (def) {
		/* Check for enclosing namespace scope */
		if (local_def || !is_subnspace(cns, ns)) {
			/* Report badly placed definition */
			ERROR err;
			if (IS_nspace_ctype(ns)) {
				if (func) {
					/* Member functions */
					err = ERR_class_mfct_scope(id);
				} else {
					/* Other class members */
					err = ERR_class_static_data_scope(id);
				}
			} else {
				/* Namespace members */
				err = ERR_dcl_nspace_memdef_scope(id);
			}
			report(crt_loc, err);
		}
	}
	return;
}


/*
    This routine checks the type t for the object id with declaration
    specifiers ds.
*/

void
check_obj_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int tentative)
{
	unsigned tag = TAG_type(t);
	if (tag == type_top_tag || tag == type_bottom_tag) {
		/* Always report void declarations */
		report(crt_loc, ERR_basic_fund_void_decl(id, t));
	} else if (tag == type_templ_tag) {
		/* Shouldn't have template type */
		report(crt_loc, ERR_temp_decl_bad());
	} else if (ds & dspec_defn) {
		/* Only check otherwise if this is a definition */
		if (tag == type_array_tag) {
			/* Arrays may be completed by the initialiser */
			/* EMPTY */
		} else if (tag == type_ref_tag) {
			/* References don't need checking */
			/* EMPTY */
		} else {
			ERROR err;
			if (!tentative) {
				err = check_complete(t);
				if (!IS_NULL_err(err)) {
					/* Other definitions should have
					 * complete type */
					ERROR err2 =
					    ERR_basic_types_def_incompl(id);
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
			}
			err = check_abstract(t);
			if (!IS_NULL_err(err)) {
				/* Objects can't have abstract type */
				ERROR err2 = ERR_class_abstract_decl(id);
				err = concat_error(err, err2);
				report(crt_loc, err);
			}
		}
	}
	return;
}


/*
    This routine constructs the declaration of an object with declaration
    specifiers ds, type t and name id.
*/

IDENTIFIER
make_object_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int def)
{
	ERROR err;
	MEMBER mem;
	NAMESPACE ns;
	int redef = 0;
	int simple_id = 1;
	int tentative = 0;
	IDENTIFIER old_id;
	IDENTIFIER alt_id;
	DECL_SPEC st, df, rs;
	IDENTIFIER prev_id = NULL_id;
	unsigned tag = TAG_type(t);
	unsigned itag = id_variable_tag;
	HASHID nm = DEREF_hashid(id_name(id));

	/* Check for template specialisations */
	bound_specialise = 0;
	if (is_templ_decl(id, NULL_type) || is_templ_spec(t)) {
		t = bind_specialise(&id, t, ds, 0, 1, def);
		if (IS_NULL_id(id)) {
			/* Invalid specialisation */
			crt_id_qualifier = qual_none;
			crt_templ_qualifier = 0;
			id = DEREF_id(hashid_id(nm));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			id = make_object_decl(ds, t, id, def);
			return id;
		}
		ns = DEREF_nspace(id_parent(id));
		check_decl_nspace(id, ns, 0, crt_namespace);
		old_id = id;
		mem = NULL_member;
		simple_id = 0;
	} else {
		/* Check on identifier name */
		QUALIFIER cq = crt_id_qualifier;
		err = check_id_name(id, CONTEXT_OBJECT);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}

		/* Check for qualified identifiers */
		if (cq == qual_none) {
			/* Declaration of simple identifier */
			ns = crt_namespace;
			mem = search_member(ns, nm, 1);
			old_id = DEREF_id(member_id(mem));
			alt_id = DEREF_id(member_alt(mem));
			if (!IS_NULL_id(old_id)) {
				if (in_function_defn && (ds & dspec_extern)) {
					/* Redeclaration of block external */
					prev_id = find_previous(t, id);
					if (EQ_id(prev_id, old_id)) {
						old_id = NULL_id;
					}
				} else {
					old_id = redecl_inherit(old_id, cq, 0,
								2);
				}
				redef = 1;
			} else if (!IS_NULL_id(alt_id)) {
				redef = 1;
			}
		} else {
			/* Redeclaration of class or namespace member */
			ns = DEREF_nspace(id_parent(id));
			check_decl_nspace(id, ns, 0, crt_namespace);
			if (IS_id_undef(id)) {
				if (IS_nspace_ctype(ns)) {
					itag = id_stat_member_tag;
				}
				mem = search_member(ns, nm, 1);
				old_id = NULL_id;
			} else {
				mem = NULL_member;
				old_id = redecl_inherit(id, cq, 0, 2);
				t = bind_specialise(&old_id, t, ds, 0, 0, def);
				if (!IS_NULL_id(old_id)) {
					id = old_id;
					itag = TAG_id(id);
					ns = DEREF_nspace(id_parent(id));
				}
			}
			simple_id = 0;
		}
	}

	/* Deal with inferred types */
	ds = check_inferred_type(ds, &t, 0);

	/* Check on storage class specifiers */
	st = check_storage(ds, CONTEXT_OBJECT, old_id);

	/* Deal with type definitions */
	if (ds & dspec_typedef) {
		id = make_type_decl(ns, ds, t, mem, id);
		return id;
	}

	/* Check on function specifiers */
	IGNORE check_func_spec(ds, CONTEXT_OBJECT);

	/* Find the object linkage and whether it is a definition */
	if (st == dspec_extern) {
		/* Explicit extern indicates a declaration (probably) */
		df = dspec_none;
		if (in_function_defn && simple_id) {
			if (IS_NULL_id(prev_id)) {
				prev_id = find_previous(t, id);
			}
			st = find_storage(prev_id, st, NULL_type);
		} else {
			prev_id = old_id;
			st = find_storage(old_id, st, t);
		}
	} else {
		if (tag == type_templ_tag && bound_specialise) {
			/* A template specialisation is a declaration
			 * (probably) */
			df = dspec_none;
		} else {
			/* Everything else is a definition */
			df = dspec_defn;
		}
		if (in_function_defn) {
			/* Objects declared in a block have no linkage */
			if (IS_NULL_member(mem)) {
				/* Use old linkage if explicitly qualified */
				st = find_storage(old_id, dspec_none, t);
			} else if (st == dspec_static) {
				st = dspec_none;
			} else if (st == dspec_register) {
				st = (dspec_auto | dspec_register);
				used_register = 1;
			} else {
				st = dspec_auto;
			}
		} else if (st == dspec_static) {
			/* Check static declarations */
			if (!def) {
				tentative = LANGUAGE_C;
			}
		} else if (st == dspec_none) {
			/* Objects declared const have internal linkage */
			CV_SPEC qual = find_cv_qual(t);
			if (qual & cv_const) {
				st = const_linkage;
				if (st & dspec_static) {
					st = find_storage(old_id, st, t);
				}
			} else {
				st = dspec_extern;
			}
			/* find_storage is not applied for objects */
			if (!def) {
				tentative = LANGUAGE_C;
			}
		}
	}

	/* Create the declaration */
	t = lvalue_type(t);
	rs = (ds & dspec_other);
	ds = (st | df | rs);
	if (!IS_NULL_id(old_id)) {
		/* Check redeclarations */
		old_id = redecl_id(ds, t, old_id, 0, 0);
		if (IS_NULL_id(old_id) && IS_NULL_member(mem)) {
			/* Bad redeclaration of class or namespace member */
			nm = lookup_anon();
			mem = search_member(ns, nm, 1);
			itag = id_stat_member_tag;
		}
	}
	object_type(t, itag);
	if (IS_NULL_id(old_id)) {
		/* Construct the declaration */
		ds = adjust_linkage(ds, 0);
		MAKE_id_variable_etc(itag, nm, ds, ns, decl_loc, t, id);
		if (in_function_defn) {
			if (ds & dspec_linkage) {
				/* Block function declarations */
				id = unify_previous(id, t, prev_id, 0);
			} else if (redef && (ds & dspec_auto)) {
				/* Redeclarations of local variables */
				mem = update_member(ns, mem);
			}
		} else {
			id = unify_subsequent(id, t, 0);
		}
		set_member(mem, id);
		if (itag == id_variable_tag && option(OPT_decl_hide)) {
			check_hiding(id);
		}
		is_redeclared = 0;
	} else {
		/* Redeclare an existing object */
		id = old_id;
		if (IS_id_member(id)) {
			t = DEREF_type(id_member_type(id));
		} else {
			t = DEREF_type(id_variable_etc_type(id));
		}
		ds = DEREF_dspec(id_storage(id));
		is_redeclared = 1;
	}
#if LANGUAGE_CPP
	if (ds & dspec_c) {
		c_linkage(id, 0);
	}
#endif
	check_obj_decl(ds, t, id, tentative);
	return id;
}


/*
    This routine constructs a function declaration for a function with
    declaration specifiers ds, type t and name id.  The argument def is
    true to distinguish function definitions from function declarations.
*/

IDENTIFIER
make_func_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int def)
{
	ERROR err;
	MEMBER mem;
	int ok = 1;
	int chk = 1;
	unsigned it;
	int simple_id = 1;
	int main_func = 0;
	IDENTIFIER old_id;
	NAMESPACE ns, ens;
	DECL_SPEC st, df, fn, rs;
	IDENTIFIER over_id = NULL_id;
	IDENTIFIER prev_id = NULL_id;
	unsigned itag = id_function_tag;
	HASHID nm = DEREF_hashid(id_name(id));
#if LANGUAGE_CPP
	int allocator = 0;
#endif

	/* Check for template specialisations */
	if (is_templ_decl(id, t) || is_templ_spec(t)) {
		t = bind_specialise(&id, t, ds, 0, 1, def);
		if (IS_NULL_id(id)) {
			/* Invalid specialisation */
			crt_id_qualifier = qual_none;
			crt_templ_qualifier = 0;
			id = DEREF_id(hashid_id(nm));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			id = make_func_decl(ds, t, id, def);
			return id;
		}
		ns = DEREF_nspace(id_parent(id));
		check_decl_nspace(id, ns, def, crt_namespace);
		ens = ns;
		mem = NULL_member;
		old_id = id;
		simple_id = 0;
	} else {
		/* Check on identifier name */
		QUALIFIER cq = crt_id_qualifier;
		err = check_id_name(id, CONTEXT_FUNCTION);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
			ok = 0;
		}
		/* Check for qualified identifiers */
		if (cq == qual_none) {
			/* Declaration of simple identifier */
			ns = crt_namespace;
			ens = nonblock_namespace;
			mem = search_member(ns, nm, 1);
			old_id = DEREF_id(member_id(mem));
			if (!IS_NULL_id(old_id)) {
				old_id = redecl_inherit(old_id, cq, 0, 1);
			}
			if (def && in_function_defn) {
				/* Check for nested function definitions */
				report(crt_loc, ERR_dcl_fct_def_scope());
			}
		} else {
			/* Redeclaration of class or namespace member */
			ns = DEREF_nspace(id_parent(id));
			check_decl_nspace(id, ns, def, crt_namespace);
			ens = ns;
			if (IS_id_undef(id)) {
				if (IS_nspace_ctype(ns)) {
					itag = id_mem_func_tag;
				}
				mem = search_member(ns, nm, 1);
				old_id = NULL_id;
			} else {
				mem = NULL_member;
				old_id = redecl_inherit(id, cq, 0, 1);
				t = bind_specialise(&old_id, t, ds, 0, 0, def);
				if (!IS_NULL_id(old_id)) {
					id = old_id;
					itag = TAG_id(id);
					ns = DEREF_nspace(id_parent(id));
					ens = ns;
				}
			}
			simple_id = 0;
		}
	}

	/* Allow for special functions */
	if (EQ_KEYWORD(nm, lex_main) && IS_nspace_global(ens)) {
		if (ds & dspec_typedef) {
			/* Ignore type definition */
			/* EMPTY */
		} else {
			t = check_main(t, nm);
			main_func = 1;
		}
	}
	it = TAG_hashid(nm);
#if LANGUAGE_CPP
	switch (it) {
	case hashid_constr_tag: {
		t = check_constr(t, id, ns);
		ds &= ~dspec_empty;
		ds |= dspec_main;
		break;
	}
	case hashid_destr_tag: {
		t = check_destr(t, id, ns);
		ds &= ~dspec_empty;
		ds |= dspec_main;
		break;
	}
	case hashid_op_tag: {
		int cl = IS_nspace_ctype(ns);
		t = check_operator(t, id, cl, &allocator);
		if (!allocator) {
			ds |= dspec_ignore;
		}
		break;
	}
	case hashid_conv_tag: {
		t = check_conv(t, id);
		ds &= ~dspec_empty;
		chk = 0;
		break;
	}
	}
#endif

	/* Deal with inferred types */
	ds = check_func_type(ds, t, def, chk, 0);
	if (main_func) {
		ds |= dspec_main;
	}

	/* Handle function definitions */
	df = (def ? dspec_defn : dspec_none);

	/* Check on storage class specifiers */
	st = check_storage(ds, CONTEXT_FUNCTION, old_id);
	if (st == dspec_static) {
		/* Check on static functions */
		if (main_func) {
			report(crt_loc, ERR_basic_start_main_link(nm, st));
			st = dspec_extern;
		} else {
			/* Check static declarations */
			/* EMPTY */
		}
	} else if (ds & dspec_inline) {
		/* Check on inline functions */
		if (main_func) {
			fn = dspec_inline;
			report(crt_loc, ERR_basic_start_main_link(nm, fn));
			ds &= ~dspec_inline;
		} else {
			if (st == dspec_extern &&
			    inline_linkage == dspec_static) {
				/* Inline functions can't be extern */
				report(crt_loc, ERR_dcl_stc_ext_inline());
			}
			if (in_function_defn) {
				/* Can't declare inline functions in a block */
				report(crt_loc, ERR_dcl_fct_spec_block());
				st = dspec_none;
			}
		}
	}

	/* Deal with type definitions */
	if (ds & dspec_typedef) {
		/* Can only apply typedef to declarations, not definitions */
		if (!def) {
			if (ok) {
				/* Recheck identifier name */
				err = check_id_name(id, CONTEXT_OBJECT);
				if (!IS_NULL_err(err)) {
					report(crt_loc, err);
				}
			}
			id = make_type_decl(ns, ds, t, mem, id);
			return id;
		}
		report(crt_loc, ERR_dcl_typedef_func());
	}

	/* Check on function specifiers */
	fn = check_func_spec(ds, CONTEXT_FUNCTION);

	/* Find the function linkage */
	if (st == dspec_extern) {
		if (in_function_defn && simple_id) {
			prev_id = find_previous(t, id);
			st = find_storage(prev_id, st, NULL_type);
		} else {
			prev_id = old_id;
			st = find_storage(old_id, st, t);
		}
	} else if (st == dspec_static) {
		if (in_function_defn) {
			/* Can't declare static functions in a block */
			report(crt_loc, ERR_dcl_stc_stat_block());
			if (simple_id) {
				prev_id = find_previous(t, id);
			} else {
				prev_id = old_id;
			}
		}
	} else if (st == dspec_none) {
		/* Inline functions have internal linkage */
		if (fn & dspec_inline) {
			st = inline_linkage;
		} else {
			st = dspec_extern;
		}
		if (in_function_defn) {
			prev_id = find_previous(t, id);
			st = find_storage(prev_id, st, NULL_type);
		} else {
			prev_id = old_id;
			st = find_storage(old_id, st, t);
		}
	}

	/* Create the declaration */
	t = lvalue_type(t);
	rs = (ds & dspec_other);
	ds = (st | df | fn | rs);
	if (!IS_NULL_id(old_id)) {
		/* Check redeclarations */
		old_id = redecl_func(ds, t, old_id, itag, &over_id, def);
		if (IS_NULL_id(old_id) && IS_NULL_member(mem)) {
			/* Bad redeclaration of class or namespace member */
			nm = lookup_anon();
			mem = search_member(ns, nm, 1);
			if (IS_nspace_ctype(ns)) {
				itag = id_mem_func_tag;
			}
			over_id = NULL_id;
		}
	}
	object_type(t, itag);
	if (IS_NULL_id(old_id)) {
		/* Declare the function */
		ds = adjust_linkage(ds, 0);
		MAKE_id_function_etc(itag, nm, ds, ns, decl_loc, t, over_id,
				     id);
		if (in_function_defn) {
			id = unify_previous(id, t, prev_id, def);
		} else {
			id = unify_subsequent(id, t, def);
		}
		set_member(mem, id);
		decl_func_type(id, t, def);

		/* Check for conversion functions */
		if (it == hashid_conv_tag && itag != id_mem_func_tag) {
			report(crt_loc, ERR_class_conv_fct_mem());
		}
		if (itag == id_function_tag && option(OPT_decl_hide)) {
			check_hiding(id);
		}
		is_redeclared = 0;
	} else {
		/* Redeclare the function */
		id = old_id;
		is_redeclared = 1;
	}
	ds = DEREF_dspec(id_storage(id));
#if LANGUAGE_CPP
	if (ds & dspec_c) {
		c_linkage(id, def);
	}
#endif

	/* Allow for discarded functions */
	if (!(rs & dspec_ignore) && option(OPT_discard_func)) {
		ds &= ~dspec_ignore;
		COPY_dspec(id_storage(id), ds);
	}
#if LANGUAGE_CPP
	if (allocator) {
		recheck_allocator(id, allocator);
	}
#endif
	if (main_func) {
		recheck_main(id);
	}
	return id;
}


/*
    This routine checks the type of the parameter id declared with type t.
*/

void
check_par_decl(TYPE t, IDENTIFIER id, int loc)
{
	unsigned tag = TAG_type(t);
	if (tag == type_compound_tag) {
		/* Parameters can't have abstract type */
		ERROR err = check_abstract(t);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_class_abstract_par());
			report(crt_loc, err);
		}
	} else if (tag == type_templ_tag) {
		/* Shouldn't have template type */
		report(crt_loc, ERR_temp_decl_bad());
	}
	if (loc == CONTEXT_WEAK_PARAM) {
		/* Check for 'void' and other types */
		ERROR err = check_param_type(id, t);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
	}
	return;
}


/*
    This routine constructs the declaration of a function parameter or
    non-type template parameter (as indicated by loc) with declaration
    specifiers ds, type t and name id.  Note that t is not checked - this
    is only a declaration, and t may still legitimately be void, however
    function and array parameters are adjusted to pointer parameters at
    this stage.
*/

IDENTIFIER
make_param_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int loc)
{
	ERROR err;
	DECL_SPEC st, rs;
	NAMESPACE ns = crt_namespace;
	HASHID nm = DEREF_hashid(id_name(id));
	MEMBER mem = search_member(ns, nm, 1);
	IDENTIFIER old_id = DEREF_id(member_id(mem));

	/* Check on identifier name */
	err = check_id_name(id, loc);
	if (!IS_NULL_err(err)) {
		report(decl_loc, err);
	}

	/* Deal with inferred types */
	ds = check_inferred_type(ds, &t, 0);
	func_type_defn(1);

	/* Check on storage class specifiers */
	st = check_storage(ds, loc, old_id);
	if (st == dspec_register) {
		st = (dspec_auto | dspec_register);
		used_register = 1;
	} else {
		st = dspec_auto;
	}

	/* Deal with type definitions */
	if (ds & dspec_typedef) {
		/* Can't have typedef in function parameters */
		report(decl_loc, ERR_dcl_typedef_par());
	}

	/* Check on function specifiers */
	IGNORE check_func_spec(ds, loc);

	/* Create the parameter declaration */
	t = make_param_type(t, loc);
	rs = (ds & dspec_other);
	ds = (st | rs | dspec_defn);
	if (!IS_NULL_id(old_id)) {
		/* Check for redeclarations */
		if (loc == CONTEXT_TEMPL_PARAM) {
			report(decl_loc, ERR_temp_param_dup(nm));
			nm = lookup_anon();
			mem = search_member(ns, nm, 1);
			id = DEREF_id(hashid_id(nm));
		} else {
			if (loc == CONTEXT_WEAK_PARAM) {
				if (IS_id_weak_param(old_id)) {
					/* Check for order of declaration */
					MEMBER mem1 =
					    DEREF_member(nspace_last(ns));
					while (!EQ_member(mem1, mem)) {
						IDENTIFIER mid =
						    DEREF_id(member_id(mem1));
						if (!IS_NULL_id(mid) &&
						    IS_id_parameter(mid)) {
							report(decl_loc, ERR_dcl_fct_par_order());
							break;
						}
						mem1 = DEREF_member(member_next(mem1));
					}
					old_id = NULL_id;
				} else if (!IS_id_parameter(old_id)) {
					report(decl_loc, ERR_dcl_fct_par_undecl(nm));
				}
			}
			if (!IS_NULL_id(old_id)) {
				if (IS_id_parameter(old_id)) {
					/* Make up new name for parameter */
					nm = lookup_anon();
					mem = search_member(ns, nm, 1);
				}
				IGNORE redecl_id(ds, t, old_id, 0, 0);
			}
		}
	} else {
		if (loc == CONTEXT_WEAK_PARAM) {
			report(decl_loc, ERR_dcl_fct_par_undecl(nm));
		}
	}
	ds = adjust_linkage(ds, 0);
	if (loc == CONTEXT_TEMPL_PARAM) {
		IDENTIFIER pid;
		object_type(t, id_token_tag);
		id = make_exp_param(t, id);
		pid = DEREF_id(id_token_alt(id));
		set_member(mem, pid);
	} else {
		t = lvalue_type(t);
		object_type(t, id_parameter_tag);
		MAKE_id_parameter(nm, ds, ns, decl_loc, t, id);
		set_member(mem, id);
	}
	check_par_decl(t, id, loc);
	is_redeclared = 0;
	return id;
}


/*
    This routine is used to declare a non-prototype function parameter.
*/

IDENTIFIER
weak_param_decl(IDENTIFIER id)
{
	NAMESPACE ns = crt_namespace;
	HASHID nm = DEREF_hashid(id_name(id));
	MEMBER mem = search_member(ns, nm, 1);
	IDENTIFIER old_id = DEREF_id(member_id(mem));
	if (!IS_NULL_id(old_id)) {
		nm = lookup_anon();
		mem = search_member(ns, nm, 1);
		IGNORE redecl_id(dspec_none, NULL_type, old_id, 0, 0);
	}
	MAKE_id_weak_param(nm, dspec_none, ns, decl_loc, id);
	set_member(mem, id);
	is_redeclared = 0;
	return id;
}


/*
    This routine checks the declaration of the class member id with type
    t and declaration specifiers ds.
*/

void
check_mem_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id)
{
	unsigned tag = TAG_type(t);
	if (ds & dspec_mutable) {
		/* Can't apply mutable to a const member */
		CV_SPEC qual = find_cv_qual(t);
		if (qual & cv_const) {
			report(crt_loc, ERR_dcl_stc_mut_const(id));
			if (IS_id_member(id)) {
				qual &= ~cv_const;
				t = qualify_type(t, qual, 0);
				COPY_type(id_member_type(id), t);
			}
		}
	}
	if (tag == type_top_tag || tag == type_bottom_tag) {
		/* Always report void members */
		report(crt_loc, ERR_basic_fund_void_mem(id, t));
	} else if (tag == type_templ_tag) {
		/* Shouldn't have template type */
		report(crt_loc, ERR_temp_decl_bad());
	} else if (ds & dspec_defn) {
		/* Only check otherwise for defined (non-static) members */
		if (tag == type_ref_tag) {
			/* References don't need checking */
			/* EMPTY */
		} else {
			/* Other members should have complete type */
			ERROR err = check_complete(t);
			if (!IS_NULL_err(err)) {
				ERROR err2 = ERR_class_mem_incompl_mem(id);
				err = concat_error(err, err2);
				report(crt_loc, err);
			} else {
				/* Members can't have abstract type */
				err = check_abstract(t);
				if (!IS_NULL_err(err)) {
					ERROR err2 = ERR_class_abstract_mem(id);
					err = concat_error(err, err2);
					report(crt_loc, err);
				}
			}
		}
	}
	return;
}


/*
    This routine constructs the declaration of a class member with
    declaration specifiers ds, type t and name id.  Note that the access
    declarations (i.e. just a qualified-id and a semicolon) can only be
    spotted at this stage.  The argument sm is true if this is the first
    declarator in a list and the next token is a semicolon.
*/

IDENTIFIER
make_member_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int sm)
{
	ERROR err;
	HASHID nm;
	MEMBER mem;
	int redef = 0;
	int tokenised = 0;
	IDENTIFIER old_id;
	IDENTIFIER alt_id;
	DECL_SPEC st, df, rs;
	OFFSET off = NULL_off;
	CLASS_TYPE ct = crt_class;
	IDENTIFIER tok_id = NULL_id;
	NAMESPACE ns = crt_namespace;
	unsigned tag = TAG_type(t);
	QUALIFIER cq = crt_id_qualifier;
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));

	/* Check for template specialisations */
	if (is_templ_decl(id, NULL_type)) {
		IGNORE bind_specialise(&id, t, dspec_extern, 0, 1, 0);
		if (!IS_NULL_id(id)) {
			report(crt_loc, ERR_temp_spec_member(id));
		}
		return id;
	}

	/* Find previous declaration */
	nm = DEREF_hashid(id_name(id));
	if (IS_hashid_constr(nm) && cq == qual_none) {
		DECL_SPEC sds = (dspec_static | dspec_typedef | dspec_reserve);
		if (!(ds & sds)) {
			/* Can use class name for non-static member */
			report(crt_loc, ERR_class_mem_ctor_data(id));
			id = DEREF_id(hashid_constr_tid(nm));
			nm = DEREF_hashid(id_name(id));
		}
	}
	mem = search_member(ns, nm, 1);
	old_id = DEREF_id(member_id(mem));
	alt_id = DEREF_id(member_alt(mem));
	if (!IS_NULL_id(old_id)) {
		old_id = redecl_inherit(old_id, cq, 1, 2);
	}

	/* Check on member qualifications */
	if (cq != qual_none) {
		if ((ds & dspec_empty) && sm) {
			/* Spot access declarations */
			id = access_decl(id);
			return id;
		}
		ns = DEREF_nspace(id_parent(id));
		if (EQ_nspace(ns, crt_namespace)) {
			/* Qualifier indicates the current class */
			report(crt_loc, ERR_dcl_meaning_mem(cq, id));
			crt_id_qualifier = qual_none;
		} else {
			/* Qualifier indicates some other namespace */
			id = make_object_decl(ds, t, id, 0);
			return id;
		}
	}

	/* Check on identifier name */
	err = check_id_name(id, CONTEXT_MEMBER);
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}

	/* Deal with inferred types */
	ds = check_inferred_type(ds, &t, 1);

	/* Check on storage class specifiers */
	st = check_storage(ds, CONTEXT_MEMBER, old_id);
	if (st == dspec_static) {
		if (tag == type_bitfield_tag) {
			/* Bitfield members can't be static */
			report(crt_loc, ERR_class_bit_static());
			st = dspec_none;
			df = dspec_defn;
		} else {
			if (ci & cinfo_union) {
				/* Unions can't have static data members */
				report(crt_loc, ERR_class_union_static(ct));
				st = dspec_none;
				df = dspec_defn;
			} else {
				/* Static members are only declared */
				df = dspec_none;
			}
		}
	} else {
		/* Other members are defined */
		df = dspec_defn;
	}

	/* Deal with type definitions */
	if (ds & dspec_typedef) {
		LIST(IDENTIFIER)ft = DEREF_list(ctype_nest(ct));
		if (tag == type_bitfield_tag) {
			report(crt_loc, ERR_class_bit_typedef());
			t = find_bitfield_type(t);
		}
		id = make_type_decl(ns, ds, t, mem, id);
		CONS_id(id, ft, ft);
		COPY_list(ctype_nest(ct), ft);
		return id;
	}

	/* Check on function specifiers */
	IGNORE check_func_spec(ds, CONTEXT_MEMBER);

	/* Record class properties */
	rs = (ds & dspec_other);
	if (rs & dspec_token) {
		tokenised = 1;
	}
	if (st == dspec_static) {
		ds = (df | rs | crt_access);
	} else {
		ds = (st | df | rs | crt_access);
	}

	/* Check for redeclarations */
	t = lvalue_type(t);
	if (!IS_NULL_id(old_id)) {
		if (st != dspec_static && IS_id_member(old_id)) {
			/* Allow for token definitions */
			if (tokenised) {
				/* Token with previous definition */
				off = DEREF_off(id_member_off(old_id));
				t = DEREF_type(id_member_type(old_id));
				tokenised = 3;
			} else {
				tok_id = find_token(old_id);
				if (IS_id_token(tok_id)) {
					/* Member was previously tokenised */
					DECL_SPEC tds =
					    DEREF_dspec(id_storage(tok_id));
					if (!(tds & (dspec_pure |
						     dspec_auto))) {
						/* Token can't be defined */
						tokenised = 2;
					}
				}
			}
		}
		if (tokenised == 0) {
			/* Redeclare if neither is a token */
			old_id = redecl_id(ds, t, old_id, 0, 0);
			if (IS_NULL_id(old_id)) {
				redef = 1;
			}
		}
	} else if (!IS_NULL_id(alt_id)) {
		redef = 1;
	}

	/* Create the declaration */
	ds = adjust_linkage(ds, 1);
	if (!really_in_function_defn) {
		ds |= dspec_extern;
	}
	if (st == dspec_static) {
		object_type(t, id_stat_member_tag);
		MAKE_id_stat_member(nm, ds, ns, decl_loc, t, id);
	} else {
		object_type(t, id_member_tag);
		MAKE_id_member(nm, ds, ns, decl_loc, t, id);
		if (tokenised == 0 || tokenised == 2) {
			/* Construct member offset if not tokenised */
			MAKE_off_member(id, off);
		}
		COPY_off(id_member_off(id), off);
		if (redef) {
			mem = update_member(ns, mem);
		}
	}

	/* Set the namespace member */
	if (tokenised >= 2) {
		/* Create dummy member */
		MEMBER mem_old = DEREF_member(nspace_last(ns));
		if (tokenised == 2) {
			/* Define existing token */
			IGNORE define_mem_token(tok_id, off, t, 1);
		} else {
			/* Token is defined later ... */
			/* EMPTY */
		}
		MAKE_member_large(NULL_member, NULL_member, mem);
		COPY_id(member_id(mem), id);
		COPY_member(nspace_last(ns), mem);
		COPY_member(member_next(mem_old), mem);
	}
	set_member(mem, id);
	check_mem_decl(ds, t, id);
	is_redeclared = 0;

	/* Adjust class information */
	if (st == dspec_static) {
		if (really_in_function_defn) {
			/* Can't have static members in local classes */
			report(crt_loc, ERR_class_local_static(id));
		}
		ci |= cinfo_static;
	} else {
		/* Check member types */
		if (crt_access != dspec_public) {
			ci |= cinfo_private;
		}
		ci = check_member_type(ct, ci, t, 0);
		ci &= ~cinfo_empty;
	}
	COPY_cinfo(ctype_info(ct), ci);
	return id;
}


/*
    This routine updates the special member function information for
    the class ct using the function id.  tag gives the identifier name tag.
*/

void
special_func_mem(CLASS_TYPE ct, IDENTIFIER id, unsigned tag, IDENTIFIER prev)
{
	switch (tag) {
	case hashid_constr_tag: {
		/* Set constructor */
		COPY_id(ctype_constr(ct), id);
		break;
	}
	case hashid_destr_tag: {
		/* Set destructor */
		COPY_id(ctype_destr(ct), id);
		break;
	}
	case hashid_conv_tag: {
		/* Maintain list of conversion functions */
		HASHID nm = DEREF_hashid(id_name(id));
		LIST(IDENTIFIER)conv = DEREF_list(ctype_conv(ct));
		LIST(IDENTIFIER)p = conv;
		while (!IS_NULL_list(p)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(p));
			HASHID pnm = DEREF_hashid(id_name(pid));
			if (EQ_hashid(nm, pnm)) {
				/* Already member of list */
				IDENTIFIER over;
				over = DEREF_id(id_function_etc_over(id));
				if (!EQ_id(pid, over) && !EQ_id(pid, prev)) {
					/* Template function has produced
					 * duplicate */
					PTR(LOCATION)ploc = id_loc(pid);
					report(crt_loc,
					       ERR_class_mem_redecl(id, ploc));
				}
				COPY_id(HEAD_list(p), id);
				return;
			}
			p = TAIL_list(p);
		}
		CONS_id(id, conv, conv);
		COPY_list(ctype_conv(ct), conv);
		break;
	}
	}
	return;
}


/*
    This routine constructs a function declaration for a class member
    function with declaration specifiers ds, type t and name id.  The
    argument def is true to distinguish function definitions from function
    declarations.
*/

#if LANGUAGE_CPP

IDENTIFIER
make_func_mem_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int def)
{
	ERROR err;
	MEMBER mem;
	int ok = 1;
	int chk = 1;
	unsigned it;
	unsigned itag;
	int allocator = 0;
	IDENTIFIER old_id;
	LIST(VIRTUAL)vt;
	DECL_SPEC st, df, fn, rs;
	IDENTIFIER over_id = NULL_id;
	IDENTIFIER hide_id = NULL_id;
	NAMESPACE ns = crt_namespace;
	QUALIFIER cq = crt_id_qualifier;
	HASHID nm = DEREF_hashid(id_name(id));
	CLASS_TYPE ct = crt_class;
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));

	/* Check for template specialisations */
	if (is_templ_decl(id, t) || is_templ_spec(t)) {
		st = (dspec_extern | (ds & dspec_inline));
		IGNORE bind_specialise(&id, t, st, 0, 1, def);
		if (!IS_NULL_id(id)) {
			report(crt_loc, ERR_temp_spec_member(id));
		}
		return id;
	}

	/* Find previous declaration */
	mem = search_member(ns, nm, 1);
	old_id = DEREF_id(member_id(mem));
	if (!IS_NULL_id(old_id)) {
		old_id = redecl_inherit(old_id, cq, 1, 1);
	}

	/* Check on member qualifications */
	if (cq != qual_none) {
		ns = DEREF_nspace(id_parent(id));
		if (EQ_nspace(ns, crt_namespace)) {
			/* Qualifier indicates the current class */
			report(crt_loc, ERR_dcl_meaning_mem(cq, id));
			crt_id_qualifier = qual_none;
		} else {
			/* Qualifier indicates some other namespace */
			id = make_func_decl(ds, t, id, def);
			return id;
		}
	}

	/* Check on identifier name */
	err = check_id_name(id, CONTEXT_FUNC_MEMBER);
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
		ok = 0;
	}

	/* Allow for special functions */
	it = TAG_hashid(nm);
	switch (it) {
	case hashid_constr_tag: {
		t = check_constr(t, id, ns);
		ds &= ~dspec_empty;
		ds |= dspec_main;
		break;
	}
	case hashid_destr_tag: {
		t = check_destr(t, id, ns);
		ds &= ~dspec_empty;
		ds |= dspec_main;
		break;
	}
	case hashid_op_tag: {
		t = check_operator(t, id, 1, &allocator);
		if (!allocator) {
			ds |= dspec_ignore;
		}
		break;
	}
	case hashid_conv_tag: {
		t = check_conv(t, id);
		ds &= ~dspec_empty;
		chk = 0;
		break;
	}
	}

	/* Deal with inferred types */
	ds = check_func_type(ds, t, def, chk, 1);

	/* Handle function definitions */
	if (def) {
		/* Functions defined in a class are inline */
		df = dspec_defn;
		ds |= dspec_inline;
	} else {
		df = dspec_none;
	}

	/* Check on storage class specifiers */
	st = check_storage(ds, CONTEXT_FUNC_MEMBER, old_id);

	/* Deal with type definitions */
	if (ds & dspec_typedef) {
		/* Can only apply typedef to declarations, not definitions */
		if (!def) {
			if (ok) {
				/* Recheck identifier name */
				err = check_id_name(id, CONTEXT_MEMBER);
				if (!IS_NULL_err(err)) {
					report(crt_loc, err);
				}
			}
			id = make_type_decl(ns, ds, t, mem, id);
			return id;
		}
		report(crt_loc, ERR_dcl_typedef_func());
	}

	/* Check special functions */
	if (allocator) {
		/* Allocator functions are implicitly static */
		if (st != dspec_static) {
			st = dspec_static;
			allocator |= 0x4;
		}
	} else if (st == dspec_static) {
		switch (it) {
		case hashid_constr_tag: {
			/* Constructors can't be static */
			report(crt_loc, ERR_class_ctor_static());
			st = dspec_none;
			break;
		}
		case hashid_destr_tag: {
			/* Destructors can't be static */
			report(crt_loc, ERR_class_dtor_static());
			st = dspec_none;
			break;
		}
		case hashid_op_tag: {
			/* Overloaded operators can't be static */
			report(crt_loc, ERR_over_oper_static());
			st = dspec_none;
			break;
		}
		case hashid_conv_tag: {
			/* Conversion functions can't be static */
			report(crt_loc, ERR_class_conv_fct_mem());
			st = dspec_none;
			break;
		}
		}
	}

	/* Check on function specifiers */
	fn = check_func_spec(ds, CONTEXT_FUNC_MEMBER);
	vt = overrides_virtual(ct, nm, t, &hide_id);
	if (!IS_NULL_list(vt)) {
		/* Check for overriding of virtual functions */
		if (!(fn & dspec_virtual)) {
			if (!(ds & dspec_implicit)) {
				err = ERR_class_virtual_override(nm);
				if (!IS_NULL_err(err))report(crt_loc, err);
			}
			fn |= dspec_virtual;
		}
	} else if (!IS_NULL_id(hide_id)) {
		err = ERR_class_virtual_hide(nm, hide_id);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}
	}
	if (fn & dspec_virtual) {
		if (st == dspec_static) {
			/* Static members can't be virtual */
			err = ERR_class_static_mfct_virt();
			if (allocator & 0x4) {
				/* Allocator functions are implicitly static */
				err = concat_error(ERR_class_free_static(nm),
						   err);
			}
			report(crt_loc, err);
			fn &= ~dspec_virtual;
		} else if (it == hashid_constr_tag) {
			/* Constructors can't be virtual */
			report(crt_loc, ERR_class_ctor_virtual());
			fn &= ~dspec_virtual;
		} else {
			if (ci & cinfo_union) {
				/* Unions can't have virtual functions */
				report(crt_loc, ERR_class_union_virtual(ct));
				fn &= ~dspec_virtual;
			} else if (ds & dspec_template) {
				/* Can't have a virtual template function */
				report(crt_loc, ERR_temp_mem_virtual());
				fn &= ~dspec_virtual;
			} else {
				/* The current class is polymorphic */
				ci |= cinfo_polymorphic;
				ci &= ~cinfo_empty;
			}
		}
	}
	if (fn & dspec_explicit) {
		/* Only constructors can be explicit */
		if (it == hashid_constr_tag) {
			have_constr_expl = 1;
		} else {
			if (it == hashid_conv_tag) {
				report(crt_loc, ERR_dcl_fct_spec_expl_conv());
				have_conv_expl = 1;
			} else {
				report(crt_loc, ERR_dcl_fct_spec_expl_constr());
				fn &= ~dspec_explicit;
			}
		}
	}
	if (ds & dspec_template) {
		/* Check for template function members */
		if (it == hashid_destr_tag) {
			report(crt_loc, ERR_temp_mem_destr());
		}
	}

	/* Record class properties */
	rs = (ds & dspec_other);
	if (st == dspec_static) {
		itag = id_stat_mem_func_tag;
		ds = (df | fn | rs | crt_access);
	} else {
		itag = id_mem_func_tag;
		ds = (st | df | fn | rs | crt_access);
	}
	if (!(ds & dspec_implicit)) {
		ci |= cinfo_function;
	}
	COPY_cinfo(ctype_info(ct), ci);

	/* Create the function declaration */
	t = lvalue_type(t);
	if (!IS_NULL_id(old_id)) {
		/* Check for redeclarations */
		IGNORE redecl_func(ds, t, old_id, itag, &over_id, def);
	}
	object_type(t, itag);
	ds = adjust_linkage(ds, 1);
	if (!really_in_function_defn) {
		ds |= dspec_extern;
	}
	MAKE_id_function_etc(itag, nm, ds, ns, decl_loc, t, over_id, id);
	if (!IS_NULL_id(over_id)) {
		id = hide_functions(id, over_id, 1);
	}
	set_member(mem, id);
	decl_func_type(id, t, def);
	is_redeclared = 0;
	ds = DEREF_dspec(id_storage(id));

	/* Maintain lists of functions */
	special_func_mem(ct, id, it, old_id);
	if (def) {
		LIST(IDENTIFIER) ft = DEREF_list(ctype_nest(ct));
		CONS_id(id, ft, ft);
		COPY_list(ctype_nest(ct), ft);
	}
	if (ds & dspec_virtual) {
		add_virtual(ct, id, vt);
	}
	if (allocator) {
		allocator &= 0x3;
		recheck_allocator(id, allocator);
	}

	/* Allow for discarded functions */
	if (!(rs & dspec_ignore) && option(OPT_discard_func)) {
		ds &= ~dspec_ignore;
		COPY_dspec(id_storage(id), ds);
	}
	return id;
}

#endif


/*
    This routine is used to handle the declaration of a friend function
    within a class.  The parameters are identical to those in the previous
    routine.
*/

#if LANGUAGE_CPP

IDENTIFIER
make_friend_decl(DECL_SPEC ds, TYPE t, IDENTIFIER id, int def, int chum)
{
	ERROR err;
	MEMBER mem;
	int chk = 1;
	unsigned it;
	int allocator = 0;
	int main_func = 0;
	IDENTIFIER old_id;
	NAMESPACE ns, ens;
	DECL_SPEC st, df, fn, rs;
	IDENTIFIER over_id = NULL_id;
	unsigned itag = id_function_tag;
	QUALIFIER cq = crt_id_qualifier;
	int td = crt_templ_qualifier;
	HASHID nm = DEREF_hashid(id_name(id));

	/* Check for template specialisations */
	if (in_template_decl && cq == qual_none && td == 0 && chum) {
		TYPE s = injected_type(t, 1);
		if (!EQ_type(s, t)) {
			/* Friend declaration is implicitly a template */
			int eq = 0;
			IDENTIFIER tid = make_friend_decl(ds, s, id, 0, 0);
			if (do_dump) {
				dump_declare(tid, &decl_loc, 0);
			}
			id = deduce_func(tid, t, &eq);
			if (IS_NULL_id(id)) {
				return tid;
			}
			crt_templ_qualifier = 1;
		}
	}
	if (is_templ_decl(id, t) || is_templ_spec(t)) {
		t = bind_specialise(&id, t, ds, 0, 1, def);
		if (IS_NULL_id(id)) {
			/* Invalid specialisation */
			crt_id_qualifier = qual_none;
			crt_templ_qualifier = 0;
			id = DEREF_id(hashid_id(nm));
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			id = make_friend_decl(ds, t, id, def, chum);
			return id;
		}
		ns = DEREF_nspace(id_parent(id));
		ens = ns;
		mem = NULL_member;
		old_id = id;
		if (def) {
			/* Check enclosing namespace scope */
			check_decl_nspace(id, ns, def, nonclass_namespace);
		}
	} else {
		/* Deal with typedef immediately */
		if ((ds & dspec_typedef) && !def) {
			id = make_func_mem_decl(ds, t, id, def);
			return id;
		}

		/* Check on identifier name */
		err = check_id_name(id, CONTEXT_FUNCTION);
		if (!IS_NULL_err(err)) {
			report(crt_loc, err);
		}

		/* Check on member qualification */
		if (cq == qual_none) {
			/* Declaration of simple identifier */
			ns = nonclass_namespace;
			ens = nonblock_namespace;
			mem = search_member(ns, nm, 1);
			old_id = DEREF_id(member_id(mem));
			if (!IS_NULL_id(old_id)) {
				old_id = redecl_inherit(old_id, cq, 0, 1);
			}
			if (in_template_decl &&
			    is_templ_nspace(crt_namespace)) {
				/* Friend of template class */
				NAMESPACE tns = templ_namespace;
				mem = search_member(tns, nm, 1);
			}
		} else {
			/* Redeclaration of class or namespace member */
			ns = DEREF_nspace(id_parent(id));
			ens = ns;
			/* QUERY: Any other restrictions? */
			if (IS_id_undef(id)) {
				report(crt_loc, ERR_lookup_qual_undef(nm, ns));
				if (IS_nspace_ctype(ns)) {
					itag = id_mem_func_tag;
				}
				mem = search_member(ns, nm, 1);
				old_id = NULL_id;
			} else {
				mem = NULL_member;
				old_id = redecl_inherit(id, cq, 0, 1);
				t = bind_specialise(&old_id, t, ds, 0, 0, def);
				if (!IS_NULL_id(old_id)) {
					id = old_id;
					itag = TAG_id(id);
					ns = DEREF_nspace(id_parent(id));
					ens = ns;
					if (def) {
						/* Check enclosing namespace
						 * scope */
						check_decl_nspace(id, ns, def, nonclass_namespace);
					}
				}
			}
		}
	}

	/* Can't define function in local class */
	if (def && really_in_function_defn) {
		report(crt_loc, ERR_class_friend_local());
	}

	/* Allow for special functions */
	if (EQ_KEYWORD(nm, lex_main) && IS_nspace_global(ens)) {
		/* Declare main as a friend - it could happen */
		t = check_main(t, nm);
		main_func = 1;
	}
	it = TAG_hashid(nm);
	switch (it) {
	case hashid_constr_tag: {
		t = check_constr(t, id, ns);
		ds |= dspec_main;
		break;
	}
	case hashid_destr_tag: {
		t = check_destr(t, id, ns);
		ds |= dspec_main;
		break;
	}
	case hashid_op_tag: {
		int cl = IS_nspace_ctype(ns);
		t = check_operator(t, id, cl, &allocator);
		if (!allocator) {
			ds |= dspec_ignore;
		}
		break;
	}
	case hashid_conv_tag: {
		t = check_conv(t, id);
		chk = 0;
		break;
	}
	}

	/* Deal with inferred types */
	ds = check_func_type(ds, t, def, chk, 1);
	if (main_func) {
		ds |= dspec_main;
	}

	/* Check on storage class specifiers */
	st = check_storage(ds, CONTEXT_FUNCTION, old_id);
	if (st != dspec_none) {
		/* Can't have storage class with friend */
		report(crt_loc, ERR_class_friend_storage(st));
	}
	if (def) {
		/* Functions defined in a class are inline */
		df = dspec_defn;
		ds |= dspec_inline;
		st = find_storage(old_id, inline_linkage, t);
	} else if (ds & dspec_inline) {
		df = dspec_none;
		st = find_storage(old_id, inline_linkage, t);
	} else {
		df = dspec_none;
		st = find_storage(old_id, dspec_extern, t);
	}
	if ((ds & dspec_inline) && main_func) {
		report(crt_loc, ERR_basic_start_main_link(nm, dspec_inline));
		ds &= ~dspec_inline;
		st = dspec_extern;
	}

	/* Check on function specifiers */
	fn = check_func_spec(ds, CONTEXT_FUNCTION);

	/* Create the declaration */
	t = lvalue_type(t);
	rs = (ds & dspec_other);
	ds = (st | df | fn | rs);
	if (!IS_NULL_id(old_id)) {
		/* Check redeclarations */
		old_id = redecl_func(ds, t, old_id, itag, &over_id, def);
		if (IS_NULL_id(old_id) && IS_NULL_member(mem)) {
			/* Bad redeclaration of class or namespace member */
			nm = lookup_anon();
			mem = search_member(ns, nm, 1);
			if (IS_nspace_ctype(ns)) {
				itag = id_mem_func_tag;
			}
			over_id = NULL_id;
		}
	}
	object_type(t, itag);
	if (IS_NULL_id(old_id)) {
		/* Declare the function */
		ds = adjust_linkage(ds, 0);
		MAKE_id_function_etc(itag, nm, ds, ns, decl_loc, t, over_id,
				     id);
		id = unify_subsequent(id, t, def);
		set_member(mem, id);
		decl_func_type(id, t, def);
		report(decl_loc, ERR_class_friend_pre(id));

		/* Check for conversion functions */
		if (it == hashid_conv_tag && itag != id_mem_func_tag) {
			report(crt_loc, ERR_class_conv_fct_mem());
		}
		if (itag == id_function_tag && option(OPT_decl_hide)) {
			check_hiding(id);
		}
		is_redeclared = 0;
	} else {
		/* Redeclare the function */
		id = old_id;
		is_redeclared = 1;
	}
	ds = DEREF_dspec(id_storage(id));
#if LANGUAGE_CPP
	if (ds & dspec_c) {
		c_linkage(id, def);
	}
#endif

	/* Maintain list of inline functions */
	if (def) {
		CLASS_TYPE ct = crt_class;
		LIST(IDENTIFIER)ft = DEREF_list(ctype_nest(ct));
		CONS_id(id, ft, ft);
		COPY_list(ctype_nest(ct), ft);
	}

	/* Allow for discarded functions */
	if (!(rs & dspec_ignore) && option(OPT_discard_func)) {
		ds &= ~dspec_ignore;
		COPY_dspec(id_storage(id), ds);
	}

	/* Make the function a friend */
	if (chum) {
		friend_function(crt_class, id, 1);
	}
	if (main_func) {
		recheck_main(id);
	}
	if (allocator) {
		recheck_allocator(id, allocator);
	}
	return id;
}

#endif


/*
    An anonymous union cannot have private or protected members or member
    functions (in addition, no union can have static data members).  This
    information is readily accessible from the class information field.
    The routine class_info is not used in this case because it includes
    the name of ct in its errors, which is not particularly useful when
    ct is anonymous.
*/

static void
check_anon_union(CLASS_TYPE ct)
{
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	report(crt_loc, ERR_class_union_anon());

	if (ci & cinfo_private) {
		report(crt_loc, ERR_class_union_anon_private());
	}
	if (ci & cinfo_function) {
		report(crt_loc, ERR_class_union_anon_func());
	}
	return;
}


/*
    This routine handles a declaration with no declarators, comprising the
    declaration specifiers ds, the template type qualifiers q and the type
    specifiers t (which may be an elaborate pre-type).  Whether this is
    legal depends on the value of the flag have_type_specifier described
    in predict.c, which indicates whether t contained a type declaration
    or definition.  Note that anonymous unions come under this heading
    (I hate anonymous unions).
*/

static IDENTIFIER
empty_object_decl(DECL_SPEC ds, TYPE q, TYPE t)
{
	CV_SPEC qual;
	DECL_SPEC st;
	IDENTIFIER tid;
	BASE_TYPE key = btype_class;
	int td = have_type_declaration;

	/* Check for type declarations */
	if (IS_type_pre(t)) {
		QUALIFIER it;
		DESTROY_type_pre(destroy, qual, tid, key, it, t);
		if (it == qual_none) {
			/* Unqualified identifier */
			DECL_SPEC mode = (dspec_defn | dspec_auto);
			td = TYPE_DECL_ELABORATE;
			tid = find_elaborate_type(tid, key, q, mode);
		} else {
			/* Qualified identifier */
			DECL_SPEC mode = (dspec_defn | dspec_alias);
			td = TYPE_DECL_OVER_ELAB;
			if (!IS_NULL_type(q)) {
				td = TYPE_DECL_ELABORATE;
			}
			tid = find_elaborate_type(tid, key, q, mode);
		}
#if LANGUAGE_CPP
		t = DEREF_type(id_class_name_etc_defn(tid));
		t = qualify_type(t, qual, 0);
#endif
	} else {
		tid = DEREF_id(type_name(t));
		qual = DEREF_cv(type_qual(t));
	}
	qual &= cv_qual;

	/* Check for anonymous unions */
	if (td == TYPE_DECL_ANON && !(ds & dspec_typedef)) {
		TYPE s = t;
		while (IS_type_templ(s)) {
			s = DEREF_type(type_templ_defn(s));
		}
		if (IS_type_compound(s)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(s));
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_union) {
				/* Anonymous union found */
				int def;
				HASHID nm;
				IDENTIFIER id;
				check_anon_union(ct);

				/* Create the union object */
				nm = lookup_anon();
				id = DEREF_id(hashid_id(nm));
				crt_id_qualifier = qual_none;
				crt_templ_qualifier = 0;
				id = make_object_decl(ds, t, id, 0);
				ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_extern) {
					/* Anonymous unions can't have external
					 * linkage */
					report(crt_loc,
					       ERR_class_union_anon_static());
				}
				def = init_object(id, NULL_exp);
				if (do_dump) {
					dump_declare(id, &crt_loc, def);
				}
				if (output_diag && !in_function_defn) {
					compile_variable(id, 1);
				}

				/* Bring fields into scope */
				if (!redecl_anon_union(ct, ds, id)) {
					report(crt_loc, ERR_dcl_dcl_empty());
				}
				return id;
			}
		}
	}

	/* Check declaration specifiers */
	if (ds != dspec_none) {
		st = check_storage(ds, CONTEXT_OBJECT, NULL_id);
		if (st != dspec_none) {
			/* Can't have a storage class specifier */
			report(crt_loc, ERR_dcl_stc_bad(st));
		}
		if (ds & dspec_typedef) {
			report(crt_loc, ERR_dcl_typedef_dcl());
		}
		IGNORE check_func_spec(ds, CONTEXT_OBJECT);
	}

	/* Check type qualifiers */
	if (qual != cv_none && td != TYPE_DECL_NONE) {
		report(crt_loc, ERR_dcl_type_cv_unused(qual));
	}

	/* Check for type definitions */
	switch (td) {
	case TYPE_DECL_NONE: {
		report(crt_loc, ERR_dcl_dcl_empty());
		tid = NULL_id;
		break;
	}
	case TYPE_DECL_ANON: {
		report(crt_loc, ERR_dcl_dcl_anon());
		break;
	}
	case TYPE_DECL_OVER_ELAB: {
		report(crt_loc, ERR_dcl_type_elab_qual(key));
		break;
	}
	}
	return tid;
}


/*
    This routine handles a class member declaration with no declarators,
    comprising the declaration specifiers ds, the template type qualifiers
    q and the type specifiers t.  This is similar to empty_object_decl,
    except that provision needs to be made for friend declarations of the
    form 'friend class C'.
*/

static IDENTIFIER
empty_member_decl(DECL_SPEC ds, TYPE q, TYPE t)
{
	CV_SPEC qual;
	IDENTIFIER tid;
	BASE_TYPE key = btype_class;
	int td = have_type_declaration;

	/* Check for type declarations */
	if (IS_type_pre(t)) {
		QUALIFIER it;
		DESTROY_type_pre(destroy, qual, tid, key, it, t);
		if (it == qual_none) {
			/* Unqualified identifier */
			DECL_SPEC mode = dspec_defn;
			if (option(OPT_class_scope)) {
				mode |= dspec_auto;
			}
			if (ds & dspec_friend) {
				mode = (dspec_defn | dspec_used | dspec_friend);
				if (in_template_decl &&
				    is_templ_nspace(crt_namespace)) {
					/* Friend of template class */
					mode |= dspec_template;
				}
				mode |= dspec_register;
			}
			tid = find_elaborate_type(tid, key, q, mode);
			if (mode & dspec_template) {
				NAMESPACE ns = DEREF_nspace(id_parent(tid));
				if (EQ_nspace(ns, templ_namespace)) {
					ns = nonclass_namespace;
					COPY_nspace(id_parent(tid), ns);
				}
			}
			td = TYPE_DECL_ELABORATE;
		} else {
			/* Qualified identifier */
			DECL_SPEC mode = (dspec_defn | dspec_alias);
			if (ds & dspec_friend) {
				mode |= dspec_friend;
			}
			tid = find_elaborate_type(tid, key, q, mode);
			td = TYPE_DECL_OVER_ELAB;
		}
		t = DEREF_type(id_class_name_etc_defn(tid));
		t = qualify_type(t, qual, 0);
	} else {
		tid = DEREF_id(type_name(t));
		qual = DEREF_cv(type_qual(t));
	}
	qual &= cv_qual;

	/* Check for anonymous unions */
	if (td == TYPE_DECL_ANON && !(ds & dspec_typedef)) {
		TYPE s = t;
		while (IS_type_templ(s)) {
			s = DEREF_type(type_templ_defn(s));
		}
		if (IS_type_compound(s)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(s));
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_union) {
				/* Anonymous union found */
				int def;
				HASHID nm;
				IDENTIFIER id;
				check_anon_union(ct);

				/* Create union member */
				nm = lookup_anon();
				id = DEREF_id(hashid_id(nm));
				crt_id_qualifier = qual_none;
				crt_templ_qualifier = 0;
				if (ds & dspec_static) {
					/* Can't be a static data member */
					report(crt_loc,
					       ERR_class_union_anon_mem());
					ds &= ~dspec_static;
				}
				id = make_member_decl(ds, t, id, 0);
				def = init_member(id, NULL_exp);
				if (do_dump) {
					dump_declare(id, &crt_loc, def);
				}

				/* Bring fields into scope */
				if (!redecl_anon_union(ct, dspec_none, id)) {
					report(crt_loc, ERR_class_mem_empty());
				}
				return id;
			}
		}
	}

	/* Check declaration specifiers */
	if (ds != dspec_none) {
		CLASS_TYPE cs = crt_class;
		CLASS_TYPE ct = NULL_ctype;
		DECL_SPEC st = check_storage(ds, CONTEXT_MEMBER, NULL_id);
		if (st != dspec_none) {
			/* Can't have a storage class specifier */
			report(crt_loc, ERR_dcl_stc_bad(st));
		}
		if (ds & dspec_typedef) {
			report(crt_loc, ERR_dcl_typedef_dcl());
		}
		if (ds & dspec_friend) {
			/* Allow for friend declarations */
			while (IS_type_templ(t)) {
				t = DEREF_type(type_templ_defn(t));
			}
			if (IS_type_compound(t)) {
				ct = DEREF_ctype(type_compound_defn(t));
			} else if (is_templ_type(t)) {
				IDENTIFIER cid = DEREF_id(type_token_tok(t));
				ct = find_class(cid);
			}
			if (!IS_NULL_ctype(ct)) {
				switch (td) {
				case TYPE_DECL_ELABORATE:
				case TYPE_DECL_OVER_ELAB:
					/* Have 'friend class A ;' */
					break;
				case TYPE_DECL_NORMAL:
					/* Have 'friend class A { ... } ;' */
					report(crt_loc, ERR_class_friend_def());
					break;
				case TYPE_DECL_ANON:
					/* Have 'friend class { ... } ;' */
					report(crt_loc, ERR_class_mem_anon());
					report(crt_loc, ERR_class_friend_def());
					break;
				default:
					/* Have 'friend A ;' */
					report(crt_loc,
					       ERR_class_friend_elab());
					break;
				}
				ds &= ~dspec_friend;
			}
		}
		IGNORE check_func_spec(ds, CONTEXT_MEMBER);
		if (!IS_NULL_ctype(ct)) {
			/* Declare a class as a friend */
			tid = DEREF_id(ctype_name(ct));
			if (qual != cv_none) {
				report(crt_loc, ERR_dcl_type_cv_unused(qual));
			}
			friend_class(cs, tid, 1);
			return tid;
		}
	}

	/* Check type qualifiers */
	if (qual != cv_none && td != TYPE_DECL_NONE) {
		report(crt_loc, ERR_dcl_type_cv_unused(qual));
	}

	/* Check for type definitions */
	switch (td) {
	case TYPE_DECL_NONE: {
		report(crt_loc, ERR_class_mem_empty());
		tid = NULL_id;
		break;
	}
	case TYPE_DECL_ANON: {
		report(crt_loc, ERR_class_mem_anon());
		break;
	}
	case TYPE_DECL_OVER_ELAB: {
		report(crt_loc, ERR_dcl_type_elab_qual(key));
		break;
	}
	}
	return tid;
}


/*
    This routine checks the empty declaration declared with the declaration
    specifiers ds, the template type qualifiers q, the pre-type bt and t
    and the cv-qualifiers cv (not all of which will be empty).  The tok
    parameter is used to pass in the number of the last lexical token read,
    this is used for a backwards compatibility hack involving types such
    as wchar_t which used to be defined by typedefs, but are now keywords.
    mem is true for member declarations.
*/

IDENTIFIER
empty_decl(DECL_SPEC ds, TYPE q, BASE_TYPE bt, TYPE t, CV_SPEC cv, int tok,
	   int mem)
{
	/* Check for empty declarations */
	IDENTIFIER id;
	int have_specifier = 1;
	decl_loc = crt_loc;
	if (ds == dspec_none && bt == btype_none && cv == cv_none) {
		if (IS_NULL_type(q)) {
			if (IS_NULL_type(t)) {
				/* Only semicolon in declaration */
				if (mem) {
					if (tok != lex_func_Hop) {
						/* Allowed after function
						 * definition */
						report(crt_loc, ERR_class_mem_semicolon());
					}
				} else {
					report(crt_loc,
					       ERR_dcl_dcl_semicolon());
				}
				return NULL_id;
			}
			if (have_type_declaration == TYPE_DECL_NONE) {
				/* No type specifier in declaration */
				have_specifier = 0;
			}
		}
	}

	/* Check for definitions of built-in types */
	if ((ds & dspec_typedef) && !mem) {
		BASE_TYPE bs = key_type(tok);
		if (bs) {
			/* Type is now a keyword */
			HASHID nm = KEYWORD(tok);
			id = DEREF_id(hashid_id(nm));
			bt &= ~bs;
			t = complete_pre_type(bt, t, cv, 0);
			report(crt_loc, ERR_lex_key_word(tok));
			crt_id_qualifier = qual_none;
			crt_templ_qualifier = 0;
			id = make_object_decl(ds, t, id, 0);
			return id;
		}
	}

	/* Check for type access declarations */
	if (!have_specifier && mem) {
		if (!IS_NULL_type(t) && IS_type_pre(t)) {
			BASE_TYPE key = DEREF_btype(type_pre_rep(t));
			if (key == btype_alias) {
				IDENTIFIER tid = DEREF_id(type_name(t));
				QUALIFIER qual = DEREF_qual(type_pre_nqual(t));
				if (qual && !IS_NULL_id(tid)) {
					id = access_decl(tid);
					return id;
				}
			}
		}
	}

	/* Perform the declaration */
	t = empty_complete_pre_type(bt, t, cv, 0);
	if (mem) {
		id = empty_member_decl(ds, q, t);
	} else {
		id = empty_object_decl(ds, q, t);
	}
	if (in_weak_param) {
		/* Shouldn't happen in parameter declaration lists */
		report(crt_loc, ERR_dcl_fct_par_none());
	}
	return id;
}


/*
    This routine is called after each external declaration.  d gives
    the number of objects declared and e gives the associated expression
    for an asm definition.  Note that this is the point of instantiation
    for any pending templates.
*/

void
external_declaration(EXP e, int d)
{
	if (crt_file_type == 0) {
		no_declarations += (unsigned long)d;
	}
	if (!IS_NULL_exp(e)) {
		/* Compile any asm definitions */
		compile_asm(e);
	}
	if (!in_preproc_dir) {
		if (crt_access_list.pending) {
			/* Clear any outstanding access checks */
			IGNORE report_access(NULL_id);
		}
		if (!IS_NULL_list(pending_templates)) {
			/* Instantiate any pending templates */
			clear_templates(0);
		}
	}
	return;
}
