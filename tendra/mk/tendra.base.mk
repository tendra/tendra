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

.MAKEOVERRIDES:	BASE_DIR
BASE_DIR?=	${.CURDIR:C/\/(mk|src).*//}
APIS=		src/lib/apis
ENVIRONMENT=	src/lib/env
STARTUP=	src/lib/startup
TOOLS=		src/tools
UTILITIES=	src/utilities

PUBLIC_BIN=	${PREFIX}/bin
INSTALL_DIR=	${PREFIX}/lib/TenDRA
COMMON_DIR=	${INSTALL_DIR}/lib
MACH_DIR=	${INSTALL_DIR}/machines
MACH_BASE=	${MACH_DIR}/${OSFAM}/${BLDARCH}
#MACH_BASE=	${MACH_DIR}/${OSFAM}/${MACH_VERS}/${BLDARCH}
MAN_DIR=	${PREFIX}/man
OBJ_DIR=	${BASE_DIR}/obj
OBJ_SDIR=	${OBJ_DIR}${.CURDIR:C/${BASE_DIR}//}
TMP_DIR=	/var/tmp

OBJS=  ${SRCS:S/.c/.o/}

# Binary paths

SHELL=		/bin/sh

ENV?=		/usr/bin/env

# Keep in alphabetical order
COPY?=		${ENV} cp
ECHO?=		${ENV} echo
ECHODIR?=	${ENV} echo
EXIT?=		exit
INSTALL?=	${ENV} install
LN?=		${ENV} ln
MKDIR?=		${ENV} mkdir
MOVE?=		${ENV} mv
REMOVE?=	${ENV} rm -f
TEST?=		${ENV} test

.endif	# !defined(_TENDRA_BASE_MK_)
