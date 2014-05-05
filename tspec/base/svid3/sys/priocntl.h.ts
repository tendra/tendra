# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IF %% __SYSV_REAL_TIME %%

+USE "svid3", "sys/types.h.ts" ;
+USE "svid3", "sys/procset.h.ts" ;

+CONST int PC_GETCID, PC_GETCLINFO, PC_SETPARMS, PC_GETPARMS ;
+CONST id_t PC_CLNULL ;

+CONST int PC_CLNMSZ, PC_CLINFOSZ ;
+NAT ~PC_CLNMSZ, ~PC_CLINFOSZ ;

+FIELD ( struct ) pcinfo_t {
    id_t pc_cid ;
    char pc_clname [ ~PC_CLNMSZ ] ;
    long pc_clinfo [ ~PC_CLINFOSZ ] ;
} ;

+CONST int PC_CLPARMSZ ;
+NAT ~PC_CLPARMSZ ;

+FIELD ( struct ) pcparms_t {
    id_t pc_cid ;
    long pc_clparms [ ~PC_CLPARMSZ ] ;
} ;

+FUNC long priocntl ( idtype_t, id_t, int, ... ) ;

+ENDIF
