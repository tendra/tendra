# $TenDRA$
# 
# the 'test' target is used for testing groff syntax.  If any
# errors show up during this target, it _should_ be fixable in
# the sgml.


.PATH: ${.CURDIR}/../manpages

MANPAGES=	calculus.1 disp.1 lexi.1 pl.1 sid.1 tcc.1 \
		tccenv.5 tcpplus.1 tdfc2.1 tld.1 tnc.1 \
		tspec.1

MAN_TMP=	${MANPAGES:R:S/^/tmp./g}

all: main

main: ${MAN_TMP} ${MANPAGES}


${MAN_TMP}:
	cat ${.CURDIR}/header |grep -v TenDRA > ${.CURDIR}/${.TARGET}
	echo "<refentry id=\"man-${.TARGET}\">" >> ${.CURDIR}/${.TARGET}
	cat ${.CURDIR}/../manpages/${.TARGET:S/tmp.//g}/manpage.sgml >> ${.CURDIR}/${.TARGET}
	echo "</refentry>" >> ${.CURDIR}/${.TARGET}


${MANPAGES}:
	cat tmp.${.TARGET:R} |sed "s/^ *//" \
	|nsgmls -gl -c ../../share/sgml/catalog - \
	|oinstant -d -croff.cmap -sroff.sdata -tdocbook-to-man.ts \
	> ${.TARGET}
	groff -Tascii -man ${.TARGET} > /dev/null

test:
	for i in ${MANPAGES}; do \
		groff -Tascii -man $$i > /dev/null; \
	done


clean:
	rm -f ${MANPAGES} ${MANPAGES:R:S/^/tmp./g}
