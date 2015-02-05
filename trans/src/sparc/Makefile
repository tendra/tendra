# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_SPARC

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/sparc
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


TRANS_DEBUG?= dwarf1

# TODO: these are not yet selectable at runtime
.if "${TRANS_DEBUG}" == "stabs"

TRANS_CFLAGS+= -D STABS

PARTS+= src/common/diag3

SRCS+= diag_out.c
SRCS+= stabs_reform.c

.elif "${TRANS_DEBUG}" == "stabs4"

TRANS_CFLAGS+= -D STABS
TRANS_CFLAGS+= -D TDF_DIAG4

PARTS+= src/common/diag4

SRCS+= newdiag_out.c

.elif "${TRANS_DEBUG}" == "dwarf1"

TRANS_CFLAGS+= -D DWARF1

PARTS+=	src/common/dwarf1
PARTS+= src/common/diag3

SRCS+= dwarf_reform.c

.elif "${TRANS_DEBUG}" == "dwarf2"

TRANS_CFLAGS+= -D TDF_DIAG4
TRANS_CFLAGS+= -D DWARF2

PARTS+= src/common/diag4
PARTS+= src/common/dwarf2

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
SRCS+=	code_here.c
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
SRCS+=	sparcins.c
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

