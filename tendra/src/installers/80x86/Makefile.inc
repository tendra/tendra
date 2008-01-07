# $TenDRA$

SRCDIRS+=	80x86/common

# installers/80x86/common
SRCS+=	c_arith_type.c codec.c coder.c cproc.c dw2_extra.c evaluate.c glopt.c \
	inlinechoice.c instr.c instr386.c is_worth.c localflags.c \
	machine_toks.c operand.c out.c overlap.c reg_record.c scan2.c spec.c \
	spec_tok.c trans.c translate.c tv_callees.c weights.c
	
CAT_EXTRA+=	${.CURDIR}/../common/msgarch.cat
