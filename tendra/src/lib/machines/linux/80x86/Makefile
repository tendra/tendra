# $TenDRA$

.PATH : ${.CURDIR} ${OBJ_DIR}/tokens

# include
DATA=	include/alloca.h include/ctype.h include/float.h \
	include/langinfo.h include/limits.h include/math.h include/nl_types.h \
	include/stdarg.h include/stddef.h include/ulimit.h include/unistd.h \
	include/varargs.h include/xti.h

# include/gnu
DATA+=	include/gnu/types.h

# include include/sys
DATA+=	include/sys/msg.h include/sys/sem.h include/sys/shm.h include/sys/types.h 

# include/linux
DATA+=	include/linux/signal.h

# include/asm
DATA+=	include/asm/bitops.h

# startup
DATA+=	startup/ansi.h startup/bsd_extn.h startup/cpp.h startup/gcc.h \
	startup/iso.h startup/iso99.h startup/posix.h startup/posix1.h \
	startup/posix2.h startup/svid3.h startup/system.h startup/unix95.h \
	startup/xpg3.h startup/xpg4.h

# tokens
TOKEN=	tokens/dep_toks.pl tokens/except_toks.pl tokens/map_toks.pl 

MAKEDIR=	include include/gnu include/sys include/linux include/asm startup tokens
TOKEN_OBJ=	${TOKEN:R:S/$/.j/g}
DEPEND_SRC=	${DATA} sys_toks.j

${DATA}:
	@${BIN_CP} ${ARGS_CP} -R ${.CURDIR}/${.TARGET} ${OBJ_DIR}/${.TARGET}

sys_toks.j: ${TOKEN_OBJ}
	${TLD} -o tokens/${.TARGET} ${TOKEN_OBJ}


CLEANOPT=	-r
CLEANFILES=     ${MAKEDIR}

.include "${.CURDIR}/../../../../../mk/base/tendra.prog.mk"
