# $Id$

# BUILD OPTIONS
#
# These flags control which components of the release should be installed.
#
# If BUILD_UPDATE is true then the public executables and their configuration
# files will be installed (this has to be done on every target platform).
#
# If BUILD_MACHINE is true then all the other target dependent components
# will be installed (this also has to be done on every target platform).
#
# If BUILD_COMMON is true then the target independent components will be
# installed (this only has to be done once, indeed if the release is being
# built simultaneously on several platforms then the builds can conflict
# with each other, so start the quickest machine off first to install
# the complete release, and get the other machines to only install the
# target dependent sections).
#
# BUILD_OK is set to false if an error occurs.

BUILD_UPDATE=	true
BUILD_MACHINE=	true
BUILD_COMMON=	true
BUILD_OK=	true

# RANDOM BITS 'N PIECES

SUBDIR=		src

.if !exists(Makefile.defs)
.BEGIN:
	@${ECHO} "Please run 'makedefs' prior to running (b)make"
	@${ECHO}
	@${EXIT} 1;
.else
all:
. if defined(BOOTSTRAP)
	@${ECHO} "==> Starting TenDRA build..."
	@${ECHO} "==> Creating object directory and symbolic links"
	@${ECHO} "==> Object directory created, bootstrapping build"
	@cd ${BASE_DIR} && ${MAKE} _objdirs_done=yes obj;
. else
.  if !exists(${.CURDIR}/obj/_obj_tree_complete)
.   if "${_objdirs_done}" != "yes"
	@${ECHO} "==> Starting TenDRA build..."
	@${ECHO} "==> Creating object directory and symbolic links"
	@cd ${BASE_DIR} && ${MAKE} _objdirs_done=yes obj;
	@${ECHO} "Do not remove this file." > ${OBJ_DIR_INDICATOR};
	@${ECHO} "==> Object directory created, building"
	@${ECHO}

_objdirs_done=yes
.   endif
.  endif
. endif
.endif

.include "Makefile.inc"
