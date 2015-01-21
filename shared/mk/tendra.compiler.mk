# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


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
#  ${TCC}    - TenDRA
#  ${GCC}    - The GNU Compiler Collection
#  ${PCC}    - The Portable C Compiler
#  ${CLANG}  - The Clang C compiler
#  ${HPCC}   - HP's ANSI C Compiler
#  ${TINYCC} - The Tiny C Compiler
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


# TODO: attempt to guess based on ${CC} for common compilers.
# Note that "tcc" is not included here to prevent ambiguity with tinycc.
# TODO: think more about this. we need ${CLANG} to take precidence over ${CC}
# TODO: can this use sh's 'case x in y' construct?
. if defined(CC)
.  if ${CC:T:Mgcc}
GCC?=	${CC}
.  elif ${CC:T:Mpcc}
PCC?=	${CC}
.  elif ${CC:T:Mclang}
CLANG?=	${CC}
.  endif
. endif


. if defined(TCC)

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

. elif defined(GCC)

#GPPOPTS?=	-std=c89
GCCOPTS?=	-std=c89
GXXOPTS?=	-std=c++98

#CPP:=		${GCC} -E
CC:=		${GCC}
CXX:=		${GCC}

#CPPFLAGS+=	${GPPOPTS}
CFLAGS+=	${GCCOPTS}
CXXFLAGS+=	${GXXOPTS}
CCOPTS+=	-pedantic -O2 -Wall

# This gives too many false positives for convoluted code
CCOPTS+=	-Wno-uninitialized

. elif defined(CLANG)

CLANGOPTS?=	-std=c89
CLANGXXOPTS?=	-std=c89

CC:=	${CLANG}
CXX:=	${CLANG}

CFLAGS+=	${CLANGOPTS}
CXXFLAGS+=	${CLANGXXOPTS}
CCOPTS+=	-pedantic -O3

. elif defined(PCC)

PCCOPTS?=
PXXOPTS?=

CC:=	${PCC}
CXX:=	${PCC}

CFLAGS+=	${PCCOPTS}
CXXFLAGS+=	${PXXOPTS}
CCOPTS+=	-O

. elif defined(HPCC)

HPCCOPTS?= -fast -DD32 +w2

CC:=	${HPCC}
CXX:=	${HPCC}

CFLAGS+=	${HPCCOPTS}
CXXFLAGS+=	${HPXXOPTS}
CCOPTS+=

. elif defined(TINYCC)

TINYCCOPTS?=	-Wunsupported -Wwrite-strings -Wall
#TINYCCXXOPTS?=

CC:=	${TINYCC}
#CXX:=	${TINYCC}

. else

CC?=		cc
CXX?=		c++
CFLAGS+=
CXXFLAGS+=
CCOPTS+=

. endif



.endif
