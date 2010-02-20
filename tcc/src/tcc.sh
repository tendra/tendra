#!/bin/sh

exec @@MACH_BASE@@/bin/tcc -yTENDRA_BASEDIR=@@PREFIX@@ -Y@@PREFIX@@/lib/tcc/env/default ${@+"$@"}
