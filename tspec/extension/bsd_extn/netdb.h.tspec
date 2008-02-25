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
+FIELD struct hostent {
    char *h_name ;
    char **h_aliases ;
    int h_addrtype ;
    int h_length ;
    char **h_addr_list ;
} ;

+FUNC struct hostent *gethostent ( void ) ;
+FUNC struct hostent *gethostbyaddr ( const char *, int, int ) ;
+FUNC struct hostent *gethostbyname ( const char * ) ;
+FUNC int sethostent ( int ) ;
+FUNC int endhostent ( void ) ;


+FIELD struct netent {
    char *n_name ;
    char **n_aliases ;
    int n_addrtype ;
    unsigned long n_net ;
} ;

+FUNC struct netent *getnetent ( void ) ;
+FUNC struct netent *getnetbyaddr ( long, int ) ;
+FUNC struct netent *getnetbyname ( const char * ) ;
+FUNC int setnetent ( int ) ;
+FUNC int endnetent ( void ) ;


+FIELD struct protoent {
    char *p_name ;
    char **p_aliases ;
    int p_proto ;
} ;

+FUNC struct protoent *getprotoent ( void ) ;
+FUNC struct protoent *getprotobyname ( const char * ) ;
+FUNC struct protoent *getprotobynumber ( int ) ;
+FUNC int setprotoent ( int ) ;
+FUNC int endprotoent ( void ) ;


+FIELD struct servent {
    char *s_name ;
    char **s_aliases ;
    int s_port ;
    char *s_proto ;
} ;

+FUNC struct servent *getservent ( void ) ;
+FUNC struct servent *getservbyname ( const char *, const char * ) ;
+FUNC struct servent *getservbyport ( int, const char * ) ;
+FUNC int setservent ( int ) ;
+FUNC int endservent ( void ) ;


+FUNC int rcmd ( char **, unsigned short, const char *, const char *, const char *, int * ) ;
+FUNC int rresvport ( int * ) ;
+FUNC int ruserok ( const char *, int, const char *, const char * ) ;
+FUNC int rexec ( char **, unsigned short, const char *, const char *, const char *, int * ) ;
