# $TenDRA$

CFLAGS= -I${.CURDIR} -I.
.PATH : ${.CURDIR} ${.CURDIR}/templ .

PROG = tnc

SRCS=	alignment.c analyser.c bitstream.c check.c de_capsule.c \
	de_unit.c decode.c enc_cap.c encode.c eval.c fetch.c \
	file.c help.c high.c main.c node.c read.c read_cap.c \
	shape.c table.c tdf.c utility.c write.c

DEPEND_SRC=	tdf.c tdf.h check_exp.h

CLEANFILES+=	tdf.c tdf.h check_exp.h

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"
