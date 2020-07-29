# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;

+IF %% __SYSV_ENHANCED_SECURITY %%

+USE "svid/svid3", "sys/types.h.ts" ;
+USE "svid/svid3", "sys/ipc.h.ts" ;

+CONST int DEV_GET, DEV_SET, DEV_PRIVATE, DEV_PUBLIC, DEV_STATIC ;
+CONST int DEV_DYNAMIC, DEV_PERSISTENT, DEV_LASTCLOSE, DEV_SYSTEM ;
+CONST int MAC_GET, MAC_SET ;
+CONST int LVL_ALIAS, LVL_FULL ;
+CONST int MLD_QUERY, MLD_REAL, MLD_VIRT ;

+TYPE struct dev_alloca ;
/* No fields specified */

+FIELD struct devstat | devstat_struct {
    unsigned short dev_state ;
    unsigned short dev_mode ;
    level_t dev_hilevel ;
    level_t dev_lolevel ;
    unsigned short dev_usecount ;
    unsigned short dev_relflag ;
} ;

+FUNC int devalloc ( const char *, int, struct dev_alloca * ) ;
+FUNC int devdealloc ( const char * ) ;
+FUNC int devstat ( const char *, int, struct devstat * ) ;
+FUNC int lvldom ( level_t *, level_t * ) ;
+FUNC int lvlequal ( level_t *, level_t * ) ;
+FUNC int lvlfile ( char *, int, level_t * ) ;
+FUNC int lvlin ( char *, level_t * ) ;
+FUNC int lvlipc ( int, int, int, level_t * ) ;
+FUNC int lvlout ( level_t *, char *, int, int ) ;
+FUNC int lvlproc ( int, level_t * ) ;
+FUNC int lvlvalid ( level_t * ) ;
+FUNC int lvlvfs ( char *, int, level_t * ) ;
+FUNC int mkmld ( const char *, mode_t ) ;
+FUNC int mldmode ( int ) ;

+ENDIF
