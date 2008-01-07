# $TenDRA$

CFLAGS+=	-I${.CURDIR}/../../common/dwarf2


PROG=  trans

SRCS+=	dw2_abbrev.c dw2_basic.c dw2_common.c dw2_entries.c dw2_iface.c \
	dw2_info.c dw2_lines.c dw2_locdata.c dw2_types.c


# installers/common/dwarf2
SRCDIRS+= common/dwarf2


# installers/sparc/solaris
SRCS+= sparcdiags.c dw2_config.c


# installers/sparc
.include "${.CURDIR}/../Makefile.inc"

# installers/
.include "${.CURDIR}/../../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"

