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

BUILD_UPDATE = true
BUILD_MACHINE = true
BUILD_COMMON = true
BUILD_OK = true

.include "Makefile.inc"

# RANDOM BITS 'N PIECES

all:
	@echo Starting TenDRA build...
	@echo Bootstrapping from ${BASE_DIR}
	@echo
	@echo building host type determiner, tuname...
	@echo ${DIST_DIR}
	@echo ${.MAKEFLAGS}

tuname:
	@cd src/utilities/tuname;\
		${MAKE} -f Makefile BASE=${BASE_DIR} CC=${CC}
