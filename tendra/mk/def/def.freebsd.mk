# $TenDRA$
#
# Binary / variable definitions for the FreeBSD operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).


# Libraries

LIB_CRT0?=		
LIB_CRT1?=		/usr/lib/crt1.o
LIB_CRTI?=		/usr/lib/crti.o
LIB_CRTN?=		/usr/lib/crtn.o
LIB_GCRT0?=		
LIB_GCRT1?=		/usr/lib/gcrt1.o
LIB_MCRT0?=		


# Arguments

ARGS_CP?=	-v
ARGS_GUNZIP?=	-f
ARGS_GZIP?=	-nf -9
ARGS_MKDIR?=	-p


# Binaries

BIN_CC?=		/usr/bin/cc
BIN_AR?=		/usr/bin/ar
BIN_AS?=		/usr/bin/as
BIN_AWK?=		/usr/bin/awk
BIN_BASENAME?=		/usr/bin/basename
BIN_CAT?=		/bin/cat
BIN_CHGRP?=		/usr/bin/chgrp
BIN_CHMOD?=		/bin/chmod
BIN_CHOWN?=		/usr/sbin/chown
BIN_CP?=		/bin/cp
BIN_CUT?=		/usr/bin/cut
BIN_DC?=		/usr/bin/dc
BIN_DIRNAME?=		/usr/bin/dirname
BIN_ECHO?=		/bin/echo
BIN_EGREP?=		/usr/bin/egrep
BIN_FALSE?=		/usr/bin/false
BIN_FILE?=		/usr/bin/file
BIN_FIND?=		/usr/bin/find
BIN_GREP?=		/usr/bin/grep
BIN_GTAR?=		/usr/bin/tar
BIN_GUNZIP?=		/usr/bin/gunzip
BIN_GZCAT?=		/usr/bin/gzcat
BIN_GZIP?=		/usr/bin/gzip
BIN_HEAD?=		/usr/bin/head
BIN_ID?=		/usr/bin/id
BIN_INSTALL?=		/usr/bin/install
BIN_LD?=		/usr/bin/ld
BIN_LDCONFIG?=		/sbin/ldconfig
BIN_LN?=		/bin/ln
BIN_LS?=		/bin/ls
BIN_MKDIR?=		/bin/mkdir
BIN_MTREE?=		/usr/sbin/mtree
BIN_MV?=		/bin/mv
BIN_PATCH?=		/usr/bin/patch
BIN_PAX?=		/bin/pax
BIN_PERL?=		/usr/bin/perl
BIN_RANLIB?=		/usr/bin/ranlib
BIN_RM?=		/bin/rm
BIN_RMDIR?=		/bin/rmdir
BIN_SED?=		/usr/bin/sed
BIN_SETENV?=		/usr/bin/env
BIN_SH?=		/bin/sh
BIN_SORT?=		/usr/bin/sort
BIN_SU?=		/usr/bin/su
BIN_TAIL?=		/usr/bin/tail
BIN_TEST?=		/bin/test
BIN_TIME?=		/usr/bin/time
BIN_TOUCH?=		/usr/bin/touch
BIN_TR?=		/usr/bin/tr
BIN_TRUE?=		/usr/bin/true
BIN_TYPE?=		type		#builtin
BIN_WC?=		/usr/bin/wc
BIN_XARGS?=		/usr/bin/xargs
