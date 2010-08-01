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
# TOKEN DECLARATIONS
#
# The following standard C tokens are declared.
#

( make_tokdec ~char variety )
( make_tokdec ~signed_int variety )


#
# OFFSET TO INTEGER CONVERSIONS
#
# These tokens are used to convert offsets to and from integers.  The
# latter uses an offset cast to prevent the rounding which would occur
# from a more natural offset_pad expression - the C++ type rules ensure
# correctness.
#

( make_tokdef ~cpp.offset.div
    ( exp a ) exp
    ( offset_div ~signed_int
	( offset_subtract
	    ( offset_pad ( alignment ( integer ~char ) ) a )
	    ( offset_zero ( alignment ( integer ~char ) ) ) )
	( offset_pad
	    ( alignment ( integer ~char ) )
	    ( shape_offset ( integer ~char ) ) ) ) )

( make_tokdef ~cpp.offset.cast
    ( alignment s exp a ) exp
    ( component
	( offset s s )
	( make_compound
	    ( offset_max
		( shape_offset
		    ( offset
			( alignment ( integer ~char ) )
			( alignment ( integer ~char ) ) ) )
		( shape_offset
		    ( offset s s ) ) )
	    ( offset_zero
		( alignment
		    ( offset
			( alignment ( integer ~char ) )
			( alignment ( integer ~char ) ) ) ) )
		a )
	( offset_zero ( alignment ( offset s s ) ) ) ) )

( make_tokdef ~cpp.offset.mult
    ( alignment s exp a ) exp
    ( ~cpp.offset.cast
	s
	( offset_mult
	    ( offset_pad
		( alignment ( integer ~char ) )
		( shape_offset ( integer ~char ) ) )
	    a ) ) )


#
# NULL POINTER TO DATA MEMBER
#
# This token gives the null pointer to data member.
#

( make_tokdef ~cpp.pm.null
    exp
    ( make_int ~signed_int 0 ) )


#
# CONSTRUCT A POINTER TO DATA MEMBER
#
# This token constructs a pointer to data member from the offset
# expression a.  Note that 1 is added to allow for null pointers to
# members.
#

( make_tokdef ~cpp.pm.make
    ( exp a ) exp
    ( plus wrap
	( ~cpp.offset.div a )
	( make_int ~signed_int 1 ) ) )


#
# DECONSTRUCT A POINTER TO DATA MEMBER
#
# This token turns the pointer to data member expression a into an offset
# for a shape of alignment s.  The result is undefined if a is the null
# pointer to member, otherwise 1 needs to be subtracted from a.
#

( make_tokdef ~cpp.pm.offset
    ( exp a alignment s ) exp
	( ~cpp.offset.mult
	    s
	    ( minus wrap a ( make_int ~signed_int 1 ) ) ) )


#
# POINTER TO DATA MEMBER TEST
#
# These tokens are used to compare the pointer to data member expressions
# a and b and to compare a against the null pointer to member.
#

( make_tokdef ~cpp.pm.compare
    ( exp a exp b label lab ntest n ) exp
    ( integer_test n lab a b ) )

( make_tokdef ~cpp.pm.test
    ( exp a label lab ntest n ) exp
    ( integer_test n lab a ( make_int ~signed_int 0 ) ) )


#
# POINTER TO DATA MEMBER CAST
#
# These tokens cast a non-null pointer to data member a by adding or
# subtracting the base class offset b.
#

( make_tokdef ~cpp.pm.cast
    ( exp a exp b ) exp
    ( plus wrap a ( ~cpp.offset.div b ) ) )

( make_tokdef ~cpp.pm.uncast
    ( exp a exp b ) exp
    ( minus wrap a ( ~cpp.offset.div b ) ) )
