# $Id$

# Note to package maintainers: this top-level Makefile is provided for the
# convenience of people checking out the entire repository, who just want to
# try it out. It is not intended to be packaged; rather, each project is
# intended to stand alone, and those ought to be packaged separately.
#
# The process for bootstrapping (building tendra with the system compiler) and
# rebuilding (using itself), which is performed by this makefile, is the same
# process that separate packages should undertake. The depencencies between
# packages have been arranged in order to make that as painless as possible.

OBJ_DIR?=     ${.CURDIR}/obj    # XXX: unused
OBJ_WWW?=     ${.CURDIR}/obj-www
OBJ_BPREFIX?= ${.CURDIR}/obj-bootstrap
OBJ_REBUILD?= ${.CURDIR}/obj-rebuild
OBJ_BOOT?=    ${OBJ_BPREFIX}/obj

# TODO: this should probably be the actual $PREFIX
OBJ_RPREFIX?=	${OBJ_REBUILD}


all: bootstrap

doc:

clean:

# TODO: depend on rebuild, and install to $PREFIX
install:

install-doc:


${OBJ_BOOT}/hello.c:
	echo '#include <stdio.h>'                    > ${.TARGET}
	echo                                        >> ${.TARGET}
	echo 'int main(void) {'                     >> ${.TARGET}
	echo '    puts("hello, world");'            >> ${.TARGET}
	echo '    return 0;'                        >> ${.TARGET}
	echo '}'                                    >> ${.TARGET}

${OBJ_BOOT}/hello-posix.c:
	echo '#include <unistd.h>'                   > ${.TARGET}
	echo                                        >> ${.TARGET}
	echo 'int main(void) {'                     >> ${.TARGET}
	echo '    write(0, "hello, world\\n", 13);' >> ${.TARGET}
	echo '    return 0;'                        >> ${.TARGET}
	echo '}'                                    >> ${.TARGET}

${OBJ_BOOT}/hello.cc:
	echo '#include <stdio>'                      > ${.TARGET}
	echo                                        >> ${.TARGET}
	echo 'int main() {'                         >> ${.TAGRET}
	echo '    puts("hello, world");'            >> ${.TARGET}
	echo '    return 0;'                        >> ${.TARGET}
	echo '}'                                    >> ${.TARGET}


bootstrap: ${BOOTSTRAP_DEPS}
	mkdir -p "${OBJ_BPREFIX}/bin"
.for project in installers-dra producers-dra tld tnc tpl tspec
	@echo "===> bootstrapping ${project} into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/${project} && ${MAKE} \
	    OBJ_DIR=${OBJ_BOOT}/${project}  \
	    PREFIX=${OBJ_BPREFIX} install
.endfor
	# TODO: these mkdirs are to be removed pending work on tcc
	mkdir -p "${OBJ_BPREFIX}/tmp"
	mkdir -p "${OBJ_BPREFIX}/lib/tcc/api"
	mkdir -p "${OBJ_BPREFIX}/lib/tcc/lpi"
	mkdir -p "${OBJ_BPREFIX}/lib/tcc/sys"
	@echo "===> bootstrapping tcc into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/tcc && ${MAKE}      \
	    OBJ_DIR=${OBJ_BOOT}/tcc       \
	    PREFIX_INCLUDE=               \
	    PREFIX_MAN=                   \
	    PREFIX_TMP=${OBJ_BPREFIX}/tmp \
	    PREFIX=${OBJ_BPREFIX} install
	@echo "===> bootstrapping osdep into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/osdep && ${MAKE}    \
	    OBJ_DIR=${OBJ_BOOT}/osdep     \
	    PREFIX=${OBJ_BPREFIX}         \
	    TSPEC_PREFIX=${TSPEC_BPREFIX} \
	    TCC=${OBJ_BPREFIX}/bin/tcc    \
	    TPL=${OBJ_BPREFIX}/bin/tpl    \
	    TNC=${OBJ_BPREFIX}/bin/tnc    \
	    TLD=${OBJ_BPREFIX}/bin/tld    \
	    install

bootstrap-test: ${OBJ_BOOT}/hello.c ${OBJ_BOOT}/hello-posix.c ${OBJ_BPREFIX}/bin/tcc
	${OBJ_BPREFIX}/bin/tcc -o ${OBJ_BOOT}/hello ${OBJ_BOOT}/hello.c
	${OBJ_BOOT}/hello
	${OBJ_BPREFIX}/bin/tcc -Yposix -o ${OBJ_BOOT}/hello-posix ${OBJ_BOOT}/hello-posix.c
	${OBJ_BOOT}/hello


bootstrap-rebuild:
	@echo "===> rebuilding with bootstrap from ${OBJ_BOOT} into ${OBJ_REBUILD}"
.for project in tspec tcc tpl tnc producers-dra installers-dra
	cd ${.CURDIR}/${project} && ${MAKE}   \
	    TCC=${OBJ_BPREFIX}/bin/tcc        \
	    OBJ_DIR=${OBJ_REBUILD}/${project} \
	    PREFIX=${OBJ_RPREFIX} install
.endfor

