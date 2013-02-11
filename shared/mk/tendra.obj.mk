# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_OBJ_MK_)
_TENDRA_OBJ_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>
.include <tendra.compiler.mk>

.if !defined(SRCS)
.BEGIN:
	@${ECHO} '$${SRCS} must be set'
	@${EXIT} 1;
.endif

# TODO: assert SRCS may not contain ../


OBJS+=  ${SRCS:S/.cc/.o/:S/.c/.o/:C/^/${OBJ_SDIR}\//}

.if exists(${BASE_DIR}/include)
CCOPTS+=	-I ${BASE_DIR}/include
.endif

.for src in ${SRCS:M*.c}
${OBJ_SDIR}/${src:S/.c/.o/}: ${src}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Compiling ${WRKDIR}/${src}"
	${CC} ${CFLAGS} ${CCOPTS} -c ${.ALLSRC} -o ${.TARGET}
.endfor

.for src in ${SRCS:M*.cc}
${OBJ_SDIR}/${src:S/.cc/.o/}: ${src}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Compiling ${WRKDIR}/${src}"
	${CXX} ${CXXFLAGS} ${CCOPTS} -c ${.ALLSRC} -o ${.TARGET}
.endfor



#
# User-facing targets
#

all:: ${OBJS}


clean::
	${RMFILE} ${OBJS}


install::



.endif
