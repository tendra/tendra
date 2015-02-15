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
#include "etype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "itype_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "off_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "access.h"
#include "allocate.h"
#include "basetype.h"
#include "cast.h"
#include "check.h"
#include "chktype.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
#include "copy.h"
#include "declare.h"
#include "derive.h"
#include "destroy.h"
#include "dump.h"
#include "exception.h"
#include "expression.h"
#include "file.h"
#include "function.h"
#include "hash.h"
#include "identifier.h"
#include "initialise.h"
#include "lex.h"
#include "namespace.h"
#include "overload.h"
#include "predict.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"
#include "typeid.h"


/*
    This routine calculates the simple arithmetic operation 'a op b'.  Any
    conversion errors are suppressed.
*/

static EXP
make_dim_exp(int op, EXP a, EXP b)
{
	EXP e;
	int et;
	if (IS_NULL_exp(a)) {
		return b;
	}
	if (IS_NULL_exp(b)) {
		return a;
	}
	et = error_threshold;
	error_threshold = ERR_SERIOUS;
	if (op == lex_plus) {
		e = make_plus_exp(a, b);
	} else {
		e = make_mult_exp(op, a, b);
	}
	error_threshold = et;
	return e;
}


/*
    The memory allocation and deallocation routines are only contained in
    the C++ producer.
*/

#if LANGUAGE_CPP


/*
    The variable type_bad_alloc is used to represent the standard exception
    type 'std::bad_alloc' thrown when an allocation function fails.  The
    list alloc_types is used to record all the function types for simple
    allocation functions.
*/

static TYPE type_bad_alloc = NULL_type;
static LIST(TYPE) alloc_types = NULL_list(TYPE);


/*
    This routine sets type_bad_alloc to be t, updating the exception
    specifiers of any simple allocation functions previously declared.
*/

static void
set_bad_alloc(TYPE t)
{
	if (!IS_NULL_type(t)) {
		LIST(TYPE)p = alloc_types;
		while (!IS_NULL_list(p)) {
			TYPE s = DEREF_type(HEAD_list(p));
			LIST(TYPE)e = DEREF_list(type_func_except(s));
			if (!IS_NULL_list(e) && !EQ_list(e, univ_type_set)) {
				/* Change 'throw ( X )' to
				 * 'throw ( std::bad_alloc )' */
				e = TAIL_list(e);
				CONS_type(t, e, e);
				COPY_list(type_func_except(s), e);
			}
			p = TAIL_list(p);
		}
		type_bad_alloc = t;
	}
	return;
}


/*
    This routine checks whether the function type t is a suitable
    declaration for the allocation or deallocation function given by id.
    mem is true for member functions.  The basic forms allowed are:

	void *operator new ( size_t, [further parameters] ) ;
	void *operator new[] ( size_t, [further parameters] ) ;
	void operator delete ( void *, [further parameters] ) ;
	void operator delete[] ( void *, [further parameters] ) ;

    Before the introduction of placement delete the only further parameters
    allowed in a deallocation function was a single 'size_t' for member
    functions.  Note that template functions are allowed (indicated by
    templ), but they must have the form above and at least one further
    parameter.
*/

TYPE
check_allocator(TYPE t, IDENTIFIER id, int mem, int templ)
{
	if (IS_type_templ(t)) {
		/* Allow for template types */
		TYPE s = DEREF_type(type_templ_defn(t));
		s = check_allocator(s, id, mem, templ + 1);
		COPY_type(type_templ_defn(t), s);

	} else {
		/* Find the operator */
		HASHID nm = DEREF_hashid(id_name(id));
		int op = DEREF_int(hashid_op_lex(nm));

		/* Decompose function type */
		TYPE s;
		TYPE r = DEREF_type(type_func_ret(t));
		LIST(TYPE)p = DEREF_list(type_func_ptypes(t));
		LIST(IDENTIFIER)q = DEREF_list(type_func_pids(t));
		int ell = DEREF_int(type_func_ellipsis(t));
		if (!IS_NULL_list(p)) {
			s = DEREF_type(HEAD_list(p));
			p = TAIL_list(p);
		} else {
			s = type_void;
		}

		if (op == lex_new || op == lex_new_Harray) {
			/* Allocator should return 'void *' */
			TYPE u = type_void_star;
			if (!eq_type(r, u)) {
				report(crt_loc, ERR_basic_stc_alloc_ret(nm, u));
			}

			/* First parameter should be 'size_t' */
			u = type_size_t;
			if (!eq_type(s, u)) {
				report(crt_loc, ERR_basic_stc_alloc_p1(nm, u));
			}

			/* First parameter can't have a default argument */
			if (!IS_NULL_list(q)) {
				IDENTIFIER pid = DEREF_id(HEAD_list(q));
				EXP darg = DEREF_exp(id_parameter_init(pid));
				if (!IS_NULL_exp(darg)) {
					report(crt_loc,
					       ERR_basic_stc_alloc_d1(nm));
				}
			}

			/* Template functions should have another parameter */
			if (templ && IS_NULL_list(p)) {
				report(crt_loc, ERR_basic_stc_alloc_templ(nm));
			}

		} else {
			/* Deallocator should return 'void' */
			TYPE u = type_void;
			if (!eq_type(r, u)) {
				report(crt_loc, ERR_basic_stc_alloc_ret(nm, u));
			}

			/* First argument should be 'void *' */
			u = type_void_star;
			if (!eq_type(s, u)) {
				report(crt_loc, ERR_basic_stc_alloc_p1(nm, u));
			}

			/* Template functions should have another parameter */
			if (templ && IS_NULL_list(p)) {
				report(crt_loc, ERR_basic_stc_alloc_templ(nm));
			}

			/* Second argument may be 'size_t' (old form) */
			if (mem && !IS_NULL_list(p)) {
				u = type_size_t;
				s = DEREF_type(HEAD_list(p));
				if (!eq_type(s, u)) {
					report(crt_loc,
					       ERR_basic_stc_alloc_p2(nm, u));
				}
				p = TAIL_list(p);
			}

			/* No further arguments allowed (old form) */
			if (!IS_NULL_list(p) || ell) {
				report(crt_loc, ERR_basic_stc_alloc_pn(nm));
			}
		}

		/* Look up 'std::bad_alloc' */
		s = type_bad_alloc;
		if (IS_NULL_type(s)) {
			s = find_std_type("bad_alloc", 1, 0);
			set_bad_alloc(s);
		}
	}
	return t;
}


/*
    This routine checks the allocator declaration id.  This should either
    be a class member or a member of the global namespace with external
    linkage.  alloc is 1 for allocator functions and 2 for deallocation
    functions.
*/

void
recheck_allocator(IDENTIFIER id, int alloc)
{
	NAMESPACE ns = DEREF_nspace(id_parent(id));
	if (alloc == 2) {
		IDENTIFIER over = DEREF_id(id_function_etc_over(id));
		if (!IS_NULL_id(over)) {
			/* Can't overload 'operator delete' (old form) */
			report(crt_loc, ERR_basic_stc_dealloc_over(over));
		}
	}
	if (!IS_NULL_nspace(ns)) {
		switch (TAG_nspace(ns)) {
		case nspace_global_tag: {
			/* Declared in global namespace */
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_static) {
				report(crt_loc, ERR_basic_stc_alloc_link(id));
			}
			if (alloc == 1 && crt_file_type == 1) {
				/* Check for built-in allocation functions */
				TYPE t = DEREF_type(id_function_type(id));
				if (IS_type_func(t)) {
					LIST(TYPE)p;
					p = DEREF_list(type_func_ptypes(t));
					if (LENGTH_list(p) == 1) {
						CONS_type(t, alloc_types,
							  alloc_types);
					}
				}
			}
			break;
		}
		case nspace_ctype_tag: {
			/* Declared in class namespace */
			break;
		}
		default: {
			/* Declared in other namespace */
			report(crt_loc, ERR_basic_stc_alloc_nspace(id));
			break;
		}
		}
	}
	return;
}


/*
    This routine selects a deallocation function from the set of overloaded
    functions id.  If pid is not the null identifier then it is an
    allocation function for which a matching placement delete is required.
    mem is true for member functions.
*/

static IDENTIFIER
resolve_delete(IDENTIFIER id, IDENTIFIER pid, int mem)
{
	int eq = 0;
	IDENTIFIER rid;
	LIST(TYPE)p;
	TYPE fn = type_temp_func;
	LIST(IDENTIFIER)pids = NULL_list(IDENTIFIER);
	COPY_type(type_func_ret(fn), type_void);
	COPY_cv(type_func_mqual(fn), cv_none);

	/* Try placement delete */
	if (!IS_NULL_id(pid)) {
		TYPE t = DEREF_type(id_function_etc_type(pid));
		if (IS_type_func(t)) {
			p = DEREF_list(type_func_ptypes(t));
			if (!IS_NULL_list(p)) {
				p = TAIL_list(p);
			}
			CONS_type(type_void_star, p, p);
			COPY_list(type_func_ptypes(fn), p);
			COPY_list(type_func_mtypes(fn), p);
			rid = resolve_func(id, fn, 1, 1, pids, &eq);
			COPY_list(type_func_ptypes(fn), NULL_list(TYPE));
			COPY_list(type_func_mtypes(fn), NULL_list(TYPE));
			DESTROY_CONS_type(destroy, t, p, p);
			UNUSED(p);
			UNUSED(t);
			if (!IS_NULL_id(rid)) {
				return rid;
			}
		}
		return NULL_id;
	}

	/* Try 'void ( void * )' */
	CONS_type(type_void_star, NULL_list(TYPE), p);
	COPY_list(type_func_ptypes(fn), p);
	COPY_list(type_func_mtypes(fn), p);
	rid = resolve_func(id, fn, 0, 1, pids, &eq);
	COPY_list(type_func_ptypes(fn), NULL_list(TYPE));
	COPY_list(type_func_mtypes(fn), NULL_list(TYPE));
	DESTROY_list(p, SIZE_type);
	if (!IS_NULL_id(rid)) {
		return rid;
	}

	/* Try 'void ( void *, size_t )' */
	if (mem) {
		CONS_type(type_size_t, NULL_list(TYPE), p);
		CONS_type(type_void_star, p, p);
		COPY_list(type_func_ptypes(fn), p);
		COPY_list(type_func_mtypes(fn), p);
		rid = resolve_func(id, fn, 0, 1, pids, &eq);
		COPY_list(type_func_ptypes(fn), NULL_list(TYPE));
		COPY_list(type_func_mtypes(fn), NULL_list(TYPE));
		DESTROY_list(p, SIZE_type);
		if (!IS_NULL_id(rid)) {
			return rid;
		}
	}
	return NULL_id;
}


/*
    This routine looks up the allocator function 'operator op'.  If b is
    true then the global namespace is checked first, otherwise if t is a
    class type then the members of t are checked, finally the allocator
    currently in scope is checked.  If option new_array is false and op
    is an array allocator, then the corresponding object allocator is
    returned, except if t is a class which has 'operator op' declared.
*/

IDENTIFIER
find_allocator(TYPE t, int op, int b, IDENTIFIER pid)
{
	int dealloc = 0;
	IDENTIFIER id = NULL_id;
	HASHID nm = lookup_op(op);
	HASHID nm_real = nm;

	/* Allow for pre-ISO dialect */
	switch (op) {
	case lex_new: {
		break;
	}
	case lex_new_Harray: {
		if (!option(OPT_new_array)) {
			nm = lookup_op(lex_new);
			t = type_error;
		}
		break;
	}
	case lex_delete: {
		dealloc = 1;
		break;
	}
	case lex_delete_Harray: {
		if (!option(OPT_new_array)) {
			nm = lookup_op(lex_delete);
			t = type_error;
		}
		dealloc = 1;
		break;
	}
	}

	if (b) {
		/* Try global scope ... */
		NAMESPACE ns = global_namespace;
		MEMBER mem = search_member(ns, nm, 0);
		if (!IS_NULL_member(mem)) {
			id = DEREF_id(member_id(mem));
			if (!IS_NULL_id(id) && dealloc) {
				id = resolve_delete(id, pid, 0);
			}
		}

	} else {
		/* Try class members ... */
		if (IS_type_compound(t)) {
			CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
			NAMESPACE ns = DEREF_nspace(ctype_member(ct));
			id = search_field(ns, nm_real, 0, 0);
			if (IS_NULL_id(id) && !EQ_hashid(nm, nm_real)) {
				id = search_field(ns, nm, 0, 0);
			}
			if (!IS_NULL_id(id) && IS_id_ambig(id)) {
				id = report_ambiguous(id, 0, 1, 1);
			}
			if (!IS_NULL_id(id) && dealloc) {
				id = resolve_delete(id, pid, 1);
			}
		}

		/* Try current scope ... */
		if (IS_NULL_id(id)) {
			id = find_op_id(nm);
			if (!IS_NULL_id(id) && dealloc) {
				id = resolve_delete(id, pid, 0);
			}
		}
	}

	/* Return function */
	if (!IS_NULL_id(id)) {
		if (IS_id_function_etc(id)) {
			/* Function found */
			return id;
		}
		if (is_ambiguous_func(id)) {
			if (dealloc) {
				/* Can't do overload resolution on delete */
				id = report_ambiguous(id, 0, 1, 1);
				return id;
			}
			return id;
		}
		if (!IS_id_dummy(id)) {
			/* Result is not a function */
			report(crt_loc, ERR_over_oper_func(id));
		}
	}
	if (IS_NULL_id(pid)) {
		/* Allocation functions not declared */
		report(crt_loc, ERR_lib_builtin(NULL_string, nm));
	}
	return NULL_id;
}


/*
    This routine constructs a delete expression in the case where the
    expression type depends on a template parameter.
*/

static EXP
make_templ_delete(int op, int b, EXP a)
{
	EXP e;
	if (b) {
		/* Allow for '::delete' */
		if (op == lex_delete) {
			op = lex_delete_Hfull;
		} else {
			op = lex_delete_Harray_Hfull;
		}
	}
	MAKE_exp_op(type_void, op, a, NULL_exp, e);
	return e;
}


/*
    This routine constructs the expressions 'delete a' and 'delete [] a'
    (as indicated by op).  b indicates whether the expression was actually
    '::delete'.  pid is used in placement delete expressions to give the
    corresponding allocation function (place then gives the extra
    arguments), otherwise it is the null identifier.
*/

static EXP
placement_delete(int op, int b, EXP a, IDENTIFIER pid, LIST(EXP)place)
{
	int i;
	EXP e, c;
	TYPE t, p;
	IDENTIFIER id;
	unsigned npids;
	EXP d = NULL_exp;
	int need_cast = 1;
	int v = EXTRA_DESTR;
	ERROR err = NULL_err;
	LIST(EXP)args = NULL_list(EXP);

	/* Do operand conversion */
	a = convert_reference(a, REF_NORMAL);
	t = DEREF_type(exp_type(a));
	if (IS_type_compound(t)) {
		/* Conversion of class to pointer */
		c = convert_gen(CTYPE_PTR, a, &err);
		if (!IS_NULL_exp(c)) {
			if (!IS_NULL_err(err)) {
				err = concat_error(err,
						   ERR_expr_delete_conv(op));
				report(crt_loc, err);
			}
			a = c;
		}
	}

	/* Check operand type */
	a = convert_lvalue(a);
	t = DEREF_type(exp_type(a));
	if (IS_type_ptr(t)) {
		CV_SPEC cv;
		int arr = 0;
		p = DEREF_type(type_ptr_sub(t));
		if (is_templ_depend(p)) {
			e = make_templ_delete(op, b, a);
			return e;
		}
		if (IS_type_top_etc(p)) {
			/* Check for 'void *' */
			report(crt_loc, ERR_expr_delete_void(op, t));
			need_cast = 0;
		} else {
			/* Check for incomplete types */
			err = check_object(p);
			if (!IS_NULL_err(err)) {
				err = concat_error(err,
						   ERR_expr_delete_obj(op));
				report(crt_loc, err);
			}
			err = check_incomplete(p);
			if (!IS_NULL_err(err)) {
				err = concat_error(err,
						   ERR_expr_delete_incompl(op));
				report(crt_loc, err);
				if (IS_type_compound(p)) {
					/* Mark incomplete class types */
					CLASS_TYPE ct =
					    DEREF_ctype(type_compound_defn(p));
					CLASS_USAGE cu =
					    DEREF_cusage(ctype_usage(ct));
					cu |= cusage_destr;
					if (b == 0) {
						if (op == lex_delete) {
							cu |= cusage_delete;
						} else {
							cu |= cusage_delete_array;
						}
					}
					COPY_cusage(ctype_usage(ct), cu);
				}
			}
		}
		while (IS_type_array(p)) {
			/* Allow for multi-dimensional arrays */
			arr = 1;
			p = DEREF_type(type_array_sub(p));
		}
		if (arr) {
			MAKE_type_ptr(cv_none, p, t);
		}
		cv = DEREF_cv(type_qual(p));
		if (cv & cv_const) {
			/* Check for deleting const objects */
			report(crt_loc, ERR_expr_delete_const(cv));
		}
	} else {
		/* Operand should be a pointer */
		if (is_templ_type(t)) {
			e = make_templ_delete(op, b, a);
			return e;
		}
		if (!IS_type_error(t)) {
			report(crt_loc, ERR_expr_delete_ptr(op, t));
		}
		MAKE_exp_value(type_void, e);
		return e;
	}

	/* Find destructors */
	err = NULL_err;
	i = (know_type(a) == 1 ? DEFAULT_DESTR : DEFAULT_DELETE);
	if (op == lex_delete && b == 0 && IS_NULL_id(pid)) {
		/* delete may be called via the destructor */
		v = (EXTRA_DESTR | EXTRA_DELETE);
	}
	d = init_default(p, &d, i, v, &err);
	if (!IS_NULL_err(err)) {
		report(crt_loc, err);
	}
	if (IS_NULL_exp(d)) {
		v = EXTRA_DESTR;
	}

	/* Find deallocation function */
	id = find_allocator(p, op, b, pid);
	if (!IS_NULL_id(id)) {
		LIST(IDENTIFIER)pids;
		TYPE fn = DEREF_type(id_function_etc_type(id));
		while (IS_type_templ(fn)) {
			fn = DEREF_type(type_templ_defn(fn));
		}
		pids = DEREF_list(type_func_pids(fn));
		npids = LENGTH_list(pids);
	} else {
		npids = 0;
	}

	/* Create dummy expression for first argument */
	MAKE_exp_dummy(t, a, LINK_NONE, NULL_off, 1, a);

	/* Create size variables if necessary */
	if (op == lex_delete || !IS_type_compound(p)) {
		c = NULL_exp;
		e = a;
	} else {
		OFFSET off;
		TYPE s = type_size_t;
		if (npids == 1 && IS_NULL_exp(d)) {
			MAKE_exp_null(s, c);
		} else {
			MAKE_exp_dummy(s, NULL_exp, LINK_NONE, NULL_off, 0, c);
		}
		MAKE_off_extra(p, -1, off);
		MAKE_exp_add_ptr(t, a, off, 0, e);
	}

	/* Create extra arguments */
	if (IS_NULL_id(pid)) {
		if (npids >= 2) {
			/* Pass size as extra argument */
			EXP sz = sizeof_exp(p);
			if (!IS_NULL_exp(c)) {
				EXP ex;
				OFFSET off;
				sz = make_dim_exp(lex_star, sz, c);
				MAKE_off_extra(p, 1, off);
				MAKE_exp_offset_size(type_size_t, off,
						     type_char, 1, ex);
				sz = make_dim_exp(lex_plus, sz, ex);
			}
			CONS_exp(sz, args, args);
		}
	} else {
		/* Copy placement arguments */
		/* NOT YET IMPLEMENTED */
		args = copy_exp_list(place, NULL_type, NULL_type);
	}

	/* Construct function call */
	if (!IS_NULL_id(id)) {
		if (need_cast) {
			MAKE_exp_cast(type_void_star, CONV_PTR_VOID, e, e);
		}
		CONS_exp(e, args, args);
		if (IS_id_stat_mem_func(id)) {
			/* Allow for static member functions */
			CONS_exp(NULL_exp, args, args);
		}
		use_func_id(id, 0, suppress_usage);
		e = apply_func_id(id, qual_none, NULL_graph, args);
		if (v == (EXTRA_DESTR | EXTRA_DELETE)) {
			/* 'operator delete' called via destructor */
			MAKE_exp_paren(type_void, e, e);
		}
	} else {
		e = NULL_exp;
	}

	/* Construct result */
	MAKE_exp_dealloc(type_void, d, e, a, c, e);
	return e;
}


/*
    This routine is a special case of placement_delete which handles the
    explicit delete expressions.
*/

EXP
make_delete_exp(int op, int b, EXP a)
{
	EXP e = placement_delete(op, b, a, NULL_id, NULL_list(EXP));
	return e;
}


/*
    It used to be necessary to include the size of the array being deleted
    in 'delete []'.  This routine deals with this anachronism.
*/

void
old_delete_array(EXP e)
{
	/* Check that e is a suitable array bound */
	int op = lex_delete_Harray;
	IGNORE make_new_array_dim(e);

	/* But complain just the same */
	report(crt_loc, ERR_expr_delete_array(op));
	return;
}


/*
    In a new-declarator the first array bound can be a variable expression,
    whereas all subsequent array bounds must be constant expressions as
    normal.  This routine is a version of make_array_dim designed exclusively
    to deal with this first bound.  Note that the result is not strictly
    a legal NAT and is only used to pass the bound information to
    make_new_exp, where it is prompty destroyed.
*/

NAT
make_new_array_dim(EXP e)
{
	NAT n;
	if (IS_exp_int_lit(e)) {
		/* Get the value if e is constant */
		n = DEREF_nat(exp_int_lit_nat(e));
	} else {
		/* Make dummy literal */
		MAKE_nat_calc(e, n);
	}
	return n;
}


/*
    This routine constructs a new expression in the case where the object
    type is a template parameter.  t gives the given type with array
    dimension d, while p is the pointer type.
*/

static EXP
make_templ_new(TYPE t, EXP d, TYPE p, int b, LIST(EXP)place, EXP init)
{
	EXP e;
	int op = (b ? lex_new_Hfull : lex_new);
	CONS_exp(init, place, place);
	CONS_exp(d, place, place);
	MAKE_exp_value(t, e);
	CONS_exp(e, place, place);
	MAKE_exp_opn(p, op, place, e);
	return e;
}


/*
    This routine constructs the expression 'new ( place ) ( t ) ( init )',
    where place is a possibly empty list of expressions and init is
    a new-initialiser expression.  n gives the number of types defined
    in t and b indicates whether the expression was actually '::new'.
*/

EXP
make_new_exp(TYPE t, int n, int b, LIST(EXP)place, EXP init)
{
	EXP e;
	EXP sz;
	TYPE ret;
	TYPE u = t;
	IDENTIFIER id;
	EXP v = NULL_exp;
	NAT d = NULL_nat;
	EXP gc = NULL_exp;
	EXP arr = NULL_exp;
	int need_cast = 1;
	int op = lex_new;
	int opd = lex_delete;
	LIST(EXP)placement = NULL_list(EXP);

	/* Check for type definitions */
	if (n) {
		report(crt_loc, ERR_expr_new_typedef());
	}

	/* Find result type (a pointer to t) and size of t */
	if (IS_type_array(t)) {
		/* Array form */
		EXP c1;
		TYPE tsz = type_size_t;
		TYPE s = DEREF_type(type_array_sub(t));
		MAKE_type_ptr(cv_none, s, ret);

		/* Check initial array bound */
		d = DEREF_nat(type_array_size(t));
		if (IS_nat_calc(d)) {
			/* Variable sized array */
			TYPE tc;
			unsigned cc;
			c1 = DEREF_exp(nat_calc_value(d));
			tc = DEREF_type(exp_type(c1));
			cc = type_category(&tc);
			if (!IS_TYPE_INT(cc) && !IS_TYPE_TEMPL(cc)) {
				/* Should have integral type */
				if (!IS_TYPE_ERROR(cc)) {
					report(crt_loc, ERR_expr_new_dim(tc));
				}
			}
			if (!in_template_decl) {
				/* Convert dimension to type 'size_t' */
				c1 = cast_exp(tsz, c1, KILL_err, CAST_STATIC);
			}
			u = s;
			v = c1;
		} else {
			c1 = calc_nat_value(d, tsz);
		}

		/* Find overall array size */
		if (IS_type_array(s)) {
			EXP c2 = sizeof_array(&s, tsz);
			c1 = make_dim_exp(lex_star, c2, c1);
		}
		if (IS_exp_int_lit(c1)) {
			/* Constant sized array */
			if (IS_type_compound(s)) {
				TYPE tc = DEREF_type(exp_type(c1));
				MAKE_exp_dummy(tc, c1, LINK_NONE, NULL_off, 0,
					       arr);
			}
			sz = sizeof_exp(t);
			d = DEREF_nat(exp_int_lit_nat(c1));
		} else {
			/* Variable sized array */
			TYPE tc = DEREF_type(exp_type(c1));
			MAKE_exp_dummy(tc, c1, LINK_NONE, NULL_off, 0, arr);
			sz = sizeof_exp(s);
			sz = make_dim_exp(lex_star, sz, arr);
			MAKE_nat_calc(c1, d);
			if (!IS_type_compound(s)) {
				arr = NULL_exp;
			}
		}

		/* Add extra array space */
		if (IS_type_compound(s)) {
			OFFSET off;
			MAKE_off_extra(s, 1, off);
			MAKE_exp_offset_size(tsz, off, type_char, 1, c1);
			sz = make_dim_exp(lex_plus, sz, c1);
		}
		op = lex_new_Harray;
		opd = lex_delete_Harray;
		t = s;
	} else {
		/* Normal form */
		if (IS_type_top_etc(t)) {
			need_cast = 0;
		}
		MAKE_type_ptr(cv_none, t, ret);
		sz = sizeof_exp(t);
	}

	/* Do reference conversions */
	if (!IS_NULL_list(place)) {
		place = convert_args(place);
		placement = place;
	}

	/* Check for template parameters */
	if (is_templ_type(t)) {
		e = make_templ_new(u, v, ret, b, place, init);
		return e;
	}

	/* Add 'sizeof ( t )' to the start of placement */
	CONS_exp(sz, place, place);

	/* Call allocator function */
	id = find_allocator(t, op, b, NULL_id);
	if (IS_NULL_id(id)) {
		e = make_error_exp(0);
		return e;
	}
	if (IS_id_stat_mem_func(id)) {
		CONS_exp(NULL_exp, place, place);
	}
	id = resolve_call(id, place, qual_none, 0);
	use_func_id(id, 0, suppress_usage);
	e = apply_func_id(id, qual_none, NULL_graph, place);
	if (need_cast) {
		MAKE_exp_cast(ret,(CONV_PTR_VOID | CONV_REVERSE), e, e);
	}

	/* Deal with array initialisers */
	if (!IS_NULL_exp(init)) {
		EXP a0 = new_try_body(init);
		if (IS_NULL_exp(a0)) {
			/* Can happen with templates */
			init = NULL_exp;
		} else {
			if (!IS_NULL_nat(d)) {
				EXP a = DEREF_exp(exp_assign_arg(a0));
				MAKE_type_array(cv_none, t, d, t);
				MAKE_exp_nof(t, NULL_exp, d, a, NULL_exp, a);
				COPY_exp(exp_assign_arg(a0), a);
				a = DEREF_exp(exp_assign_ref(a0));
				COPY_type(exp_type(a), t);
				COPY_type(exp_type(a0), t);
				/* NOT YET IMPLEMENTED - destructors of
				 * temporaries */
			}
		}
	}

	/* Deal with clean-up routine */
	if (!IS_NULL_exp(init)) {
		EXP a;
		int du = do_dump;
		int ac = do_access_checks;
		do_dump = 0;
		do_access_checks = 0;
		MAKE_exp_value(ret, a);
		if (IS_NULL_list(placement)) {
			id = NULL_id;
		}
		gc = placement_delete(opd, b, a, id, placement);
		do_access_checks = ac;
		do_dump = du;
	}

	/* Return the result */
	MAKE_exp_alloc(ret, e, init, gc, arr, e);
	return e;
}


/*
    This routine creates a new-initialiser expression of type t from the
    expression list p.
*/

EXP
make_new_init(TYPE t, LIST(EXP)p, int init)
{
	EXP e;
	int op = lex_new;
	ERROR err = check_complete(t);
	if (!IS_NULL_err(err)) {
		/* Type should be complete */
		err = concat_error(err, ERR_expr_new_incompl());
		report(crt_loc, err);
	}
	err = check_abstract(t);
	if (!IS_NULL_err(err)) {
		/* Type can't be abstract */
		err = concat_error(err, ERR_expr_new_abstract());
		report(crt_loc, err);
		err = NULL_err;
	}
	while (IS_type_array(t)) {
		/* Step over array components */
		op = lex_new_Harray;
		if (init) {
			report(crt_loc, ERR_expr_new_array_init(op));
			init = 0;
		}
		t = DEREF_type(type_array_sub(t));
	}
	p = convert_args(p);
	if (is_templ_type(t)) {
		if (op == lex_new_Harray) {
			/* Create dummy array type */
			NAT n = small_nat[1];
			MAKE_type_array(cv_none, t, n, t);
		}
		if (init) {
			MAKE_exp_opn(t, lex_compute, p, e);
		} else {
			MAKE_exp_op(t, lex_compute, NULL_exp, NULL_exp, e);
		}
	} else {
		if (init) {
			e = init_constr(t, p, &err);
		} else {
			e = init_empty(t, cv_none, 0, &err);
		}
		if (!IS_NULL_err(err)) {
			/* Report conversion errors */
			err = concat_error(ERR_expr_new_init(op), err);
			report(crt_loc, err);
		}
		if (!IS_NULL_exp(e)) {
			/* Assign value to dummy expression */
			EXP a;
			MAKE_exp_dummy(t, NULL_exp, LINK_NONE, NULL_off, 1, a);
			MAKE_exp_assign(t, a, e, e);
		}
	}
	return e;
}


/*
    Each new-initialiser is enclosed in a dummy try block.  This is because
    if the initialiser throws an exception it is necessary to catch it,
    delete the memory just allocated, and then re-throw the exception to
    the enclosing real handler.
*/

EXP
begin_new_try(void)
{
	EXP a = begin_try_stmt(0);
	EXP b = begin_compound_stmt(2);
	COPY_exp(exp_try_block_body(a), b);
	return a;
}


/*
    This routine adds the new-initialiser expression b to the try block a.
*/

EXP
end_new_try(EXP a, EXP b)
{
	EXP c = DEREF_exp(exp_try_block_body(a));
	c = add_compound_stmt(c, b);
	c = end_compound_stmt(c);
	a = cont_try_stmt(a, c);
	a = end_try_stmt(a, 1);
	if (IS_NULL_exp(b)) {
		free_exp(a, 1);
		a = NULL_exp;
	}
	return a;
}


/*
    This routine returns the initialiser component of the new-initialiser
    try block a.
*/

EXP
new_try_body(EXP a)
{
	while (!IS_NULL_exp(a)) {
		switch (TAG_exp(a)) {
		case exp_try_block_tag: {
			a = DEREF_exp(exp_try_block_body(a));
			break;
		}
		case exp_decl_stmt_tag: {
			a = DEREF_exp(exp_decl_stmt_body(a));
			break;
		}
		case exp_sequence_tag: {
			LIST(EXP)p = DEREF_list(exp_sequence_first(a));
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				a = NULL_exp;
			} else {
				a = DEREF_exp(HEAD_list(p));
			}
			break;
		}
		case exp_location_tag: {
			a = DEREF_exp(exp_location_arg(a));
			break;
		}
		default: {
			return a;
		}
		}
	}
	return NULL_exp;
}


/*
    The remaining routines are common to both producers.
*/

#endif /* LANGUAGE_CPP */


/*
    This routine multiplies the dimensions of any array components in the
    type pointed to by pt returning it as an expression of type s.  It
    assigns the non-array components back to pt.
*/

EXP
sizeof_array(TYPE *pt, TYPE s)
{
	TYPE t = *pt;
	EXP a = NULL_exp;
	while (IS_type_array(t)) {
		EXP b;
		NAT n = DEREF_nat(type_array_size(t));
		if (IS_NULL_nat(n)) {
			n = small_nat[0];
		}
		b = calc_nat_value(n, s);
		a = make_dim_exp(lex_star, a, b);
		t = DEREF_type(type_array_sub(t));
	}
	*pt = t;
	return a;
}


/*
    This routine calculates the size of the type t when this can be precisely
    evaluated, returning the null literal if this is not possible.
*/

static NAT
sizeof_type(TYPE t)
{
	switch (TAG_type(t)) {
	case type_integer_tag: {
		/* Allow for integral types */
		INT_TYPE it = DEREF_itype(type_integer_rep(t));
		if (IS_itype_basic(it)) {
			BASE_TYPE bt = DEREF_btype(itype_basic_rep(it));
			if (bt & btype_char) {
				/* char has size one */
				NAT n = small_nat[1];
				return n;
			}
		}
		break;
	}
	case type_top_tag:
	case type_bottom_tag: {
		/* void has size one */
		NAT n = small_nat[1];
		return n;
	}
	case type_array_tag: {
		/* Allow for array types */
		TYPE s = type_size_t;
		EXP a = sizeof_array(&t, s);
		NAT n = sizeof_type(t);
		if (!IS_NULL_nat(n)) {
			EXP b = calc_nat_value(n, s);
			a = make_dim_exp(lex_star, a, b);
			if (IS_exp_int_lit(a)) {
				n = DEREF_nat(exp_int_lit_nat(a));
				return n;
			}
		}
		break;
	}
	case type_enumerate_tag: {
		/* An enumeration maps to its underlying type */
		ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
		TYPE s = DEREF_type(etype_rep(et));
		return sizeof_type(s);
	}
	}
	return NULL_nat;
}


/*
    This routine constructs the expression 'sizeof ( t )' without applying
    any checks to t.
*/

EXP
sizeof_exp(TYPE t)
{
	EXP e;
	NAT sz = sizeof_type(t);
	if (IS_NULL_nat(sz)) {
		/* Calculate size if it is not obvious */
		OFFSET off;
		MAKE_off_type(t, off);
		MAKE_exp_offset_size(type_size_t, off, type_char, 1, e);
		MAKE_nat_calc(e, sz);
	}
	MAKE_exp_int_lit(type_size_t, sz, exp_offset_size_tag, e);
	return e;
}


/*
    This routine constructs the expression 'sizeof ( t )'.  Note that
    'sizeof a' has already been reduced to 'sizeof ( typeof ( a ) )'
    except in the case where the result depends on a template parameter.
    The argument n gives the number of types defined in t.  Note that the
    result is a constant integer expression.
*/

EXP
make_sizeof_exp(TYPE t, EXP a, int n, int op)
{
	/* Deal with argument dependent case */
#if LANGUAGE_CPP
	if (!IS_NULL_exp(a)) {
		EXP e;
		NAT sz;
		TYPE s = type_size_t;
		MAKE_exp_op(s, op, a, NULL_exp, e);
		MAKE_nat_calc(e, sz);
		MAKE_exp_int_lit(s, sz, exp_op_tag, e);
		return e;
	}
#else
	UNUSED(a);
#endif

	/* Check on type */
	switch (TAG_type(t)) {
	case type_func_tag: {
		/* Can't have sizeof (function) */
		report(crt_loc, ERR_expr_sizeof_func(op));
		MAKE_type_ptr(cv_none, t, t);
		break;
	}
	case type_bitfield_tag: {
		/* Can't have sizeof (bitfield) */
		report(crt_loc, ERR_expr_sizeof_bitf(op));
		t = find_bitfield_type(t);
		break;
	}
	case type_ref_tag: {
		/* sizeof (T &) equals sizeof (T) */
		t = DEREF_type(type_ref_sub(t));
		break;
	}
	default : {
		/* Can't have sizeof (incomplete) */
		ERROR err = check_incomplete(t);
		if (!IS_NULL_err(err)) {
			err = concat_error(err, ERR_expr_sizeof_incompl(op));
			report(crt_loc, err);
		}
		break;
	}
	}

	/* Report on type definitions */
	if (n) {
		report(crt_loc, ERR_expr_sizeof_typedef(op));
	}

	/* Calculate result */
	return sizeof_exp(t);
}


/*
    This routine returns the type of the expression pointed to by pa after
    apply reference conversions to it.  It is used, for example, to
    transform 'sizeof ( a )' into 'sizeof ( t )'.  n gives the number of
    side effects in pa.
*/

TYPE
typeof_exp(EXP *pa, int n, int op)
{
	TYPE t;
	EXP a = *pa;
	if (n) {
		report(crt_loc, ERR_expr_sizeof_side(op));
	}
	a = convert_reference(a, REF_NORMAL);
	a = convert_none(a);
	t = DEREF_type(exp_type(a));
	if (!is_templ_type(t)) {
		/* Free operand in simple case */
		free_exp(a, 2);
		a = NULL_exp;
	}
	*pa = a;
	return t;
}


/*
    This routine returns the number of initialisers in the expression e
    counting each array element separately.
*/

EXP
sizeof_init(EXP e, TYPE s)
{
	EXP a = NULL_exp;
	unsigned long v = 0;
	if (!IS_NULL_exp(e)) {
		LIST(EXP)p, q;
		if (IS_exp_comma(e)) {
			p = DEREF_list(exp_comma_args(e));
			p = END_list(p);
			e = DEREF_exp(HEAD_list(p));
		}
		if (IS_exp_initialiser(e)) {
			p = DEREF_list(exp_initialiser_args(e));
			q = NULL_list(EXP);
		} else {
			CONS_exp(e, NULL_list(EXP), p);
			q = p;
		}
		while (!IS_NULL_list(p)) {
			EXP b = DEREF_exp(HEAD_list(p));
			if (!IS_NULL_exp(b)) {
				TYPE t = DEREF_type(exp_type(b));
				if (IS_type_array(t)) {
					/* Multiply up array bounds */
					EXP c = sizeof_array(&t, s);
					a = make_dim_exp(lex_plus, a, c);
				} else {
					/* Other types count once */
					v++;
				}
			}
			p = TAIL_list(p);
		}
		if (!IS_NULL_list(q)) {
			DESTROY_list(q, SIZE_exp);
		}
	}
	if (IS_NULL_exp(a)) {
		NAT n = make_nat_value(v);
		a = calc_nat_value(n, s);
	} else {
		if (v) {
			NAT n = make_nat_value(v);
			EXP c = calc_nat_value(n, s);
			a = make_dim_exp(lex_plus, a, c);
		}
	}
	return a;
}
