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
+IF %% __SYSV_REAL_TIME %%

+USE "svid3", "sys/types.h" ;
+USE "svid3", "sys/procset.h" ;

+CONST int PC_GETCID, PC_GETCLINFO, PC_SETPARMS, PC_GETPARMS ;
+CONST id_t PC_CLNULL ;

+CONST int PC_CLNMSZ, PC_CLINFOSZ ;
+NAT ~PC_CLNMSZ, ~PC_CLINFOSZ ;

+FIELD ( struct ) pcinfo_t {
    id_t pc_cid ;
    char pc_clname [ ~PC_CLNMSZ ] ;
    long pc_clinfo [ ~PC_CLINFOSZ ] ;
} ;

+CONST int PC_CLPARMSZ ;
+NAT ~PC_CLPARMSZ ;

+FIELD ( struct ) pcparms_t {
    id_t pc_cid ;
    long pc_clparms [ ~PC_CLPARMSZ ] ;
} ;

+FUNC long priocntl ( idtype_t, id_t, int, ... ) ;

+ENDIF
