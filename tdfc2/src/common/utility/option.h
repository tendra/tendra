/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef OPTION_INCLUDED
#define OPTION_INCLUDED


/*
    OPTION CATALOGUES

    The table OPT_CATALOG is used to maintain the list of all boolean
    options.  The table OPT_VALUE_CATALOG is used to hold the value
    options.  Macros are given to name the entries in the latter table.
    Names for entries in the former table are generated from the
    error catalogue.
*/

typedef struct {
    const char *name;
    int scoped;
    OPTION def[2];
} OPT_DATA;

typedef struct {
    const char *name;
    LOCATION *loc;
    unsigned long max_value;
    unsigned long min_value;
    unsigned long crt_value;
    int incr;
} OPT_VALUE_DATA;

extern OPT_DATA OPT_CATALOG[];
extern OPT_VALUE_DATA OPT_VALUE_CATALOG[];


/*
    OPTION LEVELS

    These values give the various option levels.  The fact that OPTION_OFF
    is zero is used extensively.
*/

enum {
	OPTION_OFF,
	OPTION_WARN,
	OPTION_ON,
	OPTION_WHATEVER,

	OPTION_ALLOW    = OPTION_OFF,
	OPTION_DISALLOW = OPTION_ON
};


/*
    OPTION VALUES

    These macros are used to represent the various numeric option values
    within the program.
*/

enum {
	OPT_VAL_statement_depth,
	OPT_VAL_hash_if_depth,
	OPT_VAL_declarator_max,
	OPT_VAL_paren_depth,
	OPT_VAL_name_limit,
	OPT_VAL_extern_name_limit,
	OPT_VAL_external_ids,
	OPT_VAL_block_ids,
	OPT_VAL_macro_ids,
	OPT_VAL_func_pars,
	OPT_VAL_func_args,
	OPT_VAL_macro_pars,
	OPT_VAL_macro_args,
	OPT_VAL_line_length,
	OPT_VAL_string_length,
	OPT_VAL_sizeof_object,
	OPT_VAL_include_depth,
	OPT_VAL_switch_cases,
	OPT_VAL_data_members,
	OPT_VAL_enum_consts,
	OPT_VAL_nested_class,
	OPT_VAL_atexit_funcs,
	OPT_VAL_base_classes,
	OPT_VAL_direct_bases,
	OPT_VAL_class_members,
	OPT_VAL_virtual_funcs,
	OPT_VAL_virtual_bases,
	OPT_VAL_static_members,
	OPT_VAL_friends,
	OPT_VAL_access_declarations,
	OPT_VAL_ctor_initializers,
	OPT_VAL_scope_qualifiers,
	OPT_VAL_external_specs,
	OPT_VAL_template_pars,
	OPT_VAL_instance_depth,
	OPT_VAL_exception_handlers,
	OPT_VAL_exception_specs,
	OPT_VAL_cast_explicit,
	OPT_VAL_maximum_error,
	OPT_VAL_tab_width
};


/*
    COMPILER OPTION DECLARATIONS

    The routines in this module are concerned with configurable compiler
    options.
*/

extern OPTION *crt_opt;
extern OPTIONS *crt_opts;
extern OPTIONS *real_opts;
extern void set_option(int, unsigned);
extern void set_value(int, EXP, unsigned long);
extern void set_link_opt(DECL_SPEC);
extern ERROR set_severity(ERROR, int, int);
extern int find_option_no(STRING, int);
extern int find_value_no(STRING, int);
extern int find_type_no(STRING);
extern int check_value(int, unsigned long, ...);
extern int incr_value(int);
extern void decr_value(int);
extern void use_option(IDENTIFIER, unsigned);
extern void use_mode(OPTIONS *, int);
extern void set_mode(OPTIONS *);
extern void directory_option(IDENTIFIER, IDENTIFIER);
extern void begin_option(IDENTIFIER);
extern void end_option(int);
extern void init_option(int);
extern void term_option(void);

#define option(A)		(crt_opt[(A)])
#define option_value(A)	(OPT_VALUE_CATALOG[(A)].max_value)
#define crt_option_value(A)	(OPT_VALUE_CATALOG[(A)].crt_value)


#endif
