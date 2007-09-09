# $Id$
#
# Taken from:
# $FreeBSD: doc/share/mk/doc.subdir.mk,v 1.10 2003/05/21 21:16:10 trhodes Exp $
#
# This include file <doc.subdir.mk> contains the default targets
# for building subdirectories in the TenDRA Documentation Project.
#
# For all of the directories listed in the variable SUBDIR, the
# specified directory will be visited and the target made. There is
# also a default target which allows the command "make subdir" where
# subdir is any directory listed in the variable SUBDIR.
#

# ------------------------------------------------------------------------
#
# Document-specific variables:
#
#	SUBDIR		A list of subdirectories that should be
#				built as well.  Each of the targets will
#				execute the same target in the
#				subdirectories.
#
#	MAKEOPTS	Extra options to pass to $(MAKE).
#

# ------------------------------------------------------------------------
#
# Provided targets:
#
#	clean:
#			Remove files created by the build process (using
#			defaults specified by environment)
#
#	cleandir:
#			Remove the object directory, if any.
#
#	cleanall:
#			Remove all possible generated files (all predictable
#			combinations of ${FORMAT} values)
#

ECHODIR=echo

.if !target(__initialized__)
__initialized__:
.endif

_SUBDIRUSE: .USE
.for entry in ${SUBDIR}
	@${ECHODIR} "===> ${DIRPRFX}${entry}"
	@cd ${.CURDIR}/${entry} && \
	${MAKE} ${MAKEOPTS} ${.TARGET} DIRPRFX=${DIRPRFX}${entry}/
.endfor

.MAIN: all

${SUBDIR}::
	@cd ${.CURDIR}/${.TARGET} && ${MAKE} ${MAKEOPTS} all

.for __target in all cleandir lint objlink
.if !target(${__target})
${__target}: _SUBDIRUSE
.endif
.endfor

.if !target(obj)
obj:	_SUBDIRUSE
	@if ! [ -d ${CANONICALOBJDIR}/ ]; then \
		${MKDIR} -p ${CANONICALOBJDIR}; \
		if ! [ -d ${CANONICALOBJDIR}/ ]; then \
			${ECHO_CMD} "Unable to create ${CANONICALOBJDIR}."; \
			exit 1; \
		fi; \
		${ECHO} "${CANONICALOBJDIR} created ${.CURDIR}"; \
	fi
.endif

.if !target(objlink)
objlink: _SUBDIRUSE
	@if [ -d ${CANONICALOBJDIR}/ ]; then \
		${RM} -f ${.CURDIR}/obj; \
		${LN} -s ${CANONICALOBJDIR} ${.CURDIR}/obj; \
	else \
		${ECHO_CMD} "No ${CANONICALOBJDIR} to link to - do a make obj."; \
	fi
.endif

.if !target(whereobj)
whereobj:
	@${ECHO_CMD} ${.OBJDIR}
.endif

cleanobj:
	@if [ -d ${CANONICALOBJDIR}/ ]; then \
		${RM} -rf ${CANONICALOBJDIR}; \
	else \
		cd ${.CURDIR} && ${MAKE} ${MAKEOPTS} clean cleandepend; \
	fi
	@if [ -h ${.CURDIR}/obj ]; then ${RM} -f ${.CURDIR}/obj; fi

.if !target(clean)
clean: _SUBDIRUSE
.if defined(CLEANFILES) && !empty(CLEANFILES)
	${RM} -f ${CLEANFILES}
.endif
.if defined(CLEANDIRS) && !empty(CLEANDIRS)
	${RM} -rf ${CLEANDIRS}
.endif
.if defined(IMAGES_LIB) && !empty(LOCAL_IMAGES_LIB_DIR)
	${RM} -rf ${LOCAL_IMAGES_LIB_DIR}
.endif
.endif

cleandir: cleanobj _SUBDIRUSE

#
# Create /usr/obj image subdirs when ${IMAGES} contains subdir/image.xxx
#

_imagesubdir=
.for _imagedir in ${IMAGES:H}
.if ${_imagesubdir:M${_imagedir}} == ""
_imagesubdir+= ${_imagedir}
.endif
.endfor

.if ${_imagesubdir} != ""
_IMAGESUBDIR: .USE
.for dir in ${_imagesubdir}
	@if ! [ -d ${CANONICALOBJDIR}/${dir}/ ]; then \
		${MKDIR} -p ${CANONICALOBJDIR}/${dir}; \
		if ! [ -d ${CANONICALOBJDIR}/${dir}/ ]; then \
			${ECHO_CMD} "Unable to create ${CANONICALOBJDIR}/${dir}/."; \
			exit 1; \
		fi; \
		${ECHO} "${CANONICALOBJDIR}/${dir}/ created for ${.CURDIR}"; \
	fi
.endfor

obj: _IMAGESUBDIR
.endif

cleanall:
	${MAKE} ${MAKEOPTS} FORMATS="${ALL_FORMATS}" clean
