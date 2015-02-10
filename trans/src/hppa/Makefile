# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_HPPA

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/hppa
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


TRANS_DEBUG?= diag3

# TODO: these are not yet selectable at runtime
.if "${TRANS_DEBUG}" == "diag3"

TRANS_CFLAGS+= -D TDF_DIAG3

PARTS+= src/common/diag3

TRANS_CFLAGS+= -D DIAG3_STABS

SRCS+= stabs_diag3.c

.else

.BEGIN:
	@${ECHO} '$${TRANS_DEBUG} unrecognised'
	@${EXIT} 1;

.endif


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+=	src/common/shared
PARTS+=	src/common/construct
PARTS+=	src/common/linkinfo
PARTS+=	src/common/reader
PARTS+=	src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	ashof.c
SRCS+=	c_arith_type.c
SRCS+=	code_here.c
SRCS+=	comment.c
SRCS+=	eval.c
SRCS+=	frames.c
SRCS+=	getregs.c
SRCS+=	global_opt.c
SRCS+=	guard.c
SRCS+=	hppains.c
SRCS+=	inlinechoice.c
SRCS+=	inst_fmt.c
SRCS+=	is_worth.c
SRCS+=	labels.c
SRCS+=	locate.c
SRCS+=	reg_result.c
SRCS+=	machine_toks.c
SRCS+=	driver.c
SRCS+=	make_code.c
SRCS+=	move.c
SRCS+=	muldvrem.c
SRCS+=	scan.c
SRCS+=	oprators.c
SRCS+=	proc.c
SRCS+=	regable.c
SRCS+=	regalloc.c
SRCS+=	regexps.c
SRCS+=	special.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	tempdecs.c
SRCS+=	translate.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

