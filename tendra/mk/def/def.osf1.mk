# $TenDRA$
#
# Binary / variable definitions for the OSF1/Tru64 operating system.
# OSF1 4.0 and Tru64 5.x symlink /bin -> /usr/bin, so use the end location
# to not incur namei lookups on the symbolic links.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).

CRT0?=		/usr/lib/cmplrs/cc/crt0.o
CRT1?=		
CRTI?=		
CRTN?=		
GCRT0?=		/usr/lib/cmplrs/cc/gcrt0.o
GCRT1?=		
MCRT0?=		/usr/lib/cmplrs/cc/mcrt0.o

AR?=		/usr/bin/ar
AS?=		/usr/bin/as
AWK?=		/usr/bin/awk
BASENAME?=	/usr/bin/basename
CAT?=		/usr/bin/cat
CHGRP?=		/usr/bin/chgrp
CHMOD?=		/usr/bin/chmod
CHOWN?=		/usr/sbin/chown
CP?=		/usr/bin/cp
CP_ARGS?=	
CUT?=		/usr/bin/cut
DC?=		/usr/bin/dc
DIRNAME?=	/usr/bin/dirname
ECHO?=		/usr/bin/echo
EGREP?=		/usr/bin/egrep
FALSE?=		/usr/bin/false
FILE?=		/usr/bin/file
FIND?=		/usr/bin/find
GREP?=		/usr/bin/grep
GTAR?=		/usr/bin/tar
GUNZIP?=	/usr/bin/gunzip
GUNZIP_ARGS?=	-f
GZCAT?=		/usr/bin/gzcat
GZIP?=		/usr/bin/gzip
GZIP_ARGS?=	-nf -9
HEAD?=		/usr/bin/head
ID?=		/usr/bin/id
LDCONFIG?=
LN?=		/usr/bin/ln
LS?=		/usr/bin/ls
MKDIR?=		/usr/bin/mkdir
MKDIR_ARGS?=	-p
MTREE?=
MV?=		/usr/bin/mv
PATCH?=		/usr/bin/patch
PAX?=		/usr/bin/pax
PERL?=		/usr/bin/perl
RANLIB?=	/usr/bin/ranlib
RM?=		/usr/bin/rm
RMDIR?=		/usr/bin/rmdir
SED?=		/usr/bin/sed
SETENV?=	/usr/bin/env
SH?=		/usr/bin/sh
SORT?=		/usr/bin/sort
SU?=		/usr/bin/su
TAIL?=		/usr/bin/tail
TEST?=		/usr/bin/test
TOUCH?=		/usr/bin/touch
TR?=		/usr/bin/tr
TRUE?=		/usr/bin/true
TYPE?=		/usr/bin/type
WC?=		/usr/bin/wc
XARGS?=		/usr/bin/xargs
