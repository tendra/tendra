# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_REMOTE_SERVICES %%
+IF %% __SYSV_UPDATE %%

+USE "svid/svid3", "netconfig.h.ts" ;
+USE "svid/svid3", "tiuser.h.ts" ;

+TYPE struct csopts ;
+FIELD struct csopts {
    struct netconfig *nc_p ;
    int nd_opt ;
    struct netbuf *nb_p ;
} ;

+FUNC int cs_connect ( char *, char *, struct csopts *, int * ) ;
+FUNC void cs_perror ( char *, int ) ;

+ENDIF
+ENDIF
