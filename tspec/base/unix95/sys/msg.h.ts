# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;
+IMPLEMENT "posix", "sys/types.h.ts", "pid_t" ;

# don't really need this
+IMPLEMENT "xpg3", "sys/types.h.ts", "key_t" ;

+IMPLEMENT "unix95", "sys/ipc.h.ts" ;

+IMPLEMENT "xpg4", "sys/msg.h.ts" ;

