# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


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
