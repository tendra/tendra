# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "xpg4", "sys/ipc.h.ts" ;
+IMPLEMENT "xpg3", "sys/msg.h.ts" ;

/* Define XPG4 hacks in terms of my hacks */
+TYPEDEF ~msg_q_t msgqnum_t ;
+TYPEDEF ~msg_l_t msglen_t ;
