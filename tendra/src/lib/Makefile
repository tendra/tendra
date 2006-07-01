# $TenDRA: Makefile 1717 2004-03-23 20:37:45Z stefanf $

SUBDIR+=	startup

# Installs the tcc environment files
SUBDIR+=	env

# This installs system dependant headers required by apis
SUBDIR+=	machines

# API tspec source.
SUBDIR+=	apis

# Required by apis/lib/ansi
SUBDIR+=	sys

# Required by apis/lib/cpp
SUBDIR+=	libcpp/tokens

# Required by libcpp, libtdf, machines/*/tokens
SUBDIR+=	apis/lib

# Requires apis/lib/ansi, apis/lib/posix
SUBDIR+=	machines/${SRC_MACHINES}/tokens

# Requires everything :)
SUBDIR+=	libcpp libtdf

# Ada runtime
SUBDIR+=	libada

.include "${.CURDIR}/../../mk/base/tendra.subdir.mk"
