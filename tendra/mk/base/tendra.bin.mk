# $TenDRA$

# This hack strips out any path info from the sourcefiles since the objects
# are placed into the current working directory!

OBJS+=  ${SRCS:N*.h:R:S/$/.o/g}
OBJS_NODIR+=  ${SRCS:N*.h:R:S/$/.o/g:C/.*\/(.*)$/\1/g}


${PROG}: ${OBJS}
	${BIN_CC} ${CFLAGS} ${LDFLAGS} -o ${.TARGET} ${OBJS_NODIR} ${LDDESTDIR} ${LDADD}
