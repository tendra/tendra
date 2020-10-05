# Copyright 2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_SID_MK_)
_TENDRA_SID_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(SYNTAX)
.BEGIN:
	@${ECHO} '$${SYNTAX} must be set'
	@${EXIT} 1;
.endif


ACTIONS?=	${SYNTAX:S/.sid$/.act/}

.if defined(SIDOPTS)
. if !empty(SIDOPTS:M*split*:N*nosplit*)
SIDSPLIT?=	@
. endif
.endif


# If sid is not available, and anything needs to be rebuilt, give the user
# some hints about how to handle this and fail as gracefully as the
# conditions permit.
_SIDCHECK != command -v ${SID}
.if !empty(_SIDCHECK)
# TODO: really sid ought to delete its own output on error.
.for src in ${SYNTAX}
${src:R}${SIDSPLIT}.c ${src:R}.h: ${src} ${ACTIONS:M${src:R}.act}
	@${ECHO} "==> Translating ${WRKDIR}/${src}"
	${SID} ${SIDOPTS} ${.ALLSRC} ${src:R}${SIDSPLIT}.c ${src:R}.h \
		|| ( ${RMFILE} ${src:R}${SIDSPLIT:S/@/*/}.c ${src:R}.h; ${EXIT} 1 )
touch-generated-sid::
	${TOUCH} ${src:R}${SIDSPLIT}.c ${src:R}.h
.endfor
.else
.for src in ${SYNTAX}
${src:R}${SIDSPLIT}.c ${src:R}.h: ${src} ${ACTIONS:M${src:R}.act}
	@${ECHO}
	@${ECHO} "Need to run sid, and SID does not appear to point at a working executable!"
	@${ECHO} "To use the in-tree built version of sid, run make with SID"
	@${ECHO} "pointing at the in-tree executable."
	@${ECHO} "To use the in-repository versions of generated files, run"
	@${ECHO} "    make touch-generated-sid"
	@${ECHO}
	@${FALSE}
touch-generated-sid::
	${TOUCH} ${src:R}${SIDSPLIT}.c ${src:R}.h
.endfor
.endif


#
# User-facing targets
#

.for src in ${SYNTAX}
regen:: ${src:R}${SIDSPLIT}.c ${src:R}.h
.endfor


regen-clean::
.for src in ${SYNTAX}
	${RMFILE} ${src:R}${SIDSPLIT:S/@/*/}.c ${src:R}.h
.endfor


install::



.endif
