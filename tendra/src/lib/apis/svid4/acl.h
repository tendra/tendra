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

+CONST int USER_OBJ, USER, GROUP_OBJ, GROUP, CLASS_OBJ, OTHER_OBJ ;
+CONST int DEF_USER_OBJ, DEF_USER, DEF_GROUP_OBJ, DEF_GROUP ;
+CONST int DEF_CLASS_OBJ, DEF_OTHER_OBJ ;
+CONST int ACL_SET, ACL_GET, ACL_CNT ;

+FIELD struct acl | acl_struct {
    int a_type ;
    uid_t a_id ;
    unsigned short a_perm ;
} ;

+FUNC int acl ( char *, int, int, struct acl * ) ;
+FUNC int aclipc ( int, int, int, int, struct acl * ) ;
+FUNC int aclsort ( int, int, struct acl * ) ;

+ENDIF
