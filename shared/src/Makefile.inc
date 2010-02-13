# $Id$

# The shared/ directory is expected to be included in each project as a
# symbolic link. When traversing via the SUBDIR mechanism, sh would see
# paths relative to the parent directory as being trunk/shared/.. rather
# than the base directory per-project, /trunk/$project/src/shared/..
#
# The _SHARED_BASEDIR variable is expected to be passed (if shared/ is to be
# built via its symlinks) such that the project's base directory may be found.
#
# Usually this exporting takes the form of:
#
# .MAKEFLAGS:	_SHARED_BASEDIR=${.CURDIR}
#
# Which causes _SHARED_BASEDIR to be exported to subshell's environments, and
# therefore carried through when changing directory and re-executing ${MAKE}.

.if defined(_SHARED_BASEDIR)
_BASEDIR_RELATIVE := ${_SHARED_BASEDIR}/..
.elif defined(_BASEDIR_RELATIVE)
_BASEDIR_RELATIVE := ${_BASEDIR_RELATIVE}/..
.else
_BASEDIR_RELATIVE = ..
.endif

.include "${_BASEDIR_RELATIVE}/Makefile.inc"





# TODO: things for building shared/ directly, as in 'cd trunk/shared && make'

#.if !defined(BASE_DIR)
#BASE_DIR!=	cd ${.CURDIR}/${_BASEDIR_RELATIVE} && pwd
#.endif

#.if exists(${BASE_DIR}/Makefile.defs)
#. include "${BASE_DIR}/Makefile.defs"
#.endif

#.MAKEFLAGS:	-m ${BASE_DIR}/mk -r

