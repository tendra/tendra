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
+NAT ~utsname_sysname_size ;
+NAT ~utsname_nodename_size ;
+NAT ~utsname_release_size ;
+NAT ~utsname_version_size ;
+NAT ~utsname_machine_size ;

+TYPE struct utsname ;
+FIELD struct utsname {
    char sysname [ ~utsname_sysname_size ] ;
    char nodename [ ~utsname_nodename_size ] ;
    char release [ ~utsname_release_size ] ;
    char version [ ~utsname_version_size ] ;
    char machine [ ~utsname_machine_size ] ;
} ;

+FUNC int uname ( struct utsname * ) ;
