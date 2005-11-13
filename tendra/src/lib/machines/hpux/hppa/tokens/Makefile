# $TenDRA$

.PATH : ${.CURDIR} ${OBJ_DIR} ${.CURDIR}/../src . ${.CURDIR}/../../../common/tokens ${.CURDIR}/../../../common/src

TCC_OPTS+=	-yTENDRA_BASEDIR=${OBJ_PREFIX} \
		-Y${DEFAULT_BUILD} \
		-J${OBJ_PREFIX}/lib/apis/lib/posix \
		-J${OBJ_PREFIX}/lib/apis/lib/ansi


DEPEND_SRC=	except_toks.t var_toks.t dep_toks.j \
		map_toks.j target_tok.tl sys_toks.j sys.j \
		crtp_n.o dyn_begin.o dyn_end.o


# Where these get installed!
INSTALL_LIB=		target_tok.tl
INSTALL_LIB_SYS=	crtp_n.o dyn_begin.o dyn_end.o


except_toks.t: except_toks.j
	${TCC} ${TCC_OPTS} \
	-Y${SRC_DIR}/src/lib/machines/common/tokens/except_toks -Ft -o ${.TARGET} ${.ALLSRC}

var_toks.t: var_toks.j
	${TCC} ${TCC_OPTS} \
	-Y${SRC_DIR}/src/lib/machines/common/tokens/var_toks -Ft -o ${.TARGET} ${.ALLSRC}

target_tok.tl: dep_toks.j map_toks.j except_toks.t var_toks.t
	${TLD} -mc -o ${.TARGET} ${.ALLSRC}

sys_toks.j: c_toks.j dep_toks.j map_toks.j
	${TLD} -o ${.TARGET} ${.ALLSRC}

sys.j: sys_toks.j
	${TNC} -t -d -L'.~' sys_toks.j ${.TARGET}

CLEANFILES=	${DEPEND_SRC} c_toks.j except_toks.j var_toks.j

.include "${.CURDIR}/../../../../../../mk/base/tendra.prog.mk"
