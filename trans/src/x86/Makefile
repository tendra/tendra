# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_X86

# TODO: these are not yet selectable at runtime
#TRANS_CFLAGS+=	-D NEWDIAGS
#TRANS_CFLAGS+=	-D NEWDWARF
TRANS_CFLAGS+=	-D STABS
#TRANS_CFLAGS+=	-D DWARF

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/x86
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/diag
#PARTS+= src/common/newdiag
#PARTS+= src/common/dwarf
#PARTS+= src/common/dwarf2
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	assembler.c
SRCS+=	c_arith_type.c
SRCS+=	codec.c
SRCS+=	coder.c
SRCS+=	cproc.c
SRCS+=	dw2_config.c
SRCS+=	dw2_extra.c
SRCS+=	evaluate.c
SRCS+=	glopt.c
SRCS+=	inlinechoice.c
SRCS+=	instr.c
SRCS+=	instr386.c
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

SRCS+=	stabs_reform.c
#SRCS+=	cv_reform.c
#SRCS+=	dwarf_reform.c

SRCS+=	diag_out.c
#SRCS+=	cv_fns.c
#SRCS+=	cv_outtype.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

