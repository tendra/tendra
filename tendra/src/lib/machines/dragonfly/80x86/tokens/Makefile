# $Id$

SRC2=	${.CURDIR}/../../..//common/tokens

#TCC=	tcc
#TLD=	tld
#TNC=	tnc

LIB=		target_tok.tl
LIB_FILES=	dep_toks.j map_toks.j except_toks.t var_toks.t
SYS_FILES=	c_toks.j dep_toks.j map_toks.j

.PATH:	${SRC2}

basic : sys.j
	@${ECHO} all done

${LIB} : ${LIB_FILES}
	@${REMOVE} ${LIB}
	${TLD} -mc -o ${LIB} ${LIB_FILES}

except_toks.t : except_toks.j ${SRC2}/except_toks
	${TCC} -Y${SRC2}/except_toks -Ft -o except_toks.t except_toks.j

var_toks.t : var_toks.j ${SRC2}/var_toks
	${TCC} -Y${SRC2}/var_toks -Ft -o var_toks.t var_toks.j

sys_toks.j : ${SYS_FILES}
	${TLD} -o sys_toks.j ${SYS_FILES}

sys.j : sys_toks.j
	${TNC} -t -d -L'.~' sys_toks.j sys.j

clobber : clean
	${REMOVE} ${LIB}
	${REMOVE} ${LIB_FILES}
	${REMOVE} c_toks.j sys_toks.j sys.j
	${REMOVE} except_toks.j var_toks.j

#.include "../Makefile.inc"
.include "../../../Makefile.inc"
