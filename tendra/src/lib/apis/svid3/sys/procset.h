#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
+USE "svid3", "", "config" ;
+USE "svid3", "sys/types.h" (?!) ;

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
