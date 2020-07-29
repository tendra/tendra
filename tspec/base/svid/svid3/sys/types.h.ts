# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IMPLEMENT "cae/xpg3", "sys/types.h.ts", "caddr_t" ;
+IMPLEMENT "cae/xpg3", "sys/types.h.ts" ;

+TYPE ( signed ) ssize_t ;

/* Inferred */
+TYPE ( int ) ~addr_t ;
+TYPEDEF ~addr_t *addr_t ;
+TYPE daddr_t ;

+IF %% __SYSV_ENHANCED_SECURITY || __SYSV_AUDITING_EXTENSION %%
+TYPE level_t ;
+ENDIF
