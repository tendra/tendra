# $Id$

PREFIX ?= /usr/local

TARGETS = bitvec.h cstring.h dalloc.h dstring.h error.h \
	exception.h istream.h ostream.h common.h \
	bistream.h bostream.h cstring-list.h nstring-list.h

all:

clean:

install: $(TARGETS)
	install -m 755 -d ${PREFIX}/include
	install -m 755 -d ${PREFIX}/include/exds
	install -m 644 $(TARGETS) ${PREFIX}/include/exds

