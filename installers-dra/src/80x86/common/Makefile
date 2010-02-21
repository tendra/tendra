# $Id$

.include "Makefile.inc"


CCOPTS+=	-I ${BASE_DIR}/${INCLUDE}
CCOPTS+=	-I ../../common/construct
CCOPTS+=	-I ../../common/diag
CCOPTS+=	-I ../../common/dwarf2
CCOPTS+=	-I ../../common/linkinfo
CCOPTS+=	-I ../../common/reader

SRCS+=	c_arith_type.c
SRCS+=	codec.c
SRCS+=	coder.c
SRCS+=	cproc.c
SRCS+=	dw2_extra.c
SRCS+=	evaluate.c
SRCS+=	glopt.c
SRCS+=	inlinechoice.c
SRCS+=	instr.c
SRCS+=	instr386.c
SRCS+=	is_worth.c
SRCS+=	localflags.c
SRCS+=	machine_toks.c
SRCS+=	operand.c
SRCS+=	out.c
SRCS+=	overlap.c
SRCS+=	reg_record.c
SRCS+=	scan2.c
SRCS+=	spec.c
SRCS+=	spec_tok.c
SRCS+=	trans.c
SRCS+=	translate.c
SRCS+=	tv_callees.c
SRCS+=	weights.c

.include <tendra.obj.mk>

.include <tendra.partial.mk>

