# $Id$

# Copyright 2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.



#
# TOKEN DECLARATIONS
#
# The following standard tokens are declared.
#

( make_tokdec ~comp_off ( exp ) exp )
( make_tokdec ~cpp.pmf.type shape )
( make_tokdec ~cpp.typeid.type shape )
( make_tokdec ~cpp.offset.div ( exp ) exp )
( make_tokdec ~cpp.vtab.diag shape )
( make_tokdec ~signed_short variety )
( make_tokdec ~signed_int variety )
( make_id_tagdec __TCPPLUS_pure proc )


#
# VIRTUAL FUNCTION TABLE TYPE DEFINITION
#
# These tokens describe the type representing a virtual function table.
# This is basically the same as the type VTABLE defined in implement.h but
# the size of the table, n, is provided as a token argument.
#

( local make_tokdef extra.rtti
    exp
    ( offset_zero ( alignment ( pointer ( alignment top ) ) ) ) )

( local make_tokdef extra.off
    exp
    ( offset_pad
	( alignment ( integer ~signed_short ) )
	( offset_add
	    extra.rtti
	    ( shape_offset
		( pointer ( alignment ~cpp.typeid.type ) ) ) ) ) )

( local make_tokdef extra
    shape
    ( compound
	( ~comp_off
	    ( offset_add
		extra.off
		( shape_offset
		    ( integer ~signed_short ) ) ) ) ) )

( make_tokdef ~cpp.vtab.type
    ( nat n ) shape
    ( compound
	( ~comp_off
	    ( offset_max
		( shape_offset
		    ( nof n ~cpp.pmf.type ) )
		( shape_offset extra ) ) ) ) )


#
# CONSTRUCT A VIRTUAL FUNCTION TABLE
#
# This token constructs a virtual function table of size n consisting of
# the run-time type information r, the offset a and the pointer to member
# functions f.
#

( make_tokdef ~cpp.vtab.make
    ( exp r exp a nat n exp f ) exp
    ( make_compound
	( shape_offset ( ~cpp.vtab.type n ) )
	( offset_zero ( alignment extra ) )
	( make_compound
	    ( shape_offset extra )
	    extra.rtti
	    r
	    extra.off
	    ( change_variety impossible ~signed_short
		( negate wrap ( ~cpp.offset.div a ) ) ) )
	( offset_pad
	    ( alignment ~cpp.pmf.type )
	    ( shape_offset ~cpp.pmf.type ) )
	f ) )


#
# FIND A VIRTUAL FUNCTION TABLE ENTRY
#
# These tokens gives a pointer to the nth pointer to member function in the
# virtual function table t.
#

( make_tokdef ~cpp.vtab.func_exp
    ( exp t exp n ) exp
    ( add_to_ptr
	( contents
	    ( pointer ( alignment ~cpp.vtab.diag ) )
	    t )
	( offset_mult
	    ( offset_pad
		( alignment ~cpp.pmf.type )
		( shape_offset ~cpp.pmf.type ) )
		n ) ) )

( make_tokdef ~cpp.vtab.func
    ( exp t signed_nat n ) exp
    ( ~cpp.vtab.func_exp t ( make_int ~signed_int n ) ) )

( make_tokdef ~cpp.vtab.off
    ( signed_nat n ) exp
    ( offset_mult
	( offset_pad
	    ( alignment ~cpp.pmf.type )
	    ( shape_offset ~cpp.pmf.type ) )
	    ( make_int ~signed_int n ) ) )


#
# FIND RUN-TIME TYPE INFORMATION
#
# This token gives the run-time type information structure associated
# with the virtual function table t.
#

( make_tokdef ~cpp.typeid.ref
    ( exp t ) exp
    ( contents
	( pointer ( alignment ~cpp.typeid.type ) )
	( add_to_ptr
	    ( contents
		( pointer ( alignment ~cpp.vtab.diag ) )
		t )
	    extra.rtti ) ) )


#
# PURE VIRTUAL FUNCTION
#
# This token gives the function pointer used in the entry for a pure virtual 
# in a virtual function table.
#

( make_tokdef ~cpp.vtab.pure
    exp
    ( obtain_tag __TCPPLUS_pure ) )
