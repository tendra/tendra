# $Id$

# Note to package maintainers: this top-level Makefile is provided for the
# convenience of people checking out the entire repository, who just want to
# try it out. It is not intended to be packaged; rather, each project is
# intended to stand alone, and those ought to be packaged separately.

PROJECTS+=	calculus
PROJECTS+=	disp
PROJECTS+=	installers-dra
PROJECTS+=	lexi
PROJECTS+=	libexds
PROJECTS+=	make_tdf
PROJECTS+=	make_err
PROJECTS+=	producers-dra
PROJECTS+=	sid
PROJECTS+=	tcc
PROJECTS+=	tld
PROJECTS+=	tnc
PROJECTS+=	tpl
#PROJECTS+=	tendra-doc
PROJECTS+=	tspec


all:
.for proj in ${PROJECTS}
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} all
.endfor

doc:
.for proj in ${PROJECTS}
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} doc
.endfor

clean:
.for proj in ${PROJECTS}
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} clean
.endfor

install:
.for proj in ${PROJECTS}
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} install
.endfor

install-doc:
.for proj in ${PROJECTS}
	cd ${.CURDIR}/${proj} && ${MAKE} OBJ_DIR=${.CURDIR}/obj/${proj} install-doc
.endfor

