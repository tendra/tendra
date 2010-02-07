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



OBJS+=  ${SRCS:S/.cc/.o/:S/.c/.o/:C/^/${OBJ_SDIR}\//}

# TODO: explain that SRCS may be relative paths (since we don't use archives per directory for tendra)
# TODO: when we have partial linking (ld -r) per directory, these :H rules can be removed

.for src in ${SRCS:M*.c}
${OBJ_SDIR}/${src:H}:
	${MKDIR} -p ${.TARGET}

${OBJ_SDIR}/${src:S/.c/.o/}: ${OBJ_SDIR}/${src:H} ${src}
	@${ECHO} "==> Compiling ${WRKDIR}/${src}"
	${CC} ${CFLAGS} ${CCOPTS} -c ${src} -o ${.TARGET}
.endfor

.for src in ${SRCS:M*.cc}
${OBJ_SDIR}/${src:H}:
	${MKDIR} -p ${.TARGET}

${OBJ_SDIR}/${src:S/.cc/.o/}: ${OBJ_SDIR}/${src:H} ${src}
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
