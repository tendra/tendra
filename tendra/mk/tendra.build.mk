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
#       WORK_DIR        gives the working directory in which binary object
#                       files etc. created during the build process will
#                       be stored.
#
#       TMP_DIR         gives a temporary directory, used both by this
#                       script and by tcc (so make sure that there is
#                       plenty of free space).

BASE_DIR = ${.CURDIR:C/\/src.*//}
PUBLIC_BIN = /usr/local/bin
INSTALL_DIR = /usr/local/lib/TenDRA
COMMON_DIR = ${INSTALL_DIR}/lib
MACH_DIR = ${INSTALL_DIR}/machines
MAN_DIR = /usr/local/man
WORK_DIR = ${BASE_DIR}/work
TMP_DIR = /var/tmp

# Binary paths

SHELL = /bin/sh

ENV ?=		/usr/bin/env

COPY ?=		${ENV} cp
ECHO ?=		${ENV} echo
ECHODIR ?=	${ENV} echo
MOVE ?=		${ENV} mv
REMOVE ?=	${ENV} rm -f

# Build infrastructure framework

.if !target(.MAIN)
.MAIN: all
.endif

_SUBDIR: .USE
.if defined(SUBDIR) && !empty(SUBDIR)
.for entry in ${SUBDIR}
		@${ECHODIR} "Entering ${DIRPREFIX}${entry}"
		@${ECHODIR} "..Executing ${entry}: ${MAKE} ${.TARGET}"
		@cd ${.CURDIR}/${entry}; \
			${MAKE} ${.TARGET} DIRPREFIX=${DIRPREFIX}${entry}/
.endfor
.endif

.for target in all clean
${target}: _SUBDIR
.endfor

clean:
	${REMOVE} ${NAME}.core core ${NAME}
