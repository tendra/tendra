/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
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
    CONST char *name ;
    int scoped ;
    OPTION def [2] ;
} OPT_DATA ;

typedef struct {
    CONST char *name ;
    LOCATION *loc ;
    unsigned long max_value ;
    unsigned long min_value ;
    unsigned long crt_value ;
    int incr ;
} OPT_VALUE_DATA ;

extern OPT_DATA OPT_CATALOG [] ;
extern OPT_VALUE_DATA OPT_VALUE_CATALOG [] ;


/*
    OPTION LEVELS

    These values give the various option levels.  The fact that OPTION_OFF
    is zero is used extensively.
*/

#define OPTION_OFF				( ( OPTION ) 0 )
#define OPTION_WARN				( ( OPTION ) 1 )
#define OPTION_ON				( ( OPTION ) 2 )
#define OPTION_WHATEVER				( ( OPTION ) 3 )

#define OPTION_ALLOW				OPTION_OFF
#define OPTION_DISALLOW				OPTION_ON


/*
    OPTION VALUES

    These macros are used to represent the various numeric option values
    within the program.
*/

#define OPT_VAL_statement_depth			0
#define OPT_VAL_hash_if_depth			1
#define OPT_VAL_declarator_max			2
#define OPT_VAL_paren_depth			3
#define OPT_VAL_name_limit			4
#define OPT_VAL_extern_name_limit		5
#define OPT_VAL_external_ids			6
#define OPT_VAL_block_ids			7
#define OPT_VAL_macro_ids			8
#define OPT_VAL_func_pars			9
#define OPT_VAL_func_args			10
#define OPT_VAL_macro_pars			11
#define OPT_VAL_macro_args			12
#define OPT_VAL_line_length			13
#define OPT_VAL_string_length			14
#define OPT_VAL_sizeof_object			15
#define OPT_VAL_include_depth			16
#define OPT_VAL_switch_cases			17
#define OPT_VAL_data_members			18
#define OPT_VAL_enum_consts			19
#define OPT_VAL_nested_class			20
#define OPT_VAL_atexit_funcs			21
#define OPT_VAL_base_classes			22
#define OPT_VAL_direct_bases			23
#define OPT_VAL_class_members			24
#define OPT_VAL_virtual_funcs			25
#define OPT_VAL_virtual_bases			26
#define OPT_VAL_static_members			27
#define OPT_VAL_friends				28
#define OPT_VAL_access_declarations		29
#define OPT_VAL_ctor_initializers		30
#define OPT_VAL_scope_qualifiers		31
#define OPT_VAL_external_specs			32
#define OPT_VAL_template_pars			33
#define OPT_VAL_instance_depth			34
#define OPT_VAL_exception_handlers		35
#define OPT_VAL_exception_specs			36
#define OPT_VAL_cast_explicit			37
#define OPT_VAL_maximum_error			38
#define OPT_VAL_tab_width			39


/*
    COMPILER OPTION DECLARATIONS

    The routines in this module are concerned with configurable compiler
    options.
*/

extern OPTION *crt_opt ;
extern OPTIONS *crt_opts ;
extern OPTIONS *real_opts ;
extern void set_option PROTO_S ( ( int, unsigned ) ) ;
extern void set_value PROTO_S ( ( int, EXP, unsigned long ) ) ;
extern void set_link_opt PROTO_S ( ( DECL_SPEC ) ) ;
extern ERROR set_severity PROTO_S ( ( ERROR, int, int ) ) ;
extern int find_option_no PROTO_S ( ( STRING, int ) ) ;
extern int find_value_no PROTO_S ( ( STRING, int ) ) ;
extern int find_type_no PROTO_S ( ( STRING ) ) ;
extern int check_value PROTO_W ( ( int, unsigned long, ... ) ) ;
extern int incr_value PROTO_S ( ( int ) ) ;
extern void decr_value PROTO_S ( ( int ) ) ;
extern void use_option PROTO_S ( ( IDENTIFIER, unsigned ) ) ;
extern void use_mode PROTO_S ( ( OPTIONS *, int ) ) ;
extern void set_mode PROTO_S ( ( OPTIONS * ) ) ;
extern void directory_option PROTO_S ( ( IDENTIFIER, IDENTIFIER ) ) ;
extern void begin_option PROTO_S ( ( IDENTIFIER ) ) ;
extern void end_option PROTO_S ( ( int ) ) ;
extern void init_option PROTO_S ( ( int ) ) ;
extern void term_option PROTO_S ( ( void ) ) ;

#define option( A )		( crt_opt [ ( A ) ] )
#define option_value( A )	( OPT_VALUE_CATALOG [ ( A ) ].max_value )
#define crt_option_value( A )	( OPT_VALUE_CATALOG [ ( A ) ].crt_value )


#endif
