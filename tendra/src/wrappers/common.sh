#!-BIN_SH-
#
# -BIN_RUN- wrapper script
#
# $TenDRA: common.sh 1397 2003-08-25 06:34:47Z nonce $
#

# TenDRA settings
TENDRA_BASEDIR="-TENDRA_BASEDIR-"
TENDRA_VERSION="-TENDRA_VERSION-"


# binary settings
BIN_RUN="${TENDRA_BASEDIR}/bin/-BIN_RUN-"
OPTS_DEFAULT=""

#-INCLUDE-

# Execute -BIN_RUN- with our compiled options.

if [ -n "$DEBUG" ]; then
	-BIN_ECHO- ${BIN_RUN} ${OPTS_DEFAULT} ${@+"$@"}
else
	${BIN_RUN} ${OPTS_DEFAULT} ${@+"$@"}
fi;
