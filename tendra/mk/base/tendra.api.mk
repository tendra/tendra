# $TenDRA$


# This hack strips out any path info from the sourcefiles since the objects
# are placed into the current working directory!

OBJS+=  ${SRCS:N*.h:R:S/$/.j/g}
OBJS_NODIR+=  ${SRCS:N*.h:R:S/$/.j/g:C/.*\/(.*)$/\1/g}

# add the library to the cleanfiles.
CLEANFILES+= ${TL}


${TL}: ${OBJS}
	${TLD} ${LDFLAGS} -o ${.TARGET} ${OBJS_NODIR} ${LDDESTDIR} ${LDADD}
