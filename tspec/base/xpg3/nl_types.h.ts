# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# catopen() nl_catd result comparable with (nl_catd)-1, so not opaque 
+TYPE nl_item ;
+TYPE ( scalar ) nl_catd ;

+CONST int NL_SETD ;

+FUNC int catclose ( nl_catd ) ;
+FUNC char *catgets ( nl_catd, int, int, const char * ) ;
+FUNC nl_catd catopen ( const char *, int ) ;
