# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_BASE_MK_)
_TENDRA_BASE_MK_=1


# Default target
.MAIN: all

# Ensure existence of basic targets.
.for target in all clean install regen regen-clean test
${target}:: .PHONY
.endfor


UNAME?= uname

.include <tendra.makedefs.mk>


# Please override locations as best suits your system.
# ${PREFIX_LIBEXEC} should not be in $PATH
PREFIX?=         /usr/local
PREFIX_BIN?=     ${PREFIX}/bin
PREFIX_LIB?=     ${PREFIX}/lib
PREFIX_LIBEXEC?= ${PREFIX}/libexec
PREFIX_SHARE?=   ${PREFIX}/share
PREFIX_INCLUDE?= ${PREFIX}/include
PREFIX_MAN?=     ${PREFIX}/man
PREFIX_TSPEC?=   ${PREFIX_SHARE}/tspec
PREFIX_STARTUP?= ${PREFIX_LIB}/tcc/startup
PREFIX_ENV?=     ${PREFIX_LIB}/tcc/env
PREFIX_API?=     ${PREFIX_LIB}/tcc/api
PREFIX_LPI?=     ${PREFIX_LIB}/tcc/lpi
PREFIX_SYS?=     ${PREFIX_LIB}/tcc/sys
PREFIX_TMP?=     /tmp
PREFIX_HTMLDOC?= ${PREFIX_SHARE}/doc
PREFIX_HTMLMAN?= ${PREFIX_SHARE}/doc


# If you just want to have all build work undertaken in a specific directory
# (i.e. a read-only source tree), then OBJ_DIR is what you're looking for.
OBJ_DIR?=	${BASE_DIR}/obj
OBJ_SDIR?=	${OBJ_DIR}/${.CURDIR:C/^${BASE_DIR}\///}
OBJ_DDIR?=	${OBJ_SDIR:H}

# Do some pretty-printing.
WRKDIR=	${.CURDIR:C/^${BASE_DIR}\///1}

# Keep in alphabetical order
AR?=		ar
CAT?=		cat
CC?=    	cc
CALCULUS?=	calculus
COPY?=		cp
ECHO?=		echo
ECHODIR?=	echo
EXIT?=		exit
FIND?=		find
.if ${SYSTEM} == "SunOS"
INSTALL?=	ginstall
.elif ${SYSTEM} == "HP-UX"
INSTALL?=	/usr/local/coreutils/bin/install
.else
INSTALL?=	install
.endif
LEXI?=		lexi
LD?=		ld
LN?=		ln
MKDIR?=		mkdir
MOVE?=		mv
RANLIB?=	ranlib
RMDIR?=		rm -rf
RMFILE?=	rm -f
SED?=		sed
SID?=		sid
SORT?=		sort
SHELL=		/bin/sh
TEST?=		test
TLD?=		tld
TNC?=		tnc
TPL?=		tpl
TSPEC?=		tspec
XSLTPROC?=	xsltproc
XMLLINT?=	xmllint


# Platform-specific things
EXECFMT?=    	${MD_EXECFMT}
BLDARCH?=    	${MD_BLDARCH}
BLDARCHBITS?=	${MD_BLDARCHBITS}
OSFAM?=      	${MD_OSFAM}
OSVER?=      	${MD_OSVER}
LIBCVER?=     	${MD_LIBCVER}


.endif
