# $Id$

LIB=	tdf
SRCS=	INT64a.o version.o

INT64a.o: INT64b.pl abstract.pl
	${TCC} -c -o ${.TARGET} ${.ALLSRC} -WP,-I${.CURDIR}\
	-Y${BOBJ_DIR}/src/lib/env/build -yTENDRA_BASEDIR=${BOBJ_DIR}/src/ \
	-Ypl_tdf -jtarget_tok -M

.include "../Makefile.inc"
