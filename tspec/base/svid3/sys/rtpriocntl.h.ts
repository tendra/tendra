# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IF %% __SYSV_REAL_TIME %%
+USE "svid3", "sys/types.h.ts" (?!) ;

+CONST long RT_NOCHANGE, RT_TQINF, RT_TQDEF ;

+FIELD ( struct ) rtinfo_t {
    short rt_maxpri ;
} ;

+FIELD ( struct ) rtparms_t {
    short rt_pri ;
    unsigned long rt_tqsecs ;
    long rt_tqnsecs ;
} ;

+ENDIF
