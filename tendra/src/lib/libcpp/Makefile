# $TenDRA$

.PATH : ${.CURDIR}/src

CFLAGS+=	-I${.CURDIR}/src

TCC_OPTS+=	-yTENDRA_BASEDIR=${OBJ_PREFIX}/ \
		-Y${DEFAULT_BUILD} \
		-Ydefault.extra \
		-Yc++ \
		-J${OBJ_PREFIX}/lib/apis/lib/cpp \
		-J${OBJ_PREFIX}/lib/apis/lib/ansi \
		-J${OBJ_PREFIX}/lib/cpp/tokens

LIB=	libcpp.a

SRCS=	baseinfo.cc cmath.cc cstring.cc cwchar.cc exception.cc new.cc \
	new1.cc new2.cc new3.cc new4.cc new5.cc new6.cc new7.cc new8.cc \
	pure.cc term.cc typeinfo.cc what.cc

.include "../../../mk/base/tendra.prog.mk"
#.include "../../../mk/base/tendra.subdir.mk"
