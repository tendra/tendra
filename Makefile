# $Id$

# Note to package maintainers: this top-level Makefile is provided for the
# convenience of people checking out the entire repository, who just want to
# try it out. It is not intended to be packaged; rather, each project is
# intended to stand alone, and those ought to be packaged separately.

PROJECTS+=	andfutils
PROJECTS+=	calculus
PROJECTS+=	lexi
PROJECTS+=	libexds
PROJECTS+=	make_err
PROJECTS+=	sid
PROJECTS+=	tendra
#PROJECTS+=	tendra-doc
#PROJECTS+=	tendra-www
PROJECTS+=	tspec


all:
.for proj in ${PROJECTS}
	cd ${proj} && ./makedefs
	cd ${proj} && ${MAKE} all
.endfor

clean:
.for proj in ${PROJECTS}
	cd ${proj} && ${MAKE} clean
.endfor

install:
.for proj in ${PROJECTS}
	cd ${proj} && ${MAKE} install
.endfor

