# $TenDRA$
#
# Binary / variable definitions for the OpenBSD operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).

CRT0?=		/usr/lib/crt0.o
CRT1?=
CRTN?=
GCRT0?=
GCRT1?=
MCRT0?=

AR?=		/usr/bin/ar
AWK?=		/usr/bin/awk
BASENAME?=	/usr/bin/basename
CAT?=		/bin/cat
CHGRP?=		/bin/chgrp
CHMOD?=		/bin/chmod
CHOWN?=		/sbin/chown
CP?=		/bin/cp
CP_VERBOSE?=	${CP}
CUT?=		/usr/bin/cut
DC?=		/usr/bin/dc
DIRNAME?=	/usr/bin/dirname
ECHO?=		/bin/echo
EGREP?=		/usr/bin/egrep
FALSE?=		/usr/bin/false
FILE?=		/usr/bin/file
FIND?=		/usr/bin/find
GREP?=		/usr/bin/grep
GTAR?=		/bin/tar
GUNZIP_CMD?=	/usr/bin/gunzip -f
GZCAT?=		/usr/bin/gzcat
GZIP?=		-9
GZIP_CMD?=	/usr/bin/gzip -nf ${GZIP}
HEAD?=		/usr/bin/head
ID?=		/usr/bin/id
LDCONFIG?=	/sbin/ldconfig
LN?=		/bin/ln
LS?=		/bin/ls
MKDIR?=		/bin/mkdir -p
MTREE?=		/usr/sbin/mtree
MV?=		/bin/mv
PATCH?=		/usr/bin/patch
PAX?=		/bin/pax
PERL?=		/usr/bin/perl
PKGLOCALEDIR?=	share
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
