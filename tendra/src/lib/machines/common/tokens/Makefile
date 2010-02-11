# $Id$

.include "Makefile.inc"


# This makefile is depended on from lib/machines/*/*/tokens; it is not built
# directly (that is, its 'all' target is not used). Outputs built are:
#  var_toks.t
#  c_toks.j
#
# gen_tokens is just a little helper utility, and is not installed anywhere;
# It's intended to be used by developers who are adding new machines.


${OBJ_SDIR}/var_toks.t: ${OBJ_SDIR}/var_toks.j var_toks
	@${ECHO} "==> Linking ${WRKDIR}/${.TARGET:T}"
	${TCC} ${TCCOPTS} -Yvar_toks -Ft -o ${.TARGET} ${OBJ_SDIR}/var_toks.j


clean::
	${REMOVE} ${OBJ_SDIR}/c_toks.j ${OBJ_SDIR}/var_toks.t


TPLSRCS += c_toks.tpl
TPLSRCS += var_toks.tpl

.include <tendra.tpl.mk>


SRCS=	gen_tokens.c

.include <tendra.obj.mk>


PROG=	gen_tokens

.include <tendra.prog.mk>

