# $Id$

PREFIX ?= /usr/local
SHAREDIR ?= $(PREFIX)/share

TSPEC_FLAGS = -Otspec/TenDRA/include -Stspec/TenDRA/src -a

MKDIR = mkdir
REMOVE = rm -f
INSTALL = install
COPY = cp

# TODO Note posix3 is work in progress and therefore disabled
BASE_APIS = ansi iso posix cpp posix1 posix2 unix95 xpg3 xpg4 svid3 svid3
EXT_APIS = bsd_extn dummy gcc motif/1_2 \
	x5/aw x5 x5/ext x5/lib x5/mit x5/mu x5/proto x5/t

all: tspec

tspec: apis extension src/tspec
	+${MKDIR} tspec
	for api in ${BASE_APIS}; do \
		src/tspec ${TSPEC_FLAGS} -Iapis $$api; \
	done
	for api in ${EXT_APIS}; do \
		src/tspec ${TSPEC_FLAGS} -Iapis -Iextension $$api; \
	done

clean:
	$(REMOVE) -r tspec
	cd src && $(MAKE) clean

install: tspec
	$(INSTALL) -m 755 -d $(SHAREDIR)
	$(COPY) -R tspec $(SHAREDIR)/

src/tspec:
	cd src && $(MAKE) tspec

