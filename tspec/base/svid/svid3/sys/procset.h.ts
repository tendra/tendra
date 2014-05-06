# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+USE "svid/svid3", "sys/types.h.ts" (?!) ;

+TYPE ( int ) id_t ;
+CONST id_t P_MYID ;

+TYPE ( int ) idtype_t ;
+CONST idtype_t P_PID, P_PPID, P_PGID, P_SID, P_UID, P_GID, P_CID, P_ALL ;

+TYPE ( int ) idop_t ;
+CONST idop_t POP_DIFF, POP_AND, POP_OR, POP_XOR ;

+FIELD ( struct ) procset_t {
    idop_t p_op ;
    idtype_t p_lidtype ;
    id_t p_lid ;
    idtype_t p_ridtype ;
    id_t p_rid ;
} ;

+FUNC int sigsend  ( idtype_t, id_t, int ) ;
+FUNC int sigsendset ( const procset_t *, int ) ;
