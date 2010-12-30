#!/bin/sh

exec -PREFIX_LIBEXEC-/tcc -yTENDRA_BASEDIR=-PREFIX- \
	--SED-PREFIX_ENV- --CFE -Ydefault ${@+"$@"}

