# $TenDRA$
#
# Binary / variable definitions for the HP-UX operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).

# XXX: This needs to be tweaked in order to distinguish between 32- and 64-bit.

CRT0?=          /usr/ccs/lib/hpux32/crt0.o
CRT1?=		
CRTI?=		
CRTN?=		
GCRT0?=         
GCRT1?=		
MCRT0?=         

AR?=		/usr/bin/ar
AS?=		/usr/ccs/bin/as
AWK?=		/usr/bin/awk
BASENAME?=	/bin/basename
CAT?=		/bin/cat
CHGRP?=		/bin/chgrp
CHMOD?=		/bin/chmod
CHOWN?=		/bin/chown
CP?=		/bin/cp
CP_ARGS?=	
CUT?=		/bin/cut
DC?=		/bin/dc
DIRNAME?=	/bin/dirname
ECHO?=		/bin/echo
EGREP?=		/bin/egrep
FALSE?=		/bin/false
FILE?=		/bin/file
FIND?=		/bin/find
GREP?=		/bin/grep
GTAR?=		/usr/bin/tar
GUNZIP?=	/usr/bin/gunzip
GUNZIP_ARGS?=	-f
GZCAT?=		# Not a system utility, available through external package.
GZIP?=		# Not a system utility, available through external package.
GZIP_ARGS?=	-9
HEAD?=		/bin/head
ID?=		/bin/id
LDCONFIG?=	
LN?=		/bin/ln
LS?=		/bin/ls
MKDIR?=		/bin/mkdir
MKDIR_ARGS?=	-p
MTREE?=		
MV?=		/bin/mv
PATCH?=		/bin/patch
PAX?=		/usr/bin/pax
PERL?=		/usr/bin/perl
RANLIB?=	/usr/bin/ranlib
RM?=		/bin/rm
RMDIR?=		/bin/rmdir
SED?=		/usr/bin/sed
SETENV?=	/usr/bin/env
SH?=		/bin/sh
SORT?=		/usr/bin/sort
SU?=		/usr/bin/su
TAIL?=		/usr/bin/tail
TEST?=		/bin/test
TOUCH?=		/usr/bin/touch
TR?=		/usr/bin/tr
TRUE?=		/usr/bin/true
TYPE?=		type				# Shell builtin
WC?=		/usr/bin/wc
XARGS?=		/usr/bin/xargs
