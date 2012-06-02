#!/bin/sh

exec -PREFIX_LIBEXEC-/tcc \
    -Ybase -Ydefault ${@+"$@"}

