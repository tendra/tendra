# $Id$

SRC2=	${BASE_DIR}/lib/machines/common/src

#TCCOPTS=	-Ysystem

# Environments are not yet installed, so we use them in-situ.
TCCOPTS+=	--SED${OBJ_DIR}/env --CFE

all:: crt1.o crti.o crtn.o dwarf.o
	@${ECHO} all done

crt1.o: crt1.s
	${CC} ${TCCOPTS} -c crt1.s

crti.o: crti.s
	${CC} ${TCCOPTS} -c crti.s

crtn.o: crtn.s
	${CC} ${TCCOPTS} -c crtn.s

dwarf.o: dwarf.t
	${TCC} -Wt,-T -c dwarf.t

dwarf.t: dwarf.p
	${TNC} dwarf.p dwarf.t

.include "Makefile.inc"
