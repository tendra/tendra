# $TenDRA$

SRCDIRS+=	mips/common

# installers/mips/common
SRCS+=	bstack.c code_here.c comp_eq_exp.c dump_distr.c eval.c extern_adds.c \
	frames.c getregs.c glopt.c guard.c handle_sregs.c inlinechoice.c \
	inst_fmt.c is_worth.c labels.c locate.c machine.c machine_toks.c \
	makesymtab.c mips_ins.c mipsdiags.c move.c needs_scan.c new_code.c \
	new_symbol.c oddtest.c operators.c psu_ops.c regable.c regalloc.c \
	regexps.c spec.c spec_tok.c special.c syms.c tempdecs.c translate.c \
	type_to_aux.c weights.c
