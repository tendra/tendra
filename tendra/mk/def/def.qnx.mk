# $TenDRA$
#
# Binary / variable definitions for the QNX operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).

CRT0?=		
CRT1?=		/lib/crt1.o		
CRTI?=		/lib/crti.o
CRTN?=		/lib/crtn.o
GCRT0?=		
GCRT1?=		
MCRT0?=		

AR?=		
AS?=		
AWK?=		/usr/bin/awk
BASENAME?=	/usr/bin/basename
CAT?=		/bin/cat
CHGRP?=		/bin/chgrp
CHMOD?=		/bin/chmod
CHOWN?=		/chown
CP?=		/bin/cp
CP_ARGS?=	-v
CUT?=		/usr/bin/cut
DC?=		/usr/bin/dc
DIRNAME?=	/usr/bin/dirname
ECHO?=		/bin/echo
EGREP?=		/usr/bin/egrep
FALSE?=		/bin/false
FILE?=		/usr/bin/file
FIND?=		/usr/bin/find
GREP?=		/usr/bin/grep
GTAR?=		/usr/bin/tar
GUNZIP?=	/bin/gunzip
GUNZIP_ARGS?=	-f
GZCAT?=		
GZIP?=		/bin/gzip
HEAD?=		/usr/bin/head
ID?=		/usr/bin/id
LD?=		
LDCONFIG?=	
LN?=		/bin/ln
LS?=		/bin/ls
MKDIR?=		/bin/mkdir
MKDIR_ARGS?=	-p
MTREE?=		
MV?=		/bin/mv
PATCH?=		
PAX?=		/bin/pax
PERL?=		/usr/bin/perl		
RANLIB?=	
RM?=		/bin/rm
RMDIR?=		/usr/bin/rmdir
SED?=		/usr/bin/sed
SETENV?=	/usr/bin/env
SH?=		/bin/sh
SORT?=		/usr/bin/sort
SU?=		/bin/su
TAIL?=		/usr/bin/tail
TEST?=		
TOUCH?=		/usr/bin/touch
TR?=		/usr/bin/tr
TRUE?=		/bin/true
TYPE?=		type			# Shell builtin
WC?=		/usr/bin/wc
XARGS?=		/usr/bin/xargs
