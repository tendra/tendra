/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "config.h"
#include "c_types.h"
#include "ctype_ops.h"
#include "exp_ops.h"
#include "id_ops.h"
#include "hashid_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "access.h"
#include "basetype.h"
#include "class.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "declare.h"
#include "derive.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "instance.h"
#include "namespace.h"
#include "option.h"
#include "parse.h"
#include "predict.h"
#include "redeclare.h"
#include "syntax.h"
#include "template.h"
#include "tok.h"
#include "token.h"


/*
    USAGE SUPPRESSION FLAG

    This flag may be set to true to indicate that the parser is in a sizeof
    expression or similar so that any usages should not be included.
*/

int suppress_usage = 0;


/*
    MARK AN IDENTIFIER AS BEING USED

    This routine marks the identifier id as having been used and checks
    any access controls.
*/

void
use_id(IDENTIFIER id, int suppress)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	DECL_SPEC acc = (ds & dspec_access);
	if (acc)check_access(id, acc);

	/* Check usage */
	if (ds & dspec_main) {
		HASHID nm = DEREF_hashid(id_name(id));
		switch (TAG_hashid(nm)) {
		case hashid_name_tag:
			/* Can't take the address of 'main' */
			report(crt_loc, ERR_basic_start_main_addr(id));
			break;
		case hashid_constr_tag:
			/* Can't take the address of a constructor */
			report(crt_loc, ERR_class_ctor_addr(id));
			break;
		case hashid_destr_tag:
			/* Can't take the address of a destructor */
			report(crt_loc, ERR_class_dtor_addr(id));
			break;
		}
	}

	/* Mark use */
	if (!(ds & dspec_used)) {
		if (!suppress) {
			ds |= dspec_used;
			COPY_dspec(id_storage(id), ds);
		}
		if (ds & (dspec_inherit | dspec_alias | dspec_extern)) {
			/* Check for inheritance */
			IDENTIFIER uid = DEREF_id(id_alias(id));
			if (!EQ_id(uid, id)) {
				ds = DEREF_dspec(id_storage(uid));
				if (ds & dspec_used) {
					if (do_usage) {
						dump_use(id, &crt_loc, 1);
					}
					return;
				}
				if (!suppress) {
					ds |= dspec_used;
					COPY_dspec(id_storage(uid), ds);
				}
			}
		}
		if (!(ds & dspec_defn) && (ds & dspec_instance)) {
			/* Define template instance */
			if (!suppress) {
				define_template(id, 0);
			}
		}
	}
	if (do_usage) {
		dump_use(id, &crt_loc, 1);
	}
	return;
}


/*
    MARK A FUNCTION IDENTIFIER AS BEING USED

    This routine marks the function identifier id as having been called
    and checks any access controls.  In addition certain checks are applied
    to the first call of an identifier.  expl is true for explicit calls.
*/

void
use_func_id(IDENTIFIER id, int expl, int suppress)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	DECL_SPEC acc = (ds & dspec_access);
	if (acc) {
		check_access(id, acc);
	}
	if (!(ds & dspec_called)) {
		/* Mark use */
		if (!suppress) {
			if (!(ds & dspec_virtual)) {
				ds |= dspec_used;
			}
			ds |= dspec_called;
			COPY_dspec(id_storage(id), ds);
		}

		/* Check for inheritance */
		if (ds & (dspec_inherit | dspec_alias | dspec_extern)) {
			IDENTIFIER uid = DEREF_id(id_alias(id));
			if (!EQ_id(uid, id)) {
				ds = DEREF_dspec(id_storage(uid));
				if (ds & dspec_called) {
					if (do_usage) {
						dump_call(id, &crt_loc, expl);
					}
					return;
				}
				if (!suppress) {
					if (!(ds & dspec_virtual)) {
						ds |= dspec_used;
					}
					ds |= dspec_called;
					COPY_dspec(id_storage(uid), ds);
				}
			}
		}

		/* Check usage */
		if (ds & dspec_main) {
			HASHID nm = DEREF_hashid(id_name(id));
			if (IS_hashid_name(nm)) {
				/* Can't call 'main' */
				report(crt_loc, ERR_basic_start_main_call(id));
			}
		}
		if (!(ds & dspec_defn) && !suppress) {
			if (ds & dspec_implicit) {
				/* Define implicitly declared function */
				implicit_defn(id, DEFAULT_USR);
				ds = DEREF_dspec(id_storage(id));
			} else if (ds & dspec_instance) {
				/* Define template function */
				if (!(ds & dspec_virtual)) {
					define_template(id, 0);
					ds = DEREF_dspec(id_storage(id));
				}
			}
			if ((ds & dspec_inline) && !(ds & dspec_defn)) {
				/* An inline function called before it is
				 * defined */
				report(crt_loc,
				       ERR_dcl_fct_spec_inline_call(id));
			}
		}
	}
	if (do_usage) {
		dump_call(id, &crt_loc, expl);
	}
	return;
}


/*
    MARK A VIRTUAL FUNCTION AS BEING USED

    Note that use_func_id does not mark virtual functions as having been
    used because the actual function called can only be determined at
    run-time.  If subsequently it is found that the function called can
    be determined statically then this routine is called to mark that
    function as having been used.  It is also used in certain similar
    situations.
*/

void
reuse_id(IDENTIFIER id, int suppress)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_used) && !suppress) {
		ds |= dspec_used;
		COPY_dspec(id_storage(id), ds);
		if (!(ds & dspec_defn)) {
			if (ds & dspec_implicit) {
				/* Define implicitly declared function */
				implicit_defn(id, DEFAULT_USR);
			} else if (ds & dspec_instance) {
				/* Instantiate template functions */
				define_template(id, 0);
			}
		}
	}
	return;
}


/*
    DEFINE AN IDENTIFIER ALIAS

    This routine is called if the function or variable id is defined
    (excluding tentative definitions).  It passes the definition on to
    any alias of id.
*/

void
define_id(IDENTIFIER id)
{
	IDENTIFIER lid = DEREF_id(id_alias(id));
	if (!EQ_id(lid, id)) {
		/* Check for previous definition */
		LOCATION loc;
		DECL_SPEC ds;
		DEREF_loc(id_loc(id), loc);
		ds = DEREF_dspec(id_storage(lid));
		if (ds & dspec_defn) {
			EXP e = DEREF_exp(id_variable_etc_init(lid));
			if (IS_NULL_exp(e) || !IS_exp_zero(e)) {
				/* Exclude previous tentative definitions */
				PTR(LOCATION)ploc = id_loc(lid);
				ERROR err = ERR_basic_odr_def(lid, ploc);
				if (ds & dspec_c) {
					/* Explain C linkage identifications */
					HASHID nm = DEREF_hashid(id_name(lid));
					ERROR err2 =
					    ERR_dcl_link_redecl(nm, ploc);
					err = concat_error(err, err2);
				}
				report(loc, err);
			}
		}

		/* Copy definition */
		if (IS_id_function_etc(id)) {
			EXP e = DEREF_exp(id_function_etc_defn(id));
			COPY_exp(id_function_etc_defn(lid), e);
		} else if (IS_id_variable_etc(id)) {
			TYPE t = DEREF_type(id_variable_etc_type(id));
			EXP e = DEREF_exp(id_variable_etc_init(id));
			EXP d = DEREF_exp(id_variable_etc_term(id));
			COPY_exp(id_variable_etc_init(lid), e);
			COPY_exp(id_variable_etc_term(lid), d);
			COPY_type(id_variable_etc_type(lid), t);
		}

		/* Record definition */
		ds |= dspec_defn;
		COPY_dspec(id_storage(lid), ds);
		DEREF_loc(id_loc(lid), loc);
	}
	return;
}


/*
    FIND THE END OF A LIST OF IDENTIFIER ALIASES

    In most cases the alias of an identifier is its underlying meaning,
    however for function parameters it is possible to have vast lists
    of identifiers arising from redeclarations all linked by their alias
    field.  This routine scans down such a list until it finds an identifier
    which is its own alias.
*/

IDENTIFIER
chase_alias(IDENTIFIER id)
{
	while (!IS_NULL_id(id)) {
		IDENTIFIER lid = DEREF_id(id_alias(id));
		if (EQ_id(lid, id)) {
			break;
		}
		id = lid;
	}
	return id;
}


/*
    CURRENT IDENTIFIER QUALIFIER

    This variable is set to describe how the current identifier is
    qualified.
*/

QUALIFIER crt_id_qualifier = qual_none;
int crt_templ_qualifier = 0;


/*
    CHECK AN IDENTIFIER NAME

    This routine checks whether the identifier name id is suitable for use
    in the context given by loc.  The namespace qualifiers used in describing
    id will be given by crt_id_qualifier.  The routine returns true for
    legal identifiers.
*/

ERROR
check_id_name(IDENTIFIER id, int loc)
{
	/* Check on namespace component */
	ERROR err = NULL_err;
	QUALIFIER cq = crt_id_qualifier;
	switch (cq) {
	case qual_none: {
		/* No namespace specifier */
		if (in_template_decl && is_templ_alias(id)) {
			/* Check for hiding of template parameters */
			err = ERR_temp_local_hide(id);
			if (!IS_NULL_err(err)) {
				return err;
			}
		}
		if (crt_templ_qualifier) {
			goto qualifier_lab;
		}
		break;
	}
	case qual_nested:
qualifier_lab:
		/* Nested namespace specifier */
		if (loc == CONTEXT_PARAMETER || loc == CONTEXT_TEMPL_PARAM) {
			err = ERR_dcl_meaning_id(cq, id);
			if (!IS_NULL_err(err)) {
				return err;
			}
		}
		break;
	case qual_full:
	case qual_top:
		/* Namespace specifier beginning with '::' */
		err = ERR_dcl_meaning_full(cq, id);
		if (!IS_NULL_err(err)) {
			return err;
		}
		goto qualifier_lab;
	}

	/* Check on name component */
	if (loc != CONTEXT_FUNCTION && loc != CONTEXT_FUNC_MEMBER) {
		HASHID nm = DEREF_hashid(id_name(id));
		switch (TAG_hashid(nm)) {
		case hashid_constr_tag:
			/* A constructor must be a member function */
			err = ERR_class_mem_ctor(id);
			break;
		case hashid_destr_tag:
			/* A destructor must be a member function */
			err = ERR_class_dtor_func(nm);
			break;
		case hashid_conv_tag:
		case hashid_op_tag:
			/* These must be functions */
			err = ERR_dcl_meaning_id(cq, id);
			break;
		}
	}
	return err;
}


/*
    DECLARE AN IMPLICIT FUNCTION

    This routine declares a function named id in the current scope with
    declaration specifiers ds, return type ret (which may be the null type),
    parameter types p (terminated by the null type), and function kind ell.
    It is used to declare implicit functions.
*/

IDENTIFIER
declare_func(DECL_SPEC ds, IDENTIFIER id, TYPE ret, TYPE *p, int ell,
	     LIST(TYPE) ex)
{
	/* Save certain information */
	TYPE t;
	CV_SPEC cv;
	DECL_SPEC acc = crt_access;
	int td = have_type_declaration;
	QUALIFIER cq = crt_id_qualifier;
	int tq = crt_templ_qualifier;
	crt_access = dspec_public;
	crt_id_qualifier = qual_none;
	crt_templ_qualifier = 0;
	have_type_declaration = TYPE_DECL_NONE;

	/* Declare parameters */
	decl_loc = crt_loc;
	begin_param(id);
	while (!IS_NULL_type(*p)) {
		HASHID nm = lookup_anon();
		IDENTIFIER pid = DEREF_id(hashid_id(nm));
		pid = make_param_decl(dspec_none, *p, pid, CONTEXT_PARAMETER);
		init_param(pid, NULL_exp);
		p++;
	}
	if (IS_NULL_type(ret)) {
		ret = type_inferred;
	}
	cv = func_linkage(cv_none);
	t = make_func_type(ret, ell, cv, ex);
	end_param();

	/* Declare the function */
	if (in_class_defn) {
#if LANGUAGE_CPP
		if (ds & dspec_friend) {
			id = make_friend_decl(ds, t, id, 0, 1);
		} else {
			id = make_func_mem_decl(ds, t, id, 0);
		}
#else
		id = make_member_decl(ds, t, id, 0);
#endif
	} else {
		id = make_func_decl(ds, t, id, 0);
	}
	if (do_dump) {
		dump_implicit = 1;
		dump_declare(id, &decl_loc, 0);
	}
	have_type_declaration = td;
	crt_templ_qualifier = tq;
	crt_id_qualifier = cq;
	crt_access = acc;
	return id;
}


/*
    IMPLICITLY DECLARE AN IDENTIFIER

    This routine implicitly declares an identifier id, either as a local
    variable, if fn is false, or as a function.  fn will be 2 in the cases
    where C allows an implicit function declaration.  The routine returns
    the corresponding identifier expression.
*/

EXP
implicit_id_exp(IDENTIFIER id, int fn)
{
	EXP e;
	ERROR err;
	LOCATION loc;
	DECL_SPEC ds;
	IDENTIFIER pid;
	DECL_SPEC cl = crt_linkage;
	QUALIFIER cq = crt_id_qualifier;
	int tq = crt_templ_qualifier;
	NAMESPACE cns = crt_namespace;
	HASHID nm = DEREF_hashid(id_name(id));
	NAMESPACE ns = DEREF_nspace(id_parent(id));

	/* Check for implicit function declarations */
	if (fn == 2 && option(OPT_func_impl) == OPTION_DISALLOW) {
		fn = 1;
	}

	/* Allow for template dependent declarations */
	if (in_template_decl && is_templ_nspace(cns)) {
		int opt = OPT_templ_undecl;
		OPTION sev = option(opt);
		if (sev != OPTION_ALLOW) {
			/* Implicit declarations for dependent identifiers */
			if (dependent_id(id)) {
				opt = OPT_none;
				sev = OPTION_ALLOW;
			}
		}
		if (sev != OPTION_DISALLOW) {
			if (sev != OPTION_ALLOW && fn != 2) {
				if (cq == qual_none) {
					err = ERR_lookup_unqual_undef(nm);
				} else {
					err = ERR_lookup_qual_undef(nm, ns);
				}
				err = set_severity(err, opt, 0);
				report(crt_loc, err);
			}
			MAKE_exp_undeclared(type_templ_param, id, cq, e);
			return e;
		}
		if (cq == qual_none) {
			ns = NULL_nspace;
		}
	}

	/* Check for previous declaration */
	if (IS_NULL_nspace(ns)) {
		OPTION sev = option(OPT_decl_unify);
		if (sev != OPTION_OFF) {
			LIST(IDENTIFIER)p;
			NAMESPACE pns = nonblock_namespace;
			p = DEREF_list(nspace_named_etc_extra(pns));
			pid = unify_extern(id, NULL_type, pns, p);
			if (!IS_NULL_id(pid)) {
				if (sev != OPTION_ON) {
					err = ERR_lookup_unqual_vis(pid);
					err = set_severity(err, OPT_decl_unify,
							   0);
					report(crt_loc, err);
				}
				e = make_id_exp(pid);
				return e;
			}
		}
		ns = cns;
	}

	/* Rescan identifier */
	pid = search_id(ns, nm, 0, 0);
	if (!IS_NULL_id(pid)) {
		switch (TAG_id(pid)) {
		case id_variable_tag:
		case id_function_tag: {
			e = make_id_exp(pid);
			return e;
		}
		}
	}

	/* Find namespace for declaration */
	crt_linkage = dspec_c;
	crt_id_qualifier = qual_none;
	crt_templ_qualifier = 0;
	push_namespace(ns);
	bad_crt_loc++;
	loc = crt_loc;
	if (crt_state_depth == 0) {
		/* Find identifier location */
		IDENTIFIER uid = underlying_id(id);
		DEREF_loc(id_loc(uid), crt_loc);
	}

	if (fn) {
		/* Implicit functions declarations */
		int ell;
		TYPE ret = type_sint;
		TYPE pars = NULL_type;
#if LANGUAGE_CPP
		/* Type is 'int ( ... )' in C++ */
		ell = FUNC_ELLIPSIS;
		if (fn == 1) {
			ret = type_error;
		}
#else
		/* Type is 'int ()' in C */
		ell = FUNC_NO_PARAMS;
#endif
		ds = (dspec_extern | dspec_ignore);
		id = declare_func(ds, id, ret, &pars, ell, empty_type_set);
	} else {
		/* Other implicit declarations */
		decl_loc = crt_loc;
		id = make_object_decl(dspec_none, type_error, id, 0);
		IGNORE init_object(id, NULL_exp);
	}

	/* Report error */
	crt_linkage = cl;
	crt_templ_qualifier = tq;
	crt_id_qualifier = cq;
	if (fn == 2) {
		pid = DEREF_id(id_alias(id));
		ds = DEREF_dspec(id_storage(pid));
		if (ds & dspec_temp) {
			/* Implicit declaration already reported */
			err = NULL_err;
		} else {
			err = ERR_expr_call_undecl(id);
			if (!IS_NULL_err(err)) {
				ds |= dspec_temp;
				COPY_dspec(id_storage(pid), ds);
			}
		}
	} else if (cq == qual_none) {
		err = ERR_lookup_unqual_undef(nm);
	} else {
		err = ERR_lookup_qual_undef(nm, ns);
	}
	report(crt_loc, err);

	/* Construct the result */
	crt_loc = loc;
	bad_crt_loc--;
	IGNORE pop_namespace();
	e = make_id_exp(id);
	return e;
}


/*
    LIST OF MEANINGS

    This list is built up by list_ambiguous to give all the meanings of
    its ambiguous identifier which match its type argument.
*/

static LIST(IDENTIFIER) ambig_meanings = NULL_list(IDENTIFIER);


/*
    LIST MEANINGS OF AN AMBIGUOUS IDENTIFIER

    This routine adds all meanings of the ambiguous identifier id to the
    error list err.
*/

static unsigned
list_ambiguous(IDENTIFIER id, unsigned n, ERROR *err, int type, int rec)
{
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_ambig_tag: {
			/* Ambiguous identifiers */
			LIST(IDENTIFIER) p = DEREF_list(id_ambig_ids(id));
			rec = DEREF_int(id_ambig_over(id));
			while (!IS_NULL_list(p)) {
				id = DEREF_id(HEAD_list(p));
				n = list_ambiguous(id, n, err, type, rec);
				p = TAIL_list(p);
			}
			break;
		}
		case id_function_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag: {
			/* Functions */
			if (rec) {
				IDENTIFIER over;
				over = DEREF_id(id_function_etc_over(id));
				n = list_ambiguous(over, n, err, type, rec);
			}
			goto default_lab;
		}
		case id_class_name_tag:
		case id_class_alias_tag:
		case id_enum_name_tag:
		case id_enum_alias_tag:
		case id_type_alias_tag: {
			/* Types */
			type = 0;
			goto default_lab;
		}
		default:
default_lab: {
		     /* Other identifiers */
		     PTR(LOCATION) loc = id_loc(id);
		     n++;
		     add_error(err, ERR_fail_list_item(n, id, loc));
		     break;
	     }
		}
		if (type == 0) {
			/* Add to list of meanings */
			CONS_id(id, ambig_meanings, ambig_meanings);
		}
	}
	return n;
}


/*
    REPORT AN AMBIGUOUS IDENTIFIER

    This routine reports the identifier id as being ambiguous.  Overloaded
    functions count as a single identifier unless rec is true.  It returns
    one of the possible meanings.  Only types are considered if type is
    true.  If there is exactly one possible meaning or force is true the
    first meaning is returned.  Otherwise the null identifier is returned.
*/

IDENTIFIER
report_ambiguous(IDENTIFIER id, int type, int rec, int force)
{
	ERROR err, err2;
	LIST(IDENTIFIER) p;
	NAMESPACE ns = DEREF_nspace(id_parent(id));

	/* List all meanings */
	if (!IS_NULL_nspace(ns) && IS_nspace_ctype(ns)) {
		err = ERR_lookup_ambig_mem(id);
	} else {
		err = ERR_lookup_ambig_id(id);
	}
	err2 = ERR_lookup_ambig_list();
	if (!IS_NULL_err(err2)) {
		unsigned n = 0;
		err = concat_error(err, err2);
		n = list_ambiguous(id, n, &err, type, rec);
		err = concat_error(err, ERR_fail_list_end(n));
	}
	report(crt_loc, err);

	/* Check for resolved meaning */
	id = NULL_id;
	p = ambig_meanings;
	if (!IS_NULL_list(p)) {
		if (IS_NULL_list(TAIL_list(p)) || force) {
			id = DEREF_id(HEAD_list(p));
		}
		DESTROY_list(p, SIZE_id);
		ambig_meanings = NULL_list(IDENTIFIER);
	}
	return id;
}


/*
    FIND THE DECLARATION SPECIFIER FOR AN AMBIGUOUS IDENTIFIER

    This routine finds the declaration specifier for an ambiguous identifier
    given by the list of cases pids.  This consists of various properties
    which all the cases share.
*/

DECL_SPEC
find_ambig_dspec(LIST(IDENTIFIER) pids)
{
	DECL_SPEC ds = (dspec_implicit | dspec_template);
	while (!IS_NULL_list(pids)) {
		IDENTIFIER pid = DEREF_id(HEAD_list(pids));
		if (!IS_NULL_id(pid)) {
			DECL_SPEC pds = DEREF_dspec(id_storage(pid));
			ds &= pds;
		}
		pids = TAIL_list(pids);
	}
	return ds;
}


/*
    CREATE AN IDENTIFIER EXPRESSION

    This routine creates an expression corresponding to the identifier id.
    Note that static member functions are identifier expressions if they
    are not overloaded, but member expression otherwise.  They are sorted
    out properly during overload resolution (see resolve_cast).
*/

EXP
make_id_exp(IDENTIFIER id)
{
	EXP e;
	unsigned tag = TAG_id(id);
	QUALIFIER cq = crt_id_qualifier;
	switch (tag) {
	case id_variable_tag:
	case id_parameter_tag: {
		/* Variables and parameters */
		TYPE t;
		DECL_SPEC ds;
		use_id(id, 0);
		ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_auto) {
			/* Check use of automatic variable */
			NAMESPACE ns = crt_namespace;
			switch (TAG_nspace(ns)) {
			case nspace_block_tag:
			case nspace_dummy_tag: {
				if (really_in_function_defn > 1) {
					/* Used in nested function */
					IDENTIFIER fid;
					ns = DEREF_nspace(id_parent(id));
					fid = DEREF_id(nspace_name(ns));
					if (!EQ_id(fid, crt_func_id)) {
						ERROR err =
						    ERR_class_local_auto(id);
						report(crt_loc, err);
					}
				}
				break;
			}
			case nspace_param_tag:
			case nspace_templ_tag: {
				/* Used in default argument */
				if (in_default_arg) {
					ERROR err =
					    ERR_dcl_fct_default_param(id);
					report(crt_loc, err);
				}
				break;
			}
			default: {
				/* Used in local class */
				ERROR err = ERR_class_local_auto(id);
				report(crt_loc, err);
				break;
			}
			}
		}
		t = DEREF_type(id_variable_etc_type(id));
		if ((ds & dspec_extern) && cv_extern) {
			CV_SPEC cv = DEREF_cv(type_qual(t));
			t = qualify_type(t,(cv | cv_extern), 0);
			used_extern_volatile = 1;
		}
		MAKE_exp_identifier(t, id, cq, e);
		break;
	}
	case id_stat_member_tag: {
		/* Static data members */
		TYPE t;
		DECL_SPEC ds;
		use_id(id, suppress_usage);
		ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_inherit) {
			id = DEREF_id(id_alias(id));
		}
		t = DEREF_type(id_stat_member_type(id));
		if ((ds & dspec_extern) && cv_extern) {
			CV_SPEC cv = DEREF_cv(type_qual(t));
			t = qualify_type(t,(cv | cv_extern), 0);
			used_extern_volatile = 1;
		}
		MAKE_exp_identifier(t, id, cq, e);
		break;
	}
	case id_function_tag: {
		/* Normal functions */
		TYPE t = DEREF_type(id_function_type(id));
		MAKE_exp_identifier(t, id, cq, e);
		break;
	}
	case id_stat_mem_func_tag: {
		/* Static member functions */
		TYPE t = DEREF_type(id_stat_mem_func_type(id));
		IDENTIFIER over = DEREF_id(id_stat_mem_func_over(id));
		if (IS_NULL_id(over)) {
			MAKE_exp_identifier(t, id, cq, e);
		} else {
			MAKE_exp_member(t, id, cq, e);
		}
		break;
	}
	case id_mem_func_tag: {
		/* Non-static member functions */
		TYPE t = DEREF_type(id_mem_func_type(id));
		MAKE_exp_member(t, id, cq, e);
		break;
	}
	case id_member_tag: {
		/* Non-static members */
		TYPE t = DEREF_type(id_member_type(id));
		MAKE_exp_member(t, id, cq, e);
		break;
	}
	case id_enumerator_tag: {
		/* Enumerators */
		NAT n;
		TYPE t;
		use_id(id, 0);
		e = DEREF_exp(id_enumerator_value(id));
		DECONS_exp_int_lit(t, n, tag, e);
		MAKE_exp_int_lit(t, n, tag, e);
		break;
	}
	case id_token_tag: {
		/* Tokens */
		TOKEN tok = DEREF_tok(id_token_sort(id));
		switch (TAG_tok(tok)) {
		case tok_exp_tag:
		case tok_nat_tag:
		case tok_snat_tag:
		case tok_stmt_tag:
			/* Expression tokens */
			use_id(id, 0);
			id = DEREF_id(id_token_alt(id));
			e = apply_exp_token(id, NULL_list(TOKEN), 0);
			break;
		default:
			/* Other tokens */
			goto default_lab;
		}
		break;
	}
	case id_class_name_tag:
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag: {
		/* Type names */
		TYPE t = DEREF_type(id_class_name_etc_defn(id));
		report(crt_loc, ERR_expr_prim_type(id));
		MAKE_exp_value(t, e);
		break;
	}
	case id_ambig_tag: {
		/* Ambiguous identifiers */
		MAKE_exp_ambiguous(type_error, id, cq, e);
		break;
	}
	default:
default_lab:
		/* Undefined identifiers */
		if (cq == qual_none && in_template_decl) {
			/* Create a dummy identifier */
			HASHID nm = DEREF_hashid(id_name(id));
			NAMESPACE ns = nonblock_namespace;
			MAKE_id_undef(nm, dspec_none, ns, crt_loc, id);
		}
		MAKE_exp_undeclared(type_error, id, cq, e);
		break;
	}
	return e;
}


/*
    FIND THE THIS PARAMETER OF A FUNCTION

    This routine returns the 'this' parameter of the member function fn.
    If use is true then the parameter is marked as used.
*/

IDENTIFIER
this_param(IDENTIFIER fn, int use)
{
	NAMESPACE ns;
	IDENTIFIER pid;
	HASHID nm = KEYWORD(lex_this_Hname);
	TYPE t = DEREF_type(id_mem_func_type(fn));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ns = DEREF_nspace(type_func_pars(t));
	pid = search_id(ns, nm, 0, 0);
	if (!IS_NULL_id(pid) && use) {
		/* Mark parameter as used */
		DECL_SPEC ds = DEREF_dspec(id_storage(pid));
		ds |= dspec_used;
		COPY_dspec(id_storage(pid), ds);
	}
	return pid;
}


/*
    CREATE A THIS EXPRESSION

    This routine deals with the 'this' expression.  This is only in scope
    in the definition of a non-static member function.   Note that the
    current value of 'this' is given by the address of the dummy parameter
    with name given by lex_this_Hname.
*/

EXP
make_this_exp(void)
{
	EXP e;
	TYPE t;
	IDENTIFIER fn = crt_func_id;
	if (in_function_defn && IS_id_mem_func(fn)) {
		/* The current value of 'this' is returned */
		IDENTIFIER pid = this_param(fn, 1);
		if (in_default_arg) {
			/* Can't use 'this' in default argument */
			ERROR err = ERR_dcl_fct_default_param(pid);
			report(crt_loc, err);
		}
		e = DEREF_exp(id_parameter_init(pid));
		t = DEREF_type(exp_type(e));
		MAKE_exp_copy(t, e, e);
	} else {
		/* Must be inside a non-static member function */
		report(crt_loc, ERR_expr_prim_this());
		e = make_error_exp(0);
	}
	return e;
}


/*
    CREATE A THIS EXPRESSION

    This routine creates an expression corresponding to the 'this' parameter
    of a member function.  The parent class namespace is assigned to pns.
    The null expression is returned if we are outside of a member function.
*/

EXP
make_this_ref(NAMESPACE *pns)
{
	IDENTIFIER fn = crt_func_id;
	if (in_function_defn && IS_id_mem_func(fn)) {
		EXP e;
		IDENTIFIER pid = this_param(fn, 1);
		TYPE t = DEREF_type(id_parameter_type(pid));
		MAKE_exp_identifier(t, pid, qual_none, e);
		*pns = DEREF_nspace(id_parent(fn));
		return e;
	}
	return NULL_exp;
}


/*
    DECLARE A THIS PARAMETER

    This routine declares the dummy extra parameter for the non-static
    member function given by the identifier fn.  The type of this parameter
    is the first element of the corresponding mtypes list (see
    member_func_type).  An expression giving the address of the parameter
    is stored in its default argument position.  This gives the value of
    the 'this' expression.
*/

EXP
make_this_decl(IDENTIFIER fn)
{
	/* Look up identifier */
	EXP e;
	TYPE t;
	IDENTIFIER pid;
	LIST(TYPE) mtypes;
	NAMESPACE ns = crt_namespace;
	HASHID nm = KEYWORD(lex_this_Hname);
	MEMBER mem = search_member(ns, nm, 1);
	IDENTIFIER qid = DEREF_id(member_id(mem));
	DECL_SPEC ds = (dspec_auto | dspec_defn | dspec_implicit);

	/* Construct the type of the parameter */
	TYPE f = DEREF_type(id_mem_func_type(fn));
	while (IS_type_templ(f)) {
		f = DEREF_type(type_templ_defn(f));
	}
	mtypes = DEREF_list(type_func_mtypes(f));
	t = DEREF_type(HEAD_list(mtypes));

	/* Declare parameter */
	MAKE_id_parameter(nm, ds, ns, crt_loc, t, pid);
	if (!IS_NULL_id(qid)) {
		qid = DEREF_id(id_alias(qid));
		COPY_id(id_alias(pid), qid);
	}
	COPY_id(hashid_cache(nm), pid);
	COPY_id(member_id(mem), pid);

	/* Construct the 'this' expression */
	t = DEREF_type(type_ref_sub(t));
	t = rvalue_type(t);
	if (option(OPT_this_lvalue) == OPTION_ALLOW) {
		MAKE_type_ptr(cv_lvalue, t, t);
		MAKE_exp_identifier(t, pid, qual_none, e);
	} else {
		MAKE_type_ptr(cv_none, t, t);
		MAKE_exp_identifier(t, pid, qual_none, e);
		MAKE_exp_contents(t, e, e);
	}
	COPY_exp(id_parameter_init(pid), e);
	return e;
}


/*
    CHECK FOR THIS EXPRESSIONS

    This routine checks whether the expression e is a 'this' expression.
*/

int
is_this_exp(EXP e)
{
	if (!IS_NULL_exp(e)) {
		unsigned tag = TAG_exp(e);
		if (tag == exp_indir_tag) {
			e = DEREF_exp(exp_indir_ptr(e));
			tag = TAG_exp(e);
		}
		if (tag == exp_copy_tag) {
			e = DEREF_exp(exp_copy_arg(e));
			tag = TAG_exp(e);
		}
		if (tag == exp_contents_tag) {
			e = DEREF_exp(exp_contents_ptr(e));
			tag = TAG_exp(e);
		}
		if (tag == exp_copy_tag) {
			e = DEREF_exp(exp_copy_arg(e));
			tag = TAG_exp(e);
		}
		if (tag == exp_identifier_tag) {
			IDENTIFIER id = DEREF_id(exp_identifier_id(e));
			HASHID nm = DEREF_hashid(id_name(id));
			if (EQ_KEYWORD(nm, lex_this_Hname)) {
				return 1;
			}
		}
	}
	return 0;
}


/*
    FIND THE ELLIPSIS PARAMETER OF A FUNCTION

    This routine returns the ellipsis parameter of the function fn.
*/

IDENTIFIER
ellipsis_param(IDENTIFIER fn)
{
	int ell;
	TYPE t = DEREF_type(id_function_etc_type(fn));
	while (IS_type_templ(t)) {
		t = DEREF_type(type_templ_defn(t));
	}
	ell = DEREF_int(type_func_ellipsis(t));
	if (ell & FUNC_ELLIPSIS) {
		HASHID nm = KEYWORD(lex_ellipsis_Hexp);
		NAMESPACE ns = DEREF_nspace(type_func_pars(t));
		IDENTIFIER pid = search_id(ns, nm, 0, 0);
		return pid;
	}
	return NULL_id;
}


/*
    FIND ELLIPSIS TYPE

    This routine returns the type of the dummy ellipsis parameter.  If
    force is true then an error is reported if this type has not been
    declared.
*/

static TYPE
find_ellipsis_type(int force)
{
	TYPE t = type_ellipsis;
	if (IS_NULL_type(t)) {
		/* Look up token if not already defined */
		IDENTIFIER tid = get_special(TOK_va_t, 1);
		if (!IS_NULL_id(tid) && IS_id_token(tid)) {
			tid = DEREF_id(id_token_alt(tid));
			if (IS_id_class_name_etc(tid)) {
				t = DEREF_type(id_class_name_etc_defn(tid));
				type_ellipsis = t;
			}
		}
		if (IS_NULL_type(t)) {
			if (force) {
				/* Report if ellipsis type is undefined */
				HASHID nm = KEYWORD(lex_ellipsis_Hexp);
				report(crt_loc,
				       ERR_lib_builtin(NULL_string, nm));
			}
			t = type_error;
		}
	}
	return t;
}


/*
    DECLARE AN ELLIPSIS PARAMETER

    This routine declares the dummy extra parameter representing the
    ellipsis component of the function id.
*/

void
make_ellipsis_decl(void)
{
	IDENTIFIER pid;
	NAMESPACE ns = crt_namespace;
	TYPE t = find_ellipsis_type(0);
	HASHID nm = KEYWORD(lex_ellipsis_Hexp);
	MEMBER mem = search_member(ns, nm, 1);
	IDENTIFIER qid = DEREF_id(member_id(mem));
	DECL_SPEC ds = (dspec_auto | dspec_defn | dspec_implicit);
	MAKE_id_parameter(nm, ds, ns, crt_loc, t, pid);
	if (!IS_NULL_id(qid)) {
		qid = DEREF_id(id_alias(qid));
		COPY_id(id_alias(pid), qid);
	}
	COPY_id(hashid_cache(nm), pid);
	COPY_id(member_id(mem), pid);
	return;
}


/*
    CREATE AN ELLIPSIS EXPRESSION

    This routine creates an expression corresponding to the ellipsis
    expression '...'.  This can only be used in a function definition
    which has an ellipsis type, in which case it is an rvalue of type
    type_ellipsis.
*/

EXP
make_ellipsis_exp(void)
{
	EXP e;
	if (in_function_defn) {
		IDENTIFIER pid = ellipsis_param(crt_func_id);
		if (!IS_NULL_id(pid)) {
			/* Form result */
			TYPE t = find_ellipsis_type(1);
			report(crt_loc, ERR_expr_call_ell_exp());
			MAKE_exp_identifier(t, pid, qual_none, e);
			return e;
		}
	}
	report(crt_loc, ERR_expr_call_ell_func());
	e = make_error_exp(0);
	return e;
}
