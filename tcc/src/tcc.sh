#!/bin/sh

exec -PREFIX_LIBEXEC-/tcc \
    --SED${TCCENV:-"-PREFIX_ENV-"}:-PREFIX_TSPEC-/TenDRA/env --CFE \
    -Ybase -Ydefault ${@+"$@"}

