# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


PARTS+=	src/shared

.include <tendra.partial.mk>


TCCOPTS=	-Yposix -Xp

CCOPTS+=                                   \
	-DPREFIX='"${PREFIX}"'                 \
	-DPREFIX_BIN='"${PREFIX_BIN}"'         \
	-DPREFIX_LIB='"${PREFIX_LIB}"'         \
	-DPREFIX_LIBEXEC='"${PREFIX_LIBEXEC}"' \
	-DPREFIX_SHARE='"${PREFIX_SHARE}"'     \
	-DPREFIX_INCLUDE='"${PREFIX_INCLUDE}"' \
	-DPREFIX_MAN='"${PREFIX_MAN}"'         \
	-DPREFIX_TSPEC='"${PREFIX_TSPEC}"'     \
	-DPREFIX_STARTUP='"${PREFIX_STARTUP}"' \
	-DPREFIX_ENV='"${PREFIX_ENV}"'         \
	-DPREFIX_API='"${PREFIX_API}"'         \
	-DPREFIX_LPI='"${PREFIX_LPI}"'         \
	-DPREFIX_SYS='"${PREFIX_SYS}"'         \
	-DPREFIX_TMP='"${PREFIX_TMP}"'         \
	-DPREFIX_MAP='"${PREFIX_MAP}"'         \
	                                       \
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

