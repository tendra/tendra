# $TenDRA$

_SUBDIRUSE: .USE
.for entry in ${SUBDIR}
	@${ECHODIR} "===> ${DIRPRFX}${entry}"
	@cd ${.CURDIR}/${entry} && \
	${MAKE} ${.TARGET:S/realpackage/package/:S/realinstall/install/} \
		DIRPRFX=${DIRPRFX}${entry}/
.endfor


clean: _SUBDIRUSE
.if defined(CLEANFILES) && !empty(CLEANFILES)
	${RM} -f ${CLEANFILES}
.endif


#cleandir: cleanobj _SUBDIRUSE

cleanall:
	${MAKE} FORMATS="${ALL_FORMATS}" clean
