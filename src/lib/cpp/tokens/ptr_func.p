#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#


#
# STANDARD TOKEN DECLARATIONS
#
# The following tokens need to be declared.
#

( make_tokdec ~comp_off ( exp ) exp )
( make_tokdec ~ptr_to_ptr ( alignment alignment exp ) exp )
( make_tokdec ~char variety )
( make_tokdec ~signed_int variety )
( make_tokdec ~signed_short variety )
( make_tokdec ~cpp.offset.div ( exp ) exp )
( make_tokdec ~cpp.offset.mult ( alignment exp ) exp )
( make_tokdec ~cpp.vtab.func_exp ( exp exp ) exp )
( make_tokdec ~cpp.vtab.diag shape )


#
# POINTER TO MEMBER FUNCTION TYPE
#
# This token gives the type of a pointer to member function.
#

( local make_tokdef union
    shape
    ( compound
	( ~comp_off
	    ( offset_max
		( shape_offset proc )
		( shape_offset ( integer ~signed_short ) ) ) ) ) )

( local make_tokdef delta
    exp
    ( offset_zero ( alignment ( integer ~signed_short ) ) ) )

( local make_tokdef index
    exp
    ( offset_pad
	( alignment ( integer ~signed_short ) )
	( offset_add
	    delta
	    ( shape_offset ( integer ~signed_short ) ) ) ) )

( local make_tokdef func
    exp
    ( offset_pad
	( alignment union )
	( offset_add
	    index
	    ( shape_offset ( integer ~signed_short ) ) ) ) )

( local make_tokdef ptr_mem_func
    shape
    ( compound
	( ~comp_off
	    ( offset_add
		func
		( shape_offset union ) ) ) ) )


#
# NULL POINTER TO MEMBER FUNCTION
#
# These tokens gives the value of the null pointer to member function.
# There are two of them to work round an installer bug.
#

( make_tokdef ~cpp.pmf.null
    exp
    ( make_compound
	( shape_offset ptr_mem_func )
	delta
	( make_int ~signed_short 0 )
	index
	( make_int ~signed_short 0 )
	func
	( make_compound
	    ( shape_offset union )
	    ( offset_zero ( alignment proc ) )
	    make_null_proc ) ) )

( make_tokdef ~cpp.pmf.null2
    exp
    ( make_compound
	( shape_offset ptr_mem_func )
	delta
	( make_int ~signed_short 0 )
	index
	( make_int ~signed_short 0 )
	func
	( make_compound
	    ( shape_offset union )
	    ( offset_zero ( alignment proc ) )
	    make_null_proc ) ) )


#
# CONSTRUCT A POINTER TO MEMBER FUNCTION
#
# These tokens construct a pointer to member function expression.
# There are two cases, one for non-virtual functions and one for
# virtual functions.
#

( make_tokdef ~cpp.pmf.make
    ( exp a exp b exp c ) exp
    ( make_compound
	( shape_offset ptr_mem_func )
	delta
	( change_variety impossible ~signed_short
	    ( minus wrap
		( ~cpp.offset.div b )
		( ~cpp.offset.div c ) ) )
	index
	( make_int ~signed_short -1 )
	func
	( make_compound
	    ( shape_offset union )
	    ( offset_zero ( alignment proc ) )
	    a ) ) )

( make_tokdef ~cpp.pmf.vmake
    ( signed_nat a exp b exp c exp d ) exp
    ( make_compound
	( shape_offset ptr_mem_func )
	delta
	( change_variety impossible ~signed_short
	    ( minus wrap
		( ~cpp.offset.div c )
		( ~cpp.offset.div d ) ) )
	index
	( make_int ~signed_short a )
	func
	( make_compound
	    ( shape_offset union )
	    ( offset_zero ( alignment ( integer ~signed_short ) ) )
	    ( change_variety impossible ~signed_short
		( ~cpp.offset.div b ) ) ) ) )


#
# DECONSTRUCT A POINTER TO MEMBER FUNCTION
#
# These tokens give the various components of the pointer to member
# function a.
#

( make_tokdef ~cpp.pmf.func
    ( exp a ) exp
    ( contents proc ( add_to_ptr a func ) ) )

( local make_tokdef ~cpp.pmf.index
    ( exp a ) exp
    ( change_variety impossible ~signed_int
	( contents ( integer ~signed_short )
	    ( add_to_ptr a index ) ) ) )

( make_tokdef ~cpp.pmf.delta
    ( alignment a exp b ) exp
    ( ~cpp.offset.mult a
	( change_variety impossible ~signed_int
	    ( contents ( integer ~signed_short )
		( add_to_ptr b delta ) ) ) ) )

( local make_tokdef ~cpp.pmf.voff
    ( exp a ) exp
    ( change_variety impossible ~signed_int
	( contents ( integer ~signed_short )
	    ( add_to_ptr a func ) ) ) )


#
# FIND AN ACTUAL POINTER TO MEMBER FUNCTION
#
# This token modifies the pointer to member function expression a if it
# represents a virtual function by indexing into the virtual function
# for the pointer b of alignment c.
#

( make_tokdef ~cpp.pmf.virt
    ( exp a exp b alignment c ) exp
    ( identify i
	( ~cpp.pmf.index a )
	( conditional lab
	    ( sequence
		( integer_test greater_than lab
		    ( obtain_tag i )
		    ( make_int ~signed_int 0 ) )
		( assign a
		    ( contents ptr_mem_func
			( ~cpp.vtab.func_exp
			    ( add_to_ptr
				( ~ptr_to_ptr
				    c
				    ( alignment ~cpp.vtab.diag )
				    b )
				    ( ~cpp.offset.mult
					( alignment ~cpp.vtab.diag )
					( ~cpp.pmf.voff a ) ) )
			    ( obtain_tag i ) ) ) ) )
	    make_top ) ) )


#
# POINTER TO MEMBER FUNCTION TEST
#
# These tokens describe how to compare two pointer to member functions a
# and b and how to compare a against the null pointer to member function.
# Note that a and b are evaluated more than once in the comparison token,
# therefore it may be necessary to introduce an identity before calling it.
#

( make_tokdef ~cpp.pmf.compare
    ( exp a exp b label lab ntest n ) exp
    ( identify i
	( ~cpp.pmf.index a )
	( variable flag
	    ( make_int ~signed_int 0 )
	    ( sequence
		( conditional lab1
		    ( sequence
			( integer_test equal lab1
			    ( obtain_tag i )
			    ( ~cpp.pmf.index b ) )
			( offset_test equal lab1
			    ( ~cpp.pmf.delta
				( alignment ( integer ~char ) ) a )
			    ( ~cpp.pmf.delta
				( alignment ( integer ~char ) ) b ) )
			( conditional lab2
			    ( sequence
				( integer_test less_than lab2
				    ( obtain_tag i )
				    ( make_int ~signed_int 0 ) )
				( proc_test not_equal lab2
				    ( ~cpp.pmf.func a )
				    ( ~cpp.pmf.func b ) ) )
			    ( assign
				( obtain_tag flag )
				( make_int ~signed_int 1 ) ) ) )
		    make_top )
		( integer_test n lab
		    ( contents
			( integer ~signed_int )
			( obtain_tag flag ) )
		    ( make_int ~signed_int 1 ) ) ) ) ) )

( make_tokdef ~cpp.pmf.test
    ( exp a label lab ntest n ) exp
    ( integer_test n lab
	( ~cpp.pmf.index a )
	( make_int ~signed_int 0 ) ) )


#
# POINTER TO MEMBER FUNCTION CASTS
#
# These tokens cast a pointer to member function to or from a base class.
# b gives the base class offset, c gives the virtual function number offset,
# and d gives the offset of the virtual function table.
#

( make_tokdef ~cpp.pmf.cast
    ( exp a exp b exp c exp d ) exp
    ( identify i
	( ~cpp.pmf.index a )
	( conditional lab
	    ( sequence
		( integer_test not_equal lab
		    ( obtain_tag i )
		    ( make_int ~signed_int 0 ) )
		( assign ( add_to_ptr a delta )
		    ( change_variety impossible ~signed_short
			( plus wrap
			    ( change_variety impossible ~signed_int
				( contents ( integer ~signed_short )
				( add_to_ptr a delta ) ) )
			    ( ~cpp.offset.div b ) ) ) )
		( conditional lab2
		    ( sequence
			( integer_test greater_than lab2
			    ( obtain_tag i )
			    ( make_int ~signed_int 0 ) )
			( assign ( add_to_ptr a index )
			    ( change_variety impossible ~signed_short
				( plus wrap ( obtain_tag i ) c ) ) )
			( assign ( add_to_ptr a func )
			    ( change_variety impossible ~signed_short
				( ~cpp.offset.div d ) ) ) )
		    make_top ) )
		make_top ) ) )

( make_tokdef ~cpp.pmf.uncast
    ( exp a exp b exp c exp d ) exp
    ( identify i
	( ~cpp.pmf.index a )
	( conditional lab
	    ( sequence
		( integer_test not_equal lab
		    ( obtain_tag i )
		    ( make_int ~signed_int 0 ) )
		( assign ( add_to_ptr a delta )
		    ( change_variety impossible ~signed_short
			( minus wrap
			    ( change_variety impossible ~signed_int
				( contents ( integer ~signed_short )
				( add_to_ptr a delta ) ) )
			    ( ~cpp.offset.div b ) ) ) )
		( conditional lab2
		    ( sequence
			( integer_test greater_than lab2
			    ( obtain_tag i )
			    ( make_int ~signed_int 0 ) )
			( assign ( add_to_ptr a index )
			    ( change_variety impossible ~signed_short
				( minus wrap ( obtain_tag i ) c ) ) )
			( assign ( add_to_ptr a func )
			    ( change_variety impossible ~signed_short
				( ~cpp.offset.div d ) ) ) )
		    make_top ) )
		make_top ) ) )
