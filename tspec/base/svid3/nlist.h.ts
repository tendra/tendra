# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IF %% __SYSV_SOFTWARE_DEVELOPMENT %%
+TYPE struct nlist | nlist_struct ;
/* No fields specified */
+FUNC int nlist ( const char *, struct nlist * ) ;
+ENDIF
