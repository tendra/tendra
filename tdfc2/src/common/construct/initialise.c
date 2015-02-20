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
#include "version.h"
#include "c_types.h"

#include "ctype_ops.h"
#include "etype_ops.h"
#include "exp_ops.h"
#include "ftype_ops.h"
#include "graph_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "member_ops.h"
#include "nat_ops.h"
#include "nspace_ops.h"
#include "str_ops.h"
#include "type_ops.h"
#include "error.h"
#include "catalog.h"
#include "option.h"
#include "tdf.h"
#include "access.h"
#include "assign.h"
#include "basetype.h"
#include "buffer.h"
#include "cast.h"
#include "check.h"
#include "chktype.h"
#include "class.h"
#include "compile.h"
#include "constant.h"
#include "construct.h"
#include "convert.h"
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
#include "instance.h"
#include "inttype.h"
#include "literal.h"
#include "namespace.h"
#include "overload.h"
#include "parse.h"
#include "predict.h"
#include "print.h"
#include "statement.h"
#include "syntax.h"
#include "template.h"
#include "tok.h"
#include "tokdef.h"
#include "token.h"
#include "ustring.h"


/*
    A static member can be defined inline in its class.  This is only a
    provisional definition for use in constant expressions etc.  The real
    definition (which cannot contain an initialiser) must be provided
    elsewhere.  This value is used to indicate such members.
*/

#define dspec_stat_inline	dspec_explicit
#define dspec_ignore_mem	(dspec_alias | dspec_inherit | dspec_token)


/*
    This variable is used to keep track of the number of data members
    within next_data_member.  Anonymous unions, rather than their members,
    are counted.
*/

unsigned long member_no = 0;


/*
    This routine returns the first non-static, non-function member of a
    class following mem.  Anonymous unions are included if bit 1 of bf
    is false, but their members if it is true.  Anonymous bitfields are
    included if bit 0 of bf is true.  The null member is returned if there
    are no further members.
*/

MEMBER
next_data_member(MEMBER mem, int bf)
{
	while (!IS_NULL_member(mem)) {
		IDENTIFIER id = DEREF_id(member_id(mem));
		if (!IS_NULL_id(id) && IS_id_member(id)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (!(ds & dspec_ignore_mem)) {
				int ok = 1;
				HASHID nm = DEREF_hashid(id_name(id));
				if (ds & dspec_reserve) {
					/* Anonymous union members */
					if (!(bf & 2)) {
						ok = 0;
					}
				} else {
					member_no++;
				}
				if (IS_hashid_anon(nm)) {
					TYPE t = DEREF_type(id_member_type(id));
					unsigned tag = TAG_type(t);
					if (tag == type_bitfield_tag) {
						/* Anonymous bitfield */
						if (!(bf & 1)) {
							ok = 0;
						}
					} else if (tag == type_compound_tag) {
						/* Anonymous union */
						if (bf & 2) {
							ok = 0;
						}
					}
				}
				if (ok) {
					return mem;
				}
			}
		}
		mem = DEREF_member(member_next(mem));
	}
	return NULL_member;
}


/*
    This routine checks whether the expression e is a non-constant
    initialiser for id (or a component of id if off is not null).  If so
    it is embedded in a dynamic initialiser expression and an error is
    reported.
*/

EXP
dynamic_init(IDENTIFIER id, string off, EXP e)
{
	int fs = 0;
	int c = -1;
	if (!IS_NULL_id(id)) {
		switch (TAG_id(id)) {
		case id_variable_tag: {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_auto) {
				if (off == NULL) {
					return e;
				}
			} else {
				if (!(ds & dspec_linkage)) {
					fs = 1;
				}
			}
			break;
		}
		case id_stat_member_tag:
			/* Check static members */
			break;
		default:
			/* Ignore other identifiers */
			return e;
		}
	}
	if (option(OPT_init_dynamic)) {
		/* Dynamic initialisation not allowed */
		c = 1;
	}
	if (!is_const_exp(e, c)) {
		/* Non-constant initialiser */
		TYPE t = DEREF_type(exp_type(e));
		if (!is_templ_type(t)) {
			ERROR err;
			if (off) {
				err = ERR_dcl_init_aggr_dynamic();
			} else {
				err = ERR_dcl_init_dynamic();
			}
			if (!IS_NULL_err(err)) {
				ERROR err2 = ERR_dcl_init_decl(id, off);
				err = concat_error(err2, err);
				report(crt_loc, err);
			}
			if (fs) {
				/* Check function statics */
				e = check_return_exp(e, lex_static);
			}
			MAKE_exp_dynamic(t, e, e);
		}
	}
	return e;
}


/*
    This routine is called to check the initialiser for a variable or static
    data member.  Its primary purpose is to mark those temporaries which
    are bound to variables.
*/

EXP
check_init(EXP e)
{
	if (!IS_NULL_exp(e)) {
		switch (TAG_exp(e)) {
		case exp_identifier_tag: {
			IDENTIFIER id = DEREF_id(exp_identifier_id(e));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_temp) {
				ds &= ~dspec_register;
				COPY_dspec(id_storage(id), ds);
			}
			break;
		}
		case exp_init_tag: {
			IDENTIFIER id = DEREF_id(exp_init_id(e));
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_temp) {
				ds &= ~dspec_register;
				COPY_dspec(id_storage(id), ds);
			}
			break;
		}
		case exp_indir_tag: {
			EXP a = DEREF_exp(exp_indir_ptr(e));
			a = check_init(a);
			COPY_exp(exp_indir_ptr(e), a);
			break;
		}
		case exp_address_tag: {
			EXP a = DEREF_exp(exp_address_arg(e));
			a = check_init(a);
			COPY_exp(exp_address_arg(e), a);
			break;
		}
		case exp_base_cast_tag: {
			EXP a = DEREF_exp(exp_base_cast_arg(e));
			a = check_init(a);
			COPY_exp(exp_base_cast_arg(e), a);
			break;
		}
		case exp_add_ptr_tag: {
			EXP a = DEREF_exp(exp_add_ptr_ptr(e));
			a = check_init(a);
			COPY_exp(exp_add_ptr_ptr(e), a);
			break;
		}
		case exp_dynamic_tag: {
			EXP a = DEREF_exp(exp_dynamic_arg(e));
			a = check_init(a);
			COPY_exp(exp_dynamic_arg(e), a);
			break;
		}
		case exp_aggregate_tag: {
			LIST(EXP) p = DEREF_list(exp_aggregate_args(e));
			while (!IS_NULL_list(p)) {
				EXP a = DEREF_exp(HEAD_list(p));
				a = check_init(a);
				COPY_exp(HEAD_list(p), a);
				p = TAIL_list(p);
			}
			break;
		}
		case exp_nof_tag: {
			EXP a = DEREF_exp(exp_nof_start(e));
			EXP b = DEREF_exp(exp_nof_pad(e));
			EXP c = DEREF_exp(exp_nof_end(e));
			a = check_init(a);
			b = check_init(b);
			c = check_init(c);
			COPY_exp(exp_nof_start(e), a);
			COPY_exp(exp_nof_pad(e), b);
			COPY_exp(exp_nof_end(e), c);
			break;
		}
		}
	}
	return e;
}


/*
    The variable made_temporary is set to the temporary variable whenever
    a temporary variable is created.  temp_storage is used to determine
    the storage class for a local variable.
*/

IDENTIFIER made_temporary = NULL_id;
int keep_temporary = 0;
static DECL_SPEC temp_storage = dspec_auto;


/*
    This routine declares a temporary variable of type t, initial value
    e, and destructor d (the implicit destructor will be created if this
    is the null expression).  It returns an expression giving the value of
    this temporary.  Note the use of an assignment expression to ensure
    that the temporary gets initialised in the right place.
*/

EXP
make_temporary(TYPE t, EXP e, EXP d, int ref, ERROR *err)
{
	LOCATION loc;
	DECL_SPEC ds;
	EXP c = NULL_exp;
	HASHID nm = lookup_anon();
	NAMESPACE ns = crt_namespace;
	QUALIFIER cq = crt_id_qualifier;
	int tq = crt_templ_qualifier;
	int fn = in_function_defn;
	IDENTIFIER id = DEREF_id(hashid_id(nm));
	loc = decl_loc;
	decl_loc = crt_loc;
	crt_id_qualifier = qual_none;
	crt_templ_qualifier = 0;

	/* Declare the temporary object */
	if (IS_type_ref(t)) {
		t = DEREF_type(type_ref_sub(t));
	}
	if (in_default_arg) {
		/* NOT YET IMPLEMENTED */
		crt_namespace = global_namespace;
		in_function_defn = 0;
	}
	t = qualify_type(t, cv_none, 0);
	if (IS_type_compound(t)) {
		add_error(err, ERR_dcl_init_ref_tmp(t));
	}
	id = make_object_decl(dspec_temp, t, id, 0);
	ds = DEREF_dspec(id_storage(id));
	if (temp_storage != dspec_auto) {
		/* Set storage class */
		ds &= ~dspec_storage;
		ds |= temp_storage;
	}
	if (ds & dspec_auto) {
		ds |= dspec_register;
	}
	COPY_dspec(id_storage(id), ds);
	made_temporary = id;

	/* Check initialiser */
	if (!is_const_exp(e, -1)) {
		if (ds & dspec_auto) {
			c = e;
			e = NULL_exp;
		} else if (ref) {
			TYPE s = DEREF_type(exp_type(e));
			MAKE_exp_dynamic(s, e, e);
			add_error(err, ERR_dcl_init_dynamic());
		} else {
			TYPE s = DEREF_type(exp_type(e));
			c = e;
			e = make_null_exp(s);
		}
	}
	if (IS_NULL_exp(d)) {
		/* Create destructor */
		int du = do_usage;
		do_usage = 0;
		d = init_default(t, &d, DEFAULT_DESTR, EXTRA_DESTR, err);
		do_usage = du;
	}
	COPY_exp(id_variable_init(id), e);
	COPY_exp(id_variable_term(id), d);
	define_id(id);

	/* Construct the result expression */
	if (!IS_NULL_exp(c)) {
		/* Assign initial value */
		t = DEREF_type(id_variable_type(id));
		MAKE_exp_init(t, id, c, e);
		ds = DEREF_dspec(id_storage(id));
		ds |= dspec_explicit;
		COPY_dspec(id_storage(id), ds);
	} else {
		e = make_id_exp(id);
	}

	/* Define variable */
	if (!(ds & dspec_auto)) {
		if (!really_in_function_defn && !in_template_decl) {
			/* Compile variable definition */
			compile_variable(id, 0);
		}
	}
	if (do_dump) {
		dump_implicit = 1;
		dump_declare(id, &decl_loc, 1);
	}
	crt_templ_qualifier = tq;
	crt_id_qualifier = cq;
	in_function_defn = fn;
	crt_namespace = ns;
	decl_loc = loc;
	return e;
}


/*
    This routine checks whether the variable expression d is aliased in
    the expression e.
*/

static int
involves_alias(EXP e, EXP d)
{
	if (!IS_NULL_exp(d)) {
		/* NOT YET IMPLEMENTED */
		UNUSED(e);
		return 1;
	}
	return 0;
}


/*
    This routine is called to eliminate any temporary variables from the
    value e which is to be assigned to a variable given by d.  d is the
    null expression in a variable initialisation, otherwise care needs
    to be taken if d is aliased in e.  Note that creating a temporary and
    then removing it ensures that the accesses for the copy constructor
    and destructor are checked correctly.
*/

EXP
remove_temporary(EXP e, EXP d)
{
	if (!IS_NULL_exp(e)) {
		EXP a = NULL_exp;
		unsigned tag = TAG_exp(e);
		if (tag == exp_constr_tag) {
			LIST(EXP)p;
			int info = DEREF_int(exp_constr_info(e));
			if (info != DEFAULT_COPY) {
				return e;
			}
			a = DEREF_exp(exp_constr_call(e));
			p = DEREF_list(exp_func_id_args(a));
			if (IS_NULL_list(p)) {
				return e;
			}
			p = TAIL_list(p);
			if (IS_NULL_list(p)) {
				return e;
			}
			a = DEREF_exp(HEAD_list(p));
			if (!IS_exp_address(a)) {
				return e;
			}
			a = DEREF_exp(exp_address_arg(a));
		} else if (tag == exp_contents_tag) {
			a = DEREF_exp(exp_contents_ptr(e));
		}
		if (!IS_NULL_exp(a) && IS_exp_init(a)) {
			/* Check for temporary variable */
			IDENTIFIER id = DEREF_id(exp_init_id(a));
			if (IS_id_variable(id)) {
				DECL_SPEC ds = DEREF_dspec(id_storage(id));
				if ((ds & dspec_temp) && !keep_temporary) {
					/* Eliminate temporary variable */
					EXP b = DEREF_exp(exp_init_arg(a));
					if (IS_NULL_exp(b)) {
						b = DEREF_exp(id_variable_init(id));
					}
					if (!involves_alias(b, d)) {
						ds |= dspec_ignore;
						COPY_dspec(id_storage(id), ds);
						return b;
					}
				}
			}
		}
	}
	return e;
}


/*
    This flag forces a reference to be initialised by a less cv-qualified
    version of the same type.  Values of greater than 1 can arise in
    copy constructors.
*/

int init_ref_force = 1;


/*
    This routine checks whether e is a suitable lvalue initialiser for a
    reference to type t.  If so a suitably converted version of e is
    returned.  The null expression is returned otherwise.
*/

EXP
init_ref_lvalue(TYPE t, EXP e, ERROR *err)
{
	EXP a = NULL_exp;
	if (!IS_NULL_exp(e)) {
		TYPE s = DEREF_type(exp_type(e));
		CV_SPEC qual = DEREF_cv(type_qual(s));
		if (qual & cv_lvalue) {
			/* Check whether t is reference compatible with s */
			unsigned nt = TAG_type(t);
			unsigned ns = TAG_type(s);
			CV_SPEC cv = cv_compare(t, s);
			if (nt == ns) {
				if (nt == type_compound_tag) {
					/* Check for base class conversions */
					if (cv == cv_none || init_ref_force) {
						a = cast_class_class(t, e, err, CAST_IMPLICIT, 1);
					}
				} else if (nt == type_func_tag) {
					/* Allow for overloading */
					LIST(IDENTIFIER) pids =
					    NULL_list(IDENTIFIER);
					e = resolve_cast(t, e, err, 1, 0, pids);
					if (!IS_exp_member(e)) {
						s = DEREF_type(exp_type(e));
						if (eq_type_unqual(t, s)) {
							if (eq_except(t, s) != 2) {
								add_error(err, ERR_except_spec_init());
							}
							a = e;
						}
					}
				} else {
					/* Otherwise check for equal types */
					if (eq_type_unqual(t, s)) {
						a = e;
						if (cv != cv_none) {
							add_error(err, ERR_dcl_init_ref_qual(cv));
						}
					}
				}
			}
		}
		if (is_templ_type(s)) {
			/* Allow for template parameters */
			a = cast_templ_type(t, e, CAST_IMPLICIT);
		}
	}
	return a;
}


/*
    This routine checks whether e is a suitable rvalue initialiser for a
    reference to type t.  It is firstly checked that t is a const reference
    and not a reference to function.  If t is reference compatible with the
    type of s then a temporary is created to hold the value of e and the
    contents of this temporary are returned.  Otherwise the null expression
    is returned.
*/

static EXP
init_ref_rvalue(TYPE t, EXP e, ERROR *err)
{
	/* Check for reference to functions */
	CV_SPEC qual;
	unsigned nt = TAG_type(t);
	if (nt == type_func_tag) {
		add_error(err, ERR_dcl_init_ref_func());
		e = make_null_exp(t);
		return e;
	}

	/* Check for const references */
	qual = find_cv_qual(t);
	qual &= cv_qual;
	if (qual != cv_const) {
		int ok = 0;
		if (!IS_NULL_exp(e)) {
			TYPE s = DEREF_type(exp_type(e));
			if (IS_type_error(s)) {
				ok = 1;
			}
		}
		if (!ok) {
			add_error(err, ERR_dcl_init_ref_const());
		}
	}

	/* Check the initialiser */
	if (!IS_NULL_exp(e)) {
		/* Check whether t is reference compatible with s */
		int force = init_ref_force;
		TYPE s = DEREF_type(exp_type(e));
		unsigned ns = TAG_type(s);
		CV_SPEC cv = cv_compare(t, s);
		if (nt == ns && (cv == cv_none || force)) {
			TYPE r = t;
			if (nt == type_compound_tag) {
				/* t must be a base class of s */
				CLASS_TYPE ct =
				    DEREF_ctype(type_compound_defn(t));
				CLASS_TYPE cs =
				    DEREF_ctype(type_compound_defn(s));
				GRAPH gr = find_base_class(cs, ct, 1);
				if (IS_NULL_graph(gr)) {
					return NULL_exp;
				}
				r = qualify_type(s, qual, 0);
				/* NOT YET IMPLEMENTED: copy e */
			} else {
				/* Otherwise check for equal types */
				if (!eq_type_unqual(t, s)) {
					return NULL_exp;
				}
			}
			if (cv != cv_none) {
				/* Binding from more qualified type */
				add_error(err, ERR_dcl_init_ref_qual(cv));
			}
			e = make_temporary(r, e, NULL_exp, 1, err);
			if (nt == type_compound_tag) {
				/* Bind temporary to reference */
				e = cast_class_class(t, e, err, CAST_IMPLICIT, 1);
			}
			return e;
		}
	}
	return NULL_exp;
}


/*
    This routine creates a reference initialiser of type t out of the
    expression e.
*/

EXP
make_ref_init(TYPE t, EXP e)
{
	if (!IS_NULL_exp(e)) {
		if (IS_exp_op(e)) {
			/* Allow for template parameters */
			COPY_type(exp_type(e), t);
		} else {
			TYPE s = t;
			unsigned tag = TAG_type(s);
			if (tag == type_ref_tag) {
				s = DEREF_type(type_ref_sub(s));
				tag = TAG_type(s);
			}
			if (tag == type_token_tag && is_templ_type(s)) {
				/* Check again later */
				/* EMPTY */
			} else {
				MAKE_exp_address(t, e, e);
			}
		}
	}
	return e;
}


/*
    This routine creates a null expression (i.e. all zeros) for the type t.
    This is the default value for a non-explicitly initialised variable with
    internal or external linkage.
*/

EXP
make_null_exp(TYPE t)
{
	EXP e;
	switch (TAG_type(t)) {
	case type_integer_tag:
	case type_enumerate_tag: {
		NAT n = small_nat[0];
		MAKE_exp_int_lit(t, n, exp_int_lit_tag, e);
		break;
	}
	case type_floating_tag: {
		FLOAT f = get_float(t, 0);
		MAKE_exp_float_lit(t, f, e);
		break;
	}
	case type_bitfield_tag: {
		TYPE s = find_bitfield_type(t);
		e = make_null_exp(s);
		MAKE_exp_cast(t, (CONV_BITFIELD | CONV_REVERSE), e, e);
		break;
	}
	default:
		MAKE_exp_null(t, e);
		break;
	}
	return e;
}


/*
    This routine creates a unit expression (i.e. one) for the type t.
*/

EXP
make_unit_exp(TYPE t)
{
	EXP e;
	switch (TAG_type(t)) {
	case type_integer_tag:
	case type_enumerate_tag: {
		NAT n = small_nat[1];
		MAKE_exp_int_lit(t, n, exp_int_lit_tag, e);
		break;
	}
	case type_floating_tag: {
		FLOAT f = get_float(t, 1);
		MAKE_exp_float_lit(t, f, e);
		break;
	}
	case type_bitfield_tag: {
		TYPE s = find_bitfield_type(t);
		e = make_unit_exp(s);
		MAKE_exp_cast(t,(CONV_BITFIELD | CONV_REVERSE), e, e);
		break;
	}
	default:
		error(ERR_INTERNAL, "Invalid unit type");
		MAKE_exp_null(t, e);
		break;
	}
	return e;
}


/*
    This routine checks whether the expression e is a null expression.
*/

int
is_null_exp(EXP e)
{
	if (IS_NULL_exp(e)) {
		return 1;
	}
	switch (TAG_exp(e)) {
	case exp_int_lit_tag: {
		NAT n = DEREF_nat(exp_int_lit_nat(e));
		return is_zero_nat(n);
	}
	case exp_float_lit_tag: {
		FLOAT f = DEREF_flt(exp_float_lit_flt(e));
		return is_zero_float(f);
	}
	case exp_null_tag:
	case exp_zero_tag:
		return 1;
	case exp_aggregate_tag: {
		LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
		while (!IS_NULL_list(p)) {
			EXP a = DEREF_exp(HEAD_list(p));
			if (!is_null_exp(a)) {
				return 0;
			}
			p = TAIL_list(p);
		}
		return 1;
	}
	case exp_nof_tag: {
		EXP a = DEREF_exp(exp_nof_start(e));
		EXP b = DEREF_exp(exp_nof_pad(e));
		EXP c = DEREF_exp(exp_nof_end(e));
		if (!is_null_exp(a)) {
			return 0;
		}
		if (!is_null_exp(b)) {
			return 0;
		}
		return is_null_exp(c);
	}
	}
	return 0;
}


/*
    This routine creates an empty initialiser for the type t.  Basically
    this is the same as make_null_exp except that it also checks for
    uninitialised references and const objects.  Also if force is false
    then a value is only created if absolutely necessary.
*/

EXP
init_empty(TYPE t, CV_SPEC cv, int force, ERROR *err)
{
	EXP e = NULL_exp;
	switch (TAG_type(t)) {
	case type_array_tag: {
		NAT n = DEREF_nat(type_array_size(t));
		TYPE s = DEREF_type(type_array_sub(t));
		e = init_empty(s, cv, force, err);
		if (!IS_NULL_exp(e)) {
			MAKE_exp_nof(t, NULL_exp, n, e, NULL_exp, e);
		}
		break;
	}
	case type_ref_tag: {
		/* References must be initialised */
		TYPE s = DEREF_type(type_ref_sub(t));
		add_error(err, ERR_dcl_init_ref_none());
		if (IS_type_func(s)) {
			e = make_null_exp(s);
		} else {
			e = init_empty(s, cv_none, 1, err);
			e = make_temporary(s, e, NULL_exp, 1, err);
			e = make_ref_init(t, e);
		}
		break;
	}
	case type_compound_tag:
		/* Call default constructor for classes */
		e = init_default(t, &e, DEFAULT_CONSTR, EXTRA_CONSTR, err);
		if (IS_NULL_exp(e)) {
			goto default_lab;
		}
		break;
	case type_enumerate_tag:
		if (force) {
			/* Check for zero enumerator */
			ENUM_TYPE et = DEREF_etype(type_enumerate_defn(t));
			CLASS_INFO ei = DEREF_cinfo(etype_info(et));
			if (!(ei & cinfo_usr_constr)) {
				add_error(err, ERR_dcl_enum_zero(t));
			}
		}
		goto default_lab;
	case type_token_tag:
		if (is_templ_type(t)) {
			/* Allow for template parameters */
			if (force) {
				MAKE_exp_op(t, lex_cast, NULL_exp, NULL_exp, e);
			}
			break;
		}
		goto default_lab;
	default :
default_lab: {
		     CV_SPEC qual = find_cv_qual(t);
		     qual |= cv;
		     if (qual & cv_const) {
			     /* Const objects must be initialised */
			     add_error(err, ERR_dcl_init_const());
		     }
		     if (force) {
			     e = make_null_exp(t);
		     }
		     break;
	     }
	}
	return e;
}


/*
    This variable is used to hold the number of elements in the last array
    initialiser processed.  It is subsequently used to calculate the bound
    for an unbounded, but initialised, array type.
*/

static NAT last_array_size = NULL_nat;


/*
    This routine checks whether the type t is an array of 'char', 'signed
    char', 'unsigned char' 'wchar_t', and so may be initialised by a single
    literal.  It returns 1 for character arrays, 2 for wide character
    arrays, and 3 for types compatible with wide character arrays.
*/

static int
is_char_array(TYPE t)
{
	if (IS_type_array(t)) {
		TYPE s = DEREF_type(type_array_sub(t));
		if (check_int_type(s, btype_char)) {
			return 1;
		}
		if (check_int_type(s, btype_wchar_t)) {
			return 2;
		}
		if (!basetype_info[ntype_wchar_t].key) {
			s = type_composite(s, type_wchar_t, 1, 0, KILL_err, 0);
			if (!IS_NULL_type(s)) {
				return 3;
			}
		}
	}
	return 0;

}


/*
    This routine pads the array initialiser e, which contains m elements,
    with zeros until it matches the type t.  n gives the bound size of t.
*/

static EXP
pad_array(EXP e, NAT m, TYPE t, NAT n, int pad, ERROR *err)
{
	EXP a;
	int eq;
	unsigned long c;
	ERROR err2 = NULL_err;
	TYPE s = DEREF_type(type_array_sub(t));

	/* Check for equality */
	eq = compare_nat(n, m);
	if (eq == 0) {
		return e;
	} else if (eq == 1) {
		if (!pad) {
			return NULL_exp;
		}
	} else if (eq == -1) {
		/* Too many initialisers */
		if (!pad) {
			return NULL_exp;
		}
		add_error(err, ERR_dcl_init_aggr_excess(t));
		return e;
	} else {
		/* Allow for token definitions */
		force_tokdef++;
		eq = eq_nat(n, m);
		force_tokdef--;
		if (eq) {
			return e;
		}
		if (!pad) {
			return NULL_exp;
		}
	}

	/* Find number of uninitialised elements */
	c = get_nat_value(m);
	if (c != 0) {
		EXP en = calc_nat_value(n, type_size_t);
		EXP em = calc_nat_value(m, type_size_t);
		en = make_minus_exp(en, em);
		if (IS_exp_int_lit(en)) {
			n = DEREF_nat(exp_int_lit_nat(en));
			if (pad && c > 1 && is_calc_nat(n)) {
				/* Warn about potentially dubious
				 * initialisers */
				err2 = ERR_dcl_init_aggr_array_ti(m, t);
			}
			c = get_nat_value(n);
			if (c == 0) {
				return e;
			}
		}
	}

	/* Form initialiser */
	if (IS_NULL_err(err2)) {
		err2 = ERR_dcl_init_aggr_pad(n, t);
	}
	if (!IS_NULL_err(err2)) {
		add_error(err, err2);
	}
	a = init_empty(s, cv_none, 1, err);
	if (!IS_NULL_exp(e) && IS_exp_aggregate(e)) {
		if (c <= ARRAY_PADDING) {
			/* Explicitly pad small arrays */
			LIST(EXP)p = DEREF_list(exp_aggregate_args(e));
			LIST(EXP)q = NULL_list(EXP);
			while (c) {
				CONS_exp(a, q, q);
				c--;
			}
			p = APPEND_list(p, q);
			COPY_list(exp_aggregate_args(e), p);
			COPY_type(exp_type(e), t);
			return e;
		}
	}
	MAKE_exp_nof(t, e, n, a, NULL_exp, e);
	return e;
}


/*
    This routine checks the assignment style initialiser 't id = e ;' where
    t is an array type.  If arr is true then e is allowed to be another
    array expression of compatible type.  The routine returns the
    initialising expression for id.
*/

EXP
init_array(TYPE t, CV_SPEC cv, EXP e, int arr, ERROR *err)
{
	TYPE r = DEREF_type(exp_type(e));
	NAT n = DEREF_nat(type_array_size(t));
	TYPE s = DEREF_type(type_array_sub(t));
	if (IS_type_array(r)) {
		unsigned tag = TAG_exp(e);
		NAT m = DEREF_nat(type_array_size(r));
		TYPE u = DEREF_type(type_array_sub(r));
		if (IS_NULL_nat(n)) {
			n = m;
		}
		last_array_size = m;

		/* Check for templates */
		if (in_template_decl) {
			if (is_templ_type(s) || is_templ_type(u)) {
				e = cast_templ_type(t, e, CAST_IMPLICIT);
				return e;
			}
		}

		/* Initialisation by string literal */
		if (tag == exp_string_lit_tag) {
			unsigned long na, ma;
			int ca = is_char_array(t);
			STRING str = DEREF_str(exp_string_lit_str(e));
			unsigned kind = DEREF_unsigned(str_simple_kind(str));
			if (kind & STRING_WIDE) {
				/* Wide string literals */
				if (ca == 2) {
					u = s;
				} else if (ca == 3) {
					if (IS_type_enumerate(s)) {
						/* It could happen ... */
						EXP a;
						ENUM_TYPE es;
						MAKE_exp_value(u, a);
						a = cast_int_int(s, a, err, CAST_IMPLICIT, -1);
						es = DEREF_etype(type_enumerate_defn(s));
						s = DEREF_type(etype_rep(es));
						free_exp(a, 1);
					}
				} else {
					add_error(err,
						  ERR_dcl_init_string_wchar());
				}
			} else {
				/* Normal string literals */
				if (ca == 1) {
					u = s;
				} else {
					add_error(err,
						  ERR_dcl_init_string_char());
				}
			}
			if (!EQ_type(u, s)) {
				/* Deal with invalid cases */
				if (IS_type_integer(s)) {
					/* Cast string to appropriate type */
					MAKE_type_array(cv_none, s, m, r);
					MAKE_exp_string_lit(r, str, e);
				} else {
					/* Don't take any initialisers from the string */
					e = NULL_exp;
				}
			}

			/* Check array bound */
			na = get_nat_value(n);
			ma = get_nat_value(m);
			if (na != EXTENDED_MAX) {
				/* Known array bounds */
				if (ma > na) {
					/* Too many initialisers - trim string */
					if (ma == na + 1) {
						add_error(err, ERR_dcl_init_string_zero(t));
					} else {
						add_error(err, ERR_dcl_init_string_excess(t));
					}
					MAKE_exp_string_lit(t, str, e);
				} else if (ma < na) {
					/* Not enough initialisers */
					NAT d = make_nat_value(na - ma);
					add_error(err,
						  ERR_dcl_init_aggr_pad(d, t));
					MAKE_exp_string_lit(t, str, e);
				}
			} else {
				/* Unknown array bounds */
				e = pad_array(e, m, t, n, 1, err);
			}
			return e;
		}

		/* Check array initialisers */
		if (tag == exp_token_tag) {
			/* Allow rvalue array tokens */
			CV_SPEC qual = DEREF_cv(type_qual(r));
			if (!(qual & cv_lvalue)) {
				arr = 2;
			}
		}
		e = convert_reference(e, REF_ASSIGN);
		if (arr == 0) {
			/* Invalid array initialiser */
			report(crt_loc, ERR_dcl_init_aggr_array_bad());
			if (tag == exp_paren_tag) {
				/* Parenthesised initialiser */
				e = init_array(t, cv, e, arr, err);
				return e;
			}
			arr = 1;
		}
		if (eq_type_unqual(s, u)) {
			if (arr != 2) {
				EXP d;
				d = init_default(r, &e, DEFAULT_COPY,
						 EXTRA_CONSTR, err);
				if (IS_NULL_exp(d)) {
					MAKE_exp_contents(r, e, e);
				} else {
					MAKE_exp_preinc(r, e, d, lex_array, e);
				}
			}
			e = pad_array(e, m, t, n, arr - 1, err);
			if (!IS_NULL_exp(e)) {
				return e;
			}
		}
		add_error(err, ERR_basic_link_incompat(t, r));
	} else {
		/* Other array initialisations are not allowed */
		report(crt_loc, ERR_dcl_init_aggr_array_bad());
		last_array_size = NULL_nat;
	}
	e = init_empty(t, cv, 1, err);
	return e;
}


/*
    In C there is no distinction between conversion by initialisation and
    conversion by assignment.  This routine adds a suitable error message
    to err which says that the conversion cannot be done by initialisation.
*/

ERROR
init_error(ERROR err, int init)
{
	ERROR ferr;
#if LANGUAGE_CPP
	ferr = ERR_dcl_init_conv();
	UNUSED(init);
#else
	ferr = ERR_expr_ass_conv();
	if (init) {
		ferr = concat_error(ferr, ERR_dcl_init_assign());
	}
#endif
	err = concat_warning(err, ferr);
	return err;
}


/*
    This routine checks the assignment style initialiser 'cv t id = e ;'.
    It returns a suitably converted version of e.
*/

EXP
init_assign(TYPE t, CV_SPEC cv, EXP e, ERROR *err)
{
    switch (TAG_type(t)) {
	case type_array_tag: {
	    /* Array initialisers */
	    e = init_array(t, cv, e, 0, err);
	    break;
	}
	case type_ref_tag: {
	    /* Reference initialisers */
	    EXP a;
	    TYPE s = DEREF_type(type_ref_sub(t));
	    TYPE r = DEREF_type(exp_type(e));
	    if (IS_type_compound(r)) {
		if (IS_type_compound(s)) {
		    /* Check base class conversions first */
		    a = init_ref_lvalue(s, e, err);
		    if (!IS_NULL_exp(a)) {
			e = make_ref_init(t, a);
			break;
		    }
		}
		a = convert_conv_aux(t, e, err, CAST_IMPLICIT);
		if (!IS_NULL_exp(a)) {
		    e = a;
		    r = DEREF_type(exp_type(e));
		    if (eq_type(r, t)) {
			    break;
		    }
		    e = convert_reference(e, REF_ASSIGN);
		}
	    }
	    a = init_ref_lvalue(s, e, err);
	    if (IS_NULL_exp(a)) {
		a = init_ref_rvalue(s, e, err);
		if (IS_NULL_exp(a)) {
		    e = init_assign(s, cv_none, e, err);
		    if (!IS_exp_null(e)) {
			e = make_temporary(s, e, NULL_exp, 1, err);
		    }
		} else {
		    e = a;
		}
	    } else {
		e = a;
	    }
	    e = make_ref_init(t, e);
	    break;
	}
	case type_compound_tag: {
	    /* Class initialisers */
	    TYPE s = DEREF_type(exp_type(e));
	    if (IS_type_compound(s)) {
		/* Check for base class initialisers */
		CLASS_TYPE cs = DEREF_ctype(type_compound_defn(s));
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		GRAPH gr = find_base_class(cs, ct, 1);
		if (!IS_NULL_graph(gr)) {
		    e = init_direct(t, e, err);
		    break;
		}
	    }
	    e = convert_conv(t, e, err, CAST_IMPLICIT);
	    if (!IS_exp_null(e)) {
		e = make_temporary(t, e, NULL_exp, 0, err);
		e = init_direct(t, e, err);
		e = remove_temporary(e, NULL_exp);
	    }
	    break;
	}
	default:
		/* Do conversion by initialisation */
		e = convert_assign(t, e, err);
		break;
    }
    return e;
}


/*
    This routine checks the constructor style initialiser 't id ( args ) ;'.
    It returns an expression representing the result of converting args to
    type t.
*/

EXP
init_constr(TYPE t, LIST(EXP)args, ERROR *err)
{
	EXP e;
	unsigned tag = TAG_type(t);
	switch (tag) {
	case type_ref_tag: {
		/* Reference initialisers */
		EXP a;
		TYPE s = DEREF_type(type_ref_sub(t));
		if (LENGTH_list(args) == 1) {
			a = DEREF_exp(HEAD_list(args));
			a = init_ref_lvalue(s, a, err);
		} else {
			a = NULL_exp;
		}
		if (IS_NULL_exp(a)) {
			a = init_ref_rvalue(s, a, err);
			if (IS_NULL_exp(a)) {
				e = init_constr(s, args, err);
				if (!IS_exp_null(e)) {
					e = make_temporary(s, e, NULL_exp, 1,
							   err);
				}
			} else {
				e = a;
			}
		} else {
			e = a;
		}
		e = make_ref_init(t, e);
		break;
	}
	case type_compound_tag: {
		/* Class constructor initialisers */
		e = convert_constr(t, args, err, CAST_STATIC);
		e = remove_temporary(e, NULL_exp);
		break;
	}
	case type_token_tag: {
		/* Check for template parameters */
		if (is_templ_type(t)) {
			LIST(OFFSET) offs = NULL_list(OFFSET);
			MAKE_exp_initialiser(t, args, offs, 0, 0, 0, e);
			e = cast_templ_type(t, e, CAST_IMPLICIT);
			break;
		}
		goto default_lab;
	}
	default:
default_lab: {
		/* Should have at most one argument otherwise */
		unsigned nargs = LENGTH_list(args);
		if (nargs == 0) {
			e = init_empty(t, cv_none, 1, err);
		} else {
			EXP a = DEREF_exp(HEAD_list(args));
			DESTROY_list(args, SIZE_exp);
			if (nargs > 1) {
				/* Can't have more than one initialiser */
				add_error(err, ERR_dcl_init_ctor(t));
			}
			if (tag == type_array_tag) {
				e = init_array(t, cv_none, a, 0, err);
			} else {
				TYPE s = DEREF_type(exp_type(a));
				if (IS_type_compound(s)) {
					e = convert_conv(t, a, err,
							 CAST_STATIC);
				} else {
					e = convert_assign(t, a, err);
				}
			}
		}
		break;
	     }
	}
	return e;
}


/*
    This routine checks the direct initialiser 't id ( a ) ;'.  It is
    a special case of init_constr in which there is only one initialiser.
*/

EXP
init_direct(TYPE t, EXP a, ERROR *err)
{
	LIST(EXP) args;
	CONS_exp(a, NULL_list(EXP), args);
	a = init_constr(t, args, err);
	return a;
}


/*
    This buffer is used to build up field names for use in error reporting.
*/

BUFFER field_buff = NULL_buff;


/*
    Because aggregate initialisers may be spread over several lines each
    component is embedded in a location expression.  This routine gets
    the first element of the aggregate list p, setting the current location
    as appropriate.  It returns the tag of e (ignoring parentheses) via
    ptag.
*/

static EXP
get_aggr_elem(LIST(EXP) p, unsigned *ptag)
{
	EXP a = DEREF_exp(HEAD_list(p));
	if (!IS_NULL_exp(a)) {
		if (IS_exp_location(a)) {
			TYPE t;
			DESTROY_exp_location(destroy, t, crt_loc, a, a);
			UNUSED(t);
			COPY_exp(HEAD_list(p), a);
		}
		if (!IS_NULL_exp(a)) {
			EXP b = a;
			unsigned tag = TAG_exp(b);
			while (tag == exp_paren_tag) {
				b = DEREF_exp(exp_paren_arg(b));
				tag = TAG_exp(b);
			}
			*ptag = tag;
		}
	}
	return a;
}


/*
    This routine checks the aggregate initialiser expression list pointed
    to by r against the type t.  The argument start is 1 to indicate the
    presence of a open brace immediately preceding r and 2 to indicate
    the top-level aggregate.  The result is a structured aggregate
    initialiser expression for compound types t or a suitably converted
    initialiser expression.
*/

static EXP
init_aggr_aux(TYPE t, CV_SPEC cv, LIST(EXP) *r, int start, IDENTIFIER id,
	      ERROR *err)
{
	EXP e;
	LIST(EXP) p = *r;
	ERROR cerr = NULL_err;
	CLASS_INFO ci = cinfo_none;
	unsigned tag = TAG_type(t);
	switch (tag) {
	case type_array_tag: {
		/* Array types */
		NAT nc;
		LIST(EXP) a = NULL_list(EXP);
		TYPE s = DEREF_type(type_array_sub(t));
		int str = is_char_array(s);
		BUFFER *bf = &field_buff;
		unsigned boff = (unsigned)(bf->posn - bf->start);

		/* Find the array size */
		NAT n = DEREF_nat(type_array_size(t));
		unsigned long m = get_nat_value(n);
		unsigned long c = 0;

		/* Report partially bracketed initialisers */
		if (!start) {
			add_error(err, ERR_dcl_init_aggr_partial());
		}

		/* Check for string literals in braces */
		if (start && !IS_NULL_list(p)) {
			unsigned et = null_tag;
			e = get_aggr_elem(p, &et);
			if (et == exp_string_lit_tag && is_char_array(t)) {
				e = init_array(t, cv, e, 0, err);
				p = TAIL_list(p);
				break;
			}
		}

		/* Loop through at most m initialisers */
		while (!IS_NULL_list(p) && c != m) {
			LIST(EXP) p0 = p;
			ERROR serr = NULL_err;
			unsigned et = null_tag;

			/* Build up the field name */
			bfprintf(bf, " [%lu]", c);

			/* Check first element of aggregate */
			e = get_aggr_elem(p, &et);
			if (IS_NULL_exp(e)) {
				/* Can occur in template initialisers */
				e = init_empty(s, cv_none, 1, &serr);
				COPY_exp(HEAD_list(p), e);
			}
			if (et == exp_string_lit_tag && str) {
				/* Check for string literals */
				e = init_array(s, cv, e, 0, &serr);
				p = TAIL_list(p);
			} else if (et == exp_aggregate_tag && start) {
				/* Check for sub-aggregates */
				LIST(EXP) q;
				q = DEREF_list(exp_aggregate_args(e));
				e = init_aggr_aux(s, cv, &q, 1, id, &serr);
				p = TAIL_list(p);
			} else {
				/* Otherwise read constituents from p */
				e = init_aggr_aux(s, cv, &p, 0, id, &serr);
			}

			/* Report any errors for this member */
			if (!IS_NULL_err(serr)) {
				ERROR ferr = ERR_dcl_init_decl(id, bf->start);
				serr = concat_error(ferr, serr);
				report(crt_loc, serr);
			}

			/* Check for dynamic initialisers */
			e = dynamic_init(id, bf->start, e);

			/* Restore the field name */
			bf->posn = bf->start + boff;
			bf->posn[0] = 0;

			/* Check that some initialisers were used up */
			if (EQ_list(p, p0)) {
				break;
			}

			/* Build up the result (in reverse order) */
			CONS_exp(e, a, a);
			c++;
		}

		/* Construct the result */
		a = REVERSE_list(a);
		nc = make_nat_value(c);
		MAKE_type_array(cv_none, s, nc, s);
		MAKE_exp_aggregate(s, a, NULL_list(OFFSET), e);

		/* Check array size */
		if (!IS_NULL_nat(n)) {
			e = pad_array(e, nc, t, n, 1, err);
		}
		last_array_size = nc;
		break;
	}
	case type_ref_tag: {
		/* Reference types */
		TYPE s = DEREF_type(type_ref_sub(t));
		e = init_ref_rvalue(s, NULL_exp, err);
		if (IS_NULL_exp(e)) {
			e = init_aggr_aux(s, cv, r, start, id, err);
			e = make_temporary(s, e, NULL_exp, 1, err);
			e = make_ref_init(t, e);
		}
		return e;
	}
	case type_compound_tag: {
		/* Compound types */
		MEMBER mem;
		NAMESPACE ns;
		unsigned long pads = 0;
		LIST(EXP) a = NULL_list(EXP);
		LIST(OFFSET)b = NULL_list(OFFSET);
		CV_SPEC cv1 = (DEREF_cv(type_qual(t)) | cv);
		CLASS_TYPE ct = DEREF_ctype(type_compound_defn(t));
		GRAPH gr = DEREF_graph(ctype_base(ct));
		LIST(GRAPH) br = DEREF_list(graph_tails(gr));
		BUFFER *bf = &field_buff;
		unsigned boff = (unsigned)(bf->posn - bf->start);

		/* Check for non-aggregate classes */
		ci = DEREF_cinfo(ctype_info(ct));
		if (!(ci & cinfo_defined)) {
			/* Instantiate template types if necessary */
			complete_class(ct, 1);
			ci = DEREF_cinfo(ctype_info(ct));
		}
		if (!(ci & cinfo_complete)) {
			/* Incomplete types can't be initialised */
			goto incomplete_lab;
		}
		if (ci & cinfo_non_aggregate) {
			/* Types with these properties can't be initialised */
			cerr = class_info(ct, cinfo_non_aggregate, 1);
			if (ci & cinfo_token) {
				goto token_lab;
			}
			if (ci & cinfo_usr_constr) {
				goto non_aggregate_lab;
			}
			add_error(err, cerr);
			add_error(err, ERR_dcl_init_aggr_type(t));
			cerr = NULL_err;
		}

		/* Check for non-aggregate initialisations */
		if (!IS_NULL_list(p)) {
			unsigned rank;
			CONVERSION conv;
			unsigned et = null_tag;
			e = get_aggr_elem(p, &et);
			conv.from = DEREF_type(exp_type(e));
			conv.to = t;
			rank = std_convert_seq(&conv, e, 0, 0);
			if (rank != CONV_NONE) {
				goto non_aggregate_lab;
			}
		}

		/* Report partially bracketed initialisers */
		if (!start) {
			add_error(err, ERR_dcl_init_aggr_partial());
		}

		/* Loop through base classes */
		while (!IS_NULL_list(br)) {
			ERROR serr = NULL_err;
			GRAPH gs = DEREF_graph(HEAD_list(br));
			OFFSET off = DEREF_off(graph_off(gs));
			CLASS_TYPE cs = DEREF_ctype(graph_head(gs));
			TYPE s = make_class_type(cs);

			/* Build up field name */
			IDENTIFIER sid = DEREF_id(ctype_name(cs));
			HASHID snm = DEREF_hashid(id_name(sid));
			if (!IS_hashid_anon(snm)) {
				bfputc(bf, '.');
				IGNORE print_hashid(snm, 1, 0, bf, 0);
			}

			/* Check next initialiser */
			if (!IS_NULL_list(p)) {
				unsigned et = null_tag;
				e = get_aggr_elem(p, &et);
				if (et == exp_aggregate_tag && start) {
					/* Check for sub-aggregates */
					LIST(EXP) q;
					q = DEREF_list(exp_aggregate_args(e));
					e = init_aggr_aux(s, cv1, &q, 1, id,
							  &serr);
					p = TAIL_list(p);
				} else {
					/* Otherwise read constituents from p */
					e = init_aggr_aux(s, cv1, &p, 0, id,
							  &serr);
				}
			} else {
				e = init_empty(s, cv1, 1, &serr);
				pads++;
			}

			/* Report any errors for this field */
			if (!IS_NULL_err(serr)) {
				ERROR ferr = ERR_dcl_init_decl(id, bf->start);
				serr = concat_error(ferr, serr);
				report(crt_loc, serr);
			}

			/* Check for dynamic initialisers */
			e = dynamic_init(id, bf->start, e);

			/* Restore field name */
			bf->posn = bf->start + boff;
			bf->posn[0] = 0;

			/* Build up the result (in reverse order) */
			CONS_exp(e, a, a);
			CONS_off(off, b, b);
			br = TAIL_list(br);
		}

		/* Find list of class members */
		ns = DEREF_nspace(ctype_member(ct));
		mem = DEREF_member(nspace_ctype_first(ns));
		mem = next_data_member(mem, 0);

		/* Loop through structure members */
		while (!IS_NULL_member(mem)) {
			ERROR serr = NULL_err;
			CV_SPEC cv2 = cv1;
			IDENTIFIER sid = DEREF_id(member_id(mem));
			TYPE s = DEREF_type(id_member_type(sid));
			DECL_SPEC ds = DEREF_dspec(id_storage(sid));
			OFFSET off = DEREF_off(id_member_off(sid));

			/* Build up field name */
			HASHID snm = DEREF_hashid(id_name(sid));
			if (!IS_hashid_anon(snm)) {
				bfputc(bf, '.');
				IGNORE print_hashid(snm, 1, 0, bf, 0);
			}

			/* Adjust cv-qualifiers */
			if (ds & dspec_mutable)cv2 = cv_none;

			/* Check next initialiser */
			if (!IS_NULL_list(p)) {
				unsigned et = null_tag;
				e = get_aggr_elem(p, &et);
				if (et == exp_string_lit_tag &&
				    is_char_array(s)) {
					/* Check for string literals */
					e = init_array(s, cv2, e, 0, &serr);
					p = TAIL_list(p);
				} else if (et == exp_aggregate_tag && start) {
					/* Check for sub-aggregates */
					LIST(EXP) q;
					q = DEREF_list(exp_aggregate_args(e));
					e = init_aggr_aux(s, cv2, &q, 1, id,
							  &serr);
					p = TAIL_list(p);
				} else {
					/* Otherwise read constituents from p */
					e = init_aggr_aux(s, cv2, &p, 0, id,
							  &serr);
				}
			} else {
				/* Pad rest of structure */
				e = init_empty(s, cv2, 1, &serr);
				pads++;
			}

			/* Report any errors for this field */
			if (!IS_NULL_err(serr)) {
				ERROR ferr = ERR_dcl_init_decl(id, bf->start);
				serr = concat_error(ferr, serr);
				report(crt_loc, serr);
			}

			/* Check for dynamic initialisers */
			e = dynamic_init(id, bf->start, e);

			/* Restore field name */
			bf->posn = bf->start + boff;
			bf->posn[0] = 0;

			/* Build up the result (in reverse order) */
			CONS_exp(e, a, a);
			CONS_off(off, b, b);

			/* Examine next member */
			if (ci & cinfo_union) {
				break;
			}
			mem = DEREF_member(member_next(mem));
			mem = next_data_member(mem, 0);
		}

		/* Report padded structures */
		if (pads) {
			NAT n = make_nat_value(pads);
			add_error(err, ERR_dcl_init_aggr_pad(n, t));
		}

		/* Construct the result */
		a = REVERSE_list(a);
		b = REVERSE_list(b);
		MAKE_exp_aggregate(t, a, b, e);
		break;
	}
	case type_integer_tag:
	case type_floating_tag:
	case type_enumerate_tag:
	case type_ptr_tag:
	case type_ptr_mem_tag: {
		/* Scalar types */
		if (IS_NULL_list(p)) {
			/* Can't have empty initialiser */
			add_error(err, ERR_dcl_init_aggr_no_scalar());
			e = init_empty(t, cv, 1, err);
		} else {
			/* The first element must be a scalar */
			unsigned et = null_tag;
			e = get_aggr_elem(p, &et);
			if (et == exp_aggregate_tag) {
				LIST(EXP)q;
				q = DEREF_list(exp_aggregate_args(e));
				e = init_aggr_aux(t, cv, &q, 1, id, err);
			} else {
				ERROR ferr = NULL_err;
				if (start == 1) {
					/* Can only have aggregate at top
					 * level */
					ferr = ERR_dcl_init_aggr_nest();
				}
				e = convert_reference(e, REF_ASSIGN);
				e = init_assign(t, cv, e, &ferr);
				if (!IS_NULL_err(ferr)) {
					ferr = init_error(ferr, 1);
					add_error(err, ferr);
				}
			}
			p = TAIL_list(p);
		}
		break;
	}
	case type_token_tag:
token_lab: {
		   /* Tokenised types */
		   TYPE s = expand_type(t, 0);
		   if (EQ_type(s, t)) {
			   goto non_aggregate_lab;
		   }
		   e = init_aggr_aux(s, cv, r, start, id, err);
		   return e;
	   }
	case type_top_tag:
	case type_bottom_tag:
incomplete_lab:
	   /* Incomplete types */
	   add_error(err, ERR_basic_types_incompl(t));
	   add_error(err, ERR_dcl_init_incompl());
	   e = init_empty(t, cv, 1, err);
	   break;
	default:
non_aggregate_lab:
	   /* Other types */
	   if (start) {
		   /* Can't have aggregate initialisers */
		   ERROR ferr = ERR_dcl_init_decl(id, NULL_string);
		   ferr = concat_error(ferr, cerr);
		   ferr = concat_error(ferr, ERR_dcl_init_aggr_type(t));
		   report(crt_loc, ferr);
		   if (ci & cinfo_usr_constr) {
			   /* Map to constructor call */
			   LIST(EXP) q = p;
			   while (!IS_NULL_list(q)) {
				   unsigned et = null_tag;
				   IGNORE get_aggr_elem(q, &et);
				   q = TAIL_list(q);
			   }
			   e = init_constr(t, p, err);
			   return e;
		   }
	   } else {
		   if (!IS_NULL_err(cerr)) {
			   destroy_error(cerr, 1);
		   }
	   }
	   if (IS_NULL_list(p)) {
		   /* Empty initialiser list */
		   e = init_empty(t, cv, 1, err);
	   } else {
		   /* Get next initialiser from list */
		   unsigned et = null_tag;
		   e = get_aggr_elem(p, &et);
		   if (et == exp_aggregate_tag) {
			   LIST(EXP) q;
			   q = DEREF_list(exp_aggregate_args(e));
			   e = init_aggr_aux(t, cv, &q, 1, id, err);
		   } else {
			   e = convert_reference(e, REF_ASSIGN);
			   if (tag == type_token_tag && is_zero_exp(e)) {
				   /* Special concession to tokenised types */
				   e = init_empty(t, cv, 1, err);
			   } else {
				   ERROR ferr = NULL_err;
				   e = init_assign(t, cv, e, &ferr);
				   if (!IS_NULL_err(ferr)) {
					   ferr = init_error(ferr, 1);
					   add_error(err, ferr);
				   }
			   }
		   }
		   p = TAIL_list(p);
	   }
	   break;
	}

	/* Check for end of initialiser list */
	if (start && !IS_NULL_list(p)) {
		ERROR ferr = ERR_dcl_init_decl(id, NULL_string);
		ferr = concat_error(ferr, ERR_dcl_init_aggr_excess(t));
		report(crt_loc, ferr);
		p = NULL_list(EXP);
	}
	*r = p;
	return e;
}


/*
    This is the top-level routine for analysing the aggregate initialiser
    e for the object id of type t.  Any errors are added to err.
*/

EXP
init_aggregate(TYPE t, EXP e, IDENTIFIER id, ERROR *err)
{
	LOCATION loc;
	LIST(EXP) args = DEREF_list(exp_aggregate_args(e));
	if (IS_NULL_list(args)) {
		/* Report empty aggregate initialisers */
		add_error(err, ERR_dcl_init_aggr_empty());
	}
	bad_crt_loc++;
	loc = crt_loc;
	IGNORE clear_buffer(&field_buff, NIL(FILE));
	e = init_aggr_aux(t, cv_none, &args, 2, id, err);
	crt_loc = loc;
	bad_crt_loc--;
	return e;
}


/*
    This routine calls init_assign, init_constr or init_aggregate depending
    on the value of e.  If tentative is true then an absent initialiser
    (i.e. when e is null) is treated as a tentative definition.
*/

EXP
init_general(TYPE t, EXP e, IDENTIFIER id, int tentative)
{
	/* Check the initialiser */
	ERROR err = NULL_err;
	if (IS_NULL_exp(e)) {
		/* Empty initialisers */
		DECL_SPEC ds = DEREF_dspec(id_storage(id));
		if (ds & dspec_auto) {
			e = init_empty(t, cv_none, 0, &err);
		} else if (tentative) {
			MAKE_exp_zero(t, e);
		} else {
			e = init_empty(t, cv_none, 1, &err);
		}
	} else {
		switch (TAG_exp(e)) {
		case exp_aggregate_tag: {
			/* Aggregate initialisers */
			if (is_templ_type(t)) {
				e = cast_templ_type(t, e, CAST_IMPLICIT);
			} else {
				e = init_aggregate(t, e, id, &err);
			}
			break;
		}
		case exp_nof_tag: {
			/* Padded aggregate initialisers */
			e = DEREF_exp(exp_nof_start(e));
			e = init_general(t, e, id, 0);
			return e;
		}
		case exp_initialiser_tag: {
			/* Function style initialisers */
			LIST(EXP)args;
			args = DEREF_list(exp_initialiser_args(e));
			args = convert_args(args);
			e = init_constr(t, args, &err);
			if (!IS_NULL_err(err)) {
				err = init_error(err, 1);
			}
			break;
		}
		default: {
			/* Simple initialisers */
			unsigned etag = TAG_exp(e);
			e = convert_reference(e, REF_ASSIGN);
			if (etag == exp_paren_tag && IS_type_array(t)) {
				e = make_paren_exp(e);
			}
			e = init_assign(t, cv_none, e, &err);
			if (!IS_NULL_err(err)) {
				err = init_error(err, 1);
			}
			break;
		}
		}
	}

	/* Report any errors */
	if (!IS_NULL_err(err)) {
		ERROR ferr = ERR_dcl_init_decl(id, NULL_string);
		err = concat_error(ferr, err);
		report(crt_loc, err);
	}

	/* Check for dynamic initialisers */
	if (!IS_NULL_exp(e)) {
		e = dynamic_init(id, NULL_string, e);
	}
	return e;
}


/*
    This routine creates a destructor for the object id of type t,
    reporting any errors.
*/

EXP
destroy_general(TYPE t, IDENTIFIER id)
{
	EXP d = NULL_exp;
	int du = do_usage;
	ERROR err = NULL_err;
	do_usage = 0;
	d = init_default(t, &d, DEFAULT_DESTR, EXTRA_DESTR, &err);
	if (!IS_NULL_err(err)) {
		/* Report any destructor errors */
		ERROR ferr = ERR_dcl_init_decl(id, NULL_string);
		err = concat_error(ferr, err);
		report(decl_loc, err);
	}
	do_usage = du;
	return d;
}


/*
    This routine initialises the object given by id to the value e.  Note
    that e can be the null expression, indicating that no initialiser is
    given.  The routine 1 if the object is defined, 2 if it is tentatively
    defined, and 0 if it is just declared (see dump_declare).
*/

int
init_object(IDENTIFIER id, EXP e)
{
	EXP d;
	TYPE t;
	int def = 0;
	unsigned tag;
	DECL_SPEC ds;
	unsigned itag;
	int ignore = 0;

	/* Check for non-object declarations */
	if (IS_NULL_id(id)) {
		return 0;
	}
	itag = TAG_id(id);
	switch (itag) {
	case id_variable_tag:
	case id_stat_member_tag:
		/* Variables and static data members */
		break;
	case id_parameter_tag:
		/* Function parameters */
		if (!in_default_arg) {
			if (!IS_NULL_exp(e)) {
				report(crt_loc, ERR_dcl_fct_default_weak(id));
			}
			return 0;
		}
		break;
	case id_function_tag:
	case id_mem_func_tag:
	case id_stat_mem_func_tag:
		/* Check for function declarations */
		if (!IS_NULL_exp(e)) {
			/* Can't initialise functions */
			report(crt_loc, ERR_dcl_init_func(id));
		}

		/* Check previous definition */
		d = DEREF_exp(id_function_etc_defn(id));
		if (!IS_NULL_exp(d)) {
			ds = DEREF_dspec(id_storage(id));
			ds |= dspec_defn;
			COPY_dspec(id_storage(id), ds);
		}
		return 0;
	case id_member_tag:
		/* Check for non-static members (shouldn't be reached) */
		report(crt_loc, ERR_class_mem_init_mem(id));
		return 0;
	default:
		/* The declaration could have been a typedef */
		if (!IS_NULL_exp(e)) {
			/* Can't initialise a typedef */
			report(crt_loc, ERR_dcl_init_typedef(id));
		}
		return 1;
	}

	/* Get declaration data */
	t = DEREF_type(id_variable_etc_type(id));
	tag = TAG_type(t);
	ds = DEREF_dspec(id_storage(id));
	temp_storage = (ds & dspec_storage);

	/* Check array initialisers */
	if (tag == type_array_tag) {
		int chk = 0;
		if (!IS_NULL_exp(e)) {
			/* Initialisation of array types */
			NAT n = DEREF_nat(type_array_size(t));
			if ((ds & dspec_auto) && itag == id_variable_tag) {
				/* Local aggregate initialiser */
				report(crt_loc, ERR_dcl_init_aggr_auto(id));
			}
			last_array_size = NULL_nat;
			e = init_general(t, e, id, 0);
			if (IS_NULL_nat(n)) {
				/* Complete unbounded arrays */
				n = last_array_size;
				if (!IS_NULL_nat(n)) {
					CV_SPEC qual = DEREF_cv(type_qual(t));
					TYPE s = DEREF_type(type_array_sub(t));
					n = check_array_dim(n);
					MAKE_type_array(qual, s, n, t);
					COPY_type(id_variable_etc_type(id), t);
				}
			}
			ds |= dspec_defn;
			chk = 1;
		} else {
			/* Allow for tentative definitions */
			if (ds & dspec_defn) {
				chk = LANGUAGE_CPP;
			}
		}

		/* Can only spot incomplete arrays at this stage */
		if (chk) {
			ERROR err = check_complete(t);
			if (!IS_NULL_err(err)) {
				ERROR err2 = ERR_basic_types_def_incompl(id);
				err = concat_error(err, err2);
				report(decl_loc, err);
			}
		}
	} else {
		/* Other initialisers */
		if (!IS_NULL_exp(e)) {
			if (tag == type_compound_tag) {
				if ((ds & dspec_auto) &&
				    itag == id_variable_tag) {
					/* Local aggregate initialiser */
					report(crt_loc,
					       ERR_dcl_init_aggr_auto(id));
				}
			}
			if (ds & dspec_defn) {
				/* Type already check for completeness */
				/* EMPTY */
			} else if (tag == type_ref_tag) {
				/* Reference types don't need checking */
				/* EMPTY */
			} else {
				/* Type not yet checked for completeness */
				ERROR err = check_complete(t);
				if (!IS_NULL_err(err)) {
					ERROR err2 =
					    ERR_basic_types_def_incompl(id);
					err = concat_error(err, err2);
					report(decl_loc, err);
				}
				ds |= dspec_defn;
			}

			/* Examine initialiser */
			e = init_general(t, e, id, 0);
		}
	}

	/* Check on definition */
	if (ds & dspec_stat_inline) {
		/* Check for definitions of inline static members */
		if (ds & dspec_defn) {
			if (!IS_NULL_exp(e)) {
				/* Can't give a value in the definition */
				PTR(LOCATION) loc = id_loc(id);
				report(decl_loc,
				       ERR_class_static_data_def(id, loc));
			} else {
				/* Force definition to existing value */
				e = DEREF_exp(id_variable_etc_init(id));
			}
			/* Mark as defined and no longer inline */
			ds &= ~dspec_stat_inline;
		}
	} else {
		/* Provide default definition if necessary */
		if (ds & dspec_defn) {
			def = 1;
			if (IS_NULL_exp(e)) {
				e = init_general(t, e, id, LANGUAGE_C);
				if (!IS_NULL_exp(e) && IS_exp_zero(e)) {
					def = 2;
				}
			}
		}

		/* Check previous definition */
		d = DEREF_exp(id_variable_etc_init(id));
		if (!IS_NULL_exp(d)) {
			if (!IS_NULL_exp(e)) {
				/* Defined twice */
				ERROR err;
				PTR(LOCATION) loc = id_loc(id);
				if (def == 2) {
					/* This definition is tentative */
					err = ERR_basic_odr_tentative(id, loc);
					ignore = 1;
				} else if (IS_exp_zero(d)) {
					/* Previous definition was tentative */
					err = ERR_basic_odr_tentative(id, loc);
				} else {
					/* Neither definition is tentative */
					err = ERR_basic_odr_def(id, loc);
				}
				report(decl_loc, err);
			}
			ds |= dspec_defn;
		}
	}

	/* Update declaration data */
	COPY_type(id_variable_etc_type(id), t);
	COPY_dspec(id_storage(id), ds);
	if (!IS_NULL_exp(e)) {
		/* Define object */
		if (!ignore) {
			if ((ds & dspec_auto) && (ds & dspec_used)) {
				/* Local variable initialised in terms of
				 * itself */
				TYPE s = DEREF_type(exp_type(e));
				MAKE_exp_dynamic(s, e, e);
			}
			if (itag != id_parameter_tag) {
				e = check_init(e);
			}
			COPY_exp(id_variable_etc_init(id), e);
			COPY_loc(id_loc(id), decl_loc);
			define_id(id);
		}
		if (ds & dspec_linkage) {
			/* Check enclosing namespace */
			NAMESPACE ns = DEREF_nspace(id_parent(id));
			check_decl_nspace(id, ns, 1, crt_namespace);
		}
		if (def == 0) {
			def = 1;
		}
	}
	if (def) {
		/* Create destructor */
		EXP d1 = DEREF_exp(id_variable_etc_term(id));
		d = destroy_general(t, id);
		if (!IS_NULL_exp(d1) && IS_exp_paren(d1)) {
			/* Preserve parenthesised type information */
			TYPE t1 = DEREF_type(exp_type(d1));
			MAKE_exp_paren(t1, d, d);
		}
		COPY_exp(id_variable_etc_term(id), d);
	}
	if (!IS_NULL_id(unify_id_pending)) {
		/* Deal with any pending identifiers */
		IGNORE unify_id(unify_id_pending, id, 1);
	}
	temp_storage = dspec_auto;
	if (def && !(ds & dspec_auto)) {
		if (!really_in_function_defn && !in_template_decl) {
			/* Compile variable definition */
			compile_variable(id, 0);
		}
	}
	return def;
}


/*
    This routine initialises the function parameter id with the expression
    e (i.e. sets up a default argument value).  Note that the class
    definition case, where e is initially just skipped over, is dealt
    with here.
*/

void
init_param(IDENTIFIER id, EXP e)
{
	if (!IS_NULL_exp(e)) {
		if (!IS_NULL_id(id)) {
			if (IS_id_token(id)) {
				/* Template parameter */
				init_exp_param(id, e);
			} else {
				/* Function parameter */
				if (IS_exp_uncompiled(e)) {
					if (in_class_defn) {
						LIST(IDENTIFIER) ft;
						CLASS_TYPE ct = crt_class;
						ft = DEREF_list(ctype_nest(ct));
						CONS_id(id, ft, ft);
						COPY_list(ctype_nest(ct), ft);
					}
					COPY_exp(id_parameter_init(id), e);
				} else {
					in_default_arg++;
					IGNORE init_object(id, e);
					in_default_arg--;
				}
			}
		}
	}
	return;
}


/*
    This routine initialises the class member id with the expression e
    (which since it is a constant-expression has already undergone the
    appropriate operand conversions).  Note that the pure specifier is
    indistinguishible syntactically from a member initialiser, and so is
    only spotted at this stage.  See above for inline definitions of static
    data members.  The routine returns 1 for a definition and 0 for a
    declaration (see dump_declare).
*/

int
init_member(IDENTIFIER id, EXP e)
{
	int def;
	unsigned tag;

	/* Check for definitions */
	if (IS_NULL_id(id)) {
		return 0;
	}
	tag = TAG_id(id);
	if (have_access_decl) {
		def = 2;
		have_access_decl = 0;
	} else {
		switch (tag) {
		case id_stat_member_tag:
		case id_mem_func_tag:
		case id_stat_mem_func_tag:
			def = 0;
			break;
		default:
			def = 1;
			break;
		}
	}

	/* Check for function declarations */
	if (IS_NULL_exp(e)) {
		if (tag == id_mem_func_tag || tag == id_stat_mem_func_tag) {
			if (really_in_function_defn) {
				NAMESPACE ns = DEREF_nspace(id_parent(id));
				if (EQ_nspace(ns, crt_namespace)) {
					DECL_SPEC ds, mds;
					ds = DEREF_dspec(id_storage(id));
					mds = (dspec_inherit | dspec_implicit |
					       dspec_defn);
					if (!(ds & mds)) {
						/* Local functions should be
						 * defined */
						report(decl_loc, ERR_class_local_func(id));
					}
				}
			}
		}
		return def;
	}

	/* Check the various types of member */
	switch (tag) {
	case id_stat_member_tag: {
		/* Static data members may be initialised */
		DECL_SPEC ds;
		TYPE t = DEREF_type(id_stat_member_type(id));
		CV_SPEC cv = find_cv_qual(t);
		switch (TAG_type(t)) {
		case type_integer_tag:
		case type_enumerate_tag: {
			ERROR err = NULL_err;
			IGNORE make_nat_exp(e, &err);
			if (!IS_NULL_err(err)) {
				/* Initialiser should be a constant
				 * expression */
				ERROR err2 = ERR_class_mem_init_const();
				err = concat_error(err, err2);
				report(crt_loc, err);
			}
			break;
		}
		case type_token_tag: {
			if (!is_templ_type(t)) {
				goto default_lab;
			}
			break;
		}
		default:
default_lab:
			/* Only integral types allowed */
			report(crt_loc, ERR_class_static_data_init(id, t));
			break;
		}
		if (cv != (cv_const | cv_lvalue)) {
			/* Only const types allowed */
			report(crt_loc, ERR_class_static_data_const(id, t));
		}
		e = init_general(t, e, id, 0);
		e = dynamic_init(id, NULL_string, e);
		e = check_init(e);
		COPY_exp(id_stat_member_init(id), e);

		/* Mark inline member definition */
		ds = DEREF_dspec(id_storage(id));
		ds |= dspec_stat_inline;
		COPY_dspec(id_storage(id), ds);
		break;
	}
	case id_mem_func_tag:
	case id_stat_mem_func_tag: {
		/* Check for pure specifiers */
		if (is_zero_exp(e)) {
			DECL_SPEC ds = DEREF_dspec(id_storage(id));
			if (ds & dspec_virtual) {
				CLASS_TYPE ct = crt_class;
				CLASS_INFO ci = DEREF_cinfo(ctype_info(ct));

				/* Pure specifier should be precisely '0' */
				int tok = last_lex_token;
				if (tok != lex_integer_Hexp ||
				    is_literal(e)!= 2) {
					report(crt_loc,
					       ERR_class_abstract_zero());
				}

				/* Mark class as abstract */
				ci |= cinfo_abstract;
				COPY_cinfo(ctype_info(ct), ci);

				/* Mark function as pure */
				ds |= dspec_pure;
				COPY_dspec(id_storage(id), ds);
			} else {
				/* Only virtual functions can be pure */
				report(crt_loc, ERR_class_abstract_virt());
			}
		} else {
			/* Can't initialise functions otherwise */
			report(crt_loc, ERR_dcl_init_func(id));
		}
		break;
	}
	case id_member_tag: {
		/* Can't initialise non-static members */
		report(crt_loc, ERR_class_mem_init_mem(id));
		break;
	}
	default:
		/* Can't initialise a typedef */
		report(crt_loc, ERR_dcl_init_typedef(id));
		break;
	}
	return def;
}


/*
    This routine enables the token id as an initialiser.
*/

void
allow_initialiser(IDENTIFIER id)
{
	id = find_token(id);
	if (IS_id_token(id)) {
		/* NOT YET IMPLEMENTED */
		/* EMPTY */
	} else {
		report(crt_loc, ERR_token_undecl(id));
	}
	return;
}


/*
    This routine initialises the field buffer.
*/

void
init_initialise(void)
{
	field_buff.posn = extend_buffer(&field_buff, field_buff.posn);
	return;
}
