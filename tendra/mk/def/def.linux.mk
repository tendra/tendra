# $TenDRA$
#
# Binary / variable definitions for the Linux operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).


# Libraries

.if ${MACH_EXEC} = "elf"
LIB_CRT0?=		/usr/lib/crt0.o
LIB_CRT1?=		/usr/lib/crt1.o
LIB_CRTI?=		/usr/lib/crti.o
LIB_CRTBEGIN?=		/usr/lib/crtbegin.o
LIB_CRTEND?=		/usr/lib/crtend.o
LIB_CRTN?=		/usr/lib/crtn.o
LIB_LD_LINUX_1?=	/lib/ld-linux.so.1
LIB_GCRT1?=		/usr/lib/gcrt1.o
MCRT0?=?=		/usr/lib/Mcrt1.o
.endif

.if ${MACH_EXEC} = "aout"
LIB_CRT0?=	/usr/i486-linuxaout/lib/crt0.o
LIB_CRT1?=	/usr/lib/crt1.o
LIB_CRTI?=	/usr/lib/crti.o
LIB_CRTN?=	/usr/lib/crtn.o
LIB_GCRT0?=	/usr/lib/gcrt0.o
LIB_GCRT1?=	/usr/lib/gcrt1.o
LIB_MCRT0?=	/usr/lib/Mcrt1.o
.endif


# Arguments

ARGS_CP?=	-v
ARGS_GUNZIP?=	-f
ARGS_GZIP?=	-nf -9
ARGS_MKDIR?=	-p


# Binaries

.if ${MACH_EXEC} = "elf"
BIN_LD?=	/usr/bin/ld
BIN_AS?=	/usr/bin/as
.endif

.if ${MACH_EXEC} = "aout"
BIN_AS?=	/usr/i486-linuxaout/bin/as
BIN_LD?=	/usr/i486-linuxaout/bin/ld
.endif

BIN_AR?=	/usr/bin/ar
BIN_AWK?=	/bin/awk
#BIN_AS?=			# see above!
BASENAME?=	/bin/basename
BIN_CAT?=	/bin/cat
BIN_CHGRP?=	/bin/chgrp
BIN_CHMOD?=	/bin/chmod
BIN_CHOWN?=	/bin/chown
BIN_CP?=	/bin/cp
BIN_CUT?=	/usr/bin/cut
BIN_DC?=	/usr/bin/dc
BIN_DIRNAME?=	/usr/bin/dirname
BIN_ECHO?=	/bin/echo
BIN_EGREP?=	/bin/egrep
BIN_FALSE?=	/bin/false
BIN_FILE?=	/usr/bin/file
BIN_FIND?=	/usr/bin/find
BIN_GREP?=	/bin/grep
BIN_GTAR?=	/bin/tar
BIN_GUNZIP?=	/bin/gunzip
BIN_GZCAT?=	/usr/pubsw/bin/gzcat
BIN_GZIP?=	/bin/gzip
BIN_HEAD?=	/usr/bin/head
BIN_ID?=	/usr/bin/id
BIN_INSTALL?=
BIN_LDCONFIG?=	
#BIN_LD				# see above!
BIN_LN?=	/bin/ln
BIN_LS?=	/bin/ls
BIN_MKDIR?=	/bin/mkdir
BIN_MTREE?=	
BIN_MV?=	/bin/mv
BIN_PATCH?=	/usr/bin/patch
BIN_PAX?=	
BIN_PERL?=	/usr/bin/perl
BIN_RANLIB?=	/usr/bin/ranlib
BIN_RM?=	/bin/rm
BIN_RMDIR?=	/bin/rmdir
BIN_SED?=	/bin/sed
BIN_SETENV?=	/usr/bin/env
BIN_SH?=	/bin/sh
BIN_SORT?=	/bin/sort
BIN_SU?=	/bin/su
BIN_TAIL?=	/usr/bin/tail
BIN_TEST?=	/usr/bin/test
BIN_TIME?=
BIN_TOUCH?=	/bin/touch
BIN_TR?=	/usr/bin/tr
BIN_TRUE?=	/bin/true
BIN_TYPE?=	type		# shell builtin.
BIN_WC?=	/usr/bin/wc
BIN_XARGS?=	/usr/bin/xargs
