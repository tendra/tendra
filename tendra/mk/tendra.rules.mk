# TenDRA make suffix rules
#
# $Id$

.include <tendra.base.mk>

PARTIMP=        ${.IMPSRC:C/^${BASE_DIR}\///1}

# Implied rules.

.SUFFIXES: .o .c .sid .j .pl

.c.o:
	@${ECHO} "# Compiling ${PARTIMP}"
	${CC} ${CCOPTS} -c ${.IMPSRC} -o ${.TARGET}

.pl.j:
	@${ECHO} "# Transforming ${PARTIMP}"
	${TPL} ${.IMPSRC} ${.TARGET}

.sid.c:
	@${ECHO} "# Transforming ${PARTIMP} and ${PARTIMP:S/.sid/.act/}"
	${SID} ${SIDOPTS} ${.IMPSRC} ${.IMPSRC:S/.sid/.act/} ${.TARGET} \
		${.TARGET:S/.c/.h/}
