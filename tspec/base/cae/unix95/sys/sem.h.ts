# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stddef.h.ts", "size_t" ;
+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;
+IMPLEMENT "posix", "sys/types.h.ts", "pid_t" ;

# don't really need this
+IMPLEMENT "cae/xpg3", "sys/types.h.ts", "key_t" ;

+IMPLEMENT "cae/unix95", "sys/ipc.h.ts" ;

+IMPLEMENT "cae/xpg4", "sys/sem.h.ts" ;
