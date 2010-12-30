#!/bin/sh

exec @@PREFIX@@/libexec/tcc -yTENDRA_BASEDIR=@@PREFIX@@ \
	--SED@@PREFIX@@/lib/tcc/env --CFE -Ydefault ${@+"$@"}

