#!/bin/sh

exec @@MACH_BASE@@/bin/tcc -yTENDRA_BASEDIR=@@PREFIX@@ -Y@@MACH_BASE@@/env/default ${@+"$@"}
