# TenDRA make install infrastructure
#
# $Id$

.include <tendra.base.mk>

# Installation infrastructure framework

.if !target(.MAIN)
.MAIN: all
.endif

.if defined(PROG)
.if !defined(MAN)
.if exists(${PROG}.1)
MAN=    ${PROG}.1
.endif	# exists(${PROG}.1)
.endif  # !defined(MAN)
.endif

install: _instmanpages
.if defined(API)
.if !exists(${INSTALL_DIR}/lib/building/${API}.api)
	${MKDIR} -p ${INSTALL_DIR}/lib/building/${API}.api
.endif
.if !exists(${INSTALL_DIR}/lib/include/${API}.api)
	${MKDIR} -p ${INSTALL_DIR}/lib/include/${API}.api
.endif
	cd ${OBJ_DIR}/${APIS}/building/${API}.api;\
	for file in M_${API} *.c; do\
		${INSTALL} -m 644 $$file ${INSTALL_DIR}/lib/building/${API}.api/$$file;\
	done
	cd ${OBJ_DIR}/${APIS}/include/${API}.api;\
	for file in *.h; do\
		${INSTALL} -m 644 $$file ${INSTALL_DIR}/lib/include/${API}.api/$$file;\
	done
.endif # API
.if defined(ENVFILE)
.if !exists(${MACH_BASE}/env)
	${MKDIR} -p ${MACH_BASE}/env
.endif
	cd ${OBJ_SDIR};
.for entry in ${ENVFILE}
	${INSTALL} -m 644 ${OBJ_SDIR}/${entry} ${MACH_BASE}/env/${entry}
.endfor
.endif # ENVFILE
.if defined(PROG)
	cd ${OBJ_SDIR};
.if !exists(PUBLIC_BIN)
	${MKDIR} -p ${PUBLIC_BIN}
.endif
.if defined(WRAPPER)
	${INSTALL} -m 755 ${OBJ_SDIR}/${PROG}.sh ${PUBLIC_BIN}/${PROG}
.endif
.if !exists(${MACH_BASE}/bin)
	${MKDIR} -p ${MACH_BASE}/bin
.endif
	${INSTALL} -m 755 ${OBJ_SDIR}/${PROG} ${MACH_BASE}/bin/${PROG}
.endif # PROG
# XXX: Very dirty hack...
.if defined(ENVSUBDIR)
.if !exists(${MACH_BASE}/env)
	${MKDIR} -p ${MACH_BASE}/env
.endif
.for entry in ${ENVSUBDIR}
	${MKDIR} -p ${MACH_BASE}/startup/${entry}
	(cd ${entry} && for file in *;\
		do ${INSTALL} -m 644 $$file ${MACH_BASE}/env/$$file;\
		done)
.endfor
.endif
# XXX: Very dirty hack...
.if defined(STARTUPSUBDIR)
.if !exists(${COMMON_DIR}/startup)
	${MKDIR} -p ${COMMON_DIR}/startup
.endif
.for entry in ${STARTUPSUBDIR}
	${MKDIR} -p ${COMMON_DIR}/startup/${entry}
	(cd ${entry} && for file in *;\
		do ${INSTALL} -m 644 $$file ${COMMON_DIR}/startup/${entry}/$$file;\
		done)
.endfor
.endif
.if defined(MACHSUBDIR)
.if !exists(${MACH_BASE}/include)
	${MKDIR} -p ${MACH_BASE}/include
.endif
.if !exists(${MACH_BASE}/startup)
	${MKDIR} -p ${MACH_BASE}/startup
.endif
	(cd ${MACHSUBDIR}/include && for file in *; do\
		${INSTALL} -m 644 $$file ${MACH_BASE}/include/$$file;\
	done)
	(cd ${MACHSUBDIR}/startup && for file in *; do\
		${INSTALL} -m 644 $$file ${MACH_BASE}/startup/$$file;\
	done)
.endif #MACHSUBDIR

_instmanpages: .USE
.if defined(MAN)
.for M in ${MAN:O:u}
.if !exists(${MAN_DIR}/man${M:T:E})
	${MKDIR} -p ${MAN_DIR}/man${M:T:E}
.endif
	${INSTALL} -m 444 ${M} ${MAN_DIR}/man${M:T:E}/${M}
.endfor
.endif
