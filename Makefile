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

HOSTNAME!=	uname -n | cut -f1 -d.

OBJ_DIR?=     ${.CURDIR}/obj.${HOSTNAME}
OBJ_WWW?=     ${OBJ_DIR}-www
OBJ_DOC?=     ${OBJ_DIR}-doc
OBJ_APREFIX?= ${OBJ_DIR}-buildall
OBJ_BPREFIX?= ${OBJ_DIR}-bootstrap
OBJ_REBUILD?= ${OBJ_DIR}-rebuild
OBJ_REGEN?=   ${OBJ_DIR}-regen
OBJ_TEST?=    ${OBJ_BPREFIX}/test
OBJ_BOOT?=    ${OBJ_BPREFIX}/obj

# TODO: this should probably be the actual $PREFIX
OBJ_RPREFIX?=	${OBJ_REBUILD}

PREFIX?=	/usr/local


all: bootstrap

doc:

clean:

# TODO: depend on rebuild, and install to $PREFIX
install:

install-doc:

# for automated builds
build-allarch:
	cd ${.CURDIR}/trans && ${MAKE} -DALLARCH \
	    OBJ_DIR=${OBJ_APREFIX}/${project}
. for project in lexi libexds make_err make_tdf \
	tdfc2 sid tcc doc tld tnc tpl tspec
	cd ${.CURDIR}/${project} && ${MAKE} \
	    OBJ_DIR=${OBJ_APREFIX}/${project}
. endfor

# for automated builds
build-docs:
	${MAKE} doc
	${MAKE} test-doc

# for automated builds
build-bootstrap:
	${MAKE} bootstrap
	${MAKE} bootstrap-test
	# ${MAKE} bootstrap-rebuild
	# TODO: ${MAKE} bootstrap-regen


bootstrap: ${BOOTSTRAP_DEPS}
	mkdir -p "${OBJ_BPREFIX}/bin"
.for project in trans tdfc2 tld tnc tpl tspec
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
	mkdir -p "${OBJ_BPREFIX}/lib/tcc/map"
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
	    TCC=${OBJ_BPREFIX}/bin/tcc    \
	    TPL=${OBJ_BPREFIX}/bin/tpl    \
	    TNC=${OBJ_BPREFIX}/bin/tnc    \
	    TLD=${OBJ_BPREFIX}/bin/tld    \
	    install
	@echo "===> bootstrapping tdf into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/tdf && ${MAKE}      \
	    OBJ_DIR=${OBJ_BOOT}/tdf       \
	    PREFIX=${OBJ_BPREFIX}         \
	    TCC=${OBJ_BPREFIX}/bin/tcc    \
	    TPL=${OBJ_BPREFIX}/bin/tpl    \
	    TLD=${OBJ_BPREFIX}/bin/tld    \
	    install

bootstrap-test: ${OBJ_BPREFIX}/bin/tcc
.for project in tests
	cd ${.CURDIR}/${project} && ${MAKE} \
	    OBJ_DIR=${OBJ_TEST}/${project}  \
	    PREFIX=${OBJ_BPREFIX}           \
	    TCC=${OBJ_BPREFIX}/bin/tcc      \
	    TPL=${OBJ_BPREFIX}/bin/tpl      \
	    TNC=${OBJ_BPREFIX}/bin/tnc      \
	    TLD=${OBJ_BPREFIX}/bin/tld      \
	    test
.endfor

# XXX: placeholder until install: is present
bootstrap-install:
	mkdir -p "${PREFIX}/bin"
.for project in trans tdfc2 tld tnc tpl tspec
	@echo "===> installing ${project} into ${PREFIX}"
	cd ${.CURDIR}/${project} && ${MAKE} \
	    OBJ_DIR=${OBJ_BOOT}/${project}  \
	    PREFIX=${PREFIX} install
.endfor
	# TODO: these mkdirs are to be removed pending work on tcc
	mkdir -p "${PREFIX}/tmp"
	mkdir -p "${PREFIX}/lib/tcc/api"
	mkdir -p "${PREFIX}/lib/tcc/lpi"
	mkdir -p "${PREFIX}/lib/tcc/sys"
	mkdir -p "${PREFIX}/lib/tcc/map"
	@echo "===> installing tcc into ${PREFIX}"
	cd ${.CURDIR}/tcc && ${MAKE}   \
	    OBJ_DIR=${OBJ_BOOT}/tcc    \
	    PREFIX_INCLUDE=            \
	    PREFIX_MAN=                \
	    PREFIX_TMP=${PREFIX}/tmp   \
	    PREFIX=${PREFIX} install
	@echo "===> installing osdep into ${PREFIX}"
	cd ${.CURDIR}/osdep && ${MAKE} \
	    OBJ_DIR=${OBJ_BOOT}/osdep  \
	    PREFIX=${PREFIX}           \
	    TCC=${PREFIX}/bin/tcc      \
	    TPL=${PREFIX}/bin/tpl      \
	    TNC=${PREFIX}/bin/tnc      \
	    TLD=${PREFIX}/bin/tld      \
	    install
	@echo "===> installing tdf into ${PREFIX}"
	cd ${.CURDIR}/tdf && ${MAKE}   \
	    OBJ_DIR=${OBJ_BOOT}/tdf    \
	    PREFIX=${PREFIX}           \
	    TCC=${PREFIX}/bin/tcc      \
	    TPL=${PREFIX}/bin/tpl      \
	    TLD=${PREFIX}/bin/tld      \
	    install

bootstrap-rebuild:
	@echo "===> rebuilding with bootstrap from ${OBJ_BOOT} into ${OBJ_REBUILD}"
.for project in tspec tcc tpl tnc tdfc2 trans
	cd ${.CURDIR}/${project} && ${MAKE}   \
	    TCC=${OBJ_BPREFIX}/bin/tcc        \
	    OBJ_DIR=${OBJ_REBUILD}/${project} \
	    PREFIX=${OBJ_RPREFIX} install
.endfor

bootstrap-regen:
	@echo "===> bootstraping into ${OBJ_REGEN} for source regeneration"
.for project in sid calculus make_err
	@echo "===> bootstrapping ${project} into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/${project} && ${MAKE}     \
	    OBJ_DIR=${OBJ_REGEN}/obj/${project} \
	    PREFIX=${OBJ_REGEN} install
.endfor
.for project in calculus lexi make_err make_tdf tdfc2 sid tpl tspec
	@echo "===> regenerating for ${project}"
	cd ${.CURDIR}/${project} && ${MAKE}       \
	    OBJ_DIR=${OBJ_REGEN}/obj/${project}   \
	    SID=${OBJ_REGEN}/bin/sid              \
	    CALCULUS=${OBJ_REGEN}/bin/calculus    \
	    MAKE_ERR=${OBJ_REGEN}/bin/make_err    \
	    PREFIX=${OBJ_REGEN} regen-clean regen
.endfor
.for project in calculus lexi make_err make_tdf tdfc2 sid tpl tspec
	@echo "===> rebuilding for ${project}"
	cd ${.CURDIR}/${project} && ${MAKE}     \
	    OBJ_DIR=${OBJ_REGEN}/obj/${project} \
	    PREFIX=${OBJ_REGEN}
.endfor


test-doc:
	@echo "===> validating documents"
.for project in calculus trans lexi make_err \
	osdep tdf tdfc2 sid tcc doc tld tnc tpl tspec
	cd ${.CURDIR}/${project}/doc && ${MAKE} test
.endfor
	@echo "===> validating manpages"
.for project in calculus disp trans lexi make_err make_tdf \
	tdfc2 sid tcc doc tld tnc tpl tspec
	cd ${.CURDIR}/${project}/man && ${MAKE} test
.endfor

# XXX: just temporary
# XXX: need the per-project prefix that -DWEBSITE uses
doc:
	@echo "===> building documents"
.for project in calculus trans lexi make_err \
	osdep tdf tdfc2 sid tcc doc tld tnc tpl tspec
	cd ${.CURDIR}/${project}/doc && ${MAKE} \
	    OBJ_DIR=${OBJ_DOC}/${project}
.endfor
	@echo "===> building manpages"
.for project in calculus disp trans lexi make_err make_tdf \
	tdfc2 sid tcc tld tnc tpl tspec
	cd ${.CURDIR}/${project}/man && ${MAKE} \
	    OBJ_DIR=${OBJ_DOC}/${project}
.endfor

