# $Id$

.include "Makefile.inc"

.include <tendra.base.mk>
.include <tendra.makedefs.mk>


TRANS_CFLAGS+=	-D TRANS_STUB

TRANS_CFLAGS+=	-I ${BASE_DIR}/src/stub
TRANS_CFLAGS+=	-I ${BASE_DIR}/src/common

# TODO: these are not yet selectable at runtime
TRANS_DEBUG?= stub

# TODO: these are not yet selectable at runtime
.if "${TRANS_DEBUG}" == "stub"

TRANS_CFLAGS+= -D TDF_DIAG4

PARTS+= src/common/diag4

.else

.BEGIN:
	@${ECHO} '$${TRANS_DEBUG} unrecognised'
	@${EXIT} 1;

.endif


PART_CFLAGS+=	${TRANS_CFLAGS}

PARTS+= src/common/shared
PARTS+= src/common/construct
PARTS+= src/common/linkinfo
PARTS+= src/common/reader
PARTS+= src/common/refactor
PARTS+= src/common/utility
PARTS+= src/common/main

.include <tendra.partial.mk>


#TCCOPTS=	-Xc -Y32bit -Yc89

CCOPTS+=	${TRANS_CFLAGS}

SRCS+=	driver.c
SRCS+=	reg_result.c
SRCS+=	translate.c
SRCS+=	is_worth.c
SRCS+=	special_fn.c
SRCS+=	special_tok.c
SRCS+=	inlinechoice.c
SRCS+=	machine_toks.c

.include <tendra.obj.mk>


PROG=    	trans.${.CURDIR:T}
EXEC_BIN=	${PREFIX_LIBEXEC}

.include <tendra.prog.mk>

