# TenDRA make compiler infrastructure
#
# $Id$

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

CC?= cc
# Assume that the cc on this system is the GNU C Compiler.
.if ${CC} == "cc" || ${CC} == "gcc"
  TCCOPTS=
  WARNS= -W -Wall -Wmissing-prototypes -Wstrict-prototypes
  CCOPTS+= -ansi -pedantic -fno-builtin ${WARNS}
# The Intel C Compiler.
.elif ${CC} == "icc"
  TCCOPTS=
  CCOPTS+=
# The TenDRA C Compiler.
# XXX: How to differentiate between TenDRA and tinycc?
.elif ${CC} == "tcc"
  TCCOPTS= -Ysystem
  CCOPTS+=
.endif

SYS_INCLUDES= "-I/usr/include"
STRIP= :
RANLIB= ranlib
EXEC_SUFFIX=

LD?= ld
LDOPTS=
LIBS= /usr/lib/crt1.o -lc

.if exists(${OBJ_DIR}/src/utilities/sid/sid)
SID ?=${OBJ_DIR}/src/utilities/sid/sid
.else
SID ?=sid
.endif
