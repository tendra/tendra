# $Id$

SRC2=	${.CURDIR}/../../../common/tokens

TDFLIB=		target_tok.tl
CAPSULES=	dep_toks.j map_toks.j except_toks.t var_toks.t
PLTEXT=		c_toks.j dep_toks.j map_toks.j

all: sys.j
	@${ECHO} all done

${TDFLIB}: ${CAPSULES}
	${TLD} -mc -o ${TDFLIB} ${CAPSULES}

except_toks.t: except_toks.j ${SRC2}/except_toks
	${TCC} -Y${SRC2}/except_toks -Ft -o except_toks.t except_toks.j

var_toks.t: var_toks.j ${SRC2}/var_toks
	${TCC} -Y${SRC2}/var_toks -Ft -o ${OBJ_SDIR}/${.TARGET}\
		${OBJ_SDIR}/var_toks.j

sys_toks.j: ${PLTEXT}
	${TLD} -o ${OBJ_SDIR}/${.TARGET} ${PLTEXT:S/^/${OBJ_SDIR}\//}

sys.j: sys_toks.j
	${TNC} -t -d -L'.~' ${OBJ_SDIR}/sys_toks.j ${OBJ_SDIR}/${.TARGET}

clobber: clean
	${REMOVE} ${TDFLIB}
	${REMOVE} ${CAPSULES}
	${REMOVE} c_toks.j sys_toks.j sys.j
	${REMOVE} except_toks.j var_toks.j

#.include "../Makefile.inc"
.include "../../../Makefile.inc"

.PATH:	${SRC2} ${OBJ_SDIR}
