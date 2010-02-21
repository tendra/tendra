# TenDRA make compiler infrastructure
#
# $Id$

.if !defined(_TENDRA_COMPILER_MK_)
_TENDRA_COMPILER_MK_=1


#
# We need to identify which compiler is being used, for two reasons: firstly,
# to set a few sensible global default options here, and secondly to permit
# compiler-specific options per directory within the source (typically to
# specify APIs and increase strictness).
#
#
# The following compilers may be specified by setting their corresponding
# environment variables when calling make(1):
#
#  ${TCC} - TenDRA
#  ${GCC} - The GNU Compiler Collection
#
# If none of the above are set, no compiler-specific default options are used
# (either globally, or per directory).
#
#
# Each of these (where '*' is one of the above) may have language-specific
# global default options:
#
#  ${*CPPOPTS} - Options for preprocessing
#  ${*CCOPTS}  - Options for C
#  ${*CXXOPTS} - Options for C++
#
# The global defaults for these may be overridden by explicitly specifying them
# to make(1), which will replace any existing values.
#
# ${CCOPTS} is unrelated to the above; it serves to specify options which are
# language-independant, applicable to all compilers (such as -I, for example).
#
#
# If present, any compiler-specific options (either global, or per-directory)
# are appended to CFLAGS et al., along with whatever content those may have
# already.
#
# The net effect is that ${CC} and ${C*FLAGS} may be explicitly specified to
# make(1) as per usual, and doing so will not remove any compiler-specific
# options, if present.
#


. if "${TCC}" != ""

#TPPOPTS?=
TCCOPTS?=
TXXOPTS?=	-Yc++

#CPP:=		${TCC} -E
CC:=		${TCC}
CXX:=		${TCC}

#CPPFLAGS+=	${TPPOPTS}
CFLAGS+=	${TCCOPTS}
CXXFLAGS+=	${TXXOPTS}
CCOPTS+=

. elif "${GCC}" != ""

#GPPOPTS?=	-std=c89
GCCOPTS?=	-std=c89
GXXOPTS?=	-std=c++98

#CPP:=		${GCC} -E
CC:=		${GCC}
CXX:=		${GCC}

#CPPFLAGS+=	${GPPOPTS}
CFLAGS+=	${GCCOPTS}
CXXFLAGS+=	${GXXOPTS}
CCOPTS+=	-pedantic -O2

. else

CC?=		cc
CXX?=		c++
CFLAGS+=
CXXFLAGS+=
CCOPTS+=

. endif


# Options applicable to all compilers
. if "${OSVER}" != ""
CCOPTS+= -D_${OSVER}
. endif



#
# In lieu of bootstrapping here in the makefiles (as was previously done by
# passing -DBOOTSTRAP), the build is now simply re-executed with ${TCC} set to
# some version of tcc - either a temporary version built for bootstrapping, or
# a previously installed "real" version.
#
# However, some parts of the build (particularly for API building) rely on
# compiling source to TDF, and tcc is required for this. In situations where
# we're building using a compiler other than tcc, the (empty) ${TCC} variable
# is set to reference the version just built in ${OBJ_DIR}, for this use only.
#
# This will eventually go away, when tcc, and the producers and installers are
# all moved out separately.
#
# TODO: maybe just call the producer directly, since this is only ever used to
#       build .j files
#

. if "${TCC}" == ""
TCC=	tcc
#TCC=	tcc	\
#		-Y${OBJ_DIR}/src/lib/env/build	\
#		-yTENDRA_BASEDIR=${OBJ_DIR}/src

# TODO: Our .cc files depend on tccisms. This is mostly for the benefit of
# src/lib/cpp, and may be better suited to live there.
CXX:=		${TCC}
CXXFLAGS:=	-Yc++
. endif



.endif	# !defined(_TENDRA_COMPILER_MK_)
