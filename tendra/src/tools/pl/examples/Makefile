# $TenDRA$

.PATH : ${.CURDIR}

DISP_FLAGS+=	-r

EX_SRCS=	EXCEPTTOK.pl SIGCSGI.pl SIGCULTRIX.pl Throw.pl \
		TryBITF.pl arep.pl big_test.pl errcode1.pl errcode2.pl \
		for90.pl inits.pl inits2.pl johnbug.pl  lists.pl \
		newprocs.pl nonC.pl primes4.pl primes8.pl test.pl testf90.pl \
		untidy.pl varpars.pl

FILES_J=	${EX_SRCS:R:S/$/.j/g}
FILES_DISP=	${EX_SRCS:R:S/$/.disp/g}

DEPEND_SRC=	${FILES_DISP}

# XXX: a.out seems to be a file disp leaves behind on error.
CLEANFILES+=	${FILES_J} ${FILES_DISP} .aout

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"

