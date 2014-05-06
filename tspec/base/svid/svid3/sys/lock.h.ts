# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_KERNEL_EXTENSION %%
+CONST int PROCLOCK, TXTLOCK, DATLOCK, UNLOCK ;
+FUNC int plock ( int ) ;
+ENDIF
