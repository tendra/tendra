/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>

#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/literal.h>
#include <parse/preproc.h>

#include <output/compile.h>
#include <output/dump.h>
#include <output/save.h>
#include <output/stmt.h>
#include <output/tok.h>

#include <construct/basetype.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/declare.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/namespace.h>
#include <construct/statement.h>
#include <construct/variable.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "inst_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "tok_ops.h"
#include "type_ops.h"
#include "syntax.h"


/*
    The flag suppress_variable may be set to 1 to suppress variable
    analysis on function parameters and to 2 to suppress all variable
    analysis.  The flag anon_c_linkage may be set to true to indicate
    that objects with C linkage in anonymous namespaces are anonymous.
*/

int suppress_variable = 0;
int anon_c_linkage = 0;


/*
    This routine checks the usage of the identifier id.  The flag anon
    is true if the complete reach of the identifier is being analysed.  For
    example, the reach of a local variable is its scope, that of an internal
    variable is its translation unit, and that of an external variable is
    its entire program.
*/

static void
check_usage(IDENTIFIER id, EXP blk, int anon)
{
	int opt;
	ERROR err;
	LOCATION loc;
	HASHID nm = DEREF_hashid(id_name(id));
	if (!IS_hashid_anon(nm)) {
		/* Ignore anonymous identifiers */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (anon == ANON_NAMESPACE && (ds & dspec_c)) {
			if (!anon_c_linkage) {
				anon = ANON_NONE;
			}
		}
		if (ds & dspec_static) {
			if (!IS_NULL_exp(blk) || suppress_variable == 2) {
				/* Global statics are external to a block
				 * etc. */
				ds |= dspec_extern;
			}
		}
		if (anon || !(ds & dspec_extern)) {
			if (ds & dspec_implicit) {
				/* Ignore implicitly declared constructors
				 * etc. */
				/* EMPTY */
			} else if (ds & (dspec_inherit | dspec_alias)) {
				/* Don't deal with inherited members here */
				/* EMPTY */
			} else if (ds & dspec_token) {
				/* Ignore tokenised identifiers */
				/* EMPTY */
			} else if (ds & dspec_defn) {
				if (ds & dspec_used) {
					/* Defined and used */
					/* EMPTY */
				} else {
					/* Defined but not used */
					if (ds & (dspec_inline |
						  dspec_virtual)) {
						/* Ignore inline and virtual
						 * functions */
						/* EMPTY */
					} else {
						if (ds & dspec_auto) {
							err = ERR_stmt_dcl_unused(id);
						} else {
							if (ds & dspec_static) {
								opt = OPT_discard_static;
							} else {
								opt = OPT_variable;
							}
							err = ERR_basic_odr_unused(id);
							err = set_severity(err, opt, 0);
						}
						if (!IS_NULL_err(err)) {
							DEREF_loc(id_loc(id),
								  loc);
							report(loc, err);
						}
					}
				}
			} else {
				if (ds & dspec_used) {
					/* Used but not defined */
					if (IS_id_class_name_etc(id)) {
						/* Alright for type names */
						/* EMPTY */
					} else {
						if (ds & dspec_inline) {
							err = ERR_basic_odr_inline(id);
						} else {
							err = ERR_basic_odr_undef(id);
						}
						if (!IS_NULL_err(err)) {
							DEREF_loc(id_loc(id),
								  loc);
							report(loc, err);
						}
						ds |= dspec_defn;
						COPY_dspec(id_storage(id), ds);
					}
				} else if (ds & dspec_virtual) {
					/* Undefined virtual function */
					if (ds & dspec_pure) {
						/* Allow pure virtual
						 * functions */
						/* EMPTY */
					} else {
						err = ERR_basic_odr_undef(id);
						if (!IS_NULL_err(err)) {
							DEREF_loc(id_loc(id),
								  loc);
							report(loc, err);
						}
					}
				} else if (ds & dspec_inline) {
					/* Ignore inline functions */
					/* EMPTY */
				} else {
					/* Not used or defined */
					if (ds & dspec_static) {
						opt = OPT_discard_static;
					} else {
						opt = OPT_variable;
					}
					err = ERR_basic_odr_redundant(id);
					err = set_severity(err, opt, 0);
					if (!IS_NULL_err(err)) {
						DEREF_loc(id_loc(id), loc);
						report(loc, err);
					}
				}
			}
		}
	}
	return;
}


/*
    This routine calls check_identifier for each instance of the template
    id.  t gives the template type, otherwise the parameters are as in
    check_identifier.
*/

static void
check_template_id(TYPE t, IDENTIFIER id, NAMESPACE ns, EXP blk, int anon,
		  int chk)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_done)) {
		/* Scan through template applications */
		TOKEN sort = DEREF_tok(type_templ_sort(t));
		INSTANCE apps = DEREF_inst(tok_templ_apps(sort));
		COPY_dspec(id_storage(id), (ds | dspec_done));
		while (!IS_NULL_inst(apps)) {
			DECL_SPEC acc = DEREF_dspec(inst_templ_access(apps));
			if (!(acc & (dspec_main | dspec_alias))) {
				if ((acc & dspec_instance) &&
				    !(acc & dspec_mutable)) {
					IDENTIFIER aid =
					    DEREF_id(inst_templ_id(apps));
					IGNORE check_identifier(aid, ns, blk,
								anon, chk);
				}
			}
			apps = DEREF_inst(inst_next(apps));
		}
		if (spec_unit) {
			spec_unit = save_end(spec_unit, NULL_nspace);
		}
		COPY_dspec(id_storage(id), ds);
	}
	return;
}


/*
    This routine checks the class usage information cu for the type ct.
*/

static void
check_class_usage(CLASS_TYPE ct, CLASS_USAGE cu)
{
	LOCATION loc;
	if (cu & cusage_destr) {
		IDENTIFIER id = DEREF_id(ctype_destr(ct));
		if (!IS_NULL_id(id) && IS_id_mem_func(id)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_trivial)) {
				DEREF_loc(id_loc(id), loc);
				report(loc, ERR_expr_delete_post(id));
			}
		}
	}
	if (cu & cusage_delete) {
		IDENTIFIER id = find_operator(ct, lex_delete);
		if (!IS_NULL_id(id)) {
			DEREF_loc(id_loc(id), loc);
			report(loc, ERR_expr_delete_post(id));
		}
	}
	if (cu & cusage_delete_array) {
		IDENTIFIER id = find_operator(ct, lex_delete_Harray);
		if (!IS_NULL_id(id)) {
			DEREF_loc(id_loc(id), loc);
			report(loc, ERR_expr_delete_post(id));
		}
	}
	if (cu & cusage_address) {
		IDENTIFIER id = find_operator(ct, lex_and_H1);
		while (!IS_NULL_id(id) && IS_id_function_etc(id)) {
			TYPE t = DEREF_type(id_function_etc_type(id));
			if (min_no_args(t) == 1) {
				DEREF_loc(id_loc(id), loc);
				report(loc, ERR_expr_unary_op_ref_post(id));
				break;
			}
			id = DEREF_id(id_function_etc_over(id));
		}
	}
	return;
}


/*
    This routine completes a C-style tentative definition of the
    variable id.  That is, if id has not been defined elsewhere, then
    it is defined to be zero.
*/

static int
define_tentative(IDENTIFIER id, int anon)
{
	int def = 0;
	EXP e = DEREF_exp(id_variable_etc_init(id));
	if (!IS_NULL_exp(e) && IS_exp_zero(e)) {
		LOCATION loc;
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		TYPE t = DEREF_type(id_variable_etc_type(id));
		bad_crt_loc++;
		loc = crt_loc;
		DEREF_loc(id_loc(id), crt_loc);
		if (anon || !(ds & dspec_extern)) {
			/* Types for internal objects should be complete */
			ERROR err = check_complete(t);
			if (!IS_NULL_err(err)) {
				ERROR err2 = ERR_basic_types_tent_incompl(id);
				err = concat_error(err, err2);
				report(crt_loc, err);
			}
		}
		if (IS_type_array(t)) {
			/* Complete array 'A []' to 'A [1]' */
			NAT n = DEREF_nat(type_array_size(t));
			if (IS_NULL_nat(n)) {
				CV_SPEC qual = DEREF_cv(type_qual(t));
				TYPE s = DEREF_type(type_array_sub(t));
				n = small_nat[1];
				MAKE_type_array(qual, s, n, t);
				COPY_type(id_variable_etc_type(id), t);
			}
		}
		e = init_general(t, NULL_exp, id, 0);
		COPY_exp(id_variable_etc_init(id), e);
		define_id(id);
		crt_loc = loc;
		bad_crt_loc--;
		def = 1;
	}
	return def;
}


/*
    This routine applies the global program checks to the identifier id
    from the namespace ns.  If id is a class or namespace name then the
    checks are also applied recursively to the members of id.  The flag
    anon is true if the parent namespace of id is local to the current
    translation unit.  The routine returns the number of identifiers in
    id (allowing for overloaded functions).
*/

unsigned long
check_identifier(IDENTIFIER id, NAMESPACE ns, EXP blk, int anon, int chk)
{
	unsigned long n = 1;
	if (spec_unit) {
		spec_unit = save_id(spec_unit, id, ns);
	}
	switch (TAG_id(id)) {
	case id_class_name_tag: {
		/* Check the members of a class */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (!(ds & dspec_implicit)) {
			int templ = 0;
			CLASS_TYPE ct;
			CLASS_INFO ci;
			NAMESPACE cns;
			int tchk = chk;
			TYPE t = DEREF_type(id_class_name_defn(id));
			TYPE s = t;
			while (IS_type_templ(t)) {
				/* Template classes */
				templ = 1;
				tchk = 0;
				t = DEREF_type(type_templ_defn(t));
			}
			ct = DEREF_ctype(type_compound_defn(t));
			cns = DEREF_nspace(ctype_member(ct));
			ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_complete) {
				/* Check class member namespace */
				CLASS_USAGE cu = DEREF_cusage(ctype_usage(ct));
				IDENTIFIER cid = DEREF_id(ctype_name(ct));
				HASHID cnm = DEREF_hashid(id_name(cid));
				if (IS_hashid_anon(cnm)) {
					anon = ANON_CLASS;
				}
#if LANGUAGE_CPP
				if ((ci & cinfo_polymorphic) && tchk) {
					/* Compile virtual function table */
					compile_virtual(ct, anon);
				}
#endif
				if (cu != cusage_none) {
					/* Check class usage */
					check_class_usage(ct, cu);
				}
			} else {
				if ((ci & cinfo_incomplete) && tchk) {
					/* Report incomplete types */
					complete_class(ct, 0);
					ci = DEREF_cinfo(ctype_info(ct));
					if (!(ci & cinfo_complete)) {
						ERROR err = ERR_basic_types_completed(t);
						if (!IS_NULL_err(err)) {
							LOCATION loc;
							DEREF_loc(id_loc(id),
								  loc);
							report(loc, err);
						}
					}
				}
				cns = NULL_nspace;
			}
			IGNORE check_namespace(cns, NULL_exp, anon, tchk);
			if (templ) {
				/* Template classes */
				check_template_id(s, id, ns, blk, anon, chk);
			}
		}
		goto type_label;
	}
	case id_enum_name_tag:
	case id_class_alias_tag:
	case id_enum_alias_tag:
	case id_type_alias_tag:
type_label:
		/* Compile type names */
		if (chk) {
			if (anon) {
				check_usage(id, blk, anon);
			}
			if (IS_NULL_exp(blk)) {
				compile_type(id);
			}
		}
		break;
	case id_nspace_name_tag: {
		/* Check the members of a namespace */
		NAMESPACE cns = DEREF_nspace(id_nspace_name_defn(id));
		n += check_namespace(cns, NULL_exp, anon, chk);
		break;
	}
	case id_variable_tag:
		/* Check variable usage */
		if (chk) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if ((ds & dspec_static) && preserve_all) {
				compile_preserve(id);
			}
			check_usage(id, blk, anon);
			if (IS_NULL_exp(blk)) {
				if (ds & dspec_defn) {
					IGNORE define_tentative(id, anon);
				}
				compile_variable(id, 0);
			} else {
				/* End of local block */
				if (ds & dspec_auto) {
					EXP term;
					ds &= ~dspec_access;
					COPY_dspec(id_storage(id), ds);
					term = DEREF_exp(id_variable_etc_term(id));
					if (!IS_NULL_exp(term)) {
						if (do_usage) {
							dump_destr(id,
								   &stmt_loc);
						}
					}
				}
			}
		}
		break;
	case id_parameter_tag: {
		/* Check parameter usage */
		if (chk && suppress_variable == 0) {
			check_usage(id, blk, anon);
		}
		break;
	}

	case id_stat_member_tag:
		/* Check static data member usage */
		if (anon == ANON_CLASS) {
			LOCATION loc;
			DEREF_loc(id_loc(id), loc);
			report(loc, ERR_class_static_data_anon(id));
		}
		if (chk) {
			check_usage(id, blk, anon);
			if (IS_NULL_exp(blk)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_defn) {
					IGNORE define_tentative(id, anon);
				}
				compile_variable(id, 0);
			}
		}
		break;
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Check member function usage */
		TYPE t = DEREF_type(id_function_etc_type(id));
		IDENTIFIER over = DEREF_id(id_function_etc_over(id));
		if (!IS_NULL_id(over)) {
			n += check_identifier(over, ns, blk, anon, chk);
		}
		if (IS_type_func(t)) {
			/* Simple functions */
			if (chk) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if ((ds & dspec_static) && preserve_all) {
					compile_preserve(id);
				}
				if (ds & dspec_inline) {
					if (!anon) {
						anon = ANON_INLINE;
					}
				}
				check_usage(id, blk, anon);
				if (IS_NULL_exp(blk)) {
					compile_function(id, 0);
				}
			}
		} else {
			/* Template functions */
			check_template_id(t, id, ns, blk, anon, chk);
		}
		break;
	}
	case id_enumerator_tag:
		/* Check enumerator value */
		if (chk) {
			EXP e = DEREF_exp(id_enumerator_value(id));
			if (overflow_exp(e)) {
				compile_variable(id, 0);
			}
		}
		break;
	case id_nspace_alias_tag:
	case id_member_tag:
	case id_weak_param_tag:
		/* Don't check these (yet) */
		break;
	}
	return n;
}


/*
    This routine scans through all the members of the namespace ns, calling
    check_identifier for each member (including hidden members) and
    compiling any functions or non-local variables.  It returns the number
    of identifiers declared in ns.  ns may be a block scope associated
    with the statement blk.  The flag anon is true if the parent namespace
    of ns is local to the current translation unit.
*/

unsigned long
check_namespace(NAMESPACE ns, EXP blk, int anon, int chk)
{
	unsigned long n = 0;
	if (!IS_NULL_nspace(ns)) {
		MEMBER mem;
		LIST(IDENTIFIER) extra;

		/* Find namespace components */
		switch (TAG_nspace(ns)) {
		case nspace_named_tag:
		case nspace_global_tag:
		case nspace_ctype_tag:
			mem = DEREF_member(nspace_named_etc_first(ns));
			extra = DEREF_list(nspace_named_etc_extra(ns));
			break;
		case nspace_unnamed_tag:
			mem = DEREF_member(nspace_unnamed_first(ns));
			extra = DEREF_list(nspace_unnamed_extra(ns));
			if (anon != ANON_GLOBAL && suppress_variable != 2) {
				anon = ANON_NAMESPACE;
			}
			break;
		default:
			mem = DEREF_member(nspace_last(ns));
			extra = NULL_list(IDENTIFIER);
			anon = ANON_NONE;
			break;
		}

		/* Scan through namespace members */
		while (!IS_NULL_member(mem)) {
			IDENTIFIER id = DEREF_id(member_id(mem));
			IDENTIFIER alt = DEREF_id(member_alt(mem));
			if (!IS_NULL_id(id)) {
				n += check_identifier(id, ns, blk, anon, chk);
			}
			if (!IS_NULL_id(alt) && !EQ_id(id, alt)) {
				n += check_identifier(alt, ns, blk, anon, chk);
			}
			mem = DEREF_member(member_next(mem));
		}

		/* Scan through extra namespace members */
		while (!IS_NULL_list(extra)) {
			IDENTIFIER id = DEREF_id(HEAD_list(extra));
			n += check_identifier(id, ns, blk, anon, chk);
			extra = TAIL_list(extra);
		}
	}
	if (spec_unit) {
		spec_unit = save_end(spec_unit, ns);
	}
	return n;
}


/*
    This routine applies the usage checks to the tokens declared in the
    translation unit.
*/

static void
check_token(void)
{
    NAMESPACE ns = token_namespace;
    MEMBER mem = DEREF_member(nspace_global_first(ns));
    while (!IS_NULL_member(mem)) {
	IDENTIFIER id = DEREF_id(member_id(mem));
	if (!IS_NULL_id(id)) {
	    DECL_SPEC ds = DEREF_dspec(id_storage(id));
	    if (!(ds & dspec_done)) {
		if (ds & dspec_defn) {
		    /* Defined token */
		    compile_token(id, 1);
		} else if (!(ds & dspec_pure)) {
		    /* Undefined token */
		    LOCATION loc;
		    TOKEN tok = DEREF_tok(id_token_sort(id));
		    bad_crt_loc++;
		    loc = crt_loc;
		    DEREF_loc(id_loc(id), crt_loc);
		    if (IS_tok_func(tok)) {
			/* Implicitly define 'FUNC' tokens */
			IDENTIFIER fn = DEREF_id(id_token_alt(id));
			COPY_id(tok_func_defn(tok), fn);
			ds |= dspec_defn;
			COPY_dspec(id_storage(id), ds);
			if (!(ds & dspec_explicit)) {
			    /* Not explicitly redeclared */
			    report(crt_loc, ERR_token_def_implicit(id));
			}
			use_func_id(fn, 0, 0);
			compile_function(fn, 0);
			compile_token(id, 1);
		    } else if (ds & dspec_static) {
			/* Check for built-in token definitions */
			if (builtin_token(id)!= -1) {
			    ds = DEREF_dspec(id_storage(id));
			    if (!(ds & dspec_defn)) {
				compile_token(id, 0);
			    }
			} else if (suppress_variable != 2) {
			    compile_token(id, 0);
			}
		    }
		    crt_loc = loc;
		    bad_crt_loc--;
		}
	    }
	}
	mem = DEREF_member(member_next(mem));
    }
    return;
}


/*
    This routine applies check_namespace to the global namespace,
    including checking the main function if complete is true.  It also
    calls check_token.
*/

unsigned long
check_global(int complete)
{
	/* Check main function if necessary */
	unsigned long n;
	int anon = ANON_NONE;
	NAMESPACE ns = global_namespace;
	if (complete && suppress_variable != 2) {
		IDENTIFIER id = main_function;
		HASHID nm = KEYWORD(lex_main);
		if (IS_NULL_id(id)) {
			/* Look up if not defined */
			MEMBER mem = search_member(ns, nm, 0);
			if (!IS_NULL_member(mem)) {
				id = DEREF_id(member_id(mem));
				if (!IS_NULL_id(id) && IS_id_function(id)) {
					main_function = id;
				} else {
					id = NULL_id;
				}
			}
		}
		if (IS_NULL_id(id)) {
			id = DEREF_id(hashid_id(nm));
			id = underlying_id(id);
			report(builtin_loc, ERR_basic_odr_undef(id));
		} else {
			/* Mark as being used */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			ds |= (dspec_used | dspec_called);
			COPY_dspec(id_storage(id), ds);
		}
		anon = ANON_GLOBAL;
	}

	/* Apply checks to namespaces */
	begin_spec();
	n = check_namespace(ns, NULL_exp, anon, 1);
	end_spec();
	check_token();
	return n;
}


/*
    This routine constructs the expression 'set ( a )'.
*/

EXP
make_set_exp(EXP a)
{
	EXP e;
	a = convert_reference(a, REF_NORMAL);
	a = convert_lvalue(a);
	MAKE_exp_set(type_void, a, e);
	return e;
}


/*
    This routine constructs the expression 'unused ( a )'.
*/

EXP
make_unused_exp(EXP a)
{
	EXP e;
	a = convert_reference(a, REF_NORMAL);
	a = convert_lvalue(a);
	MAKE_exp_unused(type_void, a, e);
	return e;
}


/*
    This flag is set to true to indicate that all static identifiers
    should be preserved.
*/

int preserve_all = 0;


/*
    This routine preserves or suspends the static identifier id, as
    indicated by the action act.
*/

void
preserve_id(IDENTIFIER id, int act)
{
	switch (TAG_id(id)) {
	case id_function_tag: {
		IDENTIFIER over = DEREF_id(id_function_over(id));
		if (!IS_NULL_id(over)) {
			preserve_id(over, act);
		}
		goto action_lab;
	}
	case id_variable_tag:
action_lab: {
		    DECL_SPEC ds = DEREF_dspec(id_storage(id));
		    if (ds & dspec_static) {
			    if (act == lex_preserve) {
				    compile_preserve(id);
			    } else if (act == lex_suspend) {
				    ds |= dspec_used;
				    COPY_dspec(id_storage(id), ds);
			    }
		    }
		    break;
	    }
	default: {
		ERROR err = ERR_pragma_preserve_undecl(act, id);
		report(preproc_loc, err);
		break;
	}
	}
	return;
}


/*
    These values are used to mark the various usage states in the flow
    analysis routines.  The fact that va_variable equals dspec_auto and
    va_done equals dspec_done is important, but the other values are
    merely convenient.
*/

typedef DECL_SPEC VAR_INFO;

#define va_none			dspec_none
#define va_used_this		dspec_used
#define va_set			dspec_defn
#define va_maybe_set		dspec_inherit

#define va_filter		(va_used_this | va_set | va_maybe_set)

#define va_any_use		dspec_static
#define va_any_set		dspec_extern

#define va_done			dspec_done
#define va_variable		dspec_auto
#define va_ignore		dspec_ignore
#define va_error		dspec_implicit

#define va_address		dspec_register
#define va_assign		dspec_mutable
#define va_alias_used		dspec_inline
#define va_alias_set		dspec_virtual
#define va_partial		dspec_explicit
#define va_member		dspec_friend
#define va_this			dspec_typedef
#define va_dummy		dspec_pure

#define va_alias		(va_alias_used | va_alias_set)
#define va_becomes		(va_assign | va_dummy)
#define va_other		(va_address | va_becomes | va_partial)
#define va_mask			(va_alias | va_other)

#define va_unreached		dspec_main


/*
    The following declarations are required for the flow analysis
    routines.
*/

static VAR_INFO flow_exp(EXP, VAR_INFO);
static VAR_INFO flow_alias_exp(EXP, VAR_INFO);
static VAR_INFO flow_stmt(EXP, VAR_INFO, int);
static VAR_INFO flow_offset(OFFSET, VAR_INFO, int);
static void set_variable(IDENTIFIER, VAR_INFO);


/*
    The variable crt_flow_vars is used to hold a list of all the local
    variables which are in scope at any point in the variable analysis
    routines.
*/

typedef LIST(VARIABLE) VAR_LIST;
static VAR_LIST crt_flow_vars = NULL_list(VARIABLE);
static VAR_LIST crt_flow_mems = NULL_list(VARIABLE);
static LIST(IDENTIFIER) crt_flow_assign = NULL_list(IDENTIFIER);


/*
    This routine is called at the start of the analysis of the local
    variable id.
*/

static void
start_variable(IDENTIFIER id, DECL_SPEC ds, VAR_INFO use)
{
	VARIABLE var;
	use |= (va_variable | va_done | va_used_this);
	if (!(ds & dspec_used)) {
		use |= va_ignore;
	}
	var.id = id;
	var.info = DEREF_dspec(id_storage(id));
	COPY_dspec(id_storage(id), use);
	CONS_var(var, crt_flow_vars, crt_flow_vars);
	DEREF_loc(id_loc(id), stmt_loc);
	return;
}


/*
    This routine checks whether any variable analysis errors involving
    the local variable id should be ignored.  This is done if id is an
    anonymous identifier or is a const variable all of whose uses have
    been replaced by its definition (see convert_lvalue).
*/

static int
ignore_variable(IDENTIFIER id)
{
	HASHID nm = DEREF_hashid(id_name(id));
	if (IS_hashid_anon(nm)) {
		return 1;
	}
	if (IS_id_variable(id)) {
		TYPE t = DEREF_type(id_variable_type(id));
		CV_SPEC cv = find_cv_qual(t);
		if (cv & cv_volatile) {
			/* Ignore volatile variables */
			return 1;
		}
		if (cv == (cv_const | cv_lvalue)) {
			/* Check for const variables */
			EXP e = DEREF_exp(id_variable_init(id));
			if (!IS_NULL_exp(e)) {
				if (IS_exp_int_lit(e)) {
					return 1;
				}
				if (IS_exp_null(e)) {
					return 1;
				}
			}
		}
	} else if (IS_id_member(id)) {
		TYPE t = DEREF_type(id_member_type(id));
		CV_SPEC cv = find_cv_qual(t);
		if (cv & cv_volatile) {
			/* Ignore volatile members */
			return 1;
		}
	}
	return 0;
}


/*
    This routine marks the end of the variable setting ds.  ret is true if
    this end of scope is due to a return statement.  In particular it
    checks whether the variable has been assigned to and not used.
*/

static VAR_INFO
end_usage(IDENTIFIER id, VAR_INFO ds, int ret)
{
	if (ret && (ds & va_member)) {
		/* Class members are used after return */
		if (ret == 2) {
			set_variable(id, va_member);
			ds = DEREF_dspec(id_storage(id));
		} else {
			ds |= va_used_this;
		}
	} else if (!(ds & va_used_this) && (ds & va_set)) {
		if (!(ds & va_ignore) && !ignore_variable(id)) {
			report(stmt_loc, ERR_stmt_dcl_reset(id));
			ds |= va_error;
		}
		ds |= va_used_this;
	}
	return ds;
}


/*
    This routine is called at the end of the analysis of a local
    variable.  Note that unused variable have already been dealt with.
*/

static void
end_variable(int flow, int ret)
{
	VARIABLE var;
	DESTROY_CONS_var(destroy, var, crt_flow_vars, crt_flow_vars);
	if (flow) {
		VAR_INFO use = DEREF_dspec(id_storage(var.id));
		use = end_usage(var.id, use, ret);
		if (!(use & (va_member | va_ignore))) {
			if (!(use & va_any_use)) {
				/* Not used in reached code */
				if (!ignore_variable(var.id)) {
					LOCATION loc;
					DEREF_loc(id_loc(var.id), loc);
					report(loc,
					       ERR_stmt_dcl_unused(var.id));
				}
			} else if (!(use & va_any_set)) {
				/* Not set in reached code */
				if (!(use & va_error) &&
				    !ignore_variable(var.id)) {
					LOCATION loc;
					DEREF_loc(id_loc(var.id), loc);
					report(loc, ERR_stmt_dcl_unset(var.id));
				}
			}
		}
	}
	COPY_dspec(id_storage(var.id), var.info);
	return;
}


/*
    This routine adjusts the variable analysis information for the local
    variable use according to the analysis state use.
*/

static void
set_variable(IDENTIFIER id, VAR_INFO use)
{
	if (!(use & va_unreached)) {
		VAR_INFO ds = DEREF_dspec(id_storage(id));
		if (use & va_assign) {
			/* Assignment */
			if (use & va_dummy) {
				set_variable(id, va_none);
				ds = DEREF_dspec(id_storage(id));
			}
			if (use & va_partial) {
				/* Partial assignment */
				ds |= (va_maybe_set | va_any_set);
				ds |= va_used_this;
			} else {
				/* Complete assignment */
				ds = end_usage(id, ds, 0);
				if (ds & va_assign) {
					if (!(ds & va_ignore) &&
					    !ignore_variable(id)) {
						/* Multiple assignments */
						report(stmt_loc,
						       ERR_expr_ass_twice(id));
						ds |= va_error;
					}
				}
				CONS_id(id, crt_flow_assign, crt_flow_assign);
				ds |= (va_set | va_maybe_set | va_any_set |
				       va_assign);
				ds &= ~va_used_this;
			}
		} else if (use & va_alias_set) {
			/* Read-write alias */
			ds |= (va_maybe_set | va_any_set);
			ds |= (va_used_this | va_any_use);
		} else if (use & va_alias_used) {
			/* Read-only alias */
			ds |= (va_used_this | va_any_use);
		} else if (use & va_address) {
			/* Address */
			ds |= (va_used_this | va_any_use);
		} else {
			/* Use */
			if (!(ds & (va_set | va_maybe_set))) {
				/* Used without being set */
				if (!(ds & va_ignore) && !ignore_variable(id)) {
					ERROR err;
					if (use & va_member) {
						err = ERR_class_base_init_none(id);
					} else {
						err = ERR_stmt_dcl_unset(id);
					}
					report(stmt_loc, err);
					ds |= va_error;
				}
				ds |= (va_maybe_set | va_any_set);
			}
			ds |= (va_used_this | va_any_use);
		}
		COPY_dspec(id_storage(id), ds);
	}
	return;
}


/*
    This routine calls set_variable for each of the class members in the
    current variable list.
*/

static void
set_members(VAR_INFO use)
{
	if (!(use & va_unreached)) {
		VAR_LIST va = crt_flow_mems;
		while (!IS_NULL_list(va)) {
			IDENTIFIER id = DEREF_id(var_id(HEAD_list(va)));
			set_variable(id, use);
			va = TAIL_list(va);
		}
	}
	return;
}


/*
    This routine merges the variable analysis settings given by dp and dq.
    u indicates whether the variable set values are to be taken from dp,
    from dq, from both, or from neither.
*/

static VAR_INFO
merge_usage(VAR_INFO dp, VAR_INFO dq, int u)
{
	VAR_INFO ds = (dp | dq);
	VAR_INFO dt = dspec_none;
	switch (u) {
	case 0:
		dt = (dp & dq);
		break;
	case 1:
		dt = dp;
		break;
	case 2:
		dt = dq;
		break;
	}
	ds = ((ds & ~va_filter) | (dt & va_filter));
	return ds;
}


/*
    This routine searches the list of variables p for one corresponding to
    id.  q is a member of p which corresponds to id is the simplest case.
    It returns a pointer to the variable if it exists and a null pointer
    otherwise.
*/

static PTR(VARIABLE)
search_vars(VAR_LIST p, VAR_LIST q, IDENTIFIER id)
{
	if (!IS_NULL_list(q)) {
		PTR(VARIABLE) ptr = HEAD_list(q);
		IDENTIFIER pid = DEREF_id(var_id(ptr));
		if (EQ_id(pid, id)) {
			return ptr;
		}
	}
	while (!IS_NULL_list(p)) {
		PTR(VARIABLE) ptr = HEAD_list(p);
		IDENTIFIER pid = DEREF_id(var_id(ptr));
		if (EQ_id(pid, id)) {
			return ptr;
		}
		p = TAIL_list(p);
	}
	return NULL_ptr(VARIABLE);
}


/*
    This routine saves the current variable settings by merging them with
    those stored in the list va.
*/

static VAR_LIST
save_vars(VAR_LIST va, int cond)
{
	VAR_LIST vb = crt_flow_vars;
	VAR_LIST vc = va;
	VAR_LIST vd = va;
	while (!IS_NULL_list(vb)) {
		VARIABLE var;
		PTR(VARIABLE) pvar;
		var.id = DEREF_id(var_id(HEAD_list(vb)));
		var.info = DEREF_dspec(id_storage(var.id));
		if (cond) {
			var.info |= va_used_this;
			COPY_dspec(id_storage(var.id), var.info);
		}
		pvar = search_vars(vc, vd, var.id);
		if (IS_NULL_ptr(pvar)) {
			/* Add new identifier to list */
			CONS_var(var, va, va);
		} else {
			/* Merge with existing information */
			VAR_INFO acc = DEREF_dspec(var_info(pvar));
			acc = merge_usage(acc, var.info, 0);
			COPY_dspec(var_info(pvar), acc);
		}
		if (!IS_NULL_list(vd)) {
			vd = TAIL_list(vd);
		}
		vb = TAIL_list(vb);
	}
	if (IS_NULL_list(vc)) {
		va = REVERSE_list(va);
	}
	return va;
}


/*
    This routine loads the current variable settings by merging them with
    those stored in the list va.
*/

static void
load_vars(VAR_LIST va, int u)
{
	VAR_LIST vb = crt_flow_vars;
	VAR_LIST vc = va;
	while (!IS_NULL_list(vb)) {
		IDENTIFIER id = DEREF_id(var_id(HEAD_list(vb)));
		VAR_INFO acc = DEREF_dspec(id_storage(id));
		PTR(VARIABLE)pvar = search_vars(va, vc, id);
		if (!IS_NULL_ptr(pvar)) {
			VAR_INFO pacc = DEREF_dspec(var_info(pvar));
			acc = merge_usage(acc, pacc, u);
		}
		COPY_dspec(id_storage(id), acc);
		if (!IS_NULL_list(vc)) {
			vc = TAIL_list(vc);
		}
		vb = TAIL_list(vb);
	}
	return;
}


/*
    This routine swaps the current variable settings with those stored in
    the list va.
*/

static void
swap_vars(VAR_LIST va)
{
	while (!IS_NULL_list(va)) {
		VARIABLE var;
		VAR_INFO acc;
		DEREF_var(HEAD_list(va), var);
		acc = DEREF_dspec(id_storage(var.id));
		COPY_dspec(var_info(HEAD_list(va)), acc);
		COPY_dspec(id_storage(var.id), var.info);
		va = TAIL_list(va);
	}
	return;
}


/*
    This routine marks all the variables in the list va with use.
*/

static void
mark_vars(VAR_LIST va, VAR_INFO use)
{
	while (!IS_NULL_list(va)) {
		IDENTIFIER id = DEREF_id(var_id(HEAD_list(va)));
		VAR_INFO acc = DEREF_dspec(id_storage(id));
		acc |= use;
		COPY_dspec(id_storage(id), acc);
		va = TAIL_list(va);
	}
	return;
}


/*
    This routine performs flow analysis on a jump to the label lab.  cond
    is true to indicate a conditional jump.
*/

static VAR_INFO
flow_goto_stmt(IDENTIFIER lab, VAR_INFO use, int cond)
{
	if (!(use & va_unreached)) {
		VAR_INFO ds = DEREF_dspec(id_storage(lab));
		if (ds & dspec_reserve) {
			/* Has backward jump */
			mark_vars(crt_flow_vars, va_used_this);
		} else {
			/* Only forward jumps */
			VAR_LIST va = DEREF_list(id_label_vars(lab));
			va = save_vars(va, cond);
			COPY_list(id_label_vars(lab), va);
		}
		ds |= dspec_temp;
		COPY_dspec(id_storage(lab), ds);
		use |= va_unreached;
	}
	return use;
}


/*
    This routine performs flow analysis on the statement labelled by the
    label lab.
*/

static VAR_INFO
flow_label_stmt(IDENTIFIER lab, VAR_INFO use, int flow)
{
	EXP e = DEREF_exp(id_label_stmt(lab));
	VAR_INFO ds = DEREF_dspec(id_storage(lab));
	if (ds & dspec_reserve) {
		/* Has backward jump */
		mark_vars(crt_flow_vars,(va_maybe_set | va_used_this));
		use &= ~va_unreached;
	} else {
		/* Only forward jumps */
		int unreached = 0;
		VAR_LIST va = DEREF_list(id_label_vars(lab));
		if (use & va_unreached) {
			unreached = 2;
		}
		load_vars(va, unreached);
		DESTROY_list(va, SIZE_var);
		COPY_list(id_label_vars(lab), NULL_list(VARIABLE));
		if (ds & dspec_temp) {
			use &= ~va_unreached;
		}
	}
	if (!IS_NULL_exp(e)) {
		e = DEREF_exp(exp_label_stmt_body(e));
		use = flow_stmt(e, use, flow);
	}
	return use;
}


/*
    This routine is called at each sequence point in the flow analysis
    routines.  It clears the list of identifiers assigned since the last
    sequence point.
*/

static void
flow_sequence_point(void)
{
	LIST(IDENTIFIER) p = crt_flow_assign;
	while (!IS_NULL_list(p)) {
		VAR_INFO ds;
		IDENTIFIER id;
		DESTROY_CONS_id(destroy, id, p, p);
		ds = DEREF_dspec(id_storage(id));
		ds &= ~va_assign;
		COPY_dspec(id_storage(id), ds);
	}
	crt_flow_assign = NULL_list(IDENTIFIER);
	return;
}


/*
    This routine performs flow analysis following a return statement (in
    which case ret is true) or other expression which causes execution to
    cease.
*/

static VAR_INFO
flow_terminate(VAR_INFO use, int ret)
{
	if (!(use & va_unreached)) {
		VAR_LIST va = crt_flow_vars;
		while (!IS_NULL_list(va)) {
			IDENTIFIER id = DEREF_id(var_id(HEAD_list(va)));
			VAR_INFO ds = DEREF_dspec(id_storage(id));
			ds = end_usage(id, ds, ret);
			COPY_dspec(id_storage(id), ds);
			va = TAIL_list(va);
		}
	}
	UNUSED(ret);
	use |= va_unreached;
	return use;
}


/*
    This routine preforms flow analysis on the if expression with condition
    c and branches a and b.
*/

static VAR_INFO
flow_if_exp(EXP c, EXP a, EXP b, VAR_INFO use, int flow)
{
	VAR_LIST va;
	VAR_INFO ua, ub;
	int unreached = 0;
	unsigned cv = eval_const_cond(c);
	if (flow) {
		/* Condition */
		use = flow_exp(c, use);
		flow_sequence_point();
	}
	ua = use;
	ub = use;
	if (cv == BOOL_FALSE) {
		ua |= va_unreached;
	}
	if (cv == BOOL_TRUE) {
		ub |= va_unreached;
	}
	va = save_vars(NULL_list(VARIABLE), 1);
	ua = flow_stmt(a, ua, flow);
	swap_vars(va);
	ub = flow_stmt(b, ub, flow);
	if (ua & va_unreached) {
		unreached |= 1;
	}
	if (ub & va_unreached) {
		unreached |= 2;
	}
	load_vars(va, unreached);
	DESTROY_list(va, SIZE_var);
	use = (ua & ub);
	return use;
}


/*
    This routine processes the flow analysis directive indicated by act
    to the expression e.
*/

static VAR_INFO
flow_set(EXP e, VAR_INFO use, VAR_INFO act)
{
	if (!(use & va_unreached) && !IS_NULL_exp(e)) {
		EXP a = NULL_exp;
		if (IS_exp_contents(e)) {
			/* Check for simple lvalues */
			a = DEREF_exp(exp_contents_ptr(e));
		} else if (IS_exp_address(e)) {
			/* Check for array to pointer conversions */
			EXP b = DEREF_exp(exp_address_arg(e));
			TYPE s = DEREF_type(exp_type(b));
			if (IS_type_array(s)) {
				a = b;
			}
		}
		if (!IS_NULL_exp(a) && IS_exp_identifier(a)) {
			IDENTIFIER id = DEREF_id(exp_identifier_id(a));
			if (IS_id_variable_etc(id)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					if (act & va_set) {
						/* Set variable */
						ds |= (va_set | va_maybe_set |
						       va_any_set);
						ds &= ~va_used_this;
					} else {
						/* Unused variable */
						set_variable(id, act);
						ds = DEREF_dspec(id_storage(id));
						ds &= ~(va_set | va_maybe_set);
					}
					COPY_dspec(id_storage(id), ds);
				}
			}
		}
	}
	return use;
}


/*
    This routine performs flow analysis on the list of token arguments p.
*/

static VAR_INFO
flow_token_list(LIST(TOKEN) p, VAR_INFO use)
{
	while (!IS_NULL_list(p)) {
		TOKEN tok = DEREF_tok(HEAD_list(p));
		if (!IS_NULL_tok(tok)) {
			switch (TAG_tok(tok)) {
			case tok_exp_tag: {
				/* Expression tokens */
				EXP e = DEREF_exp(tok_exp_value(tok));
				use = flow_alias_exp(e, use);
				break;
			}
			case tok_stmt_tag: {
				/* Statement tokens */
				EXP e = DEREF_exp(tok_stmt_value(tok));
				use = flow_stmt(e, use, 1);
				break;
			}
			case tok_member_tag: {
				/* Member tokens */
				OFFSET off = DEREF_off(tok_member_value(tok));
				use = flow_offset(off, use, 0);
				break;
			}
			}
		}
		p = TAIL_list(p);
	}
	return use;
}


/*
    This routine performs flow analysis on the offset off.  mem is true
    in member functions when the offset is being added to 'this'.
*/

static VAR_INFO
flow_offset(OFFSET off, VAR_INFO use, int mem)
{
	DECL_SPEC ua = (use & ~va_mask);
	if (IS_NULL_off(off)) {
		return ua;
	}
	assert(ORDER_off == 13);
	switch (TAG_off(off)) {
	case off_member_tag:
		/* Member offsets */
		if (mem) {
			IDENTIFIER id = DEREF_id(off_member_id(off));
			VAR_INFO ds = DEREF_dspec(id_storage(id));
			if (ds & va_variable) {
				set_variable(id, use);
			}
		}
		break;
	case off_ptr_mem_tag: {
		/* Pointer to member offsets */
		EXP a = DEREF_exp(off_ptr_mem_arg(off));
		ua = flow_exp(a, ua);
		break;
	}
	case off_negate_tag: {
		/* Negated offsets */
		OFFSET off1 = DEREF_off(off_negate_arg(off));
		ua = flow_offset(off1, ua, 0);
		break;
	}
	case off_plus_tag: {
		/* Offset addition */
		OFFSET off1 = DEREF_off(off_plus_arg1(off));
		OFFSET off2 = DEREF_off(off_plus_arg2(off));
		ua = flow_offset(off1, ua, 0);
		ua = flow_offset(off2, ua, 0);
		break;
	}
	case off_mult_tag: {
		/* Offset multiplication */
		OFFSET off1 = DEREF_off(off_mult_arg1(off));
		EXP a = DEREF_exp(off_mult_arg2(off));
		ua = flow_offset(off1, ua, 0);
		ua = flow_exp(a, ua);
		break;
	}
	case off_ptr_diff_tag: {
		/* Difference of two pointers */
		EXP a = DEREF_exp(off_ptr_diff_ptr1(off));
		EXP b = DEREF_exp(off_ptr_diff_ptr2(off));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		break;
	}
	case off_token_tag: {
		/* Tokenised offsets */
		LIST(TOKEN)args = DEREF_list(off_token_args(off));
		ua = flow_token_list(args, ua);
		break;
	}
	}
	ua &= ~va_mask;
	return ua;
}


/*
    This routine performs flow analysis on the list of expressions p.
*/

static VAR_INFO
flow_exp_list(LIST(EXP) p, VAR_INFO use, int fn)
{
	while (!IS_NULL_list(p)) {
		EXP a = DEREF_exp(HEAD_list(p));
		if (!IS_NULL_exp(a)) {
			VAR_INFO ua;
			if (fn) {
				ua = flow_alias_exp(a, use);
			} else {
				ua = flow_exp(a, use);
			}
			if (ua & va_unreached) {
				use |= va_unreached;
			}
		}
		p = TAIL_list(p);
	}
	return use;
}


/*
    This routine performs flow analysis on the expression e which may be
    aliased by being on the right hand side of an assignment.  Note that
    there are read-only and read-write aliases, depending on whether the
    access is through a pointer or reference to const or not.
*/

static VAR_INFO
flow_alias_exp(EXP e, VAR_INFO use)
{
	VAR_INFO ua = (use | va_alias_used);
	if (!IS_NULL_exp(e)) {
		TYPE t = DEREF_type(exp_type(e));
		CV_SPEC cv = find_cv_qual(t);
		if (cv & cv_lvalue) {
			/* Aliased via lvalue */
			if (!(cv & cv_const)) {
				ua |= va_alias_set;
			}
		}
		if (IS_type_ptr_etc(t)) {
			/* Aliased via pointer or reference */
			TYPE s = DEREF_type(type_ptr_etc_sub(t));
			cv = find_cv_qual(s);
			if (!(cv & cv_const)) {
				ua |= va_alias_set;
			}
		}
	}
	ua = flow_exp(e, ua);
	return ua;
}


/*
    This routine performs flow analysis on the expression e.
*/

static VAR_INFO
flow_exp(EXP e, VAR_INFO use)
{
	VAR_INFO ua = (use & ~va_mask);
	if (IS_NULL_exp(e)) {
		return ua;
	}
	assert(ORDER_exp == 88);
	switch (TAG_exp(e)) {
	case exp_identifier_tag: {
		/* Identifier expressions */
		IDENTIFIER id = DEREF_id(exp_identifier_id(e));
		if (IS_id_variable_etc(id)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_auto) {
				set_variable(id, use);
				if ((ds & va_this) && (use & va_alias)) {
					/* Allow for aliasing using 'this' */
					set_members(use);
				}
			}
		}
		break;
	}
	case exp_assign_tag: {
		/* Assignment expressions */
		EXP a = DEREF_exp(exp_assign_ref(e));
		EXP b = DEREF_exp(exp_assign_arg(e));
		ua = flow_alias_exp(b, ua);
		if (ua & va_unreached) {
			use |= va_unreached;
		}
		ua = flow_exp(a,(use | va_assign));
		break;
	}
	case exp_init_tag: {
		/* Initialisation expressions */
		EXP a = DEREF_exp(exp_init_arg(e));
		ua = flow_alias_exp(a, ua);
		if (ua & va_unreached) {
			use |= va_unreached;
		}
		if (!IS_NULL_exp(a)) {
			IDENTIFIER id = DEREF_id(exp_init_id(e));
			if (IS_id_variable(id)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					/* Initialiser expression */
					set_variable(id,(use | va_assign));
					break;
				}
			}
		}
		break;
	}
	case exp_preinc_tag: {
		/* Pre-increment expressions */
		EXP a = DEREF_exp(exp_preinc_ref(e));
		EXP b = DEREF_exp(exp_preinc_op(e));
		EXP c = DEREF_exp(exp_dummy_value(a));
		int op = DEREF_int(exp_preinc_becomes(e));
		if (op == lex_assign) {
			/* Bitfield assignment */
			ua = flow_alias_exp(b, ua);
			if (ua & va_unreached) {
				use |= va_unreached;
			}
			if (!IS_NULL_list(crt_flow_mems) && is_this_exp(c)) {
				/* Have 'this->off' */
				OFFSET off = DEREF_off(exp_dummy_off(a));
				ua = flow_offset(off,(use | va_assign), 1);
				break;
			}
			use |= va_partial;
		} else {
			COPY_exp(exp_dummy_value(a), NULL_exp);
			ua = flow_exp(b, ua);
			COPY_exp(exp_dummy_value(a), c);
			if (ua & va_unreached) {
				use |= va_unreached;
			}
			use |= va_becomes;
		}
		ua = flow_exp(c,(use | va_assign));
		break;
	}
	case exp_postinc_tag: {
		/* Post-increment expressions */
		EXP a = DEREF_exp(exp_postinc_ref(e));
		EXP b = DEREF_exp(exp_postinc_op(e));
		EXP c = DEREF_exp(exp_dummy_value(a));
		COPY_exp(exp_dummy_value(a), NULL_exp);
		ua = flow_exp(b, ua);
		COPY_exp(exp_dummy_value(a), c);
		if (ua & va_unreached) {
			use |= va_unreached;
		}
		ua = flow_exp(a,(use | va_becomes));
		break;
	}
	case exp_indir_tag: {
		/* Indirection expressions */
		EXP a = DEREF_exp(exp_indir_ptr(e));
		if (!IS_NULL_list(crt_flow_mems) && is_this_exp(e)) {
			/* Have '*this' */
			set_members(use);
			break;
		}
		if (IS_exp_add_ptr(a)) {
			EXP b = DEREF_exp(exp_add_ptr_ptr(a));
			OFFSET off = DEREF_off(exp_add_ptr_off(a));
			if (!IS_NULL_list(crt_flow_mems) && is_this_exp(b)) {
				/* Have 'this->off' */
				ua = flow_offset(off, use, 1);
				break;
			}
			if (IS_exp_address(b)) {
				/* Have 'c.off' */
				EXP c = DEREF_exp(exp_address_arg(b));
				ua = flow_offset(off, use, 0);
				if (ua & va_unreached) {
					use |= va_unreached;
				}
				ua = flow_exp(c,(use | va_partial));
				break;
			}
		} else if (IS_exp_address(a)) {
			/* Have '*&b' */
			EXP b = DEREF_exp(exp_address_arg(a));
			ua = flow_exp(b, use);
			break;
		}
		ua = flow_exp(a, ua);
		break;
	}
	case exp_contents_tag: {
		/* Contents expressions */
		EXP a = DEREF_exp(exp_contents_ptr(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_address_tag: {
		/* Address expressions */
		EXP a = DEREF_exp(exp_address_arg(e));
		if (IS_exp_indir(a) && !is_this_exp(a)) {
			EXP b = DEREF_exp(exp_indir_ptr(a));
			TYPE t = DEREF_type(exp_type(b));
			if (!IS_type_ref(t)) {
				ua = flow_exp(b, use);
				break;
			}
		}
		ua = (use & ~va_other);
		ua = flow_exp(a,(ua | va_address));
		break;
	}
	case exp_address_mem_tag: {
		/* Member address expressions */
		EXP a = DEREF_exp(exp_address_mem_arg(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_func_tag: {
		/* Function expressions */
		TYPE t = DEREF_type(exp_type(e));
		EXP a = DEREF_exp(exp_func_fn(e));
		LIST(EXP)args = DEREF_list(exp_func_args(e));
		ua = flow_exp(a, ua);
		ua = flow_exp_list(args, ua, 1);
		if (IS_type_bottom(t)) {
			/* Deal with functions like exit */
			ua = flow_terminate(ua, 1);
		}
		break;
	}
	case exp_func_id_tag: {
		/* Function expressions */
		TYPE t = DEREF_type(exp_type(e));
		LIST(EXP) args = DEREF_list(exp_func_id_args(e));
		ua = flow_exp_list(args, ua, 1);
		if (IS_type_bottom(t)) {
			/* Deal with functions like exit */
			ua = flow_terminate(ua, 1);
		}
		break;
	}
	case exp_call_tag: {
		/* Pointer to member function expressions */
		EXP a = DEREF_exp(exp_call_ptr(e));
		EXP b = DEREF_exp(exp_call_arg(e));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		break;
	}
	case exp_negate_tag:
	case exp_compl_tag:
	case exp_not_tag:
	case exp_abs_tag: {
		/* Unary expressions */
		EXP a = DEREF_exp(exp_negate_etc_arg(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_plus_tag:
	case exp_minus_tag:
	case exp_mult_tag:
	case exp_div_tag:
	case exp_rem_tag:
	case exp_and_tag:
	case exp_or_tag:
	case exp_xor_tag:
	case exp_lshift_tag:
	case exp_rshift_tag:
	case exp_max_tag:
	case exp_min_tag: {
		/* Binary expressions */
		EXP a = DEREF_exp(exp_plus_etc_arg1(e));
		EXP b = DEREF_exp(exp_plus_etc_arg2(e));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		break;
	}
	case exp_log_and_tag:
	case exp_log_or_tag: {
		/* Logical expressions */
		EXP a = DEREF_exp(exp_plus_etc_arg1(e));
		EXP b = DEREF_exp(exp_plus_etc_arg2(e));
		ua = flow_exp(a, ua);
		flow_sequence_point();
		ua = flow_exp(b, ua);
		break;
	}
	case exp_test_tag: {
		/* Test expressions */
		EXP a = DEREF_exp(exp_test_arg(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_compare_tag: {
		/* Comparison expressions */
		EXP a = DEREF_exp(exp_compare_arg1(e));
		EXP b = DEREF_exp(exp_compare_arg2(e));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		break;
	}
	case exp_cast_tag: {
		/* Cast expressions */
		TYPE t = DEREF_type(exp_type(e));
		EXP a = DEREF_exp(exp_cast_arg(e));
		ua = (use & ~va_other);
		ua = flow_exp(a, ua);
		if (IS_type_bottom(t)) {
			/* Allow for casting to bottom */
			ua = flow_terminate(ua, 1);
		}
		break;
	}
	case exp_base_cast_tag: {
		/* Base cast expressions */
		EXP a = DEREF_exp(exp_base_cast_arg(e));
		ua = (use & ~va_other);
		ua = flow_exp(a, ua);
		break;
	}
	case exp_dyn_cast_tag: {
		/* Dynamic cast expressions */
		EXP a = DEREF_exp(exp_dyn_cast_arg(e));
		ua = (use & ~va_other);
		ua = flow_exp(a, ua);
		break;
	}
	case exp_add_ptr_tag: {
		/* Pointer addition expressions */
		EXP a = DEREF_exp(exp_add_ptr_ptr(e));
		OFFSET off = DEREF_off(exp_add_ptr_off(e));
		if (!IS_NULL_list(crt_flow_mems) && is_this_exp(a)) {
			/* Have 'this->off' */
			use &= ~va_other;
			ua = flow_offset(off, use, 1);
			break;
		}
		ua = flow_offset(off, ua, 0);
		if (ua & va_unreached) {
			use |= va_unreached;
		}
		use &= ~va_other;
		ua = flow_exp(a, use);
		break;
	}
	case exp_offset_size_tag: {
		/* Offset expressions */
		OFFSET off = DEREF_off(exp_offset_size_off(e));
		ua = flow_offset(off, ua, 0);
		break;
	}
	case exp_constr_tag: {
		/* Constructor calls */
		EXP a = DEREF_exp(exp_constr_call(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_destr_tag: {
		/* Destructor calls */
		EXP a = DEREF_exp(exp_destr_call(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_alloc_tag: {
		/* Allocation expressions */
		EXP a = DEREF_exp(exp_alloc_call(e));
		EXP b = DEREF_exp(exp_alloc_init(e));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		break;
	}
	case exp_dealloc_tag: {
		/* Deallocation expressions */
		EXP a = DEREF_exp(exp_dealloc_term(e));
		EXP b = DEREF_exp(exp_dealloc_call(e));
		EXP c = DEREF_exp(exp_dealloc_arg(e));
		EXP d = DEREF_exp(exp_dummy_value(c));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		ua = flow_set(d, ua, va_none);
		break;
	}
	case exp_rtti_tag: {
		/* Run-time type information expressions */
		EXP a = DEREF_exp(exp_rtti_arg(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_dynamic_tag: {
		/* Dynamic initialiser expressions */
		EXP a = DEREF_exp(exp_dynamic_arg(e));
		ua = flow_exp(a, ua);
		break;
	}
	case exp_aggregate_tag: {
		/* Aggregate initialiser expressions */
		LIST(EXP) args;
		args = DEREF_list(exp_aggregate_args(e));
		ua = flow_exp_list(args, ua, 0);
		break;
	}
	case exp_initialiser_tag: {
		/* Constructor initialiser expressions */
		int kind = DEREF_int(exp_initialiser_kind(e));
		LIST(EXP) p = DEREF_list(exp_initialiser_args(e));
		LIST(OFFSET) q = DEREF_list(exp_initialiser_offs(e));
		if (kind == 0) {
			q = NULL_list(OFFSET);
		}
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			ua = flow_exp(a, ua);
			if (!IS_NULL_list(q)) {
				OFFSET off = DEREF_off(HEAD_list(q));
				if (kind != DEFAULT_DESTR && !IS_NULL_exp(a)) {
					ua |= va_assign;
				}
				ua = flow_offset(off, ua, 1);
				flow_sequence_point();
				q = TAIL_list(q);
			}
			p = TAIL_list(p);
		}
		break;
	}
	case exp_nof_tag: {
		/* Array initialiser expressions */
		EXP a = DEREF_exp(exp_nof_start(e));
		EXP b = DEREF_exp(exp_nof_pad(e));
		EXP c = DEREF_exp(exp_nof_end(e));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		ua = flow_exp(c, ua);
		break;
	}
	case exp_comma_tag: {
		/* Comma expressions */
		LIST(EXP) p = DEREF_list(exp_comma_args(e));
		if (!IS_NULL_list(p)) {
			EXP a;
			for (;;) {
				a = DEREF_exp(HEAD_list(p));
				p = TAIL_list(p);
				if (IS_NULL_list(p)) {
					break;
				}
				ua = flow_exp(a, ua);
				flow_sequence_point();
				if (ua & va_unreached) {
					use |= va_unreached;
				}
			}
			ua = flow_exp(a, use);
		}
		break;
	}
	case exp_if_stmt_tag: {
		/* Conditional expressions */
		EXP c = DEREF_exp(exp_if_stmt_cond(e));
		EXP a = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b = DEREF_exp(exp_if_stmt_false_code(e));
		ua = flow_if_exp(c, a, b, ua, 1);
		break;
	}
	case exp_exception_tag: {
		/* Exception expressions */
		EXP a = DEREF_exp(exp_exception_arg(e));
		ua = flow_exp(a, ua);
		ua = flow_terminate(ua, 1);
		break;
	}
	case exp_set_tag: {
		/* Set expressions */
		EXP a = DEREF_exp(exp_set_arg(e));
		ua = flow_set(a, ua, va_set);
		break;
	}
	case exp_unused_tag: {
		/* Unused expressions */
		EXP a = DEREF_exp(exp_unused_arg(e));
		ua = flow_set(a, ua, va_none);
		break;
	}
	case exp_op_tag: {
		/* Undetermined expressions */
		EXP a = DEREF_exp(exp_op_arg1(e));
		EXP b = DEREF_exp(exp_op_arg2(e));
		ua = flow_exp(a, ua);
		ua = flow_exp(b, ua);
		break;
	}
	case exp_opn_tag: {
		/* Undetermined expressions */
		LIST(EXP) args = DEREF_list(exp_opn_args(e));
		ua = flow_exp_list(args, ua, 0);
		break;
	}
	case exp_token_tag: {
		/* Tokenised expressions */
		LIST(TOKEN) args = DEREF_list(exp_token_args(e));
		ua = flow_token_list(args, ua);
		break;
	}
	case exp_dummy_tag: {
		/* Dummy expressions */
		EXP a = DEREF_exp(exp_dummy_value(e));
		ua = flow_exp(a, use);
		break;
	}
	case exp_paren_tag:
	case exp_copy_tag: {
		/* Parenthesised expressions */
		EXP a = DEREF_exp(exp_paren_etc_arg(e));
		ua = flow_exp(a, use);
		break;
	}
	case exp_location_tag: {
		/* Location expressions */
		EXP a = DEREF_exp(exp_location_arg(e));
		ua = flow_exp(a, use);
		DEREF_loc(exp_location_end(e), stmt_loc);
		break;
	}
	case exp_sequence_tag:
	case exp_solve_stmt_tag:
	case exp_decl_stmt_tag:
	case exp_while_stmt_tag:
	case exp_do_stmt_tag:
	case exp_switch_stmt_tag:
	case exp_hash_if_tag:
	case exp_return_stmt_tag:
	case exp_goto_stmt_tag:
	case exp_label_stmt_tag:
	case exp_try_block_tag:
	case exp_handler_tag:
	case exp_reach_tag:
	case exp_unreach_tag:
		/* Statements */
		ua = flow_stmt(e, ua, 1);
		break;
	}
	ua &= ~va_mask;
	return ua;
}


/*
    This routine performs flow analysis for any destructors called by
    the goto or return statement a.  b gives smallest statement enclosing
    both the jump and its destination.
*/

static void
flow_jump(EXP a, EXP b)
{
	unsigned long d = no_destructors;
	while (!IS_NULL_exp(a) && !EQ_exp(a, b) && d) {
		/* Scan up to enclosing statement */
		if (IS_exp_decl_stmt(a)) {
			IDENTIFIER id = DEREF_id(exp_decl_stmt_id(a));
			if (IS_id_variable(id)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if (ds & dspec_auto) {
					/* Local variable */
					EXP term =
					    DEREF_exp(id_variable_term(id));
					if (!IS_NULL_exp(term)) {
						if (do_usage) {
							dump_destr(id,
								   &stmt_loc);
						}
						d--;
					}
				}
			}
		}
		a = get_parent_stmt(a);
	}
	return;
}


/*
    This routine performs flow analysis on the while statement e.
*/

static VAR_INFO
flow_while_stmt(EXP e, VAR_INFO use, int flow)
{
	VAR_INFO ua;
	EXP c = DEREF_exp(exp_while_stmt_cond(e));
	EXP a = DEREF_exp(exp_while_stmt_body(e));
	IDENTIFIER blab = DEREF_id(exp_while_stmt_break_lab(e));
	IDENTIFIER clab = DEREF_id(exp_while_stmt_cont_lab(e));
	unsigned cv = eval_const_cond(c);
	if (flow) {
		use = flow_exp(c, use);
		flow_sequence_point();
	}
	ua = use;
	if (cv != BOOL_TRUE) {
		IGNORE flow_goto_stmt(blab, use, 1);
		if (cv == BOOL_FALSE) {
			ua |= va_unreached;
		}
	}
	ua = flow_stmt(a, ua, flow);
	ua = flow_label_stmt(clab, ua, flow);
	if (flow) {
		IGNORE flow_exp(c, ua);
		flow_sequence_point();
	}
	mark_vars(crt_flow_vars, va_used_this);
	use = flow_label_stmt(blab,(use | va_unreached), flow);
	return use;
}


/*
    This routine performs flow analysis on the do statement e.
*/

static VAR_INFO
flow_do_stmt(EXP e, VAR_INFO use, int flow)
{
	EXP c = DEREF_exp(exp_do_stmt_cond(e));
	EXP a = DEREF_exp(exp_do_stmt_body(e));
	IDENTIFIER blab = DEREF_id(exp_do_stmt_break_lab(e));
	IDENTIFIER clab = DEREF_id(exp_do_stmt_cont_lab(e));
	unsigned cv = eval_const_cond(c);
	use = flow_stmt(a, use, flow);
	use = flow_label_stmt(clab, use, flow);
	if (flow) {
		use = flow_exp(c, use);
		flow_sequence_point();
	}
	mark_vars(crt_flow_vars, va_used_this);
	if (cv == BOOL_TRUE) {
		use |= va_unreached;
	}
	use = flow_label_stmt(blab, use, flow);
	return use;
}


/*
    This routine performs flow analysis on the solve statement e with
    associated variables p.
*/

static VAR_INFO
flow_solve_stmt(EXP e, LIST(IDENTIFIER) p, VAR_INFO use, int flow)
{
	if (!IS_NULL_list(p)) {
		/* Scan through variables */
		IDENTIFIER id = DEREF_id(HEAD_list(p));
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if ((ds & dspec_auto) && !(ds & dspec_done)) {
			start_variable(id, ds, va_none);
			use = flow_solve_stmt(e, TAIL_list(p), use, flow);
			end_variable(flow, 0);
			return use;
		}
		use = flow_solve_stmt(e, TAIL_list(p), use, flow);
		return use;
	}
	use = flow_stmt(e, use, flow);
	return use;
}


/*
    This routine performs flow analysis on the switch statement e.
*/

static VAR_INFO
flow_switch_stmt(EXP e, VAR_INFO use, int flow)
{
	EXP a = DEREF_exp(exp_switch_stmt_body(e));
	int exhaust = DEREF_int(exp_switch_stmt_exhaust(e));
	LIST(IDENTIFIER) p = DEREF_list(exp_switch_stmt_case_labs(e));
	IDENTIFIER dlab = DEREF_id(exp_switch_stmt_default_lab(e));
	IDENTIFIER blab = DEREF_id(exp_switch_stmt_break_lab(e));
	if (flow) {
		/* Deal with control statement */
		EXP c = DEREF_exp(exp_switch_stmt_control(e));
		use = flow_exp(c, use);
		flow_sequence_point();
	}
	if (!IS_NULL_id(dlab)) {
		/* Mark jumps to default statement */
		dlab = DEREF_id(id_alias(dlab));
		IGNORE flow_goto_stmt(dlab, use, 1);
		exhaust = 1;
	}
	while (!IS_NULL_list(p)) {
		/* Mark jumps to case statements */
		IDENTIFIER clab = DEREF_id(HEAD_list(p));
		clab = DEREF_id(id_alias(clab));
		if (!EQ_id(clab, dlab)) {
			/* Only mark each label once */
			IGNORE flow_goto_stmt(clab, use, 1);
			dlab = clab;
		}
		p = TAIL_list(p);
	}
	if (!exhaust) {
		/* Break label is reached in non-exhaustive cases */
		IGNORE flow_goto_stmt(blab, use, 1);
	}
	use = flow_stmt(a,(use | va_unreached), flow);
	use = flow_label_stmt(blab, use, flow);
	return use;
}


/*
    This routine performs flow analysis on the try block e.
*/

static VAR_INFO
flow_try_block(EXP e, VAR_INFO use, int flow)
{
	VAR_INFO ua = (use | va_unreached);
	EXP a = DEREF_exp(exp_try_block_body(e));
	LIST(EXP) p = DEREF_list(exp_try_block_handlers(e));
	EXP c = DEREF_exp(exp_try_block_ellipsis(e));
	use = flow_stmt(a, use, flow);
	/* NOT YET IMPLEMENTED */
	while (!IS_NULL_list(p)) {
		EXP b = DEREF_exp(HEAD_list(p));
		IGNORE flow_stmt(b, ua, flow);
		p = TAIL_list(p);
	}
	IGNORE flow_stmt(c, ua, flow);
	return use;
}


/*
    This routine performs flow analysis on the declaration statement e.
*/

static VAR_INFO
flow_decl_stmt(EXP e, VAR_INFO use, int flow)
{
	EXP a = DEREF_exp(exp_decl_stmt_body(e));
	IDENTIFIER id = DEREF_id(exp_decl_stmt_id(e));
	if (IS_id_variable(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_auto) {
			/* Local variable */
			EXP b = DEREF_exp(id_variable_init(id));
			EXP d = DEREF_exp(id_variable_term(id));
			if (!IS_NULL_exp(d)) {
				no_destructors++;
			}
			if (!(ds & dspec_done)) {
				start_variable(id, ds, va_none);
			}
			if (!IS_NULL_exp(b)) {
				/* Initialiser expression */
				if (flow) {
					use = flow_alias_exp(b, use);
				}
				set_variable(id,(use | va_assign));
				flow_sequence_point();
			}
			use = flow_stmt(a, use, flow);
			if (flow) {
				/* Destructor */
				use = flow_exp(d, use);
				flow_sequence_point();
			}
			if (!(ds & dspec_done)) {
				end_variable(flow, 0);
			}
			if (!IS_NULL_exp(d)) {
				no_destructors--;
			}
			return use;
		}
	}
	use = flow_stmt(a, use, flow);
	return use;
}


/*
    This routine performs flow analysis on the statement e.
*/

static VAR_INFO
flow_stmt(EXP e, VAR_INFO use, int flow)
{
	/* Deal with statements */
	VAR_INFO ua = (use & ~va_mask);
	if (IS_NULL_exp(e)) {
		return ua;
	}
	assert(ORDER_exp == 88);
	switch (TAG_exp(e)) {
	case exp_sequence_tag: {
		/* Compound statements */
		LIST(EXP) p = DEREF_list(exp_sequence_first(e));
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			if (!IS_NULL_exp(a)) {
				VAR_INFO ub = flow_stmt(a, ua, flow);
				if (ub & va_unreached) {
					ua |= va_unreached;
				} else {
					ua &= ~va_unreached;
				}
			}
			p = TAIL_list(p);
		}
		break;
	}
	case exp_solve_stmt_tag: {
		/* Solve statements */
		LIST(IDENTIFIER) p;
		EXP a = DEREF_exp(exp_solve_stmt_body(e));
		p = DEREF_list(exp_solve_stmt_vars(e));
		ua = flow_solve_stmt(a, p, ua, flow);
		break;
	}
	case exp_decl_stmt_tag:
		/* Declaration statements */
		ua = flow_decl_stmt(e, ua, flow);
		break;
	case exp_if_stmt_tag: {
		/* Conditional statements */
		EXP c = DEREF_exp(exp_if_stmt_cond(e));
		EXP a = DEREF_exp(exp_if_stmt_true_code(e));
		EXP b = DEREF_exp(exp_if_stmt_false_code(e));
		ua = flow_if_exp(c, a, b, ua, flow);
		break;
	}
	case exp_while_stmt_tag:
		/* While statements */
		ua = flow_while_stmt(e, ua, flow);
		break;
	case exp_do_stmt_tag:
		/* Do statements */
		ua = flow_do_stmt(e, ua, flow);
		break;
	case exp_switch_stmt_tag:
		/* Switch statements */
		ua = flow_switch_stmt(e, ua, flow);
		break;
	case exp_hash_if_tag: {
		/* Target dependent conditional statements */
		EXP c = DEREF_exp(exp_hash_if_cond(e));
		EXP a = DEREF_exp(exp_hash_if_true_code(e));
		EXP b = DEREF_exp(exp_hash_if_false_code(e));
		ua = flow_if_exp(c, a, b, ua, flow);
		break;
	}
	case exp_return_stmt_tag: {
		/* Return statements */
		EXP a = DEREF_exp(exp_return_stmt_value(e));
		if (flow) {
			ua = flow_exp(a, ua);
			flow_sequence_point();
		}
		ua = flow_terminate(ua, 2);
		flow_jump(e, NULL_exp);
		break;
	}
	case exp_goto_stmt_tag: {
		/* Goto statements */
		EXP join = DEREF_exp(exp_goto_stmt_join(e));
		IDENTIFIER lab = DEREF_id(exp_goto_stmt_label(e));
		lab = DEREF_id(id_alias(lab));
		ua = flow_goto_stmt(lab, ua, 0);
		flow_jump(e, join);
		break;
	}
	case exp_label_stmt_tag: {
		/* Labelled statements */
		IDENTIFIER lab = DEREF_id(exp_label_stmt_label(e));
		ua = flow_label_stmt(lab, ua, flow);
		break;
	}
	case exp_try_block_tag:
		/* Try blocks */
		ua = flow_try_block(e, ua, flow);
		break;
	case exp_handler_tag: {
		/* Exception handlers */
		EXP a = DEREF_exp(exp_handler_body(e));
		ua = flow_stmt(a, ua, flow);
		break;
	}
	case exp_reach_tag: {
		/* Reached statements */
		EXP a = DEREF_exp(exp_reach_body(e));
		ua &= ~va_unreached;
		ua = flow_stmt(a, ua, flow);
		break;
	}
	case exp_unreach_tag: {
		/* Unreached statements */
		EXP a = DEREF_exp(exp_unreach_body(e));
		ua |= va_unreached;
		ua = flow_stmt(a, ua, flow);
		break;
	}
	case exp_location_tag: {
		/* Location expressions */
		EXP a = DEREF_exp(exp_location_arg(e));
		ua = flow_stmt(a, use, flow);
		DEREF_loc(exp_location_end(e), stmt_loc);
		break;
	}
	default:
		/* Simple expressions */
		if (!(ua & va_unreached) && flow) {
			ua = flow_exp(e, ua);
			flow_sequence_point();
		}
		break;
	}
	ua &= ~va_mask;
	return ua;
}


/*
    This routine performs the flow analysis on the compound statement e
    which defines the function id.  Full flow analysis is enabled if
    flow is true, otherwise a minimal scan sufficient to determine all
    implicit destructor calls is done.
*/

void
check_flow(IDENTIFIER id, EXP e, int flow)
{
	VAR_INFO use;
	LIST(IDENTIFIER) pids;
	if (IS_id_function_etc(id)) {
		TYPE t = DEREF_type(id_function_etc_type(id));
		while (IS_type_templ(t)) {
			t = DEREF_type(type_templ_defn(t));
		}
		if (IS_id_mem_func(id)) {
			/* Allow for 'this' parameter and class members */
			IDENTIFIER pid = this_param(id, 0);
			if (flow) {
				HASHID nm = DEREF_hashid(id_name(id));
				CLASS_TYPE ct = parent_class(id);
				NAMESPACE ns = DEREF_nspace(ctype_member(ct));
				MEMBER mem =
				    DEREF_member(nspace_ctype_first(ns));
				mem = next_data_member(mem, 0);
				while (!IS_NULL_member(mem)) {
					IDENTIFIER mid =
					    DEREF_id(member_id(mem));
					start_variable(mid, dspec_used,
						       va_member);
					if (!IS_hashid_constr(nm)) {
						/* Members are set except in
						 * constructors */
						set_variable(mid, va_assign);
						set_variable(mid, va_none);
					}
					mem = DEREF_member(member_next(mem));
					mem = next_data_member(mem, 0);
				}
				crt_flow_mems = crt_flow_vars;
			}
			if (!IS_NULL_id(pid)) {
				start_variable(pid, dspec_none, va_this);
				set_variable(pid, va_assign);
			}
		}
		pids = DEREF_list(type_func_pids(t));
		while (!IS_NULL_list(pids)) {
			/* Set up parameter scopes */
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			if (!IS_NULL_id(pid)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(pid));
				start_variable(pid, ds, va_none);
				set_variable(pid, va_assign);
			}
			pids = TAIL_list(pids);
		}
	}
	DEREF_loc(id_loc(id), stmt_loc);
	flow_sequence_point();
	use = flow_stmt(e, va_none, flow);
	IGNORE flow_terminate(use, 2);
	crt_flow_mems = NULL_list(VARIABLE);
	while (!IS_NULL_list(crt_flow_vars)) {
		/* End parameter and member scopes */
		end_variable(flow, 2);
	}
	stmt_loc = crt_loc;
	return;
}
