# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_WORK_PROG_MK_)
_TENDRA_WORK_PROG_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(OBJS)
.BEGIN:
	@${ECHO} '$${OBJS} must be set'
	@${EXIT} 1;
.endif

.if !defined(PROG)
.BEGIN:
	@${ECHO} '$${PROG} must be set'
	@${EXIT} 1;
.endif



.if !defined(MAN) && exists(${.CURDIR}/${PROG}.1)
MAN=	${PROG}.1
.endif

${PROG}: ${OBJS}
	@${ECHO} "==> Linking ${WRKDIR}/${PROG}"
	${CC} ${LDOPTS} -o ${PROG} ${OBJS} ${LIBS}

.if defined(WRAPPER)
	@${ECHO} "==> Adjusting paths for ${WRAPPER}"
	sed -e 1,\$$s%@@MACH_BASE@@%${MACH_BASE}%g \
		-e 1,\$$s%@@PREFIX@@%${PREFIX}%g \
		${.CURDIR}/${WRAPPER} > ${_objdir}/${WRAPPER}

CLEAN_EXTRA+=	${_objdir}/${WRAPPER}
.endif

CLEAN_EXTRA+=	${PROG} ${PROG}.core core ${OBJS}
_objdir=	${OBJ_SDIR}



#
# User-facing targets
#

all:: ${PROG}


clean::
.if "${CLEAN_EXTRA}" != ""
	${REMOVE} ${CLEAN_EXTRA}
.endif


install::
	@${ECHO} "==> Installing ${PROG}"
	${CONDCREATE} "${PUBLIC_BIN}" "${MACH_BASE}/bin"
	${INSTALL} -m 755 ${PROG} ${MACH_BASE}/bin/${PROG}
.if "${WRAPPER}" != ""
	${INSTALL} -m 755 ${_objdir}/${WRAPPER} ${PUBLIC_BIN}/${PROG}
.endif



.endif	# !defined(_TENDRA_WORK_PROG_MK_)
