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
# CAE, Networking Services, Issue 4

+USE "unix95", "sys/socket.h" ;
+IMPLEMENT "unix95", "sys/socket.h", "sa_family_t" ;

+SUBSET "in_t" := {
    +TYPE ( unsigned ) in_port_t ;	# 16 bits
    +TYPE ( unsigned ) in_addr_t ;	# 32 bits
} ;

+FIELD struct in_addr {
    in_addr_t s_addr ;
} ;

+FIELD struct sockaddr_in {
    sa_family_t sin_family ;
    in_port_t sin_port ;
    struct in_addr sin_addr ;
    unsigned char sin_zero [ 8 ] ;
} ;

# level of getsockopt and setsockopt
+CONST int IPPROTO_IP, IPPROTO_ICMP, IPPROTO_TCP, IPPROTO_UDP ;

# destination addresses
+EXP const struct sockaddr * INADDR_ANY ;
+EXP const struct sockaddr * INADDR_BROADCAST ;
