# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "sys/types.h.ts" (!?) ;
+IMPLEMENT "posix/posix", "grp.h.ts";

/* Do these belong here? */
+FUNC int initgroups ( const char *, gid_t ) ;
