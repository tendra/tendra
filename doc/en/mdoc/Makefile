# $TenDRA$
# 
# the 'test' target is used for testing groff syntax.  If any
# errors show up during this target, it _should_ be fixable in
# the sgml.

.PATH: ${.CURDIR}/../manpages ${.CURDIR}../manpages/trans/common


# Sources.
MAN=		calculus.1 disp.1 lexi.1 pl.1 sid.1 tcc.1 \
		tccenv.5 tcpplus.1 tdfc2.1 tld.1 tnc.1 \
		tspec.1

MAN_TRANS=	680x0-sunos 80x86-cygwin32 80x86-freebsd \
		80x86-linux 80x86-netbsd 80x86-openbsd \
		80x86-sco 80x86-solaris 80x86-svr4.2 \
		alpha-freebsd alpha-osf1 hppa-hpux \
		mips-irix mips-ultrix power-aix \
		sparc-solaris sparc-sunos \

MAN_TRANS_SGML=	80x86-common.sgml alpha-common.sgml common.sgml \
		hppa-common.sgml mips-common.sgml options.sgml \
		power-common.sgml ppc601-common.sgml sparc-common.sgml


# Temporary file names.
MAN_TRANS_SGML_TMP=  ${MAN_TRANS_SGML:S/^/tmp./g}
MAN_TMP=	${MAN:R:S/^/tmp./g}
MAN_TRANS_TMP=	${MAN_TRANS:S/^/tmp./g}



# Targets
all: depend main

depend: ${MAN_TRANS_SGML} ${MAN_TMP} ${MAN_TRANS_TMP}

main: ${MAN} ${MAN_TRANS}


# Dependancies
${MAN_TRANS_SGML}:
	cat ../manpages/trans/common/${.TARGET} \
		|sed "s/^ *//" > ${.TARGET}


${MAN_TMP}:
	cat ${.CURDIR}/header |grep -v TenDRA > ${.CURDIR}/${.TARGET}
	echo "<refentry id=\"man-${.TARGET}\">" >> ${.CURDIR}/${.TARGET}
	cat ${.CURDIR}/../manpages/${.TARGET:S/tmp.//g}/manpage.sgml >> ${.CURDIR}/${.TARGET}
	echo "</refentry>" >> ${.CURDIR}/${.TARGET}


${MAN_TRANS_TMP}:
	@echo ${.TARGET}
	cat ${.CURDIR}/header |grep -v TenDRA > ${.CURDIR}/${.TARGET}
	echo "<refentry id=\"man-${.TARGET}\">" >> ${.CURDIR}/${.TARGET}
	cat ${.CURDIR}/../manpages/trans/${.TARGET:S/tmp.//g}/manpage.sgml >> ${.CURDIR}/${.TARGET}
	echo "</refentry>" >> ${.CURDIR}/${.TARGET}


# Actually build our manpages
${MAN}:
	cat tmp.${.TARGET:R} |sed "s/^ *//" \
	|nsgmls -gl -c ../../share/sgml/catalog - \
	|oinstant -d -croff.cmap -sroff.sdata -tdocbook-to-man.ts \
	> ${.TARGET}
	groff -Tascii -man ${.TARGET} > /dev/null


${MAN_TRANS}:
	cat tmp.${.TARGET} |sed "s/^ *//" \
	|nsgmls -gl -c ../../share/sgml/catalog - \
	|oinstant -d -croff.cmap -sroff.sdata -tdocbook-to-man.ts \
	> ${.TARGET}
	groff -Tascii -man ${.TARGET} > /dev/null


test:
	for i in ${MAN} ${MAN_TRANS}; do \
		groff -Tascii -man $$i > /dev/null; \
	done


clean:
	rm -f ${MANPAGES} ${MAN_TMP} ${MAN_TRANS_TMP} ${MAN_TRANS} ${MAN_TRANS_SGML} ${MAN}
