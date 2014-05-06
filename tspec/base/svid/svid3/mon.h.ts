# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_SOFTWARE_DEVELOPMENT %%
+IF 0
/* This is optional */
+TYPE WORD ;
+FUNC void monitor ( int (*) (), int (*) (), WORD *, int, int ) ;
+ENDIF
+ENDIF
