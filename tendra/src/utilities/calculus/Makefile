# $TenDRA$

CFLAGS+= -I${.CURDIR} \
	-I${SRC_DIR}/src/include -I.
.PATH : ${.CURDIR}

USE_LIBTEN=yes

PROG=	calculus

SRCS=	calculus.c

#sources in the parent dir
SRCS+=	check.c code.c common.c disk.c lex.c main.c \
	output.c pretty.c print.c read.c syntax.c \
	template.c token.c write.c

DEPEND_SRC=	keyword.h lexer.h syntax.c

syntax.c: syntax.sid syntax.act
	${SID} ${SID_OPTS} ${.CURDIR}/syntax.sid ${.CURDIR}/syntax.act \
	${OBJ_DIR}/syntax.c ${OBJ_DIR}/syntax.h

keyword.h:
	${LEXI} -k ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

lexer.h:
	${LEXI} ${.CURDIR}/lexer.lxi ${OBJ_DIR}/${.TARGET}

assert_def.h calculus.h cmd_ops.h type_ops.h::
	${OBJ_DIR}/calculus -a -x calculus.alg

print_def.h::
	${OBJ_DIR}/calculus -p calculus.alg

read_def.h write_def.h::
	${OBJ_DIR}/calculus -d calculus.alg disk.alg .

CLEANFILES+=	keyword.h lexer.h syntax.c syntax.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
