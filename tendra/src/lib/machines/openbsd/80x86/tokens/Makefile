# $TenDRA$

.PATH : ${.CURDIR} ${OBJ_DIR} . ${.CURDIR}/../../../common/tokens ${.CURDIR}/../../../common/src

TCC_OPTS+=	-yTENDRA_BASEDIR=${OBJ_PREFIX} \
		-Y${DEFAULT_BUILD} \
		-J${OBJ_PREFIX}/lib/apis/lib/posix \
		-J${OBJ_PREFIX}/lib/apis/lib/ansi


DEPEND_SRC=	except_toks.t var_toks.t dep_toks.j \
		map_toks.j target_tok.tl sys_toks.j sys.j \
		crtp_n.o

except_toks.j: except_toks.pl
	${PL} ${.IMPSRC} ${.TARGET}

except_toks.t: except_toks.j
	${TCC} ${TCC_OPTS} \
	-Y${SRC_DIR}/src/lib/machines/common/tokens/except_toks -Ft -o ${.ALLSRC:R:S/$/.t/} ${.ALLSRC}

var_toks.j: var_toks.pl
	${PL} ${.IMPSRC} ${.TARGET}

var_toks.t: var_toks.j
	${TCC} ${TCC_OPTS} \
	-Y${SRC_DIR}/src/lib/machines/common/tokens/var_toks -Ft -o ${.ALLSRC:R:S/$/.t/} ${.ALLSRC}

target_tok.tl: dep_toks.j map_toks.j except_toks.t var_toks.t
	${TLD} -mc -o ${.TARGET} dep_toks.j map_toks.j except_toks.t var_toks.t

sys_toks.j: c_toks.j dep_toks.j map_toks.j
	${TLD} -o ${.TARGET} c_toks.j dep_toks.j map_toks.j

sys.j: sys_toks.j
	${TNC} -t -d -L'.~' sys_toks.j ${.TARGET}

crtp_n.o: crtp_n.pl
	${TCC} ${TCC_OPTS} \
	-Ypl_tdf -c ${.ALLSRC}

CLEANFILES=	except_toks.j except_toks.t map_toks.j var_toks.j \
		var_toks.t dep_toks.j c_toks.j sys.j sys_toks.j target_tok.tl \
		crtp_n.o

.include "${.CURDIR}/../../../../../../mk/base/tendra.prog.mk"
