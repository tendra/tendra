/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA c_class (VERSION 1.1)
    BY calculus (VERSION 1.3)
*/

#ifndef VIRT_OPS_H_INCLUDED
#define VIRT_OPS_H_INCLUDED

/* Operations for union VIRTUAL */

#pragma token PROC(EXP : VIRTUAL :) EXP : unsigned : TAG_virt #
#pragma interface TAG_virt


/* Operations for component func of union VIRTUAL */

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(IDENTIFIER) : virt_func #
#pragma interface virt_func

/* Operations for component no of union VIRTUAL */

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(ulong_type) : virt_no #
#pragma interface virt_no

/* Operations for component base of union VIRTUAL */

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(GRAPH) : virt_base #
#pragma interface virt_base

/* Operations for component next of union VIRTUAL */

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(VIRTUAL) : virt_next #
#pragma interface virt_next

/* Operations for field table of union VIRTUAL */

#pragma token EXP const : unsigned : virt_table_tag #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_virt_table #
#pragma interface virt_table_tag IS_virt_table

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(OFFSET) : virt_table_off #
#pragma interface virt_table_off

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(LIST(VIRTUAL)) : virt_table_entries #
#pragma interface virt_table_entries

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(ulong_type) : virt_table_tok #
#pragma interface virt_table_tok

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(ulong_type) : virt_table_tbl #
#pragma interface virt_table_tbl

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(ulong_type) : virt_table_rtti #
#pragma interface virt_table_rtti

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(int) : virt_table_rtti_used #
#pragma interface virt_table_rtti_used

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : ulong_type :,\
	EXP : GRAPH :,\
	EXP : OFFSET :,\
	EXP lvalue : VIRTUAL :\
    ) STATEMENT MAKE_virt_table #
#pragma interface MAKE_virt_table

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(VIRTUAL) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : int :,\
	EXP : VIRTUAL :\
    ) STATEMENT DECONS_virt_table #
#pragma interface DECONS_virt_table

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : OFFSET :,\
	EXP lvalue : LIST(VIRTUAL) :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : int :,\
	EXP : VIRTUAL :\
    ) STATEMENT DESTROY_virt_table #
#pragma interface DESTROY_virt_table


/* Operations for field simple of union VIRTUAL */

#pragma token EXP const : unsigned : virt_simple_tag #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_virt_simple #
#pragma interface virt_simple_tag IS_virt_simple

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : ulong_type :,\
	EXP : GRAPH :,\
	EXP lvalue : VIRTUAL :\
    ) STATEMENT MAKE_virt_simple #
#pragma interface MAKE_virt_simple

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP : VIRTUAL :\
    ) STATEMENT DECONS_virt_simple #
#pragma interface DECONS_virt_simple

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP : VIRTUAL :\
    ) STATEMENT DESTROY_virt_simple #
#pragma interface DESTROY_virt_simple


/* Operations for field override of union VIRTUAL */

#pragma token EXP const : unsigned : virt_override_tag #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_virt_override #
#pragma interface virt_override_tag IS_virt_override

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(GRAPH) : virt_override_ret #
#pragma interface virt_override_ret

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(IDENTIFIER) : virt_override_orig #
#pragma interface virt_override_orig

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(GRAPH) : virt_override_src #
#pragma interface virt_override_src

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : ulong_type :,\
	EXP : GRAPH :,\
	EXP : GRAPH :,\
	EXP : IDENTIFIER :,\
	EXP : GRAPH :,\
	EXP lvalue : VIRTUAL :\
    ) STATEMENT MAKE_virt_override #
#pragma interface MAKE_virt_override

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : GRAPH :,\
	EXP : VIRTUAL :\
    ) STATEMENT DECONS_virt_override #
#pragma interface DECONS_virt_override

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : GRAPH :,\
	EXP : VIRTUAL :\
    ) STATEMENT DESTROY_virt_override #
#pragma interface DESTROY_virt_override


/* Operations for field inherit of union VIRTUAL */

#pragma token EXP const : unsigned : virt_inherit_tag #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_virt_inherit #
#pragma interface virt_inherit_tag IS_virt_inherit

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : ulong_type :,\
	EXP : GRAPH :,\
	EXP lvalue : VIRTUAL :\
    ) STATEMENT MAKE_virt_inherit #
#pragma interface MAKE_virt_inherit

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP : VIRTUAL :\
    ) STATEMENT DECONS_virt_inherit #
#pragma interface DECONS_virt_inherit

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP : VIRTUAL :\
    ) STATEMENT DESTROY_virt_inherit #
#pragma interface DESTROY_virt_inherit


/* Operations for field complex of union VIRTUAL */

#pragma token EXP const : unsigned : virt_complex_tag #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_virt_complex #
#pragma interface virt_complex_tag IS_virt_complex

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(GRAPH) : virt_complex_ret #
#pragma interface virt_complex_ret

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(IDENTIFIER) : virt_complex_orig #
#pragma interface virt_complex_orig

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(GRAPH) : virt_complex_src #
#pragma interface virt_complex_src

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : ulong_type :,\
	EXP : GRAPH :,\
	EXP : GRAPH :,\
	EXP : IDENTIFIER :,\
	EXP : GRAPH :,\
	EXP lvalue : VIRTUAL :\
    ) STATEMENT MAKE_virt_complex #
#pragma interface MAKE_virt_complex

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : GRAPH :,\
	EXP : VIRTUAL :\
    ) STATEMENT DECONS_virt_complex #
#pragma interface DECONS_virt_complex

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : GRAPH :,\
	EXP : VIRTUAL :\
    ) STATEMENT DESTROY_virt_complex #
#pragma interface DESTROY_virt_complex


/* Operations for field link of union VIRTUAL */

#pragma token EXP const : unsigned : virt_link_tag #
#pragma token PROC(EXP : VIRTUAL :) EXP : int : IS_virt_link #
#pragma interface virt_link_tag IS_virt_link

#pragma token PROC(EXP : VIRTUAL :)\
    EXP : PTR(PTR(VIRTUAL)) : virt_link_to #
#pragma interface virt_link_to

#pragma token PROC(\
	EXP : IDENTIFIER :,\
	EXP : ulong_type :,\
	EXP : GRAPH :,\
	EXP : PTR(VIRTUAL) :,\
	EXP lvalue : VIRTUAL :\
    ) STATEMENT MAKE_virt_link #
#pragma interface MAKE_virt_link

#pragma token PROC(\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : PTR(VIRTUAL) :,\
	EXP : VIRTUAL :\
    ) STATEMENT DECONS_virt_link #
#pragma interface DECONS_virt_link

#pragma token PROC(\
	EXP : DESTROYER :,\
	EXP lvalue : IDENTIFIER :,\
	EXP lvalue : ulong_type :,\
	EXP lvalue : GRAPH :,\
	EXP lvalue : VIRTUAL :,\
	EXP lvalue : PTR(VIRTUAL) :,\
	EXP : VIRTUAL :\
    ) STATEMENT DESTROY_virt_link #
#pragma interface DESTROY_virt_link


#endif
