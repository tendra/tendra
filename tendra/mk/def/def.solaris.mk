# $TenDRA$
#
# Binary / variable definitions for the Solaris operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).


# Libraries


.if ${MACH_CPU} == "80x86"
LIB_CRT0?=	
LIB_CRT1?=	
LIB_CRTI?=	
LIB_CRTN?=	
LIB_GCRT0?=	
LIB_GCRT1?=	
LIB_MCRT0?=	
LIB_MCRT1?=	
LIB_PCRT0?=	
LIB_VALUES_XA?=	/usr/ccs/lib/values-Xa.o
LIB_VALUES_XC?=	/usr/ccs/lib/values-Xc.o
LIB_VALUES_XT?=	/usr/ccs/lib/values-Xt.o
.endif


.if ${MACH_CPU} == "sparc"
LIB_CRT0?=	
LIB_CRT1?=	
LIB_CRTI?=	
LIB_CRTN?=	
LIB_GCRT0?=	
LIB_GCRT1?=	
LIB_MCRT0?=	
LIB_MCRT1?=	
LIB_PCRT0?=	
LIB_VALUES_XA?=	/usr/ccs/lib/values-Xa.o
LIB_VALUES_XC?=	/usr/ccs/lib/values-Xc.o
LIB_VALUES_XT?=	/usr/ccs/lib/values-Xt.o
.endif

# Arguments

ARGS_CP?=
ARGS_GUNZIP?=	-f
ARGS_GZIP?=	-nf -9
ARGS_MKDIR?=	-p


# Binaries

BIN_CC?=		
BIN_AR?=		/usr/ccs/bin/ar
BIN_AS?=		/usr/ccs/bin/as
BIN_AWK?=		/usr/xpg4/bin/awk
BIN_BASENAME?=		/usr/bin/basename
BIN_CAT?=		/usr/bin/cat
BIN_CHGRP?=		/usr/bin/chgrp
BIN_CHMOD?=		/usr/bin/chmod
BIN_CHOWN?=		/usr/bin/chown
BIN_CP?=		/usr/bin/cp
BIN_CUT?=		/usr/bin/cut
BIN_DC?=		/usr/bin/dc
BIN_DIRNAME?=		/usr/bin/dirname
BIN_ECHO?=		/usr/bin/echo
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
BIN_INSTALL?=		echo		# incompatible
BIN_LD?=		/usr/ccs/bin/ld
BIN_LDCONFIG?=		echo		# nonexistent
BIN_LN?=		/usr/bin/ln
BIN_LS?=		/usr/bin/ls
BIN_MKDIR?=		/usr/bin/mkdir
BIN_MTREE?=		echo		# nonexistent
BIN_MV?=		/usr/bin/mv
BIN_PATCH?=		/usr/bin/patch
BIN_PAX?=		/usr/bin/pax
BIN_PERL?=		/usr/bin/perl
BIN_RANLIB?=		/usr/ccs/bin/ranlib
BIN_RM?=		/usr/bin/rm
BIN_RMDIR?=		/usr/bin/rmdir
BIN_SED?=		/usr/bin/sed
BIN_SETENV?=		/usr/bin/env
BIN_SH?=		/usr/bin/sh
BIN_SORT?=		/usr/bin/sort
BIN_SU?=		/usr/bin/su
BIN_TAIL?=		/usr/bin/tail
BIN_TEST?=		/usr/bin/test
BIN_TIME?=		/usr/bin/time
BIN_TOUCH?=		/usr/bin/touch
BIN_TR?=		/usr/bin/tr
BIN_TRUE?=		/usr/bin/true
BIN_TYPE?=		/usr/bin/type
BIN_WC?=		/usr/bin/wc
BIN_XARGS?=		/usr/bin/xargs
