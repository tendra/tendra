/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef SPEC_OPS_H_INCLUDED
#define SPEC_OPS_H_INCLUDED

/* Operations for union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :) EXP : unsigned : TAG_spec #
#pragma interface TAG_spec


/* Operations for component major of union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :)\
    EXP : PTR(unsigned) : spec_major #
#pragma interface spec_major

/* Operations for component minor of union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :)\
    EXP : PTR(unsigned) : spec_minor #
#pragma interface spec_minor

/* Operations for component sorts of union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :)\
    EXP : PTR(LIST(SORT)) : spec_sorts #
#pragma interface spec_sorts

/* Operations for component vars of union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :)\
    EXP : PTR(LIST(LINKAGE)) : spec_vars #
#pragma interface spec_vars

/* Operations for component eqns of union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :)\
    EXP : PTR(LIST(LINKAGE)) : spec_eqns #
#pragma interface spec_eqns

/* Operations for component foreign of union SPECIFICATION */

#pragma token PROC(EXP : SPECIFICATION :)\
    EXP : PTR(LIST(LINKAGE)) : spec_foreign #
#pragma interface spec_foreign

/* Operations for field basic of union SPECIFICATION */

#pragma token EXP const : unsigned : spec_basic_tag #
#pragma token PROC(EXP : SPECIFICATION :) EXP : int : IS_spec_basic #
#pragma interface spec_basic_tag IS_spec_basic

#pragma token PROC(\
	EXP : unsigned :,\
	EXP : unsigned :,\
	EXP : LIST(SORT) :,\
	EXP : LIST(LINKAGE) :,\
	EXP : LIST(LINKAGE) :,\
	EXP : LIST(LINKAGE) :,\
	EXP lvalue : SPECIFICATION :\
    ) STATEMENT MAKE_spec_basic #
#pragma interface MAKE_spec_basic

#pragma token PROC(\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST(SORT) :,\
	EXP lvalue : LIST(LINKAGE) :,\
	EXP lvalue : LIST(LINKAGE) :,\
	EXP lvalue : LIST(LINKAGE) :,\
	EXP : SPECIFICATION :\
    ) STATEMENT DECONS_spec_basic #
#pragma interface DECONS_spec_basic

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : unsigned :,\
	EXP lvalue : LIST(SORT) :,\
	EXP lvalue : LIST(LINKAGE) :,\
	EXP lvalue : LIST(LINKAGE) :,\
	EXP lvalue : LIST(LINKAGE) :,\
	EXP : SPECIFICATION :\
    ) STATEMENT DESTROY_spec_basic #
#pragma interface DESTROY_spec_basic


#endif
