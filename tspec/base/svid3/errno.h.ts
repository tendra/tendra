# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IMPLEMENT "c/c89", "errno.h.ts" ;
+IMPLEMENT "xpg3", "errno.h.ts", "enums" ;

+CONST int EBADMSG, ELIBACC, ELIBBAD, ELIBEXEC, ELIBMAX, ELIBSCN, ELOOP ;
+CONST int ENOSR, ENOSTR, EOVERFLOW, EPROTO, ERESTART, ESTRPIPE, ETIME ;

+IF %% __SYSV_REMOTE_SERVICES %%
+CONST int ECOMM, EMULTIHOP, ENOLINK, EREMOTE, ESTALE ;
+ENDIF
