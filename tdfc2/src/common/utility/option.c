/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <assert.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include <utility/config.h>
#include "c_types.h"

#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/option.h>
#include <utility/ustring.h>
#include <utility/xalloc.h>

#include <parse/char.h>
#include <parse/constant.h>
#include <parse/file.h>
#include <parse/hash.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <parse/predict.h>
#include <parse/preproc.h>

#include "err_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "str_ops.h"
#include "cast.h"
#include "declare.h"
#include "instance.h"
#include "inttype.h"
#include "namespace.h"
#include "redeclare.h"
#include "syntax.h"


/*
    This table gives the catalogue of all options.  Each entry consists
    of an option name plus the default value of the option in the
    various standard compilation modes.  The main body is automatically
    generated from the error database.
*/

#define OPT_VALUE_off		1, { OPTION_OFF,      OPTION_OFF      }
#define OPT_VALUE_on		1, { OPTION_ON,       OPTION_ON       }
#define OPT_VALUE_none		1, { OPTION_ALLOW,    OPTION_ALLOW    }
#define OPT_VALUE_warning	1, { OPTION_WARN,     OPTION_WARN     }
#define OPT_VALUE_error		1, { OPTION_DISALLOW, OPTION_DISALLOW }
#define OPT_VALUE_whatever	1, { OPTION_WHATEVER, OPTION_WHATEVER }
#define OPT_VALUE_new		1, { OPTION_WARN,     OPTION_DISALLOW }
#define OPT_VALUE_wall		1, { OPTION_ALLOW,    OPTION_WARN     }

OPT_DATA OPT_CATALOG[] = {
#include <utility/opts.h>
	{ NULL, OPT_VALUE_off }
};

#define CATALOG_SIZE		array_size(OPT_CATALOG)


/*
    This table gives the catalogue of all option values.  Each entry
    consists of an option name, its maximum value allowed within the
    program, its minimum maximum value allowed by the standard and a
    current value.  The entries need to be kept in step with the
    OPT_VAL_* macros defined in options.h.  Note that most of the
    implementation limits are NO_LIMIT, indicating that there is no
    built-in limit.
*/

#if LANGUAGE_CPP
#define LIMIT(A, B)		((unsigned long)(A))
#else
#define LIMIT(A, B)		((unsigned long)(B))
#endif
#define NO_LIMIT		ULONG_MAX
#define STR_LIMIT		(ULONG_MAX >> 3)

OPT_VALUE_DATA OPT_VALUE_CATALOG[] = {
	/* Implementation quantities (from Annex B) */
	{ "statement_depth",     &crt_loc,     NO_LIMIT,      LIMIT(256, 15),       0, 1 },
	{ "hash_if_depth",       &preproc_loc, NO_LIMIT,      LIMIT(256, 8),        0, 1 },
	{ "declarator_max",      &crt_loc,     NO_LIMIT,      LIMIT(256, 12),       0, 0 },
	{ "paren_depth",         &crt_loc,     NO_LIMIT,      LIMIT(256, 32),       0, 1 },
	{ "name_limit",          &crt_loc,     NO_LIMIT,      LIMIT(1024, 31),      0, 0 },
	{ "extern_name_limit",   &crt_loc,     NO_LIMIT,      LIMIT(1024, 6),       0, 0 },
	{ "external_ids",        &crt_loc,     NO_LIMIT,      LIMIT(65536, 511),    0, 0 },
	{ "block_ids",           &crt_loc,     NO_LIMIT,      LIMIT(1024, 127),     0, 0 },
	{ "macro_ids",           &preproc_loc, NO_LIMIT,      LIMIT(65536, 1024),   0, 1 },
	{ "func_pars",           &crt_loc,     NO_LIMIT,      LIMIT(256, 31),       0, 0 },
	{ "func_args",           &crt_loc,     NO_LIMIT,      LIMIT(256, 31),       0, 0 },
	{ "macro_pars",          &preproc_loc, NO_LIMIT,      LIMIT(256, 31),       0, 0 },
	{ "macro_args",          &crt_loc,     NO_LIMIT,      LIMIT(256, 31),       0, 0 },
	{ "line_length",         &crt_loc,     NO_LIMIT,      LIMIT(65536, 509),    0, 0 },
	{ "string_length",       &crt_loc,     STR_LIMIT,     LIMIT(65536, 509),    0, 0 },
	{ "sizeof_object",       &crt_loc,     NO_LIMIT,      LIMIT(262144, 32767), 0, 0 },
	{ "include_depth",       &preproc_loc, 256,           LIMIT(256, 8),        0, 1 },
	{ "switch_cases",        &crt_loc,     NO_LIMIT,      LIMIT(16384, 257),    0, 0 },
	{ "data_members",        &crt_loc,     NO_LIMIT,      LIMIT(16384, 127),    0, 0 },
	{ "enum_consts",         &crt_loc,     NO_LIMIT,      LIMIT(4096, 127),     0, 0 },
	{ "nested_class",        &crt_loc,     NO_LIMIT,      LIMIT(256, 15),       0, 1 },
	{ "atexit_funcs",        &crt_loc,     NO_LIMIT,      LIMIT(32, 32),        0, 0 },
	{ "base_classes",        &crt_loc,     NO_LIMIT,      LIMIT(16384, 0),      0, 0 },
	{ "direct_bases",        &crt_loc,     NO_LIMIT,      LIMIT(1024, 0),       0, 0 },
	{ "class_members",       &crt_loc,     NO_LIMIT,      LIMIT(4096, 0),       0, 0 },
	{ "virtual_funcs",       &crt_loc,     NO_LIMIT,      LIMIT(16384, 0),      0, 0 },
	{ "virtual_bases",       &crt_loc,     NO_LIMIT,      LIMIT(1024, 0),       0, 0 },
	{ "static_members",      &crt_loc,     NO_LIMIT,      LIMIT(1024, 0),       0, 0 },
	{ "friends",             &crt_loc,     NO_LIMIT,      LIMIT(4096, 0),       0, 0 },
	{ "access_declarations", &crt_loc,     NO_LIMIT,      LIMIT(4096, 0),       0, 0 },
	{ "ctor_initializers",   &crt_loc,     NO_LIMIT,      LIMIT(6144, 0),       0, 0 },
	{ "scope_qualifiers",    &crt_loc,     NO_LIMIT,      LIMIT(256, 0),        0, 0 },
	{ "external_specs",      &crt_loc,     NO_LIMIT,      LIMIT(1024, 0),       0, 1 },
	{ "template_pars",       &crt_loc,     NO_LIMIT,      LIMIT(1024, 0),       0, 0 },
	{ "instance_depth",      &crt_loc,     17,            LIMIT(17, 0),         0, 1 },
	{ "exception_handlers",  &crt_loc,     NO_LIMIT,      LIMIT(256, 0),        0, 0 },
	{ "exception_specs",     &crt_loc,     NO_LIMIT,      LIMIT(256, 0),        0, 0 },

	/* Other quantities */
	{ "cast_explicit",       &crt_loc,     CAST_EXPLICIT, 0,                    0, 0 },
	{ "maximum_error",       &crt_loc,     32,            1,                    0, 0 },
	{ "tab_width",           &crt_loc,     8,             1,                    0, 0 },
	{ NULL,                  NULL,         0,             0,                    0, 0 }
};

#define VALUE_CAT_SIZE		array_size(OPT_VALUE_CATALOG)


/*
    This table gives the names of all the types used in the error catalogue
    together with the code letter used to encode them.
*/

typedef struct {
	const char *name;
	int number;
} OPT_TYPE_DATA;

static OPT_TYPE_DATA OPT_TYPE_CATALOG[] = {
	{ "ACCESS",     ERR_KEY_ACCESS     },
	{ "BASE_TYPE",  ERR_KEY_BASE_TYPE  },
	{ "CLASS_TYPE", ERR_KEY_CLASS_TYPE },
	{ "CV_SPEC",    ERR_KEY_CV_SPEC    },
	{ "DECL_SPEC",  ERR_KEY_DECL_SPEC  },
	{ "FLOAT",      ERR_KEY_FLOAT      },
	{ "HASHID",     ERR_KEY_HASHID     },
	{ "IDENTIFIER", ERR_KEY_IDENTIFIER },
	{ "LEX",        ERR_KEY_LEX        },
	{ "LONG_ID",    ERR_KEY_LONG_ID    },
	{ "NAMESPACE",  ERR_KEY_NAMESPACE  },
	{ "NAT",        ERR_KEY_NAT        },
	{ "PPTOKEN_P",  ERR_KEY_PPTOKEN_P  },
	{ "PTR_LOC",    ERR_KEY_PTR_LOC    },
	{ "QUALIFIER",  ERR_KEY_QUALIFIER  },
	{ "STRING",     ERR_KEY_STRING     },
	{ "TYPE",       ERR_KEY_TYPE       },
	{ "cint",       ERR_KEY_cint       },
	{ "cstring",    ERR_KEY_cstring    },
	{ "string",     ERR_KEY_string     },
	{ "ucint",      ERR_KEY_ucint      },
	{ "ulong",      ERR_KEY_ulong      },
	{ "unsigned",   ERR_KEY_unsigned   },
	{ "plural",     ERR_KEY_plural     }
};

#define TYPE_CAT_SIZE		array_size(OPT_TYPE_CATALOG)


/*
    This hash table is used to hold the names of the various options in
    the option catalogue.
*/

typedef struct opt_hash_tag {
	int number;
	OPT_DATA *entry;
	struct opt_hash_tag *next;
} OPT_HASH;

#define HASH_OPTION	128
static OPT_HASH *option_hash[HASH_OPTION + 1];
static OPT_HASH *all_option_hash = NULL;


/*
    This routine sets up the option hash table.
*/

static void
init_opt_hash(void)
{
	int i;
	OPT_DATA *cat = OPT_CATALOG;
	OPT_HASH *opt = xmalloc_nof(OPT_HASH, CATALOG_SIZE);
	for (i = 0; i <= HASH_OPTION; i++) {
		option_hash[i] = NULL;
	}
	all_option_hash = opt;
	for (i = 0; i < CATALOG_SIZE; i++) {
		unsigned long h;
		string s = ustrlit(cat->name);
		if (s) {
			h = hash(s);
			h %= HASH_OPTION;
		} else {
			h = HASH_OPTION;
		}
		opt->number = i;
		opt->entry = cat;
		opt->next = option_hash[h];
		option_hash[h] = opt;
		cat++;
		opt++;
	}
	return;
}


/*
    This routine finds the option number corresponding to the string
    literal expression s.  n gives a likely value to try first.  It
    returns -1 if s is not the name of a known option.
*/

int
find_option_no(STRING s, int n)
{
	unsigned kind = DEREF_unsigned(str_simple_kind(s));
	if (kind == STRING_NONE) {
		OPT_HASH *opt;
		unsigned long h;
		string text = DEREF_string(str_simple_text(s));
		ulong len = DEREF_ulong(str_simple_len(s));
		if (n >= 0 && n < CATALOG_SIZE) {
			string nm = ustrlit(OPT_CATALOG[n].name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return n;
				}
			}
		}
		if (all_option_hash == NULL) {
			init_opt_hash();
		}
		h = hash(text);
		h %= HASH_OPTION;
		for (opt = option_hash[h]; opt != NULL; opt = opt->next) {
			string nm = ustrlit(opt->entry->name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return opt->number;
				}
			}
		}
	}
	return -1;
}


/*
    This routine finds the value option number corresponding to the
    string literal expression s.  n gives a likely value to try first.
    It returns -1 if s is not the name of a known value option.  Note
    that there are not enough cases to warrant a hash table.
*/

int
find_value_no(STRING s, int n)
{
	unsigned kind = DEREF_unsigned(str_simple_kind(s));
	if (kind == STRING_NONE) {
		int i;
		OPT_VALUE_DATA *p = OPT_VALUE_CATALOG;
		string text = DEREF_string(str_simple_text(s));
		ulong len = DEREF_ulong(str_simple_len(s));
		if (n >= 0 && n < VALUE_CAT_SIZE) {
			string nm = ustrlit(p[n].name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return n;
				}
			}
		}
		for (i = 0; i < VALUE_CAT_SIZE; i++) {
			string nm = ustrlit(p->name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return i;
				}
			}
			p++;
		}
	}
	return -1;
}


/*
    This routine finds the encoding character for the type corresponding
    to the string literal expression s.  It returns -1 if s is not the
    name of a known value option.  Note that there are not enough cases
    to warrant a hash table.
*/

int
find_type_no(STRING s)
{
	unsigned kind = DEREF_unsigned(str_simple_kind(s));
	if (kind == STRING_NONE) {
		int i;
		OPT_TYPE_DATA *p = OPT_TYPE_CATALOG;
		string text = DEREF_string(str_simple_text(s));
		ulong len = DEREF_ulong(str_simple_len(s));
		for (i = 0; i < TYPE_CAT_SIZE; i++) {
			string nm = ustrlit(p->name);
			if (nm && ustreq(text, nm)) {
				if (len == (ulong)ustrlen(nm)) {
					return p->number;
				}
			}
			p++;
		}
	}
	return -1;
}


/*
    The variable crt_opts is used to record the current option state.
    In addition a list of all scopes defined, all_opts, is maintained.
    The variable crt_opt shadows crt_opts->opt and gives a user-accessible
    array of option values.
*/

OPTIONS *crt_opts = NULL;
OPTIONS *real_opts = NULL;
static OPTIONS *all_opts = NULL;
OPTION *crt_opt = NULL;


/*
    This routine modifies the severity level of the error err using the
    option n.  Whether the severity is set to that of option n depends
    on the value of set; it is always set if set is zero, only set if
    option n is more severe if set is positive, and only set if option
    n is less severe if set is negative.
*/

ERROR
set_severity(ERROR err, int n, int set)
{
	if (!IS_NULL_err(err)) {
		OPTION opt = crt_opts->opt[n];
		int e = error_severity[opt];
		if (set != 0) {
			/* Compare with previous severity */
			int c = DEREF_int(err_severity(err));
			if (set > 0) {
				if (e < c) {
					e = c;
				}
			} else {
				if (e > c) {
					e = c;
				}
			}
		}
		if (e == ERR_NONE) {
			/* Option off - return null error */
			destroy_error(err, 1);
			err = NULL_err;
		} else {
			/* Set severity level */
			COPY_int(err_severity(err), e);
		}
	}
	return err;
}


/*
    This routine performs any actions associated with setting the value
    of option n to opt.  The flag end is true if this call is at the
    end of a scope to restore the old value of option n.
*/

static void
action_option(int n, unsigned opt, int end)
{
	switch (n) {
	case OPT_none: {
		error_severity[OPTION_OFF] = default_severity[opt];
		break;
	}
	case OPT_warning: {
		error_severity[OPTION_WARN] = default_severity[opt];
		break;
	}
	case OPT_error: {
		error_severity[OPTION_ON] = default_severity[opt];
		break;
	}
	case OPT_whatever: {
		error_severity[OPTION_WHATEVER] = default_severity[opt];
		break;
	}
	case OPT_conv_int_int_expl:
	case OPT_conv_int_int_impl:
	case OPT_conv_int_ptr_expl:
	case OPT_conv_ptr_ptr_expl: {
		/* Individual conversion options */
		if (!end) {
			OPTION *q = real_opts->opt;
			OPTION c = OPTION_OFF;
			OPTION c1 = OPTION_OFF;
			OPTION c2 = q[OPT_conv_int_ptr_expl];
			OPTION c3 = q[OPT_conv_ptr_ptr_expl];
			OPTION c11 = q[OPT_conv_int_int_expl];
			OPTION c12 = q[OPT_conv_int_int_impl];
			if (c11 || c12) {
				c1 = OPTION_ON;
			}
			if (c1 || c2 || c3) {
				c = OPTION_ON;
			}
			q[OPT_conv_ptr_ptr] = c3;
			q[OPT_conv_int_ptr] = c2;
			q[OPT_conv_int_int] = c1;
			q[OPT_conv] = c;
		}
		break;
	}
	case OPT_discard_func:
	case OPT_discard_static:
	case OPT_discard_value: {
		/* Individual discard options */
		if (!end) {
			OPTION *q = real_opts->opt;
			OPTION d = OPTION_OFF;
			OPTION d1 = OPTION_OFF;
			OPTION d2 = q[OPT_discard_static];
			OPTION d11 = q[OPT_discard_func];
			OPTION d12 = q[OPT_discard_value];
			if (d11 || d12) {
				d1 = OPTION_ON;
			}
			if (d1 || d2) {
				d = OPTION_ON;
			}
			q[OPT_discard_exp] = d1;
			q[OPT_discard] = d;
		}
		break;
	}
	case OPT_const_internal: {
		/* Linkage of const objects */
		if (opt == OPTION_ON) {
			const_linkage = dspec_static;
		} else {
			const_linkage = dspec_extern;
		}
		break;
	}
	case OPT_inline_internal: {
		/* Linkage of inline functions */
		if (opt == OPTION_ON) {
			inline_linkage = dspec_static;
		} else {
			inline_linkage = dspec_extern;
		}
		break;
	}
	case OPT_decl_volatile: {
		/* Volatility of external objects */
		if (opt == OPTION_ON) {
			cv_extern = cv_volatile;
		} else {
			cv_extern = cv_none;
		}
		break;
	}
	case OPT_proto_scope: {
		/* Recalculate namespaces */
		update_namespace();
		break;
	}
	case OPT_cpplus_comment: {
		/* C++ comments */
		allow_cpp_comments = (opt != OPTION_DISALLOW);
		break;
	}
	case OPT_digraph: {
		/* Digraphs */
		allow_digraphs = (opt != OPTION_DISALLOW);
		break;
	}
	case OPT_dollar_ident: {
		/* Dollar in identifier */
		int c = char_z;
		if (opt == OPTION_DISALLOW) {
			c = char_dollar;
		}
		set_char_lookup(char_dollar, c);
		break;
	}
	case OPT_iso_keyword: {
		/* ISO keywords */
		allow_iso_keywords = (opt != OPTION_DISALLOW);
		break;
	}
	case OPT_lint_comment: {
		/* Lint comments */
		analyse_comments = (opt != OPTION_DISALLOW);
		break;
	}
	case OPT_longlong: {
		/* 'long long' types */
		int key = (opt != OPTION_DISALLOW);
		basetype_info[ntype_sllong].key = key;
		basetype_info[ntype_ullong].key = key;
		break;
	}
	case OPT_trigraph: {
		/* Trigraphs */
		allow_trigraphs = (opt != OPTION_DISALLOW);
		break;
	}
	}
	return;
}


/*
    This routine sets the option n to option level opt.  This can be
    OPTION_OFF (for 'off' or 'allow'), OPTION_WARN (for 'warning') or
    OPTION_ON (for 'on' or 'disallow').  Note that special action needs
    to be taken if n represents a set of options such as conv or discard
    where the set value is the logical or of the values of the set
    members.
*/

void
set_option(int n, unsigned opt)
{
	if (n != -1) {
		/* Set the option level */
		switch (n) {
		case OPT_conv: {
			/* All conversion options */
			set_option(OPT_conv_int_int_expl, opt);
			set_option(OPT_conv_int_int_impl, opt);
			set_option(OPT_conv_int_ptr_expl, opt);
			set_option(OPT_conv_ptr_ptr_expl, opt);
			break;
		}
		case OPT_conv_int_int: {
			/* All integer conversion options */
			set_option(OPT_conv_int_int_expl, opt);
			set_option(OPT_conv_int_int_impl, opt);
			break;
		}
		case OPT_conv_int_ptr: {
			/* All integer to pointer conversion options */
			set_option(OPT_conv_int_ptr_expl, opt);
			break;
		}
		case OPT_conv_ptr_ptr: {
			/* All pointer conversion options */
			set_option(OPT_conv_ptr_ptr_expl, opt);
			break;
		}
		case OPT_discard: {
			/* All discard options */
			set_option(OPT_discard_func, opt);
			set_option(OPT_discard_static, opt);
			set_option(OPT_discard_value, opt);
			break;
		}
		case OPT_discard_exp: {
			/* Expression discard options */
			set_option(OPT_discard_func, opt);
			set_option(OPT_discard_value, opt);
			break;
		}
		case OPT_func_impl: {
			/* These options are negated */
			if (opt == OPTION_ON) {
				opt = OPTION_OFF;
			} else if (opt == OPTION_OFF) {
				opt = OPTION_ON;
			}
			goto default_lab;
		}
		default:
default_lab: {
		     /* Simple options */
		     OPTIONS *p = crt_opts;
		     if (OPT_CATALOG[n].scoped) {
			     /* Scoped options */
			     int sev = (int)p->set[n];
			     OPTION new_opt = (OPTION)opt;
			     OPTION old_opt = p->opt[n];
			     if (new_opt != old_opt) {
				     /* Option value changed */
				     p->opt[n] = new_opt;
				     action_option(n, opt, 0);
			     }
			     if (sev != ERR_WHATEVER) {
				     /* Option already set in this scope */
				     string s = ustrlit(OPT_CATALOG[n].name);
				     ERROR err = ERR_pragma_scope_set(s);
				     if (!IS_NULL_err(err)) {
					     COPY_int(err_severity(err), sev);
					     report(preproc_loc, err);
				     }
			     }
			     p->set[n] = ERR_SERIOUS;
		     } else {
			     /* Unscoped options */
			     p->opt[n] = (OPTION)opt;
			     action_option(n, opt, 0);
			     p->set[n] = ERR_SERIOUS;
		     }
		     break;
	     }
		}
	}
	return;
}


/*
    This routine performs any actions associated with setting option value
    n to v.  The flag end is true if this call is at the end of a scope to
    restore the old value of option n.
*/

static void
action_value(int n, unsigned long v)
{
	switch (n) {
	case OPT_VAL_include_depth: {
		set_incl_depth(v);
		break;
	}
	case OPT_VAL_name_limit: {
		if (v < max_id_length) {
			max_id_length = v;
		}
		break;
	}
	case OPT_VAL_maximum_error: {
		max_errors = v;
		break;
	}
	case OPT_VAL_tab_width: {
		if (v != 0) {
			tab_width = v;
		}
		break;
	}
	}
	return;
}


/*
    This routine sets the option value for option n to the integer literal
    expression e or the value v.  Note that option values are not scoped.
*/

void
set_value(int n, EXP e, unsigned long v)
{
	if (!IS_NULL_exp(e)) {
		NAT m;
		if (!IS_exp_int_lit(e)) {
			return;
		}
		m = DEREF_nat(exp_int_lit_nat(e));
		v = get_nat_value(m);
	}
	if (n != -1) {
		OPT_VALUE_CATALOG[n].max_value = v;
		OPT_VALUE_CATALOG[n].min_value = v;
		action_value(n, v);
	}
	return;
}


/*
    This routine checks whether the value v is less than the maximum
    permitted value for the option n.  It returns true if so.  Extra
    arguments for use in error reporting may be provided.
*/

int
check_value(int n, unsigned long v, ...) /* VARARGS */
{
	va_list args;
	unsigned long u;
	OPT_VALUE_DATA *p;
	va_start(args, v);

	/* Check against implementation limit */
	p = OPT_VALUE_CATALOG + n;
	u = p->max_value;
	if (v > u) {
		int err = 1;
		if (p->incr) {
			if (v > u + 1) {
				err = 0;
			}
			p->incr = 2;
		}
		if (err) {
			LOCATION *loc = p->loc;
			switch (n) {
			case OPT_VAL_include_depth: {
				/* Include depth too great */
				print_error(loc, ERR_cpp_include_depth(v));
				break;
			}
			case OPT_VAL_name_limit: {
				/* Name length too great */
				HASHID nm = va_arg(args, HASHID);
				print_error(loc, ERR_lex_name_limit(nm, v, u));
				break;
			}
			case OPT_VAL_instance_depth: {
				/* Instantiation depth too great */
				print_error(loc, ERR_temp_inst_depth(v));
				break;
			}
			default : {
				/* Other limit exceeded */
				string s = ustrlit(p->name);
				print_error(loc, ERR_limits_max(s, v, u));
				break;
			}
			}
		}
		va_end(args);
		return 0;
	}

	/* Check against minimum implementation limit */
	u = p->min_value;
	if (v > u) {
		if (p->incr) {
			p->incr = 2;
		} else {
			LOCATION *loc = p->loc;
			string s = ustrlit(p->name);
			print_error(loc, ERR_limits_min(s, v, u));
		}
	}
	va_end(args);
	return 1;
}


/*
    This routine increments the current value of the option value n,
    applying check_value to the result.
*/

int
incr_value(int n)
{
	OPT_VALUE_DATA *p = OPT_VALUE_CATALOG + n;
	unsigned long v = ++(p->crt_value);
	assert(p->incr);
	return check_value(n, v);
}


/*
    This routine decrements the current value of the option value n.
*/

void
decr_value(int n)
{
	OPT_VALUE_DATA *p = OPT_VALUE_CATALOG + n;
	unsigned long v = p->crt_value;
	if (v) {
		if (p->incr == 2) {
			/* Report maximum value attained */
			LOCATION *loc = p->loc;
			string s = ustrlit(p->name);
			unsigned long u = p->min_value;
			print_error(loc, ERR_limits_min(s, v, u));
			p->incr = 1;
		}
		p->crt_value = v - 1;
	}
	return;
}


/*
    This routine sets the current external linkage option to ds.
*/

void
set_link_opt(DECL_SPEC ds)
{
	OPTIONS *p = crt_opts;
	if (p) {
		DECL_SPEC ods = p->lnk_opt[1];
		if (ods != dspec_ignore) {
			/* Option already set in this scope */
			string s = ustrlit("link_extern");
			ERROR err = ERR_pragma_scope_set(s);
			if (!IS_NULL_err(err)) {
				report(preproc_loc, err);
			}
		}
		p->lnk_opt[1] = ds;
		crt_linkage = ds;
		new_linkage = ds;
	}
	return;
}


/*
    This routine searches for a checking scope named nm, returning the
    corresponding table of options.  If nm has not been defined then the
    null pointer is returned.
*/

static OPTIONS *
find_option(HASHID nm)
{
	OPTIONS *p;
	for (p = all_opts; p != NULL; p = p->next) {
		if (EQ_hashid(nm, p->name)) {
			return p;
		}
	}
	return NULL;
}


/*
    This routine creates a new option scope named nm with initial
    values taken either from the existing scope q or, if this is the
    null pointer, the nth entry of the options catalogue above.
*/

static OPTIONS *
new_option(HASHID nm, OPTIONS *q, int n)
{
	/* Allocate space for new scope */
	int i;
	OPTIONS *p = xmalloc_nof(OPTIONS, 1);
	OPTION *po = xmalloc_nof(OPTION, 2 * CATALOG_SIZE);
	OPTION *ps = po + CATALOG_SIZE;
	p->opt = po;
	p->set = ps;
	p->val_opt[0] = no_declarations;
	p->lnk_opt[0] = crt_linkage;
	p->lnk_opt[1] = dspec_ignore;
	p->prev = NULL;
	p->name = NULL_hashid;
	p->next = all_opts;
	all_opts = p;

	/* Check scope name */
	if (!IS_NULL_hashid(nm)) {
		if (find_option(nm)) {
			report(preproc_loc, ERR_pragma_scope_redef(nm));
		}
		p->name = nm;
	}

	/* Set up scope */
	if (q) {
		/* Copy existing scope */
		OPTION *qo = q->opt;
		for (i = 0; i < CATALOG_SIZE; i++) {
			*(po++) = *(qo++);
			*(ps++) = ERR_WHATEVER;
		}
	} else {
		/* Use standard scope */
		OPT_DATA *cat = OPT_CATALOG;
		for (i = 0; i < CATALOG_SIZE; i++) {
			/* Use the nth entry from the catalogue */
			*(po++) = cat->def[n];
			*(ps++) = ERR_SERIOUS;
			cat++;
		}
	}
	return p;
}


/*
    This routine begins a new checking scope.
*/

void
begin_option(IDENTIFIER id)
{
	OPTIONS *p;
	HASHID nm = NULL_hashid;
	if (!IS_NULL_id(id)) {
		nm = DEREF_hashid(id_name(id));
	}
	p = new_option(nm, real_opts, 0);
	p->prev = real_opts;
	crt_opts = p;
	real_opts = p;
	crt_opt = p->opt;
	return;
}


/*
    This routine ends the current checking scope.
*/

void
end_option(int expl)
{
	OPTIONS *p = real_opts;
	if (p) {
		OPTIONS *q = p->prev;
		DECL_SPEC ds = p->lnk_opt[0];
		if (expl && p->val_opt[0] == no_declarations) {
			if (IS_NULL_hashid(p->name) && !preproc_only) {
				report(preproc_loc, ERR_dcl_dcl_none());
			}
		}
		crt_linkage = ds;
		new_linkage = ds;
		if (q) {
			int i;
			crt_opts = q;
			real_opts = q;
			crt_opt = q->opt;
			for (i = 0; i < CATALOG_SIZE; i++) {
				if (p->set[i]!= ERR_WHATEVER) {
					/* Restore old option value */
					OPTION opt_old = p->opt[i];
					OPTION opt_new = q->opt[i];
					if (opt_new != opt_old) {
						if (OPT_CATALOG[i].scoped) {
							action_option(i,
							  (unsigned)opt_new, 1);
						} else {
							q->opt[i] = opt_old;
							q->set[i] = 1;
						}
					}
				}
			}
			return;
		}
	}
	report(preproc_loc, ERR_pragma_scope_end());
	return;
}


/*
    This routine brings the set of checks given by p into the current
    checking scope.  e indicates the error severity with which to report
    reset options.
*/

void
use_mode(OPTIONS *p, int e)
{
	int i;
	OPTIONS *q = real_opts;
	DECL_SPEC ds = p->lnk_opt[1];
	if (ds != dspec_ignore) {
		DECL_SPEC ods = q->lnk_opt[1];
		if (ods != dspec_ignore) {
			/* Option already set in this scope */
			string s = ustrlit("link_extern");
			ERROR err = ERR_pragma_scope_set(s);
			if (!IS_NULL_err(err)) {
				COPY_int(err_severity(err), e);
				report(preproc_loc, err);
			}
		}
		q->lnk_opt[1] = ds;
		crt_linkage = ds;
		new_linkage = ds;
	}
	for (i = 0; i < CATALOG_SIZE; i++) {
		if (p->set[i]!= ERR_WHATEVER && OPT_CATALOG[i].scoped) {
			OPTION new_opt = p->opt[i];
			OPTION old_opt = q->opt[i];
			if (new_opt != old_opt) {
				/* Option value changed */
				q->opt[i] = new_opt;
				action_option(i,(unsigned)new_opt, 0);
			}
			if (q->set[i]!= ERR_WHATEVER && e != ERR_NONE) {
				/* Option already set in this scope */
				string s = ustrlit(OPT_CATALOG[i].name);
				ERROR err = ERR_pragma_scope_set(s);
				if (!IS_NULL_err(err)) {
					COPY_int(err_severity(err), e);
					report(preproc_loc, err);
				}
			}
			q->set[i] = ERR_SERIOUS;
		}
	}
	return;
}


/*
    This routine sets the current checking scope to p.  It is used in
    context switching in macro expansion.
*/

void
set_mode(OPTIONS *p)
{
	if (p) {
		crt_opts = p;
		crt_opt = p->opt;
	}
	return;
}


/*
    This routine brings the named checking scope id back into scope.  The
    opt argument describes how the resetting of these options are to be
    handled.
*/

void
use_option(IDENTIFIER id, unsigned opt)
{
	HASHID nm = DEREF_hashid(id_name(id));
	OPTIONS *p = find_option(nm);
	if (p == NULL) {
		report(preproc_loc, ERR_pragma_scope_undef(nm));
		return;
	}
	use_mode(p, error_severity[opt]);
	return;
}


/*
    This routine associates the named checking scope id with the named
    include file directory dir.
*/

void
directory_option(IDENTIFIER dir, IDENTIFIER id)
{
	string s;
	HASHID nm = DEREF_hashid(id_name(id));
	OPTIONS *p = find_option(nm);
	if (p == NULL) {
		report(preproc_loc, ERR_pragma_scope_undef(nm));
	}
	nm = DEREF_hashid(id_name(dir));
	s = DEREF_string(hashid_name_etc_text(nm));
	directory_mode(s, p);
	return;
}


/*
    This routine initialises the outer checking scope at the checking
    level indicated by level and sets up the option hash table.
*/

void
init_option(int level)
{
	int i;
	string s;
	HASHID nm;
	OPTION *po;
	OPTIONS *p1, *p2;
	OPT_DATA *cat = OPT_CATALOG;
	OPT_VALUE_DATA *vcat = OPT_VALUE_CATALOG;

	/* Mark basic options */
	cat[OPT_none].scoped = 0;
	cat[OPT_warning].scoped = 0;
	cat[OPT_error].scoped = 0;
	cat[OPT_whatever].scoped = 0;

	/* Mark unscoped options */
	cat[OPT_const_internal].scoped = 0;
	cat[OPT_cpplus_comment].scoped = 0;
	cat[OPT_digraph].scoped = 0;
	cat[OPT_dollar_ident].scoped = 0;
	cat[OPT_ellipsis_ident].scoped = 0;
	cat[OPT_inline_internal].scoped = 0;
	cat[OPT_iso_keyword].scoped = 0;
	cat[OPT_lint_comment].scoped = 0;
	cat[OPT_trigraph].scoped = 0;

	/* A few other initialisations */
	max_id_length = vcat[OPT_VAL_name_limit].min_value;

	/* Set up default compilation modes */
	s = ustrlit("__DEFAULT__");
	nm = lookup_name(s, hash(s), 0, lex_identifier);
	p1 = new_option(nm, NIL(OPTIONS), 0);
	s = ustrlit("__ALL__");
	nm = lookup_name(s, hash(s), 0, lex_identifier);
	p2 = new_option(nm, NIL(OPTIONS), 1);

	/* Bring option into scope */
	if (level == 1) {
		p1 = p2;
	}
	p1 = new_option(NULL_hashid, p1, 0);
	crt_opts = p1;
	real_opts = p1;
	po = p1->opt;
	crt_opt = po;
	for (i = 0; i < CATALOG_SIZE; i++) {
		OPTION e = *(po++);
		action_option(i, (unsigned)e, 0);
	}
	for (i = 0; i < VALUE_CAT_SIZE; i++) {
		action_value(i, vcat->max_value);
		vcat++;
	}
	return;
}


/*
    This routine calls end_option for all unterminated checking scopes.
    It also reports any implementation limits which have been exceeded
    but not previously reported.
*/

void
term_option(void)
{
	if (real_opts) {
		int i;
		int expl = 1;
		OPT_VALUE_DATA *p = OPT_VALUE_CATALOG;
		for (i = 0; i < VALUE_CAT_SIZE; i++) {
			if (p->incr == 2) {
				/* Implementation limit exceeded */
				string s = ustrlit(p->name);
				unsigned long v = p->crt_value;
				unsigned long u = p->min_value;
				report(preproc_loc, ERR_limits_min(s, v, u));
				p->incr = 1;
			}
			p++;
		}
		while (real_opts->prev) {
			end_option(expl);
			expl = 0;
		}
		if (expl && no_declarations == 0 && !preproc_only) {
			report(preproc_loc, ERR_dcl_dcl_none());
		}
	}
	xfree_nof(all_option_hash);
	all_option_hash = NULL;
	return;
}
