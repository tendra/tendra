# $Id$

#DEST=${OBJ_DIR}/src/lib
#SRC=${BASE}/src/tools/tspec
#API_DIR=${BASE_DIR}/src/lib/apis

#TCCOPTS=	-Yposix1 -Xs
#CCOPTS=		-I${BASE_DIR}/${INCLUDE} -I${.CURDIR}

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

TARGETS = hash.o index.o lex.o main.o makefile.o name.o object.o print.o \
		syntax.o type.o utility.o variable.o

REMOVE = rm -f
INSTALL = install
#LEXI=lexi
SID=sid
SIDOPTS=-s no-lines

SID_OUT=syntax.c syntax.h
#LEXI_OUT=${SRC}/lexer.h ${SRC}/keyword.h


all: tspec

install: tspec
	$(INSTALL) -m 755 -d $(BINDIR)
	$(INSTALL) -m 755 tspec $(BINDIR)/

clean:
	$(REMOVE) tspec $(TARGETS)

tspec: $(TARGETS)
	$(CC) $(CFLAGS) -o $@ $(TARGETS)



#auto : ${SID_OUT} ${LEXI_OUT}

syntax.c syntax.h: syntax.sid syntax.act
	@${REMOVE} ${SID_OUT}
	${SID} ${SIDOPTS} syntax.sid syntax.act ${SID_OUT}

#${SRC}/lexer.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/lexer.h
#	${LEXI} ${SRC}/lexer.lxi ${SRC}/lexer.h
#
#${SRC}/keyword.h : ${SRC}/lexer.lxi
#	@${REMOVE} ${SRC}/keyword.h
#	${LEXI} -k ${SRC}/lexer.lxi ${SRC}/keyword.h
#
#auto_clobber :
#	${REMOVE} ${SID_OUT} ${LEXI_OUT}

