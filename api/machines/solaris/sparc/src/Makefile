# $Id$

.include <tendra.situ.mk>

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=	-Ysystem

all:: crt1.o crti.o crtn.o dwarf.o
	@${ECHO} all done

crt1.o: crt1.s
	${TCC_IN_SITU} ${TCCOPTS} -c crt1.s

crti.o: crti.s
	${TCC_IN_SITU} ${TCCOPTS} -c crti.s

crtn.o: crtn.s
	${TCC_IN_SITU} ${TCCOPTS} -c crtn.s

dwarf.o: dwarf.t
	${TCC_IN_SITU} -Wt,-T -c dwarf.t

dwarf.t: dwarf.p
	${TNC} dwarf.p dwarf.t

.include "Makefile.inc"
