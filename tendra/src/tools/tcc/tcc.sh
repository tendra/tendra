#!/bin/sh

exec @@MACH_BASE@@/bin/tcc -Y@@MACH_BASE@@/env/default ${@+"$@"}
