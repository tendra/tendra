# $TenDRA$

SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}

.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=      yes
.include "${SRC_DIR}/config.mk"
.endif


.if defined(HAVE_CONF)

.if !defined(PROG)

.MAIN: make-subdir

make-subdir: _PROGSUBDIR

clean: _PROGSUBDIR
.endif


_PROGSUBDIR: .USE
.if defined(SUBDIR) && !empty(SUBDIR)
.for entry in ${SUBDIR}
	@${ECHODIR} "===> ${DIRPRFX}${entry}"
	@${ECHODIR} "===> ${entry}# ${MAKE} ${.TARGET}"
	@cd ${.CURDIR}/${entry}; \
		${MAKE} ${.TARGET} \
		DIRPRFX=${DIRPRFX}${entry}/
.endfor
.endif

.endif

.include "tendra.config.mk"

