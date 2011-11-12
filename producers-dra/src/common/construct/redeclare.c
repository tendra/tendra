/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "err_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "off_ops.h"
#include "nspace_ops.h"
#include "str_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "access.h"
#include "basetype.h"
#include "char.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "compile.h"
#include "constant.h"
#include "copy.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "file.h"
#include "function.h"
#include "identifier.h"
#include "instance.h"
#include "literal.h"
#include "namespace.h"
#include "option.h"
#include "overload.h"
#include "predict.h"
#include "redeclare.h"
#include "syntax.h"
#include "template.h"
#include "tokdef.h"
#include "token.h"
#include "ustring.h"


/*
    CURRENT LINKAGE SPECIFIER

    The current linkage specifier is handled by means of this global
    variable.  The default, of no linkage being given, is interpreted
    according to the source language.
*/

DECL_SPEC crt_linkage = dspec_none;
DECL_SPEC new_linkage = dspec_none;


/*
    FIND A LINKAGE SPECIFIER

    This routine translates the string literal expression e into a linkage
    specifier.  The only recognised strings are "C" and "C++".
*/

DECL_SPEC
find_linkage(EXP e)
{
	STRING s = DEREF_str(exp_string_lit_str(e));
	unsigned kind = DEREF_unsigned(str_simple_kind(s));

	/* Can only occur in namespace scope */
	if (in_function_defn || in_class_defn) {
		report(crt_loc, ERR_dcl_link_scope());
	}

	/* Check the linkage string */
	if (kind == STRING_NONE) {
		char *t = strlit(DEREF_string(str_simple_text(s)));
		unsigned long len = DEREF_ulong(str_simple_len(s));
		if (len == 1 && streq(t, "C")) {
			return dspec_c;
		}
		if (len == 3 && streq(t, "C++")) {
			return dspec_cpp;
		}
	}

	/* Report unknown strings */
	report(crt_loc, ERR_dcl_link_unknown(s));
	return crt_linkage;
}


/*
    FIND A LINKAGE STRING

    This routine returns the string corresponding to the linkage specifiers
    given by ds and cv.
*/

string
linkage_string(DECL_SPEC ds, CV_SPEC cv)
{
	const char *str;
	if ((ds & dspec_c) || (cv & cv_c)) {
		str = "C";
	} else {
		str = "C++";
	}
	return ustrlit(str);
}


/*
    ADJUST DECLARATION SPECIFIER FOR LANGUAGE

    This routine adds the current language specifier to the declaration
    specifier ds.  mem is true for a member declaration (which always
    has C++ linkage).  ds may contain a language specifier from a
    previous declaration, otherwise it is deduced from crt_linkage.
*/

DECL_SPEC
adjust_linkage(DECL_SPEC ds, int mem)
{
	DECL_SPEC rs = (ds & ~dspec_language);
	if (mem) {
		/* Members have C++ linkage */
		rs |= dspec_cpp;
	} else if (rs & dspec_linkage) {
		/* Only applies to objects with linkage */
		DECL_SPEC ln = (ds | crt_linkage);
		if (ln & dspec_c) {
			rs |= dspec_c;
		} else {
			rs |= dspec_cpp;
		}
	}
	return rs;
}


/*
    CHECK C LINKAGE DECLARATIONS

    This routine checks the identifier id declared with C linkage.  Objects
    with C linkage in different namespaces are actually the same.
*/

void
c_linkage(IDENTIFIER id, int def)
{
    TYPE t = NULL_type;
    unsigned tag = TAG_id(id);
    if (tag == id_function_tag) {
	/* Template functions can't have C linkage */
	t = DEREF_type(id_function_type(id));
	if (IS_type_templ(t)) {
	    report(decl_loc, ERR_temp_decl_linkage());
	}
    } else if (tag == id_variable_tag) {
	t = DEREF_type(id_variable_type(id));
    }
    if (!IS_NULL_type(t)) {
	NAMESPACE ns = c_namespace;
	if (!IS_NULL_nspace(ns)) {
	    HASHID nm = DEREF_hashid(id_name(id));
	    MEMBER mem = search_member(ns, nm, 1);
	    IDENTIFIER pid = DEREF_id(member_id(mem));
	    if (!IS_NULL_id(pid) && !EQ_id(id, pid)) {
		NAMESPACE cns = DEREF_nspace(id_parent(id));
		NAMESPACE pns = DEREF_nspace(id_parent(pid));
		if (!EQ_nspace(cns, pns)) {
		    DECL_SPEC cl = crt_linkage;
		    QUALIFIER cq = crt_id_qualifier;
		    DECL_SPEC ds = DEREF_dspec(id_storage(id));
		    crt_linkage = (ds & dspec_language);
		    crt_id_qualifier = qual_none;
		    pid = redecl_id(ds, t, pid, 3, -1);
		    if (!IS_NULL_id(pid)) {
			/* Set up alias */
			if (IS_id_function(pid)) {
			    TYPE s = DEREF_type(id_function_type(pid));
			    s = redecl_func_type(pid, s, t, def, 0);
			    COPY_type(id_function_type(pid), s);
			}
			ds |= dspec_alias;
			COPY_dspec(id_storage(id), ds);
			pid = DEREF_id(id_alias(pid));
			COPY_id(id_alias(id), pid);
			if (do_dump) {
				dump_alias(id, pid, &decl_loc);
			}
			id = pid;
		    }
		    crt_id_qualifier = cq;
		    crt_linkage = cl;
		}
	    }
	    COPY_id(member_id(mem), id);
	}
    }
    return;
}


/*
    FIND A PREVIOUS DECLARATION

    If a declaration in block scope is declared extern then it has external
    linkage unless the declaration matches a visible declaration of namespace
    scope.  This routine finds such a declaration for the identifier id
    of type t.
*/

IDENTIFIER
find_previous(TYPE t, IDENTIFIER id)
{
	if (crt_id_qualifier == qual_none) {
		NAMESPACE ns = nonblock_namespace;
		HASHID nm = DEREF_hashid(id_name(id));
		IDENTIFIER pid = find_extern_id(nm, ns, 0);
		if (!IS_NULL_id(pid)) {
			TYPE s;
			DECL_SPEC st;
			switch (TAG_id(pid)) {
			case id_variable_tag:
				/* Variables may be redeclared */
				s = DEREF_type(id_variable_type(pid));
				break;
			case id_function_tag: {
				/* Functions may be redeclared */
#if LANGUAGE_CPP
				int eq = 0;
				LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
				pid = resolve_func(pid, t, 0, 0, pids, &eq);
				if (IS_NULL_id(pid)) {
					return NULL_id;
				}
				if (!IS_id_function(pid)) {
					return NULL_id;
				}
#endif
				s = DEREF_type(id_function_type(pid));
				break;
			}
			default:
				/* Nothing else can be redeclared */
				return NULL_id;
			}
			st = DEREF_dspec(id_storage(pid));
			if (st & dspec_linkage) {
				/* Previous declaration must have linkage */
				s = type_composite(s, t, 0, 0, KILL_err, 0);
				if (!IS_NULL_type(s)) {
					return pid;
				}
			}
		}
	}
	return NULL_id;
}


/*
    UNIFY AN EXTERNAL IDENTIFIER

    This routine checks the identifier id, which is a variable declared
    extern in a block, against conflicts with the namespace ns into
    which it is injected.  p gives all the other extern block identifiers
    declared before id.  The routine returns any previous identifier.
*/

IDENTIFIER
unify_extern(IDENTIFIER id, TYPE t, NAMESPACE ns, LIST(IDENTIFIER) p)
{
	IDENTIFIER pid = NULL_id;
	HASHID nm = DEREF_hashid(id_name(id));
	LIST(IDENTIFIER) pids = NULL_list(IDENTIFIER);
	while (!IS_NULL_list(p)) {
		/* Check other block externs */
		IDENTIFIER bid = DEREF_id(HEAD_list(p));
		HASHID bnm = DEREF_hashid(id_name(bid));
		if (EQ_hashid(bnm, nm)) {
			bid = DEREF_id(id_alias(bid));
			CONS_id(bid, pids, pids);
		}
		p = TAIL_list(p);
	}
	if (!IS_NULL_nspace(ns)) {
		/* Check actual namespace */
		MEMBER mem = search_member(ns, nm, 0);
		if (!IS_NULL_member(mem)) {
			IDENTIFIER bid = DEREF_id(member_id(mem));
			if (!IS_NULL_id(bid)) {
				bid = DEREF_id(id_alias(bid));
				CONS_id(bid, pids, pids);
			}
		}
	}
	if (!IS_NULL_list(pids)) {
		/* Match found */
		if (IS_NULL_type(t)) {
			if (IS_NULL_list(TAIL_list(pids))) {
				pid = DEREF_id(HEAD_list(pids));
				DESTROY_list(pids, SIZE_id);
			} else {
				DECL_SPEC ds;
				pids = REVERSE_list(pids);
				ds = find_ambig_dspec(pids);
				MAKE_id_ambig(nm, ds, ns, crt_loc, pids, 1,
					      pid);
			}
		} else {
			LIST(IDENTIFIER) qids;
			DECL_SPEC cl = crt_linkage;
			QUALIFIER cq = crt_id_qualifier;
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			crt_linkage = (ds & dspec_language);
			crt_id_qualifier = qual_none;
			DEREF_loc(id_loc(id), decl_loc);
			pids = REVERSE_list(pids);
			qids = pids;
			while (!IS_NULL_list(qids)) {
				IDENTIFIER qid = DEREF_id(HEAD_list(qids));
				qid = DEREF_id(id_alias(qid));
				if (IS_type_func(t)) {
					/* Check function redeclaration */
					IDENTIFIER over = NULL_id;
					unsigned tag = TAG_id(id);
					qid = redecl_func(ds, t, qid, tag,
							  &over, -1);
				} else {
					/* Check variable redeclaration */
					qid = redecl_id(ds, t, qid, 0, -1);
				}
				if (!IS_NULL_id(qid)) {
					pid = qid;
				}
				qids = TAIL_list(qids);
			}
			DESTROY_list(pids, SIZE_id);
			crt_id_qualifier = cq;
			crt_linkage = cl;
		}
	}
	return pid;
}


/*
    UNIFY A BLOCK DECLARATION WITH A PREVIOUS DECLARATION

    This routine is used to unify the external block declaration id of
    type t with its previous declaration pid (as returned by find_previous).
    def is true is id is a function definition.  The routine returns id.
    If there is no previous declaration then one is created and added to
    the extra identifier list of the enclosing non-block namespace.
*/

IDENTIFIER
unify_previous(IDENTIFIER id, TYPE t, IDENTIFIER pid, int def)
{
	/* Unify external linkage */
	if (IS_NULL_id(pid)) {
		LIST(IDENTIFIER) p;
		NAMESPACE ns = nonblock_namespace;
		p = DEREF_list(nspace_named_etc_extra(ns));
		pid = unify_extern(id, t, ns, p);
		if (IS_NULL_id(pid)) {
			if (!is_templ_depend(t)) {
				/* Declare new external object */
				DECL_SPEC ds;
				pid = copy_id(id, 0);
				ds = DEREF_dspec(id_storage(pid));
				if (!(ds & dspec_linkage)) {
					ds |= dspec_extern;
				}
				ds &= ~dspec_alias;
				COPY_dspec(id_storage(pid), ds);
				COPY_nspace(id_parent(pid), ns);
				COPY_id(id_alias(pid), pid);
				CONS_id(pid, p, p);
				COPY_list(nspace_named_etc_extra(ns), p);
			}

			/* Check object type */
			if (!is_global_type(t)) {
				report(crt_loc, ERR_basic_link_none(t, id));
			}
		}
	}

	/* Alias id to be pid */
	if (!IS_NULL_id(pid)) {
		if (IS_id_function_etc(pid)) {
			TYPE s = DEREF_type(id_function_etc_type(pid));
			s = redecl_func_type(pid, s, t, def, 0);
			COPY_type(id_function_etc_type(pid), s);
		}
		pid = DEREF_id(id_alias(pid));
		COPY_id(id_alias(id), pid);
	}
	return id;
}


/*
    UNIFY A DECLARATION WITH A PREVIOUS BLOCK DECLARATION

    This routine is used to unify the external declaration id of type
    t with any previous external block declaration of the same object.
    def is true if id is a function definition.  The routine returns id.
*/

IDENTIFIER
unify_subsequent(IDENTIFIER id, TYPE t, int def)
{
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	if (IS_nspace_named_etc(ns)) {
		LIST(IDENTIFIER) p;
		p = DEREF_list(nspace_named_etc_extra(ns));
		if (!IS_NULL_list(p)) {
			IDENTIFIER pid = unify_extern(id, t, NULL_nspace, p);
			if (!IS_NULL_id(pid)) {
				/* Alias id to be pid */
				if (IS_id_function_etc(pid)) {
					TYPE s = DEREF_type(id_function_etc_type(pid));
					s = redecl_func_type(pid, s, t, def, 0);
					COPY_type(id_function_etc_type(pid), s);
				}
				pid = DEREF_id(id_alias(pid));
				COPY_id(id_alias(id), pid);
			}
		}
	}
	return id;
}


/*
    CHECK FOR CLASS-LIKE TYPEDEF NAMES

    This routine checks whether the typedef name id behaves like a class
    or an object with respect to name hiding.  It is not entirely clear
    whether it is just original class and enumeration names or all class
    and enumeration names (including those introduced using typedef)
    which behave in this way.
*/

int
is_tagged_type(IDENTIFIER id)
{
	switch (TAG_id(id)) {
	case id_class_name_tag:
	case id_enum_name_tag:
		/* Original class and enumeration names */
		return 1;
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag:
		/* Type aliases */
		return 0;
	}
	return 0;
}


/*
    REPORT AN OVERLOADIN ERROR

    This routine reports the overloading error err for the function id
    which cannot be overloaded for the reason corresponding to reason.
    It returns the severity of the error.
*/

static int
overload_error(IDENTIFIER id, ERROR err, int reason)
{
	int sev = ERROR_NONE;
	switch (reason) {
	case 1:
		/* Two functions with C linkage */
		err = concat_error(err, ERR_dcl_link_over());
		break;
	case 2:
		/* Two functions with indistinguishable parameters */
		err = concat_error(err, ERR_over_load_pars());
		break;
	case 3: {
		/* Two objects with C linkage */
		PTR(LOCATION)loc = id_loc(id);
		HASHID nm = DEREF_hashid(id_name(id));
		err = concat_error(err, ERR_dcl_link_redecl(nm, loc));
		break;
	}
	}

	if (!IS_NULL_err(err)) {
		sev = DEREF_int(err_severity(err));
		report(decl_loc, err);
	}
	return sev;
}


/*
    REDECLARE AN OBJECT IDENTIFIER

    This routine checks the redeclaration of the identifier id as an object
    with declaration specifiers ds and type t.  It returns id for a valid
    redeclaration and the null identifier otherwise, reporting any errors
    if necessary.  Note that it is possible to reserve an identifier using
    the reserve declaration specifier.  At present this is only done for
    the fields of an anonymous union and enumerators.  Also a class or
    enumeration name can be hidden by an object in the same scope.  A
    redeclared identifier will be marked as defined according to whether
    the redeclaration is a definition.  Whether the initial declaration
    was a definition may be determined from the initialiser expression.
*/

IDENTIFIER
redecl_id(DECL_SPEC ds, TYPE t, IDENTIFIER id, int reason, int def)
{
	TYPE s;
	DECL_SPEC ln;
	PTR(TYPE) pt;
	int changed = 0;
	int is_member = 0;
	int is_function = 0;
	ERROR err = NULL_err;
	DECL_SPEC ds_old, ln_old;

	/* Check previous definition */
	switch (TAG_id(id)) {
	case id_variable_tag:
		/* Variables may be redeclared */
		pt = id_variable_type(id);
		break;
	case id_function_tag:
		/* Functions may be redeclared */
		is_function = 1;
		pt = id_function_type(id);
		break;
	case id_class_name_tag:
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Unqualified class and enumeration names can be hidden */
		PTR(LOCATION)loc;
		if (!is_tagged_type(id)) {
			loc = id_loc(id);
			report(decl_loc, ERR_basic_odr_diff(id, loc));
			return NULL_id;
		}
		if (crt_id_qualifier == qual_none) {
			/* Check for templates */
			ds_old = DEREF_dspec(id_storage(id));
			if (!(ds_old & dspec_template)) {
				return NULL_id;
			}
		}
		loc = id_loc(id);
		report(decl_loc, ERR_basic_odr_diff(id, loc));
		return NULL_id;
	}
	case id_stat_member_tag:
		/* Members may be defined outside their class */
		is_member = 1;
		if (crt_id_qualifier == qual_none) {
			goto error_lab;
		}
		pt = id_stat_member_type(id);
		break;
	case id_mem_func_tag:
	case id_stat_mem_func_tag:
		/* Members may be defined outside their class */
		is_member = 1;
		is_function = 1;
		if (crt_id_qualifier == qual_none) {
			goto error_lab;
		}
		pt = id_function_etc_type(id);
		break;
	case id_member_tag:
		/* Non-static members cannot be redeclared */
		is_member = 1;
		if (crt_id_qualifier == qual_none) {
			goto error_lab;
		}
		report(decl_loc, ERR_class_mem_def(id));
		return NULL_id;
	case id_token_tag:
		/* Allow for token definitions */
		return NULL_id;
	case id_undef_tag:
	case id_ambig_tag:
		/* Allow for error propagation */
		return NULL_id;
	default:
error_lab:
		/* No other identifiers can be redeclared */
		if (is_member) {
			/* Member redeclaration */
			err = ERR_class_mem_redecl(id, id_loc(id));
		} else {
			/* Object redeclaration */
			err = ERR_basic_odr_decl(id, id_loc(id));
		}
		IGNORE overload_error(id, err, reason);
		return NULL_id;
	}

	/* Check declaration specifiers */
	ds_old = DEREF_dspec(id_storage(id));
	if ((ds | ds_old) & dspec_reserve) {
		/* Reserved names can't be redeclared */
		reason = 0;
		goto error_lab;
	}

	/* Check for objects with no linkage */
	ln = (ds & dspec_linkage);
	ln_old = (ds_old & dspec_linkage);
	if (ln == dspec_none || ln_old == dspec_none) {
		/* Can't redeclare objects with no linkage */
		if (!is_function) {
			reason = 0;
			goto error_lab;
		}
	}

	/* Check previous type */
	s = DEREF_type(pt);
	s = check_compatible(s, t, 0, &err, 1);
	if (!IS_NULL_err(err)) {
		/* Incompatible declaration */
		PTR(LOCATION) loc = id_loc(id);
		err = concat_error(err, ERR_basic_link_decl_type(id, loc));
		if ((ds | ds_old) & dspec_token) {
			/* Allow for interface declarations */
			err = set_severity(err, OPT_interf_incompat, -1);
		}
		if (overload_error(id, err, reason) == ERROR_SERIOUS) {
			return NULL_id;
		}
	}
	if (is_function) {
		/* Sanity check for error types */
		if (type_tag(s) != type_func_tag) {
			return NULL_id;
		}
	} else {
		if (type_tag(s) == type_func_tag) {
			return NULL_id;
		}
	}
	if (def >= 0) {
		COPY_type(pt, s);
	}

	/* Check for redeclaration of aliases */
	if ((ds | ds_old) & dspec_alias) {
		PTR(LOCATION) loc = id_loc(id);
		report(decl_loc, ERR_dcl_nspace_udecl_redecl(id, loc));
	}

	/* Check for inconsistent linkage */
	if (ln != ln_old) {
		ERROR err1;
		DECL_SPEC ln_new;
		PTR(LOCATION) loc = id_loc(id);
		if (ln_old == dspec_static) {
			err1 = ERR_dcl_stc_internal(id, loc);
		} else {
			err1 = ERR_dcl_stc_external(id, loc);
			if (is_member) {
				/* Members have external linkage */
				ERROR err2 = ERR_basic_link_mem_extern(id);
				err1 = concat_error(err2, err1);
			}
		}
		if (reason == 3) {
			/* Identification of objects with C linkage */
			HASHID nm = DEREF_hashid(id_name(id));
			ERROR err2 = ERR_dcl_link_redecl(nm, loc);
			err1 = concat_error(err1, err2);
		}
		if (def == -1 && option(OPT_link_internal) == OPTION_OFF) {
			ln_new = dspec_extern;
		} else {
			ln_new = dspec_static;
		}
		ds_old = (ln_new | (ds_old & ~dspec_linkage));
		report(decl_loc, err1);
		changed = 1;
	}

	/* Check language specifier */
	ln = crt_linkage;
	if (ln != dspec_none) {
		/* Check against the current language */
		ln_old = (ds_old & dspec_language);
		if ((ds_old & dspec_extern) && ln != ln_old) {
			/* Report inconsistent linkage */
			if (!is_member) {
				/* Should this only apply to functions? */
				PTR(LOCATION) loc = id_loc(id);
				string lang = linkage_string(ln_old, cv_none);
				report(decl_loc,
				       ERR_dcl_link_lang(id, lang, loc));
				ds_old = adjust_linkage(ds_old, is_member);
				changed = 1;
			}
		}
	}

	/* Check for inline specifier */
	if (ds & dspec_inline) {
		ds_old |= dspec_inline;
		changed = 1;
	}

	/* Mark whether this declaration is a definition */
	if (def >= 0) {
		if (ds & dspec_defn) {
			ds_old |= dspec_defn;
		} else {
			ds_old &= ~dspec_defn;
		}
	}

	/* Compatible redeclaration */
	COPY_dspec(id_storage(id), ds_old);
	if (changed) {
		update_tag(id, 0);
	}
	return id;
}


/*
    REDECLARE A FUNCTION IDENTIFIER

    This routine is similar to redecl_id except that it allows for function
    overloading.  As before it returns id if this is a redeclaration of an
    existing function, and the null identifier otherwise.  However in the
    latter case any functions overloaded by the declaration are returned
    via over.
*/

IDENTIFIER
redecl_func(DECL_SPEC ds, TYPE t, IDENTIFIER id, unsigned tag,
	    IDENTIFIER *over, int def)
{
	int reason = 0;
	IDENTIFIER fid = id;
#if LANGUAGE_CPP
	if (IS_id_function_etc(fid)) {
		DECL_SPEC ds_old;
		*over = fid;

		/* Scan through overloaded functions for a match */
		while (!IS_NULL_id(fid)) {
			int m;
			TYPE s;
			int mq = 1;
			if ((ds & dspec_extern) && crt_linkage == dspec_c) {
				/* Two functions with C linkage are the same */
				ds_old = DEREF_dspec(id_storage(fid));
				if ((ds_old & dspec_c) && IS_id_function(fid)) {
					reason = 1;
					break;
				}
			}

			/* Two functions with the same parameters are the
			 * same */
			s = DEREF_type(id_function_etc_type(fid));
			if (tag == id_stat_mem_func_tag) {
				mq = 0;
			}
			if (IS_id_stat_mem_func(fid)) {
				mq = 0;
			}
			m = eq_func_type(t, s, mq, 0);
			if (m) {
				/* Function types basically match */
				if (m == 1) {
					/* Return types don't match */
					reason = 2;
				}
				break;
			}
			fid = DEREF_id(id_function_etc_over(fid));
		}

		if (IS_NULL_id(fid)) {
			/* No match found */
			IDENTIFIER tid = find_template(id, 0);
			if (!IS_NULL_id(tid)) {
				/* Must have match with template
				 * specialisation */
				report(decl_loc, ERR_temp_spec_type(t, id));
				return NULL_id;
			}
			if (crt_id_qualifier != qual_none) {
				/* Must have match with qualified identifier */
				if (def == -2 && tag == id_function_tag) {
					/* Allow for name injection */
					/* EMPTY */
				} else {
					report(decl_loc,
					       ERR_basic_link_unmatch(t, id));
				}
				return NULL_id;
			}
			if (reason == 0) {
				return NULL_id;
			}
			fid = id;
		}

		/* Match found */
		ds_old = DEREF_dspec(id_storage(fid));
		if ((ds_old & dspec_implicit) && !(ds & dspec_implicit)) {
			if (IS_id_mem_func(fid)) {
				/* Matches implicitly declared member
				 * function */
				report(decl_loc, ERR_class_special_decl(fid));
				return NULL_id;
			}
		}
		if (ds_old & dspec_inherit) {
			/* Inherited functions (including aliases) are hidden */
			return NULL_id;
		}
		/* *over = NULL_id ; */
	}
#else
	/* Don't check overloading in C */
	*over = NULL_id;
	UNUSED(tag);
#endif

	/* Redeclare id */
	fid = redecl_id(ds, t, fid, reason, def);
	if (!IS_NULL_id(fid)) {
		TYPE form = DEREF_type(id_function_etc_form(id));
		if (def >= 0) {
			/* Allow for default arguments etc. */
			TYPE s = DEREF_type(id_function_etc_type(fid));
			s = redecl_func_type(fid, s, t, def, 1);
			COPY_type(id_function_etc_type(fid), s);
		}
		if (!IS_NULL_type(form) && IS_type_token(form)) {
			IDENTIFIER ext = DEREF_id(type_token_tok(form));
			if (!IS_NULL_id(ext) && IS_id_token(ext)) {
				/* Check for tokenised functions */
				ds = DEREF_dspec(id_storage(ext));
				ds |= dspec_explicit;
				COPY_dspec(id_storage(ext), ds);
				if (def) {
					/* Check for token definitions */
					IGNORE define_func_token(ext, fid);
					if (ds & dspec_pure) {
						report(decl_loc,
						       ERR_token_def_not(ext));
					}
				}
			}
		}
	}
	return fid;
}


/*
    REDECLARE AN INHERITED OR ALIASED MEMBER

    This routine is used to allow for declarations of class members to
    override any inherited value of the member.  id gives the inherited
    value, mem is true for a member declaration, fn is true for a function
    declaration or a declaration which can't coexist with a function
    declaration.  The null identifier is returned to indicate that id is
    to be overridden.
*/

IDENTIFIER
redecl_inherit(IDENTIFIER id, QUALIFIER qual, int mem, int fn)
{
	if (!IS_NULL_id(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_alias) {
			if (fn && IS_id_function_etc(id)) {
				/* Everything is a function */
				return id;
			}
			if (mem && IS_id_class_name(id)) {
				/* Allow for injected type names */
				if (ds & dspec_implicit) {
					return id;
				}
			}
			if (qual == qual_none) {
				/* New declaration */
				PTR(LOCATION) loc = id_loc(id);
				report(decl_loc,
				       ERR_dcl_nspace_udecl_multi(id, loc));
				return NULL_id;
			}
		}
		if (ds & dspec_inherit) {
			NAMESPACE ns;
			if (mem) {
				return NULL_id;
			}
			ns = DEREF_nspace(id_parent(id));
			id = DEREF_id(id_alias(id));
			report(decl_loc, ERR_lookup_qual_decl(id, ns));
		}
	}
	return id;
}


/*
    COPY AN IDENTIFIER

    This routine creates a copy of the identifier id.  If type is 1
    then any type components in id are copied using copy_typedef, if it
    is 2 they are further expanded using expand_type.
*/

IDENTIFIER
copy_id(IDENTIFIER id, int type)
{
	TYPE t;
	ulong no;
	ulong dno;
	HASHID nm;
	unsigned tag;
	LOCATION loc;
	NAMESPACE ns;
	DECL_SPEC ds;
	IDENTIFIER lid;
	IDENTIFIER cid = id;

	/* Examine various cases */
	if (IS_NULL_id(cid)) {
		return NULL_id;
	}
	tag = TAG_id(cid);
	switch (tag) {
	case id_class_name_tag:
	case id_class_alias_tag:
	case id_enum_name_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Types */
		BASE_TYPE bt;
		DECONS_id_class_name_etc(nm, ds, ns, loc, lid, no, dno, t, bt,
					 cid);
		if (type) {
			t = copy_typedef(cid, t, cv_none);
			if (type == 2) {
				t = expand_type(t, 1);
				if (tag == id_class_name_tag) {
					/* Name already copied by copy_class */
					CLASS_TYPE ct;
					while (IS_type_templ(t)) {
						t = DEREF_type(type_templ_defn(t));
					}
					ct = DEREF_ctype(type_compound_defn(t));
					cid = DEREF_id(ctype_name(ct));
					if (!EQ_id(cid, id)) {
						COPY_hashid(id_name(cid), nm);
						COPY_dspec(id_storage(cid), ds);
						COPY_nspace(id_parent(cid), ns);
						COPY_loc(id_loc(cid), loc);
						break;
					}
				}
				if (tag != id_enum_name_tag) {
					/* Find type alias tag */
					unsigned ta = type_tag(t);
					if (ta == type_compound_tag) {
						tag = id_class_alias_tag;
					} else if (ta == type_enumerate_tag) {
						tag = id_enum_alias_tag;
					} else {
						tag = id_type_alias_tag;
					}
				}
			}
		}
		MAKE_id_class_name_etc(tag, nm, ds, ns, loc, t, cid);
		COPY_btype(id_class_name_etc_rep(cid), bt);
		break;
	}
	case id_variable_tag:
	case id_parameter_tag:
	case id_stat_member_tag: {
		/* Objects */
		EXP a, b;
		DECONS_id_variable_etc(nm, ds, ns, loc, lid, no, dno, t,
				       a, b, cid);
		if (type) {
			t = copy_typedef(cid, t, cv_none);
			if (type == 2) {
				t = expand_type(t, 1);
			}
		}
		MAKE_id_variable_etc(tag, nm, ds, ns, loc, t, cid);
		COPY_exp(id_variable_etc_init(cid), a);
		COPY_exp(id_variable_etc_term(cid), b);
		break;
	}
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Functions */
		EXP a;
		TYPE form;
		IDENTIFIER over;
		LIST(CLASS_TYPE)fr;
		DECONS_id_function_etc(nm, ds, ns, loc, lid, no, dno, t,
				       over, form, fr, a, cid);
		if (type) {
			t = copy_typedef(cid, t, cv_none);
			if (type == 2) {
				t = expand_type(t, 1);
			}
		}
		MAKE_id_function_etc(tag, nm, ds, ns, loc, t, over, cid);
		COPY_type(id_function_etc_form(cid), form);
		COPY_exp(id_function_etc_defn(cid), a);
		if (type == 2) {
			/* Copy friend classes */
			while (!IS_NULL_list(fr)) {
				TYPE r = NULL_type;
				CLASS_TYPE cr = DEREF_ctype(HEAD_list(fr));
				cr = expand_ctype(cr, 2, &r);
				friend_function(cr, cid, 0);
				fr = TAIL_list(fr);
			}
		} else {
			COPY_list(id_function_etc_chums(cid), fr);
		}
		break;
	}
	case id_member_tag: {
		/* Members */
		GRAPH gr;
		OFFSET off;
		DECONS_id_member(nm, ds, ns, loc, lid, no, dno, t, off, gr,
				 cid);
		if (type) {
			t = copy_typedef(cid, t, cv_none);
			if (type == 2) {
				if (IS_hashid_anon(nm)) {
					/* Allow for anonymous bitfields */
					expand_anon_bitfield = 1;
				}
				t = expand_type(t, 1);
				expand_anon_bitfield = 0;
			}
		}
		MAKE_id_member(nm, ds, ns, loc, t, cid);
		COPY_graph(id_member_base(cid), gr);
		COPY_off(id_member_off(cid), off);
		break;
	}
	case id_enumerator_tag: {
		/* Enumerators */
		EXP a;
		ERROR err = NULL_err;
		DECONS_id_enumerator(nm, ds, ns, loc, lid, no, dno, t, a, cid);
		if (type == 2) {
			/* Copy enumerator value */
			TYPE s = expand_type(t, 1);
			a = copy_exp(a, t, s);
			IGNORE make_nat_exp(a, &err);
			t = s;
		}
		MAKE_id_enumerator(nm, ds, ns, loc, t, a, cid);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_dcl_enum_const(cid));
			report(crt_loc, err);
		}
		break;
	}
	case id_token_tag: {
		/* Tokens */
		TOKEN sort;
		IDENTIFIER alt;
		DECONS_id_token(nm, ds, ns, loc, lid, no, dno, sort, alt, cid);
		if (type == 2) {
			/* Expand token sort */
			sort = expand_sort(sort, 1, 1);
		}
		MAKE_id_token(nm, ds, ns, loc, sort, alt, cid);
		break;
	}
	default:
		/* Don't copy other identifiers */
		return cid;
	}

	if (type != 2) {
		COPY_id(id_alias(cid), lid);
		COPY_ulong(id_no(cid), no);
		COPY_ulong(id_dump(cid), dno);
	}
	return cid;
}


/*
    CREATE AN IDENTIFIER ALIAS

    This routine creates an alias for the identifier id in the namespace
    ns.  fn gives a list of function which the alias will overload if
    it is a function.
*/

IDENTIFIER
alias_id(IDENTIFIER id, NAMESPACE ns, IDENTIFIER fn, int rec)
{
	IDENTIFIER cid = copy_id(id, 1);
	if (!EQ_id(cid, id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(cid));
		DECL_SPEC acc = (ds & dspec_access);
		if (acc) {
			IDENTIFIER sid = DEREF_id(nspace_name(ns));
			immediate_access(sid, cid);
		}
		ds = ((ds & ~dspec_access) | dspec_alias | crt_access);
		COPY_dspec(id_storage(cid), ds);
		COPY_nspace(id_parent(cid), ns);
		if (do_dump) {
			dump_alias(cid, id, &crt_loc);
		}
		if (IS_id_function_etc(cid)) {
			/* Deal with overloaded functions */
			IDENTIFIER over;
			if (rec) {
				over = DEREF_id(id_function_etc_over(cid));
				if (IS_NULL_id(over)) {
					over = fn;
				} else {
					over = alias_id(over, ns, fn, rec);
				}
			} else {
				over = fn;
			}
			COPY_id(id_function_etc_over(cid), over);
		}
	}
	return cid;
}


/*
    DUMMY DECLARATION SPECIFIER

    This value is used as a dummy declaration specifier in the adjusting
    of overloaded functions.
*/

#define dspec_mark	((DECL_SPEC)0x7fffffff)


/*
    REMOVE HIDDEN FUNCTIONS

    This routine adjusts the set of overloaded functions id by removing
    any with storage field equal to dspec_mark.
*/

static IDENTIFIER
remove_functions(IDENTIFIER id)
{
	if (!IS_NULL_id(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		IDENTIFIER over = DEREF_id(id_function_etc_over(id));
		over = remove_functions(over);
		if (ds == dspec_mark) {
			id = over;
		} else {
			COPY_id(id_function_etc_over(id), over);
		}
	}
	return id;
}


/*
    COMPARE HIDING FUNCTIONS

    This routine compares two functions id and over, one declared in the
    normal fashion and the other by a using-declaration.  It returns
    true if the former overrides the latter.
*/

static int
compare_functions(IDENTIFIER id, IDENTIFIER over, int mem)
{
	TYPE t = DEREF_type(id_function_etc_type(id));
	TYPE s = DEREF_type(id_function_etc_type(over));
	int eq = eq_func_type(t, s, 1, 0);
	if (eq) {
		/* Equal parameter types */
		if (mem) {
			return 1;
		}
	}
	if (eq >= 2) {
		/* Equal types */
		PTR(LOCATION)loc = id_loc(over);
		report(crt_loc, ERR_dcl_nspace_udecl_multi(over, loc));
		return 1;
	}
	return 0;
}


/*
    MARK HIDDEN FUNCTIONS

    This routine marks any functions which hide, or are hidden by, id in
    its set of overloaded functions.  mem is true for member functions.
    Any hidden function is marked by setting its storage field to the
    value dspec_mark.
*/

static int
mark_functions(IDENTIFIER id, int mem)
{
    int ret = 0;
    DECL_SPEC ds = DEREF_dspec(id_storage(id));
    if (ds != dspec_mark) {
	IDENTIFIER over = DEREF_id(id_function_etc_over(id));
	while (!IS_NULL_id(over)) {
	    DECL_SPEC pds = DEREF_dspec(id_storage(over));
	    if (pds != dspec_mark) {
		if (ds & dspec_alias) {
		    if (pds & dspec_alias) {
			/* Both are using declarations */
			IDENTIFIER a = DEREF_id(id_alias(id));
			IDENTIFIER b = DEREF_id(id_alias(over));
			if (EQ_id(a, b)) {
			    /* Duplicate declarations */
			    if (mem) {
				ERROR err;
				PTR(LOCATION) loc = id_loc(over);
				err = ERR_class_mem_redecl(over, loc);
				report(crt_loc, err);
			    }
			    COPY_dspec(id_storage(over), dspec_mark);
			    ret++;
			}
		    } else {
			/* The first is a using declaration */
			if (compare_functions(id, over, mem)) {
			    COPY_dspec(id_storage(id), dspec_mark);
			    ret++;
			}
		    }
		} else if (pds & dspec_alias) {
		    /* The second is a using declaration */
		    if (compare_functions(id, over, mem)) {
			COPY_dspec(id_storage(over), dspec_mark);
			ret++;
			break;
		    }
		}
	    }
	    over = DEREF_id(id_function_etc_over(over));
	}
    }
    return ret;
}


/*
    HANDLE HIDDEN FUNCTIONS WITH USING DECLARATIONS

    The interaction of using declarations with the hiding and overriding
    of member functions is somewhat complex.  It is implemented by this
    routine which adjusts the declarations of the overloaded functions id
    up to the existing declarations over.  mem is true for member functions.
*/

IDENTIFIER
hide_functions(IDENTIFIER id, IDENTIFIER over, int mem)
{
	if (!IS_NULL_id(over)) {
		int marked = 0;
		IDENTIFIER pid = id;
		while (!EQ_id(pid, over)) {
			marked += mark_functions(pid, mem);
			pid = DEREF_id(id_function_etc_over(pid));
		}
		if (marked) {
			id = remove_functions(id);
		}
		pid = id;
		while (!IS_NULL_id(pid)) {
			/* Mark template functions */
			DECL_SPEC ds = DEREF_dspec(id_storage(pid));
			if (ds & dspec_template) {
				templ_func_decl(id);
				break;
			}
			pid = DEREF_id(id_function_etc_over(pid));
		}
	}
	return id;
}


/*
    CHECK THE VISIBILITY OF AN IDENTIFIER

    A member name in a using declaration should be visible from a direct
    base class.  This routine checks whether the member id meets this
    criterion by comparing it with its look-up in the direct base
    classes, pid.
*/

static int
using_visible(IDENTIFIER id, IDENTIFIER pid)
{
	while (!IS_NULL_id(pid)) {
		IDENTIFIER qid = DEREF_id(id_alias(pid));
		if (EQ_id(qid, id)) {
			return 1;
		}
		switch (TAG_id(pid)) {
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag:
			/* Check overloaded functions */
			pid = DEREF_id(id_function_etc_over(pid));
			break;
		case id_ambig_tag: {
			/* Check ambiguous identifiers */
			LIST(IDENTIFIER)pids;
			pids = DEREF_list(id_ambig_ids(pid));
			while (!IS_NULL_list(pids)) {
				pid = DEREF_id(HEAD_list(pids));
				if (using_visible(id, pid)) {
					return 1;
				}
				pids = TAIL_list(pids);
			}
			return 0;
		}
		default:
			/* Other identifiers */
			return 0;
		}
	}
	return 0;
}


/*
    PROCESS A CLASS USING DECLARATION

    This routine processes a using-declaration of the identifier id in
    the case when this declaration is a member-declaration.
*/

static IDENTIFIER
using_member(IDENTIFIER id, int type)
{
	MEMBER mem;
	IDENTIFIER aid;
	IDENTIFIER pid;

	/* Check the identifier */
	NAMESPACE cns = crt_namespace;
	HASHID nm = DEREF_hashid(id_name(id));
	GRAPH gr = is_subfield(cns, id);
	if (IS_NULL_graph(gr)) {
		/* id is not a member of a base class */
		CLASS_TYPE ct = crt_class;
		report(crt_loc, ERR_dcl_nspace_udecl_base(id, ct));
		return NULL_id;
	} else {
		GRAPH gu = DEREF_graph(graph_up(gr));
		GRAPH gt = DEREF_graph(graph_top(gr));
		if (EQ_graph(gt, gr)) {
			/* id is a member of the current class */
			report(crt_loc, ERR_dcl_nspace_udecl_mem(id));
			return id;
		}
		if (!EQ_graph(gt, gu)) {
			/* Not a member of a direct base class */
			IDENTIFIER bid = search_base_field(cns, nm, type, 0);
			aid = id;
			while (!IS_NULL_id(aid)) {
				IDENTIFIER qid = find_template(aid, 1);
				if (IS_NULL_id(qid)) {
					qid = aid;
				}
				qid = DEREF_id(id_alias(qid));
				if (!using_visible(qid, bid)) {
					CLASS_TYPE ct = crt_class;
					report(crt_loc, ERR_dcl_nspace_udecl_vis(aid, ct));
					break;
				}
				if (!IS_id_function_etc(aid)) {
					break;
				}
				aid = DEREF_id(id_function_etc_over(aid));
			}
		}
	}

	/* Check declarations */
	mem = search_member(cns, nm, 1);
	if (type) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_template) {
			pid = DEREF_id(member_id(mem));
		} else {
			pid = type_member(mem, 3);
		}
	} else {
		pid = DEREF_id(member_id(mem));
		if (!IS_NULL_id(pid) && is_tagged_type(pid)) {
			/* Allow hiding of non-template classes */
			DECL_SPEC ds = DEREF_dspec(id_storage(pid));
			if (!(ds & dspec_template)) {
				pid = NULL_id;
			}
		}
	}
	if (!IS_NULL_id(pid)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(pid));
		if ((ds & dspec_inherit) && !(ds & dspec_alias)) {
			/* Ignore inherited members */
			pid = NULL_id;
		} else {
			IDENTIFIER rid = DEREF_id(id_alias(id));
			IDENTIFIER qid = DEREF_id(id_alias(pid));
			if (EQ_id(rid, qid)) {
				/* Redeclaration of existing meaning */
				if (!type) {
					PTR(LOCATION)loc = id_loc(pid);
					ERROR err =
					    ERR_class_mem_redecl(pid, loc);
					report(crt_loc, err);
				}
				adjust_access(pid, crt_access, 1);
				return pid;
			}
			if (IS_id_function_etc(id) && IS_id_function_etc(pid)) {
				/* Both new and old meanings are functions */
				/* EMPTY */
			} else {
				/* One meaning is not a function */
				PTR(LOCATION) loc = id_loc(pid);
				ERROR err =
				    ERR_dcl_nspace_udecl_multi(pid, loc);
				report(crt_loc, err);
				return NULL_id;
			}
		}
	}

	/* Find inherited member */
	id = search_subfield(cns, gr, id);
	aid = alias_id(id, cns, pid, 1);
	if (!IS_NULL_id(pid)) {
		/* Deal with function hiding */
		aid = hide_functions(aid, pid, 1);
	}
	adjust_access(id, crt_access, 1);
	if (type) {
		set_type_member(mem, aid);
	} else {
		set_member(mem, aid);
	}
	return aid;
}


/*
    PROCESS A NAMESPACE USING DECLARATION

    This routine processes a using-declaration of the identifier id in
    the case when this declaration is not a member-declaration.
*/

static IDENTIFIER
using_name(IDENTIFIER id)
{
	int type;
	HASHID nm;
	MEMBER mem;
	IDENTIFIER pid;

	/* Check the identifier */
	NAMESPACE cns = crt_namespace;
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	if (IS_nspace_ctype(ns)) {
		/* id denotes a class member */
		report(crt_loc, ERR_dcl_nspace_udecl_id(id));
		switch (TAG_id(id)) {
		case id_member_tag:
		case id_stat_member_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag:
			/* Don't even try in these cases */
			return NULL_id;
		}
	}

	/* Check declarations */
	nm = DEREF_hashid(id_name(id));
	mem = search_member(cns, nm, 1);
	type = is_tagged_type(id);
	if (type) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_template) {
			pid = DEREF_id(member_id(mem));
		} else {
			pid = type_member(mem, 3);
		}
	} else {
		pid = DEREF_id(member_id(mem));
		if (!IS_id_nspace_name_etc(id)) {
			if (!IS_NULL_id(pid) && is_tagged_type(pid)) {
				/* Allow hiding of non-template classes */
				DECL_SPEC ds = DEREF_dspec(id_storage(pid));
				if (!(ds & dspec_template)) {
					pid = NULL_id;
				}
			}
		}
	}
	if (!IS_NULL_id(pid)) {
		IDENTIFIER qid = DEREF_id(id_alias(pid));
		if (EQ_id(id, qid)) {
			/* Redeclaration of existing meaning */
			if (EQ_id(id, pid)) {
				report(crt_loc, ERR_dcl_nspace_udecl_mem(id));
			}
			return pid;
		}
		if (IS_id_function_etc(id) && IS_id_function_etc(pid)) {
			/* Both new and old meanings are functions */
			/* EMPTY */
		} else {
			/* Invalid redeclaration */
			PTR(LOCATION) loc = id_loc(pid);
			ERROR err = ERR_dcl_nspace_udecl_multi(pid, loc);
			report(crt_loc, err);
			pid = NULL_id;
		}
	}

	/* Create the alias */
	id = alias_id(id, cns, pid, 1);
	if (!IS_NULL_id(pid)) {
		/* Deal with function hiding */
		id = hide_functions(id, pid, 0);
	}
	if (type) {
		set_type_member(mem, id);
	} else {
		set_member(mem, id);
	}
	return id;
}


/*
    PROCESS A USING DECLARATION

    This routine processes a using-declaration of the identifier id.  Note
    that this includes the access declarations used to modify access to
    class members.
*/

IDENTIFIER
using_identifier(IDENTIFIER id)
{
	/* Identifier must be qualified */
	MEMBER mem;
	HASHID unm;
	IDENTIFIER cid;
	IDENTIFIER uid = id;
	NAMESPACE uns = DEREF_nspace(id_parent(uid));
	uid = constr_name(uns, uid);
	unm = DEREF_hashid(id_name(uid));
	if (crt_id_qualifier == qual_none) {
		report(crt_loc, ERR_dcl_nspace_udecl_unqual());
		return uid;
	}

	/* Report undefined and ambiguous identifiers */
	switch (TAG_id(uid)) {
	case id_ambig_tag: {
		/* Introduce all the ambiguous meanings */
		LIST(IDENTIFIER) pids = DEREF_list(id_ambig_ids(uid));
		while (!IS_NULL_list(pids)) {
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			IGNORE using_identifier(pid);
			pids = TAIL_list(pids);
		}
		uid = find_qual_id(crt_namespace, unm, 0, 0);
		return uid;
	}
	case id_undef_tag:
		/* Report undeclared identifiers */
		report(crt_loc, ERR_lookup_qual_undef(unm, uns));
		return uid;
	}

	/* Can have constructors or destructors */
	switch (TAG_hashid(unm)) {
	case hashid_constr_tag:
	case hashid_destr_tag:
		report(crt_loc, ERR_dcl_nspace_udecl_constr(uid));
		return uid;
	}

	/* Check for hidden type names */
	mem = search_member(uns, unm, 0);
	cid = type_member(mem, 1);
	if (EQ_id(cid, uid)) {
		cid = NULL_id;
	}

	/* Process the declaration */
	if (in_class_defn) {
		if (!IS_NULL_id(cid)) {
			IGNORE using_member(cid, 1);
		}
		uid = using_member(uid, 0);
	} else {
		if (!IS_NULL_id(cid)) {
			cid = DEREF_id(id_alias(cid));
			IGNORE using_name(cid);
		}
		uid = DEREF_id(id_alias(uid));
		uid = using_name(uid);
	}
	if (IS_NULL_id(uid)) {
		uid = id;
	} else {
		/* Check for hiding */
		if (option(OPT_decl_hide)) {
			switch (TAG_id(id)) {
			case id_variable_tag:
			case id_function_tag:
				check_hiding(uid);
				break;
			}
		}
	}
	return uid;
}


/*
    PROCESS A USING TYPENAME DECLARATION

    This routine processes a using-declaration involving the type t
    declared using typename.
*/

void
using_typename(TYPE t)
{
	UNUSED(t);
	return;
}


/*
    REDECLARE AN IDENTIFIER

    This routine redeclares the identifier id in the namespace ns.
*/

IDENTIFIER
redeclare_id(NAMESPACE ns, IDENTIFIER id)
{
	IDENTIFIER old_id;
	int cl = is_tagged_type(id);
	HASHID nm = DEREF_hashid(id_name(id));
	MEMBER mem = search_member(ns, nm, 1);
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (cl) {
		old_id = type_member(mem, 3);
	} else {
		old_id = DEREF_id(member_id(mem));
	}
	if (!IS_NULL_id(old_id)) {
		PTR(LOCATION) loc = id_loc(old_id);
		report(crt_loc, ERR_basic_odr_decl(old_id, loc));
	}
	if (cl) {
		set_type_member(mem, id);
	} else {
		set_member(mem, id);
	}
	ds |= dspec_reserve;
	COPY_dspec(id_storage(id), ds);
	COPY_nspace(id_parent(id), ns);
	return id;
}


/*
    CHECK ANONYMOUS UNION MEMBER

    This routine checks whether the identifier id is member of an
    anonymous union.
*/

int
is_anon_member(IDENTIFIER id)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_reserve) {
		IDENTIFIER pid = DEREF_id(id_alias(id));
		if (!EQ_id(pid, id)) {
			TYPE s = DEREF_type(id_variable_etc_type(pid));
			if (IS_type_compound(s)) {
				TYPE t = DEREF_type(id_variable_etc_type(id));
				if (!eq_type(s, t)) {
					return 1;
				}
			}
		}
	}
	return 0;
}


/*
    REDECLARE A MEMBER OF AN ANONYMOUS UNION

    This routine redeclares the member id of an anonymous union.  The
    remaining arguments are as in redecl_anon_union.
*/

static IDENTIFIER
redecl_anon_member(IDENTIFIER id, CLASS_TYPE ct, DECL_SPEC ds, IDENTIFIER obj)
{
	IDENTIFIER pid = NULL_id;
	HASHID nm = DEREF_hashid(id_name(id));
	if (!IS_hashid_anon(nm)) {
		switch (TAG_id(id)) {
		case id_member_tag: {
			/* Redeclare a type member */
			TYPE t = DEREF_type(id_member_type(id));
			DEREF_loc(id_loc(id), crt_loc);
			if (IS_id_member(obj)) {
				NAMESPACE cns = crt_namespace;
				OFFSET off1 = DEREF_off(id_member_off(id));
				OFFSET off2 = DEREF_off(id_member_off(obj));
				id = find_id(nm);
				id = constr_name(cns, id);
				id = make_member_decl(ds, t, id, 0);
				MAKE_off_plus(off2, off1, off1);
				COPY_off(id_member_off(id), off1);
			} else {
				id = make_object_decl(ds, t, id, 0);
				obj = DEREF_id(id_alias(obj));
				COPY_id(id_alias(id), obj);
			}
			pid = id;
			break;
		}
		case id_class_name_tag: {
			/* Redeclare a class name */
			int templ = 0;
			CLASS_TYPE cs;
			TYPE t = DEREF_type(id_class_name_defn(id));
			while (IS_type_templ(t)) {
				templ = 1;
				t = DEREF_type(type_templ_defn(t));
			}
			cs = DEREF_ctype(type_compound_defn(t));
			if (!eq_ctype(ct, cs)) {
				NAMESPACE cns = crt_namespace;
				if (templ) {
					/* Shouldn't be a template class */
					LOCATION loc;
					DEREF_loc(id_loc(id), loc);
					report(loc, ERR_temp_decl_bad());
				}
				pid = redeclare_id(cns, id);
			}
			break;
		}
		case id_enum_name_tag:
		case id_class_alias_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag:
		case id_enumerator_tag: {
			/* Redeclare other identifiers */
			NAMESPACE cns = crt_namespace;
			pid = redeclare_id(cns, id);
			break;
		}
		}
	}
	return pid;
}


/*
    REDECLARE AN ANONYMOUS UNION

    This routine redeclares all the members of the anonymous union obj of
    type ct in the current namespace using the declaration specifiers ds.
    The routine returns false if there are no members to redeclare.  The
    redeclared members are added to the extra field of the namespace given
    by ct.
*/

int
redecl_anon_union(CLASS_TYPE ct, DECL_SPEC ds, IDENTIFIER obj)
{
	int ok = 0;
	MEMBER mem;
	NAMESPACE ns;
	LOCATION old_loc;
	bad_crt_loc++;
	old_loc = crt_loc;
	ds |= dspec_reserve;
	crt_id_qualifier = qual_none;
	crt_templ_qualifier = 0;
	ns = DEREF_nspace(ctype_member(ct));
	mem = DEREF_member(nspace_ctype_first(ns));
	while (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		IDENTIFIER aid = DEREF_id(member_alt(mem));
		if (!IS_NULL_id(aid) && !EQ_id(aid, id)) {
			aid = redecl_anon_member(aid, ct, ds, obj);
			if (!IS_NULL_id(aid)) {
				ok = 1;
			}
		}
		if (!IS_NULL_id(id)) {
			id = redecl_anon_member(id, ct, ds, obj);
			if (!IS_NULL_id(id)) {
				ok = 1;
			}
		}
		mem = DEREF_member(member_next(mem));
	}
	crt_loc = old_loc;
	bad_crt_loc--;
	return ok;
}
