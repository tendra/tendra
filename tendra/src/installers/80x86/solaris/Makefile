# $TenDRA$


PROG=	trans

# installers/80x86/solaris
SRCS=	assembler.c diag_out.c dw2_config.c machine.c

# installers/common/dwarf2
SRCDIRS+= common/dwarf2
SRCS+=	dw2_abbrev.c dw2_basic.c dw2_common.c dw2_entries.c dw2_iface.c \
	dw2_info.c dw2_lines.c dw2_locdata.c dw2_types.c

CFLAGS+=	-I${.CURDIR}/../../common/dwarf2

# installers/80x86
.include "${.CURDIR}/../Makefile.inc"

# installers/
.include "${.CURDIR}/../../Makefile.inc"

.include "${.CURDIR}/../../../../mk/base/tendra.prog.mk"
