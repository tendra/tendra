# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_X86

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/x86
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


TRANS_DEBUG?= diag4

# TODO: these are not yet selectable at runtime
.if "${TRANS_DEBUG}" == "diag3"

TRANS_CFLAGS+= -D TDF_DIAG3

PARTS+= src/common/diag3

TRANS_CFLAGS+= -D DIAG3_CODEVIEW
TRANS_CFLAGS+= -D DIAG3_STABS
TRANS_CFLAGS+= -D DIAG3_DWARF1

PARTS+= src/common/codeview
PARTS+=	src/common/dwarf1

SRCS+= stabs_diag3.c

.elif "${TRANS_DEBUG}" == "diag4"

TRANS_CFLAGS+= -D TDF_DIAG4
TRANS_CFLAGS+= -D DWARF2
TRANS_CFLAGS+= -D STABS

PARTS+= src/common/diag4
PARTS+= src/common/dwarf2

SRCS+= dw2_config.c
SRCS+= dw2_extra.c
SRCS+= stabs_diag4.c

.else

.BEGIN:
	@${ECHO} '$${TRANS_DEBUG} unrecognised'
	@${EXIT} 1;

.endif


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+= src/common/shared
PARTS+=	src/common/tdf
PARTS+=	src/common/special
PARTS+= src/common/construct
PARTS+= src/common/linkinfo
PARTS+=	src/common/flpt
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	assembler.c
SRCS+=	codec.c
SRCS+=	make_code.c
SRCS+=	cproc.c
SRCS+=	eval.c
SRCS+=	inlinechoice.c
SRCS+=	instr.c
SRCS+=	ops.c
SRCS+=	ops_float.c
SRCS+=	ops_int.c
SRCS+=	ops_logic.c
SRCS+=	ops_move.c
SRCS+=	ops_stack.c
SRCS+=	is_worth.c
SRCS+=	reg_result.c
SRCS+=	machine_toks.c
SRCS+=	driver.c
SRCS+=	operand.c
SRCS+=	out.c
SRCS+=	overlap.c
SRCS+=	reg_record.c
SRCS+=	scan.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	translate.c
SRCS+=	tv_callees.c
SRCS+=	weights.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

