#!/bin/sh

exec @@EXEC_BIN@@/tcc -yTENDRA_BASEDIR=@@PREFIX@@ -Y@@PREFIX@@/lib/tcc/env/default ${@+"$@"}
