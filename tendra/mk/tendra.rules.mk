# TenDRA make suffix rules
#
# $Id$

.if !defined(_TENDRA_RULES_MK_)
_TENDRA_RULES_MK_=1

.include <tendra.base.mk>

PARTIMP=        ${.IMPSRC:C/^${BASE_DIR}\///1}

# Implied rules.

.SUFFIXES: .o .c .sid .j .pl

.c.o:
	@${ECHO} "# Compiling ${PARTIMP}"
	${CC} ${CCOPTS} -c ${.IMPSRC} -o ${.TARGET}

.c.j:
	@${ECHO} "# Compiling ${PARTIMP}"
	${TCC} -Fj -yTENDRA_BASEDIR="${OBJ_DIR}/src"\
		-Y${OBJ_DIR}/${ENVIRONMENT}/bootstrap -Y${BLDARCHBITS}bit\
		-D__BUILDING_LIBS\
		-I${DIST_DIR}/src/lib/machines/${OSFAM}/${BLDARCH}/include\
		-I/usr/include -f${BASE_DIR}/${STARTUP_MACH}/${API}.h\
		-o ${.TARGET} ${.IMPSRC}
#-Ilib/TenDRA/machines/<OSFAM>/<OSVER>/<BLDARCH>/include

.pl.j:
	@${ECHO} "# Transforming ${PARTIMP}"
	${TPL} ${.IMPSRC} ${.TARGET}

.sid.c:
	@${ECHO} "# Transforming ${PARTIMP} and ${PARTIMP:S/.sid/.act/}"
	${SID} ${SIDOPTS} ${.IMPSRC} ${.IMPSRC:S/.sid/.act/} ${.TARGET} \
		${.TARGET:S/.c/.h/}

.endif	# !defined(_TENDRA_RULES_MK_)
