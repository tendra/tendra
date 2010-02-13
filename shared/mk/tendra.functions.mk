# TenDRA make functions
#
# $Id$

.if !defined(_TENDRA_FUNCTIONS_MK_)
_TENDRA_FUNCTIONS_MK_=1

# This shell function is inlined in rules below. Careful about quoting.
CONDCREATE=	Condcreate() {                               \
           	    for dir in $${*}; do                     \
           	        if ${TEST} ! -e $${dir}; then        \
           	            ${ECHO} "==> Creating $${dir}/"; \
           	                ${MKDIR} -p $${dir};         \
           	        fi;                                  \
           	    done;                                    \
           	}; Condcreate

.endif	# !defined(_TENDRA_FUNCTIONS_MK_)
