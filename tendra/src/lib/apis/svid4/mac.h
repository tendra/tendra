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

+IF %% __SYSV_ENHANCED_SECURITY %%

+USE "svid3", "sys/types.h" ;
+USE "svid3", "sys/ipc.h" ;

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
