# $TenDRA$
#
# Binary / variable definitions for the OSF1/Tru64 operating system.
# OSF1 4.0 and Tru64 5.x symlink /bin -> /usr/bin, so use the end location
# to not incur namei lookups on the symbolic links.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).


# Libraries

LIB_CRT0?=	/usr/lib/cmplrs/cc/crt0.o
LIB_CRT1?=	
LIB_CRTI?=	
LIB_CRTN?=	
LIB_GCRT0?=	/usr/lib/cmplrs/cc/gcrt0.o
LIB_GCRT1?=	
LIB_MCRT0?=	/usr/lib/cmplrs/cc/mcrt0.o
LIB_PCRT0?=	/usr/lib/cmplrs/cc/pcrt0.o


# Arguments

ARGS_CP?=	
ARGS_GUNZIP?=	-f
ARGS_GZIP?=	-nf -9
ARGS_MKDIR?=	-p


# Binaries

BIN_AR?=	/usr/bin/ar
BIN_AS?=	/usr/bin/as
BIN_AS1?=	/usr/lib/cmplrs/as/as1
BIN_AWK?=	/usr/bin/awk
BIN_BASENAME?=	/usr/bin/basename
BIN_CAT?=	/usr/bin/cat
BIN_CHGRP?=	/usr/bin/chgrp
BIN_CHMOD?=	/usr/bin/chmod
BIN_CHOWN?=	/usr/sbin/chown
BIN_CP?=	/usr/bin/cp
BIN_CUT?=	/usr/bin/cut
BIN_DC?=	/usr/bin/dc
BIN_DIRNAME?=	/usr/bin/dirname
BIN_ECHO?=	/usr/bin/echo
BIN_EGREP?=	/usr/bin/egrep
BIN_FALSE?=	/usr/bin/false
BIN_FILE?=	/usr/bin/file
BIN_FIND?=	/usr/bin/find
BIN_GREP?=	/usr/bin/grep
BIN_GTAR?=	/usr/bin/tar
BIN_GUNZIP?=	/usr/bin/gunzip
BIN_GZCAT?=	/usr/bin/gzcat
BIN_GZIP?=	/usr/bin/gzip
BIN_HEAD?=	/usr/bin/head
BIN_ID?=	/usr/bin/id
BIN_INSTALL?=
BIN_BIN_LD?=	/bin/ld
BIN_LDCONFIG?=	echo		# nonexistent.
BIN_LN?=	/usr/bin/ln
BIN_LS?=	/usr/bin/ls
BIN_MKDIR?=	/usr/bin/mkdir
BIN_MTREE?=	echo		# nonexistent.
BIN_MV?=	/usr/bin/mv
BIN_PATCH?=	/usr/bin/patch
BIN_PAX?=	/usr/bin/pax
BIN_PERL?=	/usr/bin/perl
BIN_RANLIB?=	/usr/bin/ranlib
BIN_RM?=	/usr/bin/rm
BIN_RMDIR?=	/usr/bin/rmdir
BIN_SED?=	/usr/bin/sed
BIN_SETENV?=	/usr/bin/env
BIN_SH?=	/usr/bin/sh
BIN_SORT?=	/usr/bin/sort
BIN_SU?=	/usr/bin/su
BIN_TAIL?=	/usr/bin/tail
BIN_TEST?=	/usr/bin/test
BIN_TIME?=
BIN_TOUCH?=	/usr/bin/touch
BIN_TR?=	/usr/bin/tr
BIN_TRUE?=	/usr/bin/true
BIN_TYPE?=	/usr/bin/type
BIN_WC?=	/usr/bin/wc
BIN_XARGS?=	/usr/bin/xargs
