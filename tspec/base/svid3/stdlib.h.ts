# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "c/c89", "stdlib.h.ts" ;
+IMPLEMENT "posix", "unistd.h.ts", "getopt" (!?) ;
+IMPLEMENT "xpg3", "stdlib.h.ts", "putenv" ;
+FUNC int getsubopt ( char **, char * [], char ** ) ;
+FUNC char *mktemp ( char * ) ;
