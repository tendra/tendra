# $TenDRA$
#
# This file holds all our current version info and targets.
#
# Note: when you make changes to *any* common directories you must bump the version
#       of all consumers.  Eg, if you've made any bugfixes or changes to 
#       installers/common, remember to bump the version of *all* installers.
#       This does however exclude installers/common/(diag|reader|dwarf.) as they
#       have their own version.
#
#       libten has its own version.  Rather than bump the consumer versions
#       (everything, pretty much) it makes more sense for it to have it's own
#       version.
#
# CVS builds will have -cvs <date> added to the version string
# SNAP builds will have -snap <date of snapshot>
# RELEASE, BETA, ALPHA will be marked as such, build date will also be compiled
# into the version string.
#
#
# Version number rules:
#
# The first digit denotes major changes, these will be *all* bumped for every 
# major release of TenDRA (6,7,8 etc).  They can be bumped on their own, for 
# instance if a major change or re-write happens.
#
# The second digit denotes either API breakage, or numerous critical bugfixes, 
# it's a 'good idea' to be careful between upgrades if this number is changed.
#
# The third represents minor bug fixes and changes, end-users won't have to 
# worry about this changing.


# the big kahuna.
VER_TENDRA=	5.0.0

# libten
VER_LIBTEN=	1.0.0

# lib/tdf
VER_TDF=	4.1.0


# utilities/calculus
VER_CALCULUS=	1.3.0

# utilities/lexi
VER_LEXI=	1.3.0

# utilities/make_tdf
VER_MAKE_TDF=	2.0.0

# utilities/sid
VER_SID=	1.9.13

# utilities/mkerr
VER_MKERR=	1.0.0


# tools/disp
VER_DISP=	1.5.0

# tools/pl
VER_PL=		5.0.0

# tools/tcc
VER_TCC=	4.0.0

# tools/tld
VER_TLD=	4.0.7

# tools/tnc
VER_TNC=	1.0.0

# tools/tspec
VER_TSPEC=	2.10.0


# producers/c
VER_PROD_C=	1.8.2

# producers/cpp
VER_PROD_CPP=	1.8.2


# common/construct
VER_INST_CONSTRUCT=	5.7.0

# common/diag
VER_INST_DIAG=		5.8.0

# common/reader
VER_INST_READER=	5.6.0

# common/dwarf
VER_INST_DWARF=		1.10.0

# common/dwarf2
VER_INST_DWARF2=	2.12.0


# 680x0/sunos
VER_INST_680x0_SUNOS=		1.6.5

# 80x86/cygwin32
VER_INST_80x86_CYGWIN32=	5.12.0

# 80x86/freebsd
VER_INST_80x86_FREEBSD=		5.12.0

# 80x86/linux
VER_INST_80x86_LINUX=		5.12.0

# 80x86/netbsd
VER_INST_80x86_NETBSD=		5.12.0

# 80x86/openbsd
VER_INST_80x86_OPENBSD=		5.12.0

# 80x86/sco
VER_INST_80x86_SCO=		5.12.0

# 80x86/solaris
VER_INST_80x86_SOLARIS=		5.12.0

# 80x86/svr4.2
VER_INST_80x86_SVR42=		5.12.0

# alpha/freebsd
VER_INST_ALPHA_FREEBSD=		2.4.11

# alpha/osf1
VER_INST_ALPHA_OSF1=		2.4.11

# hppa/hpux
VER_INST_HPPA_HPUX=		7.8.0

# mips/irix
VER_INST_MIPS_IRIX=		4.49.0

# mips/ultrix
VER_INST_MIPS_ULTRIX=		4.49.0

# power/aix
VER_INST_POWER_AIX=		4.26.0

# sparc/solaris
VER_INST_SPARC_SOLARIS=		3.11.0

# sparc/sunos
VER_INST_SPARC_SUNOS=		3.11.0


# This target allows us a nice visual representation of what the current versions are.

version-map:
	@echo "TenDRA	${VER_TENDRA}			TDF	${VER_TDF}"
	@echo "libten	${VER_LIBTEN}"
	@echo ""
	@echo "utilities:"
	@echo "calculus	${VER_CALCULUS}		lexi	${VER_LEXI}"
	@echo "make_tdf	${VER_MAKE_TDF}		sid	${VER_SID}"
	@echo "mkerr		${VER_MKERR}"
	@echo ""
	@echo "tools:"
	@echo "disp		${VER_DISP}		pl	 ${VER_PL}"
	@echo "tcc		${VER_TCC}		tld	 ${VER_TLD}"
	@echo "tnc		${VER_TNC}		tspec	 ${VER_TSPEC}"
	@echo ""
	@echo "procdures:"
	@echo "c		${VER_PROD_C}		cpp	${VER_PROD_CPP}"
	@echo ""
	@echo "installers/common:"
	@echo "construct	${VER_INST_CONSTRUCT}		diag	${VER_INST_DIAG}"
	@echo "reader		${VER_INST_READER}		dwarf	${VER_INST_DWARF}"
	@echo "dwarf2		${VER_INST_DWARF2}"
	@echo ""
	@echo "installers:"
	@echo "680x0/sunos	${VER_INST_680x0_SUNOS}"
	@echo "80x86/sunos	${VER_INST_80x86_CYGWIN32}		80x86/freebsd	${VER_INST_80x86_FREEBSD}"
	@echo "80x86/linux	${VER_INST_80x86_LINUX}		80x86/netbsd	${VER_INST_80x86_NETBSD}"
	@echo "80x86/openbsd	${VER_INST_80x86_OPENBSD}		80x86/sco	${VER_INST_80x86_SCO}"
	@echo "80x86/solaris	${VER_INST_80x86_SOLARIS}		80x86/svr4.2	${VER_INST_80x86_SVR42}"
	@echo "alpha/freebsd	${VER_INST_ALPHA_FREEBSD}		alpha/osf1	${VER_INST_ALPHA_OSF1}"
	@echo "hppa/hpux	${VER_INST_HPPA_HPUX}"
	@echo "mips/irix	${VER_INST_MIPS_IRIX}		mips/ultrix	${VER_INST_MIPS_ULTRIX}"
	@echo "power/aix	${VER_INST_POWER_AIX}"
	@echo "sparc/solaris	${VER_INST_SPARC_SOLARIS}		sparc/sunos	${VER_INST_SPARC_SUNOS}"
