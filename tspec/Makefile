# $Id$

.include "Makefile.inc"


.if !exists(Makefile.defs)
.BEGIN:
	@${ECHO} "Please run 'makedefs' prior to running (b)make"
	@${ECHO}
	@${EXIT} 1;
.endif


SUBDIR+=	src
SUBDIR+=	doc

.include <tendra.subdir.mk>


#TSPEC_FLAGS = -Otspec/TenDRA/include -Stspec/TenDRA/src -a
# TODO Note posix3 is work in progress and therefore disabled
#BASE_APIS = ansi iso posix posix1 posix2 unix95 xpg3 xpg4 svid3 svid3
#EXT_APIS = bsd_extn dummy gcc cpp motif/1_2 \
#	x5/aw x5 x5/ext x5/lib x5/mit x5/mu x5/proto x5/t
#
#	+${MKDIR} tspec
#	for api in ${BASE_APIS}; do \
#		src/tspec ${TSPEC_FLAGS} -Ibase $$api; \
#	done
#	for api in ${EXT_APIS}; do \
#		src/tspec ${TSPEC_FLAGS} -Ibase -Iextension $$api; \
#	done
#
#install: tspec
#	$(INSTALL) -m 755 -d $(SHAREDIR)
#	$(COPY) -R tspec $(SHAREDIR)/

