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

SUBSTVARS=	                                     \
    ${SED} -e '                                  \
        s,-PREFIX-,${PREFIX},g;                  \
        s,-PREFIX_BIN-,${PREFIX_BIN},g;          \
        s,-PREFIX_LIB-,${PREFIX_LIB},g;          \
        s,-PREFIX_LIBEXEC-,${PREFIX_LIBEXEC},g;  \
        s,-PREFIX_SHARE-,${PREFIX_SHARE},g;      \
        s,-PREFIX_INCLUDE-,${PREFIX_INCLUDE},g;  \
        s,-PREFIX_MAN-,${PREFIX_MAN},g;          \
        s,-PREFIX_TSPEC-,${PREFIX_TSPEC},g;      \
        s,-PREFIX_STARTUP-,${PREFIX_STARTUP},g;  \
        s,-PREFIX_ENV-,${PREFIX_ENV},g;          \
        s,-PREFIX_API-,${PREFIX_API},g;          \
        s,-PREFIX_LPI-,${PREFIX_LPI},g;          \
        s,-PREFIX_SYS-,${PREFIX_SYS},g;          \
        s,-PREFIX_TMP-,${PREFIX_TMP},g;          \
                                                 \
        s,-EXECFORMAT-,${EXECFORMAT},g;          \
        s,-BLDARCH-,${BLDARCH},g;                \
        s,-BLDARCHBITS-,${BLDARCHBITS},g;        \
        s,-OSFAM-,${OSFAM},g;                    \
        s,-OSVER-,${OSVER},g'                    \


.endif	# !defined(_TENDRA_FUNCTIONS_MK_)
