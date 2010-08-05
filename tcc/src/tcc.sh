#!/bin/sh

exec @@EXEC_BIN@@/tcc -yTENDRA_BASEDIR=@@PREFIX@@ \
	--SED@@PREFIX@@/lib/tcc/env --CFE -Ydefault ${@+"$@"}

