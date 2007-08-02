# TenDRA make compiler infrastructure
#
# $Id$

.if !defined(_TENDRA_COMPILER_MK_)
_TENDRA_COMPILER_MK_=1

# COMPILER INFORMATION
#
# These variables give information on the compiler to be used to install
# the release.  CC gives the compiler. CCOPTS and LIBOPTS give any target
# specific options required by the build, and are set by this script.  It
# is recommended that any extra flags which the user requires are made
# part of the definition of CC, so CC="gcc -O" would install using gcc
# in optimising mode.  TCCOPTS controls the extra configuration options
# required when bootstrapping the system using tcc.
#
# To install the bootstrapped compiler, install first using cc or gcc.
# Then remove the work directory (OBJ_DIR), change the compiler to tcc,
# and install again.  Bootstrapping is recommended (all our testing is
# on the bootstrapped compiler).
#
# SYS_INCLUDES gives a list of include file directories to be searched
# when building the TDF API libraries.
#
# STRIP may be set to "strip" in order to ensure that the installed
# executables are stripped.
#
# RANLIB is used on those platforms on which system libraries need to be
# ranlib-ed.
#
# EXEC_SUFFIX is used on those platforms where executable names need to
# have a particular suffix, for example it may be set to ".exe".

.if !defined(BOOTSTRAP)
.if exists(${BOBJ_DIR}/src/tools/tcc/tcc)
CC=	${BOBJ_DIR}/src/tools/tcc/tcc -Y${BOBJ_DIR}/src/lib/env/build -yTENDRA_BASEDIR=${BOBJ_DIR}/src
CFLAGS=
LDFLAGS=
.endif
.endif

# Assume that the cc on this system is the GNU C Compiler.
.if "${CC:T}" != "${CC:T:Ncc:Ngcc}"

CWARNFLAGS=-w

.if defined(WARNS)
. if ${WARNS} >= 1
CWARNFLAGS=-ansi -Wno-traditional
. endif
. if ${WARNS} >= 2
CWARNFLAGS+=-pedantic -fno-builtin
. endif
. if ${WARNS} >= 3
CWARNFLAGS+=-W -Wall -Wmissing-prototypes -Wpointer-arith -Wstrict-prototypes
. endif
.endif

  TCCOPTS=
  CCOPTS+= ${CWARNFLAGS} ${CFLAGS}
  LDOPTS+= ${LDFLAGS}
# The Intel C Compiler.
.elif "${CC:T}" != "${CC:T:Nicc}"

CWARNFLAGS=-no-gcc -w

.if defined(WARNS)
. if ${WARNS} >= 1
CWARNFLAGS=-no-gcc -ansi -std=c89
. endif
. if ${WARNS} >= 2
CWARNFLAGS+=
. endif
. if ${WARNS} >= 3
CWARNFLAGS+=-Wall
. endif
.endif

  TCCOPTS=
  CCOPTS+= ${CWARNFLAGS} ${CFLAGS}
  LDOPTS+= ${LDFLAGS}
# The TenDRA C Compiler.
# XXX: How to differentiate between TenDRA and tinycc?
.elif "${CC:T}" != "${CC:T:Ntcc}"
  CCOPTS+= ${CFLAGS}
  LDOPTS+= ${LDFLAGS}
.endif

.if exists(${BOBJ_DIR}/src/tools/tcc/tcc)
TCC?=	${BOBJ_DIR}/src/tools/tcc/tcc
.elif exists(${OBJ_DIR}/src/tools/tcc/tcc)
TCC?=	${OBJ_DIR}/src/tools/tcc/tcc
.else
TCC?=	tcc
.endif

.if exists(${BOBJ_DIR}/src/tools/tld/tld)
TLD?=	${BOBJ_DIR}/src/tools/tld/tld
.elif exists(${OBJ_DIR}/src/tools/tld/tld)
TLD?=	${OBJ_DIR}/src/tools/tld/tld
.else
TLD?=	tld
.endif

.if exists(${BOBJ_DIR}/src/tools/tnc/tnc)
TNC?=	${BOBJ_DIR}/src/tools/tnc/tnc
.elif exists(${OBJ_DIR}/src/tools/tnc/tnc)
TNC?=	${OBJ_DIR}/src/tools/tnc/tnc
.else
TNC?=	tnc
.endif

.if exists(${BOBJ_DIR}/src/tools/tspec/tspec)
TSPEC?=	${BOBJ_DIR}/src/tools/tspec/tspec
.elif exists(${OBJ_DIR}/src/tools/tspec/tspec)
TSPEC?=	${OBJ_DIR}/src/tools/tspec/tspec
.else
TSPEC?=	tspec
.endif

CCOPTS+=	-D_${OSVER}

SYS_INCLUDES=	"-I/usr/include"
STRIP= :
RANLIB=		ranlib
EXEC_SUFFIX=

BUILD_ERRORS=	${BASE_DIR}/src/build/BUILD_ERRORS

.endif	# !defined(_TENDRA_COMPILER_MK_)
