# $TenDRA$
#
# Binary / variable definitions for the Irix operating system.

# The execution startup routines.
# crt is for normal support, crti for _init, crtn for _fini.
# gcrt is for profiling support (gprof).
# mcrt is for profiling support (prof).


# Libraries

LIB_CRT0?=		
LIB_CRT1?=	/usr/lib/crt1.o
LIB_CRTI?=		
LIB_CRTN?=	/usr/lib/crtn.o
LIB_GCRT0?=		
LIB_GCRT1?=		
LIB_MCRT0?=		
LIB_MCRT1?=	/usr/lib/mcrt1.o
LIB_PCRT0?=	


# Arguments

ARGS_CP?=	-v
ARGS_GUNZIP?=	-f
ARGS_GZIP?=	-nf -9
ARGS_MKDIR?=	-p


# Binaries

BIN_CC?=		/usr/bin/cc
BIN_AR?=		/usr/bin/ar
BIN_AS?=		/usr/bin/as
BIN_AS1?=		/usr/lib/as1
BIN_AWK?=		/usr/bin/awk
BIN_BASENAME?=	/sbin/basename
BIN_CAT?=		/sbin/cat
BIN_CHGRP?=		/sbin/chgrp
BIN_CHMOD?=		/sbin/chmod
BIN_CHOWN?=		/sbin/chown
BIN_CP?=		/sbin/cp
BIN_CUT?=		/usr/bin/cut
BIN_DC?=		/usr/bin/dc
BIN_DIRNAME?=	/usr/bin/dirname
BIN_ECHO?=		echo 						# shell built-in command		
BIN_EGREP?=		/usr/bin/egrep
BIN_FALSE?=		/usr/bin/false
BIN_FILE?=		/usr/bin/file
BIN_FIND?=		/sbin/find
BIN_GREP?=		/sbin/grep
BIN_GTAR?=		/usr/freeware/bin/tar		# When installed using sgi freeware system
BIN_GUNZIP?=	/usr/sbin/gunzip	
BIN_GZCAT?=		/usr/sbin/gzcat
BIN_GZIP?=		/usr/sbin/gzip
BIN_HEAD?=		/usr/bsd/head
BIN_ID?=		/usr/bin/id
BIN_INSTALL?=	/sbin/install
BIN_LD?=		/usr/bin/ld
BIN_LDCONFIG?=	# Not needed/used on irix
BIN_LN?=		/sbin/ln
BIN_LS?=		/sbin/ls
BIN_MKDIR?=		/sbin/mkdir
BIN_MTREE?=		
BIN_MV?=		/sbin/mv
BIN_PATCH?=		/usr/sbin/patch
BIN_PAX?=		/usr/sbin/pax
BIN_PERL?=		/usr/sbin/perl
BIN_RANLIB?=	# Not needed/used on irix
BIN_RM?=		/sbin/rm
BIN_RMDIR?=		/usr/bin/rmdir
BIN_SED?=		/sbin/sed
BIN_SETENV?=	setenv						# shell built-in command 
BIN_SH?=		/sbin/sh
BIN_SORT?=		/usr/bin/sort
BIN_SU?=		/sbin/su
BIN_TAIL?=		/usr/bin/tail
BIN_TEST?=		/sbin/test
BIN_TIME?=		time						# shell built-in command
BIN_TOUCH?=		/sbin/touch
BIN_TR?=		/usr/bin/tr
BIN_TRUE?=		/usr/bin/true
BIN_TYPE?=		/sbin/type
BIN_WC?=		/sbin/wc
BIN_XARGS?=		/sbin/xargs
