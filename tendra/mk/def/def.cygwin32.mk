# $TenDRA$
#
# Binary / variable definitions for the cygwin32 environment.

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

AR?=		/bin/ar
AS?=		/bin/as
AWK?=		/bin/awk
BASENAME?=	/bin/basename
CAT?=		/bin/cat
CC=		gcc
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
GTAR?=		/bin/tar
GUNZIP?=    	/bin/gunzip
GUNZIP_ARGS?=	-f
GZCAT?=		/bin/gzcat
GZIP?=		/bin/gzip
GZIP_ARGS?=	-nf -9
HEAD?=		/bin/head
ID?=		/bin/id
LDCONFIG?=	NO/sbin/ldconfig
LN?=		/bin/ln
LS?=		/bin/ls
MKDIR?=		/bin/mkdir
MKDIR_ARGS?=	-p
MTREE?=		NO/usr/sbin/mtree
MV?=		/bin/mv
PATCH?=		GNU/usr/bin/patch
PAX?=		NO/bin/pax
PERL?=		/bin/perl
RANLIB?=	/bin/ranlib
RM?=		/bin/rm
RMDIR?=		/bin/rmdir
SED?=		/bin/sed
SETENV?=	/bin/env
SH?=		/bin/sh
SORT?=		/bin/sort
SU?=		/bin/su
TAIL?=		/bin/tail
TEST?=		/bin/test
TOUCH?=		/bin/touch
TR?=		/bin/tr
TRUE?=		/bin/true
TYPE?=		type				# Shell builtin
WC?=		/bin/wc
XARGS?=		/bin/xargs
