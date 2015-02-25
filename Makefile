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

REVISION!=	svn info | grep ^Revision: | cut -f2 -d' '
RELEASE?=	svn:${REVISION}

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

# set these to build for a particular target
# e.g. make TARGETARCH=x32_64
TARGETARCH?=

.if !empty(TARGETARCH)
TARGETFLAGS+= BLDARCH=${TARGETARCH}
.endif

# XXX: assumes GNU ld
REBUILDFLAGS!=                            \
    case "${TARGETARCH}" in               \
        x32_64) echo LDFLAGS=-melf_i386;; \
        *)      echo '';;                 \
    esac;

all: bootstrap

doc:

clean:

# TODO: depend on rebuild instead, and install to $PREFIX
install:

install-doc:

# for automated builds
build-allarch:
	cd ${.CURDIR}/trans && ${MAKE} -DALLARCH \
	    OBJ_DIR=${OBJ_APREFIX}/${project}
. for project in lexi libexds make_err make_tdf \
	tdfc2 sid tcc tld tnc tpl tspec
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
	@echo "===> bootstrapping trans into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/trans && ${MAKE}      \
	    OBJ_DIR=${OBJ_BOOT}/trans       \
	    PREFIX=${OBJ_BPREFIX}           \
	    RELEASE=${RELEASE}              \
	    ${TARGETFLAGS}                  \
	    install
.for project in tdfc2 tld tnc tpl tspec
	@echo "===> bootstrapping ${project} into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/${project} && ${MAKE} \
	    OBJ_DIR=${OBJ_BOOT}/${project}  \
	    PREFIX=${OBJ_BPREFIX}           \
	    RELEASE=${RELEASE}              \
	    install
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
	    PREFIX=${OBJ_BPREFIX}         \
	    RELEASE=${RELEASE}            \
	    ${TARGETFLAGS}                \
	    install
	@echo "===> bootstrapping osdep into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/osdep && ${MAKE}    \
	    OBJ_DIR=${OBJ_BOOT}/osdep     \
	    PREFIX=${OBJ_BPREFIX}         \
	    TCC=${OBJ_BPREFIX}/bin/tcc    \
	    TPL=${OBJ_BPREFIX}/bin/tpl    \
	    TNC=${OBJ_BPREFIX}/bin/tnc    \
	    TLD=${OBJ_BPREFIX}/bin/tld    \
	    RELEASE=${RELEASE}            \
	    ${TARGETFLAGS}                \
	    install
	@echo "===> bootstrapping tdf into ${OBJ_BPREFIX}"
	cd ${.CURDIR}/tdf && ${MAKE}      \
	    OBJ_DIR=${OBJ_BOOT}/tdf       \
	    PREFIX=${OBJ_BPREFIX}         \
	    TCC=${OBJ_BPREFIX}/bin/tcc    \
	    TPL=${OBJ_BPREFIX}/bin/tpl    \
	    TLD=${OBJ_BPREFIX}/bin/tld    \
	    RELEASE=${RELEASE}            \
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

bootstrap-rebuild:
	mkdir -p "${OBJ_RPREFIX}/bin"
	@echo "===> rebuilding with bootstrap for trans from ${OBJ_BOOT} into ${OBJ_REBUILD}"
	cd ${.CURDIR}/trans && ${MAKE}      \
	    OBJ_DIR=${OBJ_REBUILD}/trans    \
	    TCC=${OBJ_BPREFIX}/bin/tcc      \
	    PREFIX=${OBJ_RPREFIX}           \
	    RELEASE=${RELEASE}              \
	    ${TARGETFLAGS}                  \
	    ${REBUILDFLAGS}                 \
	    install
.for project in tld tspec tpl tnc tdfc2 sid lexi make_tdf make_err calculus disp libexds
	@echo "===> rebuilding with bootstrap for ${project} from ${OBJ_BOOT} into ${OBJ_REBUILD}"
	cd ${.CURDIR}/${project} && ${MAKE}   \
	    OBJ_DIR=${OBJ_REBUILD}/${project} \
	    PREFIX=${OBJ_RPREFIX}             \
	    TCC=${OBJ_BPREFIX}/bin/tcc        \
	    RELEASE=${RELEASE}                \
	    ${REBUILDFLAGS}                   \
	    install
.endfor
	# TODO: these mkdirs are to be removed pending work on tcc
	mkdir -p "${OBJ_RPREFIX}/tmp"
	mkdir -p "${OBJ_RPREFIX}/lib/tcc/api"
	mkdir -p "${OBJ_RPREFIX}/lib/tcc/lpi"
	mkdir -p "${OBJ_RPREFIX}/lib/tcc/sys"
	mkdir -p "${OBJ_RPREFIX}/lib/tcc/map"
	@echo "===> rebuilding with bootstrap for tcc from ${OBJ_BOOT} into ${OBJ_REBUILD}"
	cd ${.CURDIR}/tcc && ${MAKE}      \
	    OBJ_DIR=${OBJ_REBUILD}/tcc    \
	    TCC=${OBJ_BPREFIX}/bin/tcc    \
	    PREFIX_INCLUDE=               \
	    PREFIX_MAN=                   \
	    PREFIX_TMP=${OBJ_RPREFIX}/tmp \
	    PREFIX=${OBJ_RPREFIX}         \
	    RELEASE=${RELEASE}            \
	    ${TARGETFLAGS}                \
	    ${REBUILDFLAGS}               \
	    install
	@echo "===> rebuilding with bootstrap for osdep from ${OBJ_BOOT} into ${OBJ_REBUILD}"
	cd ${.CURDIR}/osdep && ${MAKE}    \
	    OBJ_DIR=${OBJ_REBUILD}/osdep  \
	    PREFIX=${OBJ_RPREFIX}         \
	    TCC=${OBJ_RPREFIX}/bin/tcc    \
	    TPL=${OBJ_RPREFIX}/bin/tpl    \
	    TNC=${OBJ_RPREFIX}/bin/tnc    \
	    TLD=${OBJ_RPREFIX}/bin/tld    \
	    RELEASE=${RELEASE}            \
	    ${TARGETFLAGS}                \
	    ${REBUILDFLAGS}               \
	    install
	@echo "===> rebuilding with bootstrap for tdf from ${OBJ_BOOT} into ${OBJ_REBUILD}"
	cd ${.CURDIR}/tdf && ${MAKE}      \
	    OBJ_DIR=${OBJ_REBUILD}/tdf    \
	    PREFIX=${OBJ_RPREFIX}         \
	    TCC=${OBJ_RPREFIX}/bin/tcc    \
	    TPL=${OBJ_RPREFIX}/bin/tpl    \
	    TLD=${OBJ_RPREFIX}/bin/tld    \
	    RELEASE=${RELEASE}            \
	    ${REBUILDFLAGS}               \
	    install

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
.for project in calculus lexi make_err \
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

