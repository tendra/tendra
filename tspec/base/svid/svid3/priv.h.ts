# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_ENHANCED_SECURITY %%
+USE "svid/svid3", "sys/types.h.ts" (?!) ;
+CONST int PUTPRV, GETPRV, CNTPRV, SETPRV, CLRPRV ;
+TYPE priv_t ;
+FUNC int filepriv ( const char *, int, priv_t *, int ) ;
+FUNC int procpriv ( int, priv_t *, int ) ;
+FUNC int procprivl ( int, priv_t, ... ) ;
+ENDIF
