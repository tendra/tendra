# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_FUNCTIONS_MK_)
_TENDRA_FUNCTIONS_MK_=1

# These shell functions are inlined in makefile rules. Careful about quoting.

CONDCREATE= Condcreate() {                       \
        for dir in $${*}; do                     \
            if ${TEST} ! -e $${dir}; then        \
                ${ECHO} "==> Creating $${dir}/"; \
                ${MKDIR} -p $${dir};             \
            fi;                                  \
        done;                                    \
    }; Condcreate


.endif
