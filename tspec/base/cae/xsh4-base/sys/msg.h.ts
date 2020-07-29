# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "time.h.ts", "time_t" ;

+IMPLEMENT "posix/posix", "sys/types.h.ts", "pid_t" ;
+IMPLEMENT "cae/xpg3", "sys/types.h.ts", "key_t" ;
+IMPLEMENT "cae/xpg3", "sys/msg.h.ts" ;

+USE "cae/xsh4-base", "sys/ipc.h.ts" ;

/* Define XPG4 hacks in terms of my hacks */
+TYPEDEF ~msg_q_t msgqnum_t ;
+TYPEDEF ~msg_l_t msglen_t ;
