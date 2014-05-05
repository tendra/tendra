# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "bsd_extn", "sys/types.h.ts" ;

+SUBSET "timeval" := {
    # Duplicated in a number of places
    $PROTECT = "__TDF_STRUCT_TIMEVAL" ;

    +FIELD struct timeval.1 {
	long tv_sec.1 ;
	long tv_usec.1 ;
    } ;
} ;

+IFDEF ~protect ( "svid3", "sys/types.h.ts" )
+USE ( "svid3" ), "sys/time.h.ts" ;
+ENDIF
