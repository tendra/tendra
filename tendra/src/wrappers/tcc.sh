#!-BIN_SH-
#
# tcc wrapper script
#
# $TenDRA$
#

# TenDRA settings
TENDRA_BASEDIR="-TENDRA_BASEDIR-"
TENDRA_VERSION="-TENDRA_VERSION-"


# tcc settings
TCC_BIN="${TENDRA_BASEDIR}/bin/tcc"
OPTS_DEFAULT="-yTENDRA_BASEDIR=${TENDRA_BASEDIR} -Y${TENDRA_BASEDIR}/env/default -Ysystem"



# Execute tcc with our compiled options.

if [ -n "$DEBUG " ]; then
	${TCC_BIN} ${OPTS_DEFAULT} ${@+"$@"}
else
	-BIN_ECHO- ${TCC_BIN} ${OPTS_DEFAULT} ${@+"$@"}
fi;
