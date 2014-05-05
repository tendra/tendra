# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix", "sys/stat.h.ts" ;

+SUBSET "st_proto" := {
    +USE "xpg3", "sys/types.h.ts" ;

    +FIELD struct stat {
	dev_t st_rdev ;
    } ;

    +CONST int S_IFMT, S_IFBLK, S_IFCHR, S_IFDIR, S_IFIFO, S_IFREG ;
} ;

+SUBSET "s_isvtx" := {
    +CONST int S_ISVTX ;	# not in xpg4, but back again in cose
} ;
