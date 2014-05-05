# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "sys/types.h.ts", "guid" ;
+IMPLEMENT "posix", "sys/types.h.ts", "mode_t" ;
+IMPLEMENT "xpg3", "sys/types.h.ts", "key_t" ;

+IMPLEMENT "xpg4", "sys/ipc.h.ts" ;

+FUNC key_t ftok ( const char *, int ) ;
