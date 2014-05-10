# $Id$

.include "Makefile.inc"


TRANS_CFLAGS+=	-D TRANS_HPPA
TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/hppa
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	c_arith_type.c
SRCS+=	codehere.c
SRCS+=	comment.c
SRCS+=	diag_out.c
SRCS+=	eval.c
SRCS+=	frames.c
SRCS+=	getregs.c
SRCS+=	glopt.c
SRCS+=	guard.c
SRCS+=	hppains.c
SRCS+=	inlinechoice.c
SRCS+=	inst_fmt.c
SRCS+=	is_worth.c
SRCS+=	labels.c
SRCS+=	locate.c
SRCS+=	machine.c
SRCS+=	machine_toks.c
SRCS+=	main.c
SRCS+=	makecode.c
SRCS+=	move.c
SRCS+=	muldvrem.c
SRCS+=	needscan.c
SRCS+=	oprators.c
SRCS+=	proc.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	spec_tok.c
SRCS+=	special.c
SRCS+=	tempdecs.c
SRCS+=	translat.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

