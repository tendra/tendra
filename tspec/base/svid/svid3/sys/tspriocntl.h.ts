# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_REAL_TIME %%

+CONST int TS_NOCHANGE ;

+FIELD ( struct ) tsinfo_t {
    short ts_maxupri ;
} ;

+FIELD ( struct ) tsparms_t {
    short ts_uprilim ;
    short ts_upri ;
} ;

+ENDIF
