# $TenDRA$


DEPEND_SRC=	${MAN1} ${MAN5}

SED_OPTS=	-e "s/@TENDRA_VERSION@/${VER_TENDRA}/g"

# installers
680x0.sunos.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_680x0_SUNOS}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.cygwin32.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_CYGWIN32}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.freebsd.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_FREEBSD}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.linux.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_LINUX}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.netbsd.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_NETBSD}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.openbsd.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_OPENBSD}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.sco.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_SCO}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.solaris.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_SOLARIS}/g" \
		> ${.OBJDIR}/${.TARGET}

80x86.svr4.2.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_80x86_SVR42}/g" \
		> ${.OBJDIR}/${.TARGET}

alpha.freebsd.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_ALPHA_FREEBSD}/g" \
		> ${.OBJDIR}/${.TARGET}

alpha.osf1.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_ALPHA_OSF1}/g" \
		> ${.OBJDIR}/${.TARGET}

hppa.hpux.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_HPPA_HPUX}/g" \
		> ${.OBJDIR}/${.TARGET}

mips.irix.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_MIPS_IRIX}/g" \
		> ${.OBJDIR}/${.TARGET}

mips.ultrix.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_MIPS_ULTRIX}/g" \
		> ${.OBJDIR}/${.TARGET}

power.aix.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_POWER_AIX}/g" \
		> ${.OBJDIR}/${.TARGET}

ppc601.aix.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_SPARC_SOLARIS}/g" \
		> ${.OBJDIR}/${.TARGET}

sparc.solaris.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_SPARC_SUNOS}/g" \
		> ${.OBJDIR}/${.TARGET}

sparc.sunos.trans.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_INST_SPARC_SUNOS}/g" \
		> ${.OBJDIR}/${.TARGET}


# producers
tcpplus.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_PROD_CPP}/g" \
		> ${.OBJDIR}/${.TARGET}

tdfc2.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_PROD_C}/g" \
		> ${.OBJDIR}/${.TARGET}



# tools
disp.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_DISP}/g" \
		> ${.OBJDIR}/${.TARGET}

pl.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_PL}/g" \
		> ${.OBJDIR}/${.TARGET}

tcc.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_TCC}/g" \
		> ${.OBJDIR}/${.TARGET}

tchk.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@//g" \
		> ${.OBJDIR}/${.TARGET}

tld.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_TLD}/g" \
		> ${.OBJDIR}/${.TARGET}

tnc.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_TNC}/g" \
		> ${.OBJDIR}/${.TARGET}

tspec.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_TSPEC}/g" \
		> ${.OBJDIR}/${.TARGET}


# utilities
calculus.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_CALCULUS}/g" \
		> ${.OBJDIR}/${.TARGET}

lexi.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_LEXI}/g" \
		> ${.OBJDIR}/${.TARGET}

sid.1:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@/${VER_SID}/g" \
		> ${.OBJDIR}/${.TARGET}


# orphans
tccenv.5:
	cat ${.CURDIR}/${.TARGET} \
		| ${BIN_SED} ${SED_OPTS} -e "s/@PROGRAM_VERSION@//g" \
		> ${.OBJDIR}/${.TARGET}

CLEANFILES=	${MAN1} ${MAN5}
