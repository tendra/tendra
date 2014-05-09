# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "sys/types.h.ts", "guid" ;
+IMPLEMENT "posix/posix", "sys/types.h.ts", "mode_t" ;
+IMPLEMENT "cae/xpg3", "sys/types.h.ts", "key_t" ;

+IMPLEMENT "cae/xsh4-base", "sys/ipc.h.ts" ;

+FUNC key_t ftok ( const char *, int ) ;
