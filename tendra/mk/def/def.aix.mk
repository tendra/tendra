# $TenDRA$
#
# Binary / variable definitions for the AIX operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).

# XXX: This needs to be tweaked in order to distinguish between 32- and 64-bit.


# Libraries

LIB_CRT0?=	/usr/lib/crt0.o
LIB_CRT1?=		
LIB_CRTI?=		
LIB_CRTN?=		
LIB_GCRT0?=	/usr/lib/gcrt0.o
LIB_GCRT1?=	
LIB_MCRT0?=	/usr/lib/mcrt0.o
LIB_LIBG_EXP?=	/usr/lib/libg.exp
LIB_LIB_MCRT0?=	/lib/mcrt0.o


# Arguments

ARGS_CP?=	
ARGS_GUNZIP?=	-f
ARGS_GZIP?=	-9
ARGS_MKDIR?=	-p


# Binaries

BIN_AR?=	/usr/bin/ar
BIN_AS?=	/usr/bin/as
BIN_AWK?=	/usr/bin/awk
BIN_BASENAME?=	/bin/basename
BIN_CAT?=	/bin/cat
BIN_CHGRP?=	/bin/chgrp
BIN_CHMOD?=	/bin/chmod
BIN_CHOWN?=	/bin/chown
BIN_CP?=	/bin/cp
BIN_CUT?=	/bin/cut
BIN_DC?=	/bin/dc
BIN_DIRNAME?=	/bin/dirname
BIN_ECHO?=	/bin/echo
BIN_EGREP?=	/bin/egrep
BIN_FALSE?=	/bin/false
BIN_FILE?=	/bin/file
BIN_FIND?=	/bin/find
BIN_GREP?=	/bin/grep
BIN_GTAR?=	/usr/bin/tar
BIN_GUNZIP?=	/usr/bin/gunzip
BIN_GZCAT?=	echo		# Not a system utility.
BIN_GZIP?=	/usr/bin/gzip
BIN_HEAD?=	/bin/head
BIN_ID?=	/bin/id
BIN_INSTALL?=	
BIN_LD?=	/usr/bin/ld
BIN_LDCONFIG?=	echo		# non existant.
BIN_LN?=	/bin/ln
BIN_LS?=	/bin/ls
BIN_MKDIR?=	/bin/mkdir
BIN_MTREE?=	echo		# non existant.
BIN_MV?=	/bin/mv
BIN_PATCH?=	/bin/patch
BIN_PAX?=	/usr/bin/pax
BIN_PERL?=	/usr/bin/perl
BIN_RANLIB?=	/usr/bin/ranlib
BIN_BINRM?=	/bin/rm
BIN_RMDIR?=	/bin/rmdir
BIN_SED?=	/usr/bin/sed
BIN_SETENV?=	/usr/bin/env
BIN_SH?=	/bin/sh
BIN_SORT?=	/usr/bin/sort
BIN_SU?=	/usr/bin/su
BIN_TAIL?=	/usr/bin/tail
BIN_TEST?=	/bin/test
BIN_TIME?=	
BIN_TOUCH?=	/usr/bin/touch
BIN_TR?=	/usr/bin/tr
BIN_TRUE?=	/usr/bin/true
BIN_TYPE?=	type		# Shell builtin
BIN_WC?=	/usr/bin/wc
BIN_XARGS?=	/usr/bin/xargs
