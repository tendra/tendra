# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_TERMINAL_INTERFACE %%
+TYPE ( int ) OPTIONS ;
+CONST int MAX_COMMAND ;
+CONST int E_OK, E_BAD_ARGUMENT, E_BAD_STATE, E_CONNECTED, E_CURRENT ;
+CONST int E_INVALID_FIELD, E_NOT_CONNECTED, E_NOT_POSTED, E_NOT_SELECTABLE ;
+CONST int E_NO_MATCH, E_NO_ROOM, E_POSTED, E_REQUEST_DENIED, E_SYSTEM_ERROR ;
+CONST int E_UNKNOWN_COMMAND ;
+ENDIF
