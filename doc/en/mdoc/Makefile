# $TenDRA$
# 
# the 'test' target is used for testing groff syntax.  If any
# errors show up during this target, it _should_ be fixable in
# the sgml.

# Transformation rules and source path's
.SUFFIXES:      .1 .5 .sgml .tmp .sgml_tmp .man_tmp
.PATH: ${.CURDIR}/../manpages ${.CURDIR}/../manpages/trans/common ${.CURDIR}/tmp


# Binaries
BIN_SH?=	sh
BIN_OINSTANT?=	oinstant
BIN_SED?=	sed
BIN_CAT?=	cat
BIN_NSGMLS?=	nsgmls
BIN_GROFF?=	groff


# Sources.
MAN=		calculus.1 \
		disp.1 \
		lexi.1 \
		make_tdf.1 \
		mkerr.1\
		pl.1 \
		sid.1 \
		tcc.1 \
		tccenv.5 \
		tchk.1 \
		tcpplus.1 \
		tdfc2.1 \
		tld.1 \
		tnc.1 \
		tspec.1

MAN_TRANS=	680x0.sunos.trans.1 \
		80x86.cygwin32.trans.1 \
		80x86.freebsd.trans.1 \
		80x86.linux.trans.1 \
		80x86.netbsd.trans.1 \
		80x86.openbsd.trans.1 \
		80x86.sco.trans.1 \
		80x86.solaris.trans.1 \
		80x86.svr4.2.trans.1 \
		alpha.freebsd.trans.1 \
		alpha.osf1.trans.1 \
		hppa.hpux.trans.1 \
		mips.irix.trans.1 \
		mips.ultrix.trans.1 \
		power.aix.trans.1 \
		ppc601.aix.trans.1 \
		sparc.solaris.trans.1 \
		sparc.sunos.trans.1


MAN_TRANS_SGML=	680x0-common.sgml 80x86-common.sgml alpha-common.sgml common.sgml \
		hppa-common.sgml mips-common.sgml options.sgml \
		power-common.sgml ppc601-common.sgml sparc-common.sgml


# Temporary target names.
MAN_TMP=		${MAN:R:S/$/.man_tmp/g}
MAN_TRANS_TMP=		${MAN_TRANS:R:S/$/.man_tmp/g}
MAN_TRANS_SGML_TMP=	${MAN_TRANS_SGML:R:S/$/.sgml_tmp/g}




# Targets
# We have to invoke both targets seperately, make caches the results
# of the .PATH directory list when invoked.  Unfortunatly this ensures
# any auto-generated files are not picked up.  So invoke seperate instances
# of make to avoid this problem.


.MAIN: all
all: depend main
depend:
	@echo "==> Building dependancies"
	env MAKEOBJDIR=${.CURDIR}/tmp DEPEND=yes ${MAKE} depend-all
depend-all: tmpdir ${MAN_TRANS_SGML_TMP} ${MAN_TMP} ${MAN_TRANS_TMP}

main:
	@echo "==> Building manpages"
	env MAKEOBJDIR=${.CURDIR} ${MAKE} main-all
main-all: ${MAN} ${MAN_TRANS}


# Temporary directory
tmpdir:
	mkdir -p ${.CURDIR}/tmp


# Dependancies
# We need to cat over the common files because docbook-to-man does not like
# leading whitespace, it includes them in the output.
.sgml.sgml_tmp:
	cat ${.IMPSRC} \
		|sed "s/^ *//" > ${.CURDIR}/tmp/${.TARGET}

# Note: this has to be wrapped with a defined() due to the fact the target name is the
# same as the originating source for our .man_tmp.(1|2) down below.  This causes make
# to regenerate this before invoking those rules.  There is no real way around this without
# making things much more complex (that i know of) so I opted for a defined().
# if you have a better way, please share!
.if defined(DEPEND)
${MAN_TMP}:
	${BIN_SH} ${.CURDIR}/gen.sh ${.TARGET:S/.tmp//g:R} > ${.CURDIR}/tmp/${.TARGET}

${MAN_TRANS_TMP}:
	${BIN_SH} ${.CURDIR}/gen.sh ${.TARGET:S/.trans.man_tmp//g:S/./-/} > ${.CURDIR}/tmp/${.TARGET}
.endif


# Our final transformation rule
.man_tmp.1 .man_tmp.5:
	${BIN_CAT} ${.IMPSRC} |sed "s/^ *//" \
	|${BIN_NSGMLS} -gl -c ../../share/sgml/catalog - \
	|${BIN_OINSTANT} -d -croff.cmap -sroff.sdata -t../../share/misc/docbook-to-man.ts \
	> ${.CURDIR}/${.TARGET}
	${BIN_GROFF} -Tascii -man ${.CURDIR}/${.TARGET} > /dev/null


# For testing the resulting groff manpages
test:
	for i in ${MAN} ${MAN_TRANS}; do \
		echo "==> $$i"; \
		${BIN_GROFF} -Tascii -man $$i > /dev/null; \
	done


clean:
	rm -rf ${.CURDIR}/tmp
	rm -f ${MAN} ${MAN_TRANS}
