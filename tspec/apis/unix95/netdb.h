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

+USE "ansi", "stddef.h", "size_t" (!?) ;
+IMPLEMENT "unix95", "netinet/in.h", "in_t" ;

+FIELD struct hostent {
    char *h_name ;
    char **h_aliases ;
    int h_addrtype ;
    int h_length ;
    char **h_addr_list ;
} ;

+FIELD struct netent {
    char *n_name ;
    char **n_aliases ;
    int n_addrtype ;
    in_addr_t n_net ;
} ;

+FIELD struct protoent {
    char *p_name ;
    char **p_aliases ;
    int p_proto ;
} ;

+FIELD struct servent {
    char *s_name ;
    char **s_aliases ;
    int s_port ;
    char *s_proto ;
} ;

+CONST int IPPORT_RESERVED ;

+EXP (extern) int h_errno ;

+CONST int HOST_NOT_FOUND, NO_DATA, NO_RECOVERY, TRY_AGAIN ;

+FUNC void endhostent ( void ) ;
+FUNC void endnetent ( void ) ;
+FUNC void endprotoent ( void ) ;
+FUNC void endservent ( void ) ;
+FUNC struct hostent *gethostbyaddr ( const void *, size_t, int ) ;
+FUNC struct hostent *gethostbyname ( const char * ) ;
+FUNC struct hostent *gethostent ( void ) ;
+FUNC struct netent *getnetbyaddr ( in_addr_t, int ) ;
+FUNC struct netent *getnetbyname ( const char * ) ;
+FUNC struct netent *getnetent ( void ) ;
+FUNC struct protoent *getprotobyname ( const char * ) ;
+FUNC struct protoent *getprotobynumber ( int ) ;
+FUNC struct protoent *getprotoent ( void ) ;
+FUNC struct servent *getservbyname ( const char *, const char * ) ;
+FUNC struct servent *getservbyport ( int, const char * ) ;
+FUNC struct servent *getservent ( void ) ;
+FUNC void sethostent ( int ) ;
+FUNC void setnetent ( int ) ;
+FUNC void setprotoent ( int ) ;
+FUNC void setservent ( int ) ;
