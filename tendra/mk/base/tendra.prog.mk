# $TenDRA$

CFLAGS+=${COPTS} ${DEBUG_FLAGS}

# calculate our object directory and obj prefix.
OBJ_DIR=        ${.CURDIR:C/(.*)\/src(.*)/\1\/obj\2/}
OBJ_PREFIX=     ${.CURDIR:C/(.*)\/src(.*)/\1\/obj/}


SRC_DIR=        ${.CURDIR:C/(.*)\/src.*/\1/}

.if exists (${SRC_DIR}/config.mk)
HAVE_CONF=      yes
.endif

MAIN_TARGETS=	config-check obj-dir depend all

.MAIN: ${MAIN_TARGETS}

make-subdir: ${MAIN_TARGETS}

.if defined(HAVE_CONF)

.if defined(PROG)
# this hack strips out any path info from the sourcefiles since the objects
# are placed into the current working directory!

OBJS+=  ${SRCS:N*.h:R:S/$/.o/g}
OBJS_NODIR+=  ${SRCS:N*.h:R:S/$/.o/g:C/.*\/(.*)$/\1/g}


${PROG}: ${OBJS}
	${CC} ${CFLAGS} ${LDFLAGS} -o ${.TARGET} ${OBJS_NODIR} ${LDDESTDIR} ${LDADD}

.endif

# All our nifty targets.


all:
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} make-all


MAKE_ALL=	${PROG}

make-all: ${MAKE_ALL}

depend:	
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} depend-all

depend-all: ${DEPEND_SRC}

# Our clean targets.

CLEANFILES+= ${PROG} ${OBJS}

clean:
	env MAKEOBJDIR=${OBJ_DIR} ${MAKE} clean-all

clean-all:
.if !empty(CLEANFILES)
	rm -f ${CLEANFILES}
.endif

obj-dir:
	@if ! test -d ${OBJ_DIR}/; then \
		mkdir -p ${OBJ_DIR}; \
		if ! test -d ${OBJ_DIR}/; then \
			${ECHO} "Unable to create ${OBJ_DIR}."; \
			exit 1; \
		fi; \
		${ECHO} "${OBJ_DIR} created for ${.CURDIR}"; \
	fi


.include "tendra.def.mk"
.include "tendra.sys.mk"
.include "tendra.subdir.mk"

.else

.endif

.include "tendra.config.mk"
