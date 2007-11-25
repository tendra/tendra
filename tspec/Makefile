# $Id$

TSPEC_FLAGS = -Otspec/include -Stspec/src -Iapis -a

TSPEC = tspec -v
MKDIR = mkdir
REMOVE = rm -f

# This order might seem weird, but it has to do with dependencies on another
# APIs and minimising the build costs.
APIS = ansi iso posix cpp gcc posix1 posix2 unix95 xpg3 xpg4 svid3 bsd_extn \
	dummy motif/1_2 svid3 x5/aw x5 x5/ext x5/lib x5/mit x5/mu x5/proto x5/t

all: tspec

tspec: apis
	+${MKDIR} tspec
	for api in ${APIS}; do \
		${TSPEC} ${TSPEC_FLAGS} $$api; \
	done

clean:
	$(REMOVE) -r tspec

