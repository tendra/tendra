# $TenDRA$
#
# Binary / variable definitions for the SunOS/Solaris operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).

CRT0?=		
CRT1?=		
CRTI?=		
CRTN?=		
GCRT0?=		
GCRT1?=		
MCRT0?=		

AR?=		/usr/ccs/bin/ar
AS?=		/usr/ccs/bin/as
AWK?=		/usr/bin/awk
BASENAME?=	/usr/bin/basename
CAT?=		/bin/cat
CHGRP?=		/usr/bin/chgrp
CHMOD?=		/bin/chmod
CHOWN?=		/usr/sbin/chown
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
GTAR?=		/usr/bin/tar
GUNZIP_CMD?=	/usr/bin/gunzip -f
GZCAT?=		NO-gzcat
GZIP?=		-9
GZIP_CMD?=	NO-gzip
HEAD?=		/usr/bin/head
ID?=		/usr/bin/id
LD?=		/usr/ccs/bin/ld
LDCONFIG?=	NO-ldconfig
LN?=		/bin/ln
LS?=		/bin/ls
MKDIR?=		/usr/bin/mkdir -p
MTREE?=		NO-mtree
MV?=		/bin/mv
PATCH?=		/usr/bin/patch
PAX?=		/usr/bin/pax
PERL?=		/usr/bin/perl
RM?=		/usr/bin/rm
RMDIR?=		/usr/bin/rmdir
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
TYPE?=		type			# Shell builtin
WC?=		/usr/bin/wc
XARGS?=		/usr/bin/xargs
