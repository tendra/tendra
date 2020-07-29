# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_KERNEL_EXTENSION %%
+USE "svid/svid3", "sys/types.h.ts" ;

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
