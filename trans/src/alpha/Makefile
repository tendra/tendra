# $Id$

.include "Makefile.inc"


TRANS_CFLAGS+=	-D TRANS_ALPHA

# XXX: the Alpha code currently assumes BLDARCHBITS is 64.
# Some parts use the INT64 abstraction; others do not. Until that's sorted
# out, I'm lying about BLDARCHBITS here, just so this code isn't left out
# of the build under -DALLARCH.
#TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}
TRANS_CFLAGS+=	-D BLDARCHBITS=64

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/alpha


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/diag
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/symtab
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	alpha_ins.c
SRCS+=	code_here.c
SRCS+=	coder.c
SRCS+=	comp_eq_exp.c
SRCS+=	cross.c
SRCS+=	diag_out.c
SRCS+=	symdiag_out.c
SRCS+=	dump_distr.c
SRCS+=	eval.c
SRCS+=	extern_adds.c
SRCS+=	fail.c
SRCS+=	float.c
SRCS+=	frames.c
SRCS+=	getregs.c
SRCS+=	glopt.c
SRCS+=	guard.c
SRCS+=	handle_sregs.c
SRCS+=	inlinechoice.c
SRCS+=	inst_fmt.c
SRCS+=	is_worth.c
SRCS+=	labels.c
SRCS+=	locate.c
SRCS+=	machine.c
SRCS+=	machine_toks.c
SRCS+=	driver.c
SRCS+=	move.c
SRCS+=	oddtest.c
SRCS+=	operators.c
SRCS+=	out_ba.c
SRCS+=	pseudo.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	scan.c
SRCS+=	spec.c
SRCS+=	spec_tok.c
SRCS+=	special.c
SRCS+=	tempdecs.c
SRCS+=	translate.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

