# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


PARTS+=	src/shared

.include <tendra.partial.mk>


TCCOPTS=	-Xp

TCCOPTS.archive.c	+= -Yposix
TCCOPTS.environ.c	+= -Yposix
TCCOPTS.execute.c	+= -Yposix
TCCOPTS.filename.c	+= -Yposix
TCCOPTS.main.c	+= -Yposix
TCCOPTS.hash.c	+= -Yposix

CCOPTS+=                                   \
	-DEXECFORMAT='"${EXECFORMAT}"'         \
	-DBLDARCH='"${BLDARCH}"'               \
	-DTRANSARCH='"${TRANSARCH}"'           \
	-DOSFAM='"${OSFAM}"'                   \
	-DOSVER='"${OSVER}"'

SRCS+=	archive.c
SRCS+=	compile.c
SRCS+=	environ.c
SRCS+=	execute.c
SRCS+=	filename.c
SRCS+=	flags.c
SRCS+=	lexer.c
SRCS+=	list.c
SRCS+=	main.c
SRCS+=	options.c
SRCS+=	stages.c
SRCS+=	startup.c
SRCS+=	utility.c
SRCS+=	table.c
SRCS+=	hash.c
SRCS+=	temp.c

.include <tendra.obj.mk>


PROG=		tcc

.include <tendra.prog.mk>

# ../../lexi/obj/src/lexi -a -t lex_ -p lexi_ -l c90 lexer.lxi lexer.lct lexer.c lexer.h

