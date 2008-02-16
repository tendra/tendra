# $Id$

PREFIX ?= /usr/local
SHAREDIR ?= $(PREFIX)/share

TSPEC_FLAGS = -Otspec/include -Stspec/TenDRA -Iapis -a

MKDIR = mkdir
REMOVE = rm -f
INSTALL = install
COPY = cp

# This order might seem weird, but it has to do with dependencies on another
# APIs and minimising the build costs.
# TODO Note posix3 is work in progress and therefore disabled
APIS = ansi iso posix cpp gcc posix1 posix2 unix95 xpg3 xpg4 svid3 bsd_extn \
	dummy motif/1_2 svid3 x5/aw x5 x5/ext x5/lib x5/mit x5/mu x5/proto x5/t

all: tspec

tspec: apis src/tspec
	+${MKDIR} tspec
	for api in ${APIS}; do \
		src/tspec ${TSPEC_FLAGS} $$api; \
	done

clean:
	$(REMOVE) -r tspec
	cd src && $(MAKE) clean

install: tspec
	$(INSTALL) -m 755 -d $(SHAREDIR)
	$(COPY) -R tspec $(SHAREDIR)/

src/tspec:
	cd src && $(MAKE) tspec

