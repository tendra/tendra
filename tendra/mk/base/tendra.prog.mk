# $TenDRA$

CFLAGS+=${COPTS} ${DEBUG_FLAGS}

.include "tendra.var.mk"

.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=      yes
.endif


MAIN_TARGETS=	config-check obj-dir make-dir depend all

.MAIN: ${MAIN_TARGETS}

.ORDER: config-check obj-dir make-dir depend all

make-subdir: ${MAIN_TARGETS}


.if defined(HAVE_CONF)

.include "tendra.config.mk"

.if defined(USE_LIBTEN)
.include "tendra.libten.mk"
.endif

.if defined(TL)
.include "tendra.api.mk"
.endif

.if defined(PROG)
.include "tendra.bin.mk"
.endif

.if defined(SHLIB)
.include "tendra.lib.mk"
.endif

# All our nifty targets.


all:
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} make-all


MAKE_ALL=	${PROG} ${TL} ${SHLIB}

make-all: ${MAKE_ALL}

depend:	
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} depend-all

depend-all: ${DEPEND_SRC}


# Install target.
install:
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} install-all



# Our clean targets.

CLEANFILES+= ${PROG} ${OBJS}

clean:
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} clean-all

clean-all:
.if !empty(CLEANFILES)
	@if [ -d "${OBJ_DIR}" ]; then \
		echo ${BIN_RM} -f ${CLEANOPT} ${CLEANFILES}; \
		${BIN_RM} -f ${CLEANOPT} ${CLEANFILES}; \
	else \
		${BIN_ECHO} "WARNING: Object directory ${OBJ_DIR} does not exist!"; \
	fi

.endif

obj-dir:
.if !defined(NO_OBJDIR)
	@if ! test -d ${OBJ_DIR}/; then \
		${BIN_MKDIR} ${ARGS_MKDIR} ${OBJ_DIR}; \
		if ! test -d ${OBJ_DIR}/; then \
			${BIN_ECHO} "Unable to create ${OBJ_DIR}."; \
			exit 1; \
		fi; \
		${BIN_ECHO} "${OBJ_DIR} created for ${.CURDIR}"; \
	fi
.endif

make-dir:
.if defined(MAKEDIR)
.for i in ${MAKEDIR}
	@if ! test -d ${OBJ_DIR}/${i}; then \
		${BIN_MKDIR} ${ARGS_MKDIR} ${OBJ_DIR}/${i}; \
	fi
.endfor
.endif

.include "tendra.version.mk"
.include "tendra.def.mk"
.include "tendra.sys.mk"
.include "tendra.install.mk"
.include "tendra.subdir.mk"

.else

.endif

#.include "tendra.config.mk"
