#!/bin/sh
# Simple tcc wrapper script
#
# $TenDRA$
#

TENDRA_BASEDIR=-INSTALL_PREFIX-

exec ${TENDRA_BASEDIR}/bin/tcc \
   -yTENDRA_BASEDIR=${TENDRA_BASEDIR} \
   -Y${TENDRA_BASEDIR}/env/default \
   ${@+"$@"}
