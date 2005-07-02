# $Id$

SRC2=	${.CURDIR}/../../../common/tokens

TDFLIB=		target_tok.tl
CAPSULES=	dep_toks.j map_toks.j except_toks.t var_toks.t
PLTEXT=		c_toks.j dep_toks.j map_toks.j

.include "../../../Makefile.inc"

TCCOPTS=	-Y${OBJ_DIR}/${ENVIRONMENT}/bootstrap \
		-yTENDRA_BASEDIR="${OBJ_DIR}/src"

all: ${TDFLIB} sys.j
	@${ECHO} all done

${TDFLIB}: ${CAPSULES}
	${TLD} -mc -o ${TDFLIB} ${CAPSULES}

except_toks.t: except_toks.j ${SRC2}/except_toks
	${TCC} ${TCCOPTS} -Y${SRC2}/except_toks -Ft -o ${.TARGET} except_toks.j

var_toks.t: var_toks.j ${SRC2}/var_toks
	${TCC} ${TCCOPTS} -Y${SRC2}/var_toks -Ft -o ${.OBJDIR}/${.TARGET}\
		${.OBJDIR}/var_toks.j

sys_toks.j: ${PLTEXT}
	${TLD} -o ${OBJ_SDIR}/${.TARGET} ${PLTEXT:S/^/${OBJ_SDIR}\//}

sys.j: sys_toks.j
	${TNC} -t -d -L'.~' ${OBJ_SDIR}/sys_toks.j ${OBJ_SDIR}/${.TARGET}

CLEAN_EXTRA=	${TDFLIB} ${CAPSULES} c_toks.j sys_toks.j sys.j except_toks.j\
		var_toks.j

.PATH:	${SRC2} ${OBJ_SDIR} ${.OBJDIR}
