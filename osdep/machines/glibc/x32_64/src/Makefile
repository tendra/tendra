# $Id$

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>

all:: crtbegin.o

crtbegin.o: crtbegin.s
	${TCC} ${TCCOPTS} -c crtbegin.s

install:: all
	@${CONDCREATE} ${PREFIX_LIB}
	@${CONDCREATE} ${PREFIX_LIB}/x86
	${INSTALL} -m 644 crtbegin.o ${PREFIX_LIB}/x86/crtbegin.o
	rm crtbegin.o

.include "Makefile.inc"
