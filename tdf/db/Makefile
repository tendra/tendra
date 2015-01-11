# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.functions.mk>


FILES+=	README
FILES+=	def_4_0.db
FILES+=	def_4_1.db


#
# User-facing targets
#

all::

clean::

.for file in ${FILES}
install:: ${file}
	@${ECHO} "==> Installing ${file}"
	@${CONDCREATE} "${PREFIX_SHARE}/tdf"
	${INSTALL} -m 644 ${file} "${PREFIX_SHARE}/tdf/${file}"
.endfor

