# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "cae/xpg3", "sys/stat.h.ts", "st_proto" ;

+CONST int FTW_F, FTW_D, FTW_DNR, FTW_NS ;
+FUNC int ftw ( const char *,
    int (*) ( const char *, const struct stat *, int ), int ) ;
