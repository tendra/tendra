# $TenDRA$
#
# Our .PATH statement is at the bottom so BUILD_OS and MACH_CPU can be filled
# in by tendra.prog.mk


TCC_OPTS=	-yTENDRA_BASEDIR=${OBJ_PREFIX} \
		-Y${DEFAULT_BUILD} \
		-Ydefault.extra

DEPEND_SRC=	sys.j 

sys_toks.j: c_toks.j dep_toks.j map_toks.j
	${TLD} -o ${.TARGET} c_toks.j dep_toks.j map_toks.j

sys.j: sys_toks.j
	${TNC} -t -d -L'.~' sys_toks.j ${.TARGET}

CLEANFILES=	c_toks.j dep_toks.j map_toks.j sys.j sys_toks.j

.include "${.CURDIR}/../../../mk/base/tendra.prog.mk"

.PATH :	${.CURDIR}/../machines/common/tokens ${.CURDIR}/../machines/common/src \
	${.CURDIR}/../machines/${BUILD_OS}/${MACH_CPU}/tokens
