/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef ENTRY_OPS_H_INCLUDED
#define ENTRY_OPS_H_INCLUDED

/* Operations for union ENTRY */

#pragma token PROC(EXP : ENTRY :) EXP : unsigned : TAG_entry #
#pragma interface TAG_entry


/* Operations for component name of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(string) : entry_name #
#pragma interface entry_name

/* Operations for component alt_name of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(string) : entry_alt_name #
#pragma interface entry_alt_name

/* Operations for component signature of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(LIST(PARAM)) : entry_signature #
#pragma interface entry_signature

/* Operations for component use of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(USAGE) : entry_use #
#pragma interface entry_use

/* Operations for component alt_use of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(USAGE) : entry_alt_use #
#pragma interface entry_alt_use

/* Operations for component props of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(LIST(PROPERTY)) : entry_props #
#pragma interface entry_props

/* Operations for component maps of union ENTRY */

#pragma token PROC(EXP : ENTRY :)\
    EXP : PTR(LIST(MAP)) : entry_maps #
#pragma interface entry_maps

/* Operations for field basic of union ENTRY */

#pragma token EXP const : unsigned : entry_basic_tag #
#pragma token PROC(EXP : ENTRY :) EXP : int : IS_entry_basic #
#pragma interface entry_basic_tag IS_entry_basic

#pragma token PROC(\
	EXP : string :,\
	EXP : string :,\
	EXP : LIST(PARAM) :,\
	EXP : USAGE :,\
	EXP : USAGE :,\
	EXP : LIST(PROPERTY) :,\
	EXP : LIST(MAP) :,\
	EXP lvalue : ENTRY :\
    ) STATEMENT MAKE_entry_basic #
#pragma interface MAKE_entry_basic

#pragma token PROC(\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : LIST(PARAM) :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : LIST(PROPERTY) :,\
	EXP lvalue : LIST(MAP) :,\
	EXP : ENTRY :\
    ) STATEMENT DECONS_entry_basic #
#pragma interface DECONS_entry_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : string :,\
	EXP lvalue : string :,\
	EXP lvalue : LIST(PARAM) :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : USAGE :,\
	EXP lvalue : LIST(PROPERTY) :,\
	EXP lvalue : LIST(MAP) :,\
	EXP : ENTRY :\
    ) STATEMENT DESTROY_entry_basic #
#pragma interface DESTROY_entry_basic


#endif
