# $Id$

PREFIX ?= /usr/local

CC = cc
CFLAGS = -I ../include
LINK = ld -shared

# For NetBSD:
# LINK = ld -shared -rpath $(PREFIX)/lib

# For Darwin:
# LINK = gcc -dynamiclib -single_module

# For gcc:
# CC = gcc
# CFLAGS -fPIC -Wall -Werror -ansi -pedantic -O2 -I ../include

# For TenDRA, -Ysystem is required for stdint.h:
# CC = tcc
# CFLAGS = -Ysystem -Xs -I ../include

AR ?= ar
INSTALL ?= install
REMOVE ?= rm -f
RANLIB ?= ranlib

TARGETS = bitvec.o cstring.o dalloc.o dstring.o error.o \
	exception.o istream.o ostream.o syntax.o \
	bistream.o bostream.o cstring-list.o nstring-list.o


all: libexds.so libexds.a ${TARGETS}

clean:
	${REMOVE} libexds.a libexds.so ${TARGETS}

install: libexds.so libexds.a
	$(INSTALL) -m 755 -d $(PREFIX)/lib
	$(INSTALL) -m 644 libexds.a ${PREFIX}/lib/
	$(INSTALL) -m 644 libexds.so ${PREFIX}/lib/

libexds.so: ${TARGETS}
	${LINK} -o libexds.so ${TARGETS}

libexds.a: $(TARGETS)
	$(AR) r libexds.a $(TARGETS)
	$(RANLIB) libexds.a

