# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


# XXX: due to go, when tspec is split off

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
# User-facing targets
#

all::


clean::


install::
	@${ECHO} "==> Installing ${WRKDIR}/${STARTUPSUBDIR} startup directories"
	@${CONDCREATE} ${STARTUPSUBDIR:S,^,${PREFIX_STARTUP}/,g}
	@${FIND} ${STARTUPSUBDIR} -name '.*' -prune -o -print |                       \
	while read file; do                                                           \
		if ${TEST} -d $${file}; then                                              \
			${ECHO} ${INSTALL} -m 755 -d ${PREFIX_STARTUP}/$${file};              \
			${INSTALL} -m 755 -d ${PREFIX_STARTUP}/$${file} || ${EXIT} $$?;       \
		else                                                                      \
			${ECHO} ${INSTALL} -m 644 $${file} ${PREFIX_STARTUP}/$${file};        \
			${INSTALL} -m 644 $${file} ${PREFIX_STARTUP}/$${file} || ${EXIT} $$?; \
		fi;                                                                       \
	done



.endif	# !defined(_TENDRA_WORK_STARTUP_MK_)
