# $Id$

.include "Makefile.inc"


HEADERS+=	bistream.h
HEADERS+=	bitvec.h
HEADERS+=	bostream.h
HEADERS+=	common.h
HEADERS+=	cstring-list.h
HEADERS+=	cstring.h
HEADERS+=	dalloc.h
HEADERS+=	dstring.h
HEADERS+=	error.h
HEADERS+=	exception.h
HEADERS+=	istream.h
HEADERS+=	nstring-list.h
HEADERS+=	ostream.h

.include <tendra.base.mk>
.include <tendra.functions.mk>


install:: ${HEADERS}
	@${CONDCREATE} "${PREFIX_INCLUDE}" "${PREFIX_INCLUDE}/exds"
.for header in ${HEADERS}
	${INSTALL} -m 644 ${header} ${PREFIX_INCLUDE}/exds/
.endfor

