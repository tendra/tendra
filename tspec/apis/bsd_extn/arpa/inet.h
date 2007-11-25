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
+USE "bsd_extn", "sys/types.h" ;
+USE "bsd_extn", "netinet/in.h" ;

+FUNC unsigned long inet_addr ( const char * ) ;
+FUNC unsigned long inet_network ( const char * ) ;
+FUNC struct in_addr inet_makeaddr ( int, int ) ;
+FUNC unsigned long inet_lnaof ( struct in_addr ) ;
+FUNC unsigned long inet_netof ( struct in_addr ) ;
+FUNC char *inet_ntoa ( struct in_addr ) ;
