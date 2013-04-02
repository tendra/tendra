# $Id$

# Copyright 2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.



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
