# $TenDRA$

.if !defined(CROSS_TEST)

SUBDIR=	${MACH_CPU}/${BUILD_OS}

.else

SUBDIR+= 680x0/sunos

SUBDIR+=80x86/cygwin32 80x86/freebsd 80x86/linux 80x86/netbsd 80x86/openbsd \
	80x86/sco 80x86/solaris
# 80x86/svr4.2

SUBDIR+=alpha/freebsd alpha/osf1

SUBDIR+=hppa/hpux

#SUBDIR+=mips/irix mips/ultrix

#SUBDIR+=power/aix

#SUBDIR+=ppc601/aix

SUBDIR+=sparc/solaris sparc/sunos

.endif

.include "${.CURDIR}/../../mk/base/tendra.subdir.mk"

