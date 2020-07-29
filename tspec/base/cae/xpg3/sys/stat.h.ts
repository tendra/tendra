# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+IMPLEMENT "posix/posix", "sys/stat.h.ts" ;

+SUBSET "st_proto" := {
    +USE "cae/xpg3", "sys/types.h.ts" ;

    +FIELD struct stat {
	dev_t st_rdev ;
    } ;

    +CONST int S_IFBLK, S_IFCHR, S_IFDIR, S_IFIFO, S_IFREG ;
} ;

+SUBSET "s_ifmt" := {
	+CONST int S_IFMT ; # XSH4 leaves this to XNS4 only. Is the same true for XPG3?
} ;

+SUBSET "s_isvtx" := {
    +CONST int S_ISVTX ;	# not in xpg4, but back again in cose
} ;
