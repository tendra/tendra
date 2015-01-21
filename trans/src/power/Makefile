# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_POWER

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
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	ashof.c
SRCS+=	code_here.c
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
SRCS+=	reg_result.c
SRCS+=	machine_toks.c
SRCS+=	macro.c
SRCS+=	driver.c
SRCS+=	makecode.c
SRCS+=	mask.c
SRCS+=	mem_copy.c
SRCS+=	move.c
SRCS+=	muldvrem.c
SRCS+=	scan.c
SRCS+=	oprators.c
SRCS+=	parameter.c
SRCS+=	pp.c
SRCS+=	proc.c
SRCS+=	record_bit.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	stack.c
SRCS+=	tempdecs.c
SRCS+=	translate.c
SRCS+=	weights.c

SRCS+=	stabs_reform.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

