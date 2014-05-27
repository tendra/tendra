# $Id$

.include "Makefile.inc"


TRANS_CFLAGS+=	-D TRANS_80x86
TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

# TODO: these are not yet selectable at runtime
# -D NEWDIAGS
# -D NEWDWARF

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/80x86
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/diag
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/common/utility

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	assembler.c
SRCS+=	c_arith_type.c
SRCS+=	codec.c
SRCS+=	coder.c
SRCS+=	cproc.c
SRCS+=	diag_out.c
SRCS+=	dw2_config.c
SRCS+=	dw2_extra.c
SRCS+=	evaluate.c
SRCS+=	glopt.c
SRCS+=	inline.c
SRCS+=	instr.c
SRCS+=	instr386.c
SRCS+=	is_worth.c
SRCS+=	localflags.c
SRCS+=	machine.c
SRCS+=	machine_toks.c
SRCS+=	main.c
SRCS+=	operand.c
SRCS+=	out.c
SRCS+=	overlap.c
SRCS+=	reg_record.c
SRCS+=	scan2.c
SRCS+=	spec.c
SRCS+=	spec_tok.c
SRCS+=	translate.c
SRCS+=	tv_callees.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

