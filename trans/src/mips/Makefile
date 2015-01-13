# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_MIPS
TRANS_CFLAGS+=	-D BLDARCHBITS=${BLDARCHBITS}

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/mips
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


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


#TCCOPTS=-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	ashof.c
SRCS+=	code_here.c
SRCS+=	comp_eq_exp.c
SRCS+=	diag_out.c
SRCS+=	dump_distr.c
SRCS+=	eval.c
SRCS+=	extern_adds.c
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
SRCS+=	mips_ins.c
SRCS+=	move.c
SRCS+=	scan.c
SRCS+=	new_code.c
SRCS+=	oddtest.c
SRCS+=	operators.c
SRCS+=	out_ba.c
SRCS+=	psu_ops.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	special.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	tempdecs.c
SRCS+=	translate.c
SRCS+=	weights.c

SRCS+=	stabs_reform.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

