#!/bin/sh

exec -PREFIX_LIBEXEC-/tcc \
    --SED${TCCENV:-"-PREFIX_ENV-"} --CFE -Ybase -Ydefault ${@+"$@"}

