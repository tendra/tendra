# $Id$

.include "Makefile.inc"


TRANS_CFLAGS+=	-D TRANS_SPARC
TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

# TODO: these are not yet selectable at runtime
TRANS_CFLAGS+=	-D NEWDIAGS
TRANS_CFLAGS+=	-D NEWDWARF

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/sparc
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/newdiag
PARTS+=	src/common/dwarf2
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	code_here.c
SRCS+=	comment.c
SRCS+=	diag_out.c
SRCS+=	dw2_config.c
SRCS+=	dw2_extra.c
SRCS+=	eval.c
SRCS+=	getregs.c
SRCS+=	glopt.c
SRCS+=	guard.c
SRCS+=	inlinechoice.c
SRCS+=	inst_fmt.c
SRCS+=	is_worth.c
SRCS+=	labels.c
SRCS+=	locate.c
SRCS+=	machine.c
SRCS+=	machine_toks.c
SRCS+=	driver.c
SRCS+=	makecode.c
SRCS+=	move.c
SRCS+=	muldvrem.c
SRCS+=	needscan.c
SRCS+=	oprators.c
SRCS+=	proc.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	sparcins.c
SRCS+=	spec_tok.c
SRCS+=	special.c
SRCS+=	tempdecs.c
SRCS+=	translate.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

