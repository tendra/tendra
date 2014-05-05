# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "sys/types.h.ts" ;
+USE "svid3", "siginfo.h.ts" ;
+USE "svid3", "sys/procset.h.ts" ;

+FUNC int waitid ( idtype_t, id_t, siginfo_t *, int ) ;
