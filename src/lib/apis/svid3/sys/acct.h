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
+IF %% __SYSV_KERNEL_EXTENSION %%
+USE "svid3", "sys/types.h" ;

+TYPE ( arith ) comp_t ;
+FIELD struct acct | acct_struct {
    char ac_flag ;
    char ac_stat ;
    uid_t ac_uid ;
    gid_t ac_gid ;
    dev_t ac_tty ;
    time_t ac_btime ;
    comp_t ac_utime ;
    comp_t ac_stime ;
    comp_t ac_etime ;
    comp_t ac_mem ;
    comp_t ac_io ;
    comp_t ac_rw ;
    char ac_comm [8] ;
} ;

+CONST int AFORK, ASU, ACCTF ;
+FUNC int acct ( const char * ) ;
+ENDIF
