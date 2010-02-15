# TenDRA make build infrastructure
#
# $Id$

# STANDARD DIRECTORIES
#
# These directories are used to configure where the release is to be
# installed:
#
#       BASE_DIR        gives the directory in which the source has been
#                       installed (i.e. the directory containing this script).
#
#	PREFIX		gives the base directory prefix in which binaries and
#			helper files will be installed.
#
#       PUBLIC_BIN      gives the directory in which the public executables
#                       (tcc, tchk and tspec) are to be installed.  If
#                       PUBLIC_BIN is left blank then the public executables
#                       will be installed in the private executables
#                       directory.
#
#       INSTALL_DIR     gives the directory in which the configuration files,
#                       include files, private executables, libraries etc.
#                       are to be installed.
#
#       COMMON_DIR      gives the sub-directory of INSTALL_DIR in which the
#                       target independent components are to be installed.
#
#       MACH_DIR        gives the sub-directory of INSTALL_DIR in which the
#                       target dependent components are to be installed.
#
#       MAN_DIR         gives the directory in which the manual pages are
#                       to be installed.
#
#       OBJ_DIR         gives the working directory in which binary object
#                       files etc. created during the build process will
#                       be stored.
#
#	OBJ_SDIR	gives the full path to the working directory and the
#			sub-directory of the current source directory.
#
#       TMP_DIR         gives a temporary directory, used both by this
#                       script and by tcc (so make sure that there is
#                       plenty of free space).

.if !defined(_TENDRA_BASE_MK_)
_TENDRA_BASE_MK_=1

# Default target
.MAIN: all

# Ensure existence of basic targets.
.for target in all doc clean install
${target}:: .PHONY
.endfor


INSTALL_DIR=	${PREFIX}/lib/TenDRA
COMMON_DIR=	${INSTALL_DIR}/lib
MACH_DIR=	${INSTALL_DIR}/machines
MACH_BASE=	${MACH_DIR}/${OSFAM}/${BLDARCH}
#MACH_BASE=	${MACH_DIR}/${OSFAM}/${MACH_VERS}/${BLDARCH}
MAN_DIR=	${PREFIX}/man
OBJ_DIR?=	${BASE_DIR}/obj
OBJ_SDIR?=	${OBJ_DIR}/${.CURDIR:C/^${BASE_DIR}\///}
OBJ_DDIR?=	${OBJ_SDIR:H}
TMP_DIR=	/var/tmp

# Do some pretty-printing.
WRKDIR=	${.CURDIR:C/^${BASE_DIR}\///1}

# Binary paths
SHELL=		/bin/sh

# Keep in alphabetical order
AR?=		ar
COPY?=		cp
DIA?=		dia
DOT?=		dot
ECHO?=		echo
ECHODIR?=	echo
EXIT?=		exit
FIND?=		find
INSTALL?=	install
LEXI?=		lexi
LD?=		ld
LN?=		ln
MKDIR?=		mkdir
MOVE?=		mv
RANLIB?=	ranlib
REMOVE?=	rm -f
SID?=		sid
SORT?=		sort
TEST?=		test
TLD?=		tld
TNC?=		tnc
TPL?=		tpl
TSPEC?=		tspec
XSLTPROC?=	xsltproc

.endif	# !defined(_TENDRA_BASE_MK_)
