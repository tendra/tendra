# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_M68K

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/m68k
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


TRANS_DEBUG?= stabs

# TODO: these are not yet selectable at runtime
.if "${TRANS_DEBUG}" == "stabs"

PARTS+= src/common/diag3

SRCS+= stab_types.c
SRCS+= stabs_reform.c

SRCS+= xdb_basics.c
SRCS+= xdb_output.c
SRCS+= xdb_types.c

.else

.BEGIN:
	@${ECHO} '$${TRANS_DEBUG} unrecognised'
	@${EXIT} 1;

.endif


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yposix

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	68k_globals.c
SRCS+=	assembler.c
SRCS+=	codec.c
SRCS+=	coder.c
SRCS+=	codex.c
SRCS+=	evaluate.c
SRCS+=	general_proc.c
SRCS+=	glopt.c
SRCS+=	inlinechoice.c
SRCS+=	instr.c
SRCS+=	reg_result.c
SRCS+=	machine_toks.c
SRCS+=	mach_ins.c
SRCS+=	mach_op.c
SRCS+=	driver.c
SRCS+=	ops_float.c
SRCS+=	ops_int.c
SRCS+=	ops_logic.c
SRCS+=	ops_misc.c
SRCS+=	output.c
SRCS+=	peephole.c
SRCS+=	scan.c
SRCS+=	special_exps.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	tests.c
SRCS+=	translate.c
SRCS+=	utility.c
SRCS+=	weights.c
SRCS+=	where.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

