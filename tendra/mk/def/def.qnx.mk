# $TenDRA$
#
# Binary / variable definitions for the QNX operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).


# Libraries

LIB_CRT0?=	
LIB_CRT1?=	/lib/crt1.o		
LIB_CRTI?=	/lib/crti.o
LIB_CRTN?=	/lib/crtn.o
LIB_GCRT0?=	
LIB_GCRT1?=	
LIB_MCRT0?=	


# Arguments

ARGS_CP?=	-v
ARGS_GUNZIP?=	-f
ARGS_MKDIR?=	-p


# Binaries

BIN_AR?=	
BIN_AS?=	
BIN_AWK?=	/usr/bin/awk
BIN_BASENAME?=	/usr/bin/basename
BIN_CAT?=	/bin/cat
BIN_CHGRP?=	/bin/chgrp
BIN_CHMOD?=	/bin/chmod
BIN_CHOWN?=	/chown
BIN_CP?=	/bin/cp
BIN_CUT?=	/usr/bin/cut
BIN_DC?=	/usr/bin/dc
BIN_DIRNAME?=	/usr/bin/dirname
BIN_ECHO?=	/bin/echo
BIN_EGREP?=	/usr/bin/egrep
BIN_FALSE?=	/bin/false
BIN_FILE?=	/usr/bin/file
BIN_FIND?=	/usr/bin/find
BIN_GREP?=	/usr/bin/grep
BIN_GTAR?=	/usr/bin/tar
BIN_GUNZIP?=	/bin/gunzip
BIN_GZCAT?=	
BIN_GZIP?=	/bin/gzip
BIN_HEAD?=	/usr/bin/head
BIN_ID?=	/usr/bin/id
BIN_INSTALL?=
BIN_LD?=	
BIN_LDCONFIG?=	
BIN_LN?=	/bin/ln
BIN_LS?=	/bin/ls
BIN_MKDIR?=	/bin/mkdir
BIN_MTREE?=	
BIN_MV?=	/bin/mv
BIN_PATCH?=	
BIN_PAX?=	/bin/pax
BIN_PERL?=	/usr/bin/perl		
BIN_RANLIB?=	
BIN_RM?=	/bin/rm
BIN_RMDIR?=	/usr/bin/rmdir
BIN_SED?=	/usr/bin/sed
BIN_SETENV?=	/usr/bin/env
BIN_SH?=	/bin/sh
BIN_SORT?=	/usr/bin/sort
BIN_SU?=	/bin/su
BIN_TAIL?=	/usr/bin/tail
BIN_TEST?=	
BIN_TIME?=
BIN_TOUCH?=	/usr/bin/touch
BIN_TR?=	/usr/bin/tr
BIN_TRUE?=	/bin/true
BIN_TYPE?=	type			# Shell builtin
BIN_WC?=	/usr/bin/wc
BIN_XARGS?=	/usr/bin/xargs
