# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_PARTIAL_MK_)
_TENDRA_PARTIAL_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

#
# This makefile has two modes:
#  ${OBJS} is set: construct a partial library
#  ${PARTS} is set: depend on a partial library
#
.if !defined(OBJS) && !defined(PARTS)
.BEGIN:
	@${ECHO} 'Either $${OBJS} or $${PARTS} must be set'
	@${EXIT} 1;
.endif



.if defined(PARTS)
#
# Depend on a partial library
#

OBJS+=	${PARTS:C/^/${OBJ_SDIR}\/_partial\//:C/$/\/_partial.o/}

.for part in ${PARTS}
# TODO: explain what's going on. we have e.g. config.h which is supplied by the *current* directory,
# and a part is built differently to suit this particular config.h
# TODO: here we construct a mirrored OBJDIR for this part under *our* OBJ_SDIR
# TODO: build the part into that OBJ_SDIR
# TODO: override OBJ_* etc when calling ${MAKE}
# TODO: pass through CFLAGS etc (call these PART_CFLAGS, PART_CCOPTS etc)
# TODO: directory here is ${OBJ_SDIR}/_partial/installers/80x86/common
${OBJ_SDIR}/_partial/${part}/_partial.o::
	@cd ${BASE_DIR}/${part} && ${MAKE}        \
	    BASE_DIR=${BASE_DIR}                  \
	    OBJ_DIR=${OBJ_SDIR}/_partial          \
	    OBJ_SDIR=${OBJ_SDIR}/_partial/${part} \
	    CFLAGS="${CFLAGS} ${PART_CFLAGS}"     \
	    _partial

clean::
	@cd ${BASE_DIR}/${part} && ${MAKE}        \
	    OBJ_DIR=${OBJ_SDIR}/_partial          \
	    OBJ_SDIR=${OBJ_SDIR}/_partial/${part} \
		clean

.endfor



.else
#
# Construct a partial library
#

${OBJ_SDIR}/_partial.o: ${OBJS}
	@${CONDCREATE} "${OBJ_SDIR}"
	@${ECHO} "==> Partially linking ${WRKDIR}"
	${LD} ${LDFLAGS} -r -o ${.TARGET} ${OBJS}

_partial: ${OBJ_SDIR}/_partial.o



#
# User-facing targets
#

all::


clean::
	${RMFILE} ${OBJ_SDIR}/_partial.o


install::


.endif


.endif
