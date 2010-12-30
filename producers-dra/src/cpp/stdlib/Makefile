# $Id$

.include "Makefile.inc"


# Here we're using tcc(1) to call the not-yet-installed C++ producer.
# This way, we can make use of tcc's usual environments, which is far more
# convenient than explicitly specifying everything (like error-checking
# profiles) to the C++ producer by hand.


# Tell tcc(1) where to find our pre-'make install' C++ producer binary
CXXFLAGS+=   -Ex:${OBJ_SDIR:H}/tcpplus

# Tell the -Yc++ environment where to find the C++ tspec API
CXXFLAGS+=   -yTENDRA_INCLDIR=${PREFIX_TSPEC}/TenDRA/include


SRCS+=	baseinfo.cc
SRCS+=	cmath.cc
SRCS+=	cstring.cc
SRCS+=	cwchar.cc
SRCS+=	exception.cc
SRCS+=	new.cc
SRCS+=	new1.cc
SRCS+=	new2.cc
SRCS+=	new3.cc
SRCS+=	new4.cc
SRCS+=	new5.cc
SRCS+=	new6.cc
SRCS+=	new7.cc
SRCS+=	new8.cc
SRCS+=	pure.cc
SRCS+=	term.cc
SRCS+=	typeinfo.cc
SRCS+=	what.cc

.include <tendra.obj.mk>


LIB=	cpp

.include <tendra.lib.mk>

