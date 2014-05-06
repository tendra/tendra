# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


$SOURCENAME = "rpc/rpc_types.h.ts" ;
+USE "svid/svid3", "sys/types.h.ts" (?!) ;
+IF %% __SYSV_REMOTE_SERVICES %%
+TYPE bool_t, enum_t ;
+ENDIF
