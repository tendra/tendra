# $Id$

.include "Makefile.inc"


TRANS_CFLAGS+=	-D TRANS_680x0
TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/680x0
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/diag
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
SRCS+=	mach_ins.c
SRCS+=	mach_op.c
SRCS+=	driver.c
SRCS+=	ops_float.c
SRCS+=	ops_int.c
SRCS+=	ops_logic.c
SRCS+=	ops_misc.c
SRCS+=	output.c
SRCS+=	peephole.c
SRCS+=	scan2.c
SRCS+=	special_exps.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	stab_types.c
SRCS+=	tests.c
SRCS+=	translate.c
SRCS+=	utility.c
SRCS+=	weights.c
SRCS+=	where.c
SRCS+=	xdb_basics.c
SRCS+=	xdb_output.c
SRCS+=	xdb_types.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

