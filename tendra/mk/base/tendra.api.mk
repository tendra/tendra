# $TenDRA$


# this hack strips out any path info from the sourcefiles since the objects
# are placed into the current working directory!

OBJS+=  ${SRCS:N*.h:R:S/$/.j/g}
OBJS_NODIR+=  ${SRCS:N*.h:R:S/$/.j/g:C/.*\/(.*)$/\1/g}

${TL}: ${OBJS}
	@echo ${TLD} ${TCCFLAGS} ${LDFLAGS} -o ${.TARGET} ${OBJS_NODIR} ${LDDESTDIR} ${LDADD}
