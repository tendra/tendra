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
PROJECTS+=	producers-dra
PROJECTS+=	sid
PROJECTS+=	tcc
PROJECTS+=	tendra
#PROJECTS+=	tendra-doc
#PROJECTS+=	tendra-www
PROJECTS+=	tspec


all:
.for proj in ${PROJECTS}
. if !exists(${.CURDIR}/${proj}/Makefile.defs)
	cd ${.CURDIR}/${proj} && ./makedefs
. endif
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} all
.endfor

doc:
.for proj in ${PROJECTS}
. if !exists(${.CURDIR}/${proj}/Makefile.defs)
	cd ${.CURDIR}/${proj} && ./makedefs
. endif
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} doc
.endfor

clean:
.for proj in ${PROJECTS}
. if !exists(${.CURDIR}/${proj}/Makefile.defs)
	cd ${.CURDIR}/${proj} && ./makedefs
. endif
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} clean
.endfor

install:
.for proj in ${PROJECTS}
. if !exists(${.CURDIR}/${proj}/Makefile.defs)
	cd ${.CURDIR}/${proj} && ./makedefs
. endif
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} install
.endfor

# Render documentation for use on the tendra.org website.
doc-www:
.for proj in ${PROJECTS} tendra-doc
. if !exists(${.CURDIR}/${proj}/Makefile.defs)
	cd ${.CURDIR}/${proj} && ./makedefs
. endif
. if exists(${.CURDIR}/${proj})
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj-www/${proj} -DWEBSITE doc
. endif
.endfor

