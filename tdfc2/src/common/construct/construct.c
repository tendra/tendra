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

#include <syntax/syntax.h>

#include <parse/constant.h>
#include <parse/hash.h>
#include <parse/predict.h>

#include <construct/access.h>
#include <construct/allocate.h>
#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/check.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/copy.h>
#include <construct/chktype.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <construct/destroy.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/instance.h>
#include <construct/label.h>
#include <construct/namespace.h>
#include <construct/operator.h>
#include <construct/overload.h>
#include <construct/statement.h>
#include <construct/template.h>
#include <construct/token.h>

#include <output/capsule.h>
#include <output/compile.h>
#include <output/dump.h>

#include "ctype_ops.h"
#include "exp_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"


/*
    If t is a function type with an inferred return type then the actual
    return type is set according to id.  The routine returns the original
    inferred return type.
*/

TYPE
inferred_return(TYPE t, IDENTIFIER id)
{
	if (IS_type_func(t)) {
		TYPE r = DEREF_type(type_func_ret(t));
		if (is_type_inferred(r) == INFERRED_EMPTY) {
			HASHID nm = DEREF_hashid(id_name(id));
			switch (TAG_hashid(nm)) {
			case hashid_constr_tag:
			case hashid_destr_tag: {
				/* Constructors and destructors */
				COPY_type(type_func_ret(t), type_void);
				break;
			}
			case hashid_conv_tag: {
				/* Conversion functions */
				TYPE s = DEREF_type(hashid_conv_type(nm));
				COPY_type(type_func_ret(t), s);
				break;
			}
			}
			return r;
		}
	}
	return NULL_type;
}


/*
    This routine checks whether the function type fn has first parameter
    of type '[volatile] ct &', 'const [volatile] ct &' or '[const]
    [volatile] ct' with any subsequent parameters being optional.  It
    returns 1, 2 and 3 respectively in these cases, or 0 if fn does not
    match this description.
*/

static int
check_copy_constr(TYPE fn, CLASS_TYPE ct)
{
	int c = 0;
	if (IS_type_templ(fn)) {
		/* Allow for template constructors */
		in_template_decl++;
		fn = DEREF_type(type_templ_defn(fn));
		c = check_copy_constr(fn, ct);
		in_template_decl--;
	} else {
		LIST(IDENTIFIER)pids = DEREF_list(type_func_pids(fn));
		if (!IS_NULL_list(pids)) {
			/* Have at least one parameter */
			IDENTIFIER pid = DEREF_id(HEAD_list(pids));
			TYPE t = DEREF_type(id_parameter_type(pid));

			/* Check for second parameter */
			pids = TAIL_list(pids);
			if (!IS_NULL_list(pids)) {
				/* Second parameter must have a default
				 * argument */
				EXP e;
				pid = DEREF_id(HEAD_list(pids));
				e = DEREF_exp(id_parameter_init(pid));
				if (IS_NULL_exp(e)) {
					return 0;
				}
			}

			/* Check parameter type */
			if (IS_type_ref(t)) {
				TYPE s = DEREF_type(type_ref_sub(t));
				if (IS_type_compound(s)) {
					CLASS_TYPE cs =
					    DEREF_ctype(type_compound_defn(s));
					if (eq_ctype(cs, ct)) {
						/* Reference to same class */
						CV_SPEC qual =
						    DEREF_cv(type_qual(s));
						c = ((qual & cv_const) ? 2 : 1);
					}
				} else if (is_templ_type(s)) {
					/* Reference to template parameter */
					CV_SPEC qual = DEREF_cv(type_qual(s));
					c = ((qual & cv_const)? 2 : 1);
				}
			} else if (IS_type_compound(t)) {
				CLASS_TYPE cs =
				    DEREF_ctype(type_compound_defn(t));
				if (eq_ctype(cs, ct)) {
					c = 3;
				}
			} else if (is_templ_type(t)) {
				/* Template parameter */
				c = 1;
			}
		}
	}
	return c;
}


/*
    This routine checks the function type t for the constructor id declared
    in namespace ns.  The check that the constructor is a non-static member
    function is carried out elsewhere.  Note that no return type can be given
    for id - it is implicitly void.  Remedial action is taken to transform
    illegal copy constructors such as 'X::X ( X )' into valid constructors
    such as 'X::X ( X & )'.  This is to avoid having to check for infinite
    loops later.
*/

TYPE
check_constr(TYPE t, IDENTIFIER id, NAMESPACE ns)
{
	if (IS_type_templ(t)) {
		/* Allow for template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		s = check_constr(s, id, ns);
		COPY_type(type_templ_defn(t), s);
	} else {
		/* Decompose function type */
		TYPE r = DEREF_type(type_func_ret(t));
		CV_SPEC cv = DEREF_cv(type_func_mqual(t));

		/* Find underlying class */
		CLASS_TYPE ct = namespace_class(ns);

		/* No return type can be given for a constructor */
		if (is_type_inferred(r)!= INFERRED_EMPTY) {
			HASHID nm = DEREF_hashid(id_name(id));
			report(crt_loc, ERR_class_ctor_ret(nm));
		}
		COPY_type(type_func_ret(t), type_void);

		/* Check for invalid copy constructors */
		if (check_copy_constr(t, ct) == 3) {
			HASHID nm = DEREF_hashid(id_name(id));
			report(crt_loc, ERR_class_copy_bad(nm));
		}

		/* A constructor cannot be cv-qualified */
		if (cv & cv_qual) {
			HASHID nm = DEREF_hashid(id_name(id));
			report(crt_loc, ERR_class_ctor_qual(nm, cv));
		}
	}
	return t;
}


/*
    This routine checks the function type t for the destructor id.  The
    check that the destructor is a non-static member function is carried
    out elsewhere.  Note that no return type can be given for id - it is
    implicitly void.
*/

TYPE
check_destr(TYPE t, IDENTIFIER id, NAMESPACE ns)
{
	if (IS_type_templ(t)) {
		/* Allow for template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		s = check_destr(s, id, ns);
		COPY_type(type_templ_defn(t), s);
	} else {
		/* Decompose function type */
		TYPE r = DEREF_type(type_func_ret(t));
		CV_SPEC cv = DEREF_cv(type_func_mqual(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		LIST(TYPE)p = DEREF_list(type_func_ptypes(t));

		/* Check namespace */
		HASHID nm = DEREF_hashid(id_name(id));
		TYPE dt = DEREF_type(hashid_destr_type(nm));
		if (IS_type_compound(dt)) {
			/* Check inheritance */
			CLASS_TYPE dct = DEREF_ctype(type_compound_defn(dt));
			NAMESPACE dns = DEREF_nspace(ctype_member(dct));
			if (!EQ_nspace(dns, ns)) {
				report(crt_loc, ERR_class_dtor_inherit(nm, ns));
			}
		}

		/* No return type can be given for a destructor */
		if (is_type_inferred(r)!= INFERRED_EMPTY) {
			report(crt_loc, ERR_class_dtor_ret(nm));
		}
		COPY_type(type_func_ret(t), type_void);

		/* No parameter types can be given for a destructor */
		if (!IS_NULL_list(p) || ell) {
			report(crt_loc, ERR_class_dtor_pars(nm));
		}

		/* A destructor cannot be cv-qualified */
		if (cv & cv_qual) {
			report(crt_loc, ERR_class_dtor_qual(nm, cv));
		}
	}
	return t;
}


/*
    This routine checks the function type t for the conversion function id.
    The check that the converter is a non-static member function is carried
    out elsewhere.  Note that no return type can be given for id - it is
    inferred from the type used in id.  This may not be a legal return type,
    so inject_pre_type is used to check it.
*/

TYPE
check_conv(TYPE t, IDENTIFIER id)
{
	if (IS_type_templ(t)) {
		/* Allow for template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		s = check_conv(s, id);
		COPY_type(type_templ_defn(t), s);
	} else {
		/* Find the conversion type */
		HASHID nm = DEREF_hashid(id_name(id));
		TYPE s = DEREF_type(hashid_conv_type(nm));

		/* Decompose function type */
		TYPE r = DEREF_type(type_func_ret(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		LIST(TYPE)p = DEREF_list(type_func_ptypes(t));

		/* No return type can be given for a conversion function */
		if (is_type_inferred(r)!= INFERRED_EMPTY) {
			/* If a return type is given it might as well be
			 * right */
			if (eq_type(r, s)) {
				report(crt_loc, ERR_class_conv_fct_ret(nm));
			} else {
				report(crt_loc,
				       ERR_class_conv_fct_ret_bad(nm, r));
			}
		}
		COPY_type(type_func_ret(t), NULL_type);
		t = inject_pre_type(t, s, 0);

		/* No parameter types can be given for a conversion function */
		if (!IS_NULL_list(p) || ell) {
			report(crt_loc, ERR_class_conv_fct_pars(nm));
		}

		/* Can't have conversion to cv-qualified void */
		if (IS_type_top_etc(s)) {
			report(crt_loc, ERR_class_conv_fct_void(nm));
		}
	}
	return t;
}


/*
    This routine looks up the overloaded operator function 'operator op'
    in the class ct.
*/

IDENTIFIER
find_operator(CLASS_TYPE ct, int op)
{
	HASHID nm = lookup_op(op);
	NAMESPACE cns = DEREF_nspace(ctype_member(ct));
	IDENTIFIER id = search_field(cns, nm, 0, 0);
	return id;
}


/*
    This routine finds either a default constructor, a copy constructor,
    a default destructor or a copy assignment operator of the class ct,
    depending on the value of n.  The null identifier is returned and
    an error is added to err if such a function does not exist (including
    for incomplete types).
*/

static IDENTIFIER
find_constr(CLASS_TYPE ct, int n, ERROR *err)
{
	CLASS_INFO ci;
	int match = 0;
	int nargs = 0;
	int kind = KIND_FUNC;
	IDENTIFIER id = NULL_id;
	IDENTIFIER qid = NULL_id;

	/* Check for complete types */
	complete_class(ct, 1);
	ci = DEREF_cinfo(ctype_info(ct));
	if (!(ci & cinfo_complete)) {
		return NULL_id;
	}

	/* Find the basic identifier */
	switch (n) {
	case DEFAULT_CONSTR:
	case DEFAULT_COPY:
	case DEFAULT_USR: {
		/* Find constructors */
		id = DEREF_id(ctype_constr(ct));
		if (n == DEFAULT_COPY) {
			nargs = 1;
		}
		kind = KIND_CONSTR;
		break;
	}
	case DEFAULT_DESTR:
	case DEFAULT_DELETE: {
		/* Find destructors */
		id = DEREF_id(ctype_destr(ct));
		nargs = 1;
		break;
	}
	case DEFAULT_ASSIGN: {
		/* Find 'operator =' */
		id = find_operator(ct, lex_assign);
		nargs = 2;
		break;
	}
	}

	/* Find appropriate function */
	if (!IS_NULL_id(id) && IS_id_mem_func(id)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_template) {
			/* Allow for template constructors */
			match = 2;
		} else {
			switch (n) {
			case DEFAULT_CONSTR:
			case DEFAULT_DESTR:
			case DEFAULT_DELETE:
			case DEFAULT_USR: {
				/* Should take no arguments */
				IDENTIFIER pid = id;
				while (!IS_NULL_id(pid)) {
					TYPE t =
					    DEREF_type(id_mem_func_type(pid));
					if (min_no_args(t) == 1) {
						qid = pid;
						match++;
					}
					pid = DEREF_id(id_mem_func_over(pid));
				}
				break;
			}
			case DEFAULT_COPY:
			case DEFAULT_ASSIGN: {
				/* Should be a copy constructor */
				IDENTIFIER pid = id;
				while (!IS_NULL_id(pid)) {
					TYPE t =
					    DEREF_type(id_mem_func_type(pid));
					if (check_copy_constr(t, ct)) {
						qid = pid;
						match++;
					}
					pid = DEREF_id(id_mem_func_over(pid));
				}
				break;
			}
			}
		}
	} else {
		/* This can only happen for dummy classes */
		return NULL_id;
	}

	/* Deal with ambiguous cases */
	if (match > 1) {
		CANDIDATE_LIST *p = &candidates;
		p->size = 0;
		add_candidates(p, id, 1, KIND_CONSTR);
		if (p->size) {
			CANDIDATE *q;
			unsigned rank;
			TYPE t = make_class_type(ct);
			LIST(EXP)args = NULL_list(EXP);
			while (nargs) {
				/* Create dummy arguments */
				EXP a;
				MAKE_exp_value(t, a);
				CONS_exp(a, args, args);
				nargs--;
			}
			if (kind == KIND_CONSTR) {
				swap_candidates(p,(unsigned)0);
			}
			q = resolve_overload(p, args, t, 0);
			if (kind == KIND_CONSTR) {
				swap_candidates(p,(unsigned)0);
			}
			rank = q->rank;
			if (rank >= RANK_VIABLE) {
				qid = q->func;
				if (rank == RANK_BEST) {
					/* Best match */
					if (match_no_viable > 1) {
						ERROR err2;
						if (kind == KIND_CONSTR) {
							err2 = ERR_over_match_ctor_ok(qid);
						} else {
							err2 = ERR_over_match_call_ok(qid);
						}
						add_error(err, err2);
					}
					match = 1;
				} else {
					/* Ambiguous call */
					ERROR err2;
					if (kind == KIND_CONSTR) {
						err2 = ERR_over_match_ctor_ambig(qid);
					} else {
						err2 = ERR_over_match_call_ambig(qid);
					}
					err2 = list_candidates(err2, p, RANK_VIABLE);
					add_error(err, err2);
				}
			} else {
				/* No viable call */
				qid = NULL_id;
				match = 0;
			}
			if (!IS_NULL_list(args)) {
				free_exp_list(args, 1);
			}
		} else {
			/* No viable call */
			qid = NULL_id;
			match = 0;
		}
	}

	/* Report error */
	if (match == 0) {
		switch (n) {
		case DEFAULT_CONSTR:
		case DEFAULT_USR: {
			add_error(err, ERR_class_ctor_default(ct));
			break;
		}
		case DEFAULT_COPY: {
			add_error(err, ERR_class_copy_constr(ct));
			break;
		}
		case DEFAULT_DESTR:
		case DEFAULT_DELETE: {
			add_error(err, ERR_class_dtor_default(ct));
			break;
		}
		case DEFAULT_ASSIGN: {
			add_error(err, ERR_class_copy_assign(ct));
			break;
		}
		}
	}
	return qid;
}


/*
    This routine finds the number of extra constructor arguments required
    by the member function id of the class ct.  For constructors and
    assignment operators for classes with a virtual base the extra
    argument is true to indicate that the virtual components should be
    initialised.  For non-trivial destructors bit 1 of the extra argument
    is used to indicate that any virtual components should be destroyed,
    while bit 0 is used to indicate that 'operator delete' should be
    called on the argument.  The macros EXTRA_* are used to represent
    these values.
*/

unsigned
extra_constr_args(IDENTIFIER id, CLASS_TYPE ct)
{
	DECL_SPEC ds = DEREF_dspec(id_storage(id));
	if (!(ds & dspec_trivial)) {
		HASHID nm = DEREF_hashid(id_name(id));
		unsigned tag = TAG_hashid(nm);
		if (tag == hashid_constr_tag) {
			/* Constructors */
			CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
			if (ci & cinfo_virtual_base) {
				return 1;
			}
		} else if (tag == hashid_destr_tag) {
			/* Destructors */
			return 1;
		}
	}
	return 0;
}


/*
    This flag is set to true in a constructor base class initialiser.
    This overrides the value of any extra arguments passed to the
    constructor.
*/

static int in_ctor_base_init = 0;


/*
    This routine adds any necessary extra constructor arguments to the
    member function call expression e.  ct gives the associate class
    type and v is the value to be passed to such arguments.
*/

EXP
add_constr_args(EXP e, CLASS_TYPE ct, int v)
{
	if (IS_exp_func_id(e)) {
		IDENTIFIER id = DEREF_id(exp_func_id_id(e));
		unsigned n = extra_constr_args(id, ct);
		if (n) {
			LIST(EXP)args = DEREF_list(exp_func_id_args(e));
			LIST(EXP)extra = NULL_list(EXP);
			if (in_ctor_base_init) {
				v = 0;
			}
			while (n) {
				EXP a;
				NAT c = small_nat[v];
				MAKE_exp_int_lit(type_sint, c,
						 exp_int_lit_tag, a);
				CONS_exp(a, extra, extra);
				n--;
			}
			args = APPEND_list(args, extra);
			COPY_list(exp_func_id_args(e), args);
		}
	}
	return e;
}


/*
    This routine constructs a default call of the constructor or destructor
    id of type n.  ct gives the corresponding class type and pb gives the
    second argument for copy constructors and assignment operators.
*/

static EXP
call_constr(IDENTIFIER id, EXP *pb, int n, int v, CLASS_TYPE ct)
{
	/* Create argument list */
	TYPE t;
	EXP e, a, b;
	LIST(EXP)args = NULL_list(EXP);
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	MAKE_type_compound(cv_lvalue, ct, t);
	COPY_id(type_name(t), cid);
	MAKE_exp_dummy(t, NULL_exp, LINK_NONE, NULL_off, 0, a);
	if (n == DEFAULT_ASSIGN || n == DEFAULT_DELETE) {
		/* Don't know object type */
		COPY_int(exp_dummy_virt(a), 1);
	}
	if (n == DEFAULT_COPY || n == DEFAULT_ASSIGN) {
		/* These have two arguments */
		TYPE s = t;
		int virt = 1;
		b = *pb;
		if (!IS_NULL_exp(b)) {
			s = DEREF_type(exp_type(b));
			while (IS_type_array(s)) {
				s = DEREF_type(type_array_sub(s));
			}
			s = lvalue_type(s);
			if (know_type(b)) {
				virt = 0;
			}
		}
		MAKE_exp_dummy(s, b, LINK_NONE, NULL_off, DUMMY_copy, b);
		COPY_int(exp_dummy_virt(b), virt);
		CONS_exp(b, args, args);
		*pb = b;
	} else {
		/* These have one argument */
		b = a;
	}
	CONS_exp(a, args, args);

	/* Call the function */
	use_func_id(id, 0, suppress_usage);
	e = apply_func_id(id, qual_none, NULL_graph, args);
	e = add_constr_args(e, ct, v);
	if (n == DEFAULT_DESTR || n == DEFAULT_DELETE) {
		MAKE_exp_destr(type_void, e, a, e);
	} else {
		t = make_class_type(ct);
		MAKE_exp_constr(t, e, a, b, n, e);
	}
	return e;
}


/*
    This routine creates a default initialiser for an object of type t
    in a constructor, destructor or assignment operator (as indicated
    by n).  Any resultant errors are added to err.
*/

EXP
init_default(TYPE t, EXP *pa, int n, int v, ERROR *err)
{
	CV_SPEC cv;
	EXP e = NULL_exp;
	unsigned tag = TAG_type(t);

	/* Deal with classes */
	if (tag == type_compound_tag) {
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		IDENTIFIER id = find_constr(ct, n, err);
		if (!IS_NULL_id(id)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_trivial)) {
				/* Non-trivial constructor */
				e = call_constr(id, pa, n, v, ct);
			} else if (ds & dspec_implicit) {
				if (!(ds & dspec_defn)) {
					/* Trivial constructor */
					implicit_defn(id, n);
				}
			}
		}
		return e;
	}

	/* Deal with arrays */
	if (tag == type_array_tag) {
		NAT m = DEREF_nat(type_array_size(t));
		TYPE s = DEREF_type(type_array_sub(t));
		e = init_default(s, pa, n, v, err);
		if (!IS_NULL_exp(e)) {
			/* Apply to each array element */
			MAKE_exp_nof(t, NULL_exp, m, e, NULL_exp, e);
		}
		return e;
	}

	/* Everything else is alright in these cases */
	if (n == DEFAULT_COPY || n == DEFAULT_DESTR || n == DEFAULT_DELETE) {
		return NULL_exp;
	}

	/* Deal with references */
	if (tag == type_ref_tag) {
		add_error(err, ERR_dcl_init_ref_none());
		if (n == DEFAULT_ASSIGN) {
			return NULL_exp;
		}
		MAKE_exp_null(t, e);
		return e;
	}

	/* Deal with const objects */
	cv = DEREF_cv(type_qual(t));
	if (cv & cv_const) {
		add_error(err, ERR_dcl_init_const());
	}
	return NULL_exp;
}


/*
    This routine reports the error err which occurred in the initialisation
    of id in constructor or destructor fn of type n.
*/

static void
constr_error(ERROR err, IDENTIFIER id, IDENTIFIER fn, int n)
{
	ERROR err1;
	ERROR err2 = ERR_dcl_init_decl(id, NULL_string);
	if (n == DEFAULT_USR) {
		err1 = ERR_class_base_init_err(fn);
	} else {
		err1 = ERR_class_base_init_impl(fn);
	}
	err = concat_error(err2, err);
	err = concat_error(err1, err);
	report(crt_loc, err);
	return;
}


/*
    This routine creates a default initialiser for the base class gr
    for the constructor or destructor fn of type n.  For copy constructors
    and assignment operators a dummy expression is used to indicate that
    the base should be initialised from the corresponding base of the
    second argument (see enc_ctor_exp).
*/

static EXP
init_empty_base(GRAPH gr, IDENTIFIER fn, int n, int m)
{
	EXP e = NULL_exp;
	ERROR err = NULL_err;
	CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
	TYPE t = make_class_type(ct);
	e = init_default(t, &e, m, EXTRA_NONE, &err);
	if (IS_NULL_exp(e)) {
		if (n == DEFAULT_USR && m != DEFAULT_DESTR) {
			/* Warn about uninitialised bases */
			if (!is_empty_class(t)) {
				IDENTIFIER id = DEREF_id(ctype_name(ct));
				err = concat_error(err, ERR_class_base_init_none(id));
			}
		}
		if (m == DEFAULT_COPY || m == DEFAULT_ASSIGN) {
			/* Dummy value for copy constructor */
			MAKE_exp_value(t, e);
		}
	}
	if (!IS_NULL_err(err)) {
		IDENTIFIER id = DEREF_id(ctype_name(ct));
		constr_error(err, id, fn, n);
	}
	return e;
}


/*
    This routine creates a default initialiser for a class member id
    for the constructor or destructor fn of type n.  Again a dummy value
    is used in copy constructors and assignment operators.
*/

static EXP
init_empty_mem(IDENTIFIER id, IDENTIFIER fn, int n, int m)
{
	EXP e = NULL_exp;
	ERROR err = NULL_err;
	TYPE t = DEREF_type(id_member_type(id));
	int v = (m == DEFAULT_DESTR ? EXTRA_DESTR : EXTRA_CONSTR);
	e = init_default(t, &e, m, v, &err);
	if (IS_NULL_exp(e)) {
		if (m == DEFAULT_COPY || m == DEFAULT_ASSIGN) {
			/* Dummy value for copy constructor */
			if (IS_type_ptr(t)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(fn));
				if (!(ds & dspec_trivial)) {
					/* Warn about shallow copies */
					err = concat_error(err, ERR_class_copy_ptr());
				}
			}
			MAKE_exp_value(t, e);
		}
	}
	if (!IS_NULL_err(err)) {
		constr_error(err, id, fn, n);
	}
	return e;
}


/*
    These lists are built up by the constructor initialisers.
*/

static LIST(GRAPH) init_bases = NULL_list(GRAPH);
static LIST(EXP) val_bases = NULL_list(EXP);
static LIST(IDENTIFIER) init_mems = NULL_list(IDENTIFIER);
static LIST(EXP) val_mems = NULL_list(EXP);
static unsigned long no_ctor_init = 0;
static int init_base_last = 1;


/*
    This routine clears the lists of constructor initialisers above.
*/

static void
destroy_ctor_lists(void)
{
	IGNORE check_value(OPT_VAL_ctor_initializers, no_ctor_init);
	DESTROY_list(init_bases, SIZE_graph);
	DESTROY_list(val_bases, SIZE_exp);
	DESTROY_list(init_mems, SIZE_id);
	DESTROY_list(val_mems, SIZE_exp);
	init_bases = NULL_list(GRAPH);
	val_bases = NULL_list(EXP);
	init_mems = NULL_list(IDENTIFIER);
	val_mems = NULL_list(EXP);
	init_base_last = 1;
	no_ctor_init = 0;
	return;
}


/*
    This routine finds the base class initialiser for gr in the lists
    given above.  If gr is a member of init_bases then the corresponding
    element of val_bases is returned, otherwise the null expression is
    returned.
*/

static EXP
find_base_init(GRAPH gr)
{
	LIST(GRAPH)p = init_bases;
	LIST(EXP)q = val_bases;
	while (!IS_NULL_list(p)) {
		GRAPH gs = DEREF_graph(HEAD_list(p));
		if (eq_graph(gs, gr)) {
			/* Found graph - return corresponding expression */
			EXP e = DEREF_exp(HEAD_list(q));
			return e;
		}
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return NULL_exp;
}


/*
    This routine finds the class member initialiser for id in the lists
    given above.  If id is a member of init_mems then the corresponding
    element of val_mems is returned, otherwise the null expression is
    returned.
*/

static EXP
find_mem_init(IDENTIFIER id)
{
	LIST(IDENTIFIER)p = init_mems;
	LIST(EXP)q = val_mems;
	while (!IS_NULL_list(p)) {
		IDENTIFIER mid = DEREF_id(HEAD_list(p));
		if (EQ_id(mid, id)) {
			/* Found identifier - return corresponding expression */
			EXP e = DEREF_exp(HEAD_list(q));
			return e;
		}
		q = TAIL_list(q);
		p = TAIL_list(p);
	}
	return NULL_exp;
}


/*
    This routine marks the initialiser expression e for an object of type t
    if t has a non-trivial destructor by enclosing it in parentheses.
*/

static EXP
destr_init(TYPE t, EXP e)
{
	TYPE s = t;
	while (IS_type_array(s)) {
		s = DEREF_type(type_array_sub(s));
	}
	if (IS_type_compound(s)) {
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
		IDENTIFIER id = DEREF_id(ctype_destr(cs));
		if (IS_id_mem_func(id)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_trivial)) {
				if (ds & dspec_implicit) {
					if (!(ds & dspec_defn)) {
						/* Trivial constructor */
						implicit_defn(id, DEFAULT_DESTR);
					}
				}
				MAKE_exp_paren(t, e, e);
			}
		}
	}
	return e;
}


/*
    This routine creates a constructor or destructor initialiser list.
    cns gives the corresponding class namespace and fn is the function
    name.  n and m indicate the constructor or destructor type.  This can
    be an implicitly declared constructor, destructor or assignment
    function, or an explicitly declared constructor.  In the latter
    case the ctor-initialiser lists above are used to indicate the
    initialiser values.
*/

static EXP
make_constr(NAMESPACE cns, IDENTIFIER fn, int n, int m)
{
	EXP r;
	int usr = 0;
	int str = 1;
	unsigned nv = 0;
	unsigned nb = 0;
	unsigned long no = 0;
	int templ = in_template_decl;
	LIST(EXP)p = NULL_list(EXP);
	LIST(OFFSET)q = NULL_list(OFFSET);

	/* Deconstruct class type */
	CLASS_TYPE ct = namespace_class(cns);
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH)br = DEREF_list(graph_tails(gr));
	LIST(GRAPH)bv = DEREF_list(ctype_vbase(ct));
	MEMBER mem = DEREF_member(nspace_ctype_first(cns));

	/* Mark 'this' parameter as used */
	crt_access_list.inherit++;
	IGNORE this_param(fn, 1);

	/* Check for user-defined constructors */
	if (n == DEFAULT_USR && m == DEFAULT_CONSTR) {
		usr = 1;
	}

	/* Initialise virtual bases */
	if (m != DEFAULT_ASSIGN) {
		while (!IS_NULL_list(bv)) {
			EXP e = NULL_exp;
			GRAPH gs = DEREF_graph(HEAD_list(bv));
			DECL_SPEC acc = DEREF_dspec(graph_access(gs));
			if (usr) {
				e = find_base_init(gs);
			}
			if (IS_NULL_exp(e) && !(acc & dspec_template)) {
				e = init_empty_base(gs, fn, n, m);
				if (templ) {
					/* Only testing for template classes */
					free_exp(e, 1);
					e = NULL_exp;
				}
			}
			if (m == DEFAULT_CONSTR && !templ) {
				CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
				TYPE s = make_class_type(cs);
				e = destr_init(s, e);
			}
			if (!IS_NULL_exp(e)) {
				OFFSET off = DEREF_off(graph_off(gs));
				CONS_off(off, q, q);
				CONS_exp(e, p, p);
				nv++;
			}
			bv = TAIL_list(bv);
		}
	}

	/* Initialise direct bases */
	while (!IS_NULL_list(br)) {
		EXP e = NULL_exp;
		GRAPH gs = DEREF_graph(HEAD_list(br));
		DECL_SPEC acc = DEREF_dspec(graph_access(gs));
		if (!(acc & dspec_virtual) || m == DEFAULT_ASSIGN) {
			if (usr) {
				e = find_base_init(gs);
			}
			if (IS_NULL_exp(e) && !(acc & dspec_template)) {
				e = init_empty_base(gs, fn, n, m);
				if (templ) {
					/* Only testing for template classes */
					free_exp(e, 1);
					e = NULL_exp;
				}
			}
			if (m == DEFAULT_CONSTR && !templ) {
				CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
				TYPE s = make_class_type(cs);
				e = destr_init(s, e);
			}
			if (!IS_NULL_exp(e)) {
				OFFSET off = DEREF_off(graph_off(gs));
				CONS_off(off, q, q);
				CONS_exp(e, p, p);
				nb++;
			}
		}
		br = TAIL_list(br);
	}

	/* Initialise data members */
	member_no = no;
	mem = next_data_member(mem, 2);
	if (usr && (ci & cinfo_union)) {
		/* Check union initialisers */
		unsigned ni = LENGTH_list(init_mems);
		if (ni) {
			if (ni > 1) {
				/* More than one initialiser for union */
				report(crt_loc, ERR_class_base_init_union(ct));
			}
			str = 0;
		}
	}
	while (!IS_NULL_member(mem)) {
		EXP e = NULL_exp;
		IDENTIFIER id = DEREF_id(member_id(mem));
		if (usr) {
			e = find_mem_init(id);
			if (!IS_NULL_exp(e)) {
				if (no == member_no) {
					/* More than one initialiser for
					 * anonymous union */
					report(crt_loc,
					       ERR_class_base_init_anon(id));
				}
				no = member_no;
			}
		}
		if (IS_NULL_exp(e) && str) {
			e = init_empty_mem(id, fn, n, m);
			if (templ) {
				/* Only testing for template classes */
				free_exp(e, 1);
				e = NULL_exp;
			}
		}
		if (m == DEFAULT_CONSTR && !templ) {
			TYPE s = DEREF_type(id_member_type(id));
			e = destr_init(s, e);
		}
		if (!IS_NULL_exp(e)) {
			OFFSET off = DEREF_off(id_member_off(id));
			e = check_init(e);
			CONS_off(off, q, q);
			CONS_exp(e, p, p);
		}
		if (ci & cinfo_union) {
			if (!usr) {
				break;
			}
			str = 0;
		}
		mem = DEREF_member(member_next(mem));
		mem = next_data_member(mem, 2);
	}

	/* Construct the result */
	crt_access_list.inherit--;
	if (IS_NULL_list(p)) {
		DECL_SPEC ds = DEREF_dspec(id_storage(fn));
		if (ds & dspec_trivial) {
			return NULL_exp;
		}
		if (m != DEFAULT_DESTR && !templ) {
			if (ci & (cinfo_virtual_base | cinfo_polymorphic)) {
				/* These require an initialiser */
				/* EMPTY */
			} else {
				return NULL_exp;
			}
		}
	}
	if (m != DEFAULT_DESTR) {
		/* Initialisers are built in reverse order */
		p = REVERSE_list(p);
		q = REVERSE_list(q);
	}
	MAKE_exp_initialiser(type_void, p, q, m, nv, nb, r);
	return r;
}


/*
    The destruction of the base classes and members of a class takes
    place at the end of the destructor, and it is this which is handled
    by make_constr.  However for polymorphic classes some action is
    also required at the start of the destructor, namely the resetting
    of the virtual function tables.  This routine creates a dummy
    initialiser expression which performs this action.
*/

static EXP
make_destr_prelude(NAMESPACE cns)
{
	EXP r = NULL_exp;
	CLASS_TYPE ct = namespace_class(cns);
	CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));
	if (ci & cinfo_polymorphic) {
		/* Create dummy initialiser */
		MAKE_exp_initialiser(type_void, NULL_list(EXP),
				     NULL_list(OFFSET), DEFAULT_PRELUDE, 0, 0,
				     r);
	}
	return r;
}


/*
    This routine copies the constructor initialiser list of type m.
*/

EXP
copy_ctor(EXP e, int m)
{
	IDENTIFIER fn = crt_func_id;
	NAMESPACE cns = DEREF_nspace(id_parent(fn));
	LIST(EXP)p = DEREF_list(exp_initialiser_args(e));
	LIST(OFFSET)q = DEREF_list(exp_initialiser_offs(e));
	if (!IS_NULL_list(p)) {
		/* Copy initialisers */
		while (!IS_NULL_list(p) && !IS_NULL_list(q)) {
			int redo = 0;
			IDENTIFIER id = NULL_id;
			EXP a = DEREF_exp(HEAD_list(p));
			OFFSET off = DEREF_off(HEAD_list(q));
			EXP b = implicit_cast_exp(a);
			if (!IS_NULL_exp(b) && !EQ_exp(b, a)) {
				redo = 1;
				a = b;
			}
			a = copy_exp(a, NULL_type, NULL_type);
			if (redo && !IS_exp_initialiser(a)) {
				/* Turn expression into ctor-initialiser list */
				LIST(EXP)r = NULL_list(EXP);
				LIST(OFFSET)s = NULL_list(OFFSET);
				CONS_exp(a, r, r);
				MAKE_exp_initialiser(type_void, r, s, 0, 0, 0,
						     a);
			}
			off = copy_offset(off, lex_plus);
			switch (TAG_off(off)) {
			case off_member_tag: {
				/* Member initialiser */
				id = DEREF_id(off_member_id(off));
				break;
			}
			case off_base_tag: {
				/* Direct base class initialiser */
				GRAPH gr = DEREF_graph(off_base_graph(off));
				CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
				id = DEREF_id(ctype_name(ct));
				break;
			}
			case off_deriv_tag: {
				/* Indirect base class initialiser */
				GRAPH gr = DEREF_graph(off_deriv_graph(off));
				CLASS_TYPE ct = DEREF_ctype(graph_head(gr));
				id = DEREF_id(ctype_name(ct));
				break;
			}
			}
			if (!IS_NULL_id(id)) {
				/* Add initialiser to list */
				ctor_initialise(cns, id, a);
			}
			q = TAIL_list(q);
			p = TAIL_list(p);
		}
	}
	e = make_constr(cns, fn, DEFAULT_USR, m);
	destroy_ctor_lists();
	return e;
}


/*
    This routine is called at the start of a ctor-initialiser list to
    check that the current function is a constructor.  If so it returns
    the corresponding class namespace.  Otherwise the null namespace
    is returned.
*/

NAMESPACE
ctor_begin(void)
{
	IDENTIFIER id = crt_func_id;
	HASHID nm = DEREF_hashid(id_name(id));
	if (IS_hashid_constr(nm)) {
		TYPE t = DEREF_type(hashid_constr_type(nm));
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			NAMESPACE cns = DEREF_nspace(ctype_member(ct));
			return cns;
		}
	}
	report(crt_loc, ERR_class_base_init_bad(id));
	return NULL_nspace;
}


/*
    This routine is called at the end of a ctor-initialiser list.  cns
    gives the class namespace, e is the compound statement to which
    the initialisers are to be added and elem is true if the list was
    not empty.  The routine returns the resultant compound statement.
*/

EXP
ctor_end(NAMESPACE cns, EXP e, int elem)
{
	if (!IS_NULL_nspace(cns)) {
		/* Construct the constructor */
		IDENTIFIER id = crt_func_id;
		if (!elem) {
			report(crt_loc, ERR_class_base_init_empty(id));
		}
		if (IS_id_mem_func(id)) {
			EXP c = make_constr(cns, id, DEFAULT_USR,
					    DEFAULT_CONSTR);
			if (!IS_NULL_exp(c)) {
				e = add_compound_stmt(e, c);
			}
		}
		destroy_ctor_lists();
	}
	return e;
}


/*
    This routine is called for a function definition which contains no
    ctor-initialiser.  e gives the compound statement giving the function
    body.  The routine returns the value of e after any initialisers
    required for constructors have been added.  Any destructors which need
    to be called at the end of the function are returned via p.
*/

EXP
ctor_none(EXP e, EXP *p)
{
	IDENTIFIER id = crt_func_id;
	if (IS_id_mem_func(id)) {
		HASHID nm = DEREF_hashid(id_name(id));
		switch (TAG_hashid(nm)) {
		case hashid_constr_tag: {
			/* Constructor declarations */
			NAMESPACE cns = DEREF_nspace(id_parent(id));
			EXP c = make_constr(cns, id, DEFAULT_USR,
					    DEFAULT_CONSTR);
			if (!IS_NULL_exp(c)) {
				/* Add initialiser to function body */
				e = add_compound_stmt(e, c);
			}
			break;
		}
		case hashid_destr_tag: {
			/* Destructor declarations */
			NAMESPACE cns = DEREF_nspace(id_parent(id));
			EXP c = make_destr_prelude(cns);
			EXP d = make_constr(cns, id, DEFAULT_USR,
					    DEFAULT_DESTR);
			if (!IS_NULL_exp(c)) {
				/* Add destructor prelude to function body */
				e = add_compound_stmt(e, c);
			}
			if (!IS_NULL_exp(d)) {
				/* Set up destructor postlude */
				IDENTIFIER lab = postlude_label();
				EXP a = begin_label_stmt(lab, lex_return);
				*p = end_label_stmt(a, d);
			}
			break;
		}
		}
	}
	return e;
}


/*
    This routine adds the postlude expression d to the end of the
    function body e.  This is used in user declared destructors where the
    default destructors need to be called after the main function body.
    For convenience the code for falling out of a normal function body
    is also handled by this routine.
*/

EXP
ctor_postlude(EXP e, EXP d)
{
	if (!IS_NULL_exp(d)) {
		/* Add postlude expression */
		EXP r;
		unreached_code = 0;
		e = add_compound_stmt(e, d);
		unreached_code = 0;
		MAKE_exp_return_stmt(type_bottom, NULL_exp, r);
		e = add_compound_stmt(e, r);
		unreached_code = 1;
		unreached_last = 0;
	} else {
		/* Fall out of function */
		if (!unreached_code) {
			EXP r = fall_return_stmt();
			e = add_compound_stmt(e, r);
		}
	}
	return e;
}


/*
    This routine creates an expression which will be called in the exception
    specifier for the function id.  This is used in constructors to destroy
    the partially complete object.
*/

EXP
except_postlude(IDENTIFIER id)
{
	EXP e = NULL_exp;
	HASHID nm = DEREF_hashid(id_name(id));
	if (IS_hashid_constr(nm)) {
		/* Have a constructor */
		TYPE t = DEREF_type(hashid_constr_type(nm));
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			NAMESPACE cns = DEREF_nspace(ctype_member(ct));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & (dspec_friend | dspec_trivial))) {
				/* Constructor may throw an exception */
				int ac = do_access_checks;
				EXP a = DEREF_exp(id_function_etc_defn(id));
				if (!IS_NULL_exp(a) && IS_exp_initialiser(a)) {
					LIST(EXP)p;
					p = DEREF_list(exp_initialiser_args(a));
					if (LENGTH_list(p) == 1) {
						/* Single initialiser in constructor */
						a = DEREF_exp(HEAD_list(p));
						if (!IS_NULL_exp(a)) {
							TYPE s = DEREF_type(exp_type(a));
							if (!IS_type_array(s)) {
								return e;
							}
						}
					}
				}
				do_access_checks = 0;
				COPY_dspec(id_storage(id), (ds | dspec_trivial));
				start_try_check(univ_type_set);
				e = make_constr(cns, id, DEFAULT_DESTR, DEFAULT_DESTR);
				if (!IS_NULL_exp(e)) {
					/* Add destructor prelude */
					EXP d = make_destr_prelude(cns);
					e = join_exp(d, e);
				}
				e = end_try_check(id, e);
				COPY_dspec(id_storage(id), ds);
				do_access_checks = ac;
			}
		}
	}
	return e;
}


/*
    This routine compares the order of initialisation of the base graphs
    gr and gs.  It returns 1 if gr is initialised before gs, -1 if gr is
    initialised before gr and 0 if they are equal.  Note that virtual
    bases are initialised before direct bases.
*/

static int
compare_base(GRAPH gr, GRAPH gs)
{
	DECL_SPEC ar, as;
	LIST(GRAPH)br;
	if (eq_graph(gr, gs)) {
		return 0;
	}
	ar = DEREF_dspec(graph_access(gr));
	as = DEREF_dspec(graph_access(gs));
	if (ar & dspec_virtual) {
		if (as & dspec_virtual) {
			GRAPH gt = DEREF_graph(graph_top(gr));
			CLASS_TYPE ct = DEREF_ctype(graph_head(gt));
			br = DEREF_list(ctype_vbase(ct));
		} else {
			return 1;
		}
	} else {
		if (as & dspec_virtual) {
			return -1;
		} else {
			GRAPH gt = DEREF_graph(graph_top(gr));
			br = DEREF_list(graph_tails(gt));
		}
	}
	while (!IS_NULL_list(br)) {
		GRAPH gt = DEREF_graph(HEAD_list(br));
		if (eq_graph(gt, gr)) {
			return 1;
		}
		if (eq_graph(gt, gs)) {
			return -1;
		}
		br = TAIL_list(br);
	}
	return 0;
}


/*
    This routine compares the order of initialisation of the members pid
    and mid of the class namespace ns.  It returns 1 if mid is initialised
    before pid, -1 if pid is initialised before mid and 0 if they are equal.
*/

static int
compare_mem(NAMESPACE ns, IDENTIFIER mid, IDENTIFIER pid)
{
	MEMBER mem;
	if (EQ_id(mid, pid)) {
		return 0;
	}
	mem = DEREF_member(nspace_ctype_first(ns));
	while (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		if (EQ_id(id, mid)) {
			return 1;
		}
		if (EQ_id(id, pid)) {
			return -1;
		}
		mem = DEREF_member(member_next(mem));
	}
	return 0;
}


/*
    This routine looks up the name id as a ctor-initialiser for the class
    cns.  If it denotes a base class then the corresponding graph is
    returned via pgr.  If id is the null identifier then this is an
    anachronistic way of initialising the unique direct base class of
    cns, if this exists.  The null identifier is returned for illegal
    initialisers.
*/

static IDENTIFIER
ctor_field(NAMESPACE cns, IDENTIFIER id, GRAPH *pgr)
{
	if (!IS_NULL_nspace(cns)) {
		if (IS_NULL_id(id)) {
			/* Search for unique base class */
			ERROR err = ERR_class_base_init_old(crt_func_id);
			CLASS_TYPE ct = namespace_class(cns);
			GRAPH gr = uniq_base_class(ct, &err);
			if (!IS_NULL_graph(gr)) {
				ct = DEREF_ctype(graph_head(gr));
				id = DEREF_id(ctype_name(ct));
				*pgr = gr;
			} else {
				id = NULL_id;
			}
			report(crt_loc, err);

		} else {
			/* Look up name as class member */
			GRAPH gr;
			int check_base = 1;
			IDENTIFIER fid = id;
			NAMESPACE fns = DEREF_nspace(id_parent(fid));
			if (EQ_nspace(fns, crt_namespace)) {
				/* Rescan constructor parameters in enclosing
				 * scope */
				HASHID nm = DEREF_hashid(id_name(fid));
				int c = cache_lookup;
				cache_lookup = 0;
				remove_namespace();
				fid = find_id(nm);
				add_namespace(fns);
				cache_lookup = c;
				id = fid;
			}

			/* Check for class members */
			gr = is_subfield(cns, fid);
			if (!IS_NULL_graph(gr)) {
				check_base = 0;
				fid = search_subfield(cns, gr, fid);
				switch (TAG_id(fid)) {
				case id_member_tag: {
					/* Non-static data members */
					DECL_SPEC ds =
					    DEREF_dspec(id_storage(fid));
					if (ds & dspec_inherit) {
						/* Can't denote an inherited
						 * member */
						ERROR err;
						err = ERR_class_base_init_inherit(fid);
						report(crt_loc, err);
						id = NULL_id;
					} else {
						id = fid;
					}
					break;
				}
				case id_class_name_tag:
				case id_class_alias_tag: {
					/* Check for base classes */
					check_base = 1;
					break;
				}
				case id_undef_tag: {
					/* Undeclared members */
					HASHID nm = DEREF_hashid(id_name(fid));
					ERROR err =
					    ERR_lookup_qual_undef(nm, fns);
					report(crt_loc, err);
					id = NULL_id;
					break;
				}
				case id_ambig_tag: {
					/* Ambiguous members */
					id = report_ambiguous(fid, 0, 1, 1);
					break;
				}
				default : {
					/* Other members */
					ERROR err =
					    ERR_class_base_init_static(fid);
					report(crt_loc, err);
					id = NULL_id;
					break;
				}
				}
			}

			/* Check for base classes */
			if (check_base) {
				CLASS_TYPE cs = find_class(fid);
				if (IS_NULL_ctype(cs) && IS_id_undef(fid)) {
					TYPE s = check_typename(fns, fid,
								btype_class);
					if (!IS_NULL_type(s) &&
					    IS_type_compound(s)) {
						cs = DEREF_ctype(type_compound_defn(s));
					}
				}
				if (!IS_NULL_ctype(cs)) {
					/* Class name found */
					ERROR err = NULL_err;
					CLASS_TYPE ct = namespace_class(cns);
					gr = direct_base_class(ct, cs, &err);
					if (!IS_NULL_err(err)) {
						/* Report invalid bases */
						report(crt_loc, err);
					}
					if (!IS_NULL_graph(gr)) {
						id = DEREF_id(ctype_name(cs));
						*pgr = gr;
					} else {
						id = NULL_id;
					}
				} else {
					/* Invalid ctor-initialiser */
					ERROR err = ERR_lookup_qual_bad(id, cns);
					report(crt_loc, err);
					id = NULL_id;
				}
			}
		}
	} else {
		/* Invalid class namespace */
		id = NULL_id;
	}
	return id;
}


/*
    This routine processes a ctor-initialiser which sets the id component
    of the current constructor function to the initialiser expression init.
    cns gives the value returned by ctor_check.  id may be the null
    identifier indicating the anachronistic single inheritance base class
    initialisation.
*/

void
ctor_initialise(NAMESPACE cns, IDENTIFIER id, EXP init)
{
	TYPE t;
	int n = 0;
	int ok = 1;
	GRAPH gr = NULL_graph;

	/* Check member identifier */
	IDENTIFIER mid = ctor_field(cns, id, &gr);
	if (!IS_NULL_id(mid)) {
		EXP e;
		if (IS_id_member(mid)) {
			/* Member initialiser */
			e = find_mem_init(mid);
			t = DEREF_type(id_member_type(mid));
			n = 1;
		} else {
			/* Base class initialiser */
			e = find_base_init(gr);
			t = DEREF_type(id_class_name_etc_defn(mid));
			if (in_template_decl) {
				/* Allow for template parameters */
				DECL_SPEC acc = DEREF_dspec(graph_access(gr));
				if (acc & dspec_template) {
					CLASS_TYPE ct =
					    DEREF_ctype(graph_head(gr));
					t = DEREF_type(ctype_form(ct));
				}
			}
			n = 2;
		}
		if (!IS_NULL_exp(e)) {
			/* Initialiser already given */
			report(crt_loc, ERR_class_base_init_dup(mid));
		}
	} else {
		/* Invalid initialiser */
		HASHID nm = KEYWORD(lex_zzzz);
		mid = DEREF_id(hashid_id(nm));
		t = type_error;
	}

	/* Check for order of initialisers */
	if (init_base_last) {
		/* Previous initialiser was a base */
		if (n == 2) {
			if (!IS_NULL_list(init_bases)) {
				GRAPH gp = DEREF_graph(HEAD_list(init_bases));
				int cmp = compare_base(gr, gp);
				if (cmp > 0) {
					ok = 0;
				}
			}
		}
	} else {
		/* Previous initialiser was a member */
		if (n == 1) {
			if (!IS_NULL_list(init_mems)) {
				IDENTIFIER pid = DEREF_id(HEAD_list(init_mems));
				int cmp = compare_mem(cns, mid, pid);
				if (cmp > 0) {
					ok = 0;
				}
			}
		} else if (n == 2) {
			ok = 0;
		}
	}
	if (!ok) {
		/* Initialisers out of sequence */
		report(crt_loc, ERR_class_base_init_order(mid));
	}

	/* Perform initialisation */
	if (IS_exp_initialiser(init)) {
		crt_access_list.inherit++;
		decl_loc = crt_loc;
		if (n == 2) {
			in_ctor_base_init = 1;
		}
		init = init_general(t, init, mid, 0);
		in_ctor_base_init = 0;
		crt_access_list.inherit--;
	}
	if (n == 1) {
		CONS_id(mid, init_mems, init_mems);
		CONS_exp(init, val_mems, val_mems);
		init_base_last = 0;
	} else if (n == 2) {
		CONS_graph(gr, init_bases, init_bases);
		CONS_exp(init, val_bases, val_bases);
		init_base_last = 1;
	}
	no_ctor_init++;
	return;
}


/*
    This routine creates a pseudo-destructor with class name given by
    id1 and b1 and destructor name given by id2 and b2.
*/

IDENTIFIER
make_pseudo_destr(IDENTIFIER id1, BASE_TYPE b1, IDENTIFIER id2, BASE_TYPE b2)
{
	HASHID nm;
	int create = 0;
	int rescan = 0;
	TYPE t1 = NULL_type;
	TYPE t2 = NULL_type;
	NAMESPACE ns = NULL_nspace;

	/* Check class name */
	if (b1 == btype_none) {
		if (!IS_NULL_id(id1)) {
			ns = find_namespace(id1);
			if (IS_id_class_name_etc(id1)) {
				t1 = DEREF_type(id_class_name_etc_defn(id1));
				t1 = copy_typedef(id1, t1, cv_none);
				COPY_id(type_name(t1), id1);
				if (IS_NULL_nspace(ns)) {
					ns = DEREF_nspace(id_parent(id1));
				} else {
					/* Have class name */
					rescan = 1;
				}
				use_id(id1, 0);
			} else {
				if (!IS_NULL_nspace(ns) && !IS_NULL_id(id2)) {
					/* Namespace qualifier allowed */
					create = 1;
				} else {
					report(crt_loc, ERR_dcl_type_simple_undef(id1));
				}
			}
		}
	} else {
		t1 = make_base_type(b1);
	}

	/* Check destructor name */
	if (b2 == btype_none) {
		if (!EQ_id(id2, id1)) {
			nm = DEREF_hashid(id_name(id2));
			if (!IS_NULL_nspace(ns)) {
				/* Rescan id2 in the context of id1 */
				IDENTIFIER id3 =
				    find_qual_id(ns, nm, create, 1);
				if (!IS_NULL_id(id3)) {
					id2 = id3;
				}
			}
			if (IS_id_class_name_etc(id2)) {
				t2 = DEREF_type(id_class_name_etc_defn(id2));
				t2 = copy_typedef(id2, t2, cv_none);
				COPY_id(type_name(t2), id2);
				use_id(id2, 0);
			} else {
				report(crt_loc, ERR_dcl_type_simple_undef(id2));
			}
		}
	} else {
		if (b2 != b1) {
			t2 = make_base_type(b2);
		}
	}

	/* Form pseudo-destructor name */
	if (IS_NULL_type(t2)) {
		t2 = t1;
		if (IS_NULL_type(t2)) {
			t2 = type_error;
		}
	} else {
		if (rescan) {
			/* Error will be caught in search_field */
			/* EMPTY */
		} else {
			if (!IS_NULL_type(t1) && !eq_type(t1, t2)) {
				/* If both specified, types should match */
				report(crt_loc, ERR_expr_pseudo_type(t1, t2));
			}
		}
	}
	nm = lookup_destr(t2, id2);
	id2 = DEREF_id(hashid_id(nm));
	return id2;
}


/*
    This value gives the declaration specifiers used for implicitly declared
    constructors and destructors.
*/

#define dspec_constr	(dspec_implicit | dspec_ignore | dspec_inline)


/*
    This routine adds the list of exceptions thrown by the implicit
    constructor or destructor (given by n) of the class ct to the list p.
*/

static LIST(TYPE)
add_constr_except(LIST(TYPE)p, CLASS_TYPE ct, int n)
{
	IDENTIFIER id = find_constr(ct, n, KILL_err);
	if (!IS_NULL_id(id) && IS_id_mem_func(id)) {
		TYPE fn = DEREF_type(id_mem_func_type(id));
		if (IS_type_func(fn)) {
			LIST(TYPE)q = DEREF_list(type_func_except(fn));
			p = union_type_set(p, q);
		}
	}
	return p;
}


/*
    This routine finds the list of exceptions thrown by the implicit
    constructor or destructor (given by n) of the class ct.
*/

static LIST(TYPE)
constr_except(CLASS_TYPE ct, int n)
{
	LIST(TYPE)res = NULL_list(TYPE);
	GRAPH gr = DEREF_graph(ctype_base(ct));
	LIST(GRAPH)br = DEREF_list(graph_tails(gr));
	NAMESPACE cns = DEREF_nspace(ctype_member(ct));
	MEMBER mem = DEREF_member(nspace_ctype_first(cns));

	/* Scan through virtual bases */
	if (n != DEFAULT_ASSIGN) {
		LIST(GRAPH)bv = DEREF_list(ctype_vbase(ct));
		while (!IS_NULL_list(bv)) {
			GRAPH gs = DEREF_graph(HEAD_list(bv));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			res = add_constr_except(res, cs, n);
			if (EQ_list(res, univ_type_set)) {
				return res;
			}
			bv = TAIL_list(bv);
		}
	}

	/* Scan through direct bases */
	while (!IS_NULL_list(br)) {
		GRAPH gs = DEREF_graph(HEAD_list(br));
		DECL_SPEC acc = DEREF_dspec(graph_access(gs));
		if (!(acc & dspec_virtual) || n == DEFAULT_ASSIGN) {
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			res = add_constr_except(res, cs, n);
			if (EQ_list(res, univ_type_set)) {
				return res;
			}
		}
		br = TAIL_list(br);
	}

	/* Scan through data members */
	mem = next_data_member(mem, 2);
	while (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		TYPE s = DEREF_type(id_member_type(id));
		while (IS_type_array(s)) {
			s = DEREF_type(type_array_sub(s));
		}
		if (IS_type_compound(s)) {
			CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
			res = add_constr_except(res, cs, n);
			if (EQ_list(res, univ_type_set)) {
				return res;
			}
		}
		mem = DEREF_member(member_next(mem));
		mem = next_data_member(mem, 2);
	}
	return res;
}


/*
    This routine is called at the end of a class definition to implicitly
    declare any necessary default constructors, copy constructors, assignment
    operators or destructors.  Note that these are only actually defined
    if they are used, and errors are only detected at this definition stage.
    The routine returns information on the class being defined.
*/

CLASS_INFO
implicit_decl(CLASS_TYPE ct, CLASS_INFO ci, DECL_SPEC cds)
{
	TYPE t;
	HASHID nm;
	IDENTIFIER id;
	TYPE pars[2];
	CLASS_INFO cj;
	LIST(TYPE)ex;
	IDENTIFIER cid = DEREF_id(ctype_name(ct));
	NAMESPACE ns = DEREF_nspace(ctype_member(ct));
	LIST(IDENTIFIER)pals = DEREF_list(ctype_pals(ct));

	/* Options being checked */
	int need_copy_constr = 1;
	int need_default_constr = 1;
	int need_assignment_op = 1;
	int need_destructor = 1;
	int noncopy_constr = 0;
	int access_constr = 0;
	int access_destr = 0;
	int three_rule = 0;

	/* Find accumulated information */
	cj = (ci & cinfo_implicit);
	if (ci & (cinfo_virtual_base | cinfo_polymorphic)) {
		cj &= ~cinfo_trivial_make;
	}
	ci &= ~cinfo_implicit;

	/* Check constructors */
	id = DEREF_id(ctype_constr(ct));
	if (IS_id_mem_func(id)) {
		IDENTIFIER fid = id;
		while (!IS_NULL_id(fid)) {
			TYPE fn = DEREF_type(id_mem_func_type(fid));
			int c = check_copy_constr(fn, ct);
			if (c) {
				/* Copy constructor */
				if (c == 2) {
					ci |= cinfo_const_copy;
				}
				need_copy_constr = 0;
				three_rule++;
			} else {
				/* Check access for other constructors */
				DECL_SPEC acc = DEREF_dspec(id_storage(fid));
				if ((acc & dspec_access)!= dspec_private) {
					access_constr = 1;
				}
				noncopy_constr = 1;
			}
			fid = DEREF_id(id_mem_func_over(fid));
		}
		ci |= cinfo_usr_constr;
		need_default_constr = 0;
	} else {
		/* Delete non-function meanings */
		nm = DEREF_hashid(id_name(id));
		clear_member(ns, nm);
	}

	/* Implicit declaration of default constructor */
	if (need_default_constr) {
		DECL_SPEC ds = (dspec_constr | cds);
		if (cj & cinfo_trivial_constr) {
			ci |= cinfo_trivial_constr;
			ds |= dspec_trivial;
		}
		pars[0] = NULL_type;
		ex = constr_except(ct, DEFAULT_CONSTR);
		IGNORE declare_func(ds, id, NULL_type, pars, FUNC_NONE, ex);
		noncopy_constr = 1;
		access_constr = 1;
	}

	/* Implicit declaration of copy constructor */
	if (need_copy_constr) {
		CV_SPEC cv = cv_lvalue;
		DECL_SPEC ds = (dspec_constr | cds);
		if (cj & cinfo_trivial_copy) {
			ci |= cinfo_trivial_copy;
			ds |= dspec_trivial;
		}
		if (cj & cinfo_const_copy) {
			ci |= cinfo_const_copy;
			cv |= cv_const;
		}
		MAKE_type_compound(cv, ct, t);
		COPY_id(type_name(t), cid);
		MAKE_type_ref(cv_none, t, t);
		pars[0] = t;
		pars[1] = NULL_type;
		ex = constr_except(ct, DEFAULT_COPY);
		IGNORE declare_func(ds, id, NULL_type, pars, FUNC_NONE, ex);
	}

	/* Check assignment operators (ignore inheritance) */
	nm = lookup_op(lex_assign);
	id = search_id(ns, nm, 0, 0);
	if (!IS_NULL_id(id)) {
		if (IS_id_mem_func(id)) {
			IDENTIFIER fid = id;
			while (!IS_NULL_id(fid)) {
				TYPE fn = DEREF_type(id_mem_func_type(fid));
				int c = check_copy_constr(fn, ct);
				if (c) {
					if (c == 2 || c == 3) {
						ci |= cinfo_const_assign;
					}
					need_assignment_op = 0;
					three_rule++;
				}
				fid = DEREF_id(id_mem_func_over(fid));
			}
		} else {
			/* Delete non-function meanings */
			clear_member(ns, nm);
		}
	} else {
		/* Create a dummy identifier */
		id = DEREF_id(hashid_id(nm));
	}

	/* Implicit declaration of copy assignment operator */
	if (need_assignment_op) {
		CV_SPEC cv = cv_lvalue;
		DECL_SPEC ds = (dspec_constr | cds);
		if (cj & cinfo_trivial_assign) {
			ci |= cinfo_trivial_assign;
			ds |= dspec_trivial;
		}
		if (cj & cinfo_const_assign) {
			ci |= cinfo_const_assign;
			cv |= cv_const;
		}
		MAKE_type_compound(cv, ct, t);
		COPY_id(type_name(t), cid);
		MAKE_type_ref(cv_none, t, t);
		pars[0] = t;
		pars[1] = NULL_type;
		MAKE_type_compound(cv_lvalue, ct, t);
		COPY_id(type_name(t), cid);
		MAKE_type_ref(cv_none, t, t);
		ex = constr_except(ct, DEFAULT_ASSIGN);
		IGNORE declare_func(ds, id, t, pars, FUNC_NONE, ex);
	}

	/* Check destructors */
	id = DEREF_id(ctype_destr(ct));
	if (IS_id_mem_func(id)) {
		DECL_SPEC acc = DEREF_dspec(id_storage(id));
		if ((acc & dspec_access)!= dspec_private) {
			access_destr = 1;
		}
		need_destructor = 0;
		three_rule++;
	} else {
		/* Delete non-function meanings */
		nm = DEREF_hashid(id_name(id));
		clear_member(ns, nm);
	}

	/* Implicit declaration of default destructor */
	if (need_destructor) {
		/* Check for trivial destructors */
		DECL_SPEC ds = (dspec_constr | cds);
		if (cj & cinfo_trivial_destr) {
			ci |= cinfo_trivial_destr;
			ds |= dspec_trivial;
		}
		pars[0] = NULL_type;
		ex = constr_except(ct, DEFAULT_DESTR);
		IGNORE declare_func(ds, id, NULL_type, pars, FUNC_NONE, ex);
		access_destr = 1;
	}

	/* Report inaccessible constructors or destructors */
	if (three_rule != 0 && three_rule != 3) {
		report(crt_loc, ERR_class_dtor_three(ct));
	}
	if (!noncopy_constr) {
		report(crt_loc, ERR_class_ctor_make(ct));
		access_constr = 1;
	}
	if (IS_NULL_list(pals)) {
		if (!access_constr) {
			report(crt_loc, ERR_class_ctor_private(ct));
		}
		if (!access_destr) {
			report(crt_loc, ERR_class_dtor_private(ct));
		}
	}
	return ci;
}


/*
    This routine finds the kind of constructor for the function id of
    type t.
*/

int
constr_kind(IDENTIFIER id, TYPE t)
{
	int n = DEFAULT_USR;
	HASHID nm = DEREF_hashid(id_name(id));
	switch (TAG_hashid(nm)) {
	case hashid_constr_tag: {
		if (min_no_args(t) == 1) {
			n = DEFAULT_CONSTR;
		} else {
			n = DEFAULT_COPY;
		}
		break;
	}
	case hashid_destr_tag: {
		/* Implicit default destructor */
		n = DEFAULT_DESTR;
		break;
	}
	case hashid_op_tag: {
		/* Implicit assignment operator */
		n = DEFAULT_ASSIGN;
		break;
	}
	}
	return n;
}


/*
    This routine defines the function id, which will be one of the
    implicitly declared constructors or destructors declared in
    implicit_decl.  n gives the constructor type or DEFAULT_USR if this
    is not known.
*/

void
implicit_defn(IDENTIFIER id, int n)
{
	TYPE t;
	EXP c, e, r;
	DECL_SPEC ds;
	IDENTIFIER fn;
	NAMESPACE cns;
	int in_func, in_decl;

	/* Check for previous definition */
	if (!IS_id_mem_func(id)) {
		return;
	}
	ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_inherit) {
		/* Inherited functions */
		id = DEREF_id(id_alias(id));
		ds = DEREF_dspec(id_storage(id));
	}
	if (!(ds & dspec_implicit)) {
		return;
	}
	if (ds & dspec_defn) {
		return;
	}
	ds |= dspec_defn;
	COPY_dspec(id_storage(id), ds);

	/* Find constructor type */
	t = DEREF_type(id_mem_func_type(id));
	if (!IS_type_func(t)) {
		return;
	}
	if (n == DEFAULT_USR) {
		n = constr_kind(id, t);
	}

	/* Force immediate access checks */
	in_func = in_function_defn;
	in_decl = in_declaration;
	fn = crt_func_id;
	in_function_defn = 1;
	in_declaration = 0;
	crt_func_id = id;

	/* Make initialiser list */
	start_try_check(univ_type_set);
	cns = DEREF_nspace(type_func_pars(t));
	push_namespace(cns);
	r = make_this_decl(id);
	/* create a compound block so that declarations for default
	 * arguments of inherited constructors will be added */
	c = begin_compound_stmt(1);
	cns = DEREF_nspace(id_parent(id));
	e = make_constr(cns, id, n, n);
	if (n == DEFAULT_DESTR) {
		/* Allow for destructor prelude */
		if (!(ds & dspec_trivial)) {
			EXP d = make_destr_prelude(cns);
			e = join_exp(d, e);
		}
	} else if (n == DEFAULT_ASSIGN) {
		/* Allow for return value */
		r = make_indir_exp(r);
		MAKE_exp_return_stmt(type_bottom, r, r);
		e = join_exp(e, r);
	}
	c = add_compound_stmt(c, e);
	e = end_compound_stmt(c);
	IGNORE pop_namespace();
	e = end_try_check(id, e);
	COPY_exp(id_mem_func_defn(id), e);
	define_id(id);

	/* Compile the function definition */
	if (!(ds & dspec_trivial)) {
		if (do_dump) {
			dump_implicit = 1;
			dump_declare(id, &crt_loc, 1);
		}
		compile_function(id, 0);
	}

	/* Restore old values */
	in_function_defn = in_func;
	in_declaration = in_decl;
	crt_func_id = fn;
	return;
}


/*
    These flags are used to indicate that an explicit constructor or
    conversion function has been declared.
*/

int have_conv_expl = 0;
int have_constr_expl = 0;


/*
    This routine removes all explicit constructors from the candidate list
    p beginning with the mth element.
*/

static void
remove_explicit(CANDIDATE_LIST *p, unsigned m)
{
	unsigned i, n = p->size;
	CANDIDATE *q = p->elem + m;
	for (i = m; i < n; i++) {
		DECL_SPEC ds = DEREF_dspec(id_storage(q->base));
		if (ds & dspec_explicit) {
			q->rank = RANK_IGNORE;
		}
		q++;
	}
	return;
}


/*
    This routine constructs the candidate list consisting of the constructors
    for the class type t (including the explicit constructors only if cast
    indicates an explicit conversion).  The candidates are added to the
    list p.  The routine returns the first constructor for t.
*/

static IDENTIFIER
constr_candidates(CANDIDATE_LIST *p, TYPE t, unsigned cast)
{
	/* Search for constructor candidates */
	IDENTIFIER cid;
	CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
	complete_class(ct, 1);
	cid = DEREF_id(ctype_constr(ct));
	if (IS_id_mem_func(cid)) {
		unsigned i = p->size;
		add_candidates(p, cid, 1, KIND_CONSTR);
		swap_candidates(p, i);
		if (cast == CAST_IMPLICIT && have_constr_expl) {
			remove_explicit(p, i);
		}
	} else {
		/* Can happen for incomplete types and in C */
		cid = NULL_id;
	}
	return cid;
}


/*
    This routine constructs the candidate list for the conversion functions
    for the type s which can be implicitly converted to type t, plus the
    constructors of t if t is a class type.  The candidates are added to
    the end of p.  The routine returns the first constructor for t if t is
    a class type, and the null identifier otherwise.
*/

IDENTIFIER
conv_candidates(CANDIDATE_LIST *p, TYPE t, TYPE s, unsigned cast)
{
	/* Add constructors */
	IDENTIFIER cid = NULL_id;
	if (IS_type_compound(t)) {
		cid = constr_candidates(p, t, cast);
	}

	/* Add conversion functions */
	if (IS_type_compound(s)) {
		LIST(IDENTIFIER)conv;
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
		complete_class(cs, 1);
		conv = DEREF_list(ctype_conv(cs));
		while (!IS_NULL_list(conv)) {
			IDENTIFIER id = DEREF_id(HEAD_list(conv));
			TYPE fn = DEREF_type(id_function_etc_type(id));
			if (IS_type_templ(fn)) {
				/* Allow for template functions */
				fn = deduce_conv(fn, t);
				if (!IS_NULL_type(fn)) {
					int eq = 0;
					id = deduce_func(id, fn, &eq);
				} else {
					id = NULL_id;
				}
			}
			if (!IS_NULL_id(id)) {
				unsigned r;
				CONVERSION c;
				HASHID nm = DEREF_hashid(id_name(id));
				c.from = DEREF_type(hashid_conv_type(nm));
				c.to = t;
				r = std_convert_seq(&c, NULL_exp, 0, 0);
				if (r != CONV_NONE) {
					unsigned i = p->size;
					add_candidates(p, id, 1, KIND_CONV);
					if (cast == CAST_IMPLICIT &&
					    have_conv_expl) {
						remove_explicit(p, i);
					}
				}
			}
			conv = TAIL_list(conv);
		}
	}
	return cid;
}


/*
    This routine adds all the conversion functions from the type t to
    types matching the type category mask kind to the candidate list p.
    Note that template conversion functions are excluded - they cannot
    give a non-ambiguous resolution and are beaten by any non-template
    conversion function.
*/

static void
gen_candidates(CANDIDATE_LIST *p, TYPE t, unsigned kind)
{
	if (IS_type_compound(t)) {
		LIST(IDENTIFIER)conv;
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		complete_class(ct, 1);
		conv = DEREF_list(ctype_conv(ct));
		while (!IS_NULL_list(conv)) {
			IDENTIFIER id = DEREF_id(HEAD_list(conv));
			TYPE fn = DEREF_type(id_function_etc_type(id));
			if (IS_type_func(fn)) {
				TYPE r = DEREF_type(type_func_ret(fn));
				unsigned c = type_category(&r);
				if (c & kind) {
					unsigned i = p->size;
					add_candidates(p, id, 1, KIND_CONV);
					if (have_conv_expl) {
						remove_explicit(p, i);
					}
				}
			}
			conv = TAIL_list(conv);
		}
	}
	return;
}


/*
    This routine applies a trivial destructor to the expression a.  It
    is used in explicit destructor and pseudo-destructor calls.
*/

EXP
trivial_destr(EXP a)
{
	EXP e = make_discard_exp(a);
	MAKE_exp_cast(type_void, CONV_ELLIPSIS, e, e);
	return e;
}


/*
    This routine applies the trivial constructor or destructor id to
    the arguments args.  The null expression is returned for invalid
    arguments.
*/

EXP
apply_trivial_func(IDENTIFIER id, LIST(EXP)args)
{
	EXP e = NULL_exp;
	TYPE t = DEREF_type(id_function_etc_type(id));
	int n = constr_kind(id, t);
	switch (n) {
	case DEFAULT_CONSTR: {
		if (LENGTH_list(args) == 1) {
			/* Trivial constructor */
			CLASS_TYPE ct = parent_class(id);
			t = make_class_type(ct);
			e = make_null_exp(t);
		}
		break;
	}
	case DEFAULT_COPY: {
		if (LENGTH_list(args) == 2) {
			/* Trivial copy constructor */
			ERROR err = NULL_err;
			LIST(TYPE)p = DEREF_list(type_func_mtypes(t));
			TYPE ta = DEREF_type(HEAD_list(p));
			ta = DEREF_type(type_ref_sub(ta));
			e = DEREF_exp(HEAD_list(TAIL_list(args)));
			e = convert_reference(e, REF_NORMAL);
			e = convert_class(ta, e, &err);
			if (!IS_NULL_err(err)) {
				err = concat_warning(err, ERR_expr_ass_conv());
				report(crt_loc, err);
			}
		}
		break;
	}
	case DEFAULT_DESTR: {
		if (LENGTH_list(args) == 1) {
			/* Trivial destructor */
			EXP a = DEREF_exp(HEAD_list(args));
			e = trivial_destr(a);
		}
		break;
	}
	case DEFAULT_ASSIGN: {
		if (LENGTH_list(args) == 2) {
			/* Trivial assignment */
			EXP a = DEREF_exp(HEAD_list(args));
			EXP b = DEREF_exp(HEAD_list(TAIL_list(args)));
			e = make_assign_exp(a, b, 1);
		}
		break;
	}
	}
	return e;
}


/*
    This routine applies the constructor id to the arguments args, using a
    dummy expression for the object the constructor is applied to.  The
    definition of this object, whether an existing object or a temporary,
    is filled in later.
*/

EXP
apply_constr(IDENTIFIER id, LIST(EXP)args)
{
	TYPE t;
	EXP e, a;
	DECL_SPEC ds;
	CLASS_TYPE ct;
	IDENTIFIER cid;
	CONS_exp(NULL_exp, args, args);

	/* Check for trivial constructors */
	ds = DEREF_dspec(id_storage(id));
	if (ds & dspec_trivial) {
		e = apply_trivial_func(id, args);
		if (!IS_NULL_exp(e)) {
			DESTROY_list(args, SIZE_exp);
			return e;
		}
	}

	/* Create dummy argument */
	ct = parent_class(id);
	cid = DEREF_id(ctype_name(ct));
	MAKE_type_compound(cv_lvalue, ct, t);
	COPY_id(type_name(t), cid);
	MAKE_exp_dummy(t, NULL_exp, LINK_NONE, NULL_off, 0, a);
	COPY_exp(HEAD_list(args), a);

	/* Apply the constructor */
	e = apply_func_id(id, qual_none, NULL_graph, args);
	if (IS_exp_func_id(e)) {
		int n = DEFAULT_USR;
		TYPE fn = DEREF_type(id_function_etc_type(id));
		if (check_copy_constr(fn, ct)) {
			/* Mark copy constructor calls */
			n = DEFAULT_COPY;
		}
		e = add_constr_args(e, ct, EXTRA_CONSTR);
		t = make_class_type(ct);
		MAKE_exp_constr(t, e, a, a, n, e);
	}
	return e;
}


/*
    This routine converts the argument list args to the class type t by
    constructor.  The cast parameter indicates if this is an explicit
    conversion.  The routine is used, for example, in initialisations of
    the form 't id ( args )'.
*/

EXP
convert_constr(TYPE t, LIST(EXP)args, ERROR *err, unsigned cast)
{
	EXP e;
	IDENTIFIER cid;
	CANDIDATE_LIST *p;

	/* Check for template parameters */
	if (dependent_conv(t, args)) {
		MAKE_exp_opn(t, lex_static_Hcast, args, e);
		return e;
	}

	/* Construct list of candidates */
	p = &candidates;
	p->size = 0;
	cid = constr_candidates(p, t, cast);

	/* Perform overload resolution */
	if (p->size) {
		CANDIDATE *q = resolve_overload(p, args, NULL_type, 0);
		IDENTIFIER qid = q->func;
		unsigned rank = q->rank;
		int kind = q->kind;
		if (rank == RANK_BEST) {
			/* Unambiguous resolution */
			if (!IS_NULL_id(cid)) {
				swap_candidates(p,(unsigned)0);
			}
			if (match_no_viable > 1 && overload_warn) {
				add_error(err, ERR_over_match_ctor_ok(qid));
			}
		} else if (rank == RANK_VIABLE) {
			/* Ambiguous resolution */
			q = resolve_ambiguous(p, args, NULL_type, 0);
			qid = q->func;
			rank = q->rank;
			if (!IS_NULL_id(cid)) {
				swap_candidates(p,(unsigned)0);
			}
			if (rank == RANK_TARGET) {
				ERROR err2 = ERR_over_match_ctor_target(qid);
				qid = make_ambig_func(p, qid, args, qual_none,
						      &err2);
				kind = KIND_FUNC;
				add_error(err, err2);
			} else if (rank == RANK_VIABLE) {
				ERROR err2 = ERR_over_match_ctor_ambig(qid);
				err2 = list_candidates(err2, p, RANK_VIABLE);
				add_error(err, err2);
			}
		} else {
			/* No resolution */
			if (!IS_NULL_id(cid)) {
				swap_candidates(p,(unsigned)0);
			}
			goto error_lab;
		}
		use_func_id(qid, 0, suppress_usage);
		if (kind == KIND_CONSTR) {
			e = apply_constr(qid, args);
		} else {
			/* Can only happen for target dependent resolutions */
			e = apply_func_id(qid, qual_none, NULL_graph, args);
			if (IS_exp_constr(e)) {
				/* Introduce temporary variable if necessary */
				TYPE s = DEREF_type(exp_type(e));
				e = make_temporary(s, e, NULL_exp, 0, err);
				e = convert_lvalue(e);
			}
		}
		return e;
	}

	/* Deal with incomplete structures */
	if (IS_NULL_id(cid)) {
		ERROR err2 = check_incomplete(t);
		if (!IS_NULL_err(err2)) {
			add_error(err, err2);
			add_error(err, ERR_expr_type_conv_incompl());
			e = make_null_exp(t);
			return e;
		}
#if LANGUAGE_C
		if (IS_NULL_list(args)) {
			/* C default initialisation */
			e = make_null_exp(t);
			return e;
		}
		if (IS_NULL_list(TAIL_list(args))) {
			/* C copy initialisation */
			EXP a = DEREF_exp(HEAD_list(args));
			a = convert_none(a);
			a = convert_class(t, a, err);
			a = remove_temporary(a, NULL_exp);
			return a;
		}
#endif
	}

	/* No candidates */
error_lab: {
		   CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		   cid = DEREF_id(ctype_constr(ct));
		   add_error(err, ERR_over_match_ctor_none(cid));
		   e = make_null_exp(t);
	   }
	   return e;
}


/*
    This routine checks for user-defined conversions of a to type t.
    It is identical to convert_conv except that it returns the null
    expression is there are no viable conversion functions.
*/

EXP
convert_conv_aux(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	IDENTIFIER cid;
	CANDIDATE_LIST *p;
	LIST(EXP)args;
	TYPE s = DEREF_type(exp_type(a));
	if (IS_type_error(s)) {
		EXP e = make_error_exp(0);
		return e;
	}

	/* Check for template parameters */
	CONS_exp(a, NULL_list(EXP), args);
	if (dependent_conv(t, args)) {
		EXP e = cast_templ_type(t, a, cast);
		DESTROY_list(args, SIZE_exp);
		return e;
	}

	/* Construct list of candidates */
	p = &candidates;
	p->size = 0;
	cid = conv_candidates(p, t, s, cast);

	/* Perform overload resolution */
	if (p->size) {
		EXP e;
		int kind;
		DECL_SPEC ds;
		CANDIDATE *q;
		unsigned rank;
		IDENTIFIER qid;
		match_this++;
		q = resolve_overload(p, args, t, 0);
		match_this--;
		qid = q->func;
		rank = q->rank;
		kind = q->kind;
		if (rank == RANK_BEST) {
			/* Unambiguous resolution */
			if (!IS_NULL_id(cid)) {
				swap_candidates(p,(unsigned)0);
			}
			if (match_no_viable > 1 && overload_warn) {
				add_error(err, ERR_over_match_conv_ok(qid));
			}
		} else if (rank == RANK_VIABLE) {
			/* Ambiguous resolution */
			q = resolve_ambiguous(p, args, t, 0);
			qid = q->func;
			rank = q->rank;
			if (!IS_NULL_id(cid)) {
				swap_candidates(p,(unsigned)0);
			}
			if (rank == RANK_TARGET) {
				ERROR err2 = ERR_over_match_conv_target(s, t);
				qid = make_ambig_func(p, qid, args, qual_none,
						      &err2);
				kind = KIND_FUNC;
				add_error(err, err2);
			} else if (rank == RANK_VIABLE) {
				ERROR err2 = ERR_over_match_conv_ambig(s, t);
				err2 = list_candidates(err2, p, RANK_VIABLE);
				add_error(err, err2);
			}
		} else {
			/* No resolution */
			if (!IS_NULL_id(cid)) {
				swap_candidates(p,(unsigned)0);
			}
			DESTROY_list(args, SIZE_exp);
			return NULL_exp;
		}

		/* Check conversion function */
		ds = DEREF_dspec(id_storage(qid));
		if (ds & dspec_trivial) {
			/* Trivial copy constructor */
			if (!(ds & dspec_defn)) {
				implicit_defn(qid, DEFAULT_COPY);
			}
			CONS_exp(NULL_exp, args, args);
			a = apply_trivial_func(qid, args);
			DESTROY_list(args, SIZE_exp);
			return a;
		}

		/* Apply conversion function */
		use_func_id(qid, 0, suppress_usage);
		if (kind == KIND_CONSTR) {
			if (eq_type_unqual(t, s)) {
				/* Force initialisation in copy constructor */
				int depth = init_ref_force;
				if (depth > 2 && IS_type_compound(t)) {
					TYPE fn = DEREF_type(id_function_etc_type(qid));
					CLASS_TYPE ct =
					    DEREF_ctype(type_compound_defn(t));
					int c = check_copy_constr(fn, ct);
					if (c == 3) {
						/* Bad copy constructor */
						HASHID nm =
						    DEREF_hashid(id_name(qid));
						add_error(err, ERR_class_copy_bad(nm));
						DESTROY_list(args, SIZE_exp);
						return a;
					}
				}
				init_ref_force = depth + 1;
				e = apply_constr(qid, args);
				init_ref_force = depth;
			} else {
				e = apply_constr(qid, args);
			}
		} else {
			e = apply_func_id(qid, qual_none, NULL_graph, args);
			if (IS_exp_constr(e)) {
				/* Introduce temporary variable if necessary */
				s = DEREF_type(exp_type(e));
				e = make_temporary(s, e, NULL_exp, 0, err);
			}
		}
		return e;
	}

	/* No candidates */
	DESTROY_list(args, SIZE_exp);
	return NULL_exp;
}


/*
    This routine converts the expression a to the type t by user-defined
    conversions.  It is used, for example, in initialisations of the form
    't id = a'.
*/

EXP
convert_conv(TYPE t, EXP a, ERROR *err, unsigned cast)
{
	EXP e = convert_conv_aux(t, a, err, cast);
	if (IS_NULL_exp(e)) {
		/* No viable conversion functions */
		TYPE s;
		a = convert_lvalue(a);
		s = DEREF_type(exp_type(a));
		if (!IS_type_error(s) && !IS_type_error(t)) {
			add_error(err, check_incomplete(t));
			if (check_int_type(t, btype_bool)) {
				e = convert_boolean(a, exp_paren_tag, err);
				return e;
			}
			add_error(err, ERR_expr_cast_invalid(s, t));
		}
		e = make_null_exp(t);
	} else {
		/* Deal with further implicit conversions */
		TYPE s = DEREF_type(exp_type(e));
		if (IS_type_ref(s)) {
			/* Reference conversion */
			s = DEREF_type(type_ref_sub(s));
			MAKE_exp_indir(s, e, e);
		}
		if (!IS_type_ref(t)) {
			CV_SPEC cv = DEREF_cv(type_qual(s));
			if (cv & cv_lvalue) {
				/* lvalue conversion */
				s = rvalue_type(s);
				MAKE_exp_contents(s, e, e);
			}
		}
		if (!eq_type(t, s)) {
			cast = (CAST_STANDARD | CAST_IMPLICIT);
			e = cast_exp(t, e, err, cast);
		}
	}
	return e;
}


/*
    This routine selects a user-defined conversion from the expression a
    to a type with category matching kind.  It returns the null expression
    if no such conversion exists.
*/

EXP
convert_gen(unsigned kind, EXP a, ERROR *err)
{
	EXP e = NULL_exp;
	TYPE t = DEREF_type(exp_type(a));

	/* Construct list of candidates */
	CANDIDATE_LIST *p = &candidates;
	p->size = 0;
	gen_candidates(p, t, kind);

	/* Perform overload resolution */
	if (p->size) {
		CANDIDATE *q;
		unsigned rank;
		IDENTIFIER qid;
		LIST(EXP)args;
		CONS_exp(a, NULL_list(EXP), args);
		match_this++;
		q = resolve_overload(p, args, NULL_type, 0);
		match_this--;
		qid = q->func;
		rank = q->rank;
		if (rank == RANK_BEST) {
			/* Unambiguous resolution */
			if (match_no_viable > 1 && overload_warn) {
				add_error(err, ERR_over_match_conv_ok(qid));
			}
		} else if (rank == RANK_VIABLE) {
			/* Ambiguous resolution */
			q = resolve_ambiguous(p, args, NULL_type, 0);
			qid = q->func;
			rank = q->rank;
			if (rank != RANK_BEST) {
				/* Can't be target dependent */
				ERROR err2 = ERR_over_match_conv_dup(t);
				err2 = list_candidates(err2, p, RANK_VIABLE);
				add_error(err, err2);
			}
		} else {
			/* No viable candidates */
			return e;
		}
		use_func_id(qid, 0, suppress_usage);
		e = apply_func_id(qid, qual_none, NULL_graph, args);
		e = convert_reference(e, REF_NORMAL);
		e = convert_lvalue(e);
	}

	/* No candidates */
	return e;
}
