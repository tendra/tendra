# $TenDRA$

.PATH : ${.CURDIR} ${OBJ_DIR}/tokens

# include
DATA=	include/ctype.h include/limits.h include/stdarg.h include/unistd.h include/xti.h 

# include/sys
DATA=	include/sys/param.h include/sys/shm.h

# startup
DATA+=	startup/ansi.h startup/bsd_extn.h startup/cpp.h startup/gcc.h startup/iso.h \
	startup/posix.h startup/posix1.h startup/posix2.h startup/svid3.h startup/ \
	startup/system.h startup/unix95.h startup/xpg3.h startup/xpg4.h 

# tokens
TOKEN=	tokens/dep_toks.pl tokens/except_toks.pl tokens/map_toks.pl

MAKEDIR=	include include/sys startup tokens
TOKEN_OBJ=	${TOKEN:R:S/$/.j/g}
DEPEND_SRC=	${DATA} sys_toks.j

${DATA}:
	@cp -vR ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

sys_toks.j: ${TOKEN_OBJ}
	${TLD} -o tokens/${.TARGET} ${TOKEN_OBJ}


CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
