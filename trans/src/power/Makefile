# $Id$

.include "Makefile.inc"


TRANS_CFLAGS+=	-D TRANS_POWER
TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/power
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common/linkinfo


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor

.include <tendra.partial.mk>


#TCCOPTS=-Xc -Y32bit -Yansi

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	ash.c
SRCS+=	codehere.c
SRCS+=	comment.c
SRCS+=	diagout.c
SRCS+=	dynamic_init.c
SRCS+=	error.c
SRCS+=	eval.c
SRCS+=	frames.c
SRCS+=	getregs.c
SRCS+=	glopt.c
SRCS+=	guard.c
SRCS+=	inlinechoice.c
SRCS+=	inst_fmt.c
SRCS+=	instruct.c
SRCS+=	is_worth.c
SRCS+=	labels.c
SRCS+=	locate.c
SRCS+=	machine.c
SRCS+=	machine_toks.c
SRCS+=	macro.c
SRCS+=	main.c
SRCS+=	makecode.c
SRCS+=	mask.c
SRCS+=	mem_copy.c
SRCS+=	move.c
SRCS+=	muldvrem.c
SRCS+=	needscan.c
SRCS+=	oprators.c
SRCS+=	parameter.c
SRCS+=	pp.c
SRCS+=	proc.c
SRCS+=	record_bit.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	spec.c
SRCS+=	spec_tok.c
SRCS+=	stack.c
SRCS+=	tempdecs.c
SRCS+=	translat.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

