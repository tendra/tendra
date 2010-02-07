# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_OBJ_MK_)
_TENDRA_WORK_OBJ_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(SRCS)
.BEGIN:
	@${ECHO} '$${SRCS} must be set'
	@${EXIT} 1;
.endif

# TODO: assert SRCS may not contain ../


OBJS+=  ${SRCS:S/.cc/.o/:S/.c/.o/:C/^/${OBJ_SDIR}\//}

${OBJ_SDIR}:
	${MKDIR} -p ${.TARGET}

.for src in ${SRCS:M*.c}
${OBJ_SDIR}/${src:S/.c/.o/}: ${OBJ_SDIR} ${src}
	@${ECHO} "==> Compiling ${WRKDIR}/${src}"
	${CC} ${CFLAGS} ${CCOPTS} -c ${src} -o ${.TARGET}
.endfor

.for src in ${SRCS:M*.cc}
${OBJ_SDIR}/${src:S/.cc/.o/}: ${OBJ_SDIR} ${src}
	@${ECHO} "==> Compiling ${WRKDIR}/${src}"
	${CXX} ${CXXFLAGS} ${CCOPTS} -c ${src} -o ${.TARGET}
.endfor



#
# User-facing targets
#

all:: ${OBJS}


clean::
	${REMOVE} ${OBJS}


install::



.endif	# !defined(_TENDRA_WORK_PROG_MK_)
