# $TenDRA$

.if !defined(SRC_DIR)
SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}
.endif

.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=      yes
.include "${SRC_DIR}/config.mk"
.endif


.if defined(HAVE_CONF)

.if !defined(PROG)

.MAIN: make-subdir

install: _PROGSUBDIR

make-subdir: _PROGSUBDIR

clean: _PROGSUBDIR
.endif


_PROGSUBDIR: .USE
.if defined(SUBDIR) && !empty(SUBDIR)
.for entry in ${SUBDIR}
	@${BIN_ECHO} "===> ${DIRPRFX}${entry}"
	@${BIN_ECHO} "===> ${entry}# ${MAKE} ${.TARGET}"
	cd ${.CURDIR}/${entry}; \
		${MAKE} ${.TARGET} \
		DIRPRFX=${DIRPRFX}${entry}/
.endfor
.endif

.endif

.include "tendra.config.mk"

