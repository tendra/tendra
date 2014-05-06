# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "time.h.ts" ;

+SUBSET "timeval" := {
    # Duplicated in a number of places
    $PROTECT = "__TDF_STRUCT_TIMEVAL" ;

    +TYPE (int) ~tv_sec_t ;
    +TYPE (int) ~tv_usec_t ;
    +FIELD struct timeval {
	~tv_sec_t tv_sec ;
	~tv_usec_t tv_usec ;
    } ;
} ;
