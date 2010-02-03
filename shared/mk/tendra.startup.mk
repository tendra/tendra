# TenDRA make build infrastructure
# XXX: due to go, when tspec is split off
#
# $Id$

.if !defined(_TENDRA_WORK_STARTUP_MK_)
_TENDRA_WORK_STARTUP_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(STARTUPSUBDIR)
.BEGIN:
	@${ECHO} '$${STARTUPSUBDIR} must be set'
	@${EXIT} 1;
.endif



#
# Install startup files in object directory
#
_REALWORK: .USE
	@${ECHO} "# Installing ${STARTUPSUBDIR} startup directories into object directory"
	${CONDCREATE} ${STARTUPSUBDIR:S/^/${OBJ_SDIR}\//g}
	@${FIND} ${STARTUPSUBDIR} -name '.*' -prune -or -print | \
	while read file; do \
		if ${TEST} -d $${file}; then \
			${ECHO} ${INSTALL} -m 755 -d ${OBJ_SDIR}/${startsub}/$${file}; \
			${INSTALL} -m 755 -d ${OBJ_SDIR}/${startsub}/$${file} || ${EXIT} $$?; \
		else \
			${ECHO} ${INSTALL} -m 644 $${file} ${OBJ_SDIR}/${startsub}/$${file}; \
			${INSTALL} -m 644 $${file} ${OBJ_SDIR}/${startsub}/$${file} || ${EXIT} $$?; \
		fi; \
	done

_objdir=	${OBJ_SDIR}



#
# Install additional startup files (?).
#
_REALINSTALL: .USE
	@${ECHO} "==> Installing ${STARTUPSUBDIR} startup directories"
	${CONDCREATE} ${STARTUPSUBDIR:S/^/${COMMON_DIR}\/startup\//g}
	@cd ${.CURDIR} && ${FIND} ${STARTUPSUBDIR} -name '.*' -prune -o -print | \
	while read file; do \
		if ${TEST} -d $${file}; then \
			${ECHO} ${INSTALL} -m 755 -d ${COMMON_DIR}/startup/$${file}; \
			${INSTALL} -m 755 -d ${COMMON_DIR}/startup/$${file} || ${EXIT} $$?; \
		else \
			${ECHO} ${INSTALL} -m 644 $${file} ${COMMON_DIR}/startup/$${file}; \
			${INSTALL} -m 644 $${file} ${COMMON_DIR}/startup/$${file} || ${EXIT} $$?; \
		fi; \
	done



.endif	# !defined(_TENDRA_WORK_STARTUP_MK_)
