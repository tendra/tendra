# $TenDRA$
#
# Binary / variable definitions for the OSF1/Tru64 operating system.
# OSF1 4.0 and Tru64 5.x symlink /bin -> /usr/bin, so use the end location
# to not incur namei lookups on the symbolic links.

AWK?=		/usr/bin/awk
BASENAME?=	/usr/bin/basename
CAT?=		/usr/bin/cat
CHGRP?=		/usr/bin/chgrp
CHMOD?=		/usr/bin/chmod
CHOWN?=		/usr/sbin/chown
CP?=		/usr/bin/cp
CP_VERBOSE?=	${CP}
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
GUNZIP_CMD?=	/usr/bin/gunzip -f
GZCAT?=		/usr/bin/gzcat
GZIP?=		-9
GZIP_CMD?=	/usr/bin/gzip -nf ${GZIP}
HEAD?=		/usr/bin/head
ID?=		/usr/bin/id
LDCONFIG?=
LN?=		/usr/bin/ln
LS?=		/usr/bin/ls
MKDIR?=		/usr/bin/mkdir -p
MTREE?=
MV?=		/usr/bin/mv
PATCH?=		/usr/bin/patch
PAX?=		/usr/bin/pax
PERL?=		/usr/bin/perl
PKGLOCALEDIR?=	share
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
